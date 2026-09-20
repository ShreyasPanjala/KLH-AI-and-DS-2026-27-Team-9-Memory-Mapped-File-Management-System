#include <stdio.h>
#include <pthread.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "sync.h"

char *mapped_memory;

void *thread_function(void *arg)
{
    int id = *(int *)arg;

    lock_memory();

    printf("Thread %d entered critical section\n", id);

    strcat(mapped_memory, " Thread updated file.");

    printf("Thread %d modified the mapped memory\n", id);

    unlock_memory();

    return NULL;
}

int main()
{
    int fd = open("data.txt", O_RDWR);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    mapped_memory = mmap(NULL, 4096,
                         PROT_READ | PROT_WRITE,
                         MAP_SHARED, fd, 0);

    if (mapped_memory == MAP_FAILED)
    {
        perror("mmap");
        close(fd);
        return 1;
    }

    init_mutex();

    pthread_t t1, t2;
    int id1 = 1, id2 = 2;

    pthread_create(&t1, NULL, thread_function, &id1);
    pthread_create(&t2, NULL, thread_function, &id2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("\nFinal content:\n%s\n", mapped_memory);

    msync(mapped_memory, 4096, MS_SYNC);

    destroy_mutex();

    munmap(mapped_memory, 4096);
    close(fd);

    return 0;
}
