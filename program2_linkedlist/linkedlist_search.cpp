// Member 4 - [WK]
// program2_linkedlist/linkedlist_search.cpp - Search implementation for Linked List program

#include "linkedlist_search.h"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;
using namespace std::chrono;

// Helper: check if a node's resident matches the search criteria
static bool matchesLL(const Resident& r, SearchCriteria criteria, const char* keyword, int& comparisonCount) {
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

SearchResult linearSearchLL(const ResidentList& list, SearchCriteria criteria, const char* keyword) {
    SearchResult result;
    result.indices = new int[list.size()]; // Member 1 provided size() in linkedlist.cpp

    auto start = high_resolution_clock::now();
    Node* curr = list.getHead();
    int idx = 0;

    while (curr != nullptr) {
        if (matchesLL(curr->data, criteria, keyword, result.comparisons)) {
            result.indices[result.count++] = idx;
        }
        curr = curr->next;
        idx++;
    }

    auto end = high_resolution_clock::now();
    result.timeMs = duration<double, milli>(end - start).count();
    return result;
}

SearchResult orderedSearchLL(const ResidentList& list, SearchCriteria criteria, const char* keyword) {
    SearchResult result;
    result.indices = new int[list.size()];

    auto start = high_resolution_clock::now();
    Node* curr = list.getHead();
    int idx = 0;

    // Ordered Traversal Example: If searching for distance >= threshold
    // and the list is sorted by distance, we still check all.
    // However, if searching for a SPECIFIC age in a sorted list:
    while (curr != nullptr) {
        bool isMatch = matchesLL(curr->data, criteria, keyword, result.comparisons);

        if (isMatch) {
            result.indices[result.count++] = idx;
        } else {
            // Optimization: If list is sorted by Age and we are searching for
            // a specific Age Group, we could break early here.
            // For this general assignment, we will continue until the end
            // but note the "Early Break" possibility in your report.
        }

        curr = curr->next;
        idx++;
    }

    auto end = high_resolution_clock::now();
    result.timeMs = duration<double, milli>(end - start).count();
    return result;
}

void printSearchResultsLL(const ResidentList& list, const SearchResult& result,
                          SearchCriteria criteria, const char* keyword) {
    cout << "\nLinked List Results for [" << keyword << "]: " << result.count << " match(es) found\n";
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

    // Optimized approach: Traverse the matches directly
    for (int i = 0; i < result.count; i++) {
        Node* target = list.getAt(result.indices[i]);
        if (target != nullptr) { // Safety check
            const Resident& r = target->data;
            cout << left
                 << setw(12) << r.residentID    << " | "
                 << setw(4)  << r.age           << " | "
                 << setw(12) << r.transportMode << " | "
                 << setw(10) << fixed << setprecision(2) << r.dailyDistance    << " | "
                 << setw(10) << fixed << setprecision(4) << r.monthlyEmission  << " | "
                 << setw(15) << r.ageGroup      << "\n";
        }
    }
    cout << "--------------------------------------------------------------------------------------------------\n";
}

void printSearchComparisonLL(const SearchResult& linear, const SearchResult& ordered) {
    cout << "\n--- Linked List Search Performance Comparison ---\n";
    cout << left  << setw(25) << "Method"
         << right << setw(12) << "Matches"
         << right << setw(15) << "Comparisons"
         << right << setw(12) << "Time (ms)" << "\n";
    cout << left  << setw(25) << "Linear Search"
         << right << setw(12) << linear.count
         << right << setw(15) << linear.comparisons
         << right << setw(12) << fixed << setprecision(4) << linear.timeMs << "\n";
    cout << left  << setw(25) << "Ordered Traversal"
         << right << setw(12) << ordered.count
         << right << setw(15) << ordered.comparisons
         << right << setw(12) << fixed << setprecision(4) << ordered.timeMs << "\n";
}
