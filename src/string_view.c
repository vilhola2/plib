#include <stdio.h>
#include <string.h>
#include <plib/string.h>
#include <plib/hints.h>
#include "include/string_internal.h"

extern inline size_t string_view_len(const string_view_t *sv) {
    const struct sv_internal *temp = (const struct sv_internal *)sv;
    return string_len(temp->view) - temp->offset;
}

extern inline bool string_view_set_offset(string_view_t *sv, const size_t new_offset) {
    if (unlikely(new_offset > PLIB_STR_MAX || new_offset > string_view_len(sv))) {
        fprintf(stderr, "string_view.c: Offset is too large!\n");
        return false;
    }
    ((struct sv_internal *)sv)->offset = new_offset;
    return true;
}

extern inline size_t string_view_get_offset(const string_view_t *sv) {
    return ((struct sv_internal *)sv)->offset;
}

extern inline const char *string_view_as_cstr(const string_view_t *sv) {
    const struct sv_internal *temp = (const struct sv_internal *)sv;
    return string_as_cstr(temp->view) + temp->offset;
}

int string_view_cmp(const string_view_t *a, const string_view_t *b) {
    const char  *a_str = string_view_as_cstr(a),
                *b_str = string_view_as_cstr(b);
    const size_t a_len = string_view_len(a),
                 b_len = string_view_len(b);
    const size_t min_len = (a_len < b_len ? a_len : b_len);
    const int cmp = strncmp(a_str, b_str, min_len);
    if (cmp != 0) return cmp;
    if (a_len < b_len) return -1;
    if (a_len > b_len) return 1;
    return 0;
}

