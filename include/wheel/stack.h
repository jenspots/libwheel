#include <wheel/misc/macros.h>
#include <wheel/types/optional.h>
#include <wheel/types/stack.h>
#include <wheel/types/vec.h>

#ifdef LIBWHEEL_TYPE
#define T LIBWHEEL_TYPE
#else
#warning "MACRO NOT DEFINED: LIBWHEEL_TYPE"
#endif

#include <wheel/def/stack.h>
#include <wheel/def/optional.h>
#include <wheel/def/vec.h>

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

#include <wheel/undef/stack.h>
#include <wheel/undef/optional.h>
#include <wheel/undef/vec.h>
