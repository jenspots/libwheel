#ifndef LIBWHEEL_BITOPS_H
#define LIBWHEEL_BITOPS_H

#include <limits.h>

#define N_BITS(i) (i == 0 ? 0 : i == 64 ? UINT_MAX \
                                        : ((uint64_t)1 << (uint64_t)(i)) - 1)

#define HEAD(i, x) (((uint64_t)x) & N_BITS((uint64_t)i))
#define TAIL(i, x) (i == 64 ? (x) : (((uint64_t)x) & ~(N_BITS(64 - (i)-1))) >> (64 - (i)))

#define NTH_BIT(i)        ((1UL << (i)))
#define NTH_BIT_SET(i, x) ((1 << (i)) & (x)) > 0

#define POW2(i) NTH_BIT(i)

#endif // LIBWHEEL_BITOPS_H
