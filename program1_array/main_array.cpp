// Main program for Array-based implementation
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include "arraylist.hpp"
#include "../shared/csvloader.hpp"
#include "../shared/analysis.hpp"
#include "array_sort.hpp"
#include "array_search.hpp"
#include "../shared/performance.hpp"

using namespace std;

// Dataset file paths
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

    // Populate ResidentArray objects from raw arrays for structured access
    ResidentArray arrA, arrB, arrC;
    for (int i = 0; i < countA; i++) arrA.add(rawA[i]);
    for (int i = 0; i < countB; i++) arrB.add(rawB[i]);
    for (int i = 0; i < countC; i++) arrC.add(rawC[i]);

    int choice = 0;
    do {
        cout << "\n========================================\n"
             << "  DSTR Assignment - Array Program\n"
             << "========================================\n"
             << "1. Age Group Categorization & Analysis\n"     // Member 1 [BAN]
             << "2. Carbon Emission Analysis\n"                // Member 2 [EV]
             << "3. Sorting Experiments\n"                     // Member 3 [WT]
             << "4. Searching Experiments\n"                   // Member 4 [WK]
             << "5. Performance Analysis\n"                    // Member 5 [EEE]
             << "0. Exit\n"
             << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            // Case 1: Display age group categorisation and emission analysis for all cities
            case 1:
                analyzeByAgeGroup(arrA.getData(), arrA.size(), "City A");
                analyzeByAgeGroup(arrB.getData(), arrB.size(), "City B");
                analyzeByAgeGroup(arrC.getData(), arrC.size(), "City C");
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
                            printTotalEmissions(arrA.getData(), arrA.size(), "City A");
                            printTotalEmissions(arrB.getData(), arrB.size(), "City B");
                            printTotalEmissions(arrC.getData(), arrC.size(), "City C");
                            break;
                        case 2:
                            printEmissionsByTransport(arrA.getData(), arrA.size(), "City A");
                            printEmissionsByTransport(arrB.getData(), arrB.size(), "City B");
                            printEmissionsByTransport(arrC.getData(), arrC.size(), "City C");
                            break;
                        case 3:
                            printEmissionsByAgeGroup(arrA.getData(), arrA.size(), "City A");
                            printEmissionsByAgeGroup(arrB.getData(), arrB.size(), "City B");
                            printEmissionsByAgeGroup(arrC.getData(), arrC.size(), "City C");
                            break;
                        case 4:
                            compareAllCities(arrA.getData(), arrA.size(), arrB.getData(), arrB.size(), arrC.getData(), arrC.size());
                            break;
                        case 5:
                            compareAllCitiesByAgeGroup(arrA.getData(), arrA.size(), arrB.getData(), arrB.size(), arrC.getData(), arrC.size());
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
                // TODO [WT]: prompt sort field/order, run bubbleSort + mergeSort, print comparison           
                while (choice != 0) {
                    cout << "\n--- Sorting Experiments: Array ---\n";
                    cout << "Choose Dataset:\n";
                    cout << "1. City A\n";
                    cout << "2. City B\n";
                    cout << "3. City C\n";
                    cout << "4. All Cities\n";
                    cout << "0. Back to Main Menu\n";
                    cout << "Select: ";

                    int cityChoice;
                    cin >> cityChoice;

                    if (cityChoice == 0) {
                        break;
                    }

                    ResidentArray* selectedArrays[3];
                    const char* cityLabels[3];
                    int cityCount = 0;

                    if (cityChoice == 1) {
                        selectedArrays[0] = &arrA;
                        cityLabels[0] = "City A";
                        cityCount = 1;
                    } else if (cityChoice == 2) {
                        selectedArrays[0] = &arrB;
                        cityLabels[0] = "City B";
                        cityCount = 1;
                    } else if (cityChoice == 3) {
                        selectedArrays[0] = &arrC;
                        cityLabels[0] = "City C";
                        cityCount = 1;
                    } else if (cityChoice == 4) {
                        selectedArrays[0] = &arrA;
                        selectedArrays[1] = &arrB;
                        selectedArrays[2] = &arrC;

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
                        cout << "Select: ";

                        int fieldChoice;
                        cin >> fieldChoice;

                        if (fieldChoice == 0) {
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
                            cout << "9. Exit\n";
                            cout << "Select: ";

                            int orderChoice;
                            cin >> orderChoice;

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
                            ResidentArray* selectedArray = selectedArrays[cityIndex];
                            const char* cityLabel = cityLabels[cityIndex];
                            
                            int recordCount = selectedArray->size();

                            // Create two copies so both algorithms sort the same original data
                            ResidentArray bubbleCopy(recordCount);
                            ResidentArray mergeCopy(recordCount);

                            for (int i = 0; i < recordCount; i++) {
                                bubbleCopy.add(selectedArray->get(i));
                                mergeCopy.add(selectedArray->get(i));
                            }

                            double bubbleTime = bubbleSort(bubbleCopy, field, order);
                            double mergeTime = mergeSort(mergeCopy, field, order);

                            printSortedTable(mergeCopy, field, "Merge Sort");
                            printSortComparison(bubbleTime, mergeTime, cityLabel);

                            // Estimated memory usage
                            size_t arrayStorage = recordCount * sizeof(Resident);
                            size_t bubbleExtraMemory = sizeof(Resident);
                            size_t mergeExtraMemory = recordCount * sizeof(Resident);

                            cout << "\n--- Estimated Memory Usage [Array - " << cityLabel << "] ---\n";
                            cout << left << setw(30) << "Item"
                                << right << setw(20) << "Memory (bytes)"
                                << setw(15) << "Big-O" << "\n";
                            cout << string(65, '-') << "\n";

                            cout << left << setw(30) << "Array Record Storage"
                                << right << setw(20) << arrayStorage
                                << setw(15) << "O(n)" << "\n";

                            cout << left << setw(30) << "Bubble Sort Extra Memory"
                                << right << setw(20) << bubbleExtraMemory
                                << setw(15) << "O(1)" << "\n";

                            cout << left << setw(30) << "Merge Sort Extra Memory"
                                << right << setw(20) << mergeExtraMemory
                                << setw(15) << "O(n)" << "\n";

                            // Save the sorted result back to the selected array
                            selectedArray->clear();
                            for (int i = 0; i < mergeCopy.size(); i++) {
                                selectedArray->add(mergeCopy.get(i));
                            }

                            cout << "\n" << cityLabel << " has been sorted using Merge Sort.\n";

                            if (field == SORT_BY_AGE)
                                cout << cityLabel << " is now sorted by Age.\n";
                            else if (field == SORT_BY_DISTANCE)
                                cout << cityLabel << " is now sorted by Daily Distance.\n";
                            else if (field == SORT_BY_EMISSION)
                                cout << cityLabel << " is now sorted by Monthly Carbon Emission.\n";

                            cout << "Note: Binary Search in Option 4 is only valid when the search field matches the sorted field.\n";
                        }

                        if (cityChoice == 4) {
                            cout << "\nAll cities have been sorted using the selected field and order.\n";
                        }
                    }
                }
            }
                    break;
                }         
            
            case 4: {
                cout << "\n--- Searching Experiments ---\n";
                cout << "1. Age Group\n2. Transport Mode\n3. Distance Threshold\nSelect: ";
                int sChoice;
                cin >> sChoice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                string keyword;
                cout << "Enter search keyword (Case Sensitive, e.g., 'Car' or 'Working Adults (26-45)'): ";
                getline(cin, keyword);

                SearchCriteria crit = (sChoice == 1) ? SEARCH_BY_AGE_GROUP :
                                      (sChoice == 2) ? SEARCH_BY_TRANSPORT :
                                                       SEARCH_BY_DISTANCE_THRESHOLD;

                // We will create pointers to easily iterate through our cities
                ResidentArray* cities[] = {&arrA, &arrB, &arrC};
                const char* cityNames[] = {"City A", "City B", "City C"};

                for (int i = 0; i < 3; i++) {
                    cout << "\n>>> Results for " << cityNames[i] << " <<<";

                    // Run Searches
                    SearchResult linRes = linearSearch(*cities[i], crit, keyword.c_str());
                    SearchResult binRes = binarySearch(*cities[i], crit, keyword.c_str());

                    // Display results using your functions
                    printSearchResults(*cities[i], linRes, crit, keyword.c_str());
                    printSearchComparison(linRes, binRes);
                }
                break;
            }
            case 5: {
                ResidentArray* cities[]      = {&arrA, &arrB, &arrC};
                const char*    cityNames[]   = {"City A", "City B", "City C"};
                int            recordCounts[] = {countA, countB, countC};

                // ----- Sort Benchmarks (run on temporary copies) -----
                cout << "\n--- Sort Performance (field: Monthly Emission, order: Ascending) ---\n";
                cout << left
                     << setw(14) << "Algorithm"
                     << setw(10) << "City"
                     << right
                     << setw(10) << "Number"
                     << setw(12) << "Time(ms)" << "\n";
                cout << "------------------------------------------\n";

                for (int i = 0; i < 3; i++) {
                    int count = recordCounts[i];
                    ResidentArray tempBubble(count), tempMerge(count);
                    for (int j = 0; j < count; j++) {
                        tempBubble.add(cities[i]->get(j));
                        tempMerge.add(cities[i]->get(j));
                    }
                    double timeBubble = bubbleSort(tempBubble, SORT_BY_EMISSION, ASCENDING);
                    double timeMerge  = mergeSort (tempMerge,  SORT_BY_EMISSION, ASCENDING);

                    cout << left  << setw(14) << "BubbleSort"
                         << setw(10) << cityNames[i]
                         << right << setw(10) << count
                         << setw(12) << fixed << setprecision(4) << timeBubble << "\n";
                    cout << left  << setw(14) << "MergeSort"
                         << setw(10) << cityNames[i]
                         << right << setw(10) << count
                         << setw(12) << fixed << setprecision(4) << timeMerge  << "\n";
                }

                // ----- Search Benchmarks -----
                cout << "\n--- Search Performance (criteria: Transport Mode = 'Car') ---\n";
                cout << left
                     << setw(14) << "Algorithm"
                     << setw(10) << "City"
                     << right
                     << setw(10) << "Number"
                     << setw(10) << "Matches"
                     << setw(14) << "Comparisons"
                     << setw(12) << "Time(ms)" << "\n";
                cout << "------------------------------------------------------------------\n";

                for (int i = 0; i < 3; i++) {
                    int count = recordCounts[i];
                    SearchResult linearResult = linearSearch(*cities[i], SEARCH_BY_TRANSPORT, "Car");
                    SearchResult binaryResult = binarySearch(*cities[i], SEARCH_BY_TRANSPORT, "Car");

                    cout << left  << setw(14) << "LinearSearch"
                         << setw(10) << cityNames[i]
                         << right << setw(10) << count
                         << setw(10) << linearResult.count
                         << setw(14) << linearResult.comparisons
                         << setw(12) << fixed << setprecision(4) << linearResult.timeMs << "\n";
                    cout << left  << setw(14) << "BinarySearch"
                         << setw(10) << cityNames[i]
                         << right << setw(10) << count
                         << setw(10) << binaryResult.count
                         << setw(14) << binaryResult.comparisons
                         << setw(12) << fixed << setprecision(4) << binaryResult.timeMs << "\n";
                }

                // ----- Memory Footprint -----
                cout << "\n--- Memory Footprint (Array) ---\n";
                cout << "sizeof(Resident) = " << sizeof(Resident) << " bytes per element\n";
                cout << left  << setw(10) << "City"
                     << right << setw(10) << "Number"
                     << setw(16) << "Mem (bytes)"
                     << setw(12) << "Mem (KB)" << "\n";
                cout << "--------------------------------------------\n";
                for (int i = 0; i < 3; i++) {
                    int memoryBytes = static_cast<int>(sizeof(Resident)) * recordCounts[i];
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
