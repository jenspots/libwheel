#ifndef LIBWHEEL_STRING_H
#define LIBWHEEL_STRING_H

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define LIBWHEEL_TYPE  char*
#define LIBWHEEL_ALIAS string

#define LIBWHEEL_TRAIT_SHALLOW_COPY
char* string_trait_shallow_copy(const char* value) {
    char* result = strdup(value);
    assert(result);
    return result;
}

#define LIBWHEEL_TRAIT_DEEP_COPY
char* string_trait_deep_copy(const char* value) {
    return string_trait_shallow_copy(value);
}

#define LIBWHEEL_TRAIT_COMPARE
int64_t string_trait_compare(const char* a, const char* b) {
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

#define LIBWHEEL_TRAIT_HASHABLE
uint64_t string_trait_hash(const char* t) {
    exit(-1);
}

#define LIBWHEEL_TRAIT_DESTROY
void string_trait_destroy(char* value) {
    free(value);
}

#include "wheel.h"

#endif // LIBWHEEL_STRING_H