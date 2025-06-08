#ifndef PLIB_IO_H
#define PLIB_IO_H

#include <stdio.h>
#include <stdint.h>
#include "hints.h"

/**
 * @defgroup internal_functions Internal functions
 * @{
 */

static ALWAYS_INLINE void impl_bin_generic(const uint64_t value, const int_fast8_t bits, char *buf) {
    for (int i = bits - 1; i >= 0; --i)
        buf[bits - 1 - i] = (value & (1ULL << i)) ? '1' : '0';
    buf[bits] = '\0';
}

/**
 * @}
 */

/**
 * @defgroup input_functions Input functions
 * @{
 */

/**
 * @brief Reads a line from a stream, excluding the newline.
 *
 * Reads characters from the given input stream until a newline or EOF is encountered.
 * The newline character will not be included in the string.
 *
 * The caller is responsible for freeing the returned string.
 *
 * @param stream Input stream to read from.
 * @return A malloc'ed string, or NULL on EOF or allocation failure.
 *         The caller must free the returned string.
 */
char *str_input(FILE *stream);

/**
 * @}
 */

/**
 * @defgroup output_functions Output functions
 * @{
 */

/**
 * @defgroup binary_output Binary output functions
 * 
 * These functions allow you to get the binary representation of a value.
 * They all take a string buffer as a parameter, where the binary will be stored.
 * The functions can be used with eg. printf.
 *
 * @{
 */

/**
 * @param b A byte to represent in binary.
 * @param buf A buffer where the string will be stored in.
 * @return A pointer to 'buf' for convenience.
 */
MAYBE_UNUSED static ALWAYS_INLINE char *bin8(const uint8_t b, char buf[static 8 + 1]) {
    impl_bin_generic(b, 8, buf);
    return buf;
}

/**
 * @param w A word to represent in binary.
 * @param buf A buffer where the string will be stored in.
 * @return A pointer to 'buf' for convenience.
 */
MAYBE_UNUSED static ALWAYS_INLINE char *bin16(const uint16_t w, char buf[static 16 + 1]) {
    impl_bin_generic(w, 16, buf);
    return buf;
}

/**
 * @param dw A double-word to represent in binary.
 * @param buf A buffer where the string will be stored in.
 * @return A pointer to 'buf' for convenience.
 */
MAYBE_UNUSED static ALWAYS_INLINE char *bin32(const uint32_t dw, char buf[static 32 + 1]) {
    impl_bin_generic(dw, 32, buf);
    return buf;
}

/**
 * @param qw A quad-word to represent in binary.
 * @param buf A buffer where the string will be stored in.
 * @return A pointer to 'buf' for convenience.
 */
MAYBE_UNUSED static ALWAYS_INLINE char *bin64(const uint64_t qw, char buf[static 64 + 1]) {
    impl_bin_generic(qw, 64, buf);
    return buf;
}

/**
 * @}
 */

/**
 * @}
 */

#endif
