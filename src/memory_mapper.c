#include "memory_mapper.h"

#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int map_file(const char *filename, int protection, MappedFile *mapped_file)
{
    struct stat file_info;

    if (filename == NULL || mapped_file == NULL) {
        fprintf(stderr, "Invalid argument to map_file()\n");
        return -1;
    }

    mapped_file->fd = -1;
    mapped_file->size = 0;
    mapped_file->address = MAP_FAILED;

    /*
     * Open the file for reading and writing.
     * O_RDWR is required when the mapping may be writable.
     */
    mapped_file->fd = open(filename, O_RDWR);

    if (mapped_file->fd == -1) {
        perror("open");
        return -1;
    }

    /*
     * Obtain the size of the file.
     */
    if (fstat(mapped_file->fd, &file_info) == -1) {
        perror("fstat");
        close(mapped_file->fd);
        mapped_file->fd = -1;
        return -1;
    }

    mapped_file->size = (size_t)file_info.st_size;

    if (mapped_file->size == 0) {
        fprintf(stderr, "Cannot map an empty file\n");
        close(mapped_file->fd);
        mapped_file->fd = -1;
        mapped_file->size = 0;
        return -1;
    }

    /*
     * Create a shared memory mapping.
     *
     * MAP_SHARED means changes made to the mapped region
     * can be synchronized with the underlying file.
     */
    mapped_file->address = mmap(
        NULL,
        mapped_file->size,
        protection,
        MAP_SHARED,
        mapped_file->fd,
        0
    );

    if (mapped_file->address == MAP_FAILED) {
        perror("mmap");
        close(mapped_file->fd);

        mapped_file->fd = -1;
        mapped_file->size = 0;
        mapped_file->address = MAP_FAILED;

        return -1;
    }

    return 0;
}

int sync_file(MappedFile *mapped_file)
{
    if (mapped_file == NULL ||
        mapped_file->address == MAP_FAILED ||
        mapped_file->size == 0) {
        fprintf(stderr, "Invalid mapped file in sync_file()\n");
        return -1;
    }

    /*
     * MS_SYNC waits for synchronization to complete.
     */
    if (msync(
            mapped_file->address,
            mapped_file->size,
            MS_SYNC) == -1) {
        perror("msync");
        return -1;
    }

    return 0;
}

int unmap_file(MappedFile *mapped_file)
{
    if (mapped_file == NULL) {
        fprintf(stderr, "Invalid mapped file in unmap_file()\n");
        return -1;
    }

    if (mapped_file->address != MAP_FAILED &&
        mapped_file->size > 0) {

        if (munmap(
                mapped_file->address,
                mapped_file->size) == -1) {
            perror("munmap");
            return -1;
        }
    }

    if (mapped_file->fd != -1) {
        if (close(mapped_file->fd) == -1) {
            perror("close");
            return -1;
        }
    }

    mapped_file->address = MAP_FAILED;
    mapped_file->size = 0;
    mapped_file->fd = -1;

    return 0;
}
