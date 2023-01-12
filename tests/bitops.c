#include <assert.h>
#include <limits.h>
#include <stdint.h>
#include <wheel/misc/bitops.h>

int main() {
    assert(NTH_BIT(0) == 0b0001);
    assert(NTH_BIT(1) == 0b0010);
    assert(NTH_BIT(2) == 0b0100);
    assert(NTH_BIT(3) == 0b1000);

    assert(NTH_BIT_SET(0, 0b0001));
    assert(NTH_BIT_SET(1, 0b0010));
    assert(NTH_BIT_SET(2, 0b0100));
    assert(NTH_BIT_SET(3, 0b1000));

    assert(NTH_BIT_SET(0, 0b1111));
    assert(NTH_BIT_SET(1, 0b1111));
    assert(NTH_BIT_SET(2, 0b1111));
    assert(NTH_BIT_SET(3, 0b1111));

    assert(N_BITS(0) == 0b0000);
    assert(N_BITS(1) == 0b0001);
    assert(N_BITS(2) == 0b0011);
    assert(N_BITS(3) == 0b0111);
    assert(N_BITS(4) == 0b1111);

    assert(HEAD(0, 0b1111) == 0b0000);
    assert(HEAD(1, 0b1111) == 0b0001);
    assert(HEAD(2, 0b1111) == 0b0011);
    assert(HEAD(3, 0b1111) == 0b0111);
    assert(HEAD(4, 0b1111) == 0b1111);

    uint64_t bit = (uint64_t)1 << 63;
    assert(TAIL(1, bit) == 0b1);
    assert(TAIL(2, bit) == 0b10);
    assert(TAIL(3, bit) == 0b100);

    assert(TAIL(64 - 4, 0b1111) == 0b0000);
    assert(TAIL(64 - 3, 0b1111) == 0b0001);
    assert(TAIL(64 - 2, 0b1111) == 0b0011);
    assert(TAIL(64 - 1, 0b1111) == 0b0111);
    assert(TAIL(64 - 0, 0b1111) == 0b1111);

    uint64_t result = 1;
    for (uint64_t i = 0; i < 64; ++i) {
        assert(POW2(i) == result);
        result *= 2;
    }
}
