// Member 1 (skeleton) - all members contribute
// program1_array/main_array.cpp - Main program for Array-based implementation

#include <iostream>
#include <limits>
#include <string>
#include "arraylist.h"
#include "../shared/csvloader.h"
#include "../shared/analysis.h"
#include "array_sort.h"
#include "array_search.h"

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
            case 3:
                // TODO [WT]: prompt sort field/order, run bubbleSort + mergeSort, print comparison
                break;
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

                // Create pointers to easily iterate through our cities
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
            case 5:
                // TODO [EEE]: display collected timing + memory discussion
                break;
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
