#ifndef LIBWHEEL_BITOPS_H
#define LIBWHEEL_BITOPS_H

#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define N_BITS(i) (i == 0 ? 0 : i == 64 ? UINT_MAX \
                                        : ((uint64_t)1 << (uint64_t)(i)) - 1)

#define HEAD(i, x) (((uint64_t)x) & N_BITS((uint64_t)i))
#define TAIL(i, x) (i == 64 ? (x) : (((uint64_t)x) & ~(N_BITS(64 - (i)-1))) >> (64 - (i)))

#define NTH_BIT(i)        ((1UL << (i)))
#define NTH_BIT_SET(i, x) ((1 << (i)) & (x)) > 0

#define POW2(i) NTH_BIT(i)

#ifndef LIBWHEEL_BITVECTOR_SCALAR
#define LIBWHEEL_BITVECTOR_SCALAR 2
#endif

typedef struct vec_bit {
    uint64_t* values;
    uint64_t size;
} vec_bit;

vec_bit vec_bit_init() {
    vec_bit v = {
        .values = calloc(1, sizeof(uint64_t)),
        .size = 1,
    };
    assert(v.values);
    return v;
}

vec_bit vec_bit_with_cap(uint64_t capacity) {
    assert(capacity > 0);

    // How long the array must be.
    uint64_t length = (capacity / 64) + (capacity % 64 == 0 ? 0 : 1);
    vec_bit v = {
        .values = calloc(length, sizeof(uint64_t)),
        .size = capacity,
    };
    assert(v.values);
    return v;
}

bool vec_bit_get(vec_bit* v, uint64_t index) {
    assert(v);

    if (index > v->size) {
        return false;
    }

    return (NTH_BIT(index % 64) & v->values[index / 64]) > 0;
}

void vec_bit_delete(vec_bit* v) {
    assert(v);
    assert(v->values);
    free(v->values);
}

void vec_bit_grow(vec_bit* v) {
    assert(v);
    v->size *= LIBWHEEL_BITVECTOR_SCALAR;
    uint64_t length = (v->size / 64) + (v->size % 64 == 0 ? 0 : 1);
    v->values = realloc(v->values, sizeof(uint64_t) * length);
    assert(v->values);
}

void vec_bit_set(vec_bit* v, uint64_t index, bool value) {
    assert(v);

    while (index >= v->size) {
        vec_bit_grow(v);
    }

    if (value) {
        v->values[index / 64] |= NTH_BIT(index % 64);
    } else {
        v->values[index / 64] &= ~NTH_BIT(index % 64);
    }
}

#endif // LIBWHEEL_BITOPS_H
