#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <errno.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        int current_nice = nice(5);
        if (current_nice == -1 && errno != 0) {
            perror("Failed to change nice value in child");
            exit(1);
        }
        printf("Child Process: My PID is %d, Nice value is %d\n", getpid(), current_nice);
    } else {
        printf("Parent Process: My PID is %d, Child PID is %d\n", getpid(), pid);
    }

    return 0;
}