#include <stdio.h>

struct process {
    int id, at, bt, ct, tat, wt, remaining_bt;
};

int main() {
    int n, tq, current_time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process p[n];
    int queue[100], front = 0, rear = 0;
    int visited[100] = {0}; 

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nProcess %d\n", p[i].id);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        p[i].remaining_bt = p[i].bt;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    for(int i = 0; i < n; i++) {
        if(p[i].at <= current_time) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    while (completed != n) {
        int idx = queue[front++];
        
        int execute_time = (p[idx].remaining_bt > tq) ? tq : p[idx].remaining_bt;
        
        p[idx].remaining_bt -= execute_time;
        current_time += execute_time;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && visited[i] == 0) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if (p[idx].remaining_bt > 0) {
  
            queue[rear++] = idx;
        } else {
      
            p[idx].ct = current_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            total_wt += p[idx].wt;
            total_tat += p[idx].tat;
            completed++;
        }

        if (front == rear && completed != n) {
            for (int i = 0; i < n; i++) {
                if (visited[i] == 0) {
                    current_time = p[i].at; 
                    queue[rear++] = i;
                    visited[i] = 1;
                    break;
                }
            }
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}
