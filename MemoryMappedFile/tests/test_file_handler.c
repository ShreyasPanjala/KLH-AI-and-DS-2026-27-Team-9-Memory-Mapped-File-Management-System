#include <stdio.h>
#include <sys/stat.h>

#include "../include/file_handler.h"

int main()
{
    int fd;
    struct stat file_info;

    fd = open_file("sample.txt");

    if (fd == -1)
    {
        return 1;
    }

    if (get_file_size(fd, &file_info) == -1)
    {
        close_file(fd);
        return 1;
    }

    close_file(fd);

    return 0;
}
