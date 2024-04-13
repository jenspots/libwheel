#include "wheel/wheel/def.h"

int64_t compare(const LIBWHEEL_TYPE, const LIBWHEEL_TYPE);

uint64_t hash(const LIBWHEEL_TYPE);

void destroy(LIBWHEEL_TYPE);

LIBWHEEL_TYPE clone(const LIBWHEEL_TYPE);

#ifdef LIBWHEEL_TRAIT_SHALLOW_COPY
LIBWHEEL_TYPE shallow_copy(const LIBWHEEL_TYPE);
#endif

#include "wheel/wheel/undef.h"
