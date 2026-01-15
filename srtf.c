#include <stdio.h>
#include <limits.h>

int main() {
    int n, i, time = 0, completed = 0;
    int minRemaining, shortest = -1;
    int finishTime;
    float totalWT = 0, totalTAT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], rt[n], wt[n], tat[n];
    int isCompleted[n];

    for (i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];   
        isCompleted[i] = 0;
    }

    while (completed != n) {
        minRemaining = INT_MAX;
        shortest = -1;

        for (i = 0; i < n; i++) {
            if (at[i] <= time && !isCompleted[i] && rt[i] < minRemaining && rt[i] > 0) {
                minRemaining = rt[i];
                shortest = i;
            }
        }

        if (shortest == -1) {
            time++;
            continue;
        }

        rt[shortest]--;
        time++;

        if (rt[shortest] == 0) {
            finishTime = time;
            isCompleted[shortest] = 1;
            completed++;

            tat[shortest] = finishTime - at[shortest];
            wt[shortest] = tat[shortest] - bt[shortest];

            totalWT += wt[shortest];
            totalTAT += tat[shortest];
        }
    }

    printf("\nProcess\tAT\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f", totalWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", totalTAT / n);

    return 0;
}
