#include <assert.h>
#include <wheel/misc/bitops.h>
#include <stdint.h>

int main() {
    vec_bit v = vec_bit_with_cap(64);

    for (uint64_t i = 0; i < 256; i += 2) {
        assert(!vec_bit_get(&v, i));
        vec_bit_set(&v, i, true);
        assert(vec_bit_get(&v, i));
    }

    for (uint64_t i = 1; i < 256; i += 2) {
        assert(!vec_bit_get(&v, i));
    }

    for (uint64_t i = 0; i < 256; i += 2) {
        assert(vec_bit_get(&v, i));
        vec_bit_set(&v, i, false);
        assert(!vec_bit_get(&v, i));
    }

    vec_bit_delete(&v);
}
