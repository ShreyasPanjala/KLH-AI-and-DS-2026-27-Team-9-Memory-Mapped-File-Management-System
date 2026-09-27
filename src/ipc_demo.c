#include "ipc_demo.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

void run_ipc_demo(void)
{
    printf("\n========================================\n");
    printf("      INTER-PROCESS COMMUNICATION\n");
    printf("========================================\n");

    int pipefd[2];

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return;
    }

    printf("Communication channel created successfully\n");

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {
        /*
         * Child reads from pipe.
         */
        close(pipefd[1]);

        char buffer[100] = {0};

        ssize_t bytes_read =
            read(pipefd[0], buffer, sizeof(buffer) - 1);

        if (bytes_read == -1)
        {
            perror("read");
            close(pipefd[0]);
            exit(EXIT_FAILURE);
        }

        printf("\nChild received message:\n");
        printf("  \"%s\"\n", buffer);

        close(pipefd[0]);

        exit(EXIT_SUCCESS);
    }
    else
    {
        /*
         * Parent writes to pipe.
         */
        close(pipefd[0]);

        const char *message = "Hello from Parent through IPC";

        ssize_t bytes_written =
            write(pipefd[1], message, strlen(message) + 1);

        if (bytes_written == -1)
        {
            perror("write");
            close(pipefd[1]);
            return;
        }

        printf("\nParent sent message:\n");
        printf("  \"%s\"\n", message);

        close(pipefd[1]);

        waitpid(pid, NULL, 0);

        printf("\nIPC using anonymous pipe completed successfully.\n");
    }
}
