#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <time.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s command [arguments...]\n", argv[0]);
        return 1;
    }

    struct timespec start, end;
    struct rusage usage;
    int status;

    /* Start measuring elapsed time. */
    if (clock_gettime(CLOCK_MONOTONIC, &start) == -1) {
        perror("clock_gettime");
        return 1;
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        /* Replace the child process with the requested command. */
        execvp(argv[1], &argv[1]);

        /* Reached only if execution fails. */
        perror(argv[1]);
        _exit(127);
    }

    /* Wait for the command and collect resource usage. */
    while (wait4(pid, &status, 0, &usage) == -1) {
        if (errno == EINTR)
            continue;

        perror("wait4");
        return 1;
    }

    if (clock_gettime(CLOCK_MONOTONIC, &end) == -1) {
        perror("clock_gettime");
        return 1;
    }

    double real = (end.tv_sec - start.tv_sec)
                + (end.tv_nsec - start.tv_nsec) / 1e9;

    double user = usage.ru_utime.tv_sec
                + usage.ru_utime.tv_usec / 1e6;

    double system = usage.ru_stime.tv_sec
                  + usage.ru_stime.tv_usec / 1e6;

    printf("\n--- Execution Profile ---\n");
    printf("Command        : %s\n", argv[1]);
    printf("Process ID     : %ld\n", (long)pid);
    printf("Elapsed time   : %.6f seconds\n", real);
    printf("User CPU time  : %.6f seconds\n", user);
    printf("System CPU time: %.6f seconds\n", system);
    printf("Peak memory    : %ld KB\n", usage.ru_maxrss);

    if (WIFEXITED(status)) {
        printf("Exit status    : %d\n", WEXITSTATUS(status));
        return WEXITSTATUS(status);
    }

    if (WIFSIGNALED(status)) {
        printf("Killed by signal: %d\n", WTERMSIG(status));
        return 128 + WTERMSIG(status);
    }

    return 1;
}
