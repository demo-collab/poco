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

void count_characters(char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("File open failed");
        return;
    }

    int count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        count++;
    }

    fclose(file);
    printf("Number of characters: %d\n", count);
}

void count_words(char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("File open failed");
        return;
    }

    int count = 0;
    char ch;
    char prev = ' ';
    while ((ch = fgetc(file)) != EOF) {
        if ((ch == ' ' || ch == '\n' || ch == '\t') && (prev != ' ' && prev != '\n' && prev != '\t')) {
            count++;
        }
        prev = ch;
    }

    if (prev != ' ' && prev != '\n' && prev != '\t') {
        count++;  // To account for the last word if it wasn't followed by whitespace
    }

    fclose(file);
    printf("Number of words: %d\n", count);
}

void count_lines(char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("File open failed");
        return;
    }

    int count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            count++;
        }
    }

    fclose(file);
    printf("Number of lines: %d\n", count);
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
        } else if (strcmp(args[0], "count") == 0) {
            if (args[2] == NULL) {
                printf("Invalid command format\n");
            } else if (strcmp(args[1], "c") == 0) {
                count_characters(args[2]);
            } else if (strcmp(args[1], "w") == 0) {
                count_words(args[2]);
            } else if (strcmp(args[1], "1") == 0) {
                count_lines(args[2]);
            } else {
                printf("Unknown option for count command\n");
            }
        } else {
            execute_command(args);
        }
    }

    return 0;
}