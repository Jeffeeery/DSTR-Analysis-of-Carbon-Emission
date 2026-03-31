// Member 1 - [BAN]
// shared/resident.h - Core data structure shared across both programs

#ifndef RESIDENT_H
#define RESIDENT_H

// Age group labels
#define AGE_GROUP_1 "Children/Teens (6-17)"
#define AGE_GROUP_2 "Young Adults (18-25)"
#define AGE_GROUP_3 "Working Adults (26-45)"
#define AGE_GROUP_4 "Middle-Aged (46-60)"
#define AGE_GROUP_5 "Seniors (61-100)"

struct Resident {
    char residentID[15];
    int age;
    char transportMode[30];
    double dailyDistance;       // km
    double emissionFactor;      // kg CO2 per km
    int avgDaysPerMonth;
    double monthlyEmission;     // computed: dailyDistance * emissionFactor * avgDaysPerMonth
    char ageGroup[35];          // assigned based on age
};

// Assign age group string based on age
// 6-17: Children/Teens, 18-25: Young Adults, 26-45: Working Adults,
// 46-60: Middle-Aged, 61-100: Seniors
void assignAgeGroup(Resident& r);

// Compute monthly carbon emission and assign age group
void computeResident(Resident& r);

#endif // RESIDENT_H
