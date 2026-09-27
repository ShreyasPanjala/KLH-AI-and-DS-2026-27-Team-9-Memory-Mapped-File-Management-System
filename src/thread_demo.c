#include "thread_demo.h"

#include <stdio.h>
#include <pthread.h>

#define ITERATIONS 1000

static int shared_counter = 0;

static pthread_mutex_t counter_mutex =
    PTHREAD_MUTEX_INITIALIZER;

static void *worker(void *arg)
{
    int thread_number = *(int *)arg;

    printf("Thread %d started.\n", thread_number);

    for (int i = 0; i < ITERATIONS; i++)
    {
        pthread_mutex_lock(&counter_mutex);

        shared_counter++;

        pthread_mutex_unlock(&counter_mutex);
    }

    printf("Thread %d completed.\n", thread_number);

    return NULL;
}

void run_thread_demo(void)
{
    printf("\n");
    printf("===============================================\n");
    printf("              CONCURRENT ACCESS\n");
    printf("===============================================\n");

    shared_counter = 0;

    pthread_t thread1;
    pthread_t thread2;

    int id1 = 1;
    int id2 = 2;

    printf("Creating two threads...\n");

    if (pthread_create(
            &thread1,
            NULL,
            worker,
            &id1) != 0)
    {
        perror("pthread_create");
        return;
    }

    if (pthread_create(
            &thread2,
            NULL,
            worker,
            &id2) != 0)
    {
        perror("pthread_create");
        return;
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("\nBoth threads completed.\n");
    printf("Final shared counter: %d\n",
           shared_counter);

    pthread_mutex_destroy(&counter_mutex);

    printf("Concurrent access completed successfully.\n");
}
