#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <climits>

#include "main.h"

// Array of RAs during the school year
RA All_School_RAs[FREDDY_SCHOOL_RAS];
// Array of RAs during the summer
RA All_Summer_RAs[FREDDY_SUMMER_RAS];

void TEST_print_line(std::string test_line) {
    int end_of_line = 0;

    while(!test_line.empty()) {
        // Find the substring
        end_of_line = test_line.find(",");

        // Last substring in the line
        if(end_of_line < 0) {
            end_of_line = test_line.length();
        }

        std::cout << test_line.substr(0, end_of_line) << std::endl;
        test_line.erase(0, end_of_line + 1);
    }
}

void read_availability_file() {
    std::fstream availability_file;
    std::string test;

    availability_file.open("./SAMPLE_one_person.csv", std::fstream::in);
    std::getline(availability_file, test);

    // File found
    if(availability_file.is_open()) {
        TEST_print_line(test);
    }
    
    // Cannot read file
    else {
        std::cout << "READING NOT WORKING..." << std::endl;
    }
}

void read_schedule_outline_file() {
    std::fstream schedule_outline_file;
    std::string test;

    schedule_outline_file.open("./SAMPLE_schedule_outline.csv", std::fstream::in);
    std::getline(schedule_outline_file, test);

    // File found
    if(schedule_outline_file.is_open()) {
        TEST_print_line(test);
    }
    
    // Cannot read file
    else {
        std::cout << "READING NOT WORKING..." << std::endl;
    }
}

void build_RA_objects() {
    std::fstream frederiksen_court_staff_file;
    std::string staff_member;

    frederiksen_court_staff_file.open("./frederiksen_court_staff.csv", std::fstream::in);

    // File found
    if(frederiksen_court_staff_file.is_open()) {
        // Throw out the first line (just labels for data)
        std::getline(frederiksen_court_staff_file, staff_member);

        for(int i = 0; i < 29; i++) {
            int start_of_read = 0; int end_of_read = 0;

            // Get the line with the RA's information
            std::getline(frederiksen_court_staff_file, staff_member);

            // Get the building number of the RA
            end_of_read = staff_member.find(",");
            All_School_RAs[i].RA_building_number = stoi(staff_member.substr(start_of_read, (end_of_read - start_of_read)));
            start_of_read = end_of_read + 1;

            // Get the name of the RA
            end_of_read = staff_member.find(",", start_of_read);
            All_School_RAs[i].RA_name = staff_member.substr(start_of_read, (end_of_read - start_of_read));
            start_of_read = end_of_read + 1;

            // Get the experience of the RA (only need to check first character of last field)
            if(staff_member[start_of_read] == 'R') {
                All_School_RAs[i].RA_experience = 3;
            }
            else if(staff_member[start_of_read] == 'T') {
                All_School_RAs[i].RA_experience = 2;
            }
            else {
                All_School_RAs[i].RA_experience = 1;
            }
        }
    }
    
    // Cannot read file
    else {
        std::cout << "READING NOT WORKING..." << std::endl;
    }
}

int main(int argc, char* argv[]) {
    //read_availability_file();
    
    // Build each RA object for the algorithm
    build_RA_objects();

    // Test print for ensuring information reading is correct
    for(int i = 0; i < 29; i++) {
        std::cout << "Name: " << All_School_RAs[i].RA_name << std::endl <<
        "Building: " << All_School_RAs[i].RA_building_number << std::endl <<
        "Experience: " << All_School_RAs[i].RA_experience << std::endl;
    }

    //read_schedule_outline_file();

    return 0;
}