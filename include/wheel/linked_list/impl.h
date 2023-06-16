#include "header.h"

#include "def.h"

#ifdef LIBWHEEL_TYPE
#define T LIBWHEEL_TYPE
#else
#warning "MACRO NOT DEFINED: LIBWHEEL_TYPE"
#endif

typedef struct ll {
    ll_node* head;
    ll_node* tail;
} ll;

typedef struct ll_node {
    ll_node* prev;
    ll_node* next;
    T element;
} ll_node;

#include "undef.h"