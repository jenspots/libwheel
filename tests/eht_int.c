#include <assert.h>
#include "impl/int.h"

int main() {
    eht_int* t = eht_int_init();

    uint64_t b00100 = (uint64_t)0b00100 << 59;
    uint64_t b01111 = (uint64_t)0b01111 << 59;
    uint64_t b10010 = (uint64_t)0b10010 << 59;
    uint64_t b11100 = (uint64_t)0b11100 << 59;
    uint64_t b11111 = (uint64_t)0b11111 << 59;

    assert(eht_int_index(t, b00100) == 0);
    assert(eht_int_insert(t, b00100));

    assert(eht_int_index(t, b01111) == 0);
    assert(eht_int_insert(t, b01111));

    assert(eht_int_index(t, b10010) == 1);
    assert(eht_int_insert(t, b10010));

    assert(eht_int_index(t, b11100) == 1);
    assert(eht_int_insert(t, b11100));

    assert(eht_int_capacity(t) == 2);

    assert(eht_int_search(t, b00100).present);
    assert(eht_int_search(t, b01111).present);
    assert(eht_int_search(t, b10010).present);
    assert(eht_int_search(t, b11100).present);

    assert(eht_int_insert(t, b11111));
    assert(eht_int_capacity(t) == 4);

    assert(eht_int_search(t, b00100).present);
    assert(eht_int_search(t, b01111).present);
    assert(eht_int_search(t, b10010).present);
    assert(eht_int_search(t, b11100).present);
}
