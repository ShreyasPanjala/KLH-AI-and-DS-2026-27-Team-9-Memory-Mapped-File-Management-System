#include "process_demo.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void run_process_demo(void)
{
    printf("\n");
    printf("===============================================\n");
    printf("             PROCESS MANAGEMENT\n");
    printf("===============================================\n");

    printf("Parent PID: %d\n", getpid());
    printf("Creating child process...\n");

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {
        printf("\nChild process created.\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());

        printf("Executing child operation...\n");

        execlp(
            "echo",
            "echo",
            "Child process executed successfully.",
            (char *)NULL
        );

        perror("exec");
        exit(EXIT_FAILURE);
    }
    else
    {
        int status;

        printf("Parent is waiting for child...\n");

        if (waitpid(pid, &status, 0) == -1)
        {
            perror("waitpid");
            return;
        }

        if (WIFEXITED(status))
        {
            printf("\nChild exited with status: %d\n",
                   WEXITSTATUS(status));
        }

        printf("Parent process completed successfully.\n");
    }
}
