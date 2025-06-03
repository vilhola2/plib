#include <stdio.h>
#include <stdlib.h>

// Returns a heap-allocated string. Must bee free'd with free().
char *str_input(FILE *stream) {
    int ch;
    size_t len = 0;
    size_t bufsize = 16;
    char *buffer = malloc(bufsize);
    if (!buffer) {
        fprintf(stderr, "str_input: Malloc failed\n");
        return NULL;
    }
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        buffer[len++] = ch;
        if (len + 1 == bufsize) {
            char *temp = realloc(buffer, (bufsize += 16));
            if (!temp) {
                printf("str_input: Realloc failed\n");
                free(buffer);
                return NULL;
            } else {
                buffer = temp;
            }
        }
    }
    buffer[len] = '\0';
    return buffer;
}

