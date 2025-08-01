#include <stdio.h>
#include <plib/hints.h>
#include <plib/string.h>

bool string_input(string_t *str, FILE *stream) {
    int ch;
    size_t len = 0;
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (!string_copy_ch(str, len++, ch)) return false;
    }
    if (unlikely(len == 0 && ch == EOF)) {
        fprintf(stderr, "string_input: No characters read before EOF\n");
        return false;
    }
    return true;
}
