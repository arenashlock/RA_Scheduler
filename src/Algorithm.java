import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Algorithm {
    public static final String STAFF_FILEPATH = "./frederiksen_court_staff.csv";
    public static final String IN_SCHEDULE_FILEPATH = "./SAMPLE_in_schedule.csv";
    public static final String OUT_SCHEDULE_FILEPATH = "./";

    public static Staff staff;

    public static void main(String[] args) {
        staff = new Staff();

        create_staff(STAFF_FILEPATH);

        System.out.println(staff.staff_string());

        // try {
        //     FileWriter test = new FileWriter(IN_SCHEDULE_FILEPATH, false);
        //     test.write("Hello");
        //     test.close();
        // } catch (IOException e) {
        //     System.err.println("Something is not right");
        // }

    }

    public static void create_staff(String staff_filepath) {
        // File that contains the staff's information
        File staffFile = new File(staff_filepath);

        // Read through the file and create RA objects
        try {
            Scanner staffScanner = new Scanner(staffFile);

            // Throw out the header line from the file
            staffScanner.nextLine();

            // Get each RA's information
            while(staffScanner.hasNextLine()) {
                // All the information
                String RA_line = staffScanner.nextLine();

                // Create another scanner for the line
                Scanner RAScanner = new Scanner(RA_line);
                // Default delimiter is " ", so change it to ","
                RAScanner.useDelimiter(",");

                // Building number of the RA
                int RA_building = RAScanner.nextInt();

                // Name of the RA
                String RA_name = RAScanner.next();

                // Experience of the RA
                RA.Experience RA_experience;
                String temp_experience = RAScanner.next();
                if(temp_experience.equals("New Staff")) {
                    RA_experience = RA.Experience.NEW_STAFF;
                } else if(temp_experience.equals("Transfer/RFA")) {
                    RA_experience = RA.Experience.TRANSFER_RFA;
                } else {
                    RA_experience = RA.Experience.RETURNER;
                }

                // Hours worked already by the RA
                int RA_hours = RAScanner.nextInt();

                RA new_RA = new RA(RA_name, RA_building, RA_experience, RA_hours);

                staff.add_RA(new_RA);

                // Close the scanner
                RAScanner.close();
            }

            // Close the scanner
            staffScanner.close();
        } catch (FileNotFoundException e) {
            System.err.println("Either the file is missing or the filepath is incorrect!");
        }
    }

    public static void interpret_schedule(String in_schedule_filepath) {

    }
}