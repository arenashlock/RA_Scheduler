import java.util.ArrayList;

public class Staff {
    private ArrayList<RA> RA_staff;

    // -------------------- CONSTRUCTOR --------------------

    public Staff() {
        RA_staff = new ArrayList<>();
    }

    // -------------------- GETTERS --------------------

    public ArrayList<RA> RA_staff() {
        return RA_staff;
    }

    public RA get(int index) {
        return RA_staff.get(index);
    }

    // -------------------- SETTERS --------------------

    public void add_RA(RA new_RA) {
        RA_staff.add(new_RA);
    }

    public void inc_RA_hours(int index, int increase_by) {
        RA temp = RA_staff.get(index);
        int old_hours = temp.hours();
        temp.hours(old_hours + increase_by);
        RA_staff.set(index, temp);
    }

    public void dec_RA_hours(int index, int decrease_by) {
        RA temp = RA_staff.get(index);
        int old_hours = temp.hours();
        temp.hours(old_hours - decrease_by);
        RA_staff.set(index, temp);
    }
    
    public void set_RA_name(int index, String name) {
        RA temp = RA_staff.get(index);
        temp.name(name);
        RA_staff.set(index, temp);
    }

    public void set_RA_building(int index, int building) {
        RA temp = RA_staff.get(index);
        temp.building(building);
        RA_staff.set(index, temp);
    }

    public void set_RA_experience(int index, RA.Experience experience) {
        RA temp = RA_staff.get(index);
        temp.experience(experience);
        RA_staff.set(index, temp);
    }

    public void set_RA_hours(int index, int hours) {
        RA temp = RA_staff.get(index);
        temp.hours(hours);
        RA_staff.set(index, temp);
    }

    // -------------------- OTHER METHODS --------------------

    public String staff_string() {
        String staff_string = "";

        for(int i = 0; i < RA_staff.size(); i++) {
            RA curr_RA = RA_staff.get(i);

            String RA_building = Integer.toString(curr_RA.building());

            String RA_name = curr_RA.name();

            String RA_hours = Integer.toString(curr_RA.hours());

            staff_string += RA_building + ", " + RA_name + ", " + RA_hours;

            if(i < 28) {
                staff_string += "\n";
            }
        }

        return staff_string;
    }
}