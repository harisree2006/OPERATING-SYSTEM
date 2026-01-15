#include <stdio.h>

struct Process {
    int pid, at, bt, pr, ct, tat, wt, completed;
};

void main() {
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
        printf("Priority: ");
        scanf("%d", &p[i].pr);
        p[i].completed = 0;
    }

    printf("\nExecution Order: ");
    while (completed_count < n) {
        int idx = -1;
        int highest_priority = 1e9; // Large value for comparison

        // Find the process with the highest priority that has arrived
        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && p[i].completed == 0) {
                if (p[i].pr < highest_priority) {
                    highest_priority = p[i].pr;
                    idx = i;
                }
                // If priorities are same, use FCFS (Arrival Time)
                else if (p[i].pr == highest_priority) {
                    if (p[i].at < p[idx].at) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            printf("P%d -> ", p[idx].pid);
            current_time += p[idx].bt;
            p[idx].ct = current_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            
            total_wt += p[idx].wt;
            total_tat += p[idx].tat;
            p[idx].completed = 1;
            completed_count++;
        } else {
            // If no process has arrived, advance time
            current_time++;
        }
    }

    printf("Done\n");

    // Output Table
    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].pr, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);
}
