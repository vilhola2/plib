#ifndef INTFMT_H
#define INTFMT_H

#include <inttypes.h>

// Signed integer types
#define WD8   "%" PRId8
#define WD16  "%" PRId16
#define WD32  "%" PRId32
#define WD64  "%" PRId64
#define WDMAX "%" PRIdMAX
#define WDPTR "%" PRIdPTR

// Unsigned integer types
#define WU8   "%" PRIu8
#define WU16  "%" PRIu16
#define WU32  "%" PRIu32
#define WU64  "%" PRIu64
#define WUMAX "%" PRIuMAX
#define WUPTR "%" PRIuPTR

// Uppercase hexadecimal
#define WX8   "%" PRIX8
#define WX16  "%" PRIX16
#define WX32  "%" PRIX32
#define WX64  "%" PRIX64
#define WXPTR "%" PRIXPTR
#define WXMAX "%" PRIXMAX

// Lowercase hexadecimal
#define Wx8   "%" PRIx8
#define Wx16  "%" PRIx16
#define Wx32  "%" PRIx32
#define Wx64  "%" PRIx64
#define WxPTR "%" PRIxPTR
#define WxMAX "%" PRIxMAX

#endif
