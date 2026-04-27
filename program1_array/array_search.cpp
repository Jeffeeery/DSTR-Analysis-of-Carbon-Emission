// Member 4 - [WK]
// program1_array/array_search.cpp - Search implementation for Array program

#include "array_search.h"
#include "array_sort.h"
#include <chrono>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std::chrono;

// Helper: check if a resident matches the search criteria
static bool matches(const Resident& r, SearchCriteria criteria, const char* keyword, int& comparisonCount) {
    comparisonCount++; // Increment every time we check a record
    switch (criteria) {
        case SEARCH_BY_AGE_GROUP:
            return (strcmp(r.ageGroup, keyword) == 0);
        case SEARCH_BY_TRANSPORT:
            return (strcmp(r.transportMode, keyword) == 0);
        case SEARCH_BY_DISTANCE_THRESHOLD:
            // Convert string keyword to double for comparison
            return (r.dailyDistance >= atof(keyword));
        default:
            return false;
    }
}

SearchResult linearSearch(const ResidentArray& arr, SearchCriteria criteria, const char* keyword) {
    SearchResult result;
    result.indices = new int[arr.size()]; // Allocate max possible size
    
    auto start = high_resolution_clock::now();

    for (int i = 0; i < arr.size(); i++) {
        if (matches(arr.get(i), criteria, keyword, result.comparisons)) {
            result.indices[result.count++] = i;
        }
    }

    auto end = high_resolution_clock::now();
    result.timeMs = duration<double, std::milli>(end - start).count();
    return result;
}

SearchResult binarySearch(const ResidentArray& arr, SearchCriteria criteria, const char* keyword) {
    SearchResult result;
    result.indices = new int[arr.size()];
    
    auto start = high_resolution_clock::now();

    int low = 0, high = arr.size() - 1;
    int firstMatch = -1;

    while (low <= high) {
        result.comparisons++; // Track the "Divide" step
        int mid = low + (high - low) / 2;
        
        int cmp;
        if (criteria == SEARCH_BY_DISTANCE_THRESHOLD) {
            double target = atof(keyword);
            if (arr.get(mid).dailyDistance == target) cmp = 0;
            else if (arr.get(mid).dailyDistance < target) cmp = -1;
            else cmp = 1;
        } else {
            const char* currentVal = (criteria == SEARCH_BY_AGE_GROUP) ? arr.get(mid).ageGroup : arr.get(mid).transportMode;
            cmp = strcmp(currentVal, keyword);
        }

        if (cmp == 0) {
            firstMatch = mid;
            break; 
        } else if (cmp < 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    // Expand search to capture all identical matches (e.g., all "Bus" users)
    if (firstMatch != -1) {
        int temp = firstMatch;
        while (temp >= 0 && matches(arr.get(temp), criteria, keyword, result.comparisons)) {
            result.indices[result.count++] = temp;
            temp--;
        }
        temp = firstMatch + 1;
        while (temp < arr.size() && matches(arr.get(temp), criteria, keyword, result.comparisons)) {
            result.indices[result.count++] = temp;
            temp++;
        }
    }

    auto end = high_resolution_clock::now();
    result.timeMs = duration<double, std::milli>(end - start).count();
    return result;
}

void printSearchResults(const ResidentArray& arr, const SearchResult& result,
                        SearchCriteria criteria, const char* keyword) {
    printf("\nSearch Results for [%s]: %d match(es) found\n", keyword, result.count);
    if (result.count == 0) return;

    printf("--------------------------------------------------------------------------------------------------\n");
    printf("%-12s | %-4s | %-12s | %-10s | %-10s | %-15s\n", 
           "ResidentID", "Age", "Transport", "Distance", "Emission", "Age Group");
    printf("--------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < result.count; i++) {
        const Resident& r = arr.get(result.indices[i]);
        printf("%-12s | %-4d | %-12s | %-10.2f | %-10.4f | %-15s\n", 
               r.residentID, r.age, r.transportMode, r.dailyDistance, r.monthlyEmission, r.ageGroup);
    }
    printf("--------------------------------------------------------------------------------------------------\n");
}

void printSearchComparison(const SearchResult& linear, const SearchResult& binary) {
    printf("\n--- Search Performance Comparison ---\n");
    printf("%-20s %12s %15s %12s\n", "Method", "Matches", "Comparisons", "Time (ms)");
    printf("%-20s %12d %15d %12.4f\n", "Linear Search", linear.count, linear.comparisons, linear.timeMs);
    printf("%-20s %12d %15d %12.4f\n", "Binary Search", binary.count, binary.comparisons, binary.timeMs);
}
