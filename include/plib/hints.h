#ifndef HINTS_H
#define HINTS_H

#define ALWAYS_INLINE __attribute__((always_inline)) inline
#define MAYBE_UNUSED __attribute__((unused))
#define likely(condition)   __builtin_expect(!!(condition), 1)
#define unlikely(condition) __builtin_expect(!!(condition), 0)

#endif

