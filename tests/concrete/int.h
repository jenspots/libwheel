#ifndef LIBWHEEL_INT_H
#define LIBWHEEL_INT_H

#include <stdint.h>

#define LIBWHEEL_TYPE  int
#define LIBWHEEL_ALIAS int

#include <wheel/optional.h>
#include <wheel/bst.h>
#include <wheel/vec.h>
#include <wheel/stack.h>
#include <wheel/types/interface.h>

int64_t compare(const int a, const int b) {
    return b - a;
}

uint64_t hash(const int t) {
    return t;
}

void destroy(int t) {
    // pass
}

int clone(const int t) {
    return t;
}

#undef LIBWHEEL_TYPE
#undef LIBWHEEL_ALIAS

#endif // LIBWHEEL_INT_H
