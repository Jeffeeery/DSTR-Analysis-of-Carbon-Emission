// Search implementation for Array program

#include "array_search.hpp"
#include "array_sort.hpp"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;
using namespace std::chrono;

// Helper: check if a resident matches the search criteria
static bool matches(const Resident& r, SearchCriteria criteria, const char* keyword, int& comparisonCount) {
    comparisonCount++; // Increment every time we check a record
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
    result.timeMs = duration<double, milli>(end - start).count();
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
            double target = stod(string(keyword));
            if (arr.get(mid).dailyDistance == target) cmp = 0;
            else if (arr.get(mid).dailyDistance < target) cmp = -1;
            else cmp = 1;
        } else {
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
    result.timeMs = duration<double, milli>(end - start).count();
    return result;
}

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
