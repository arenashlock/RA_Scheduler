public class RA {
    enum Experience {
        NEW_STAFF,
        TRANSFER_RFA,
        RETURNER
    }

    private String name;
    private int building;
    private int experience;
    private int hours;

    // -------------------- CONSTRUCTORS --------------------

    // General constructor for most situations
    public RA(String name, int building, int experience) {
        this.name = name;
        this.building = building;
        this.experience = experience;
        hours = 0;
    }

    // In case there needs to be functionality for RAs with hours already worked
    public RA(String name, int building, int experience, int hours) {
        this.name = name;
        this.building = building;
        this.experience = experience;
        this.hours = hours;
    }

    // -------------------- GETTERS --------------------

    public void name(String name) {
        this.name = name;
    }

    public void building(int building) {
        this.building = building;
    }

    public void experience(int experience) {
        this.experience = experience;
    }

    public void hours(int hours) {
        this.hours = hours;
    }

    // -------------------- SETTERS --------------------

    public String name() {
        return name;
    }

    public int building() {
        return building;
    }

    public int experience() {
        return experience;
    }

    public int hours() {
        return hours;
    }
}