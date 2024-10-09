#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

typedef struct {
    int id;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
} Process;

void calculateSJF(Process processes[], int n) {
    int completed = 0, currentTime = 0, minIndex;
    double totalWaitingTime = 0, totalTurnaroundTime = 0;

    printf("\nGantt Chart:\n| ");
    
    while (completed < n) {
        minIndex = -1;
        int minBurstTime = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].burstTime > 0) {
                if (processes[i].burstTime < minBurstTime) {
                    minBurstTime = processes[i].burstTime;
                    minIndex = i;
                }
            }
        }

        if (minIndex == -1) {
            currentTime++; // No process is ready, increment time
            continue;
        }

        printf("P%d | ", processes[minIndex].id);
        currentTime += processes[minIndex].burstTime;
        processes[minIndex].turnaroundTime = currentTime - processes[minIndex].arrivalTime;
        processes[minIndex].waitingTime = processes[minIndex].turnaroundTime - processes[minIndex].burstTime;
        totalWaitingTime += processes[minIndex].waitingTime;
        totalTurnaroundTime += processes[minIndex].turnaroundTime;

        processes[minIndex].burstTime = 0; // Mark the process as completed
        completed++;
    }

    printf("Idle\n");
    printf("\nProcess\tArrival Time\tBurst Time\tTurnaround Time\tWaiting Time\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrivalTime, processes[i].burstTime + processes[i].waitingTime, processes[i].turnaroundTime, processes[i].waitingTime);
    }

    printf("\nAverage Turnaround Time: %.2f", totalTurnaroundTime / n);
    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
}

int main() {
    int n;
    Process processes[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
    }

    calculateSJF(processes, n);

    return 0;
}