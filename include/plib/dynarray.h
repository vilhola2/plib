#ifndef PLIB_DYNARRAY_H
#define PLIB_DYNARRAY_H

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hints.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup dstructs Data structures
 * @{
 */

/**
 * @defgroup dynarray Dynarray
 * @{
 */

#ifndef PLIB_DYNARRAY_DEFAULT_SIZE 
#define PLIB_DYNARRAY_DEFAULT_SIZE 4u
#endif

/**
 * @defgroup da_internal_structs Internal structs
 * @{
 */

struct da_header {
    size_t len, cap;
    unsigned char data[];
};

/**
 * @}
 */

/**
 * @defgroup da_internal_functions Internal functions
 * @{
 */

void *impl_da_create(const size_t element_sz, const size_t starting_sz);
bool impl_da_push(void **ptr, const void *item, const size_t element_sz);
bool impl_da_grow_exp(struct da_header **h, const size_t new_bytes);
bool impl_da_reserve(struct da_header **h, const size_t element_sz, const size_t new_sz);

static inline struct da_header *impl_get_da_header(const void *arr) {
    return (struct da_header *)((unsigned char *)arr - offsetof(struct da_header, data));
}

/**
 * @}
 */

/**
 * @defgroup da_api_macros API macros
 * @{
 */

/**
 * @brief Creates a dynarray with the default starting size.
 *
 * The dynarray must be free'd with dynarray_destroy().
 *
 * @param type A type which size will be used as a multiplier for the default starting size.
 * @return Returns a pointer to the start of the array.
 */
#define dynarray_create(type) \
    impl_da_create(sizeof(type), PLIB_DYNARRAY_DEFAULT_SIZE)

/**
 * @brief Creates a dynarray with a specified size.
 *
 * The dynarray must be free'd with dynarray_destroy().
 *
 * @param type A type which size will be used as a multiplier for the starting size.
 * @param elements An integer representing the amount of elements the dynarray will have initial capacity for.
 * @return Returns a pointer to the start of the array.
 */
#define dynarray_create_presized(type, elements) \
    impl_da_create(sizeof(type), (elements))

/**
 * @brief Pushes an element into a dynarray.
 *
 * @warning 'arr' must originate from dynarray_create()!
 *
 * @param arr A dynarray to push an element into.
 * @param elem The element to push into the dynarray.
 * @return Returns true on success, false on failure.
 */
#define dynarray_push(arr, elem) \
    ({ \
        typeof(*(arr)) elem__ = (elem); \
        void *temp__ = (arr); \
        bool success__ = impl_da_push(&temp__, &(elem__), sizeof(elem__)); \
        (arr) = temp__; \
        success__; \
    })

/**
 * @brief Reserves space for a dynarray.
 *
 * @warning 'arr' must originate from dynarray_create()!
 *
 * @param arr A dynarray to reserve space for.
 * @param new_elements The amount of new elements to reserve space for.
 * @return Returns true on success, false on failure.
 */
#define dynarray_reserve(arr, new_elements) \
    ({ \
        struct da_header *h__ = impl_get_da_header(arr); \
        bool success__ = impl_da_reserve(&h__, sizeof(*(arr)), (new_elements)); \
        if (likely(success__)) (arr) = (typeof(arr))h__->data; \
        success__; \
    })

/**
 * @brief Returns the length of a dynarray.
 *
 * @warning 'arr' must originate from dynarray_create()!
 *
 * @param arr A dynarray to get the length from.
 */
#define dynarray_len(arr) \
    ((impl_get_da_header(arr))->len / sizeof(*(arr)))

/**
 * @brief Returns the capacity of a dynarray.
 *
 * @warning 'arr' must originate from dynarray_create()!
 *
 * @param arr A dynarray to get the capacity from.
 */
#define dynarray_cap(arr) \
    ((impl_get_da_header(arr))->cap / sizeof(*(arr)))

/**
 * @brief An iterator for a dynarray.
 *
 * @warning 'arr' must originate from dynarray_create()!
 *
 * @param arr The array to iterate over.
 * @param elem_ptr The name of the element pointer to capture in each iteration.
 */
#define dynarray_foreach(arr, elem_ptr) \
    for ( \
        typeof(*arr) *(elem_ptr) = (arr), \
        *end__##elem_ptr = (arr) + dynarray_len(arr); \
        (elem_ptr) < end__##elem_ptr; ++(elem_ptr) \
        /* the end pointer's name is mangled to avoid variable shadowing */ \
    )

/**
 * @}
 */

/**
 * @defgroup da_api_functions API functions
 * @{
 */

/**
 * @brief Frees the memory of a dynarray.
 *
 * @warning 'arr' must originate from dynarray_create()!
 * 'arr' must not be used after this function is called!
 *
 * @param arr The array to destroy.
 */
MAYBE_UNUSED static ALWAYS_INLINE void dynarray_destroy(void *arr) {
    free(impl_get_da_header(arr));
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
