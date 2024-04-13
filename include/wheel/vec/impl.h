#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "wheel/misc/bitops.h"

#ifndef LIBWHEEL_INITIAL_SIZE
#define LIBWHEEL_INITIAL_SIZE 32
#endif

#ifndef LIBWHEEL_VECTOR_SCALAR
#define LIBWHEEL_VECTOR_SCALAR 2
#endif

#include "header.h"
#include "wheel/wheel/def.h"

typedef struct vec {
    LIBWHEEL_TYPE* values;
    vec_bit present;
    uint64_t size;
} vec;

vec vec_init() {
    vec v = {
        .values = malloc(LIBWHEEL_INITIAL_SIZE * sizeof(LIBWHEEL_TYPE)),
        .present = vec_bit_with_cap(LIBWHEEL_INITIAL_SIZE),
        .size = LIBWHEEL_INITIAL_SIZE,
    };
    assert(v.values);
    return v;
}

vec vec_with_cap(uint64_t capacity) {
    assert(capacity > 0);
    vec v = {
        .values = malloc(capacity * sizeof(LIBWHEEL_TYPE)),
        .present = vec_bit_with_cap(capacity),
        .size = capacity,
    };
    assert(v.values);
    return v;
}

#ifdef LIBWHEEL_TRAIT_SHALLOW_COPY
optional vec_get(vec* v, uint64_t index) {
    assert(v);

    if (index >= v->size) {
        return optional_empty();
    }

    if (!vec_bit_get(&v->present, index)) {
        return optional_empty();
    }

    return optional_of(shallow_copy(v->values[index]));
}
#endif // LIBWHEEL_TRAIT_SHALLOW_COPY

inline LIBWHEEL_TYPE* vec_get_ptr(const vec* v, const uint64_t index) {
    assert(v);

    if (index >= v->size) {
        return NULL;
    }

    if (!vec_bit_get(&v->present, index)) {
        return NULL;
    }

    return v->values + index;
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
    v->values = realloc(v->values, sizeof(LIBWHEEL_TYPE) * v->size);
    assert(v->values);
}

void vec_set(vec* v, uint64_t index, LIBWHEEL_TYPE value) {
    assert(v);

    while (index >= v->size) {
        vec_grow(v);
    }

    vec_bit_set(&v->present, index, true);
    v->values[index] = value;
}

void vec_foreach(vec* v, void (*f)(LIBWHEEL_TYPE)) {
    for (uint64_t i = 0; i < v->size; ++i) {
        if (vec_bit_get(&v->present, i)) {
            f(v->values[i]);
        }
    }
}

void vec_map(vec* v, LIBWHEEL_TYPE (*f)(LIBWHEEL_TYPE)) {
    assert(v);

    for (uint64_t i = 0; i < v->size; ++i) {
        if (vec_bit_get(&v->present, i)) {
            v->values[i] = f(v->values[i]);
        }
    }
}

void vec_filter(vec* v, bool (*f)(LIBWHEEL_TYPE)) {
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
        .values = malloc(sizeof(LIBWHEEL_TYPE) * v->size),
        .present = vec_bit_clone(&v->present),
        .size = v->size,
    };

    assert(copy.values);
    memcpy(copy.values, v->values, v->size * sizeof(LIBWHEEL_TYPE));

    return copy;
}

vec vec_deep_clone(const vec* v) {
    vec copy = {
        .values = malloc(sizeof(LIBWHEEL_TYPE) * v->size),
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
