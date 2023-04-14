#include "wheel/misc/macros.h"
#include "wheel/optional/header.h"
#include "wheel/optional/def.h"
#include <stdbool.h>

#ifdef LIBWHEEL_TYPE
#define T LIBWHEEL_TYPE
#else
#warning "MACRO NOT DEFINED: LIBWHEEL_TYPE"
#endif

typedef struct optional {
    bool present;
    T value;
} optional;

optional optional_of(T value) {
    optional result;
    result.present = true;
    result.value = value;
    return result;
}

optional optional_empty() {
    optional result;
    result.present = false;
    return result;
}

#undef T
#include "wheel/optional/undef.h"
