// Sorting implementation for Array program

#include "array_sort.hpp"
#include <chrono>
#include <iomanip>
#include <iostream>

using namespace std;
using namespace std::chrono;

static double getKey(const Resident& r, SortField field) {
    if (field == SORT_BY_AGE)
        return r.age;
    else if (field == SORT_BY_DISTANCE)
        return r.dailyDistance;
    else
        return r.monthlyEmission;
}

static const char* getFieldName(SortField field) {
    if (field == SORT_BY_AGE)
        return "Age";
    else if (field == SORT_BY_DISTANCE)
        return "Daily Distance";
    else
        return "Monthly Emission";
}

// Helper: compare two Residents by chosen field
// Returns true if a should come before b 
static bool compare(const Resident& a, const Resident& b, SortField field, SortOrder order) {
    double keyA = getKey(a, field);
    double keyB = getKey(b, field);

    if (order == ASCENDING)
        return keyA < keyB;
    else
        return keyA > keyB;
}

double insertionSort(ResidentArray& arr, SortField field, SortOrder order) {
    auto start = high_resolution_clock::now();

    int n = arr.size();

    for (int i = 1; i < n; i++) {
        Resident key = arr.get(i);
        int j = i - 1;

        while (j >= 0 && compare(key, arr.get(j), field, order)) {
            arr.get(j + 1) = arr.get(j);
            j--;
        }

        arr.get(j + 1) = key;
    }

    auto end = high_resolution_clock::now();
    duration<double, milli> elapsed = end - start;
    return elapsed.count();
}

// Merge Sort helper: merge two halves into a temp buffer then copy back
static void merge(ResidentArray& arr, int left, int mid, int right, SortField field, SortOrder order) {
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    Resident* leftArr = new Resident[leftSize];
    Resident* rightArr = new Resident[rightSize];

    for (int i = 0; i < leftSize; i++)
        leftArr[i] = arr.get(left + i);

    for (int j = 0; j < rightSize; j++)
        rightArr[j] = arr.get(mid + 1 + j);

    int i = 0;
    int j = 0;
    int k = left;

    while (i < leftSize && j < rightSize) {
        // Keep left item first if both are equal
        if (!compare(rightArr[j], leftArr[i], field, order)) {
            arr.get(k) = leftArr[i];
            i++;
        } else {
            arr.get(k) = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < leftSize) {
        arr.get(k) = leftArr[i];
        i++;
        k++;
    }

    while (j < rightSize) {
        arr.get(k) = rightArr[j];
        j++;
        k++;
    }

    delete[] leftArr;
    delete[] rightArr;
}

static void mergeSortHelper(ResidentArray& arr, int left, int right, SortField field, SortOrder order) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSortHelper(arr, left, mid, field, order);
        mergeSortHelper(arr, mid + 1, right, field, order);

        merge(arr, left, mid, right, field, order);
    }
}

double mergeSort(ResidentArray& arr, SortField field, SortOrder order) {
    auto start = high_resolution_clock::now();

    if (arr.size() > 1)
        mergeSortHelper(arr, 0, arr.size() - 1, field, order);

    auto end = high_resolution_clock::now();
    duration<double, milli> elapsed = end - start;
    return elapsed.count();
}

void printSortedTable(const ResidentArray& arr, SortField field, const char* algorithm) {
    cout << "\n--- Sorted Results: " << algorithm
         << " by " << getFieldName(field) << " ---\n";

    cout << left
         << setw(15) << "Resident ID"
         << setw(8)  << "Age"
         << setw(18) << "Transport"
         << setw(18) << "Distance(km)"
         << setw(22) << "Monthly Emission"
         << setw(28) << "Age Group"
         << "\n";

    cout << string(109, '-') << "\n";

    for (int i = 0; i < arr.size(); i++) {
        const Resident& r = arr.get(i);

        cout << left
             << setw(15) << r.residentID
             << setw(8)  << r.age
             << setw(18) << r.transportMode
             << setw(18) << fixed << setprecision(2) << r.dailyDistance
             << setw(22) << fixed << setprecision(2) << r.monthlyEmission
             << setw(28) << r.ageGroup
             << "\n";
    }
}

void printSortComparison(double InsertionTime, double mergeTime, const char* cityLabel) {
    cout << "\n--- Sort Performance Comparison [" << cityLabel << "] ---\n";
    cout << left  << setw(20) << "Algorithm"
         << right << setw(15) << "Time (ms)" << "\n";
    cout << string(35, '-') << "\n";

    cout << left  << setw(20) << "Insertion Sort"
         << right << setw(15) << fixed << setprecision(4) << InsertionTime << "\n";

    cout << left  << setw(20) << "Merge Sort"
         << right << setw(15) << fixed << setprecision(4) << mergeTime << "\n";
}