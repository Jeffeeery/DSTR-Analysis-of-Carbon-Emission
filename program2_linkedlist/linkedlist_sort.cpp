// Member 3 - [WT]
// program2_linkedlist/linkedlist_sort.cpp - Sorting implementation for Linked List program

#include "linkedlist_sort.h"
#include <chrono>
#include <iomanip>
#include <iostream>

using namespace std;
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
    cout << "\n--- Linked List Sort Performance [" << cityLabel << "] ---\n";
    cout << left  << setw(25) << "Algorithm"
         << right << setw(15) << "Time (ms)" << "\n";
    cout << left  << setw(25) << "Insertion Sort"
         << right << setw(15) << fixed << setprecision(4) << insertTime << "\n";
    cout << left  << setw(25) << "Selection Sort"
         << right << setw(15) << fixed << setprecision(4) << selectTime << "\n";
}

void printCrossStructureComparison(
    double arraySortTime, const char* arrayAlgo,
    double llSortTime,    const char* llAlgo,
    const char* cityLabel
) {
    cout << "\n--- Array vs Linked List Sort Comparison [" << cityLabel << "] ---\n";
    cout << left  << setw(25) << "Structure"
         << left  << setw(20) << "Algorithm"
         << right << setw(15) << "Time (ms)" << "\n";
    cout << left  << setw(25) << "Array"
         << left  << setw(20) << arrayAlgo
         << right << setw(15) << fixed << setprecision(4) << arraySortTime << "\n";
    cout << left  << setw(25) << "Linked List"
         << left  << setw(20) << llAlgo
         << right << setw(15) << fixed << setprecision(4) << llSortTime << "\n";
}
