// Member 5 - [EV]
// shared/analysis.cpp - Carbon emission analysis implementation

#include "analysis.h"
#include <cstdio>
#include <cstring>

// -------------------------------------------------------
// analyzeByAgeGroup()
// Purpose : For a given city dataset, loop through all 5 age groups and display:
//           - Number of residents in that group
//           - Most preferred transport mode (by frequency count)
//           - Total monthly carbon emission for the group
//           - Average monthly carbon emission per resident
// -------------------------------------------------------
void analyzeByAgeGroup(const Resident* arr, int count, const char* cityLabel) {

    const char* groups[] = {
        AGE_GROUP_1,   
        AGE_GROUP_2,   
        AGE_GROUP_3,   
        AGE_GROUP_4,   
        AGE_GROUP_5    
    };

    printf("\n========================================\n");
    printf("  Age Group Analysis: %s\n", cityLabel);
    printf("========================================\n");

    // Iterate over each of the 5 age groups
    for (int g = 0; g < 5; g++) {
        double totalEmission = 0.0;
        int groupCount = 0;

        // Parallel arrays used as a manual frequency map 
        char modes[10][30];
        int freq[10];
        int uniqueCount = 0;

        // Zero-initialise frequency array before counting
        for (int k = 0; k < 10; k++) freq[k] = 0;

        // --- Pass 1: Scan all residents, filter by current age group ---
        for (int i = 0; i < count; i++) {

            // Skip diff age grp residents 
            if (strcmp(arr[i].ageGroup, groups[g]) != 0) continue;

            groupCount++;
            totalEmission += arr[i].monthlyEmission; 

            // Check if this transport mode has already been seen
            bool found = false;
            for (int j = 0; j < uniqueCount; j++) {
                if (strcmp(modes[j], arr[i].transportMode) == 0) {
                    freq[j]++;   // Increment frequency for existing mode
                    found = true;
                    break;
                }
            }

            // If this is a new transport mode, register it
            if (!found && uniqueCount < 10) {
                strcpy(modes[uniqueCount], arr[i].transportMode);
                freq[uniqueCount] = 1;   // First occurrence
                uniqueCount++;
            }
        }

        // --- Find the mode with the highest frequency (most preferred) ---
        char preferred[30] = "N/A";  // Default 
        int maxFreq = 0;
        for (int j = 0; j < uniqueCount; j++) {
            if (freq[j] > maxFreq) {
                maxFreq = freq[j];
                strcpy(preferred, modes[j]);
            }
        }

        // --- Calculate average emission per resident in this group ---
        double avg = (groupCount > 0) ? totalEmission / groupCount : 0.0;

        // --- Display results for this age grp ---
        printf("\nAge Group: %s\n", groups[g]);
        printf("  Residents        : %d\n", groupCount);
        printf("  Preferred Mode   : %s\n", preferred);
        printf("  Total Emission   : %.2f kg CO2\n", totalEmission);
        printf("  Avg per Resident : %.2f kg CO2\n", avg);
        printf("  ----------------------------------------\n");
    }
}

// -------------------------------------------------------
// printTotalEmissions()
// Purpose : Sum and display the total monthly carbon emission for one city dataset.
// -------------------------------------------------------
void printTotalEmissions(const Resident* arr, int count, const char* cityLabel) {
    double total = 0.0;

    // Accumulate monthly emission across all residents in the dataset
    for (int i = 0; i < count; i++) {
        total += arr[i].monthlyEmission;
    }

    // Display as a simple two-column table
    printf("\n--- Total Emissions: %s ---\n", cityLabel);
    printf("%-30s %s\n", "City", "Total Emission (kg CO2)");
    printf("%-30s %.2f\n", cityLabel, total);
}

