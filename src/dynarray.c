#include <stdlib.h>
#include <string.h>
#include <plib/dynarray.h>
#include <plib/hints.h>
#include <stdio.h>

bool impl_da_grow_exp(struct da_header **h, const size_t new_bytes) {
    size_t new_cap = (*h)->cap;
    while ((*h)->cap < (*h)->len + new_bytes) {
        size_t temp;
        if (unlikely(__builtin_mul_overflow(new_cap, 2, &temp))) {
            fprintf(stderr, "dynarray.c: Capacity multiplication overflow!\n");
            return false;
        }
        new_cap = temp;
    }
    struct da_header *temp = realloc(*h, sizeof(struct da_header) + new_cap);
    if (unlikely(!temp)) return false;
    (*h = temp)->cap = new_cap;
#ifdef DEBUG
    printf("successfully grew dynarray: len: %zu, cap: %zu\n", (*h)->len, (*h)->cap); 
#endif
    return true;
}

bool impl_da_reserve(struct da_header **h, const size_t element_sz, const size_t new_sz) {
    const size_t new_cap = new_sz * element_sz;
    struct da_header *temp = realloc(*h, sizeof(struct da_header) + new_cap);
    if (unlikely(!temp)) return false;
    (*h = temp)->cap = new_cap;
#ifdef DEBUG
    printf("successfully reserved space for dynarray: len: %zu, cap: %zu\n", (*h)->len, (*h)->cap); 
#endif
    return true;
}

void *impl_da_create(const size_t element_sz, const size_t starting_sz) {
    struct da_header *h = malloc(sizeof(*h) + starting_sz * element_sz);
    if (unlikely(!h)) return NULL;
    *h = (struct da_header) { .cap = starting_sz * element_sz };
#ifdef DEBUG
    printf("created dynarray: len: %zu, cap: %zu\n", h->len, h->cap); 
#endif
    return (void *)h->data;
}

bool impl_da_push(void **ptr, const void *item, const size_t element_sz) {
    struct da_header *h = impl_get_da_header(*ptr);
    if (unlikely(!impl_da_grow_exp(&h, element_sz))) return false;
    memcpy(h->data + h->len, item, element_sz);
    h->len += element_sz;
    *ptr = h->data;
#ifdef DEBUG
    printf("successfully pushed element to dynarray: len: %zu, cap: %zu\n", h->len, h->cap); 
#endif
    return true;
}

