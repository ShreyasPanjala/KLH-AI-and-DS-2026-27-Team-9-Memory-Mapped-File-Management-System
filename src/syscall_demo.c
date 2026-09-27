#include "syscall_demo.h"

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define FILE_NAME "data/syscall_test.txt"

void run_syscall_demo(void)
{
    printf("\n");
    printf("===============================================\n");
    printf("            SYSTEM CALL OPERATIONS\n");
    printf("===============================================\n");

    printf("Process ID: %d\n", getpid());

    int fd = open(FILE_NAME, O_CREAT | O_RDWR | O_TRUNC, 0644);

    if (fd == -1)
    {
        perror("open");
        return;
    }

    printf("open()  : SUCCESS\n");

    const char *message = "Hello from Linux system calls!\n";

    ssize_t written = write(fd, message, strlen(message));

    if (written == -1)
    {
        perror("write");
        close(fd);
        return;
    }

    printf("write() : SUCCESS (%zd bytes)\n", written);

    if (lseek(fd, 0, SEEK_SET) == -1)
    {
        perror("lseek");
        close(fd);
        return;
    }

    char buffer[100] = {0};

    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);

    if (bytes_read == -1)
    {
        perror("read");
        close(fd);
        return;
    }

    printf("read()  : SUCCESS\n");
    printf("Content : %s", buffer);

    if (close(fd) == -1)
    {
        perror("close");
        return;
    }

    printf("close() : SUCCESS\n");

    printf("\nSystem call operations completed successfully.\n");
}
