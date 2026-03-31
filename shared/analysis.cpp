// Member 5 - [EV]
// shared/analysis.cpp - Carbon emission analysis implementation

#include "analysis.h"
#include <cstdio>
#include <cstring>

void analyzeByAgeGroup(const Resident* arr, int count, const char* cityLabel) {
    // TODO:
    // For each of 5 age groups:
    //   - Count residents
    //   - Tally emissions per transport mode to find most preferred
    //   - Sum total monthly emission
    //   - Compute average = total / count
    // Print as formatted text table
}

void printTotalEmissions(const Resident* arr, int count, const char* cityLabel) {
    // TODO:
    // Sum all monthlyEmission values and print with cityLabel
}

void printEmissionsByTransport(const Resident* arr, int count, const char* cityLabel) {
    // TODO:
    // For each unique transport mode, sum emissions and print as table
}

void compareAllCities(
    const Resident* cityA, int countA,
    const Resident* cityB, int countB,
    const Resident* cityC, int countC
) {
    // TODO:
    // Print a side-by-side comparison table of total emissions per city
}

void printRecommendations(
    const Resident* cityA, int countA,
    const Resident* cityB, int countB,
    const Resident* cityC, int countC
) {
    // TODO:
    // Analyse findings and print 3-5 policy recommendations for city planners
    // e.g. highest-emitting age group, dominant transport mode, cross-city lessons
}
