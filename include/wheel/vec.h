#include <stdint.h>
#include <stdlib.h>
#include <wheel/macros.h>
#include <wheel/types/optional.h>
#include <wheel/types/vec.h>

#ifdef LIBWHEEL_TYPE
#define T LIBWHEEL_TYPE
#else
#warning "MACRO NOT DEFINED: LIBWHEEL_TYPE"
#endif

#ifndef LIBWHEEL_ALIAS
#warning "MACRO NOT DEFINED: LIBWHEEL_ALIAS"
#endif

#ifndef LIBWHEEL_INITIAL_SIZE
#define LIBWHEEL_INITIAL_SIZE 32
#endif

#ifndef LIBWHEEL_VECTOR_SCALAR
#define LIBWHEEL_VECTOR_SCALAR 2
#endif

#ifndef LIBWHEEL_COMPARATOR
int vec_comparator(const T a, const T b) { return b - a; }
#endif

#ifndef LIBWHEEL_FREE_T
void vec_free_type(T value) { }
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
            vec_free_type(element.value);
        }
    }
    free(v->values);
}

void vec_grow(vec* v) {
    assert(v);
    assert(v->values);
    v->size *= LIBWHEEL_VECTOR_SCALAR;
    v->values = realloc(
        v->values,
        sizeof(optional) * v->size
    );
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

#undef T
