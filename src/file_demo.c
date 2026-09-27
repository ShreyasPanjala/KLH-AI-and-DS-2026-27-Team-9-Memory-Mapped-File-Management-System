#include "file_demo.h"

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

#define FILE_NAME "data/file_demo.txt"

void run_file_demo(void)
{
    printf("\n");
    printf("===============================================\n");
    printf("                FILE OPERATIONS\n");
    printf("===============================================\n");

    int fd = open(
        FILE_NAME,
        O_CREAT | O_RDWR | O_TRUNC,
        0644
    );

    if (fd == -1)
    {
        perror("open");
        return;
    }

    printf("open() : SUCCESS\n");
    printf("File descriptor: %d\n", fd);

    const char *text =
        "Linux file system demonstration.\n";

    if (write(fd, text, strlen(text)) == -1)
    {
        perror("write");
        close(fd);
        return;
    }

    printf("write(): SUCCESS\n");

    struct stat info;

    if (fstat(fd, &info) == -1)
    {
        perror("fstat");
        close(fd);
        return;
    }

    printf("File size: %ld bytes\n",
           (long)info.st_size);

    if (lseek(fd, 0, SEEK_SET) == -1)
    {
        perror("lseek");
        close(fd);
        return;
    }

    char buffer[100] = {0};

    if (read(fd, buffer, sizeof(buffer) - 1) == -1)
    {
        perror("read");
        close(fd);
        return;
    }

    printf("read(): SUCCESS\n");

    printf("File contents:\n");
    printf("%s", buffer);

    if (close(fd) == -1)
    {
        perror("close");
        return;
    }

    printf("close(): SUCCESS\n");

    printf("\nFile operations completed successfully.\n");
}
