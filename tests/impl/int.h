#ifndef LIBWHEEL_INT_H
#define LIBWHEEL_INT_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define LIBWHEEL_TYPE  uint64_t
#define LIBWHEEL_ALIAS int

#define LIBWHEEL_TRAIT_COMPARE
int64_t int_compare(const uint64_t a, const uint64_t b) {
    if (a == b) {
        return 0;
    } else if (a > b) {
        return 1;
    } else {
        return -1;
    }
}

#define LIBWHEEL_TRAIT_SHALLOW_COPY
uint64_t int_shallow_copy(const uint64_t t) {
    return t;
}

#define LIBWHEEL_TRAIT_HASHABLE
uint64_t int_hash(const uint64_t t) {
    return t;
}

#define LIBWHEEL_TRAIT_STRINGIFY
uint64_t int_stringify(char* target, const uint64_t t) {
    const int size = snprintf(NULL, 0, "%llu", t);

    if (target == NULL) {
        return size;
    }

    return snprintf(target, size + 1, "%llu", t);
}

#define LIBWHEEL_TRAIT_SERIALIZE_JSON
uint64_t int_serialize_json(char* target, const uint64_t t) {
    return int_stringify(target, t);
}

#include <wheel.h>

void int_destroy(uint64_t t) {
    // pass
}

uint64_t int_clone(const uint64_t t) {
    return t;
}

#endif // LIBWHEEL_INT_H