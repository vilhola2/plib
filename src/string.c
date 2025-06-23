#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <plib/hints.h>
#include <plib/string.h>
#include <plib/utils.h>
#include "include/string_internal.h"

static ALWAYS_INLINE bool impl_get_str_user_buffer(const struct str_internal *str) {
    return str->raw & PLIB_STR_USER_BUFFER_MASK;
}

static ALWAYS_INLINE void impl_set_str_user_buffer(struct str_internal *str, bool val) {
    if (val) str->raw |= PLIB_STR_USER_BUFFER_MASK;
    else str->raw &= ~PLIB_STR_USER_BUFFER_MASK;
}

static ALWAYS_INLINE size_t impl_get_str_cap(const struct str_internal *str) {
    return str->raw & PLIB_STR_CAP_MASK;
}

static ALWAYS_INLINE void impl_set_str_cap(struct str_internal *str, const size_t new_cap) {
    str->raw = (str->raw & PLIB_STR_USER_BUFFER_MASK) | new_cap;
}

extern inline size_t string_cap(const string_t *str) {
    return impl_get_str_cap((const struct str_internal *)str);
}

extern inline size_t string_len(const string_t *str) {
    return ((struct str_internal *)str)->len;
}

extern inline const char *string_as_cstr(const string_t *str) {
    return ((struct str_internal *)str)->str;
}

extern inline string_view_t string_as_sv(const string_t *str) {
    struct sv_internal sv = { .view = str };
    return ucast(string_view_t, sv);
}

string_t string_create(void) {
    struct str_internal new_str;
    new_str.len = 0;
    new_str.raw = 0;
    new_str.str = malloc(PLIB_STR_DEFAULT_SIZE + 1);
    if (unlikely(!new_str.str)) {
        fprintf(stderr, "string.c: Malloc failed!\n");
        return (string_t){0};
    }
    *new_str.str = '\0';
    impl_set_str_user_buffer(&new_str, false);
    impl_set_str_cap(&new_str, PLIB_STR_DEFAULT_SIZE);
    return ucast(string_t, new_str);
}

void string_destroy(string_t *str) {
    struct str_internal *temp = (struct str_internal *)str;
    if (impl_get_str_user_buffer(temp)) return;
    free(temp->str);
}

string_t string_init(char *buf, size_t bufsize) {
    if (unlikely(bufsize > PLIB_STR_MAX)) {
        fprintf(stderr, "string.c: Buffer size is too large!\n");
        return (string_t){0};
    }
    if (unlikely(!buf)) {
        fprintf(stderr, "string.c: No buffer specified!\n");
        return (string_t){0};
    }
    if (unlikely(bufsize == 0)) {
        fprintf(stderr, "string.c: No buffer size specified!\n");
        return (string_t){0};
    }
    struct str_internal new_str;
    new_str.len = 0;
    new_str.raw = 0;
    new_str.str = buf;
    *new_str.str = '\0';
    impl_set_str_user_buffer(&new_str, true);
    impl_set_str_cap(&new_str, bufsize);
    return ucast(string_t, new_str);
}

bool impl_str_reserve(struct str_internal *str, size_t new_cap) {
    if (unlikely(new_cap > PLIB_STR_MAX)) {
        fprintf(stderr, "string.c: Capacity is too large!\n");
        return false;
    }
    char *temp = realloc(str->str, new_cap);
    if (unlikely(!temp)) {
        fprintf(stderr, "string.c: Realloc failed!\n");
        return false;
    }
    str->str = temp;
    impl_set_str_cap(str, new_cap);
    return true;
}

bool impl_str_grow_exp(struct str_internal *str, const size_t new_len) {
    size_t new_cap = impl_get_str_cap(str);
    if (unlikely(new_cap == 0)) new_cap = PLIB_STR_DEFAULT_SIZE;
    while(new_cap < new_len + 1) {
        size_t temp;
        if (unlikely(__builtin_mul_overflow(new_cap, 2, &temp))) {
            fprintf(stderr, "string.c: Capacity multiplication overflow!\n");
            return false;
        }
        new_cap = temp;
    }
    return impl_str_reserve(str, new_cap);
}

