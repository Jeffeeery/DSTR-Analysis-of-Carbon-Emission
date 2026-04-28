// Member 2 - [EV]
// shared/analysis.cpp - Carbon emission analysis implementation

#include "analysis.hpp"
#include <iomanip>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Helper: safely copy string into a fixed char buffer
static void copyStr(char* dst, size_t cap, const string& src) {
    size_t n = src.copy(dst, cap - 1);
    dst[n] = '\0';
}

void analyzeByAgeGroup(const Resident* arr, int count, const char* cityLabel) {


    const char* ageGroups[] = {
        AGE_GROUP_1,   // Children/Teens (6-17)
        AGE_GROUP_2,   // Young Adults (18-25)
        AGE_GROUP_3,   // Working Adults (26-45)
        AGE_GROUP_4    // Middle-Aged (46-60)
    };

    cout << "\n========================================\n";
    cout << "  Age Group Analysis: " << cityLabel << "\n";
    cout << "========================================\n";

    for (int grpNum = 0; grpNum < 4; grpNum++) {
        double totalEmission = 0.0;
        int grpCount = 0;

        char modes[6][20];
        int modeFreq[6];
        int modeCount = 0;

        // Zero-initialise frequency array before counting
        for (int x = 0; x < 6; x++) 
        {
            modeFreq[x] = 0;
        }

        // Scan all residents, filter by current age group
        for (int r = 0; r < count; r++) {

            if (string(arr[r].ageGroup) != ageGroups[grpNum]) 
            {
                continue;
            }

            grpCount++;
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
            if (!modeExists && modeCount < 6) {
                copyStr(modes[modeCount], sizeof(modes[modeCount]), arr[r].transportMode);
                modeFreq[modeCount] = 1;
                modeCount++;
            }
        }

        // Find most preferred transport mode
        char topMode[20] = "N/A";
        int highestFreq = 0;

        for (int m = 0; m < modeCount; m++) {
            if (modeFreq[m] > highestFreq) {    
                highestFreq = modeFreq[m];
                copyStr(topMode, sizeof(topMode), modes[m]);
            }
        }

        double avg = (grpCount > 0) ? totalEmission / grpCount : 0.0;

        cout << "\nAge Group : " << ageGroups[grpNum] << "\n";
        cout << "Residents : " << grpCount << "\n";
        cout << "Top Mode  : " << topMode << "\n";
        cout << "Total CO2 : " << fixed << setprecision(2) << totalEmission << " kg\n";
        cout << "Avg CO2   : " << fixed << setprecision(2) << avg << " kg per resident\n";
        cout << "----------------------------------------\n";
    }
}

void printTotalEmissions(const Resident* arr, int count, const char* cityLabel) {
    double total = 0.0;

    // Sum up monthly emission for every resident in this dataset
    for (int r = 0; r < count; r++) {
        total += arr[r].monthlyEmission;
    }

    cout << "\n--- Total Emissions: " << cityLabel << " ---\n";
    cout << "City  : " << cityLabel << "\n";
    cout << "Total : " << fixed << setprecision(2) << total << " kg CO2\n";
}

void printEmissionsByTransport(const Resident* arr, int count, const char* cityLabel) {

    char modes[6][20];
    double modeEmission[6];
    int modeResidents[6];           
    int modeCount = 0;

    // Zero-initialise before accumulation
    for (int x = 0; x < 6; x++) {
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
        if (!modeExists && modeCount < 6) {
            copyStr(modes[modeCount], sizeof(modes[modeCount]), arr[r].transportMode);
            modeEmission[modeCount] = arr[r].monthlyEmission;
            modeResidents[modeCount] = 1;
            modeCount++;
        }
    }

    cout << "\n--- Emissions by Transport: " << cityLabel << " ---\n";
    cout << left
         << setw(20) << "Mode"
         << setw(10) << "Count"
         << setw(20) << "Total (kg CO2)"
         << setw(20) << "Avg per Resident" << "\n";
    cout << left
         << setw(20) << "----"
         << setw(10) << "-----"
         << setw(20) << "--------------"
         << setw(20) << "----------------" << "\n";

    for (int m = 0; m < modeCount; m++) {
        double avg = (modeResidents[m] > 0) ? modeEmission[m] / modeResidents[m] : 0.0;
        cout << left
             << setw(20) << modes[m]
             << setw(10) << modeResidents[m]
             << setw(20) << fixed << setprecision(2) << modeEmission[m]
             << setw(20) << fixed << setprecision(2) << avg << "\n";
    }
}

