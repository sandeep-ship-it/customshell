#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 1024

int main() {
    char command[MAX_CMD_LEN];

    while (1) {
        printf("myshell> ");
        fflush(stdout);

        if (!fgets(command, MAX_CMD_LEN, stdin)) {
            break;
        }

        // Remove trailing newline
        command[strcspn(command, "\n")] = 0;

        if (strcmp(command, "exit") == 0) {
            break;
        }

        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            execlp("/bin/sh", "sh", "-c", command, (char *)NULL);
            perror("execlp failed");
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            // Parent process
            wait(NULL);
        } else {
            perror("fork failed");
        }
    }

    return 0;
}

