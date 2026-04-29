// CSV file loading implementation

#include "csvloader.hpp"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Helper: copy a string into a fixed-size char buffer (null-terminated)
static void copyField(char* dst, int cap, const string& src) {
    int n = src.copy(dst, cap - 1);
    dst[n] = '\0';
}

void trimString(char* str) {
    string s(str);

    // Remove trailing whitespace and newline
    while (!s.empty() && (s.back() == ' ' || s.back() == '\n' || s.back() == '\r')) {
        s.pop_back();
    }

    // Remove leading whitespace
    int start = 0;
    while (start < (int)s.size() && s[start] == ' ') {
        start++;
    }
    s.erase(0, start);

    int n = s.copy(str, s.size());
    str[n] = '\0';
}

void processResidents(Resident* arr, int count) {
    for (int i = 0; i < count; i++) {
        computeResident(arr[i]);
    }
}

int loadCSV(const char* filename, Resident* arr, int maxSize) {
    // 1. Open file with ifstream
    ifstream file;
    file.open(filename);
    if (!file.is_open())
        return -1;

    // 2. Read and skip header line
    string header;
    getline(file, header);

    // 3. For each data line, parse comma-separated fields into a Resident struct
    string line;
    int count = 0;
    while (count < maxSize && getline(file, line)) {
        istringstream ss(line);
        string field;

        // residentID
        if (!getline(ss, field, ',')) continue;
        copyField(arr[count].residentID, sizeof(arr[count].residentID), field);

        // age
        if (!getline(ss, field, ',')) continue;
        arr[count].age = stoi(field);

        // transportMode
        if (!getline(ss, field, ',')) continue;
        copyField(arr[count].transportMode, sizeof(arr[count].transportMode), field);

        // dailyDistance
        if (!getline(ss, field, ',')) continue;
        arr[count].dailyDistance = stod(field);

        // emissionFactor
        if (!getline(ss, field, ',')) continue;
        arr[count].emissionFactor = stod(field);

        // avgDaysPerMonth
        if (!getline(ss, field, ',')) continue;
        arr[count].avgDaysPerMonth = stoi(field);

        count++;
    }

    // 4. Call processResidents() after loading
    processResidents(arr, count);

    // 5. Return count of loaded records
    return count;
}
