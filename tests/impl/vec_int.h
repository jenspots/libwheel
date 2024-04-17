#ifndef LIBWHEEL_VEC_INT_H
#define LIBWHEEL_VEC_INT_H

#include <wheel/std/int.h>

#define LIBWHEEL_TYPE  vec_int
#define LIBWHEEL_ALIAS vec_int

#define LIBWHEEL_TRAIT_SHALLOW_COPY
vec_int vec_int_trait_shallow_copy(const vec_int v) {
    vec_int result = vec_int_init();

    for (int64_t i = 0; i < v.size; ++i) {
        vec_bit_set(&result.present, i, vec_bit_get(&v.present, i));
        result.values[i] = v.values[i];
    }

    return result;
}

#define LIBWHEEL_TRAIT_DEEP_COPY
vec_int vec_int_trait_deep_copy(const vec_int v) {
    return vec_int_trait_shallow_copy(v);
}

#define LIBWHEEL_TRAIT_DESTROY
void vec_int_trait_destroy(vec_int v) {
    vec_int_destroy(&v);
}

#include "wheel.h"

#endif
