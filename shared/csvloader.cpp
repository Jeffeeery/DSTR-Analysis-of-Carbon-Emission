// Member 1 - [BAN]
// shared/csvloader.cpp - CSV file loading implementation

#include "csvloader.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>

void trimString(char* str) {
    // Remove trailing whitespace and newline
    int len = strlen(str);
    while (len > 0 && (str[len-1] == ' ' || str[len-1] == '\n' || str[len-1] == '\r')) {
        str[len-1] = '\0';
        len--;
    }

    // Remove leading whitespace
    int start = 0;
    while (str[start] == ' ') {
        start++;
    }

    if (start > 0) {
        memmove(str, str + start, strlen(str) - start + 1);
    }
}

void processResidents(Resident* arr, int count) {
    for (int i = 0; i < count; i++) {
        computeResident(arr[i]);
    }
}

int loadCSV(const char* filename, Resident* arr, int maxSize) {
    // 1. Open file with fopen
    FILE* file = fopen(filename, "r");
    if (file == NULL)
        return -1;
    
    // 2. Read and skip header line
    char line[256];
    fgets(line, sizeof(line), file);

    // 3. For each data line, parse comma-separated fields into a Resident struct
    //    - Handle City A column order vs City B/C column order
    int count = 0;
    while (fgets(line, sizeof(line), file) != NULL && count < maxSize) {
        sscanf(line, "%14[^,],%d,%29[^,],%lf,%lf,%d",
            arr[count].residentID,          // %14[^,] - Reads up to 14 characters, stopping at a comma
            &arr[count].age,                // %d - Reads an integer
            arr[count].transportMode,       // %29[^,] - Reads up to 29 characters, stopping at a comma
            &arr[count].dailyDistance,      // %lf - Reads a decimal number
            &arr[count].emissionFactor,     // %lf
            &arr[count].avgDaysPerMonth);   // %d
        count++;
    }

    // 4. Call processResidents() after loading
    processResidents(arr, count);
    fclose(file);

    // 5. Return count of loaded records
    return count;
}
