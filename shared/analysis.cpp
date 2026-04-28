// Member 5 - [EV]
// shared/analysis.cpp - Carbon emission analysis implementation

#include "analysis.h"
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

// Helper: copy a string into a fixed-size char buffer (null-terminated)
static void setField(char* dst, size_t cap, const string& src) {
    size_t n = src.copy(dst, cap - 1);
    dst[n] = '\0';
}

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

    cout << "\n========================================\n";
    cout << "  Age Group Analysis: " << cityLabel << "\n";
    cout << "========================================\n";

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
            if (string(arr[i].ageGroup) != groups[g]) continue;

            groupCount++;
            totalEmission += arr[i].monthlyEmission;

            // Check if this transport mode has already been seen
            bool found = false;
            for (int j = 0; j < uniqueCount; j++) {
                if (string(modes[j]) == arr[i].transportMode) {
                    freq[j]++;   // Increment frequency for existing mode
                    found = true;
                    break;
                }
            }

            // If this is a new transport mode, register it
            if (!found && uniqueCount < 10) {
                setField(modes[uniqueCount], sizeof(modes[uniqueCount]), arr[i].transportMode);
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
                setField(preferred, sizeof(preferred), modes[j]);
            }
        }

        // --- Calculate average emission per resident in this group ---
        double avg = (groupCount > 0) ? totalEmission / groupCount : 0.0;

        // --- Display results for this age grp ---
        cout << "\nAge Group: " << groups[g] << "\n";
        cout << "  Residents        : " << groupCount << "\n";
        cout << "  Preferred Mode   : " << preferred << "\n";
        cout << "  Total Emission   : " << fixed << setprecision(2) << totalEmission << " kg CO2\n";
        cout << "  Avg per Resident : " << fixed << setprecision(2) << avg << " kg CO2\n";
        cout << "  ----------------------------------------\n";
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
    cout << "\n--- Total Emissions: " << cityLabel << " ---\n";
    cout << left << setw(30) << "City" << "Total Emission (kg CO2)\n";
    cout << left << setw(30) << cityLabel << fixed << setprecision(2) << total << "\n";
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
            if (string(modes[j]) == mode) {
                totals[j] += arr[i].monthlyEmission;  // Add to existing total
                modeCounts[j]++;
                found = true;
                break;
            }
        }

        // If new mode — register it
        if (!found && uniqueCount < 10) {
            setField(modes[uniqueCount], sizeof(modes[uniqueCount]), mode);
            totals[uniqueCount] = arr[i].monthlyEmission;
            modeCounts[uniqueCount] = 1;
            uniqueCount++;
        }
    }

    // --- Print results in table ---
    cout << "\n--- Emissions by Transport Mode: " << cityLabel << " ---\n";
    cout << left
         << setw(20) << "Transport Mode"
         << setw(10) << "Count"
         << setw(25) << "Total Emission (kg CO2)"
         << setw(25) << "Avg per Resident" << "\n";
    cout << left
         << setw(20) << "--------------------"
         << setw(10) << "----------"
         << setw(25) << "-------------------------"
         << setw(25) << "-------------------------" << "\n";

    for (int i = 0; i < uniqueCount; i++) {
        // Compute average emission for this transport mode
        double avg = (modeCounts[i] > 0) ? totals[i] / modeCounts[i] : 0.0;
        cout << left
             << setw(20) << modes[i]
             << setw(10) << modeCounts[i]
             << setw(25) << fixed << setprecision(2) << totals[i]
             << setw(25) << fixed << setprecision(2) << avg << "\n";
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
    cout << "\n========================================\n";
    cout << "   Cross-City Emission Comparison\n";
    cout << "========================================\n";
    cout << left
         << setw(20) << "City"
         << setw(12) << "Residents"
         << setw(25) << "Total Emission (kg CO2)"
         << setw(25) << "Avg per Resident" << "\n";
    cout << left
         << setw(20) << "--------------------"
         << setw(12) << "------------"
         << setw(25) << "-------------------------"
         << setw(25) << "-------------------------" << "\n";
    cout << left
         << setw(20) << "City A (Metro)"
         << setw(12) << countA
         << setw(25) << fixed << setprecision(2) << totalA
         << setw(25) << fixed << setprecision(2) << avgA << "\n";
    cout << left
         << setw(20) << "City B (Uni Town)"
         << setw(12) << countB
         << setw(25) << fixed << setprecision(2) << totalB
         << setw(25) << fixed << setprecision(2) << avgB << "\n";
    cout << left
         << setw(20) << "City C (Suburban)"
         << setw(12) << countC
         << setw(25) << fixed << setprecision(2) << totalC
         << setw(25) << fixed << setprecision(2) << avgC << "\n";
    cout << left
         << setw(20) << "--------------------"
         << setw(12) << "------------"
         << setw(25) << "-------------------------"
         << setw(25) << "-------------------------" << "\n";
    cout << left
         << setw(20) << "OVERALL"
         << setw(12) << totalResidents
         << setw(25) << fixed << setprecision(2) << grandTotal
         << setw(25) << fixed << setprecision(2) << grandAvg << "\n";
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
                if (string(modes[j]) == mode) { freq[j]++; found = true; break; }
            }
            if (!found && uniqueCount < 10) {
                setField(modes[uniqueCount], sizeof(modes[uniqueCount]), mode);
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
        if (freq[j] > maxFreq) { maxFreq = freq[j]; setField(dominantMode, sizeof(dominantMode), modes[j]); }
        if (freq[j] < minFreq) { minFreq = freq[j]; setField(leastMode,    sizeof(leastMode),    modes[j]); }
    }

    // --- Print recommendations ---
    cout << "\n========================================\n";
    cout << "   Policy Recommendations\n";
    cout << "========================================\n";

    cout << "\n1. PRIORITISE EMISSION REDUCTION IN " << highestCity << "\n";
    cout << "   -> This city recorded the highest total emissions ("
         << fixed << setprecision(2) << highestTotal << " kg CO2).\n";
    cout << "      City planners should introduce stricter vehicle emission standards\n";
    cout << "      and increase investment in public transport infrastructure here first.\n";

    cout << "\n2. REDUCE DEPENDENCY ON " << dominantMode << "\n";
    cout << "   -> '" << dominantMode << "' is the most commonly used transport mode across all cities.\n";
    cout << "      Introducing congestion charges or carpooling incentives can\n";
    cout << "      reduce per-capita emissions from this mode significantly.\n";

    cout << "\n3. PROMOTE LOW-EMISSION ALTERNATIVES\n";
    cout << "   -> '" << leastMode << "' is the least used transport mode.\n";
    cout << "      Subsidies, improved infrastructure (e.g. cycling lanes, bus shelters),\n";
    cout << "      and awareness campaigns can encourage a shift to greener options.\n";

    cout << "\n4. TARGET HIGH-EMISSION AGE GROUPS WITH INCENTIVES\n";
    cout << "   -> Working Adults (26-60) typically travel longer distances by car.\n";
    cout << "      Flexible work-from-home policies and employer transit subsidies\n";
    cout << "      can meaningfully reduce emissions in this demographic.\n";

    cout << "\n5. EXPAND SUSTAINABLE OPTIONS FOR YOUNGER RESIDENTS\n";
    cout << "   -> City B (University Town) has students who are more open to cycling\n";
    cout << "      and walking. Investing in safe cycling infrastructure and affordable\n";
    cout << "      public transport passes would lower emissions among this group.\n";

    cout << "\n========================================\n";
}
