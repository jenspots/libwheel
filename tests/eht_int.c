#include "./concrete/int.h"

int main() {
    eht_int* t = eht_init_int();

    uint64_t b00100 = (uint64_t)0b00100 << 59;
    uint64_t b01111 = (uint64_t)0b01111 << 59;
    uint64_t b10010 = (uint64_t)0b10010 << 59;
    uint64_t b11100 = (uint64_t)0b11100 << 59;
    uint64_t b11111 = (uint64_t)0b11111 << 59;

    assert(eht_index_int(t, b00100) == 0);
    assert(eht_insert_int(t, b00100));

    assert(eht_index_int(t, b01111) == 0);
    assert(eht_insert_int(t, b01111));

    assert(eht_index_int(t, b10010) == 1);
    assert(eht_insert_int(t, b10010));

    assert(eht_index_int(t, b11100) == 1);
    assert(eht_insert_int(t, b11100));

    assert(t->bit_count == 1);

    assert(eht_search_int(t, b00100).present);
    assert(eht_search_int(t, b01111).present);
    assert(eht_search_int(t, b10010).present);
    assert(eht_search_int(t, b11100).present);

    assert(eht_insert_int(t, b11111));
    assert(t->bit_count == 2);

    assert(eht_search_int(t, b00100).present);
    assert(eht_search_int(t, b01111).present);
    assert(eht_search_int(t, b10010).present);
    assert(eht_search_int(t, b11100).present);
}
