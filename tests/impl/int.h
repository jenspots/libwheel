#ifndef LIBWHEEL_INT_H
#define LIBWHEEL_INT_H

#include <stdint.h>

#define LIBWHEEL_TYPE  uint64_t
#define LIBWHEEL_ALIAS int
#define LIBWHEEL_TRAIT_SHALLOW_COPY

#include <wheel.h>

int64_t int_compare(const uint64_t a, const uint64_t b) {
    if (a == b) {
        return 0;
    } else if (a > b) {
        return 1;
    } else {
        return -1;
    }
}

uint64_t int_hash(const uint64_t t) {
    return t;
}

void int_destroy(uint64_t t) {
    // pass
}

uint64_t int_clone(const uint64_t t) {
    return t;
}

uint64_t int_shallow_copy(const uint64_t t) {
    return t;
}

#endif // LIBWHEEL_INT_H