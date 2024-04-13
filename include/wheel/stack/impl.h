#include "header.h"
#include "wheel/wheel/def.h"

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

void stack_push(stack* s, LIBWHEEL_TYPE element) {
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

void stack_delete(stack* s) {
    vec_destroy(&s->values);
}

#include "wheel/wheel/undef.h"
