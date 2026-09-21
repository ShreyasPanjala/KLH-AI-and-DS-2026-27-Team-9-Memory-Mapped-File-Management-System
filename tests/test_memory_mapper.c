#include "memory_mapper.h"

#include <stdio.h>
#include <sys/mman.h>

static int test_read_mapping(void)
{
    MappedFile file;

    printf("\n=== TEST 1: READ-ONLY MAPPING ===\n");

    if (map_file("data/test.txt", PROT_READ, &file) != 0) {
        printf("TEST 1 FAILED\n");
        return -1;
    }

    printf("Mapping successful.\n");
    printf("File size: %zu bytes\n", file.size);

    printf("Contents:\n");
    printf("%.*s", (int)file.size, (char *)file.address);

    if (unmap_file(&file) != 0) {
        printf("Unmapping failed.\n");
        return -1;
    }

    printf("Read-only mapping released successfully.\n");

    return 0;
}

static int test_write_mapping(void)
{
    MappedFile file;

    printf("\n=== TEST 2: READ-WRITE MAPPING ===\n");

    if (map_file(
            "data/test.txt",
            PROT_READ | PROT_WRITE,
            &file) != 0) {
        printf("TEST 2 FAILED\n");
        return -1;
    }

    printf("Read-write mapping successful.\n");

    char *data = (char *)file.address;

    /*
     * Change the first character through mapped memory.
     */
    if (data[0] == 'H') {
        data[0] = 'h';
    } else if (data[0] == 'h') {
        data[0] = 'H';
    }

    printf("Modified first character through mapped memory.\n");

    if (sync_file(&file) != 0) {
        printf("Synchronization failed.\n");
        unmap_file(&file);
        return -1;
    }

    printf("msync() completed successfully.\n");

    if (unmap_file(&file) != 0) {
        printf("Unmapping failed.\n");
        return -1;
    }

    printf("Read-write mapping released successfully.\n");

    return 0;
}

static int test_memory_access(void)
{
    MappedFile file;

    printf("\n=== TEST 3: DIRECT MEMORY ACCESS ===\n");

    if (map_file(
            "data/test.txt",
            PROT_READ | PROT_WRITE,
            &file) != 0) {
        printf("TEST 3 FAILED\n");
        return -1;
    }

    char *data = (char *)file.address;

    printf("First 10 bytes through mapped memory:\n");

    size_t count = file.size < 10 ? file.size : 10;

    for (size_t i = 0; i < count; i++) {
        putchar(data[i]);
    }

    putchar('\n');

    if (unmap_file(&file) != 0) {
        return -1;
    }

    return 0;
}

int main(void)
{
    printf("========================================\n");
    printf(" Linux Memory-Mapped File System\n");
    printf(" Memory Mapping Module Tests\n");
    printf("========================================\n");

    if (test_read_mapping() != 0) {
        return 1;
    }

    if (test_write_mapping() != 0) {
        return 1;
    }

    if (test_memory_access() != 0) {
        return 1;
    }

    printf("\n========================================\n");
    printf(" All tests completed successfully!\n");
    printf("========================================\n");

    return 0;
}
