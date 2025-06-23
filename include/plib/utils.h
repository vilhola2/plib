#ifndef UTILS_H
#define UTILS_H

#define swap(a, b) \
    do { \
        __auto_type a__ = &(a); \
        __auto_type b__ = &(b); \
        __auto_type tmp__ = *a__; \
        *a__ = *b__; \
        *b__ = tmp__; \
    } while(0)

#define min(a, b) ({ \
    __auto_type a__ = (a); \
    __auto_type b__ = (b); \
    (a__ > b__ ? b__ : a__); \
})

#define max(a, b) ({ \
    __auto_type a__ = (a); \
    __auto_type b__ = (b); \
    (a__ > b__ ? a__ : b__); \
})

#endif

