// Member 5 - [EEE]
// shared/performance.cpp - Execution timing and performance logging

#include "performance.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// -------------------------------------------------------
// Timer
// -------------------------------------------------------

Timer::Timer() : running(false) {}

void Timer::start() {
    startTime = chrono::high_resolution_clock::now();
    running = true;
}

void Timer::stop() {
    endTime = chrono::high_resolution_clock::now();
    running = false;
}

// Duration between stop() and start() in milliseconds
double Timer::elapsedMs() const {
    auto dur = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
    return dur.count() / 1000.0;
}

// Duration in microseconds (useful when operation is sub-millisecond)
double Timer::elapsedUs() const {
    auto dur = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
    return static_cast<double>(dur.count());
}

// -------------------------------------------------------
// PerfLog — static backing store
// -------------------------------------------------------

static PerfRecord logStore[PerfLog::MAX_RECORDS];
static int        logCount = 0;

void PerfLog::add(const PerfRecord& rec) {
    if (logCount < MAX_RECORDS)
        logStore[logCount++] = rec;
}

int PerfLog::size() {
    return logCount;
}

const PerfRecord& PerfLog::get(int index) {
    return logStore[index];
}

void PerfLog::printTable() {
    if (logCount == 0) {
        cout << "\nNo performance records logged.\n";
        return;
    }

    const int W = 96;
    cout << "\n" << string(W, '=') << "\n";
    cout << "  PERFORMANCE ANALYSIS TABLE\n";
    cout << string(W, '=') << "\n";
    cout << left
         << setw(12) << "Structure"
         << setw(10) << "Operation"
         << setw(18) << "Algorithm"
         << setw(10) << "City"
         << right
         << setw(6)  << "N"
         << setw(12) << "Time(ms)"
         << setw(14) << "Comparisons"
         << setw(14) << "Mem(bytes)"
         << "\n";
    cout << string(W, '-') << "\n";

    for (int i = 0; i < logCount; i++) {
        const PerfRecord& r = logStore[i];
        cout << left
             << setw(12) << r.structure
             << setw(10) << r.operation
             << setw(18) << r.algorithm
             << setw(10) << r.city
             << right
             << setw(6)  << r.n
             << setw(12) << fixed << setprecision(4) << r.timeMs
             << setw(14) << r.comparisons
             << setw(14) << (long long)r.memBytes
             << "\n";
    }
    cout << string(W, '=') << "\n";
}

void PerfLog::printByOperation(const char* operation) {
    string op(operation);
    bool found = false;

    for (int i = 0; i < logCount; i++) {
        if (string(logStore[i].operation) != op) continue;

        if (!found) {
            cout << "\n--- " << op << " Records ---\n";
            cout << left
                 << setw(12) << "Structure"
                 << setw(18) << "Algorithm"
                 << setw(10) << "City"
                 << right
                 << setw(6)  << "N"
                 << setw(12) << "Time(ms)"
                 << setw(14) << "Comparisons"
                 << "\n";
            cout << string(72, '-') << "\n";
            found = true;
        }

        const PerfRecord& r = logStore[i];
        cout << left
             << setw(12) << r.structure
             << setw(18) << r.algorithm
             << setw(10) << r.city
             << right
             << setw(6)  << r.n
             << setw(12) << fixed << setprecision(4) << r.timeMs
             << setw(14) << r.comparisons
             << "\n";
    }
    if (!found)
        cout << "No records for operation: " << op << "\n";
}

void PerfLog::clear() {
    logCount = 0;
}

// -------------------------------------------------------
// makePerfRecord
// -------------------------------------------------------

static void copyField(char* dst, size_t cap, const string& src) {
    size_t n = src.copy(dst, cap - 1);
    dst[n] = '\0';
}

PerfRecord makePerfRecord(
    const char* structure,
    const char* operation,
    const char* algorithm,
    const char* city,
    int n,
    double timeMs,
    long long comparisons,
    size_t memBytes
) {
    PerfRecord rec;
    copyField(rec.structure, sizeof(rec.structure), string(structure));
    copyField(rec.operation, sizeof(rec.operation), string(operation));
    copyField(rec.algorithm, sizeof(rec.algorithm), string(algorithm));
    copyField(rec.city,      sizeof(rec.city),      string(city));
    rec.n           = n;
    rec.timeMs      = timeMs;
    rec.comparisons = comparisons;
    rec.memBytes    = memBytes;
    return rec;
}
