#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter the number of integers: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    bubbleSort(arr, n);

    char *args[n + 2];
    for (int i = 0; i < n; i++) {
        args[i] = malloc(12 * sizeof(char));
        sprintf(args[i], "%d", arr[i]);
    }
    args[n] = malloc(12 * sizeof(char));
    printf("Enter the item to search: ");
    scanf("%d", args[n]);
    args[n + 1] = NULL;

    char *programPath = "./binary_search"; 

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        execve(programPath, args, NULL);
        perror("execve failed");
        exit(1);
    } else {
        wait(NULL);
        for (int i = 0; i < n; i++) {
            free(args[i]);
        }
        free(args[n]);
    }

    return 0;
}