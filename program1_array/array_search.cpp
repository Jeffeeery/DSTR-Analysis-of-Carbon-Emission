// Member 4 - [WK]
// program1_array/array_search.cpp - Search implementation for Array program

#include "array_search.h"
#include "array_sort.h"
#include <chrono>
#include <cstdio>
#include <cstring>

using namespace std::chrono;

// Helper: check if a resident matches the search criteria
static bool matches(const Resident& r, SearchCriteria criteria, const char* keyword) {
    // TODO: compare r.ageGroup / r.transportMode / r.dailyDistance against keyword
    return false;
}

SearchResult linearSearch(const ResidentArray& arr, SearchCriteria criteria, const char* keyword) {
    // TODO:
    // 1. Record start time
    // 2. Iterate all elements, call matches(), collect matching indices
    // 3. Count comparisons
    // 4. Return SearchResult with time, count, indices
    SearchResult result;
    return result;
}

SearchResult binarySearch(const ResidentArray& arr, SearchCriteria criteria, const char* keyword) {
    // NOTE: Array must be sorted by the relevant field before calling this
    // TODO:
    // 1. Record start time
    // 2. Standard binary search loop
    // 3. Expand left/right to collect all matching neighbours
    // 4. Return SearchResult with time, count, indices
    SearchResult result;
    return result;
}

void printSearchResults(const ResidentArray& arr, const SearchResult& result,
                        SearchCriteria criteria, const char* keyword) {
    // TODO: print matched residents in a formatted table
    printf("Search Results for [%s]: %d match(es) found\n", keyword, result.count);
}

void printSearchComparison(const SearchResult& linear, const SearchResult& binary) {
    printf("\n--- Search Performance Comparison ---\n");
    printf("%-20s %12s %15s %12s\n", "Method", "Matches", "Comparisons", "Time (ms)");
    printf("%-20s %12d %15d %12.4f\n", "Linear Search", linear.count, linear.comparisons, linear.timeMs);
    printf("%-20s %12d %15d %12.4f\n", "Binary Search", binary.count, binary.comparisons, binary.timeMs);
}
