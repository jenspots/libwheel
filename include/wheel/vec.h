#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <wheel/macros.h>
#include <wheel/types/optional.h>
#include <wheel/types/interface.h>
#include <wheel/types/vec.h>

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

typedef struct vec vec;

typedef struct vec {
    optional* values;
    uint64_t size;
} vec;

vec vec_init() {
    vec v = {
        .values = calloc(LIBWHEEL_INITIAL_SIZE, sizeof(optional)),
        .size = LIBWHEEL_INITIAL_SIZE,
    };
    assert(v.values);
    return v;
}

vec vec_with_cap(uint64_t capacity) {
    assert(capacity > 0);
    vec v = {
        .values = calloc(capacity, sizeof(optional)),
        .size = capacity,
    };
    assert(v.values);
    return v;
}

optional vec_get(vec* v, uint64_t index) {
    assert(v);

    if (index < v->size) {
        return v->values[index];
    }

    return optional_empty();
}

optional vec_pop(vec* v, uint64_t index) {
    assert(v);

    if (index < v->size) {
        optional result = v->values[index];
        v->values[index] = optional_empty();
        return result;
    }

    return optional_empty();
}

void vec_delete(vec* v) {
    assert(v);
    assert(v->values);

    for (uint64_t i = 0; i < v->size; ++i) {
        optional element = vec_get(v, i);
        if (element.present) {
            destroy(element.value);
        }
    }
    free(v->values);
}

void vec_grow(vec* v) {
    assert(v);
    assert(v->values);
    v->size *= LIBWHEEL_VECTOR_SCALAR;
    v->values = realloc(v->values, sizeof(optional) * v->size);
    assert(v->values);
}

void vec_set(vec* v, uint64_t index, T value) {
    assert(v);

    while (index >= v->size) {
        vec_grow(v);
    }

    v->values[index] = optional_of(value);
}

void vec_foreach(vec* v, void (*f)(T)) {
    for (uint64_t i = 0; i < v->size; ++i) {
        optional element = vec_get(v, i);
        if (element.present) {
            f(element.value);
        }
    }
}

void vec_map(vec* v, T (*f)(T)) {
    assert(v);

    for (uint64_t i = 0; i < v->size; ++i) {
        optional element = vec_get(v, i);
        if (element.present) {
            v->values[i] = optional_of(f(element.value));
        }
    }
}

void vec_filter(vec* v, bool(*f)(T)) {
    assert(v);

    for (uint64_t i = 0; i < v->size; ++i) {
        optional element = vec_get(v, i);
        if (element.present && !f(element.value)) {
            destroy(element.value);
            v->values[i] = optional_empty();
        }
    }
}

vec vec_shallow_clone(vec* v) {
    vec copy = {
        .values = malloc(sizeof(T) * v->size),
        .size = v->size,
    };

    assert(copy.values);
    memcpy(copy.values, v->values, v->size * sizeof(T));

    return copy;
}

vec vec_deep_clone(vec* v) {
    vec copy = {
        .values = malloc(sizeof(T) * v->size),
        .size = v->size,
    };

    for (int i = 0; i < v->size; ++i) {
        optional element = vec_get(v, i);
        if (element.present) {
            copy.values[i] = optional_of(clone(element.value));
        } else {
            copy.values[i] = element;
        }
    }

    return copy;
}

#undef T
