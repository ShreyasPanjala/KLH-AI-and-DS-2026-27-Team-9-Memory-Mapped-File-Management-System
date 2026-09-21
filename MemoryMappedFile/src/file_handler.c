#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#include "../include/file_handler.h"

int open_file(const char *filename)
{
    int fd;

    fd = open(filename, O_RDWR);

    if (fd == -1)
    {
        perror("open");
        return -1;
    }

    printf("File opened successfully.\n");
    printf("File descriptor: %d\n", fd);

    return fd;
}

int get_file_size(int fd, struct stat *file_info)
{
    if (fstat(fd, file_info) == -1)
    {
        perror("fstat");
        return -1;
    }

    if (file_info->st_size == 0)
{
    printf("File is empty (zero-length file).\n");
}
else
{
    printf("File size: %ld bytes\n", file_info->st_size);
}

    return 0;
}

int close_file(int fd)
{
    if (close(fd) == -1)
    {
        perror("close");
        return -1;
    }

    printf("File closed successfully.\n");

    return 0;
}
