#ifndef MAIN_H
#define MAIN_H

// Number of Freddy RAs
extern const int NUM_FREDDY_RAS = 29;

// Experience values for assigning shifts
extern const int IGNORE = 6;
extern const int RETURNER = 3;
extern const int TRANSFER_OR_RFA = 2;
extern const int NEW_STAFF = 1;

// Constant to make the code more readable for if a schedule is found
extern const int SCHEDULE_FOUND = 1;

class RA {
public:
    int RA_building_number;
    std::string RA_name;
    int RA_experience;

    int RA_hours_scheduled;
    bool RA_max_hours;

    int RA_availability[7][10];
};

class DAY {
public:
    int DAY_shifts;
    int DAY_positions;
    std::string DAY_header;

    std::vector<int> DAY_shift_hours;
    std::vector<std::string> DAY_shift_timeframe;
    // The nested vector should be the experience ratings
    std::vector<std::vector<int> > DAY_shift_experience;
    // Need 2 separate 2D vectors in case backtracking is required
    std::vector<std::vector<std::string> > DAY_final_schedule;
};

class SCHEDULE {
public:
    int SCHEDULE_num_days;
    int SCHEDULE_total_hours;

    int SCHEDULE_max_hours_per_RA;

    std::vector<DAY> SCHEDULE_days;
    RA SCHEDULE_all_RAs[NUM_FREDDY_RAS];
};

#endif