#ifndef FILES_H
#define FILES_H

extern const int FREDDY_SCHOOL_RAS = 29;
extern const int FREDDY_SUMMER_RAS = 10;

class RA {
public:
    int id;
    std::string name;
    int species_id;
    int height;
    int weight;
    int base_experience;
    int order;
    int is_default;
};

extern RA All_School_RAs[FREDDY_SCHOOL_RAS];
extern RA All_Summer_RAs[FREDDY_SUMMER_RAS];

#endif