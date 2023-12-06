#include <stdbool.h>

#include "header.h"
#include "wheel/wheel/def.h"

typedef struct optional {
    bool present;
    LIBWHEEL_TYPE value;
} optional;

optional optional_of(LIBWHEEL_TYPE value) {
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

#include "wheel/wheel/undef.h"
