#include "wheel/wheel/def.h"

#ifdef LIBWHEEL_TRAIT_COMPARE
int64_t trait_compare(const LIBWHEEL_TYPE, const LIBWHEEL_TYPE);
#endif // LIBWHEEL_TRAIT_COMPARE

#ifdef LIBWHEEL_TRAIT_HASHABLE
uint64_t trait_hash(const LIBWHEEL_TYPE);
#endif // LIBWHEEL_TRAIT_HASHABLE

#ifndef LIBWHEEL_TRAIT_DESTROY
#error "LIBWHEEL_TRAIT_DESTROY must be defined"
#endif
void trait_destroy(LIBWHEEL_TYPE);

#ifdef LIBWHEEL_TRAIT_SHALLOW_COPY
LIBWHEEL_TYPE trait_shallow_copy(const LIBWHEEL_TYPE);
#endif

#ifdef LIBWHEEL_TRAIT_DEEP_COPY
LIBWHEEL_TYPE trait_deep_copy(const LIBWHEEL_TYPE);
#endif

#ifdef LIBWHEEL_TRAIT_STRINGIFY
uint64_t trait_stringify(char* target, const LIBWHEEL_TYPE);
#endif // LIBWHEEL_TRAIT_STRINGIFY

#ifdef LIBWHEEL_TRAIT_SERIALIZE_JSON
uint64_t trait_serialize_json(char* target, const LIBWHEEL_TYPE);
#endif // LIBWHEEL_TRAIT_SERIALIZE_JSON

#include "wheel/wheel/undef.h"
