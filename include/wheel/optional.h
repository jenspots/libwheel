#include <stdbool.h>
#include <wheel/macros.h>
#include <wheel/types/optional.h>

#ifdef LIBWHEEL_TYPE
#define T LIBWHEEL_TYPE
#else
#warning "MACRO NOT DEFINED: LIBWHEEL_TYPE"
#endif

#ifndef LIBWHEEL_ALIAS
#warning "MACRO NOT DEFINED: LIBWHEEL_ALIAS"
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
