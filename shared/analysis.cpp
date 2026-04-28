// Member 2 - [EV]
// shared/analysis.cpp - Carbon emission analysis implementation

#include "analysis.h"
#include <cstdio>
#include <cstring>
#include <string>

using namespace std;

// Helper: safely copy string into a fixed char buffer
static void copyStr(char* dst, size_t cap, const string& src) {
    size_t n = src.copy(dst, cap - 1);
    dst[n] = '\0';
}

void analyzeByAgeGroup(const Resident* arr, int count, const char* cityLabel) {

    // Only 4 age groups — no dataset covers 61-100 (Seniors)
    const char* ageGroups[] = {
        AGE_GROUP_1,   // Children/Teens (6-17)
        AGE_GROUP_2,   // Young Adults (18-25)
        AGE_GROUP_3,   // Working Adults (26-45)
        AGE_GROUP_4    // Middle-Aged (46-60)
    };

    printf("\n========================================\n");
    printf("  Age Group Analysis: %s\n", cityLabel);
    printf("========================================\n");

    for (int groupIdx = 0; groupIdx < 4; groupIdx++) {
        double totalEmission = 0.0;
        int groupCount = 0;

        char modes[10][30];
        int modeFreq[10];
        int modeCount = 0;

        // Zero-initialise frequency array before counting
        for (int x = 0; x < 10; x++) modeFreq[x] = 0;

        // Scan all residents, filter by current age group
        for (int r = 0; r < count; r++) {

            if (string(arr[r].ageGroup) != ageGroups[groupIdx]) continue;

            groupCount++;
            totalEmission += arr[r].monthlyEmission;

            // Check if transport mode already seen
            bool modeExists = false;
            for (int m = 0; m < modeCount; m++) {
                if (string(modes[m]) == arr[r].transportMode) {
                    modeFreq[m]++;
                    modeExists = true;
                    break;
                }
            }

            // New mode — register it
            if (!modeExists && modeCount < 10) {
                copyStr(modes[modeCount], sizeof(modes[modeCount]), arr[r].transportMode);
                modeFreq[modeCount] = 1;
                modeCount++;
            }
        }

        // Find most preferred transport mode
        char topMode[30] = "N/A";
        int highestFreq = 0;
        for (int m = 0; m < modeCount; m++) {
            if (modeFreq[m] > highestFreq) {
                highestFreq = modeFreq[m];
                copyStr(topMode, sizeof(topMode), modes[m]);
            }
        }

        double avg = (groupCount > 0) ? totalEmission / groupCount : 0.0;

        printf("\nAge Group : %s\n", ageGroups[groupIdx]);
        printf("Residents : %d\n", groupCount);
        printf("Top Mode  : %s\n", topMode);
        printf("Total CO2 : %.2f kg\n", totalEmission);
        printf("Avg CO2   : %.2f kg per resident\n", avg);
        printf("----------------------------------------\n");
    }
}

void printTotalEmissions(const Resident* arr, int count, const char* cityLabel) {
    double total = 0.0;

    // Sum up monthly emission for every resident in this dataset
    for (int r = 0; r < count; r++) {
        total += arr[r].monthlyEmission;
    }

    printf("\n--- Total Emissions: %s ---\n", cityLabel);
    printf("City : %s\n", cityLabel);
    printf("Total: %.2f kg CO2\n", total);
}

void printEmissionsByTransport(const Resident* arr, int count, const char* cityLabel) {

    char modes[10][30];
    double modeEmission[10];
    int modeResidents[10];
    int modeCount = 0;

    // Zero-initialise before accumulation
    for (int x = 0; x < 10; x++) {
        modeEmission[x] = 0.0;
        modeResidents[x] = 0;
    }

    // Accumulate emissions by transport mode
    for (int r = 0; r < count; r++) {
        bool modeExists = false;

        for (int m = 0; m < modeCount; m++) {
            if (string(modes[m]) == arr[r].transportMode) {
                modeEmission[m] += arr[r].monthlyEmission;
                modeResidents[m]++;
                modeExists = true;
                break;
            }
        }

        // New mode — register it
        if (!modeExists && modeCount < 10) {
            copyStr(modes[modeCount], sizeof(modes[modeCount]), arr[r].transportMode);
            modeEmission[modeCount] = arr[r].monthlyEmission;
            modeResidents[modeCount] = 1;
            modeCount++;
        }
    }

    printf("\n--- Emissions by Transport: %s ---\n", cityLabel);
    printf("%-20s %-10s %-20s %-20s\n",
           "Mode", "Count", "Total (kg CO2)", "Avg per Resident");
    printf("%-20s %-10s %-20s %-20s\n",
           "----", "-----", "--------------", "----------------");

    for (int m = 0; m < modeCount; m++) {
        double avg = (modeResidents[m] > 0) ? modeEmission[m] / modeResidents[m] : 0.0;
        printf("%-20s %-10d %-20.2f %-20.2f\n",
               modes[m], modeResidents[m], modeEmission[m], avg);
    }
}

