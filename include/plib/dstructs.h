#ifndef PLIB_DSTRUCTS_H
#define PLIB_DSTRUCTS_H

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
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

static inline struct da_header *impl_get_da_header(const void *arr) {
    return (struct da_header *)((unsigned char *)arr - offsetof(struct da_header, data));
}

// --- API macros ---

#define dynarray_create(type) \
    (impl_da_create(sizeof(type), DYNARRAY_DEFAULT_SIZE))

// CAUTION! 'arr' must originate from dynarray_create()!
#define dynarray_push(arr, elem) \
    ({ \
        bool success__ = true; \
        typeof(*(arr)) elem__ = (elem); \
        (arr) = impl_da_push((arr), &(elem__), sizeof(elem__)); \
        if (!arr) success__ = false; \
        success__; \
    })

// CAUTION! 'arr' must originate from dynarray_create()!
#define dynarray_reserve(arr, additional_elements) \
    ({ \
        struct da_header *h__ = impl_get_da_header(arr); \
        bool success__ = true; \
        h__ = impl_da_reserve(h__, sizeof(*(arr)), (additional_elements)); \
        if(!h__) { \
            (arr) = NULL; \
            success__ = false; \
        } else (arr) = (void *)((struct da_header *)h__->data); \
        success__; \
    })

// CAUTION! 'arr must originate from dynarray_create()!
#define dynarray_len(arr) \
    ((impl_get_da_header(arr))->len / sizeof(*(arr)))

// CAUTION! 'arr' must originate from dynarray_create()!
#define dynarray_cap(arr) \
    ((impl_get_da_header(arr))->cap / sizeof(*(arr)))

// CAUTION! 'arr' must originate from dynarray_create()!
#define dynarray_iterate(arr, elem_ptr) \
    for( \
        typeof(*arr) *(elem_ptr) = (arr), \
        *end__##elem_ptr = (arr) + dynarray_len(arr); \
        (elem_ptr) < end__##elem_ptr; ++(elem_ptr) \
        /* the end pointer's name is mangled to avoid variable shadowing */ \
    )

// --- API functions ---

// CAUTION! 'arr' must originate from dynarray_create()!
// 'arr' must not be used after this function is called
__attribute((unused)) static inline void dynarray_destroy(void *arr) {
    if (arr != NULL) free(impl_get_da_header(arr));
}

#ifdef __cplusplus
}
#endif

#endif
