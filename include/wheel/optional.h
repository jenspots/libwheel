#include <stdbool.h>
#include <wheel/misc/macros.h>
#include <wheel/types/optional.h>
#include <wheel/def/optional.h>

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
#include <wheel/undef/optional.h>
