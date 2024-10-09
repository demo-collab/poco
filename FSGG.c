#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        printf("Child Process: My PID is %d and my Parent PID is %d\n", getpid(), getppid());
        sleep(5);
        printf("Child Process: My PID is %d and my Parent PID is %d (after sleep)\n", getpid(), getppid());
    } else {
        printf("Parent Process: My PID is %d and I am terminating\n", getpid());
        exit(0);
    }

    return 0;
}