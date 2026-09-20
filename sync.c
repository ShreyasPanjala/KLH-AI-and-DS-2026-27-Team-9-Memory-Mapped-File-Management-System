#include <stdio.h>
#include "sync.h"

pthread_mutex_t mutex;

void init_mutex()
{
    pthread_mutex_init(&mutex, NULL);
}

void lock_memory()
{
    pthread_mutex_lock(&mutex);
}

void unlock_memory()
{
    pthread_mutex_unlock(&mutex);
}

void destroy_mutex()
{
    pthread_mutex_destroy(&mutex);
}
