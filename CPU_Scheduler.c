#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Process {
    char id[10];
    int arrival_time, burst_time, completion_time;
    int turnaround_time, waiting_time, response_time;
};

void printGanttChart(struct Process p[], int n) {
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < n; i++) {
        printf(" %s |", p[i].id);
    }
    printf("\n0");
    for (int i = 0; i < n; i++) {
        printf(" %d", p[i].completion_time);
    }
    printf("\n");
}

void calculateAverages(struct Process p[], int n) {
    float total_tat = 0, total_wt = 0, total_rt = 0;
    for (int i = 0; i < n; i++) {
        total_tat += p[i].turnaround_time;
        total_wt += p[i].waiting_time;
        total_rt += p[i].response_time;
    }
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Response Time: %.2f\n", total_rt / n);
}

void FCFS(struct Process p[], int n) {
    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival_time) {
            time = p[i].arrival_time;
        }
        time += p[i].burst_time;
        p[i].completion_time = time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        p[i].response_time = p[i].waiting_time;
    }

    printf("\nFCFS Scheduling:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].arrival_time, p[i].burst_time,
               p[i].completion_time, p[i].turnaround_time, p[i].waiting_time, p[i].response_time);
    }

    printGanttChart(p, n);
    calculateAverages(p, n);
}

void RoundRobin(struct Process p[], int n, int quantum) {
    int time = 0, finished = 0;
    int remaining[n];

    for (int i = 0; i < n; i++) {
        remaining[i] = p[i].burst_time;
        p[i].response_time = -1;
    }

    printf("\nGantt Chart:\n|");
    while (finished < n) {
        int all_idle = 1;
        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0 && p[i].arrival_time <= time) {
                all_idle = 0;
                if (p[i].response_time == -1) {
                    p[i].response_time = time - p[i].arrival_time;
                }
                printf(" %s |", p[i].id);
                int exec_time = remaining[i] > quantum ? quantum : remaining[i];
                time += exec_time;
                remaining[i] -= exec_time;
                if (remaining[i] == 0) {
                    finished++;
                    p[i].completion_time = time;
                    p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
                    p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
                }
            }
        }
        if (all_idle) {
            time++;
        }
    }

    printf("\n0");
    for (int i = 0; i < n; i++) {
        printf(" %d", p[i].completion_time);
    }
    printf("\n");

    printf("\nRound Robin Scheduling:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].arrival_time, p[i].burst_time,
               p[i].completion_time, p[i].turnaround_time, p[i].waiting_time, p[i].response_time);
    }

    calculateAverages(p, n);
}

int main() {
    int n, choice, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    printf("Enter Process ID, Arrival Time, and Burst Time:\n");
    for (int i = 0; i < n; i++) {
        scanf("%s %d %d", p[i].id, &p[i].arrival_time, &p[i].burst_time);
    }

    while (1) {
        printf("\nCPU Scheduling Menu:\n1. FCFS\n2. Round Robin\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                FCFS(p, n);
                break;
            case 2:
                printf("Enter Time Quantum: ");
                scanf("%d", &quantum);
                RoundRobin(p, n, quantum);
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
