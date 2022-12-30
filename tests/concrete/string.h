#ifndef LIBWHEEL_STRING_H
#define LIBWHEEL_STRING_H

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define LIBWHEEL_TYPE  char*
#define LIBWHEEL_ALIAS string

#include <wheel/optional.h>
#include <wheel/bst.h>
#include <wheel/vec.h>
#include <wheel/stack.h>

int64_t compare_string(const char* a, const char* b) {
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

void destroy_string(char* value) {
    free(value);
}

char* clone_string(const char* value) {
    char* result = strdup(value);
    assert(result);
    return result;
}

#endif // LIBWHEEL_STRING_H
