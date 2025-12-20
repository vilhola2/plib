#ifndef PLIB_THREAD_H
#define PLIB_THREAD_H

#include <stdbool.h>

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
typedef HANDLE thread_t;

#else

#include <pthread.h>
typedef pthread_t thread_t;

#endif

bool thread_create(thread_t *t, void *(*func)(void *arg), void *arg);
bool thread_join(thread_t *thread);
bool thread_detach(thread_t *thread);

#endif

