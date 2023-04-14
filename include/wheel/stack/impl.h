#include "header.h"
#include "wheel/misc/macros.h"
#include "wheel/optional/header.h"
#include "wheel/vec/header.h"

#ifdef LIBWHEEL_TYPE
#define T LIBWHEEL_TYPE
#else
#warning "MACRO NOT DEFINED: LIBWHEEL_TYPE"
#endif

#include "def.h"
#include "wheel/optional/def.h"
#include "wheel/vec/def.h"

typedef struct stack {
    vec values;
    uint64_t index;
} stack;

stack stack_init() {
    return (stack) {
        .values = vec_init(),
        .index = 0,
    };
}

void stack_push(stack* s, T element) {
    vec_set(&s->values, s->index, element);
    s->index += 1;
}

optional stack_pop(stack* s) {
    if (s->index > 0) {
        s->index -= 1;
        optional element = vec_pop(&s->values, s->index);
        return element;
    } else {
        return optional_empty();
    }
}

#include "undef.h"
#include "wheel/optional/undef.h"
#include "wheel/vec/undef.h"
