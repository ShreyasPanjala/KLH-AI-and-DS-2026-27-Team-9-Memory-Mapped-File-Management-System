#include "memory_mapper.h"

#include <stdio.h>
#include <sys/mman.h>

int main(void)
{
    const char *filename = "data/test.txt";
    MappedFile mapped_file;

    printf("========================================\n");
    printf(" Linux Memory-Mapped File System Demo\n");
    printf("========================================\n\n");

    /* ------------------------------------------
     * STEP 1: Read-only memory mapping
     * ------------------------------------------ */
    printf("[1] READ-ONLY MAPPING\n");
    printf("----------------------------------------\n");

    if (map_file(filename, PROT_READ, &mapped_file) != 0) {
        fprintf(stderr, "Failed to map file for reading.\n");
        return 1;
    }

    printf("File mapped successfully.\n");
    printf("File size: %zu bytes\n", mapped_file.size);
    printf("Mapped address: %p\n", mapped_file.address);

    printf("\nFile contents through mapped memory:\n");
    fwrite(mapped_file.address, 1, mapped_file.size, stdout);
    printf("\n");

    if (unmap_file(&mapped_file) != 0) {
        fprintf(stderr, "Failed to unmap read-only mapping.\n");
        return 1;
    }

    printf("\nRead-only mapping released successfully.\n\n");


    /* ------------------------------------------
     * STEP 2: Read-write memory mapping
     * ------------------------------------------ */
    printf("[2] READ-WRITE MAPPING\n");
    printf("----------------------------------------\n");

    if (map_file(filename, PROT_READ | PROT_WRITE, &mapped_file) != 0) {
        fprintf(stderr, "Failed to map file for writing.\n");
        return 1;
    }

    printf("Read-write mapping successful.\n");
    printf("Mapped address: %p\n", mapped_file.address);

    /*
     * Save the original first byte so that the
     * demonstration does not permanently modify
     * data/test.txt.
     */
    char *data = (char *)mapped_file.address;
    char original_character = data[0];

    printf("Original first character: '%c'\n", original_character);

    /*
     * Modify the file through mapped memory.
     */
    if (data[0] >= 'a' && data[0] <= 'z') {
        data[0] = data[0] - ('a' - 'A');
    } else if (data[0] >= 'A' && data[0] <= 'Z') {
        data[0] = data[0] + ('a' - 'A');
    } else {
        data[0] = 'X';
    }

    printf("Modified first character: '%c'\n", data[0]);

    /* Synchronize mapped memory with the file. */
    if (sync_file(&mapped_file) != 0) {
        fprintf(stderr, "msync() failed.\n");
        unmap_file(&mapped_file);
        return 1;
    }

    printf("msync() completed successfully.\n");

    /*
     * Restore the original character so the demonstration
     * does not permanently change data/test.txt.
     */
    data[0] = original_character;

    if (sync_file(&mapped_file) != 0) {
        fprintf(stderr, "Failed to restore original file contents.\n");
        unmap_file(&mapped_file);
        return 1;
    }

    printf("Original file contents restored.\n");

    if (unmap_file(&mapped_file) != 0) {
        fprintf(stderr, "Failed to release read-write mapping.\n");
        return 1;
    }

    printf("Read-write mapping released successfully.\n\n");


    /* ------------------------------------------
     * STEP 3: Direct memory access
     * ------------------------------------------ */
    printf("[3] DIRECT MEMORY ACCESS\n");
    printf("----------------------------------------\n");

    if (map_file(filename, PROT_READ, &mapped_file) != 0) {
        fprintf(stderr, "Failed to map file.\n");
        return 1;
    }

    printf("First 10 bytes through mapped memory:\n");

    size_t bytes_to_display =
        mapped_file.size < 10 ? mapped_file.size : 10;

    fwrite(mapped_file.address, 1, bytes_to_display, stdout);
    printf("\n");

    if (unmap_file(&mapped_file) != 0) {
        fprintf(stderr, "Failed to release mapping.\n");
        return 1;
    }

    printf("\n========================================\n");
    printf(" Memory-mapped file demo completed!\n");
    printf("========================================\n");

    return 0;
}
