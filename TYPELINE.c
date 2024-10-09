#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_CMD_LEN 100
#define MAX_ARGS 10

void execute_command(char *args[]) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        if (execvp(args[0], args) < 0) {
            perror("Execution failed");
            exit(1);
        }
    } else {
        wait(NULL);
    }
}

void typeline(char *option, int n, char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("File open failed");
        return;
    }

    char line[256];
    int count = 0;

    if (strcmp(option, "a") == 0) {
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
    } else if (option[0] == '-') {
        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        fseek(file, 0, SEEK_SET);

        while (fgets(line, sizeof(line), file)) {
            count++;
        }

        fseek(file, 0, SEEK_SET);
        for (int i = 0; i < count - n; i++) {
            fgets(line, sizeof(line), file);
        }

        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
    } else {
        while (fgets(line, sizeof(line), file)) {
            if (++count > n) break;
            printf("%s", line);
        }
    }

    fclose(file);
}

int main() {
    char command[MAX_CMD_LEN];
    char *args[MAX_ARGS];
    char *token;

    while (1) {
        printf("myshell$ ");
        fgets(command, MAX_CMD_LEN, stdin);
        command[strcspn(command, "\n")] = '\0';  // Remove trailing newline

        int i = 0;
        token = strtok(command, " ");
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (strcmp(args[0], "exit") == 0) {
            break;
        } else if (strcmp(args[0], "typeline") == 0) {
            if (args[2] == NULL) {
                printf("Invalid command format\n");
            } else if (strcmp(args[1], "a") == 0) {
                typeline("a", 0, args[2]);
            } else if (args[1][0] == '-') {
                int n = atoi(&args[1][1]);
                typeline("-", n, args[2]);
            } else {
                int n = atoi(args[1]);
                typeline("", n, args[2]);
            }
        } else {
            execute_command(args);
        }
    }

    return 0;
}