#include <assert.h>
#include <stdint.h>
#include <stdio.h>
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
    int64_t size;
} vec;

typedef struct vec_iter {
    const vec* v;
    int64_t index;
    bool forward;
} vec_iter;

vec vec_init() {
    vec v = {
        .values = malloc(LIBWHEEL_INITIAL_SIZE * sizeof(LIBWHEEL_TYPE)),
        .present = vec_bit_with_cap(LIBWHEEL_INITIAL_SIZE),
        .size = LIBWHEEL_INITIAL_SIZE,
    };
    assert(v.values);
    return v;
}

vec* vec_init_ptr() {
    vec* v = malloc(sizeof(vec));
    assert(v);
    *v = vec_init();
    return v;
}

void vec_destroy(vec* v) {
    assert(v);
    assert(v->values);

    for (int64_t i = 0; i < v->size; ++i) {
        if (vec_bit_get(&v->present, i)) {
            trait_destroy(v->values[i]);
        }
    }

    free(v->values);
    vec_bit_destroy(&v->present);
}

void vec_destroy_ptr(vec** v) {
    assert(v);
    assert(*v);

    // Remove the underlying vector.
    vec_destroy(*v);

    // Free the allocated memory and set the pointer to null.
    free(*v);
    *v = NULL;
}

vec vec_with_cap(int64_t capacity) {
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
optional vec_get(const vec* v, const int64_t index) {
    assert(v);

    if (index >= v->size) {
        return optional_empty();
    }

    if (!vec_bit_get(&v->present, index)) {
        return optional_empty();
    }

    return optional_of(trait_shallow_copy(v->values[index]));
}
#endif // LIBWHEEL_TRAIT_SHALLOW_COPY

inline LIBWHEEL_TYPE* vec_get_ptr(const vec* v, const int64_t index) {
    assert(v);

    if (index >= v->size) {
        return NULL;
    }

    if (!vec_bit_get(&v->present, index)) {
        return NULL;
    }

    return v->values + index;
}

optional vec_pop(vec* v, int64_t index) {
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

void vec_grow(vec* v) {
    assert(v);
    assert(v->values);
    v->size *= LIBWHEEL_VECTOR_SCALAR;
    v->values = realloc(v->values, sizeof(LIBWHEEL_TYPE) * v->size);
    assert(v->values);
}

void vec_set(vec* v, int64_t index, LIBWHEEL_TYPE value) {
    assert(v);

    while (index >= v->size) {
        vec_grow(v);
    }

    vec_bit_set(&v->present, index, true);
    v->values[index] = value;
}

void vec_foreach(vec* v, void (*f)(LIBWHEEL_TYPE)) {
    for (int64_t i = 0; i < v->size; ++i) {
        if (vec_bit_get(&v->present, i)) {
            f(v->values[i]);
        }
    }
}

void vec_map(vec* v, LIBWHEEL_TYPE (*f)(LIBWHEEL_TYPE)) {
    assert(v);

    for (int64_t i = 0; i < v->size; ++i) {
        if (vec_bit_get(&v->present, i)) {
            v->values[i] = f(v->values[i]);
        }
    }
}

void vec_filter(vec* v, bool (*f)(LIBWHEEL_TYPE)) {
    assert(v);

    for (int64_t i = 0; i < v->size; ++i) {
        if (vec_bit_get(&v->present, i) && !f(v->values[i])) {
            vec_bit_set(&v->present, i, false);
            trait_destroy(v->values[i]);
        }
    }
}

#ifdef LIBWHEEL_TRAIT_SHALLOW_COPY
vec vec_shallow_copy(vec* this) {
    vec copy = {
        .values = malloc(sizeof(LIBWHEEL_TYPE) * this->size),
        .present = vec_bit_clone(&this->present),
        .size = this->size,
    };
    assert(copy.values);

    for (int i = 0; i < this->size; ++i) {
        if (vec_bit_get(&this->present, i)) {
            copy.values[i] = trait_shallow_copy(this->values[i]);
        }
    }

    return copy;
}
#endif // LIBWHEEL_TRAIT_SHALLOW_COPY

#ifdef LIBWHEEL_TRAIT_DEEP_COPY
vec vec_deep_copy(const vec* v) {
    vec copy = {
        .values = malloc(sizeof(LIBWHEEL_TYPE) * v->size),
        .present = vec_bit_clone(&v->present),
        .size = v->size,
    };

    for (int i = 0; i < v->size; ++i) {
        if (vec_bit_get(&v->present, i)) {
            copy.values[i] = trait_deep_copy(v->values[i]);
        }
    }

    return copy;
}
#endif // LIBWHEEL_TRAIT_DEEP_COPY

#ifdef LIBWHEEL_TRAIT_SERIALIZE_JSON
int64_t vec_serialize_json(const vec* v, char* target) {
    // Calculate the total length of the JSON string.
    int64_t total_length = 2; // '[' and ']'

    for (int64_t i = 0; i < v->size; ++i) {
        if (vec_bit_get(&v->present, i)) {
           total_length += trait_serialize_json(NULL, v->values[i]);
           total_length += 1; // ','
        }
    }

    if (target == NULL) {
        return total_length;
    }

    // Open the array.
    target[0] = '[';
    int64_t offset = 1;

    // Serialize each value separately.
    for (int64_t i = 0; i < v->size; ++i) {
        if (vec_bit_get(&v->present, i)) {
            offset += trait_serialize_json(target + offset, v->values[i]);
            target[offset] = ',';
            offset += 1;
        }
    }

    // Overwrite the last ',' with ']' if there are any elements.
    if (offset > 1) {
        target[offset - 1] = ']';
    } else {
        target[offset] = ']';
    }

    return total_length;
}
#endif // LIBWHEEL_TRAIT_SERIALIZE_JSON

vec_iter vec_begin(const vec* v) {
    vec_iter result = {
        .v = v,
        .forward = true,
    };

    // Find the first set element.
    for (int i = 0; i < v->size; ++i) {
        if (vec_bit_get(&v->present, i)) {
            result.index = i;
            return result;
        }
    }

    // No elements are found, so the iterator points to the end.
    result.index = v->size;
    return result;
}

vec_iter vec_rbegin(const vec* v) {
    vec_iter result = {
        .v = v,
        .forward = false,
    };

    // Find the last set element.
    for (int64_t i = v->size - 1; i >= 0; --i) {
        if (vec_bit_get(&v->present, i)) {
            result.index = i;
            return result;
        }
    }

    // No elements are found, so the iterator points to the end.
    result.index = -1;
    return result;
}

#ifdef LIBWHEEL_TRAIT_SHALLOW_COPY
LIBWHEEL_TYPE vec_iget(vec_iter* it) {
    if (it->index == -1 || it->index == it->v->size) {
        fprintf(stderr, "vec_iter is out of bounds or invalid.");
        exit(EXIT_FAILURE);
    }

    return it->v->values[it->index];
}
#endif // LIBWHEEL_TRAIT_SHALLOW_COPY

LIBWHEEL_TYPE* vec_iget_ptr(vec_iter* it) {
    if (it->index == -1 || it->index == it->v->size) {
        fprintf(stderr, "vec_iter is out of bounds or invalid.");
        exit(EXIT_FAILURE);
    }

    return it->v->values + it->index;
}

bool vec_next(vec_iter* it) {
    if (it->forward) {
        // Check if finished.
        if (it->index == it->v->size) {
            return false;
        }

        // Find next element.
        for (int64_t i = it->index + 1; i < it->v->size; ++i) {
            if (vec_bit_get(&it->v->present, i)) {
                it->index = i;
                return true;
            }
        }

        // None found.
        it->index = it->v->size;
        return false;
    } else {
        // Check if finished.
        if (it->index == -1) {
            return false;
        }

        // Find next element.
        for (int64_t i = it->index - 1; i >= 0; --i) {
            if (vec_bit_get(&it->v->present, i)) {
                it->index = i;
                return true;
            }
        }

        // None found.
        it->index = -1;
        return false;
    }
}

#ifdef LIBWHEEL_TRAIT_SHALLOW_COPY
optional vec_head(const vec* v) {
    for (int64_t i = 0; i < v->size; ++i) {
        if (vec_bit_get(&v->present, i)) {
            return optional_of(trait_shallow_copy(v->values[i]));
        }
    }

    return optional_empty();
}
#endif // LIBWHEEL_TRAIT_SHALLOW_COPY

LIBWHEEL_TYPE* vec_head_ptr(const vec* v) {
    for (int64_t i = 0; i < v->size; ++i) {
        if (vec_bit_get(&v->present, i)) {
            return v->values + i;
        }
    }

    return NULL;
}

#ifdef LIBWHEEL_TRAIT_SHALLOW_COPY
optional vec_last(const vec* v) {
    for (int64_t i = v->size - 1; i >= 0; --i) {
        if (vec_bit_get(&v->present, i)) {
            return optional_of(trait_shallow_copy(v->values[i]));
        }
    }

    return optional_empty();
}
#endif // LIBWHEEL_TRAIT_SHALLOW_COPY

LIBWHEEL_TYPE* vec_last_ptr(const vec* v) {
    for (int64_t i = v->size - 1; i >= 0; --i) {
        if (vec_bit_get(&v->present, i)) {
            return v->values + i;
        }
    }

    return NULL;
}

#include "wheel/wheel/undef.h"
