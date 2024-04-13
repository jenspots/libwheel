#include "wheel/misc/macros.h"

#define destroy        LIBWHEEL_PREPEND(destroy)
#define clone          LIBWHEEL_PREPEND(clone)

#define trait_compare        LIBWHEEL_PREPEND(trait_compare)
#define trait_hash           LIBWHEEL_PREPEND(trait_hash)
#define trait_shallow_copy   LIBWHEEL_PREPEND(trait_shallow_copy)
#define trait_stringify      LIBWHEEL_PREPEND(trait_stringify)
#define trait_serialize_json LIBWHEEL_PREPEND(trait_serialize_json)
