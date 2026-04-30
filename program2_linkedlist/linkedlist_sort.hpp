// Sorting declarations for Linked List program
#ifndef LINKEDLIST_SORT_HPP
#define LINKEDLIST_SORT_HPP

#include "linkedlist.hpp"
#include "../program1_array/array_sort.hpp"  // reuse SortField, SortOrder enums

// Insertion Sort on ResidentList (re-links nodes, no data copying)
// Returns execution time in milliseconds
double insertionSortLL(ResidentList& list, SortField field, SortOrder order = ASCENDING);

// Merge Sort on ResidentList
// Returns execution time in milliseconds
double mergeSortLL(ResidentList& list, SortField field, SortOrder order = ASCENDING);

// Selection Sort on ResidentList
// Returns execution time in milliseconds
double selectionSortLL(ResidentList& list, SortField field, SortOrder order = ASCENDING);

// Print sorted linked list as a formatted text table
void printSortedTableLL(const ResidentList& list, SortField field, const char* algorithm);

// Print comparison: Insertion Sort vs Selection Sort
void printSortComparisonLL(double insertTime, double selectTime, const char* cityLabel);

// Print Array vs Linked List sort time comparison
void printCrossStructureComparison(
    double arraySortTime, const char* arrayAlgo,
    double llSortTime,    const char* llAlgo,
    const char* cityLabel
);

#endif // LINKEDLIST_SORT_HPP
