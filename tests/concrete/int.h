#ifndef LIBWHEEL_INT_H
#define LIBWHEEL_INT_H

#include <stdint.h>

#define LIBWHEEL_TYPE  uint64_t
#define LIBWHEEL_ALIAS int

#include <wheel/optional.h>
#include <wheel/bst.h>
#include <wheel/vec.h>
#include <wheel/eht.h>
#include <wheel/stack.h>
#include <wheel/types/interface.h>

int64_t compare(const uint64_t a, const uint64_t b) {
    return a < b;
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