bool impl_str_ncopy(struct str_internal *dest, size_t offset, const char *src, size_t n) {
    const size_t new_len = offset + n;
    if (new_len + 1 > impl_get_str_cap(dest)) {
        if (impl_get_str_user_buffer(dest)) {
            fprintf(stderr, "string.c: Buffer size is too small!\n");
            return false;
        }
        if (unlikely(!impl_str_grow_exp(dest, new_len))) return false;
    }
    memcpy(dest->str + offset, src, n);
    dest->str[new_len] = '\0';
    dest->len = new_len;
    return true;
}

extern inline bool string_copy_cstr(string_t *dest, size_t offset, const char *src) {
    struct str_internal *str = (struct str_internal *)dest;
    return impl_str_ncopy(str, offset, src, strlen(src));
}

extern inline bool string_copy_sv(string_t *dest, size_t offset, const string_view_t *src) {
    struct str_internal *dest_str = (struct str_internal *)dest;
    return impl_str_ncopy(dest_str, offset, string_view_as_cstr(src), string_view_len(src));
}

extern inline bool string_copy(string_t *dest, size_t offset, const string_t *src) {
    const struct str_internal *src_str  = (const struct str_internal *)src;
    struct str_internal *dest_str = (struct str_internal *)dest;
    return impl_str_ncopy(dest_str, offset, src_str->str, src_str->len);
}

extern inline bool string_ncopy_cstrn(string_t *dest, size_t offset, const char *src, size_t n) {
    struct str_internal *str = (struct str_internal *)dest;
    return impl_str_ncopy(str, offset, src, n);
}

extern inline bool string_ncopy_sv(string_t *dest, size_t offset, const string_view_t *src, size_t n) {
    struct str_internal *dest_str = (struct str_internal *)dest;
    return impl_str_ncopy(dest_str, offset, string_view_as_cstr(src), n);
}

extern inline bool string_ncopy(string_t *dest, size_t offset, const string_t *src, size_t n) {
    const struct str_internal *src_str = (const struct str_internal *)src;
    struct str_internal *dest_str = (struct str_internal *)dest;
    return impl_str_ncopy(dest_str, offset, src_str->str, n);
}

bool impl_str_cat(struct str_internal *str, const char *src, size_t n) {
    const size_t new_len = str->len + n + 1;
    if (new_len > impl_get_str_cap(str)) {
        if (impl_get_str_user_buffer(str)) {
            fprintf(stderr, "string.c: Buffer size is too small!\n");
            return false;
        }
        if (unlikely(!impl_str_grow_exp(str, new_len))) return false;
    }
    memcpy(str->str + str->len, src, n);
    str->str[str->len + n] = '\0';
    str->len += n;
    return true;
}

extern inline bool string_cat_cstr(string_t *dest, const char *src) {
    struct str_internal *str = (struct str_internal *)dest;
    return impl_str_cat(str, src, strlen(src));
}

extern inline bool string_cat_sv(string_t *dest, const string_view_t *src) {
    struct str_internal *str = (struct str_internal *)dest;
    return impl_str_cat(str, string_view_as_cstr(src), string_view_len(src));
}

extern inline bool string_cat(string_t *dest, const string_t *src) {
    const struct str_internal *src_str = (const struct str_internal *)src;
    struct str_internal *dest_str = (struct str_internal *)dest;
    return impl_str_cat(dest_str, src_str->str, src_str->len);
}

extern inline bool string_ncat_cstrn(string_t *dest, const char *src, size_t n) {
    struct str_internal *str = (struct str_internal *)dest;
    return impl_str_cat(str, src, n);
}

extern inline bool string_ncat_sv(string_t *dest, const string_view_t *src, size_t n) {
    struct str_internal *str = (struct str_internal *)dest;
    return impl_str_cat(str, string_view_as_cstr(src), n);
}

extern inline bool string_ncat(string_t *dest, const string_t *src, size_t n) {
    const struct str_internal *src_str = (const struct str_internal *)src;
    struct str_internal *dest_str = (struct str_internal *)dest;
    return impl_str_cat(dest_str, src_str->str, n);
}

