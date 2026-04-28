// Member 5 - [EEE]
// shared/performance.cpp - Execution timing and performance logging

#include "performance.hpp"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// -------------------------------------------------------
// Timer
// -------------------------------------------------------

Timer::Timer() : running(false) {}

void Timer::start() {
    // (GeeksforGeeks, 2017)
    startTime = chrono::high_resolution_clock::now();
    running = true;
}

void Timer::stop() {
    // (GeeksforGeeks, 2017)
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

// Prints `width` copies of `ch` followed by newline — avoids string(int,char) constructor
static void printLine(char ch, int width) {
    for (int i = 0; i < width; i++) cout << ch;
    cout << "\n";
}

// PerfLog — static backing store
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
    cout << "\n";
    printLine('=', W);
    cout << "  PERFORMANCE ANALYSIS TABLE\n";
    printLine('=', W);
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
    printLine('-', W);

    for (int i = 0; i < logCount; i++) {
        const PerfRecord& r = logStore[i];
        cout << left
            << setw(12) << r.structure
            << setw(10) << r.operation
            << setw(18) << r.algorithm
            << setw(10) << r.city
            << right
            << setw(6)  << r.recordCount
            << setw(12) << fixed << setprecision(4) << r.timeMs
            << setw(14) << r.comparisons
            << setw(14) << r.memoryBytes
            << "\n";
    }
    printLine('=', W);
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
            printLine('-', 72);
            found = true;
        }

        const PerfRecord& r = logStore[i];
        cout << left
            << setw(12) << r.structure
            << setw(18) << r.algorithm
            << setw(10) << r.city
            << right
            << setw(6)  << r.recordCount
            << setw(12) << fixed << setprecision(4) << r.timeMs
            << setw(14) << r.comparisons
            << setw(14) << r.memoryBytes
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

static void copyField(char* dst, int capacity, const string& src) {
    auto copied = src.copy(dst, capacity - 1);
    dst[copied] = '\0';
}

PerfRecord makePerfRecord(
    const char* structure,
    const char* operation,
    const char* algorithm,
    const char* city,
    int recordCount,
    double timeMs,
    long long comparisons,
    int memoryBytes
) {
    PerfRecord rec;
    copyField(rec.structure, (int)sizeof(rec.structure), string(structure));
    copyField(rec.operation, (int)sizeof(rec.operation), string(operation));
    copyField(rec.algorithm, (int)sizeof(rec.algorithm), string(algorithm));
    copyField(rec.city,      (int)sizeof(rec.city),      string(city));
    rec.recordCount  = recordCount;
    rec.timeMs       = timeMs;
    rec.comparisons  = comparisons;
    rec.memoryBytes  = memoryBytes;
    return rec;
}
