// Member 3 - [WT]
// program2_linkedlist/linkedlist_sort.cpp - Sorting implementation for Linked List program

#include "linkedlist_sort.h"
#include <chrono>
#include <cstdio>

using namespace std::chrono;

// Helper: get the sort key value from a node
static double getKey(const Node* node, SortField field) {
    // TODO: return node->data.age / dailyDistance / monthlyEmission based on field
    return 0.0;
}

double insertionSortLL(ResidentList& list, SortField field, SortOrder order) {
    // TODO:
    // 1. Record start time
    // 2. Insertion sort by relinking nodes (do NOT copy data into an array)
    //    - Build a new sorted list by inserting each node into its correct position
    // 3. Call list.setHead(newHead) with the sorted head
    // 4. Return elapsed time in milliseconds
    return 0.0;
}

double selectionSortLL(ResidentList& list, SortField field, SortOrder order) {
    // TODO:
    // 1. Record start time
    // 2. Selection sort: repeatedly find min/max node and swap data values
    // 3. Return elapsed time in milliseconds
    return 0.0;
}

void printSortedTableLL(const ResidentList& list, SortField field, const char* algorithm) {
    // TODO: traverse list and print each node as a row in a formatted table
}

void printSortComparisonLL(double insertTime, double selectTime, const char* cityLabel) {
    printf("\n--- Linked List Sort Performance [%s] ---\n", cityLabel);
    printf("%-25s %15s\n", "Algorithm", "Time (ms)");
    printf("%-25s %15.4f\n", "Insertion Sort", insertTime);
    printf("%-25s %15.4f\n", "Selection Sort", selectTime);
}

void printCrossStructureComparison(
    double arraySortTime, const char* arrayAlgo,
    double llSortTime,    const char* llAlgo,
    const char* cityLabel
) {
    printf("\n--- Array vs Linked List Sort Comparison [%s] ---\n", cityLabel);
    printf("%-25s %-20s %15s\n", "Structure", "Algorithm", "Time (ms)");
    printf("%-25s %-20s %15.4f\n", "Array",       arrayAlgo, arraySortTime);
    printf("%-25s %-20s %15.4f\n", "Linked List", llAlgo,    llSortTime);
}
