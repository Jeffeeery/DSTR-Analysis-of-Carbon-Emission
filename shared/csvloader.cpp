// Member 1 - [BAN]
// shared/csvloader.cpp - CSV file loading implementation

#include "csvloader.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>

void trimString(char* str) {
    // TODO: remove leading/trailing whitespace and quotes from str
}

void processResidents(Resident* arr, int count) {
    for (int i = 0; i < count; i++) {
        computeResident(arr[i]);
    }
}

int loadCSV(const char* filename, Resident* arr, int maxSize) {
    // TODO:
    // 1. Open file with fopen
    // 2. Read and skip header line
    // 3. For each data line, parse comma-separated fields into a Resident struct
    //    - Handle City A column order vs City B/C column order
    // 4. Call processResidents() after loading
    // 5. Return count of loaded records
    return 0;
}
