// Member 1 (skeleton) - all members contribute
// program1_array/main_array.cpp - Main program for Array-based implementation

#include <cstdio>
#include "arraylist.h"
#include "../shared/csvloader.h"
#include "../shared/analysis.h"
#include "array_sort.h"
#include "array_search.h"

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

    // Populate ResidentArray objects from raw arrays for structured access
    ResidentArray arrA, arrB, arrC;
    for (int i = 0; i < countA; i++) arrA.add(rawA[i]);
    for (int i = 0; i < countA; i++) arrB.add(rawB[i]);
    for (int i = 0; i < countA; i++) arrC.add(rawC[i]);

    int choice = 0;
    do {
        printf("\n========================================\n");
        printf("  DSTR Assignment - Array Program\n");
        printf("========================================\n");
        printf("1. Age Group Categorization & Analysis\n");     // Member 1 [BAN]
        printf("2. Carbon Emission Analysis\n");                // Member 5 [EV]
        printf("3. Sorting Experiments\n");                     // Member 2 [WT]
        printf("4. Searching Experiments\n");                   // Member 4 [WK]
        printf("5. Performance Analysis\n");                    // Member 3 [EEE]
        printf("6. Insights & Recommendations\n");              // All
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            // Case 1: Display age group categorisation and emission analysis for all cities
            case 1:
                analyzeByAgeGroup(rawA, countA, "City A");
                analyzeByAgeGroup(rawB, countB, "City B");
                analyzeByAgeGroup(rawC, countC, "City C");
                break;
            case 2:
                // TODO [EV]: call printTotalEmissions + printEmissionsByTransport

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
            case 4:{
                printf("\n--- Searching Experiments ---\n");
                printf("1. Age Group\n2. Transport Mode\n3. Distance Threshold\nSelect: ");
                int sChoice;
                scanf("%d", &sChoice);

                char keyword[50];
                printf("Enter search keyword (Case Sensitive, e.g., 'Car' or 'Working Adults (26-45)'): ");
                scanf(" %[^\n]s", keyword); 

                SearchCriteria crit = (sChoice == 1) ? SEARCH_BY_AGE_GROUP : 
                                    (sChoice == 2) ? SEARCH_BY_TRANSPORT : 
                                    SEARCH_BY_DISTANCE_THRESHOLD;

                // Create pointers to easily iterate through our cities
                ResidentArray* cities[] = {&arrA, &arrB, &arrC};
                const char* cityNames[] = {"City A", "City B", "City C"};

                for (int i = 0; i < 3; i++) {
                    printf("\n>>> Results for %s <<<", cityNames[i]);
        
                    // Run Searches
                    SearchResult linRes = linearSearch(*cities[i], crit, keyword);
                    SearchResult binRes = binarySearch(*cities[i], crit, keyword);

                    // Display results using your functions
                    printSearchResults(*cities[i], linRes, crit, keyword);
                    printSearchComparison(linRes, binRes);
                }
                break;
            }                  
            case 5:
                // TODO [EEE]: display collected timing + memory discussion
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
