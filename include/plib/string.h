#ifndef PLIB_STRING_H
#define PLIB_STRING_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdalign.h>
#include <assert.h>

/**
 * @defgroup dstructs Data structures
 * @{
 */

/**
 * @defgroup string string
 * @{
 */

/**
 * @brief The information that a string_t holds
 * 'raw' Is a bitfield:
 * - Bits 0-30: is the strings capacity
 * - Bit 31: tells whether the 'str' members memory is managed by the user (1) or internally (0)
 * @warning Do not access this structs members unless you know what you are doing!
 */
struct str_internal {
    size_t raw, len;
    char *str;
};

/**
 * This is a semi-opaque string type.
 * This type should only be used with functions declared here.
 */
typedef struct {
    alignas(struct str_internal) char pad[sizeof(struct str_internal)];
} string_t;

static_assert(sizeof(string_t) == sizeof(struct str_internal),   "string_t size mismatch");
static_assert(alignof(string_t) == alignof(struct str_internal), "string_t alignment mismatch");

/**
 * @}
 */

/**
 * @defgroup string_view string_view
 * @{
 */

struct sv_internal {
    const string_t *view;
    size_t offset;
};

typedef struct {
    alignas(struct sv_internal) char pad[sizeof(struct sv_internal)];
} string_view_t;

static_assert(sizeof(string_view_t) == sizeof(struct sv_internal),   "string_view_t size mismatch");
static_assert(alignof(string_view_t) == alignof(struct sv_internal), "string_view_t alignment mismatch");

/**
 * @}
 */

/**
 * @ingroup string string
 * @{
 */

#ifndef PLIB_STR_DEFAULT_SIZE
#define PLIB_STR_DEFAULT_SIZE 64u
#endif

/**
 * @defgroup str_api_functions API functions
 * @{
 */

/**
 * @brief Creates a string_t with the cstr on the heap.
 * @return A string_t with internally managed memory.
 */
string_t string_create(void);

/**
 * @brief Destroys a string_t which was initialized with internally managed memory.
 * @warning Do not call this function if you initialized a string_t with your own buffer.
 *          Instead free the buffer.
 */
void string_destroy(string_t *str);

/**
 * @brief Creates a string_t with a user specified buffer.
 * @warning Do NOT free the string_t with string_destroy.
 * @return A string_t.
 */
string_t string_init(char *buf, size_t bufsize);

const char *string_as_cstr(const string_t *str);
string_view_t string_as_sv(const string_t *str);

/**
 * @brief Returns a string_t's capacity.
 */
size_t string_cap(const string_t *str);

/**
 * @brief Returns a string_t's length.
 */
size_t string_len(const string_t *str);

// Dear future me: sorry not sorry :)

bool string_copy_cstr(string_t *dest, size_t offset, const char *src); 
bool string_copy_sv(string_t *dest, size_t offset, const string_view_t *src); 
bool string_copy(string_t *dest, size_t offset, const string_t *src); 
bool string_ncopy_cstrn(string_t *dest, size_t offset, const char *src, size_t n); 
bool string_ncopy_sv(string_t *dest, size_t offset, const string_view_t *src, size_t n); 
bool string_ncopy(string_t *dest, size_t offset, const string_t *src, size_t n); 
bool string_cat_cstr(string_t *dest, const char *src); 
bool string_cat_sv(string_t *dest, const string_view_t *src); 
bool string_cat(string_t *dest, const string_t *src); 
bool string_ncat_cstrn(string_t *dest, const char *src, size_t n); 
bool string_ncat_sv(string_t *dest, const string_view_t *src, size_t n); 
bool string_ncat(string_t *dest, const string_t *src, size_t n); 

/**
 * @}
 */

/**
 * @}
 */

/**
 * @ingroup string_view string_view
 * @{
 */

/**
 * @defgroup sv_api_functions API functions
 * @{
 */

int string_view_cmp(const string_view_t *a, const string_view_t *b);

size_t string_view_len(const string_view_t *sv);

bool string_view_set_offset(string_view_t *sv, const size_t new_offset);
size_t string_view_get_offset(const string_view_t *sv);

const char *string_view_as_cstr(const string_view_t *sv);

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

