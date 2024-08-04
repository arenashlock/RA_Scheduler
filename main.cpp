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

void output_schedule_to_file() {
    // Create (or open) file to output the schedule that works
    std::ofstream schedule_file ("schedule.csv");

    for(int i = 0; i < Final_Schedule.SCHEDULE_num_days; i++) {
        // Output the header for the day prior to the schedule
        schedule_file << Final_Schedule.SCHEDULE_days[i].DAY_header << std::endl;

        // Output the actual schedule
        for(int j = 0; j < Final_Schedule.SCHEDULE_days[i].DAY_shifts; j++) {
            // Get the timeframe for the shift
            schedule_file << Final_Schedule.SCHEDULE_days[i].DAY_shift_timeframe[j] << ",";

            // Get the shift lineup
            for(int k = 0; k < Final_Schedule.SCHEDULE_days[i].DAY_positions; k++) {
                schedule_file << Final_Schedule.SCHEDULE_days[i].DAY_final_schedule[j][k] << ",";
            }
            
            schedule_file << std::endl;
        }
    }

    // Include the list of RAs and total hours they are scheduled for the job
    schedule_file << ",\nRA Name,Hours Scheduled" << std::endl;
    for(int i = 0; i < 29; i++) {
        schedule_file << Final_Schedule.SCHEDULE_all_RAs[i].RA_name << "," << Final_Schedule.SCHEDULE_all_RAs[i].RA_hours_scheduled << std::endl;
    }

    schedule_file.close();
}

int find_schedule() {
    std::srand(std::time(nullptr));

    for(int i = 0; i < Final_Schedule.SCHEDULE_num_days; i++) {
        for(int j = 0; j < Final_Schedule.SCHEDULE_days[i].DAY_shifts; j++) {
            std::vector<std::string> shift_lineup;
            for(int k = 0; k < Final_Schedule.SCHEDULE_days[i].DAY_positions; k++) {
                if(Final_Schedule.SCHEDULE_days[i].DAY_shift_experience[j][k] < 6) {
                    int chosen_RA = std::rand() % NUM_FREDDY_RAS;
                    while(Final_Schedule.SCHEDULE_all_RAs[chosen_RA].RA_max_hours) {
                        chosen_RA = std::rand() % NUM_FREDDY_RAS;
                    }
                    std::string chosen_RA_name = Final_Schedule.SCHEDULE_all_RAs[chosen_RA].RA_name;
                    shift_lineup.push_back(chosen_RA_name);
                    Final_Schedule.SCHEDULE_all_RAs[chosen_RA].RA_hours_scheduled += Final_Schedule.SCHEDULE_days[i].DAY_shift_hours[j];
                    if(Final_Schedule.SCHEDULE_all_RAs[chosen_RA].RA_hours_scheduled == Final_Schedule.SCHEDULE_max_hours_per_RA ||
                    Final_Schedule.SCHEDULE_all_RAs[chosen_RA].RA_hours_scheduled == (Final_Schedule.SCHEDULE_max_hours_per_RA + 1)) {
                        Final_Schedule.SCHEDULE_all_RAs[chosen_RA].RA_max_hours = true;
                    }
                }
                else {
                    shift_lineup.push_back("N/A");
                }
            }
            Final_Schedule.SCHEDULE_days[i].DAY_final_schedule.push_back(shift_lineup);
        }
    }

    return SCHEDULE_FOUND;
}

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

    // Get the experience of the RA (only need to check first character)
    if(file_line[start] == 'R') {
        Final_Schedule.SCHEDULE_all_RAs[array_index].RA_experience = RETURNER;
    }
    else if(file_line[start] == 'T') {
        Final_Schedule.SCHEDULE_all_RAs[array_index].RA_experience = TRANSFER_OR_RFA;
    }
    else {
        Final_Schedule.SCHEDULE_all_RAs[array_index].RA_experience = NEW_STAFF;
    }
    end = file_line.find(",", start); start = end + 1;

    // Get the number of hours already worked
    Final_Schedule.SCHEDULE_all_RAs[array_index].RA_hours_scheduled = stoi(file_line.substr(start));

    // Set the boolean for working max hours by checking how many hours they have already worked
    if(Final_Schedule.SCHEDULE_all_RAs[array_index].RA_hours_scheduled == Final_Schedule.SCHEDULE_max_hours_per_RA ||
    Final_Schedule.SCHEDULE_all_RAs[array_index].RA_hours_scheduled == (Final_Schedule.SCHEDULE_max_hours_per_RA + 1)) {
        Final_Schedule.SCHEDULE_all_RAs[array_index].RA_max_hours = true;
    }
    else {
        Final_Schedule.SCHEDULE_all_RAs[array_index].RA_max_hours = false;
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

    // Find the max number of hours each RA can work (for a balanced schedule)
    Final_Schedule.SCHEDULE_max_hours_per_RA = Final_Schedule.SCHEDULE_total_hours / NUM_FREDDY_RAS;
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
         for(int l = 0; l < NUM_FREDDY_RAS; l++) {
            std::cout << "Name: " << Final_Schedule.SCHEDULE_all_RAs[l].RA_name << std::endl <<
            "Building: " << Final_Schedule.SCHEDULE_all_RAs[l].RA_building_number << std::endl <<
            "Experience: " << Final_Schedule.SCHEDULE_all_RAs[l].RA_experience << std::endl <<
            "Hours Worked: " << Final_Schedule.SCHEDULE_all_RAs[l].RA_hours_scheduled << std::endl;
        } 

    // Run algorithm to find a functional schedule
    schedule_result = find_schedule();

    // Output to the schedule.csv file
    if(schedule_result == SCHEDULE_FOUND) {
        output_schedule_to_file();
    }
    
    // Algorithm couldn't find a schedule (currently just fail, but implement rollback in the future)
    else {
        std::cout << "Schedule not found..." << std::endl;
    }

    std::cout << "Max hours = " << Final_Schedule.SCHEDULE_max_hours_per_RA << std::endl;

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
        int chosen_RA = std::rand() % 29;
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