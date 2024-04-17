// clang-format off

#include "wheel/misc/macros.h"

// Conventions: base
#define vec                LIBWHEEL_APPEND(vec)

// Conventions: constructors and destructors
#define vec_init           LIBWHEEL_DEFINE(vec, init)
#define vec_init_ptr       LIBWHEEL_DEFINE(vec, init_ptr)
#define vec_destroy        LIBWHEEL_DEFINE(vec, destroy)
#define vec_destroy_ptr    LIBWHEEL_DEFINE(vec, destroy_ptr)

// Conventions: retrieving elements
#define vec_head           LIBWHEEL_DEFINE(vec, head)
#define vec_head_ptr       LIBWHEEL_DEFINE(vec, head_ptr)
#define vec_last           LIBWHEEL_DEFINE(vec, last)
#define vec_last_ptr       LIBWHEEL_DEFINE(vec, last_ptr)
#define vec_get            LIBWHEEL_DEFINE(vec, get)
#define vec_get_ptr        LIBWHEEL_DEFINE(vec, get_ptr)

// Conventions: serialization
#define vec_serialize_json LIBWHEEL_DEFINE(vec, serialize_json)

// Conventions: iterators
#define vec_iter      LIBWHEEL_DEFINE(vec, iter)
#define vec_begin     LIBWHEEL_DEFINE(vec, begin)
#define vec_rbegin    LIBWHEEL_DEFINE(vec, rbegin)
#define vec_end       LIBWHEEL_DEFINE(vec, end)
#define vec_rend      LIBWHEEL_DEFINE(vec, rend)
#define vec_iget      LIBWHEEL_DEFINE(vec, iget)
#define vec_iget_ptr  LIBWHEEL_DEFINE(vec, iget_ptr)
#define vec_next      LIBWHEEL_DEFINE(vec, next)

// Additional definitions.
#define vec_with_cap       LIBWHEEL_DEFINE(vec, with_cap)
#define vec_pop            LIBWHEEL_DEFINE(vec, pop)
#define vec_set            LIBWHEEL_DEFINE(vec, set)
#define vec_grow           LIBWHEEL_DEFINE(vec, grow)
#define vec_foreach        LIBWHEEL_DEFINE(vec, foreach)
#define vec_comparator     LIBWHEEL_DEFINE(vec, comparator)
#define vec_free_type      LIBWHEEL_DEFINE(vec, free_type)
#define vec_map            LIBWHEEL_DEFINE(vec, map)
#define vec_filter         LIBWHEEL_DEFINE(vec, filter)
#define vec_shallow_copy   LIBWHEEL_DEFINE(vec, shallow_copy)
#define vec_deep_copy      LIBWHEEL_DEFINE(vec, deep_copy)

// clang-format on
