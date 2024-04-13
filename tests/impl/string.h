#ifndef LIBWHEEL_STRING_H
#define LIBWHEEL_STRING_H

#include <stdint.h>

#define LIBWHEEL_TYPE  char*
#define LIBWHEEL_ALIAS string
#define LIBWHEEL_TRAIT_SHALLOW_COPY

#include <wheel.h>

int64_t string_compare(const char* a, const char* b) {
    assert(a);
    assert(b);

    uint64_t i = 0;
    while (true) {
        if (a[i] > b[i]) {
            return 1;
        } else if (a[i] < b[i]) {
            return -1;
        } else if (a[i] == '\0') {
            return 0;
        }
        i += 1;
    }
}

uint64_t string_hash(const char* t) {
    exit(-1);
}

void string_destroy(char* value) {
    free(value);
}

char* string_clone(const char* value) {
    char* result = strdup(value);
    assert(result);
    return result;
}

char* string_shallow_copy(const char* value) {
    char* result = strdup(value);
    assert(result);
    return result;
}

#endif // LIBWHEEL_STRING_H
