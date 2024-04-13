#include "wheel/wheel/def.h"

typedef struct vec vec;

/**
 * Initialize a new vector with the default capacity.
 * @note The default capacity is defined by LIBWHEEL_INITIAL_SIZE.
 * @return A stack allocated vector.
 * @see `vec_init_ptr` for a heap allocated vector.
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

#ifdef LIBWHEEL_TRAIT_SHALLOW_COPY
/**
 * Shallow copy the value at the given index in a vector.
 * @param v The vector to get the value from.
 * @param index The index of the element to be copied.
 * @return A shallow copy of the value at the given index embedded in an
 * optional. If the element doesn't exist, or the index is out of bounds
 * the optional will be empty.
 * @note This function requires the `LIBWHEEL_TRAIT_SHALLOW_COPY` trait.
 * @see `vec_get_ptr` for a pointer to the value.
 */
optional vec_get(const vec* v, uint64_t index);
#endif

/**
 * Get a reference to the value at the given index in a vector.
 * @param v The vector to get the value from.
 * @param index The index of the element to be referenced.
 * @return A pointer to the value at the given index. If the element doesn't
 * exist, or the index is out of bounds, the pointer will be null.
 * @see `vec_get` for a shallow copy of the value.
 */
LIBWHEEL_TYPE* vec_get_ptr(const vec* v, uint64_t index);

#ifdef LIBWHEEL_TRAIT_SERIALIZE_JSON
/**
 * Serialize a vector to a JSON string.
 * @param v The vector to serialize.
 * @param target A pointer to the target buffer. The caller is responsible
 * for allocating the buffer. If the target is null, the function will return
 * the required buffer size.
 * @return The amount of characters written if the target is non null,
 * otherwise the required buffer size is returned.
 * @note This function requires the `LIBWHEEL_TRAIT_SERIALIZE_JSON` trait.
 */
uint64_t vec_serialize_json(const vec* v, char* target);
#endif // LIBWHEEL_TRAIT_SERIALIZE_JSON

vec vec_with_cap(uint64_t capacity);

optional vec_pop(vec* v, uint64_t index);

void vec_grow(vec* v);

void vec_set(vec* v, uint64_t index, LIBWHEEL_TYPE value);

void vec_foreach(vec* v, void (*f)(LIBWHEEL_TYPE));

void vec_map(vec* v, LIBWHEEL_TYPE (*f)(LIBWHEEL_TYPE));

void vec_filter(vec* v, bool (*f)(LIBWHEEL_TYPE));

vec vec_shallow_clone(vec* v);

vec vec_deep_clone(const vec* v);


#include "wheel/wheel/undef.h"
