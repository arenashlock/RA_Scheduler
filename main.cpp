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

void TEST_assign_availability() {
    All_School_RAs[0].availability[0][0] = 1;
    std::cout << All_School_RAs[0].availability[0][0] << std::endl;
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

int main(int argc, char* argv[]) {
    //read_availability_file();
    read_schedule_outline_file();

    return 0;
}