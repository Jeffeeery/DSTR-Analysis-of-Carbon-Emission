// Main program for Linked List-based implementation

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
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            choice = -1;
            continue;
        }

        switch (choice) {
            // Case 1: Display age ground categorisation and emission analysis for all cities
            case 1:
                analyzeByAgeGroup(listA, "City A");
                analyzeByAgeGroup(listB, "City B");
                analyzeByAgeGroup(listC, "City C");
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
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input.\n";
                        subChoice = -1;
                        continue;
                    }
                    switch (subChoice) {
                        case 1:
                            printTotalEmissions(listA, "City A");
                            printTotalEmissions(listB, "City B");
                            printTotalEmissions(listC, "City C");
                            break;
                        case 2:
                            printEmissionsByTransport(listA, "City A");
                            printEmissionsByTransport(listB, "City B");
                            printEmissionsByTransport(listC, "City C");
                            break;
                        case 3:
                            printEmissionsByAgeGroup(listA, "City A");
                            printEmissionsByAgeGroup(listB, "City B");
                            printEmissionsByAgeGroup(listC, "City C");
                            break;
                        case 4:
                            compareAllCities(listA, listB, listC);
                            break;
                        case 5:
                            compareAllCitiesByAgeGroup(listA, listB, listC);
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
                // TODO [WT]: prompt sort field/order, run insertionSortLL + mergeSortLL
            while (choice != 0) {
                cout << "\n--- Sorting Experiments: Linked List ---\n";
                cout << "Choose Dataset:\n";
                cout << "1. City A\n";
                cout << "2. City B\n";
                cout << "3. City C\n";
                cout << "4. All Cities\n";
                cout << "0. Back to Main Menu\n";
                cout << "9. Exit Program\n";
                cout << "Select: ";

                int cityChoice;
                cin >> cityChoice;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input.\n";
                    continue;
                }

                if (cityChoice == 0) {
                    break;
                }

                if (cityChoice == 9) {
                    cout << "Exiting...\n";
                    choice = 0;
                    break;
                }

                ResidentList* selectedLists[3];
                const char* cityLabels[3];
                int cityCount = 0;

                if (cityChoice == 1) {
                    selectedLists[0] = &listA;
                    cityLabels[0] = "City A";
                    cityCount = 1;
                } else if (cityChoice == 2) {
                    selectedLists[0] = &listB;
                    cityLabels[0] = "City B";
                    cityCount = 1;
                } else if (cityChoice == 3) {
                    selectedLists[0] = &listC;
                    cityLabels[0] = "City C";
                    cityCount = 1;
                } else if (cityChoice == 4) {
                    selectedLists[0] = &listA;
                    selectedLists[1] = &listB;
                    selectedLists[2] = &listC;

                    cityLabels[0] = "City A";
                    cityLabels[1] = "City B";
                    cityLabels[2] = "City C";

                    cityCount = 3;
                } else {
                    cout << "Invalid city choice.\n";
                    continue;
                }

                while (choice != 0) {
                    cout << "\nChoose Sort Field:\n";
                    cout << "1. Age\n";
                    cout << "2. Daily Distance\n";
                    cout << "3. Monthly Carbon Emission\n";
                    cout << "0. Back to Dataset Selection\n";
                    cout << "9. Exit Program\n";
                    cout << "Select: ";

                    int fieldChoice;
                    cin >> fieldChoice;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input.\n";
                        continue;
                    }

                    if (fieldChoice == 0) {
                        break;
                    }

                    if (fieldChoice == 9) {
                        cout << "Exiting...\n";
                        choice = 0;
                        break;
                    }

                    SortField field;

                    if (fieldChoice == 1)
                        field = SORT_BY_AGE;
                    else if (fieldChoice == 2)
                        field = SORT_BY_DISTANCE;
                    else if (fieldChoice == 3)
                        field = SORT_BY_EMISSION;
                    else {
                        cout << "Invalid sort field.\n";
                        continue;
                    }

                    while (choice != 0) {
                        cout << "\nChoose Sort Order:\n";
                        cout << "1. Ascending\n";
                        cout << "2. Descending\n";
                        cout << "0. Back to Sort Field Selection\n";
                        cout << "9. Exit Program\n";
                        cout << "Select: ";

                        int orderChoice;
                        cin >> orderChoice;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Invalid input.\n";
                            continue;
                        }

                        if (orderChoice == 0) {
                            break;
                        }

                        if (orderChoice == 9) {
                            cout << "Exiting...\n";
                            choice = 0;
                            break;
                        }

                        SortOrder order;

                        if (orderChoice == 1)
                            order = ASCENDING;
                        else if (orderChoice == 2)
                            order = DESCENDING;
                        else {
                            cout << "Invalid sort order.\n";
                            continue;
                        }

                        for (int cityIndex = 0; cityIndex < cityCount; cityIndex++) {
                            ResidentList* selectedList = selectedLists[cityIndex];
                            const char* cityLabel = cityLabels[cityIndex];

                            int recordCount = selectedList->size();

                            // Create two copies so both algorithms sort the same original data
                            ResidentList insertionCopy;
                            ResidentList mergeCopy;

                            Node* current = selectedList->getHead();

                            while (current != nullptr) {
                                insertionCopy.insertAtTail(current->data);
                            mergeCopy.insertAtTail(current->data);
                                current = current->next;
                            }

                            double insertTime = insertionSortLL(insertionCopy, field, order);
                            double mergeTime = mergeSortLL(mergeCopy, field, order);

                            printSortedTableLL(mergeCopy, field, "Merge Sort");
                            printSortComparisonLL(insertTime, mergeTime, cityLabel);

                            // Estimated memory usage
                            size_t linkedListStorage = recordCount * sizeof(Node);
                            size_t insertionExtraMemory = 4 * sizeof(Node*);
                            size_t mergeExtraMemory = 3 * sizeof(Node*);

                            cout << "\n--- Estimated Memory Usage [Linked List - " << cityLabel << "] ---\n";
                            cout << left << setw(35) << "Item"
                                << right << setw(20) << "Memory (bytes)"
                                << setw(15) << "Big-O" << "\n";
                            cout << string(70, '-') << "\n";

                            cout << left << setw(35) << "Linked List Node Storage"
                                << right << setw(20) << linkedListStorage
                                << setw(15) << "O(n)" << "\n";

                            cout << left << setw(35) << "Insertion Sort Extra Memory"
                                << right << setw(20) << insertionExtraMemory
                                << setw(15) << "O(1)" << "\n";

                            cout << left << setw(35) << "Merge Sort Extra Memory"
                                << right << setw(20) << mergeExtraMemory
                                << setw(15) << "O(log n)" << "\n";
                            // Save the sorted result back to the selected linked list
                            selectedList->clear();

                            Node* sortedCurrent = mergeCopy.getHead();

                            while (sortedCurrent != nullptr) {
                                selectedList->insertAtTail(sortedCurrent->data);
                                sortedCurrent = sortedCurrent->next;
                            }

                            cout << "\n" << cityLabel << " has been sorted using Merge Sort.\n";

                            if (field == SORT_BY_AGE)
                                cout << cityLabel << " is now sorted by Age.\n";
                            else if (field == SORT_BY_DISTANCE)
                                cout << cityLabel << " is now sorted by Daily Distance.\n";
                            else if (field == SORT_BY_EMISSION)
                                cout << cityLabel << " is now sorted by Monthly Carbon Emission.\n";

                            cout << "Note: Ordered Search in Option 4 is only valid when the search field matches the sorted field.\n";
                        }

                        if (cityChoice == 4) {
                            cout << "\nAll cities have been sorted using the selected field and order.\n";
                        }

                        cout << "\nEnter another option, or choose 0 to go back.\n";
                    }
                }
            }

            break;
        }                       
            
            case 4: {
                int searchMenu = -1;
                while (searchMenu != 0) {
                    cout << "\n--- Searching Experiments (Linked List) ---" << endl;
                    cout << "1. Search by Age Group" << endl;
                    cout << "2. Search by Transport Mode" << endl;
                    cout << "3. Search by Distance Threshold" << endl;
                    cout << "0. Back to Main Menu" << endl;
                    cout << "Select: ";
                    cin >> searchMenu;
                    if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Invalid input.\n"; searchMenu = -1; continue; }

                    if (searchMenu == 0) break; // Back function

                    string keyword = "";
                    SearchCriteria crit;

                    switch (searchMenu) {
                        case 1: {
                            cout << "\nSelect Age Group:\n"
                                 << "1. Children & Teenagers (6-17)\n"
                                 << "2. University Students / Young Adults (18-25)\n"
                                 << "3. Working Adults (Early Career) (26-45)\n"
                                 << "4. Working Adults (Late Career) (46-60)\n"
                                 << "5. Senior Citizens / Retirees (61-100)\n"
                                 << "Select: ";
                            int ageChoice; cin >> ageChoice;
                            if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Invalid input.\n"; continue; }
                            if (ageChoice == 1) keyword = "6-17";
                            else if (ageChoice == 2) keyword = "18-25";
                            else if (ageChoice == 3) keyword = "26-45";
                            else if (ageChoice == 4) keyword = "46-60";
                            else keyword = "61-100";
                            crit = SEARCH_BY_AGE_GROUP;
                            break;
                        }
                        case 2: {
                            // City A, B, and C combined transport modes
                            cout << "\nSelect Transport Mode:\n"
                                 << "1. Car\n2. Bus\n3. Bicycle\n4. Walking\n5. School Bus\n6. Carpool\n"
                                 << "Select: ";
                            int transChoice; cin >> transChoice;
                            if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Invalid input.\n"; continue; }
                            const char* modes[] = {"", "Car", "Bus", "Bicycle", "Walking", "School Bus", "Carpool"};
                            if (transChoice >= 1 && transChoice <= 6) keyword = modes[transChoice];
                            crit = SEARCH_BY_TRANSPORT;
                            break;
                        }
                        case 3: {
                            cout << "Enter minimum daily distance (km) threshold: ";
                            cin >> keyword;
                            crit = SEARCH_BY_DISTANCE_THRESHOLD;
                            break;
                        }
                        default: 
                            cout << "Invalid selection." << endl;
                            continue;
                    }

                    ResidentList* lists[] = {&listA, &listB, &listC};
                    const char* names[] = {"City A", "City B", "City C"};

                    for (int i = 0; i < 3; i++) {
                        cout << "\n>>> " << names[i] << " Results (Linked List) <<<";
                        
                        // Run Linear Search
                        SearchResult linRes = linearSearchLL(*lists[i], crit, keyword.c_str());
                        
                        // Run Ordered Search (Member 4 Task)
                        cout << "\n(Ordered Search assumes data was sorted by Member 3)\n";
                        SearchResult ordRes = orderedSearchLL(*lists[i], crit, keyword.c_str());

                        // Show Results and Performance Comparison[cite: 4]
                        printSearchResultsLL(*lists[i], linRes, crit, keyword.c_str());
                        printSearchComparisonLL(linRes, ordRes);

                        // CRITICAL: Cleanup memory if indices were heap-allocated
                        // delete[] linRes.indices; 
                        // delete[] ordRes.indices;
                    }
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
                    ResidentList tempInsertion, tempMerge;
                    for (Node* current = lists[i]->getHead(); current != nullptr; current = current->next) {
                        tempInsertion.insertAtTail(current->data);
                        tempMerge.insertAtTail(current->data);
                    }
                    double timeInsertion = insertionSortLL(tempInsertion, SORT_BY_EMISSION, ASCENDING);
                    double timeMerge = mergeSortLL(tempMerge, SORT_BY_EMISSION, ASCENDING);

                    cout << left  << setw(16) << "InsertionSort"
                         << setw(10) << cityNames[i]
                         << right << setw(10) << count
                         << setw(12) << fixed << setprecision(4) << timeInsertion << "\n";
                    cout << left  << setw(16) << "MergeSort"
                         << setw(10) << cityNames[i]
                         << right << setw(10) << count
                         << setw(12) << fixed << setprecision(4) << timeMerge << "\n";
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
