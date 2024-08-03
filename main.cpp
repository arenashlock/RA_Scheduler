#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <climits>
#include <ctime>

#include "main.h"

// Array of all the Freddy RAs
RA All_RAs[NUM_FREDDY_RAS];

// Global variables containing information about the schedule to make
int SCHEDULE_TOTAL_DAYS;
int SCHEDULE_TOTAL_HOURS;

void read_staff_line(int array_index, std::string file_line) {
    int start = 0; int end = 0;

    // Get the building number of the RA
    end = file_line.find(",");
    All_RAs[array_index].RA_building_number = stoi(file_line.substr(start, (end - start)));
    start = end + 1;

    // Get the name of the RA
    end = file_line.find(",", start);
    All_RAs[array_index].RA_name = file_line.substr(start, (end - start));
    start = end + 1;

    // Get the experience of the RA (only need to check first character of last field)
    if(file_line[start] == 'R') {
        All_RAs[array_index].RA_experience = RETURNER;
    }
    else if(file_line[start] == 'T') {
        All_RAs[array_index].RA_experience = TRANSFER_OR_RFA;
    }
    else {
        All_RAs[array_index].RA_experience = NEW_STAFF;
    }
}

void read_staff_file() {
    std::fstream frederiksen_court_staff_file;
    std::string file_line;

    frederiksen_court_staff_file.open("./frederiksen_court_staff.csv", std::fstream::in);

    // File found
    if(frederiksen_court_staff_file.is_open()) {
        // Throw out the first line (just labels for data)
        std::getline(frederiksen_court_staff_file, file_line);

        for(int i = 0; i < 29; i++) {
            std::getline(frederiksen_court_staff_file, file_line);

            // Call the function to read the singular line and set some variables
            read_staff_line(i, file_line);

            // Set some variables not read from the line
            All_RAs[i].RA_hours_scheduled = 0;
            All_RAs[i].RA_max_hours = false;
        }

        frederiksen_court_staff_file.close();
    }
    
    // Cannot read file
    else {
        std::cout << "FILE NOT FOUND..." << std::endl;
    }
}

int main(int argc, char* argv[]) {
    // Read in the schedule_outline.csv file and set up the data structures and objects


    // Read the frederiksen_court_staff.csv file and build each RA object
    read_staff_file();

    // Little test to make sure the staff information is read correctly
    /* for(int i = 0; i < 29; i++) {
        std::cout << "Name: " << All_RAs[i].RA_name << std::endl <<
        "Building: " << All_RAs[i].RA_building_number << std::endl <<
        "Experience: " << All_RAs[i].RA_experience << std::endl;
    } */

    // 


    return 0;
}























/* // Information for creating the schedule
int SHIFTS = 0;
int POSITIONS = 0;
int TOTAL_HOURS = 0;
std::string SCHEDULE_HEADER;

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

void output_RA_schedule() {
    // Create (or open) file to output the schedule(s) that work
    std::ofstream schedule_file ("schedule.csv");

    // CODE...

    schedule_file.close();
}

void make_schedule() {
    std::srand(std::time(nullptr));

    for(int i = 0; i < 10; i++) {
        int chosen_RA = std::rand() % 30;
        std::cout << "Name: " << All_School_RAs[chosen_RA].RA_name << std::endl;
    }
}

void read_availability_file() {
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

/* void read_schedule_outline_file() {
    std::fstream schedule_outline_file;
    std::string schedule_outline_line;

    schedule_outline_file.open("./SAMPLE_schedule_outline.csv", std::fstream::in);

    // File found
    if(schedule_outline_file.is_open()) {
        // ------------------------------- READING LINE #1 -------------------------------

        std::getline(schedule_outline_file, schedule_outline_line);

        // Get the number of shifts (convert to an int from char)
        SHIFTS = schedule_outline_line[9] - '0';

        
            POTENTIAL BUG: If it is a double-digit number, this doesn't work. Could just read as a string and convert!
        */
        // Get the number of positions (convert to an int from char)
        /* POSITIONS = schedule_outline_line[21] - '0';

        // ------------------------------- READING LINE #2 -------------------------------

        int start_of_read = 0; int end_of_read = 0;

        std::getline(schedule_outline_file, schedule_outline_line);

        // Get the building number of the RA
        end_of_read = schedule_outline_line.find(",");
        TOTAL_HOURS = stoi(schedule_outline_line.substr(start_of_read, (end_of_read - start_of_read)));
        start_of_read = end_of_read + 1;

        // Header with day and positions in it
        SCHEDULE_HEADER = schedule_outline_line.substr(start_of_read);

        // ------------------------- READING THE REMAINING LINES -------------------------

        //while(std::getline(schedule_outline_file, schedule_outline_line)) {
            // CODE...
        //}
    }
    
    // Cannot read file
    else {
        std::cout << "READING NOT WORKING..." << std::endl;
    }
}

int main(int argc, char* argv[]) {

     read_schedule_outline_file();

    //read_availability_file();

    // Make the schedule using DFS
    //make_schedule();

    // Output the list of RAs and the amount of hours they are working
    output_RA_hours();

    return 0;
} */