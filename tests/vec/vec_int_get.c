#include "../impl/vec_int.h"

#include <assert.h>

int main() {
    vec_int v = vec_int_with_cap(8);

    // Out of bounds.
    assert(!vec_int_get(&v, -1).present);
    assert(!vec_int_get(&v, 8).present);

    // Not initially present.
    for (int i = 0; i < 8; ++i) {
        assert(!vec_int_get(&v, i).present);
    }

    // Set a value.
    for (int i = 0; i < 8; ++i) {
        vec_int_set(&v, i, i);
    }

    // Check if present.
    for (int i = 0; i < 8; ++i) {
        assert(vec_int_get(&v, i).present);
    }

    // Unset.
    for (int i = 0; i < 8; ++i) {
        optional_int o = vec_int_pop(&v, i);
        assert(o.present && o.value == i);
    }

    // Check if present.
    for (int i = 0; i < 8; ++i) {
        assert(!vec_int_get(&v, i).present);
    }

    vec_int_destroy(&v);
}
