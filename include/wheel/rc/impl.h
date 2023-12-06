#include <stdlib.h>
#include "wheel/interface/header.h"

#include "header.h"
#include "wheel/wheel/def.h"

typedef struct rc {
    uint64_t *counter;
    LIBWHEEL_TYPE value;
} rc;

rc rc_init(LIBWHEEL_TYPE value) {
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

#include "wheel/wheel/undef.h"
