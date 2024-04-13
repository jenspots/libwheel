#include "wheel/wheel/def.h"

#ifdef LIBWHEEL_TRAIT_COMPARE
int64_t compare(const LIBWHEEL_TYPE, const LIBWHEEL_TYPE);
#endif // LIBWHEEL_TRAIT_COMPARE

#ifdef LIBWHEEL_TRAIT_HASHABLE
uint64_t hash(const LIBWHEEL_TYPE);
#endif // LIBWHEEL_TRAIT_HASHABLE

void destroy(LIBWHEEL_TYPE);

LIBWHEEL_TYPE clone(const LIBWHEEL_TYPE);

#ifdef LIBWHEEL_TRAIT_SHALLOW_COPY
LIBWHEEL_TYPE shallow_copy(const LIBWHEEL_TYPE);
#endif

#ifdef LIBWHEEL_TRAIT_STRINGIFY
uint64_t stringify(char* target, const LIBWHEEL_TYPE);
#endif // LIBWHEEL_TRAIT_STRINGIFY

#ifdef LIBWHEEL_TRAIT_SERIALIZE_JSON
uint64_t serialize_json(char* target, const LIBWHEEL_TYPE);
#endif // LIBWHEEL_TRAIT_SERIALIZE_JSON

#include "wheel/wheel/undef.h"
