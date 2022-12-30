#include <wheel/macros.h>
#include <wheel/misc/warnings.h>

#define compare LIBWHEEL_PREFIX(compare)
#define hash    LIBWHEEL_PREFIX(hash)
#define destroy LIBWHEEL_PREFIX(destroy)
#define clone   LIBWHEEL_PREFIX(clone)

int64_t compare(const LIBWHEEL_TYPE, const LIBWHEEL_TYPE);

uint64_t hash(const LIBWHEEL_TYPE);

void destroy(LIBWHEEL_TYPE);

LIBWHEEL_TYPE clone(const LIBWHEEL_TYPE);
