#ifndef LIBWHEEL_VEC_INT_H
#define LIBWHEEL_VEC_INT_H

#include "int.h"

#define LIBWHEEL_TYPE  vec_int
#define LIBWHEEL_ALIAS vec_int

#define LIBWHEEL_TRAIT_SHALLOW_COPY
vec_int vec_int_trait_shallow_copy(const vec_int v) {
    vec_int result = vec_int_init();

    for (uint64_t i = 0; i < v.size; ++i) {
        vec_bit_set(&result.present, i, vec_bit_get(&v.present, i));
        result.values[i] = v.values[i];
    }

    return result;
}

#include "wheel.h"

void vec_int_destroy(vec_int v) {
    vec_int_delete(&v);
}

vec_int vec_int_clone(const vec_int v) {
    return vec_int_deep_clone(&v);
}

#endif
