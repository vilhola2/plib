#ifndef PLIB_INTFMT_H
#define PLIB_INTFMT_H

#include <inttypes.h>

/**
 * @defgroup fmt_macros Integer format specifier macros
 *
 * These macros are wrappers for the fixed-with integer format specifiers defined in <inttypes.h>
 *
 * @{
 */

/**
 * @defgroup signed_types Signed integer types
 * @{
 */

#define WD8   "%" PRId8
#define WD16  "%" PRId16
#define WD32  "%" PRId32
#define WD64  "%" PRId64
#define WDMAX "%" PRIdMAX
#define WDPTR "%" PRIdPTR

/**
 * @}
 */

/**
 * @defgroup unsigned_types Unsigned integer types
 * @{
 */

#define WU8   "%" PRIu8
#define WU16  "%" PRIu16
#define WU32  "%" PRIu32
#define WU64  "%" PRIu64
#define WUMAX "%" PRIuMAX
#define WUPTR "%" PRIuPTR

/**
 * @}
 */

/**
 * @defgroup uppercase_hex Uppercase hexadecimal
 * @{
 */

#define WX8   "%" PRIX8
#define WX16  "%" PRIX16
#define WX32  "%" PRIX32
#define WX64  "%" PRIX64
#define WXPTR "%" PRIXPTR
#define WXMAX "%" PRIXMAX

/**
 * @}
 */

/**
 * @defgroup lowercase_hex Lowercase hexadecimal
 * @{
 */

#define Wx8   "%" PRIx8
#define Wx16  "%" PRIx16
#define Wx32  "%" PRIx32
#define Wx64  "%" PRIx64
#define WxPTR "%" PRIxPTR
#define WxMAX "%" PRIxMAX

/**
 * @}
 */

/**
 * @}
 */

#endif

