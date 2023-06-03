#include "header.h"
#include "wheel/interface/header.h"
#include <stdlib.h>

#include "def.h"
#include "wheel/interface/def.h"
#include "wheel/optional/def.h"

#ifdef LIBWHEEL_TYPE
#define T LIBWHEEL_TYPE
#else
#warning "MACRO NOT DEFINED: LIBWHEEL_TYPE"
#endif

typedef struct rc {
    uint64_t *counter;
    T value;
} rc;

rc rc_init(T value) {
    rc result;

    // Initialize the counter to one.
    result.counter = malloc(sizeof(uint64_t));
    *result.counter = 1;

    // Keep track of the pointer itself.
    result.value = value;

    // That's it.
    return result;
}

rc rc_copy(rc r) {
    // Increase the counter.
    *r.counter += 1;

    // Copied by value.
    return r;
}

void rc_delete(rc r) {
    // Decrease the counter.
    *r.counter -= 1;

    // If no references remain, delete the underlying value.
    if (*r.counter == 0) {
        destroy(r.value);
    }
}