// -------------------------------------------------------
// printEmissionsByTransport()
// Purpose : Break down monthly emissions by transport mode for one city.
//           Shows count of residents, total emission, and average per resident
//           for each unique transport mode found in the dataset.
// -------------------------------------------------------
void printEmissionsByTransport(const Resident* arr, int count, const char* cityLabel) {

    // Parallel arrays acting as a manual key-value store for transport modes
    char modes[10][30];
    double totals[10];
    int modeCounts[10];
    int uniqueCount = 0;

    // Zero-initialise 
    for (int i = 0; i < 10; i++) {
        totals[i] = 0.0;
        modeCounts[i] = 0;
    }

    // --- loop through all residents and accumulate by transport mode ---
    for (int i = 0; i < count; i++) {
        const char* mode = arr[i].transportMode;
        bool found = false;

        // Search if this mode already exists in our manual map
        for (int j = 0; j < uniqueCount; j++) {
            if (strcmp(modes[j], mode) == 0) {
                totals[j] += arr[i].monthlyEmission;  // Add to existing total
                modeCounts[j]++;
                found = true;
                break;
            }
        }

        // If new mode — register it
        if (!found && uniqueCount < 10) {
            strcpy(modes[uniqueCount], mode);
            totals[uniqueCount] = arr[i].monthlyEmission;
            modeCounts[uniqueCount] = 1;
            uniqueCount++;
        }
    }

    // --- Print results in table ---
    printf("\n--- Emissions by Transport Mode: %s ---\n", cityLabel);
    printf("%-20s %-10s %-25s %-25s\n",
           "Transport Mode", "Count", "Total Emission (kg CO2)", "Avg per Resident");
    printf("%-20s %-10s %-25s %-25s\n",
           "--------------------", "----------",
           "-------------------------", "-------------------------");

    for (int i = 0; i < uniqueCount; i++) {
        // Compute average emission for this transport mode
        double avg = (modeCounts[i] > 0) ? totals[i] / modeCounts[i] : 0.0;
        printf("%-20s %-10d %-25.2f %-25.2f\n",
               modes[i], modeCounts[i], totals[i], avg);
    }
}

// -------------------------------------------------------
// compareAllCities()
// Purpose : Display a side-by-side comparison table of total emissions
//           across all three city datasets, plus an overall combined row.
// -------------------------------------------------------
void compareAllCities(
    const Resident* cityA, int countA,
    const Resident* cityB, int countB,
    const Resident* cityC, int countC
) {
    // Accumulate totals for each city separately
    double totalA = 0, totalB = 0, totalC = 0;
    for (int i = 0; i < countA; i++) totalA += cityA[i].monthlyEmission;
    for (int i = 0; i < countB; i++) totalB += cityB[i].monthlyEmission;
    for (int i = 0; i < countC; i++) totalC += cityC[i].monthlyEmission;

    // Compute per-resident averages for each city
    double avgA = countA > 0 ? totalA / countA : 0;
    double avgB = countB > 0 ? totalB / countB : 0;
    double avgC = countC > 0 ? totalC / countC : 0;

    // Combined totals across all three cities
    int totalResidents = countA + countB + countC;
    double grandTotal  = totalA + totalB + totalC;
    double grandAvg    = totalResidents > 0 ? grandTotal / totalResidents : 0;

    // --- Print comparison table ---
    printf("\n========================================\n");
    printf("   Cross-City Emission Comparison\n");
    printf("========================================\n");
    printf("%-20s %-12s %-25s %-25s\n",
           "City", "Residents", "Total Emission (kg CO2)", "Avg per Resident");
    printf("%-20s %-12s %-25s %-25s\n",
           "--------------------", "------------",
           "-------------------------", "-------------------------");
    printf("%-20s %-12d %-25.2f %-25.2f\n", "City A (Metro)",    countA, totalA, avgA);
    printf("%-20s %-12d %-25.2f %-25.2f\n", "City B (Uni Town)", countB, totalB, avgB);
    printf("%-20s %-12d %-25.2f %-25.2f\n", "City C (Suburban)", countC, totalC, avgC);
    printf("%-20s %-12s %-25s %-25s\n",     // Separator before OVERALL row
           "--------------------", "------------",
           "-------------------------", "-------------------------");
    printf("%-20s %-12d %-25.2f %-25.2f\n", "OVERALL",
           totalResidents, grandTotal, grandAvg);
}

