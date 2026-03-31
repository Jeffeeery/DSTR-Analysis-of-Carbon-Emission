// Member 2 - [WT]
// program1_array/array_sort.cpp - Sorting implementation for Array program

#include "array_sort.h"
#include <chrono>
#include <cstdio>
#include <iomanip>
#include <iostream>

using namespace std::chrono;

// Helper: compare two Residents by chosen field
// Returns true if a should come before b (for ASCENDING order)
static bool compare(const Resident& a, const Resident& b, SortField field, SortOrder order) {
    // TODO: compare by field (age / dailyDistance / monthlyEmission)
    // flip result if order == DESCENDING
    return false;
}

double bubbleSort(ResidentArray& arr, SortField field, SortOrder order) {
    // TODO:
    // 1. Record start time with chrono
    // 2. Standard bubble sort using arr.swap(i, j) and compare()
    // 3. Record end time, return duration in milliseconds
    return 0.0;
}

// Merge Sort helper: merge two halves into a temp buffer then copy back
static void merge(ResidentArray& arr, int left, int mid, int right, SortField field, SortOrder order) {
    // TODO
}

static void mergeSortHelper(ResidentArray& arr, int left, int right, SortField field, SortOrder order) {
    // TODO: recursive divide and conquer
}

double mergeSort(ResidentArray& arr, SortField field, SortOrder order) {
    // TODO:
    // 1. Record start time
    // 2. Call mergeSortHelper(arr, 0, arr.size()-1, field, order)
    // 3. Return duration in milliseconds
    return 0.0;
}

void printSortedTable(const ResidentArray& arr, SortField field, const char* algorithm) {
    // TODO: print header + rows using printf with fixed-width columns
    // Show: ResidentID | Age | Transport | DailyDist | MonthlyEmission | AvgDays
}

void printSortComparison(double bubbleTime, double mergeTime, const char* cityLabel) {
    printf("\n--- Sort Performance Comparison [%s] ---\n", cityLabel);
    printf("%-20s %15s\n", "Algorithm", "Time (ms)");
    printf("%-20s %15.4f\n", "Bubble Sort", bubbleTime);
    printf("%-20s %15.4f\n", "Merge Sort",  mergeTime);
}
