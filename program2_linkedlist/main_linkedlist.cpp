// Member 1 (skeleton) - all members contribute
// program2_linkedlist/main_linkedlist.cpp - Main program for Linked List-based implementation

#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include "linkedlist.hpp"
#include "../shared/csvloader.hpp"
#include "../shared/analysis.hpp"
#include "linkedlist_sort.hpp"
#include "linkedlist_search.hpp"

using namespace std;

// Dataset file paths (adjust relative path as needed)
#define PATH_CITY_A "dataset1-cityA.csv"
#define PATH_CITY_B "dataset2-cityB.csv"
#define PATH_CITY_C "dataset3-cityC.csv"

int main() {
    // --- Load datasets ---
    Resident rawA[MAX_RESIDENTS], rawB[MAX_RESIDENTS], rawC[MAX_RESIDENTS];
    int countA = loadCSV(PATH_CITY_A, rawA, MAX_RESIDENTS);
    int countB = loadCSV(PATH_CITY_B, rawB, MAX_RESIDENTS);
    int countC = loadCSV(PATH_CITY_C, rawC, MAX_RESIDENTS);

    if (countA < 0 || countB < 0 || countC < 0) {
        cout << "Error loading one or more CSV files.\n";
        return 1;
    }

    cout << "Loaded: City A = " << countA
         << " | City B = " << countB
         << " | City C = " << countC << "\n";

    // Populate ResidentList objects from raw arrays from structured access
    ResidentList listA, listB, listC;
    for (int i = 0; i < countA; i++) listA.insertAtTail(rawA[i]);
    for (int i = 0; i < countB; i++) listB.insertAtTail(rawB[i]);
    for (int i = 0; i < countC; i++) listC.insertAtTail(rawC[i]);

    int choice = 0;
    do {
        cout << "\n========================================\n"
             << "  DSTR Assignment - Linked List Program\n"
             << "========================================\n"
             << "1. Age Group Categorization & Analysis\n"  // Member 1 [BAN]
             << "2. Carbon Emission Analysis\n"              // Member 2 [EV]
             << "3. Sorting Experiments\n"                   // Member 3 [EEE]
             << "4. Searching Experiments\n"                 // Member 4 [WK]
             << "5. Performance Analysis\n"                  // Member 5 [EEE]
             << "0. Exit\n"
             << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            // Case 1: Display age ground categorisation and emission analysis for all cities
            case 1:
                analyzeByAgeGroup(rawA, countA, "City A");
                analyzeByAgeGroup(rawB, countB, "City B");
                analyzeByAgeGroup(rawC, countC, "City C");
                break;
            case 2: {
                int subChoice = 0;
                do {
                    cout << "\n--- Carbon Emission Analysis ---\n"
                         << "1. Total emissions per city\n"
                         << "2. Emissions by transport mode\n"
                         << "3. Emissions by age group\n"
                         << "4. Compare all cities\n"
                         << "5. Compare all cities by age group\n"
                         << "0. Back\n"
                         << "Enter choice: ";
                    cin >> subChoice;
                    switch (subChoice) {
                        case 1:
                            printTotalEmissions(rawA, countA, "City A");
                            printTotalEmissions(rawB, countB, "City B");
                            printTotalEmissions(rawC, countC, "City C");
                            break;
                        case 2:
                            printEmissionsByTransport(rawA, countA, "City A");
                            printEmissionsByTransport(rawB, countB, "City B");
                            printEmissionsByTransport(rawC, countC, "City C");
                            break;
                        case 3:
                            printEmissionsByAgeGroup(rawA, countA, "City A");
                            printEmissionsByAgeGroup(rawB, countB, "City B");
                            printEmissionsByAgeGroup(rawC, countC, "City C");
                            break;
                        case 4:
                            compareAllCities(rawA, countA, rawB, countB, rawC, countC);
                            break;
                        case 5:
                            compareAllCitiesByAgeGroup(rawA, countA, rawB, countB, rawC, countC);
                            break;
                        case 0:
                            break;
                        default:
                            cout << "Invalid choice.\n";
                    }
                } while (subChoice != 0);
                break;
            }
            case 3: {
                // TODO [WT]: prompt sort field/order, run insertionSortLL + selectionSortLL
                cout << "\n--- Sorting Experiments: Linked List ---\n";

                    cout << "Choose Dataset:\n";
                    cout << "1. City A\n";
                    cout << "2. City B\n";
                    cout << "3. City C\n";
                    cout << "Select: ";

                    int cityChoice;
                    cin >> cityChoice;

                    ResidentList* selectedList = nullptr;
                    const char* cityLabel = "";

                    if (cityChoice == 1) {
                        selectedList = &listA;
                        cityLabel = "City A";
                    } else if (cityChoice == 2) {
                        selectedList = &listB;
                        cityLabel = "City B";
                    } else if (cityChoice == 3) {
                        selectedList = &listC;
                        cityLabel = "City C";
                    } else {
                        cout << "Invalid city choice.\n";
                        break;
                    }

                    cout << "\nChoose Sort Field:\n";
                    cout << "1. Age\n";
                    cout << "2. Daily Distance\n";
                    cout << "3. Monthly Carbon Emission\n";
                    cout << "Select: ";

                    int fieldChoice;
                    cin >> fieldChoice;

                    SortField field;

                    if (fieldChoice == 1)
                        field = SORT_BY_AGE;
                    else if (fieldChoice == 2)
                        field = SORT_BY_DISTANCE;
                    else if (fieldChoice == 3)
                        field = SORT_BY_EMISSION;
                    else {
                        cout << "Invalid sort field.\n";
                        break;
                    }

                    cout << "\nChoose Sort Order:\n";
                    cout << "1. Ascending\n";
                    cout << "2. Descending\n";
                    cout << "Select: ";

                    int orderChoice;
                    cin >> orderChoice;

                    SortOrder order;

                    if (orderChoice == 2)
                        order = DESCENDING;
                    else
                        order = ASCENDING;

                    // Create two copies so both algorithms sort the same original data
                    ResidentList insertionCopy;
                    ResidentList selectionCopy;

                    Node* current = selectedList->getHead();

                    while (current != nullptr) {
                        insertionCopy.insertAtTail(current->data);
                        selectionCopy.insertAtTail(current->data);
                        current = current->next;
                    }

                    double insertTime = insertionSortLL(insertionCopy, field, order);
                    double selectTime = selectionSortLL(selectionCopy, field, order);

                    printSortedTableLL(insertionCopy, field, "Insertion Sort");
                    printSortComparisonLL(insertTime, selectTime, cityLabel);

                    // Save the sorted result back to the selected linked list
                    // This helps ordered traversal search if needed later
                    selectedList->clear();

                    Node* sortedCurrent = insertionCopy.getHead();

                    while (sortedCurrent != nullptr) {
                        selectedList->insertAtTail(sortedCurrent->data);
                        sortedCurrent = sortedCurrent->next;
                    }

                    cout << "\nThe selected dataset has been sorted using Insertion Sort.\n";

                break;
            }
            
            case 4: {
                cout << "\n--- Searching Experiments (All Cities - Linked List) ---\n";
                cout << "1. Age Group\n2. Transport Mode\n3. Distance Threshold\nSelect: ";
                int sChoice;
                cin >> sChoice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                string keyword;
                cout << "Enter search keyword: ";
                getline(cin, keyword);

                SearchCriteria crit;
                if (sChoice == 1) crit = SEARCH_BY_AGE_GROUP;
                else if (sChoice == 2) crit = SEARCH_BY_TRANSPORT;
                else crit = SEARCH_BY_DISTANCE_THRESHOLD;

                // Array of pointers to our 3 lists for easy iteration
                ResidentList* lists[] = {&listA, &listB, &listC};
                const char* cityNames[] = {"City A", "City B", "City C"};

                for (int i = 0; i < 3; i++) {
                    cout << "\n>>> Searching " << cityNames[i] << " <<<";

                    // Run Linear Search
                    SearchResult linRes = linearSearchLL(*lists[i], crit, keyword.c_str());

                    // Run Ordered Traversal Search
                    cout << "\nNote: Ordered Search results only valid if " << cityNames[i]
                         << " was sorted by this field in Option 3.\n";
                    SearchResult ordRes = orderedSearchLL(*lists[i], crit, keyword.c_str());

                    // Show Results and Performance Comparison
                    printSearchResultsLL(*lists[i], linRes, crit, keyword.c_str());
                    printSearchComparisonLL(linRes, ordRes);
                }
                break;
            }
            case 5: {
                ResidentList* lists[]        = {&listA, &listB, &listC};
                const char*   cityNames[]    = {"City A", "City B", "City C"};
                int           recordCounts[] = {countA, countB, countC};

                // ----- Sort Benchmarks (run on temporary copies) -----
                cout << "\n--- Sort Performance (field: Monthly Emission, order: Ascending) ---\n";
                cout << left
                     << setw(16) << "Algorithm"
                     << setw(10) << "City"
                     << right
                     << setw(10) << "Number"
                     << setw(12) << "Time(ms)" << "\n";
                cout << "--------------------------------------------\n";

                for (int i = 0; i < 3; i++) {
                    int count = recordCounts[i];
                    ResidentList tempInsertion, tempSelection;
                    for (Node* current = lists[i]->getHead(); current != nullptr; current = current->next) {
                        tempInsertion.insertAtTail(current->data);
                        tempSelection.insertAtTail(current->data);
                    }
                    double timeInsertion = insertionSortLL(tempInsertion, SORT_BY_EMISSION, ASCENDING);
                    double timeSelection = selectionSortLL(tempSelection, SORT_BY_EMISSION, ASCENDING);

                    cout << left  << setw(16) << "InsertionSort"
                         << setw(10) << cityNames[i]
                         << right << setw(10) << count
                         << setw(12) << fixed << setprecision(4) << timeInsertion << "\n";
                    cout << left  << setw(16) << "SelectionSort"
                         << setw(10) << cityNames[i]
                         << right << setw(10) << count
                         << setw(12) << fixed << setprecision(4) << timeSelection << "\n";
                }

                // ----- Search Benchmarks -----
                cout << "\n--- Search Performance (criteria: Transport Mode = 'Car') ---\n";
                cout << left
                     << setw(16) << "Algorithm"
                     << setw(10) << "City"
                     << right
                     << setw(10) << "Number"
                     << setw(10) << "Matches"
                     << setw(14) << "Comparisons"
                     << setw(12) << "Time(ms)" << "\n";
                cout << "------------------------------------------------------------------\n";

                for (int i = 0; i < 3; i++) {
                    int count = recordCounts[i];
                    SearchResult linearResult  = linearSearchLL (*lists[i], SEARCH_BY_TRANSPORT, "Car");
                    SearchResult orderedResult = orderedSearchLL(*lists[i], SEARCH_BY_TRANSPORT, "Car");

                    cout << left  << setw(16) << "LinearSearch"
                         << setw(10) << cityNames[i]
                         << right << setw(10) << count
                         << setw(10) << linearResult.count
                         << setw(14) << linearResult.comparisons
                         << setw(12) << fixed << setprecision(4) << linearResult.timeMs << "\n";
                    cout << left  << setw(16) << "OrderedSearch"
                         << setw(10) << cityNames[i]
                         << right << setw(10) << count
                         << setw(10) << orderedResult.count
                         << setw(14) << orderedResult.comparisons
                         << setw(12) << fixed << setprecision(4) << orderedResult.timeMs << "\n";
                }

                // ----- Memory Footprint -----
                cout << "\n--- Memory Footprint (Linked List) ---\n";
                cout << "sizeof(Node) = " << sizeof(Node) << " bytes per node"
                     << " (Resident data + 1 pointer)\n";
                cout << left  << setw(10) << "City"
                     << right << setw(10) << "Number"
                     << setw(16) << "Mem (bytes)"
                     << setw(12) << "Mem (KB)" << "\n";
                cout << "--------------------------------------------\n";
                for (int i = 0; i < 3; i++) {
                    int memoryBytes = static_cast<int>(sizeof(Node)) * recordCounts[i];
                    cout << left  << setw(10) << cityNames[i]
                         << right << setw(10) << recordCounts[i]
                         << setw(16) << memoryBytes
                         << setw(12) << fixed << setprecision(2) << memoryBytes / 1024.0 << "\n";
                }
                break;
            }
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
