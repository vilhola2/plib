#define PLIB_IMPL 1
#include <stdlib.h>
#include <string.h>
#include "../include/plib/dstructs.h"

#ifdef DEBUG_VERBOSE
#include <stdio.h>
#endif

struct da_header *impl_da_grow(struct da_header *h, const size_t new_bytes) {
    while (h->cap < h->len + new_bytes) {
        const size_t new_cap = h->cap * 2;
        struct da_header *temp = realloc(h, sizeof(struct da_header) + new_cap);
        if (!temp) return NULL;
        (h = temp)->cap = new_cap;
    }
#ifdef DEBUG_VERBOSE
    printf("succesfully grew dynarray: len: %zu, cap: %zu\n", h->len, h->cap); 
#endif
    return h;
}

struct da_header *impl_da_reserve(struct da_header *h, const size_t element_sz, const size_t additional_elements) {
    const size_t new_cap = h->cap + additional_elements * element_sz;
    struct da_header *temp = realloc(h, sizeof(struct da_header) + new_cap);
    if (!temp) return NULL;
    (h = temp)->cap = new_cap;
#ifdef DEBUG_VERBOSE
    printf("succesfully reserved space for dynarray: len: %zu, cap: %zu\n", h->len, h->cap); 
#endif
    return h;
}

void *impl_da_create(const size_t element_sz, const size_t starting_sz) {
    struct da_header *h = malloc(sizeof(*h) + starting_sz * element_sz);
    if (!h) return NULL;
    *h = (struct da_header) { .cap = starting_sz * element_sz };
#ifdef DEBUG_VERBOSE
    printf("created dynarray: len: %zu, cap: %zu\n", h->len, h->cap); 
#endif
    return (void *)((struct da_header *)h + 1);
}

void *impl_da_push(void *ptr, const void *item, const size_t element_sz) {
    struct da_header *h = impl_da_grow(impl_get_da_header(ptr), element_sz);
    if (!h) return NULL;
    memcpy(h->data + h->len, item, element_sz);
    h->len += element_sz;
#ifdef DEBUG_VERBOSE
    printf("succesfully pushed element to dynarray: len: %zu, cap: %zu\n", h->len, h->cap); 
#endif
    return h->data;
}

