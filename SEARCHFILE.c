#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

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

void search_first_occurrence(char *filename, char *pattern) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("File open failed");
        return;
    }

    char line[256];
    int line_number = 0;

    while (fgets(line, sizeof(line), file)) {
        line_number++;
        if (strstr(line, pattern) != NULL) {
            printf("First occurrence found at line %d: %s", line_number, line);
            fclose(file);
            return;
        }
    }

    printf("Pattern not found\n");
    fclose(file);
}

void search_all_occurrences(char *filename, char *pattern) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("File open failed");
        return;
    }

    char line[256];
    int line_number = 0;
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        line_number++;
        if (strstr(line, pattern) != NULL) {
            printf("Occurrence found at line %d: %s", line_number, line);
            found = 1;
        }
    }

    if (!found) {
        printf("Pattern not found\n");
    }

    fclose(file);
}

void count_occurrences(char *filename, char *pattern) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("File open failed");
        return;
    }

    char line[256];
    int count = 0;

    while (fgets(line, sizeof(line), file)) {
        char *ptr = line;
        while ((ptr = strstr(ptr, pattern)) != NULL) {
            count++;
            ptr += strlen(pattern); // Move past the last found occurrence
        }
    }

    printf("Number of occurrences: %d\n", count);
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
        } else if (strcmp(args[0], "search") == 0) {
            if (args[3] == NULL) {
                printf("Invalid command format\n");
            } else if (strcmp(args[1], "f") == 0) {
                search_first_occurrence(args[2], args[3]);
            } else if (strcmp(args[1], "a") == 0) {
                search_all_occurrences(args[2], args[3]);
            } else if (strcmp(args[1], "c") == 0) {
                count_occurrences(args[2], args[3]);
            } else {
                printf("Unknown option for search command\n");
            }
        } else {
            execute_command(args);
        }
    }

    return 0;
}