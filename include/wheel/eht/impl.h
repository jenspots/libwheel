#include "wheel/eht/header.h"
#include "wheel/interface/header.h"
#include "wheel/misc/bitops.h"
#include "wheel/optional/header.h"
#include "wheel/vec/header.h"
#include <math.h>

#ifndef LIBWHEEL_EHT_BUCKET_COUNT
#define LIBWHEEL_EHT_BUCKET_COUNT 1
#endif

#ifndef LIBWHEEL_EHT_BUCKET_SIZE
#define LIBWHEEL_EHT_BUCKET_SIZE 2
#endif

#include "header.h"
#include "wheel/wheel/def.h"

typedef struct eht {
    ehtb** buckets;
    uint64_t bit_count;
} eht;

typedef struct ehtb {
    optional values[LIBWHEEL_EHT_BUCKET_SIZE];
    uint64_t bit_count;
} ehtb;

ehtb* ehtb_init(uint64_t bit_count) {
    ehtb* b = calloc(1, sizeof(ehtb));
    b->bit_count = bit_count;
    return b;
}

eht* eht_init() {
    eht* result = malloc(sizeof(eht));
    uint64_t size = 1 << LIBWHEEL_EHT_BUCKET_COUNT;

    result->bit_count = LIBWHEEL_EHT_BUCKET_COUNT;
    result->buckets = malloc(sizeof(ehtb) * size);

    for (uint64_t i = 0; i < size; ++i) {
        result->buckets[i] = ehtb_init(LIBWHEEL_EHT_BUCKET_COUNT);
    }

    return result;
}

void eht_expand(eht* table) {
    assert(table);

    uint64_t len = eht_capacity(table);

    table->buckets = realloc(
        table->buckets,
        sizeof(ehtb*) * 2 * len);

    assert(table->buckets);

    table->bit_count += 1;

    for (uint64_t i = len; i > 0; --i) {
        ehtb* b = table->buckets[i - 1];
        table->buckets[2 * i - 1] = b;
        table->buckets[2 * i - 2] = b;
    }
}

void eht_split(eht* table, uint64_t index) {
    assert(table);

    ehtb* old = table->buckets[index];

    if (old->bit_count == table->bit_count) {
        eht_expand(table);
    }

    uint64_t start = index + (1 << (table->bit_count - old->bit_count - 1));
    uint64_t end = index + (1 << (table->bit_count - old->bit_count)) - 1;

    ehtb* new = ehtb_init(old->bit_count + 1);

    for (uint64_t i = start; i <= end; ++i) {
        table->buckets[i] = new;
    }

    uint64_t next = 0;
    index <<= 1;
    for (uint64_t i = 0; i < LIBWHEEL_EHT_BUCKET_SIZE; ++i) {
        optional element = old->values[i];
        assert(element.present);
        if (index == eht_index(table, element.value)) {
            old->values[i].present = false;
            new->values[next] = element;
            next += 1;
        }
    }
}

uint64_t eht_index(eht* table, LIBWHEEL_TYPE element) {
    return TAIL(table->bit_count, hash(element));
}

bool eht_insert(eht* table, LIBWHEEL_TYPE element) {
    while (true) {
        uint64_t hash_value = hash(element);
        uint64_t bucket_index = eht_index(table, element);
        ehtb* bucket = table->buckets[bucket_index];
        bool free_element = false;
        uint64_t free_index;

        /* Linear search to check if the element is already contained. */
        for (uint64_t i = 0; i < LIBWHEEL_EHT_BUCKET_SIZE; ++i) {
            optional e = bucket->values[i];

            if (e.present && hash_value == hash(e.value)) {
                return false;
            }

            if (!e.present && !free_element) {
                free_element = true;
                free_index = i;
            }
        }

        /* Check if there's room to insert this new element. */
        if (free_element) {
            bucket->values[free_index] = optional_of(element);
            return true;
        }

        /* No space left. We must split the current bucket. */
        eht_split(table, bucket_index);
    }
}

optional ehtb_search(ehtb* bucket, uint64_t hash_value) {
    for (uint64_t i = 0; i < LIBWHEEL_EHT_BUCKET_SIZE; ++i) {
        optional e = bucket->values[i];
        if (e.present && hash_value == hash(e.value)) {
            return e;
        }
    }
    return optional_empty();
}

optional eht_search(eht* table, LIBWHEEL_TYPE element) {
    ehtb* bucket = table->buckets[eht_index(table, element)];
    assert(bucket);
    return ehtb_search(bucket, hash(element));
}

uint64_t eht_capacity(eht* e) {
    return 1 << (e->bit_count);
}

#include "wheel/wheel/undef.h"