void compareAllCities(
    const Resident* cityA, int countA,
    const Resident* cityB, int countB,
    const Resident* cityC, int countC
) {
    // Sum emissions per city
    double emissionA = 0, emissionB = 0, emissionC = 0;
    for (int r = 0; r < countA; r++) emissionA += cityA[r].monthlyEmission;
    for (int r = 0; r < countB; r++) emissionB += cityB[r].monthlyEmission;
    for (int r = 0; r < countC; r++) emissionC += cityC[r].monthlyEmission;

    // Average per resident per city
    double avgA = countA > 0 ? emissionA / countA : 0;
    double avgB = countB > 0 ? emissionB / countB : 0;
    double avgC = countC > 0 ? emissionC / countC : 0;

    // Combined overall figures
    int totalResidents     = countA + countB + countC;
    double overallEmission = emissionA + emissionB + emissionC;
    double overallAvg      = totalResidents > 0 ? overallEmission / totalResidents : 0;

    printf("\n========================================\n");
    printf("   Cross-City Emission Comparison\n");
    printf("========================================\n");
    printf("%-20s %-12s %-20s %-20s\n",
           "City", "Residents", "Total (kg CO2)", "Avg per Resident");
    printf("%-20s %-12s %-20s %-20s\n",
           "----", "---------", "--------------", "----------------");
    printf("%-20s %-12d %-20.2f %-20.2f\n", "City A (Metro)",    countA, emissionA, avgA);
    printf("%-20s %-12d %-20.2f %-20.2f\n", "City B (Uni Town)", countB, emissionB, avgB);
    printf("%-20s %-12d %-20.2f %-20.2f\n", "City C (Suburban)", countC, emissionC, avgC);
    printf("%-20s %-12s %-20s %-20s\n",
           "----", "---------", "--------------", "----------------");
    printf("%-20s %-12d %-20.2f %-20.2f\n",
           "OVERALL", totalResidents, overallEmission, overallAvg);
}

void printRecommendations(
    const Resident* cityA, int countA,
    const Resident* cityB, int countB,
    const Resident* cityC, int countC
) {
    // Find highest-emitting city
    double emissionA = 0, emissionB = 0, emissionC = 0;
    for (int r = 0; r < countA; r++) emissionA += cityA[r].monthlyEmission;
    for (int r = 0; r < countB; r++) emissionB += cityB[r].monthlyEmission;
    for (int r = 0; r < countC; r++) emissionC += cityC[r].monthlyEmission;

    const char* topCity = "City A";
    double highestTotal = emissionA;
    if (emissionB > highestTotal) { highestTotal = emissionB; topCity = "City B"; }
    if (emissionC > highestTotal) { highestTotal = emissionC; topCity = "City C"; }

    // Find most and least used transport mode across all cities
    const Resident* cityDatasets[3] = { cityA, cityB, cityC };
    int cityCounts[3] = { countA, countB, countC };

    char modes[10][30];
    int modeFreq[10];
    int modeCount = 0;
    for (int x = 0; x < 10; x++) modeFreq[x] = 0;

    for (int d = 0; d < 3; d++) {
        for (int r = 0; r < cityCounts[d]; r++) {
            bool modeExists = false;
            for (int m = 0; m < modeCount; m++) {
                if (string(modes[m]) == cityDatasets[d][r].transportMode) {
                    modeFreq[m]++;
                    modeExists = true;
                    break;
                }
            }
            if (!modeExists && modeCount < 10) {
                copyStr(modes[modeCount], sizeof(modes[modeCount]),
                        cityDatasets[d][r].transportMode);
                modeFreq[modeCount] = 1;
                modeCount++;
            }
        }
    }

    char mostUsedMode[30]  = "N/A";
    char leastUsedMode[30] = "N/A";
    int highestFreq = 0, lowestFreq = 999999;

    for (int m = 0; m < modeCount; m++) {
        if (modeFreq[m] > highestFreq) {
            highestFreq = modeFreq[m];
            copyStr(mostUsedMode, sizeof(mostUsedMode), modes[m]);
        }
        if (modeFreq[m] < lowestFreq) {
            lowestFreq = modeFreq[m];
            copyStr(leastUsedMode, sizeof(leastUsedMode), modes[m]);
        }
    }

    printf("\n========================================\n");
    printf("   Policy Recommendations\n");
    printf("========================================\n");

    printf("\n1. Focus emission reduction efforts on %s\n", topCity);
    printf("   This city has the highest total emissions (%.2f kg CO2).\n", highestTotal);
    printf("   Stricter emission standards and better public transport are recommended.\n");

    printf("\n2. Reduce reliance on %s as transport\n", mostUsedMode);
    printf("   This is the most used mode across all cities.\n");
    printf("   Congestion charges and carpooling incentives could help lower emissions.\n");

    printf("\n3. Encourage use of %s\n", leastUsedMode);
    printf("   This is currently the least used transport mode.\n");
    printf("   Better infrastructure and subsidies could increase adoption.\n");

    printf("\n4. Support working adults (26-60) with greener commute options\n");
    printf("   This group tends to drive longer distances.\n");
    printf("   Work-from-home policies and transit subsidies would help.\n");

    printf("\n5. Invest in cycling and walking infrastructure for City B\n");
    printf("   University students are more likely to adopt green transport.\n");
    printf("   Affordable passes and safe cycling lanes would make a difference.\n");

    printf("\n========================================\n");
}