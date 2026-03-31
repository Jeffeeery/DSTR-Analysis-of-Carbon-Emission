// Member 4 - [WK]
// program2_linkedlist/linkedlist_search.cpp - Search implementation for Linked List program

#include "linkedlist_search.h"
#include <chrono>
#include <cstdio>
#include <cstring>

using namespace std::chrono;

// Helper: check if a node's resident matches the search criteria
static bool matchesLL(const Resident& r, SearchCriteria criteria, const char* keyword) {
    // TODO: same logic as array version — compare ageGroup / transportMode / dailyDistance
    return false;
}

SearchResult linearSearchLL(const ResidentList& list, SearchCriteria criteria, const char* keyword) {
    // TODO:
    // 1. Record start time
    // 2. Traverse all nodes from head, call matchesLL(), collect matching indices
    // 3. Count comparisons (every node visited = 1 comparison)
    // 4. Return SearchResult
    SearchResult result;
    return result;
}

SearchResult orderedSearchLL(const ResidentList& list, SearchCriteria criteria, const char* keyword) {
    // NOTE: List must be sorted by the relevant field before calling this
    // TODO:
    // 1. Record start time
    // 2. Traverse from head; once past the target range, break early
    // 3. Collect matching indices, count comparisons
    // 4. Return SearchResult
    SearchResult result;
    return result;
}

void printSearchResultsLL(const ResidentList& list, const SearchResult& result,
                          SearchCriteria criteria, const char* keyword) {
    // TODO: print matched residents in a formatted table
    printf("Linked List Search Results for [%s]: %d match(es)\n", keyword, result.count);
}

void printSearchComparisonLL(const SearchResult& linear, const SearchResult& ordered) {
    printf("\n--- Linked List Search Performance Comparison ---\n");
    printf("%-25s %12s %15s %12s\n", "Method", "Matches", "Comparisons", "Time (ms)");
    printf("%-25s %12d %15d %12.4f\n", "Linear Search",    linear.count,  linear.comparisons,  linear.timeMs);
    printf("%-25s %12d %15d %12.4f\n", "Ordered Traversal",ordered.count, ordered.comparisons, ordered.timeMs);
}
