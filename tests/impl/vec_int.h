#ifndef LIBWHEEL_VEC_INT_H
#define LIBWHEEL_VEC_INT_H

#include "int.h"

#define LIBWHEEL_TYPE vec_int
#define LIBWHEEL_ALIAS vec_int

#include <wheel.h>

int64_t vec_int_compare(const vec_int a, const vec_int b) {
    return 0;
}

uint64_t vec_int_hash(const vec_int v) {
    return 0;
}

void vec_int_destroy(vec_int v) {
    vec_int_delete(&v);
}

vec_int vec_int_clone(const vec_int v) {
    return vec_int_deep_clone(&v);
}

#endif
