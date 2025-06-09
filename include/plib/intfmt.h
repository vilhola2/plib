#ifndef PLIB_INTFMT_H
#define PLIB_INTFMT_H

#include <inttypes.h>

/**
 * @defgroup fmt_macros Integer format specifier macros
 *
 * These macros are wrappers for the fixed-width integer format specifiers defined in <inttypes.h>
 *
 * Naming convention:
 *   - W = Write (printf-style)
 *   - R = Read  (scanf-style)
 *   - D = Decimal (signed)
 *   - U = Unsigned
 *   - x/X = Hex (lower/upper)
 *   - 8/16/32/64/MAX/PTR = Bit width
 * @{
 */


/**
 * @defgroup write_macros Write macros
 *
 * These are for printf-style writes.
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

/**
 * @defgroup read_macros Read macros
 *
 * These are for scanf-style reads.
 * @{
 */

/**
 * @defgroup signed_types Signed integer types
 * @{
 */

#define RD8   "%" SCNd8
#define RD16  "%" SCNd16
#define RD32  "%" SCNd32
#define RD64  "%" SCNd64
#define RDMAX "%" SCNdMAX
#define RDPTR "%" SCNdPTR

/**
 * @}
 */

/**
 * @defgroup unsigned_types Unsigned integer types
 * @{
 */

#define RU8   "%" SCNu8
#define RU16  "%" SCNu16
#define RU32  "%" SCNu32
#define RU64  "%" SCNu64
#define RUMAX "%" SCNuMAX
#define RUPTR "%" SCNuPTR

/**
 * @}
 */

/**
 * @defgroup uppercase_hex Uppercase hexadecimal
 * @{
 */

#define RX8   "%" SCNX8
#define RX16  "%" SCNX16
#define RX32  "%" SCNX32
#define RX64  "%" SCNX64
#define RXPTR "%" SCNXPTR
#define RXMAX "%" SCNXMAX

/**
 * @}
 */

/**
 * @defgroup lowercase_hex Lowercase hexadecimal
 * @{
 */

#define Rx8   "%" SCNx8
#define Rx16  "%" SCNx16
#define Rx32  "%" SCNx32
#define Rx64  "%" SCNx64
#define RxPTR "%" SCNxPTR
#define RxMAX "%" SCNxMAX

/**
 * @}
 */

/**
 * @}
 */


/**
 * @}
 */

#endif

