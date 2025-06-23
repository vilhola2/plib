#ifndef PLIB_STRING_INTERNAL_H
#define PLIB_STRING_INTERNAL_H

#define ucast(type, src) \
    ({\
        union { \
            typeof(src) src__; \
            type dest__; \
        } u = { .src__ = (src) }; \
        u.dest__; \
    })

#define SIZE_T_BITS (sizeof(size_t) * 8)
#define PLIB_STR_USER_BUFFER_MASK ((size_t)1 << (SIZE_T_BITS - 1))
#define PLIB_STR_CAP_MASK (~PLIB_STR_USER_BUFFER_MASK)
#define PLIB_STR_MAX PLIB_STR_CAP_MASK

#endif

