
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>

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

void list_files(char *dirname) {
    struct dirent *de;
    DIR *dr = opendir(dirname);

    if (dr == NULL) {
        perror("Could not open directory");
        return;
    }

    while ((de = readdir(dr)) != NULL) {
        printf("%s\n", de->d_name);
    }

    closedir(dr);
}

void count_entries(char *dirname) {
    struct dirent *de;
    DIR *dr = opendir(dirname);
    int count = 0;

    if (dr == NULL) {
        perror("Could not open directory");
        return;
    }

    while ((de = readdir(dr)) != NULL) {
        count++;
    }

    printf("Total entries: %d\n", count);
    closedir(dr);
}

void list_inodes(char *dirname) {
    struct dirent *de;
    struct stat filestat;
    DIR *dr = opendir(dirname);
    char filepath[512];

    if (dr == NULL) {
        perror("Could not open directory");
        return;
    }

    while ((de = readdir(dr)) != NULL) {
        snprintf(filepath, sizeof(filepath), "%s/%s", dirname, de->d_name);
        if (stat(filepath, &filestat) == 0) {
            printf("Filename: %s, Inode: %lu\n", de->d_name, filestat.st_ino);
        }
    }

    closedir(dr);
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
        } else if (strcmp(args[0], "list") == 0) {
            if (args[2] == NULL) {
                printf("Invalid command format\n");
            } else if (strcmp(args[1], "f") == 0) {
                list_files(args[2]);
            } else if (strcmp(args[1], "n") == 0) {
                count_entries(args[2]);
            } else if (strcmp(args[1], "i") == 0) {
                list_inodes(args[2]);
            } else {
                printf("Unknown option for list command\n");
            }
        } else {
            execute_command(args);
        }
    }

    return 0;
}