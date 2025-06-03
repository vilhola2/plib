#ifndef INTFMT_H
#define INTFMT_H

#include <inttypes.h>

// -- Signed integer types --
#define WD8   "%" PRId8
#define WD16  "%" PRId16
#define WD32  "%" PRId32
#define WD64  "%" PRId64
#define WDMAX "%" PRIdMAX
#define WDPTR "%" PRIdPTR

// -- Unsigned integer types --
#define WU8   "%" PRIu8
#define WU16  "%" PRIu16
#define WU32  "%" PRIu32
#define WU64  "%" PRIu64
#define WUMAX "%" PRIuMAX
#define WUPTR "%" PRIuPTR

// -- Uppercase hexadecimal --
#define WX8   "%" PRIX8
#define WX16  "%" PRIX16
#define WX32  "%" PRIX32
#define WX64  "%" PRIX64
#define WXPTR "%" PRIXPTR
#define WXMAX "%" PRIXMAX

// -- Lowercase hexadecimal --
#define Wx8   "%" PRIx8
#define Wx16  "%" PRIx16
#define Wx32  "%" PRIx32
#define Wx64  "%" PRIx64
#define WxPTR "%" PRIxPTR
#define WxMAX "%" PRIxMAX


// -- Binary printing --

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

