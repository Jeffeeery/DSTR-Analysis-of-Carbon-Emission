// Member 4 - [WK]
// program1_array/array_search.h - Search algorithm declarations for Array program

#ifndef ARRAY_SEARCH_H
#define ARRAY_SEARCH_H

#include "arraylist.hpp"

// Search criteria selector
enum SearchCriteria {
    SEARCH_BY_AGE_GROUP,
    SEARCH_BY_TRANSPORT,
    SEARCH_BY_DISTANCE_THRESHOLD
};

// Result struct to hold matched indices
struct SearchResult {
    int* indices;   // matched positions in the array
    int count;      // number of matches
    int comparisons; // number of comparisons made
    double timeMs;  // execution time in milliseconds

    SearchResult() : indices(nullptr), count(0), comparisons(0), timeMs(0.0) {}
    ~SearchResult() { delete[] indices; }
};

// Linear Search on unsorted array
// keyword: age group string / transport mode / distance value as string
SearchResult linearSearch(const ResidentArray& arr, SearchCriteria criteria, const char* keyword);

// Binary Search on sorted array (must be sorted by the matching field first)
SearchResult binarySearch(const ResidentArray& arr, SearchCriteria criteria, const char* keyword);

// Print matched residents as a formatted text table
void printSearchResults(const ResidentArray& arr, const SearchResult& result,
                        SearchCriteria criteria, const char* keyword);

// Print performance comparison between linear and binary search
void printSearchComparison(const SearchResult& linear, const SearchResult& binary);

#endif // ARRAY_SEARCH_H
