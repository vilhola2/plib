#include <stdbool.h>
#include <plib/thread.h>
#include <plib/hints.h>

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

struct thread_internal {
    void *(*func)(void *arg);
    void *arg;
};

DWORD WINAPI thread_start(LPVOID arg) {
    struct thread_internal *thread = (struct thread_internal *)arg;
    thread->func(thread->arg);
    free(thread);
    return 0;
}

bool thread_create(thread_t *thread, void *(*func)(void *arg), void *arg) {
    struct thread_internal *new_thread = malloc(sizeof(struct thread_internal));
    if (unlikely(!new_thread)) return false;
    new_thread->arg = arg;
    new_thread->func = func;
    *thread = CreateThread(NULL, 0, thread_start, new_thread, 0, NULL);
    if (unlikely(!(*thread))) return false;
    return true;
}

bool thread_join(thread_t *thread) {
    if (unlikely(WaitForSingleObject(*thread, INFINITE) != WAIT_OBJECT_0)) return false;
    CloseHandle(*thread);
    return true;
}

bool thread_detach(thread_t *thread) {
    if (unlikely(!CloseHandle(*thread))) return false;
    return true;
}

#else

#include <pthread.h>

ALWAYS_INLINE bool thread_create(thread_t *thread, void *(*func)(void *arg), void *arg) {
    if (unlikely(pthread_create(thread, NULL, func, arg))) return false;
    return true;
}

ALWAYS_INLINE bool thread_join(thread_t *thread) {
    if (unlikely(pthread_join(*thread, NULL))) return false;
    return true;
}

ALWAYS_INLINE bool thread_detach(thread_t *thread) {
    if (unlikely(pthread_detach(*thread))) return false;
    return true;
}

#endif

