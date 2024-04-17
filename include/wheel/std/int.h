#ifndef LIBWHEEL_INT_H
#define LIBWHEEL_INT_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define LIBWHEEL_TYPE  int
#define LIBWHEEL_ALIAS int

#define LIBWHEEL_TRAIT_COMPARE
int64_t int_trait_compare(const int a, const int b) {
    if (a == b) {
        return 0;
    } else if (a > b) {
        return 1;
    } else {
        return -1;
    }
}

#define LIBWHEEL_TRAIT_SHALLOW_COPY
int int_trait_shallow_copy(const int t) {
    return t;
}

#define LIBWHEEL_TRAIT_DEEP_COPY
int int_trait_deep_copy(const int t) {
    return t;
}

#define LIBWHEEL_TRAIT_HASHABLE
uint64_t int_trait_hash(const int t) {
    return t;
}

#define LIBWHEEL_TRAIT_STRINGIFY
uint64_t int_trait_stringify(char* target, const int t) {
    const int size = snprintf(NULL, 0, "%d", t);

    if (target == NULL) {
        return size;
    }

    return snprintf(target, size + 1, "%d", t);
}

#define LIBWHEEL_TRAIT_SERIALIZE_JSON
uint64_t int_trait_serialize_json(char* target, const int t) {
    return int_trait_stringify(target, t);
}

#define LIBWHEEL_TRAIT_DESTROY
void int_trait_destroy(const int t __attribute__((unused))) {
    // Do nothing.
}

#include <wheel.h>

#endif // LIBWHEEL_INT_H
