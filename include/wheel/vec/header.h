#include "wheel/wheel/def.h"

typedef struct vec vec;

/**
 * Initialize a new vector with the default capacity.
 * @note The default capacity is defined by LIBWHEEL_INITIAL_SIZE.
 * @return A stack allocated vector.
 * @see vec_init_ptr for a heap allocated vector.
 */
vec vec_init();

/**
 * Initialize a new vector with the default capacity.
 * @note The default capacity is defined by LIBWHEEL_INITIAL_SIZE.
 * @return A heap allocated vector.
 * @see `vec_init` for a stack allocated vector.
 */
vec* vec_init_ptr();

/**
 * Destroy a stack-allocated vector and free its memory.
 * @param v The vector to destroy.
 * @see `vec_destroy_ptr` for heap allocated vectors.
 */
void vec_destroy(vec* v);

/**
 * Destroy a heap-allocated vector and free its memory.
 * @param v The vector to destroy.
 * @see `vec_destroy` for stack allocated vectors.
 */
void vec_destroy_ptr(vec** v);

vec vec_with_cap(uint64_t capacity);

#ifdef LIBWHEEL_TRAIT_SHALLOW_COPY
optional vec_get(vec* v, uint64_t index);
#endif

LIBWHEEL_TYPE* vec_get_ptr(const vec* v, uint64_t index);

optional vec_pop(vec* v, uint64_t index);


void vec_grow(vec* v);

void vec_set(vec* v, uint64_t index, LIBWHEEL_TYPE value);

void vec_foreach(vec* v, void (*f)(LIBWHEEL_TYPE));

void vec_map(vec* v, LIBWHEEL_TYPE (*f)(LIBWHEEL_TYPE));

void vec_filter(vec* v, bool (*f)(LIBWHEEL_TYPE));

vec vec_shallow_clone(vec* v);

vec vec_deep_clone(const vec* v);

#ifdef LIBWHEEL_TRAIT_SERIALIZE_JSON
uint64_t vec_serialize_json(const vec* v, char* target);
#endif // LIBWHEEL_TRAIT_SERIALIZE_JSON

#include "wheel/wheel/undef.h"
