#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <climits>
#include <ctime>
#include <vector>

#include "main.h"

// Global schedule variable (that essentially everything runs through)
SCHEDULE Final_Schedule;

void read_staff_line(int array_index, std::string file_line) {
    int start = 0; int end = 0;

    // Get the building number of the RA
    end = file_line.find(",");
    Final_Schedule.SCHEDULE_all_RAs[array_index].RA_building_number = stoi(file_line.substr(start, (end - start)));
    start = end + 1;

    // Get the name of the RA
    end = file_line.find(",", start);
    Final_Schedule.SCHEDULE_all_RAs[array_index].RA_name = file_line.substr(start, (end - start));
    start = end + 1;

    // Get the experience of the RA (only need to check first character of last field)
    if(file_line[start] == 'R') {
        Final_Schedule.SCHEDULE_all_RAs[array_index].RA_experience = RETURNER;
    }
    else if(file_line[start] == 'T') {
        Final_Schedule.SCHEDULE_all_RAs[array_index].RA_experience = TRANSFER_OR_RFA;
    }
    else {
        Final_Schedule.SCHEDULE_all_RAs[array_index].RA_experience = NEW_STAFF;
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
            Final_Schedule.SCHEDULE_all_RAs[i].RA_hours_scheduled = 0;
            Final_Schedule.SCHEDULE_all_RAs[i].RA_max_hours = false;
        }

        frederiksen_court_staff_file.close();
    }
    
    // Cannot read file
    else {
        std::cout << "FILE NOT FOUND..." << std::endl;
    }
}

void read_schedule_outline_ALGORITHM_INFORMATION(int day, int vector_index, std::string file_line) {
    // Variables for reading the line
    int start; int end;

    // Get the length of the shift
    Final_Schedule.SCHEDULE_days[day].DAY_shift_hours.push_back((int) file_line[0] - '0');

    // Get the timeframe of the shift
    start = 2; end = file_line.find(",", start);
    Final_Schedule.SCHEDULE_days[day].DAY_shift_timeframe.push_back(file_line.substr(start, (end - start)));
                    
    // Make a vector for the experience of each position in the shift
    std::vector<int> experience_vector;

    // Get the experience necessary for the shift
    for(int i = 0; i < Final_Schedule.SCHEDULE_days[day].DAY_positions; i++) {
        start = end + 1; end = file_line.find(",", start);

        // Get the string stating what the experience should be
        std::string experience = file_line.substr(start, (end - start));

        // Parse the experience string
        if(experience[0] == 'R') {
            experience_vector.push_back(RETURNER);
        }
        else if(experience[0] == 'T') {
            experience_vector.push_back(TRANSFER_OR_RFA);
        }
        else if(experience[0] == 'N'){
            experience_vector.push_back(NEW_STAFF);
        }
        else {
            experience_vector.push_back(IGNORE);
        }
    }

    // Update the shift's vector to the newly created one from the file
    Final_Schedule.SCHEDULE_days[day].DAY_shift_experience.push_back(experience_vector);
}

void read_schedule_outline_DAY_INFORMATION(std::string file_line) {
    // Create a new DAY object
    DAY new_day;

    // Variables for reading the line
    int start; int end;

    // Get the number of shifts
    start = 8; end = file_line.find(",", start);
    new_day.DAY_shifts = stoi(file_line.substr(start, (end - start)));
                    
    // Get the number of positions
    start = end + 11; end = file_line.find(",", start);
    new_day.DAY_positions = stoi(file_line.substr(start, (end - start)));

    // Add the day to the Final_Schedule object
    Final_Schedule.SCHEDULE_days.push_back(new_day);
}

void read_schedule_outline_SCHEDULE_INFORMATION(std::string file_line) {
    // Variables for reading the line
    int start; int end;

    // Get the number of days
    start = 6; end = file_line.find(",", start);
    Final_Schedule.SCHEDULE_num_days = stoi(file_line.substr(start, (end - start)));
        
    // Get the total number of hours
    start = end + 13; end = file_line.find(",", start);
    Final_Schedule.SCHEDULE_total_hours = stoi(file_line.substr(start, (end - start)));
}

