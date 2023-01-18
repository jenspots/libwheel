#ifndef LIBWHEEL_INT_H
#define LIBWHEEL_INT_H

#include <stdint.h>

#define LIBWHEEL_TYPE  uint64_t
#define LIBWHEEL_ALIAS int

#include <wheel/wheel.h>

#undef LIBWHEEL_TYPE
#undef LIBWHEEL_ALIAS

int64_t compare_int(const uint64_t a, const uint64_t b) {
    if (a == b) {
        return 0;
    } else if (a > b) {
        return 1;
    } else {
        return -1;
    }
}

uint64_t hash_int(const uint64_t t) {
    return t;
}

void destroy_int(uint64_t t) {
    // pass
}

uint64_t clone_int(const uint64_t t) {
    return t;
}

#endif // LIBWHEEL_INT_H