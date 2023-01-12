#include <wheel/misc/macros.h>
#include <wheel/misc/warnings.h>

#ifdef LIBWHEEL_TYPE
#define T LIBWHEEL_TYPE
#else
#warning "MACRO NOT DEFINED: LIBWHEEL_TYPE"
#endif

#define eht              LIBWHEEL_PREFIX(eht)
#define eht_init         LIBWHEEL_PREFIX(eht_init)
#define eht_expand       LIBWHEEL_PREFIX(eht_expand)
#define eht_insert       LIBWHEEL_PREFIX(eht_insert)
#define eht_search       LIBWHEEL_PREFIX(eht_search)
#define eht_get          LIBWHEEL_PREFIX(eht_get)
#define eht_capacity     LIBWHEEL_PREFIX(eht_capacity)
#define eht_split        LIBWHEEL_PREFIX(eht_split)

#define ehtb             LIBWHEEL_PREFIX(ehtb)
#define ehtb_init        LIBWHEEL_PREFIX(ehtb_init)
#define ehtb_get         LIBWHEEL_PREFIX(ehtb_get)
#define eht_index        LIBWHEEL_PREFIX(eht_index)
#define ehtb_search      LIBWHEEL_PREFIX(ehtb_search)

typedef struct eht eht;

typedef struct ehtb ehtb;

ehtb* ehtb_init(uint64_t bit_count);

uint64_t eht_capacity(eht* e);

uint64_t eht_index(eht* table, T element);

bool eht_insert(eht* table, T element);
