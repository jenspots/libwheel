#include "wheel/wheel/def.h"

/**
 * A dynamically sized array which may contain empty slots.
 */
typedef struct vec vec;

/**
 * A vector iterator.
 */
typedef struct vec_iter vec_iter;

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
 * retrieve the first element in a vector.
 * @param v the vector to get the value from.
 * @return a shallow copy of the first element in the vector, or
 * `optional_empty` if it doesn't exist.
 * @note this function requires the `LIBWHEEL_TRAIT_SHALLOW_COPY` trait.
 */
optional vec_head(const vec* v);
#endif // LIBWHEEL_TRAIT_SHALLOW_COPY

/**
 * Retrieve the first element in a vector.
 * @param v The vector to get the value from.
 * @return A pointer to the first element in the vector, or null if it doesn't exist.
 */
LIBWHEEL_TYPE* vec_head_ptr(const vec* v);

#ifdef LIBWHEEL_TRAIT_SHALLOW_COPY
/**
 * Retrieve the last element in a vector.
 * @param v The vector to get the value from.
 * @return A shallow copy of the last element in the vector, or
 * `optional_empty` if it doesn't exist.
 * @note This function requires the `LIBWHEEL_TRAIT_SHALLOW_COPY` trait.
 */
optional vec_last(const vec* v);
#endif // LIBWHEEL_TRAIT_SHALLOW_COPY

/**
 * Retrieve the last element in a vector.
 * @param v The vector to get the value from.
 * @return A pointer to the last element in the vector, or null if it doesn't exist.
 */
LIBWHEEL_TYPE* vec_last_ptr(const vec* v);

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

/**
 * Create an iterator which traverses the vector forwards.
 * @param v The vector to create the iterator for.
 * @return An iterator pointing to the first element in the vector.
 */
vec_iter vec_begin(const vec* v);

/**
 * Create an iterator which traverses the vector backwards.
 * @param v The vector to create the iterator for.
 * @return An iterator pointing to the last element in the vector.
 */
vec_iter vec_rbegin(const vec* v);

/**
 * Retrieve an element based off the current position of the iterator.
 * @param it The iterator to retrieve the element from.
 * @return A shallow copy of the element at the current position.
 * @note This function requires the `LIBWHEEL_TRAIT_OPTIONAL` trait.
 * @note Errors if the iterator is out of bounds or invalid.
 */
LIBWHEEL_TYPE vec_iget(vec_iter* it);

/**
 * Retrieve a pointer to an element based off the current position of the iterator.
 * @param it The iterator to retrieve the element from.
 * @return A pointer to the element at the current position.
 * @note Errors if the iterator is out of bounds or invalid.
 */
LIBWHEEL_TYPE* vec_iget_ptr(vec_iter* it);

/**
 * Advances the iterator to the next element.
 * @param it The iterator to advance.
 * @return True if the iterator points to another element, false otherwise.
 */
bool vec_next(vec_iter* it);

vec vec_with_cap(int64_t capacity);

optional vec_pop(vec* v, uint64_t index);

void vec_grow(vec* v);

void vec_set(vec* v, uint64_t index, LIBWHEEL_TYPE value);

void vec_foreach(vec* v, void (*f)(LIBWHEEL_TYPE));

void vec_map(vec* v, LIBWHEEL_TYPE (*f)(LIBWHEEL_TYPE));

void vec_filter(vec* v, bool (*f)(LIBWHEEL_TYPE));

#ifdef LIBWHEEL_TRAIT_SHALLOW_COPY
vec vec_shallow_copy(vec* this);
#endif // LIBWHEEL_TRAIT_SHALLOW_COPY

#ifdef LIBWHEEL_TRAIT_DEEP_COPY
vec vec_deep_copy(const vec* v);
#endif // LIBWHEEL_TRAIT_DEEP_COPY

#include "wheel/wheel/undef.h"
