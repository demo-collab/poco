#include <stdio.h>

#define MAX 100

void calculateTurnaroundAndWaitingTimes(int n, int burstTime[], int arrivalTime[], int timeQuantum) {
    int waitingTime[MAX], turnaroundTime[MAX];
    int remainingBurstTime[MAX];
    int time = 0, completed = 0;
    
    for (int i = 0; i < n; i++) {
        remainingBurstTime[i] = burstTime[i];
        waitingTime[i] = 0;
    }

    printf("\nGantt Chart:\n");
    printf("| ");
    
    while (completed < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (arrivalTime[i] <= time && remainingBurstTime[i] > 0) {
                found = 1;

                if (remainingBurstTime[i] > timeQuantum) {
                    time += timeQuantum;
                    remainingBurstTime[i] -= timeQuantum;
                } else {
                    time += remainingBurstTime[i];
                    waitingTime[i] += (time - arrivalTime[i] - burstTime[i]);
                    remainingBurstTime[i] = 0;
                    completed++;
                    turnaroundTime[i] = waitingTime[i] + burstTime[i];

                    printf("%d | ", i + 1);
                }
                break;
            }
        }

        if (!found) {
            time++; // Increment time if no process is ready
        }
    }

    printf("Idle\n");
    printf("\nProcess\tBurst Time\tArrival Time\tTurnaround Time\tWaiting Time\n");

    double totalTurnaroundTime = 0, totalWaitingTime = 0;
    for (int i = 0; i < n; i++) {
        totalTurnaroundTime += turnaroundTime[i];
        totalWaitingTime += waitingTime[i];
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, burstTime[i], arrivalTime[i], turnaroundTime[i], waitingTime[i]);
    }

    printf("\nAverage Turnaround Time: %.2f", totalTurnaroundTime / n);
    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
}

int main() {
    int n, timeQuantum;
    int burstTime[MAX], arrivalTime[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    printf("Enter time quantum: ");
    scanf("%d", &timeQuantum);

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &arrivalTime[i], &burstTime[i]);
    }

    calculateTurnaroundAndWaitingTimes(n, burstTime, arrivalTime, timeQuantum);
    
    return 0;
}