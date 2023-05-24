#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
    int pipefd[2];
    pid_t pid;
    int commands[][3] = {
        {STDIN_FILENO, STDOUT_FILENO, 0},      // cat file3.txt
        {0, STDOUT_FILENO, 1},                  // grep "hello"
        {STDIN_FILENO, STDOUT_FILENO, 2}       // tee file4.txt
    };

    // Create the pipes
    for (int i = 0; i < 2; i++) {
        if (pipe(pipefd) == -1) {
            perror("pipe");
            return 1;
        }

        // Fork a child process
        if ((pid = fork()) == -1) {
            perror("fork");
            return 1;
        } else if (pid == 0) {
            // Child process

            // Close unused pipe ends
            close(pipefd[commands[i][2]]);

            // Redirect input/output
            dup2(pipefd[commands[i][0]], commands[i][0]);
            dup2(pipefd[commands[i][1]], commands[i][1]);

            // Execute the command
            if (i == 0) {
                execlp("cat", "cat", "file3.txt", NULL);
            } else if (i == 1) {
                execlp("grep", "grep", "hello", NULL);
            } else if (i == 2) {
                int fd = open("file4.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
                if (fd == -1) {
                    perror("open");
                    return 1;
                }
                dup2(fd, STDOUT_FILENO);
                execlp("tee", "tee", NULL);
            }
            perror("execlp");
            return 1;
        }

        // Close unused pipe ends in the parent process
        close(pipefd[commands[i][0]]);
        close(pipefd[commands[i][1]]);
    }

    // Wait for all child processes to finish
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    return 0;
}