#include "vm_demo.h"

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdlib.h>

#define TEST_FILE "data/test.txt"

void run_vm_demo(void)
{
    printf("\n========================================\n");
    printf("           MEMORY MAPPING\n");
    printf("========================================\n");

    long page_size = sysconf(_SC_PAGESIZE);

    if (page_size == -1)
    {
        perror("sysconf");
        return;
    }

    printf("System page size: %ld bytes\n", page_size);

    int fd = open(TEST_FILE, O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        return;
    }

    struct stat file_info;

    if (fstat(fd, &file_info) == -1)
    {
        perror("fstat");
        close(fd);
        return;
    }

    if (file_info.st_size == 0)
    {
        printf("File is empty.\n");
        close(fd);
        return;
    }

    printf("File size: %ld bytes\n", (long)file_info.st_size);

    void *mapped =
        mmap(NULL,
             file_info.st_size,
             PROT_READ,
             MAP_PRIVATE,
             fd,
             0);

    if (mapped == MAP_FAILED)
    {
        perror("mmap");
        close(fd);
        return;
    }

    printf("mmap() mapping: SUCCESS\n");
    printf("Mapped address: %p\n", mapped);

    printf("\nData through virtual memory:\n");
    printf("----------------------------------------\n");
    write(STDOUT_FILENO, mapped, file_info.st_size);
    printf("\n----------------------------------------\n");

    if (munmap(mapped, file_info.st_size) == -1)
    {
        perror("munmap");
        close(fd);
        return;
    }

    printf("munmap() : SUCCESS\n");

    close(fd);

    printf("\n memory mapping operation completed.\n");
}
