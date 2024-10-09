#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("I am Child Process. My PID is %d\n", getpid());
    } else {
        // Parent process
        printf("I am Parent Process. My PID is %d and my Child PID is %d\n", getpid(), pid);
    }

    return 0;
}