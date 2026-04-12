// Member 1 (skeleton) - all members contribute
// program2_linkedlist/main_linkedlist.cpp - Main program for Linked List-based implementation

#include <cstdio>
#include "linkedlist.h"
#include "../shared/csvloader.h"
#include "../shared/analysis.h"
#include "linkedlist_sort.h"
#include "linkedlist_search.h"

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
        printf("Error loading one or more CSV files.\n");
        return 1;
    }

    printf("Loaded: City A = %d | City B = %d | City C = %d\n", countA, countB, countC);

    // Populate ResidentList objects from raw arrays from structured access
    ResidentList listA, listB, listC;
    for (int i = 0; i < countA; i++) listA.insertAtTail(rawA[i]);
    for (int i = 0; i < countB; i++) listB.insertAtTail(rawB[i]);
    for (int i = 0; i < countC; i++) listC.insertAtTail(rawC[i]);

    int choice = 0;
    do {
        printf("\n========================================\n");
        printf("  DSTR Assignment - Linked List Program\n");
        printf("========================================\n");
        printf("1. Age Group Categorization & Analysis\n");  // Member 1 [BAN]
        printf("2. Carbon Emission Analysis\n");              // Member 5 [EV]
        printf("3. Sorting Experiments\n");                   // Member 3 [EEE]
        printf("4. Searching Experiments\n");                 // Member 4 [WK]
        printf("5. Performance Analysis\n");                  // Member 3 [EEE]
        printf("6. Insights & Recommendations\n");            // All
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            // Case 1: Display age ground categorisation and emission analysis for all cities
            case 1:
                analyzeByAgeGroup(rawA, countA, "City A");
                analyzeByAgeGroup(rawB, countB, "City B");
                analyzeByAgeGroup(rawC, countC, "City C");
                break;
            case 2:
                // TODO [EV]: call printTotalEmissions + printEmissionsByTransport
                break;
            case 3:
                // TODO [EEE]: prompt sort field/order, run insertionSortLL + selectionSortLL
                break;
            case 4:
                // TODO [WK]: prompt search criteria/keyword, run linearSearchLL + orderedSearchLL
                break;
            case 5:
                // TODO [EEE]: display collected timing + cross-structure comparison
                break;
            case 6:
                // TODO [ALL]: call compareAllCities + printRecommendations
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);

    return 0;
}
