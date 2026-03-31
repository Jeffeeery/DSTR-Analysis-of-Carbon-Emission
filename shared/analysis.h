// Member 5 - [EV]
// shared/analysis.h - Carbon emission analysis declarations

#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "resident.h"

// -------------------------------------------------------
// Age Group Analysis
// -------------------------------------------------------

// Print a table showing for each age group:
//   - most preferred transport mode
//   - total monthly emission
//   - average monthly emission per resident
void analyzeByAgeGroup(const Resident* arr, int count, const char* cityLabel);

// -------------------------------------------------------
// Emission Totals
// -------------------------------------------------------

// Print total emissions for a dataset
void printTotalEmissions(const Resident* arr, int count, const char* cityLabel);

// Print emissions broken down by transport mode
void printEmissionsByTransport(const Resident* arr, int count, const char* cityLabel);

// -------------------------------------------------------
// Cross-Dataset Comparison
// -------------------------------------------------------

// Compare total emissions across 3 cities side-by-side
void compareAllCities(
    const Resident* cityA, int countA,
    const Resident* cityB, int countB,
    const Resident* cityC, int countC
);

// -------------------------------------------------------
// Insights & Recommendations
// -------------------------------------------------------

// Print policy recommendations based on analysis results
void printRecommendations(
    const Resident* cityA, int countA,
    const Resident* cityB, int countB,
    const Resident* cityC, int countC
);

#endif // ANALYSIS_H
