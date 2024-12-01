import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Algorithm {
    public static void main(String[] args) {
        read_staff_file();
    }

    public static void read_staff_file() {
        File staffFile = new File("./frederiksen_court_staff.csv");

        try {
            Scanner staffScanner = new Scanner(staffFile);

            while(staffScanner.hasNextLine()) {
                System.err.println(staffScanner.nextLine());
            }
        } catch (FileNotFoundException e) {
            System.err.println("Either the file is missing or the filepath is incorrect!");
        }
    }
}