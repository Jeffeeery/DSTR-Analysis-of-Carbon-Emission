// Member 1 (skeleton) - all members contribute
// program2_linkedlist/main_linkedlist.cpp - Main program for Linked List-based implementation

#include <iostream>
#include <limits>
#include <string>
#include "linkedlist.h"
#include "../shared/csvloader.h"
#include "../shared/analysis.h"
#include "linkedlist_sort.h"
#include "linkedlist_search.h"

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
             << "2. Carbon Emission Analysis\n"              // Member 5 [EV]
             << "3. Sorting Experiments\n"                   // Member 3 [EEE]
             << "4. Searching Experiments\n"                 // Member 4 [WK]
             << "5. Performance Analysis\n"                  // Member 3 [EEE]
             << "6. Insights & Recommendations\n"            // All
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
            case 2:
                printTotalEmissions(rawA, countA, "City A");
                printTotalEmissions(rawB, countB, "City B");
                printTotalEmissions(rawC, countC, "City C");
                printEmissionsByTransport(rawA, countA, "City A");
                printEmissionsByTransport(rawB, countB, "City B");
                printEmissionsByTransport(rawC, countC, "City C");
                break;
            case 3:
                // TODO [EEE]: prompt sort field/order, run insertionSortLL + selectionSortLL
                break;
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
            case 5:
                // TODO [EEE]: display collected timing + cross-structure comparison
                break;
            case 6:
                // TODO [ALL]: call compareAllCities + printRecommendations
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
