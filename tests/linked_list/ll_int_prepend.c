#include "../impl/int.h"

int main() {
    ll_int l = ll_int_init();

    for (uint64_t i = 0; i < 64; ++i) {
        ll_int_prepend(&l, i);
    }

    assert(l.size == 64);

    for (uint64_t i = 0; i < 64; ++i) {
        optional_int result = ll_int_get(&l, i);
        assert(result.present);
        assert(result.value == (63 - i));
    }

    ll_int_destroy(l);
}