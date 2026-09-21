#ifndef MEMORY_MAPPER_H
#define MEMORY_MAPPER_H

#include <stddef.h>

typedef struct {
    int fd;
    size_t size;
    void *address;
} MappedFile;

/*
 * Maps a file into the process virtual address space.
 *
 * protection:
 *   PROT_READ
 *   PROT_READ | PROT_WRITE
 *
 * Returns 0 on success, -1 on failure.
 */
int map_file(const char *filename, int protection, MappedFile *mapped_file);

/*
 * Synchronizes changes in mapped memory with the underlying file.
 *
 * Returns 0 on success, -1 on failure.
 */
int sync_file(MappedFile *mapped_file);

/*
 * Releases the memory mapping and closes the file descriptor.
 *
 * Returns 0 on success, -1 on failure.
 */
int unmap_file(MappedFile *mapped_file);

#endif
