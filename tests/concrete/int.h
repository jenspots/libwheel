#ifndef LIBWHEEL_INT_H
#define LIBWHEEL_INT_H

#include <stdint.h>

int64_t compare_int(int a, int b) {
    return b - a;
}

uint64_t hash_int(int t) {
    return t;
}

void destroy_int(int t) {
    // pass
}

int clone_int(int t) {
    return t;
}

#endif // LIBWHEEL_INT_H
