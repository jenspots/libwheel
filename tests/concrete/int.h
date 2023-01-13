#ifndef LIBWHEEL_INT_H
#define LIBWHEEL_INT_H

#include <stdint.h>

#define LIBWHEEL_TYPE  uint64_t
#define LIBWHEEL_ALIAS int

#include <wheel/wheel.h>

int64_t compare(const uint64_t a, const uint64_t b) {
    if (a == b) {
        return 0;
    } else if (a > b) {
        return 1;
    } else {
        return -1;
    }
}

uint64_t hash(const uint64_t t) {
    return t;
}

void destroy(uint64_t t) {
    // pass
}

uint64_t clone(const uint64_t t) {
    return t;
}

#undef LIBWHEEL_TYPE
#undef LIBWHEEL_ALIAS

#endif // LIBWHEEL_INT_H