void read_schedule_outline_file() {
    std::fstream schedule_outline_file;
    std::string file_line;

    schedule_outline_file.open("./SAMPLE_schedule_outline.csv", std::fstream::in);

    // File found
    if(schedule_outline_file.is_open()) {
        // Get the information for SCHEDULE
        std::getline(schedule_outline_file, file_line);

        // Call the funtion to derive the information for the schedule
        read_schedule_outline_SCHEDULE_INFORMATION(file_line);

        // Keep count of the days for accessing the correct vector entry
        int day = 0;

        // Boolean to know if it is the header of the day
        bool header = false;

        // Start reading the information for the days in the schedule
        while(std::getline(schedule_outline_file, file_line)) {
            // Either a blank line in the sheet or information about the day
            if(file_line[0] == ',') {
                if(file_line[1] == 'S') {
                    // Call the funtion to derive the information for the schedule
                    read_schedule_outline_DAY_INFORMATION(file_line);

                    // Going to be looking at the header next
                    header = true;
                }
            }

            // Part of the schedule
            else {
                if(header == true) {
                    int start = file_line.find(',') + 1;
                    Final_Schedule.SCHEDULE_days[day].DAY_header = file_line.substr(start);

                    // Moving onto reading the hours and experience necessary for each shift
                    header = false;
                }

                else {
                    // Create a temporary variable to make for loop more readable
                    int day_shifts = Final_Schedule.SCHEDULE_days[day].DAY_shifts;

                    for(int i = 0; i < day_shifts; i++) {
                        if(i == 0) {
                            // SKIP THE GETLINE (since we got it during the while loop)
                        }

                        else {
                            std::getline(schedule_outline_file, file_line);
                        }

                        // Run the function to derive the shift hours and experience necessary
                        read_schedule_outline_ALGORITHM_INFORMATION(day, i, file_line);
                    }

                    // Done reading information for this day
                    day++;
                }
            }
        }

        schedule_outline_file.close();
    }
    
    // Cannot read file
    else {
        std::cout << "FILE NOT FOUND..." << std::endl;
    }
}

int main(int argc, char* argv[]) {
    // Variable to check if a schedule was found or not
    int schedule_result = 0;

    // Read in the schedule_outline.csv file and set up the data structures and objects
    read_schedule_outline_file();

        // TEST: To make sure the schedule's information is read correctly
        /* std::cout << "Number of days: " << Final_Schedule.SCHEDULE_num_days << ", Total hours: " << Final_Schedule.SCHEDULE_total_hours << std::endl;
        for(int i = 0; i < Final_Schedule.SCHEDULE_num_days; i++) {
            DAY test_day = Final_Schedule.SCHEDULE_days[i];
            std::cout << "\nDay #" << i << ", Number of shifts: " << test_day.DAY_shifts << ", Number of positions: " << test_day.DAY_positions << std::endl <<
            "Header: " << test_day.DAY_header << std::endl;
            for(int j = 0; j < test_day.DAY_shifts; j++) {
                std::cout << "Length of shift: " << test_day.DAY_shift_hours[j] << ", Timeframe: " << test_day.DAY_shift_timeframe[j];
                for(int k = 0; k < test_day.DAY_positions; k++) {
                    std::cout << " " << test_day.DAY_shift_experience[j][k];
                }
                std::cout << std::endl;
            }
        } */

    // Read the frederiksen_court_staff.csv file and build each RA object
    read_staff_file();

        // TEST: To make sure the staff's information is read correctly
        /* for(int l = 0; l < 29; l++) {
            std::cout << "Name: " << Final_Schedule.SCHEDULE_all_RAs[l].RA_name << std::endl <<
            "Building: " << Final_Schedule.SCHEDULE_all_RAs[l].RA_building_number << std::endl <<
            "Experience: " << Final_Schedule.SCHEDULE_all_RAs[l].RA_experience << std::endl;
        } */

    // Run algorithm to find a functional schedule
    // schedule_result = ?

    // Output to the schedule.csv file
    if(schedule_result == SCHEDULE_FOUND) {
        // OUTPUT
    }
    else {
        std::cout << "Schedule not found..." << std::endl;
    }

    // SPACE TO TEST STUFF BEFORE WRITING CODE
    

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