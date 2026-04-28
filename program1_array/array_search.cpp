// Member 4 - wk
// program1_array/array_search.cpp - Search experiments 

#include "array_search.h"
#include "array_sort.h"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;
using namespace std::chrono;

// Helper function: check if a record matches the user input
// Make sure Linear and Binary search use the same matching logic for fair comparison
static bool matches(const Resident& r, SearchCriteria criteria, const char* keyword, int& comparisonCount) {
    comparisonCount++; // Increment every time when checking a record 
    switch (criteria) {
        case SEARCH_BY_AGE_GROUP:
            return (string(r.ageGroup) == keyword);
        case SEARCH_BY_TRANSPORT:
            return (string(r.transportMode) == keyword);
        case SEARCH_BY_DISTANCE_THRESHOLD:
            // Convert string keyword to double for comparison
            return (r.dailyDistance >= stod(string(keyword)));
        default:
            return false;
    }
}

// Standard O(n) linear search on unsorted array 
SearchResult linearSearch(const ResidentArray& arr, SearchCriteria criteria, const char* keyword) {
    SearchResult result;
    result.indices = new int[arr.size()]; // Allocate max possible size for indices (worst case all match)


    auto start = high_resolution_clock::now();

    for (int i = 0; i < arr.size(); i++) {
        // If matches, store the index in result.indices and increment count
        if (matches(arr.get(i), criteria, keyword, result.comparisons)) {
            result.indices[result.count++] = i;
        }
    }

    auto end = high_resolution_clock::now();
    result.timeMs = duration<double, milli>(end - start).count();
    return result;
}

// Optimized O(log n) binary search on sorted array with specific criteria (must be sorted by the matching field first)
SearchResult binarySearch(const ResidentArray& arr, SearchCriteria criteria, const char* keyword) {
    SearchResult result;
    result.indices = new int[arr.size()];

    auto start = high_resolution_clock::now();

    int low = 0, high = arr.size() - 1;
    int firstMatch = -1;

    // Stage 1: Use binary search to find one match first, then expand around it to find all matches (for non-unique fields)
    while (low <= high) {
        result.comparisons++; // Track the "Divide" comparison step
        int mid = low + (high - low) / 2;

        int cmp;
        // Numerical comparison for distance threshold
        if (criteria == SEARCH_BY_DISTANCE_THRESHOLD) {
            double target = stod(string(keyword));
            if (arr.get(mid).dailyDistance == target) cmp = 0;
            else if (arr.get(mid).dailyDistance < target) cmp = -1;
            else cmp = 1;
        } else { // String comparison for age group or transport mode
            const char* currentVal = (criteria == SEARCH_BY_AGE_GROUP) ? arr.get(mid).ageGroup : arr.get(mid).transportMode;
            cmp = string(currentVal).compare(keyword);
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

    // Stage 2: Linear Expansion - Expand search to capture all identical matches (e.g., all "Bus" users)
    if (firstMatch != -1) {
        // Expand left and right from the first match to find all matches
        int temp = firstMatch;
        while (temp >= 0 && matches(arr.get(temp), criteria, keyword, result.comparisons)) {
            result.indices[result.count++] = temp;
            temp--;
        }
        // Start from the first match and expand right
        temp = firstMatch + 1;
        while (temp < arr.size() && matches(arr.get(temp), criteria, keyword, result.comparisons)) {
            result.indices[result.count++] = temp;
            temp++;
        }
    }

    auto end = high_resolution_clock::now();
    result.timeMs = duration<double, milli>(end - start).count();
    return result;
}

// Print matched residents as a formatted text table
// Use fixed-width columns for better readability, and include all relevant fields for context
void printSearchResults(const ResidentArray& arr, const SearchResult& result,
                        SearchCriteria criteria, const char* keyword) {
    cout << "\nSearch Results for [" << keyword << "]: " << result.count << " match(es) found\n";
    if (result.count == 0) return;

    cout << "--------------------------------------------------------------------------------------------------\n";
    cout << left
         << setw(12) << "ResidentID" << " | "
         << setw(4)  << "Age"        << " | "
         << setw(12) << "Transport"  << " | "
         << setw(10) << "Distance"   << " | "
         << setw(10) << "Emission"   << " | "
         << setw(15) << "Age Group"  << "\n";
    cout << "--------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < result.count; i++) {
        const Resident& r = arr.get(result.indices[i]);
        cout << left
             << setw(12) << r.residentID    << " | "
             << setw(4)  << r.age           << " | "
             << setw(12) << r.transportMode << " | "
             << setw(10) << fixed << setprecision(2) << r.dailyDistance    << " | "
             << setw(10) << fixed << setprecision(4) << r.monthlyEmission  << " | "
             << setw(15) << r.ageGroup      << "\n";
    }
    cout << "--------------------------------------------------------------------------------------------------\n";
}

// Print performance comparison between linear and binary search
void printSearchComparison(const SearchResult& linear, const SearchResult& binary) {
    cout << "\n--- Search Performance Comparison ---\n";
    cout << left  << setw(20) << "Method"
         << right << setw(12) << "Matches"
         << right << setw(15) << "Comparisons"
         << right << setw(12) << "Time (ms)" << "\n";
    cout << left  << setw(20) << "Linear Search"
         << right << setw(12) << linear.count
         << right << setw(15) << linear.comparisons
         << right << setw(12) << fixed << setprecision(4) << linear.timeMs << "\n";
    cout << left  << setw(20) << "Binary Search"
         << right << setw(12) << binary.count
         << right << setw(15) << binary.comparisons
         << right << setw(12) << fixed << setprecision(4) << binary.timeMs << "\n";
}
