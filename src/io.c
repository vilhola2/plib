#include <stdio.h>
#include <stdlib.h>
#include <plib/hints.h>

char *str_input(FILE *stream) {
    int ch;
    size_t len = 0;
    size_t bufsize = 16;
    char *buffer = malloc(bufsize);
    if (unlikely(!buffer)) {
        fprintf(stderr, "str_input: Malloc failed\n");
        return NULL;
    }
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        buffer[len++] = ch;
        if (len + 1 == bufsize) {
            char *temp = realloc(buffer, (bufsize *= 2));
            if (unlikely(!temp)) {
                fprintf(stderr, "str_input: Realloc failed\n");
                free(buffer);
                return NULL;
            }
            buffer = temp;
        }
    }
    if (unlikely(len == 0 && ch == EOF)) {
        free(buffer);
        return NULL;
    }
    buffer[len] = '\0';
    return buffer;
}
