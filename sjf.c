#include <stdio.h>

struct Process {
    int pid, at, bt, ct, tat, wt, completed;
};

int main() {
    int n, current_time = 0, completed_count = 0;
    float total_wt = 0, total_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nProcess %d\n", p[i].pid);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        p[i].completed = 0;
    }

    while (completed_count < n) {
        int idx = -1;
        int min_bt = 1e9; // Large value to find the minimum

        // Look for the process with the shortest burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && p[i].completed == 0) {
                if (p[i].bt < min_bt) {
                    min_bt = p[i].bt;
                    idx = i;
                }
                // If burst times are equal, pick the one that arrived first (FCFS)
                else if (p[i].bt == min_bt) {
                    if (p[i].at < p[idx].at) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            // Found a process to run
            current_time += p[idx].bt;
            p[idx].ct = current_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            total_wt += p[idx].wt;
            total_tat += p[idx].tat;
            p[idx].completed = 1;
            completed_count++;
        } else {
            // No process has arrived yet, move time forward
            current_time++;
        }
    }

    // Output table
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}
