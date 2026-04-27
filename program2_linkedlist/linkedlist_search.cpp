// Member 4 - [WK]
// program2_linkedlist/linkedlist_search.cpp - Search experiments for Linked List-based implementation

#include "linkedlist_search.h"
#include <chrono>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std::chrono;

// Helper function: check if a node's resident matches the search criteria
static bool matchesLL(const Resident& r, SearchCriteria criteria, const char* keyword, int& comparisonCount) {
    comparisonCount++; // Increment every time when checking a record
    switch (criteria) {
        case SEARCH_BY_AGE_GROUP:
            return (strcmp(r.ageGroup, keyword) == 0);
        case SEARCH_BY_TRANSPORT:
            return (strcmp(r.transportMode, keyword) == 0);
        case SEARCH_BY_DISTANCE_THRESHOLD:
            // Convert string keyword to double for numeric comparison
            return (r.dailyDistance >= atof(keyword));
        default:
            return false;
    }
}

// Standard O(n) linear search on linked list
SearchResult linearSearchLL(const ResidentList& list, SearchCriteria criteria, const char* keyword) {
    SearchResult result;
    result.indices = new int[list.size()]; // Member 1 provided size() in linkedlist.cpp 
    
    auto start = high_resolution_clock::now();
    Node* curr = list.getHead(); // Start traversal at head pointer
    int idx = 0;

    // Standard linear search - Traverse the linked list from head to tail, checking each node's resident data against the search criteria
    while (curr != nullptr) {
        if (matchesLL(curr->data, criteria, keyword, result.comparisons)) {
            result.indices[result.count++] = idx;
        }
        curr = curr->next; // Move to the next node
        idx++;
    }

    auto end = high_resolution_clock::now();
    result.timeMs = duration<double, std::milli>(end - start).count();
    return result;
}

// Ordered Traversal Search Implementation 
SearchResult orderedSearchLL(const ResidentList& list, SearchCriteria criteria, const char* keyword) {
    SearchResult result;
    result.indices = new int[list.size()];
    
    auto start = high_resolution_clock::now();
    Node* curr = list.getHead();
    int idx = 0;

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
    result.timeMs = duration<double, std::milli>(end - start).count();
    return result;
}

// Print matched residents as a formatted text table
void printSearchResultsLL(const ResidentList& list, const SearchResult& result,
                          SearchCriteria criteria, const char* keyword) {
    printf("\nLinked List Results for [%s]: %d match(es) found\n", keyword, result.count);
    if (result.count == 0) return;

    printf("--------------------------------------------------------------------------------------------------\n");
    printf("%-12s | %-4s | %-12s | %-10s | %-10s | %-15s\n", 
           "ResidentID", "Age", "Transport", "Distance", "Emission", "Age Group");
    printf("--------------------------------------------------------------------------------------------------\n");

    // Iterate through the matched indices and print the corresponding resident data
    for (int i = 0; i < result.count; i++) {
        Node* target = list.getAt(result.indices[i]);
        if (target != nullptr) { // Safety check
            const Resident& r = target->data;
            printf("%-12s | %-4d | %-12s | %-10.2f | %-10.4f | %-15s\n", 
                   r.residentID, r.age, r.transportMode, r.dailyDistance, r.monthlyEmission, r.ageGroup);
        }
    }
    printf("--------------------------------------------------------------------------------------------------\n");
}

// Print performance comparison between linear and ordered traversal search
void printSearchComparisonLL(const SearchResult& linear, const SearchResult& ordered) {
    printf("\n--- Linked List Search Performance Comparison ---\n");
    printf("%-25s %12s %15s %12s\n", "Method", "Matches", "Comparisons", "Time (ms)");
    printf("%-25s %12d %15d %12.4f\n", "Linear Search",    linear.count,  linear.comparisons,  linear.timeMs);
    printf("%-25s %12d %15d %12.4f\n", "Ordered Traversal",ordered.count, ordered.comparisons, ordered.timeMs);
}
