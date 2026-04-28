// Member 1 (skeleton) - all members contribute
// program1_array/main_array.cpp - Main program for Array-based implementation

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
             << "2. Carbon Emission Analysis\n"                // Member 5 [EV]
             << "3. Sorting Experiments\n"                     // Member 2 [WT]
             << "4. Searching Experiments\n"                   // Member 4 [WK]
             << "5. Performance Analysis\n"                    // Member 3 [EEE]
             << "6. Insights & Recommendations\n"              // All
             << "0. Exit\n"
             << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            // Case 1: Display age group categorisation and emission analysis for all cities
            case 1:
                analyzeByAgeGroup(rawA, countA, "City A");
                analyzeByAgeGroup(rawB, countB, "City B");
                analyzeByAgeGroup(rawC, countC, "City C");
                break;
            case 2:
                printTotalEmissions(rawA, countA, "City A");
                printTotalEmissions(rawB, countB, "City B");
                printTotalEmissions(rawC, countC, "City C");
                printEmissionsByTransport(rawA, countA, "City A");
                printEmissionsByTransport(rawB, countB, "City B");
                printEmissionsByTransport(rawC, countC, "City C");
                break;
            case 3: {
                // TODO [WT]: prompt sort field/order, run bubbleSort + mergeSort, print comparison
                cout << "\n--- Sorting Experiments: Array ---\n";

                cout << "Choose Dataset:\n";
                cout << "1. City A\n";
                cout << "2. City B\n";
                cout << "3. City C\n";
                cout << "Select: ";

                int cityChoice;
                cin >> cityChoice;

                ResidentArray* selectedArray = nullptr;
                const char* cityLabel = "";

                if (cityChoice == 1) {
                    selectedArray = &arrA;
                    cityLabel = "City A";
                } else if (cityChoice == 2) {
                    selectedArray = &arrB;
                    cityLabel = "City B";
                } else if (cityChoice == 3) {
                    selectedArray = &arrC;
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
                ResidentArray bubbleCopy(selectedArray->size());
                ResidentArray mergeCopy(selectedArray->size());

                for (int i = 0; i < selectedArray->size(); i++) {
                    bubbleCopy.add(selectedArray->get(i));
                    mergeCopy.add(selectedArray->get(i));
                }

                double bubbleTime = bubbleSort(bubbleCopy, field, order);
                double mergeTime = mergeSort(mergeCopy, field, order);

                printSortedTable(mergeCopy, field, "Merge Sort");
                printSortComparison(bubbleTime, mergeTime, cityLabel);

                // Save the sorted result back to the selected array
                // This helps binary search / ordered search if needed later
                selectedArray->clear();
                for (int i = 0; i < mergeCopy.size(); i++) {
                    selectedArray->add(mergeCopy.get(i));
                }

                cout << "\nThe selected dataset has been sorted using Merge Sort.\n";

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
            case 6:
                compareAllCities(rawA, countA, rawB, countB, rawC, countC);
                printRecommendations(rawA, countA, rawB, countB, rawC, countC);
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
