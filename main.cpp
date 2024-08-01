#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <climits>
#include <ctime>

#include "main.h"

// Information for creating the schedule
int SHIFTS = 0;
int POSITIONS = 0;
int TOTAL_HOURS = 0;

// Array of RAs during the school year
RA All_School_RAs[FREDDY_SCHOOL_RAS];
// Array of RAs during the summer
RA All_Summer_RAs[FREDDY_SUMMER_RAS];

void output_RA_hours() {
    // Create (or open) file to output the schedule(s) that work
    std::ofstream schedule_file ("schedule.csv");

    // Include the list of RAs and total hours they are scheduled for the job
    schedule_file << "RA Name, Hours Scheduled" << std::endl;
    for(int i = 0; i < 29; i++) {
        schedule_file << All_School_RAs[i].RA_name << ", " << All_School_RAs[i].RA_hours_scheduled << std::endl;
    }

    schedule_file.close();
}

void make_schedule() {
    std::srand(std::time(nullptr));

    for(int i = 0; i < 10; i++) {
        int chosen_RA = std::rand() % 30;
        std::cout << "Name: " << All_School_RAs[chosen_RA].RA_name << std::endl;
    }
}

/*void read_availability_file() {
    std::fstream availability_file;
    std::string test;

    availability_file.open("./SAMPLE_one_person.csv", std::fstream::in);
    std::getline(availability_file, test);

    // File found
    if(availability_file.is_open()) {
        // ... SOMETHING ...
    }
    
    // Cannot read file
    else {
        std::cout << "READING NOT WORKING..." << std::endl;
    }
}*/

void read_schedule_outline_file() {
    std::fstream schedule_outline_file;
    std::string schedule_outline_line;

    schedule_outline_file.open("./SAMPLE_schedule_outline.csv", std::fstream::in);

    // File found
    if(schedule_outline_file.is_open()) {
        // Get first line for information
        std::getline(schedule_outline_file, schedule_outline_line);

        // Get the number of shifts (convert to an int from char)
        SHIFTS = schedule_outline_line[9] - '0';

        // Get the number of positions (convert to an int from char)
        POSITIONS = schedule_outline_line[21] - '0';




        int start_of_read = 0; int end_of_read = 0;

        // Get the second line for additional information and the header of the schedule
        std::getline(schedule_outline_file, schedule_outline_line);

        // Get the building number of the RA
        end_of_read = schedule_outline_line.find(",");
        TOTAL_HOURS = stoi(schedule_outline_line.substr(start_of_read, (end_of_read - start_of_read)));
        start_of_read = end_of_read + 1;

        std::cout << "TOTAL_HOURS = " << TOTAL_HOURS << std::endl;
        std::cout << schedule_outline_line.substr(start_of_read) << std::endl;

        //while(std::getline(schedule_outline_file, schedule_outline_line)) {
            // CODE...
        //}
    }
    
    // Cannot read file
    else {
        std::cout << "READING NOT WORKING..." << std::endl;
    }
}

void read_RA_information() {
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
                All_School_RAs[i].RA_experience = RETURNER;
            }
            else if(staff_member[start_of_read] == 'T') {
                All_School_RAs[i].RA_experience = TRANSFER_OR_RFA;
            }
            else {
                All_School_RAs[i].RA_experience = NEW_STAFF;
            }

            All_School_RAs[i].RA_hours_scheduled = 0;
            All_School_RAs[i].RA_max_hours = false;
        }

        frederiksen_court_staff_file.close();
    }
    
    // Cannot read file
    else {
        std::cout << "READING NOT WORKING..." << std::endl;
    }
}

int main(int argc, char* argv[]) {
    // Build each RA object for the algorithm
    read_RA_information();

    // Test print for ensuring information reading is correct
    /* for(int i = 0; i < 29; i++) {
        std::cout << "Name: " << All_School_RAs[i].RA_name << std::endl <<
        "Building: " << All_School_RAs[i].RA_building_number << std::endl <<
        "Experience: " << All_School_RAs[i].RA_experience << std::endl;
    } */

    read_schedule_outline_file();

    //read_availability_file();

    // Make the schedule using DFS
    //make_schedule();

    // Output the list of RAs and the amount of hours they are working
    output_RA_hours();

    return 0;
}