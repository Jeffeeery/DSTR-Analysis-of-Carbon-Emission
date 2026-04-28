// Member 1 - [BAN]
// shared/csvloader.h - CSV file loading declarations

#ifndef CSVLOADER_H
#define CSVLOADER_H

#include "resident.hpp"

// Maximum number of residents that can be loaded
#define MAX_RESIDENTS 500

// Load residents from a CSV file into an array
// Returns the number of records loaded, or -1 on error
// Handles both City A format and City B/C format automatically
int loadCSV(const char* filename, Resident* arr, int maxSize);

// Helper: trim whitespace/quotes from a C-string in-place
void trimString(char* str);

// Helper: assign ageGroup and compute monthlyEmission after loading
void processResidents(Resident* arr, int count);

#endif // CSVLOADER_H
