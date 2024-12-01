public class Schedule {
    private int shifts;
    private int positions;
    private String[][] out_schedule;

    public Schedule(int shifts, int positions) {
        this.shifts = shifts;
        this.positions = positions;
        out_schedule = new String[shifts][positions];
    }

    public Schedule clone() {
        Schedule clone = new Schedule(shifts, positions);
        String[][] clone_out_schedule = new String[shifts][positions];

        for(int i = 0; i < shifts; i++) {
            for(int j = 0; j < positions; j++) {
                clone_out_schedule[i][j] = out_schedule[shifts][positions];
            }
        }

        return clone;
    }
}