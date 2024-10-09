#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

typedef struct {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
    int priority;
    int isFinished;
} Process;

void calculatePreemptivePriorityScheduling(Process processes[], int n) {
    int completed = 0, currentTime = 0;
    double totalWaitingTime = 0, totalTurnaroundTime = 0;

    printf("\nGantt Chart:\n| ");

    while (completed < n) {
        int minIndex = -1;
        int highestPriority = -1;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && !processes[i].isFinished) {
                if (processes[i].priority > highestPriority) {
                    highestPriority = processes[i].priority;
                    minIndex = i;
                }
            }
        }

        if (minIndex == -1) {
            currentTime++;
            continue;
        }

        printf("P%d | ", processes[minIndex].id);
        processes[minIndex].remainingTime--;
        currentTime++;

        if (processes[minIndex].remainingTime == 0) {
            processes[minIndex].isFinished = 1;
            completed++;
            processes[minIndex].turnaroundTime = currentTime - processes[minIndex].arrivalTime;
            processes[minIndex].waitingTime = processes[minIndex].turnaroundTime - processes[minIndex].burstTime;
            totalWaitingTime += processes[minIndex].waitingTime;
            totalTurnaroundTime += processes[minIndex].turnaroundTime;

            processes[minIndex].burstTime = rand() % 10 + 1;
            processes[minIndex].remainingTime = processes[minIndex].burstTime;
            processes[minIndex].arrivalTime = currentTime + 2;
            processes[minIndex].priority = rand() % 10;
        }
    }

    printf("Idle\n");
    printf("\nProcess\tArrival Time\tBurst Time\tPriority\tTurnaround Time\tWaiting Time\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrivalTime - 2, processes[i].burstTime, processes[i].priority, processes[i].turnaroundTime, processes[i].waitingTime);
    }

    printf("\nAverage Turnaround Time: %.2f", totalTurnaroundTime / n);
    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
}

int main() {
    srand(time(NULL));
    int n;
    Process processes[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time, initial burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrivalTime, &processes[i].burstTime, &processes[i].priority);
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].isFinished = 0;
    }

    calculatePreemptivePriorityScheduling(processes, n);
    return 0;
}