#include "header.h"
#include "wheel/interface/header.h"
#include "wheel/misc/macros.h"
#include "wheel/optional/header.h"
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "def.h"
#include "wheel/misc/bitops.h"
#include "wheel/interface/def.h"
#include "wheel/optional/def.h"

#ifdef LIBWHEEL_TYPE
#define T LIBWHEEL_TYPE
#else
#warning "MACRO NOT DEFINED: LIBWHEEL_TYPE"
#endif

#ifndef LIBWHEEL_INITIAL_SIZE
#define LIBWHEEL_INITIAL_SIZE 32
#endif

#ifndef LIBWHEEL_VECTOR_SCALAR
#define LIBWHEEL_VECTOR_SCALAR 2
#endif

typedef struct vec {
    T* values;
    vec_bit present;
    uint64_t size;
} vec;

vec vec_init() {
    vec v = {
        .values = malloc(LIBWHEEL_INITIAL_SIZE * sizeof(T)),
        .present = vec_bit_with_cap(LIBWHEEL_INITIAL_SIZE),
        .size = LIBWHEEL_INITIAL_SIZE,
    };
    assert(v.values);
    return v;
}

vec vec_with_cap(uint64_t capacity) {
    assert(capacity > 0);
    vec v = {
        .values = malloc(capacity * sizeof(T)),
        .present = vec_bit_with_cap(capacity),
        .size = capacity,
    };
    assert(v.values);
    return v;
}

optional vec_get(vec* v, uint64_t index) {
    assert(v);

    if (index >= v->size) {
        return optional_empty();
    }

    if (!vec_bit_get(&v->present, index)) {
        return optional_empty();
    }

    return optional_of(v->values[index]);
}

optional vec_pop(vec* v, uint64_t index) {
    assert(v);

    if (index >= v->size) {
        return optional_empty();
    }

    if (!vec_bit_get(&v->present, index)) {
        return optional_empty();
    }

    optional result = optional_of(v->values[index]);
    vec_bit_set(&v->present, index, false);
    return result;
}

void vec_delete(vec* v) {
    assert(v);
    assert(v->values);

    for (uint64_t i = 0; i < v->size; ++i) {
        if (vec_bit_get(&v->present, i)) {
            destroy(v->values[i]);
        }
    }

    free(v->values);
    vec_bit_delete(&v->present);
}

void vec_grow(vec* v) {
    assert(v);
    assert(v->values);
    v->size *= LIBWHEEL_VECTOR_SCALAR;
    v->values = realloc(v->values, sizeof(T) * v->size);
    assert(v->values);
}

void vec_set(vec* v, uint64_t index, T value) {
    assert(v);

    while (index >= v->size) {
        vec_grow(v);
    }

    vec_bit_set(&v->present, index, true);
    v->values[index] = value;
}

void vec_foreach(vec* v, void (*f)(T)) {
    for (uint64_t i = 0; i < v->size; ++i) {
        if (vec_bit_get(&v->present, i)) {
            f(v->values[i]);
        }
    }
}

void vec_map(vec* v, T (*f)(T)) {
    assert(v);

    for (uint64_t i = 0; i < v->size; ++i) {
        if (vec_bit_get(&v->present, i)) {
            v->values[i] = f(v->values[i]);
        }
    }
}

void vec_filter(vec* v, bool (*f)(T)) {
    assert(v);

    for (uint64_t i = 0; i < v->size; ++i) {
        if (vec_bit_get(&v->present, i) && !f(v->values[i])) {
            vec_bit_set(&v->present, i, false);
            destroy(v->values[i]);
        }
    }
}

vec vec_shallow_clone(vec* v) {
    vec copy = {
        .values = malloc(sizeof(T) * v->size),
        .present = vec_bit_clone(&v->present),
        .size = v->size,
    };

    assert(copy.values);
    memcpy(copy.values, v->values, v->size * sizeof(T));

    return copy;
}

vec vec_deep_clone(vec* v) {
    vec copy = {
        .values = malloc(sizeof(T) * v->size),
        .present = vec_bit_clone(&v->present),
        .size = v->size,
    };

    for (int i = 0; i < v->size; ++i) {
        if (vec_bit_get(&v->present, i)) {
            copy.values[i] = clone(v->values[i]);
        }
    }

    return copy;
}

#include "wheel/wheel/undef.h"
