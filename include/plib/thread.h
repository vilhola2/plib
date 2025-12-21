#ifndef PLIB_THREAD_H
#define PLIB_THREAD_H

#include <stdbool.h>

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
typedef struct {
    HANDLE handle;
    void *(*func)(void *arg);
    void *arg, *retval;
} thread_t;

typedef HANDLE mutex_t;

#else

#include <pthread.h>
typedef pthread_t thread_t;
typedef pthread_mutex_t mutex_t;

#endif

bool thread_create(thread_t *t, void *(*func)(void *arg), void *arg);
void *thread_join(thread_t *thread);
bool thread_detach(thread_t *thread);
bool mutex_create(mutex_t *mutex);
bool mutex_destroy(mutex_t *mutex);
bool mutex_lock(mutex_t *mutex);
bool mutex_unlock(mutex_t *mutex);

#endif

