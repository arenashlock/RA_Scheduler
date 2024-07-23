#ifndef FILES_H
#define FILES_H

// Cout of RAs during different times in the year
extern const int FREDDY_SCHOOL_RAS = 29;
extern const int FREDDY_SUMMER_RAS = 10;

// Experience values for assigning shifts
extern const int RETURNER = 3;
extern const int TRANSFER_OR_RFA = 2;
extern const int NEW_STAFF = 1;

class RA {
public:
    int RA_building_number;
    std::string RA_name;
    int RA_experience;
    int RA_availability[7][10];
};

extern RA All_School_RAs[FREDDY_SCHOOL_RAS];
extern RA All_Summer_RAs[FREDDY_SUMMER_RAS];

#endif