#include "resident.h"
#include <cstring>

void computeResident(Resident& r) {
    r.monthlyEmission = r.dailyDistance * r.emissionFactor * r.avgDaysPerMonth;
    assignAgeGroup(r);
}

void assignAgeGroup(Resident& r) {
    if (r.age >= 6 && r.age <= 17)
        strcpy(r.ageGroup, AGE_GROUP_1);
    else if (r.age >= 18 && r.age <= 25)
        strcpy(r.ageGroup, AGE_GROUP_2);
    else if (r.age >= 26 && r.age <= 45)
        strcpy(r.ageGroup, AGE_GROUP_3);
    else if (r.age >= 46 && r.age <= 60)
        strcpy(r.ageGroup, AGE_GROUP_4);
    else
        strcpy(r.ageGroup, AGE_GROUP_5);
}