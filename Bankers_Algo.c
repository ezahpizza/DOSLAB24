#include <stdio.h>
#include <stdbool.h>

#define MAX_P 100
#define MAX_R 100

void calculateNeed(int need[MAX_P][MAX_R], int max[MAX_P][MAX_R], int allot[MAX_P][MAX_R], int p, int r) {
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }
}

void printNeedMatrix(int need[MAX_P][MAX_R], int p, int r) {
    printf("\nNeed Matrix:\n");
    printf("    ");
    for (int j = 0; j < r; j++) {
        printf("R%d ", j);
    }
    printf("\n");
    for (int i = 0; i < p; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < r; j++) {
            printf("%d  ", need[i][j]);
        }
        printf("\n");
    }
}

bool isSafe(int processes[], int avail[], int max[][MAX_R], int allot[][MAX_R], int p, int r) {
    int need[MAX_P][MAX_R];
    calculateNeed(need, max, allot, p, r);

    printNeedMatrix(need, p, r);

    bool finished[MAX_P] = {false};
    int safeSequence[MAX_P];
    int work[MAX_R];

    for (int i = 0; i < r; i++) {
        work[i] = avail[i];
    }

    int count = 0;

    while (count < p) {
        bool found = false;

        for (int i = 0; i < p; i++) {
            if (!finished[i]) {
                bool canAllocate = true;

                for (int j = 0; j < r; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    for (int j = 0; j < r; j++) {
                        work[j] += allot[i][j];
                    }

                    safeSequence[count++] = processes[i];
                    finished[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("System is not in a safe state.\n");
            return false;
        }
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < p; i++) {
        printf("%d ", safeSequence[i]);
    }
    printf("\n");

    return true;
}

int main() {
    int p, r;

    printf("Enter the number of processes: ");
    scanf("%d", &p);

    printf("Enter the number of resources: ");
    scanf("%d", &r);

    int processes[MAX_P];
    int avail[MAX_R];
    int max[MAX_P][MAX_R];
    int allot[MAX_P][MAX_R];

    printf("Enter process IDs: \n");
    for (int i = 0; i < p; i++) {
        printf("Process P%d ID: ", i);
        scanf("%d", &processes[i]);
    }

    printf("Enter the available resources: \n");
    for (int i = 0; i < r; i++) {
        printf("Available instances of Resource R%d: ", i);
        scanf("%d", &avail[i]);
    }

    printf("Enter the maximum resource matrix: \n");
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            printf("Max of Process P%d for Resource R%d: ", i, j);
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the allocation matrix: \n");
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < r; j++) {
            printf("Allocation of Process P%d for Resource R%d: ", i, j);
            scanf("%d", &allot[i][j]);
        }
    }

    isSafe(processes, avail, max, allot, p, r);

    return 0;
}
