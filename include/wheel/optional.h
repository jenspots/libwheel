#include <stdbool.h>
#include <wheel/macros.h>

#ifdef LIBWHEEL_TYPE
#define T LIBWHEEL_TYPE
#else
#warning "MACRO NOT DEFINED: LIBWHEEL_TYPE"
#endif

#ifndef LIBWHEEL_ALIAS
#warning "MACRO NOT DEFINED: LIBWHEEL_ALIAS"
#endif

#define optional        LIBWHEEL_PREFIX(optional)
#define optional_exists LIBWHEEL_PREFIX(optional_exists)
#define optional_empty  LIBWHEEL_PREFIX(optional_empty)

typedef struct optional {
    bool present;
    T value;
} optional;

optional optional_exists(T value) {
    optional result;
    result.present = true;
    result.value = value;
}

optional optional_empty() {
    optional result;
    result.present = false;
    return result;
}
