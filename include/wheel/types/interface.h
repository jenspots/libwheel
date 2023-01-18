#include <wheel/def/wheel.h>

int64_t compare(const LIBWHEEL_TYPE, const LIBWHEEL_TYPE);

uint64_t hash(const LIBWHEEL_TYPE);

void destroy(LIBWHEEL_TYPE);

LIBWHEEL_TYPE clone(const LIBWHEEL_TYPE);

#include <wheel/undef/wheel.h>
