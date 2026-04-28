#include "resident.hpp"
#include <string>

using namespace std;

// Helper: copy a string into a fixed-size char buffer (null-terminated)
static void setField(char* dst, size_t cap, const string& src) {
    size_t n = src.copy(dst, cap - 1);
    dst[n] = '\0';
}

void computeResident(Resident& r) {
    r.monthlyEmission = r.dailyDistance * r.emissionFactor * r.avgDaysPerMonth;
    assignAgeGroup(r);
}

void assignAgeGroup(Resident& r) {
    string label;
    if (r.age >= 6 && r.age <= 17)        label = AGE_GROUP_1;
    else if (r.age >= 18 && r.age <= 25)  label = AGE_GROUP_2;
    else if (r.age >= 26 && r.age <= 45)  label = AGE_GROUP_3;
    else if (r.age >= 46 && r.age <= 60)  label = AGE_GROUP_4;
    else                                  label = AGE_GROUP_5;
    setField(r.ageGroup, sizeof(r.ageGroup), label);
}