// -------------------------------------------------------
// printRecommendations()
// Purpose : Analyse cross-city data and print practical policy recommendations
//           for city planners based on emission patterns and transport preferences.
// -------------------------------------------------------
void printRecommendations(
    const Resident* cityA, int countA,
    const Resident* cityB, int countB,
    const Resident* cityC, int countC
) {
    // --- Find highest-emitting city ---
    double totalA = 0, totalB = 0, totalC = 0;
    for (int i = 0; i < countA; i++) totalA += cityA[i].monthlyEmission;
    for (int i = 0; i < countB; i++) totalB += cityB[i].monthlyEmission;
    for (int i = 0; i < countC; i++) totalC += cityC[i].monthlyEmission;

    const char* highestCity = "City A";
    double highestTotal = totalA;
    if (totalB > highestTotal) { highestTotal = totalB; highestCity = "City B"; }
    if (totalC > highestTotal) { highestTotal = totalC; highestCity = "City C"; }

    // --- Find dominant transport mode across all cities combined ---
    // Merge all three datasets into one scan
    const Resident* allCities[3] = { cityA, cityB, cityC };
    int allCounts[3] = { countA, countB, countC };

    char modes[10][30];
    int freq[10];
    int uniqueCount = 0;
    for (int k = 0; k < 10; k++) freq[k] = 0;

    for (int d = 0; d < 3; d++) {
        for (int i = 0; i < allCounts[d]; i++) {
            const char* mode = allCities[d][i].transportMode;
            bool found = false;
            for (int j = 0; j < uniqueCount; j++) {
                if (strcmp(modes[j], mode) == 0) { freq[j]++; found = true; break; }
            }
            if (!found && uniqueCount < 10) {
                strcpy(modes[uniqueCount], mode);
                freq[uniqueCount] = 1;
                uniqueCount++;
            }
        }
    }

    // Find the most and least used transport mode overall
    char dominantMode[30] = "N/A";
    char leastMode[30]    = "N/A";
    int maxFreq = 0, minFreq = 999999;
    for (int j = 0; j < uniqueCount; j++) {
        if (freq[j] > maxFreq) { maxFreq = freq[j]; strcpy(dominantMode, modes[j]); }
        if (freq[j] < minFreq) { minFreq = freq[j]; strcpy(leastMode,    modes[j]); }
    }

    // --- Print recommendations ---
    printf("\n========================================\n");
    printf("   Policy Recommendations\n");
    printf("========================================\n");

    printf("\n1. PRIORITISE EMISSION REDUCTION IN %s\n", highestCity);
    printf("   -> This city recorded the highest total emissions (%.2f kg CO2).\n", highestTotal);
    printf("      City planners should introduce stricter vehicle emission standards\n");
    printf("      and increase investment in public transport infrastructure here first.\n");

    printf("\n2. REDUCE DEPENDENCY ON %s\n", dominantMode);
    printf("   -> '%s' is the most commonly used transport mode across all cities.\n", dominantMode);
    printf("      Introducing congestion charges or carpooling incentives can\n");
    printf("      reduce per-capita emissions from this mode significantly.\n");

    printf("\n3. PROMOTE LOW-EMISSION ALTERNATIVES\n");
    printf("   -> '%s' is the least used transport mode.\n", leastMode);
    printf("      Subsidies, improved infrastructure (e.g. cycling lanes, bus shelters),\n");
    printf("      and awareness campaigns can encourage a shift to greener options.\n");

    printf("\n4. TARGET HIGH-EMISSION AGE GROUPS WITH INCENTIVES\n");
    printf("   -> Working Adults (26-60) typically travel longer distances by car.\n");
    printf("      Flexible work-from-home policies and employer transit subsidies\n");
    printf("      can meaningfully reduce emissions in this demographic.\n");

    printf("\n5. EXPAND SUSTAINABLE OPTIONS FOR YOUNGER RESIDENTS\n");
    printf("   -> City B (University Town) has students who are more open to cycling\n");
    printf("      and walking. Investing in safe cycling infrastructure and affordable\n");
    printf("      public transport passes would lower emissions among this group.\n");

    printf("\n========================================\n");
}