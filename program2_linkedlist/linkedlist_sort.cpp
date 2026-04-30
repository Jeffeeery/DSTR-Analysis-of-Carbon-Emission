// Sorting implementation for Linked List program
#include "linkedlist_sort.hpp"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;
using namespace std::chrono;

// Helper: get the sort key value from a node
static double getKey(const Node* node, SortField field) {
    if (field == SORT_BY_AGE)
        return node->data.age;
    else if (field == SORT_BY_DISTANCE)
        return node->data.dailyDistance;
    else
        return node->data.monthlyEmission;
}

static const char* getFieldNameLL(SortField field) {
    if (field == SORT_BY_AGE)
        return "Age";
    else if (field == SORT_BY_DISTANCE)
        return "Daily Distance";
    else
        return "Monthly Emission";
}

static bool comesBefore(const Node* a, const Node* b, SortField field, SortOrder order) {
    double keyA = getKey(a, field);
    double keyB = getKey(b, field);

    if (order == ASCENDING)
        return keyA < keyB;
    else
        return keyA > keyB;
}

double insertionSortLL(ResidentList& list, SortField field, SortOrder order) {
    auto start = high_resolution_clock::now();

    Node* current = list.getHead();
    Node* sortedHead = nullptr;

    while (current != nullptr) {
        Node* nextNode = current->next;
        current->next = nullptr;

        // Insert at beginning if sorted list is empty
        // or current should come before sortedHead
        if (sortedHead == nullptr || comesBefore(current, sortedHead, field, order)) {
            current->next = sortedHead;
            sortedHead = current;
        } else {
            Node* sortedCurrent = sortedHead;

            while (sortedCurrent->next != nullptr &&
                   !comesBefore(current, sortedCurrent->next, field, order)) {
                sortedCurrent = sortedCurrent->next;
            }

            current->next = sortedCurrent->next;
            sortedCurrent->next = current;
        }

        current = nextNode;
    }

    list.setHead(sortedHead);

    auto end = high_resolution_clock::now();
    duration<double, milli> elapsed = end - start;
    return elapsed.count();
}

static void splitList(Node* source, Node*& front, Node*& back) {
    if (source == nullptr || source->next == nullptr) {
        front = source;
        back = nullptr;
        return;
    }

    Node* slow = source;
    Node* fast = source->next;

    while (fast != nullptr) {
        fast = fast->next;

        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    front = source;
    back = slow->next;
    slow->next = nullptr;
}

static Node* mergeSortedLists(Node* first, Node* second, SortField field, SortOrder order) {
    Node* resultHead = nullptr;
    Node* resultTail = nullptr;

    while (first != nullptr && second != nullptr) {
        Node* selected = nullptr;

        if (!comesBefore(second, first, field, order)) {
            selected = first;
            first = first->next;
        } else {
            selected = second;
            second = second->next;
        }

        selected->next = nullptr;

        if (resultHead == nullptr) {
            resultHead = selected;
            resultTail = selected;
        } else {
            resultTail->next = selected;
            resultTail = selected;
        }
    }

    Node* remaining = nullptr;

    if (first != nullptr)
        remaining = first;
    else
        remaining = second;

    if (resultHead == nullptr) {
        resultHead = remaining;
    } else {
        resultTail->next = remaining;
    }

    return resultHead;
}

static Node* mergeSortNodes(Node* head, SortField field, SortOrder order) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    Node* firstHalf = nullptr;
    Node* secondHalf = nullptr;

    splitList(head, firstHalf, secondHalf);

    firstHalf = mergeSortNodes(firstHalf, field, order);
    secondHalf = mergeSortNodes(secondHalf, field, order);

    return mergeSortedLists(firstHalf, secondHalf, field, order);
}

double mergeSortLL(ResidentList& list, SortField field, SortOrder order) {
    auto start = high_resolution_clock::now();

    Node* sortedHead = mergeSortNodes(list.getHead(), field, order);
    list.setHead(sortedHead);

    auto end = high_resolution_clock::now();
    duration<double, milli> elapsed = end - start;
    return elapsed.count();
}

void printSortedTableLL(const ResidentList& list, SortField field, const char* algorithm) {
    cout << "\n--- Sorted Results: " << algorithm
         << " by " << getFieldNameLL(field) << " ---\n";

    cout << left
         << setw(15) << "Resident ID"
         << setw(8)  << "Age"
         << setw(18) << "Transport"
         << setw(18) << "Distance(km)"
         << setw(22) << "Monthly Emission"
         << setw(28) << "Age Group"
         << "\n";

    cout << setfill('-') << setw(109) << "" << setfill(' ') << "\n";

    Node* current = list.getHead();

    while (current != nullptr) {
        const Resident& r = current->data;

        cout << left
             << setw(15) << r.residentID
             << setw(8)  << r.age
             << setw(18) << r.transportMode
             << setw(18) << fixed << setprecision(2) << r.dailyDistance
             << setw(22) << fixed << setprecision(2) << r.monthlyEmission
             << setw(28) << r.ageGroup
             << "\n";

        current = current->next;
    }
}

void printSortComparisonLL(double insertTime, double mergeTime, const char* cityLabel) {
    cout << "\n--- Linked List Sort Performance [" << cityLabel << "] ---\n";
    cout << left  << setw(25) << "Algorithm"
         << right << setw(15) << "Time (ms)" << "\n";
    cout << string(40, '-') << "\n";

    cout << left  << setw(25) << "Insertion Sort"
         << right << setw(15) << fixed << setprecision(4) << insertTime << "\n";

    cout << left  << setw(25) << "Merge Sort"
         << right << setw(15) << fixed << setprecision(4) << mergeTime << "\n";
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
    cout << setfill('-') << setw(60) << "" << setfill(' ') << "\n";

    cout << left  << setw(25) << "Array"
         << left  << setw(20) << arrayAlgo
         << right << setw(15) << fixed << setprecision(4) << arraySortTime << "\n";

    cout << left  << setw(25) << "Linked List"
         << left  << setw(20) << llAlgo
         << right << setw(15) << fixed << setprecision(4) << llSortTime << "\n";
}