#ifndef SYNC_H
#define SYNC_H

#include <pthread.h>

void init_mutex();
void lock_memory();
void unlock_memory();
void destroy_mutex();

#endif
