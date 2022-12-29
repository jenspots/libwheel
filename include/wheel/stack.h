#include <wheel/macros.h>
#include <wheel/types/optional.h>
#include <wheel/types/vec.h>
#include <wheel/types/stack.h>

#ifdef LIBWHEEL_TYPE
#define T LIBWHEEL_TYPE
#else
#warning "MACRO NOT DEFINED: LIBWHEEL_TYPE"
#endif

#ifndef LIBWHEEL_ALIAS
#warning "MACRO NOT DEFINED: LIBWHEEL_ALIAS"
#endif

typedef struct stack stack;

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

#undef T
