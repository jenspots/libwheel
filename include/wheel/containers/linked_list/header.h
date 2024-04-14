#include "wheel/wheel/def.h"

typedef struct ll ll;

typedef struct ll_node ll_node;

ll ll_init();

optional ll_head(ll* l);

optional ll_tail(ll* l);

optional ll_get(ll* l, uint64_t index);

void ll_prepend(ll* l, LIBWHEEL_TYPE element);

void ll_append(ll* l, LIBWHEEL_TYPE element);

void ll_insert_at(ll* l, uint64_t index, LIBWHEEL_TYPE element);

void ll_set(ll* l, uint64_t index, LIBWHEEL_TYPE value);

void ll_delete(ll l);

#include "wheel/wheel/undef.h"
