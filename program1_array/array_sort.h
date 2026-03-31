// Member 2 - [WT]
// program1_array/array_sort.h - Sorting algorithm declarations for Array program

#ifndef ARRAY_SORT_H
#define ARRAY_SORT_H

#include "arraylist.h"

// Sort field selector
enum SortField {
    SORT_BY_AGE,
    SORT_BY_DISTANCE,
    SORT_BY_EMISSION
};

// Sort order
enum SortOrder {
    ASCENDING,
    DESCENDING
};

// Bubble Sort on ResidentArray
// Returns execution time in milliseconds
double bubbleSort(ResidentArray& arr, SortField field, SortOrder order = ASCENDING);

// Merge Sort on ResidentArray
// Returns execution time in milliseconds
double mergeSort(ResidentArray& arr, SortField field, SortOrder order = ASCENDING);

// Print sorted results as a formatted text table
void printSortedTable(const ResidentArray& arr, SortField field, const char* algorithm);

// Print comparison of Bubble Sort vs Merge Sort execution times
void printSortComparison(double bubbleTime, double mergeTime, const char* cityLabel);

#endif // ARRAY_SORT_H