void compareAllCities(
    const Resident* cityA, int countA,
    const Resident* cityB, int countB,
    const Resident* cityC, int countC
) {
    // Safety check
    if (!cityA || !cityB || !cityC || countA <= 0 || countB <= 0 || countC <= 0) {
        cout << "Error: Invalid data passed to compareAllCities!\n";
        return;
    }

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

    cout << "\n========================================\n";
    cout << "   Cross-City Emission Comparison\n";
    cout << "========================================\n";
    cout << left
         << setw(20) << "City"
         << setw(12) << "Residents"
         << setw(20) << "Total (kg CO2)"
         << setw(20) << "Avg per Resident" << "\n";
    cout << left
         << setw(20) << "----"
         << setw(12) << "---------"
         << setw(20) << "--------------"
         << setw(20) << "----------------" << "\n";
    cout << left
         << setw(20) << "City A (Metro)"
         << setw(12) << countA
         << setw(20) << fixed << setprecision(2) << emissionA
         << setw(20) << fixed << setprecision(2) << avgA << "\n";
    cout << left
         << setw(20) << "City B (Uni Town)"
         << setw(12) << countB
         << setw(20) << fixed << setprecision(2) << emissionB
         << setw(20) << fixed << setprecision(2) << avgB << "\n";
    cout << left
         << setw(20) << "City C (Suburban)"
         << setw(12) << countC
         << setw(20) << fixed << setprecision(2) << emissionC
         << setw(20) << fixed << setprecision(2) << avgC << "\n";
    cout << left
         << setw(20) << "----"
         << setw(12) << "---------"
         << setw(20) << "--------------"
         << setw(20) << "----------------" << "\n";
    cout << left
         << setw(20) << "OVERALL"
         << setw(12) << totalResidents
         << setw(20) << fixed << setprecision(2) << overallEmission
         << setw(20) << fixed << setprecision(2) << overallAvg << "\n";
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

    char modes[6][20];
    int modeFreq[6];
    int modeCount = 0;
    for (int x = 0; x < 6; x++) modeFreq[x] = 0;

    // Safety check: ensure cityCounts are valid
    if (countA <= 0 || countB <= 0 || countC <= 0) {
        cout << "Error: Invalid city data counts!\n";
        return;
    }

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
            if (!modeExists && modeCount < 6) {
                copyStr(modes[modeCount], sizeof(modes[modeCount]),
                        cityDatasets[d][r].transportMode);
                modeFreq[modeCount] = 1;
                modeCount++;
            }
        }
    }

    char mostUsedMode[20]  = "N/A";
    char leastUsedMode[20] = "N/A";
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
cout << "\n========================================\n";
    cout << "   Policy Recommendations\n";
    cout << "========================================\n";

    // highest-emitting city recommendation
    cout << "\n1. Focus emission reduction efforts on " << topCity << "\n";
    cout << "   This city has the highest total emissions ("
         << fixed << setprecision(2) << highestTotal << " kg CO2).\n";
    cout << "   Prioritize large-scale infrastructure and high-capacity public transit.\n";

    // highest per-resident emissions recommendation
    cout << "\n2. Address high per-resident emissions in City C\n";
    cout << "   Suburban residents have the largest carbon footprint (44.99 kg/person).\n";
    cout << "   Incentivizing carpooling and green commuting is critical here.\n";

    // least used transport mode recommendation
    cout << "\n3. Encourage use of " << leastUsedMode << "\n";
    cout << "   This is currently the least used transport mode across datasets.\n";
    cout << "   Expanding the City B school bus model to other cities could reduce emissions.\n";

    // highest per-resident emissions recommendation
    cout << "\n4. Support working adults (26-60) with greener commute options\n";
    cout << "   This group drives the most, especially in " << topCity << " and City C.\n";
    cout << "   Work-from-home policies and transit subsidies would help significantly.\n";

    // most used transport mode recommendation
    cout << "\n5. Invest in cycling and walking infrastructure for City B\n";
    cout << "   Students show high adoption of zero-emission transport (Bicycle/Walking).\n";
    cout << "   Expanding safe cycling lanes will maintain this eco-friendly trend.\n";
}