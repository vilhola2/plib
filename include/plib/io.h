#ifndef PLIB_IO_H
#define PLIB_IO_H

#include <stdio.h>
#include <stdint.h>

// -- Input functions --

// Returns a heap-allocated string. Must be free'd with free().
char *str_input(FILE *stream);

// -- Output functions --

__attribute((flatten))
__attribute((always_inline))
static inline void impl_bin_generic(const uint64_t value, const int_fast8_t bits, char *buf) {
    for (int i = bits - 1; i >= 0; --i) {
        buf[bits - 1 - i] = (value & (1ULL << i)) ? '1' : '0';
    }
    buf[bits] = '\0';
}

// CAUTION! 'buf' will be mutated.
// Returns a pointer to 'buf' for convenience.
__attribute((unused))
__attribute((flatten))
__attribute((always_inline))
static inline char *bin8(const uint8_t b, char buf[static 8 + 1]) {
    impl_bin_generic(b, 8, buf);
    return buf;
}

// CAUTION! 'buf' will be mutated.
// Returns a pointer to 'buf' for convenience.
__attribute((unused))
__attribute((flatten))
__attribute((always_inline))
static inline char *bin16(const uint16_t w, char buf[static 16 + 1]) {
    impl_bin_generic(w, 16, buf);
    return buf;
}

// CAUTION! 'buf' will be mutated.
// Returns a pointer to 'buf' for convenience.
__attribute((unused))
__attribute((flatten))
__attribute((always_inline))
static inline char *bin32(const uint32_t dw, char buf[static 32 + 1]) {
    impl_bin_generic(dw, 32, buf);
    return buf;
}

// CAUTION! 'buf' will be mutated.
// Returns a pointer to 'buf' for convenience.
__attribute((unused))
__attribute((flatten))
__attribute((always_inline))
static inline char *bin64(const uint64_t qw, char buf[static 64 + 1]) {
    impl_bin_generic(qw, 64, buf);
    return buf;
}

#endif
