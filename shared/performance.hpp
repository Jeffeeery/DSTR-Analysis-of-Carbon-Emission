// Execution timing and performance logging
#ifndef PERFORMANCE_HPP
#define PERFORMANCE_HPP

#include <chrono>


// Timer - wraps std::chrono::high_resolution_clock
class Timer {
private:
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point endTime;
    bool running;

public:
    Timer();

    // Begin timing
    void start();

    // End timing
    void stop();

    // Elapsed time in milliseconds (double precision)
    double elapsedMs() const;

    // Elapsed time in microseconds (for very fast ops)
    double elapsedUs() const;
};

// -------------------------------------------------------
// PerfRecord - one timing entry
// -------------------------------------------------------
struct PerfRecord {
    char structure[16];     // "Array" or "LinkedList"
    char operation[24];     // "Sort", "Search"
    char algorithm[24];     // "BubbleSort", "MergeSort", "Linear", "Binary", ...
    char city[16];          // "City A" / "City B" / "City C"
    int  recordCount;        // number of records in the dataset
    double timeMs;           // execution time in milliseconds
    long long comparisons;   // number of comparisons made (0 if not tracked)
    int memoryBytes;         // estimated memory footprint in bytes (0 if N/A)
};

// -------------------------------------------------------
// PerfLog - global record store (max 64 entries)
// -------------------------------------------------------
class PerfLog {
public:
    static const int MAX_RECORDS = 64;

    // Append a record. Silently drops if full.
    static void add(const PerfRecord& rec);

    // Number of records stored
    static int size();

    // Read-only access to a record at index
    static const PerfRecord& get(int index);

    // Print all records as formatted table
    static void printTable();

    // Print only records matching a given operation ("Sort" or "Search")
    static void printByOperation(const char* operation);

    // Wipe all records
    static void clear();
};

// -------------------------------------------------------
// Helper: build a PerfRecord with safe string copying
// -------------------------------------------------------
PerfRecord makePerfRecord(
    const char* structure,
    const char* operation,
    const char* algorithm,
    const char* city,
    int recordCount,
    double timeMs,
    long long comparisons = 0,
    int memoryBytes = 0
);

#endif // PERFORMANCE_HPP
