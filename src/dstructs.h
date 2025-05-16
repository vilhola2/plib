#ifndef dstructs_h
#define dstructs_h

#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "c" {
#endif

#ifndef DYNARRAY_DEFAULT_SIZE 
#define DYNARRAY_DEFAULT_SIZE 4
#endif

// --- Internal structs ---

struct da_header {
    size_t len, cap;
    unsigned char data[];
};

// --- Internal functions ---

void *impl_da_create(const size_t element_sz, const size_t starting_sz);
void *impl_da_push(void *ptr, const void *item, const size_t element_sz);
struct da_header *impl_da_grow(struct da_header *h, const size_t new_bytes);
struct da_header *impl_da_reserve(struct da_header *h, const size_t element_sz, const size_t additional_elements);

[[maybe_unused]] static inline struct da_header *impl_get_da_header(const void *ptr) {
    return (struct da_header *)((unsigned char *)ptr - offsetof(struct da_header, data));
}

// --- API macros ---

#define dynarray_create(type) \
    (impl_da_create(sizeof(type), DYNARRAY_DEFAULT_SIZE))

// CAUTION! 'ptr' must originate from dynarray_create()!
#define dynarray_push(arr, elem) \
    do { \
        typeof(*(arr)) elem__ = (elem); \
        (arr) = impl_da_push((arr), &(elem__), sizeof(elem__)); \
    } while(0)

// CAUTION! 'ptr' must originate from dynarray_create()!
#define dynarray_reserve(arr, additional_elements) \
    do { \
        struct da_header *h__ = impl_get_da_header(arr); \
        h__ = impl_da_reserve(h__, sizeof(*(arr)), (additional_elements)); \
        if(!h__) (arr) = nullptr; \
        else (arr) = (void *)((struct da_header *)h__->data); \
    } while(0)

// CAUTION! 'ptr' must originate from dynarray_create()!
#define dynarray_len(ptr) \
    ((impl_get_da_header(ptr))->len / sizeof(*(ptr)))

// CAUTION! 'ptr' must originate from dynarray_create()!
#define dynarray_cap(ptr) \
    ((impl_get_da_header(ptr))->cap / sizeof(*(ptr)))

// --- API functions ---

// CAUTION! 'ptr' must originate from dynarray_create()!
// 'ptr' must not be used after this function is called
[[maybe_unused]] static inline void dynarray_destroy(void *ptr) {
    if (ptr != nullptr) free(impl_get_da_header(ptr));
}

#ifdef __cplusplus
}
#endif

#endif

