#include "wheel/wheel/def.h"

typedef struct vec vec;

vec vec_init();

vec vec_with_cap(uint64_t capacity);

#ifdef LIBWHEEL_TRAIT_SHALLOW_COPY
optional vec_get(vec* v, uint64_t index);
#endif

LIBWHEEL_TYPE* vec_get_ptr(const vec* v, uint64_t index);

optional vec_pop(vec* v, uint64_t index);

void vec_delete(vec* v);

void vec_grow(vec* v);

void vec_set(vec* v, uint64_t index, LIBWHEEL_TYPE value);

void vec_foreach(vec* v, void (*f)(LIBWHEEL_TYPE));

void vec_map(vec* v, LIBWHEEL_TYPE (*f)(LIBWHEEL_TYPE));

void vec_filter(vec* v, bool (*f)(LIBWHEEL_TYPE));

vec vec_shallow_clone(vec* v);

vec vec_deep_clone(const vec* v);

#include "wheel/wheel/undef.h"
