#ifndef LIBWHEEL_INT_H
#define LIBWHEEL_INT_H

#include <stdint.h>

#define LIBWHEEL_TYPE  int
#define LIBWHEEL_ALIAS int

#include <wheel/optional.h>
#include <wheel/bst.h>
#include <wheel/vec.h>
#include <wheel/stack.h>

int64_t compare_int(const int a, const int b) {
    return b - a;
}

uint64_t hash_int(const int t) {
    return t;
}

void destroy_int(int t) {
    // pass
}

int clone_int(const int t) {
    return t;
}

#endif // LIBWHEEL_INT_H
