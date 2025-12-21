#include <stdbool.h>
#include <plib/thread.h>
#include <plib/hints.h>

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <process.h>

DWORD WINAPI thread_start(LPVOID arg) {
    thread_t *new_thread = (thread_t *)arg;
    new_thread->retval = new_thread->func(new_thread->arg);
    return 0;
}

bool thread_create(thread_t *thread, void *(*func)(void *arg), void *arg) {
    thread->arg = arg;
    thread->func = func;
    thread->handle = (HANDLE)_beginthreadex(NULL, 0, thread_start, thread, 0, NULL);
    if (unlikely(!(thread->handle))) return false;
    return true;
}

void *thread_join(thread_t *thread) {
    if (unlikely(WaitForSingleObject(thread->handle, INFINITE) != WAIT_OBJECT_0)) return NULL;
    CloseHandle(thread->handle);
    return thread->retval;
}

bool thread_detach(thread_t *thread) {
    if (unlikely(!CloseHandle(thread->handle))) return false;
    return true;
}

ALWAYS_INLINE bool mutex_create(mutex_t *mutex) {
    if(unlikely(!(*mutex = CreateMutex(NULL, FALSE, NULL)))) {
        fprintf(stderr, "CreateMutex error: %d\n", GetLastError());
        return false;
    }
    return true;
}

ALWAYS_INLINE bool mutex_destroy(mutex_t *mutex) {
    if (unlikely(!CloseHandle(*mutex))) return false;
    return true;
}

ALWAYS_INLINE bool mutex_lock(mutex_t *mutex) {
    if (unlikely(WaitForSingleObject(*mutex, INFINITE) != WAIT_OBJECT_0)) return false;
    return true;
}

ALWAYS_INLINE bool mutex_unlock(mutex_t *mutex) {
    if (unlikely(!ReleaseMutex(*mutex))) return false;
    return true;
}

#else

#include <pthread.h>

ALWAYS_INLINE bool thread_create(thread_t *thread, void *(*func)(void *arg), void *arg) {
    if (unlikely(pthread_create(thread, NULL, func, arg))) return false;
    return true;
}

ALWAYS_INLINE void *thread_join(thread_t *thread) {
    void *retval;
    if (unlikely(pthread_join(*thread, &retval))) return NULL;
    return retval;
}

ALWAYS_INLINE bool thread_detach(thread_t *thread) {
    if (unlikely(pthread_detach(*thread))) return false;
    return true;
}

ALWAYS_INLINE bool mutex_create(mutex_t *mutex) {
    if (unlikely(pthread_mutex_init(mutex, NULL))) return false;
    return true;
}

ALWAYS_INLINE bool mutex_destroy(mutex_t *mutex) {
    if (unlikely(pthread_mutex_destroy(mutex))) return false;
    return true;
}

ALWAYS_INLINE bool mutex_lock(mutex_t *mutex) {
    if (unlikely(pthread_mutex_lock(mutex))) return false;
    return true;
}

ALWAYS_INLINE bool mutex_unlock(mutex_t *mutex) {
    if (unlikely(pthread_mutex_unlock(mutex))) return false;
    return true;
}

#endif

