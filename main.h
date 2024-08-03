#ifndef FILES_H
#define FILES_H

// Number of Freddy RAs
extern const int NUM_FREDDY_RAS = 29;

// Experience values for assigning shifts
extern const int RETURNER = 3;
extern const int TRANSFER_OR_RFA = 2;
extern const int NEW_STAFF = 1;



class RA {
public:
    int RA_building_number;
    std::string RA_name;
    int RA_experience;

    int RA_hours_scheduled;
    bool RA_max_hours;

    int RA_availability[7][10];
};

extern RA All_RAs[NUM_FREDDY_RAS];

#endif