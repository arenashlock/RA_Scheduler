#ifndef FILES_H
#define FILES_H

extern const int FREDDY_SCHOOL_RAS = 29;
extern const int FREDDY_SUMMER_RAS = 10;

class RA {
public:
    std::string name;
    int availability[7][10];
};

extern RA All_School_RAs[FREDDY_SCHOOL_RAS];
extern RA All_Summer_RAs[FREDDY_SUMMER_RAS];

#endif