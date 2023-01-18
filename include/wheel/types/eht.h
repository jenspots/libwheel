#include <wheel/def/wheel.h>

typedef struct eht eht;

typedef struct ehtb ehtb;

eht* eht_init();

ehtb* ehtb_init(uint64_t bit_count);

void eht_expand(eht* table);

void eht_split(eht* table, uint64_t index);

uint64_t eht_capacity(eht* e);

uint64_t eht_index(eht* table, LIBWHEEL_TYPE element);

bool eht_insert(eht* table, LIBWHEEL_TYPE element);

optional ehtb_search(ehtb* bucket, uint64_t hash_value);

optional eht_search(eht* table, LIBWHEEL_TYPE element);

#include <wheel/undef/wheel.h>
