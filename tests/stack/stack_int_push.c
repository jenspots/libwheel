/*
 * Copyright (c) 2023.
 */

#include <assert.h>
#include <wheel/std/int.h>

int main() {
    stack_int s = stack_int_init();

    for (int i = 0; i <= 100; ++i) {
        stack_int_push(&s, i);
    }

    for (int i = 100; i >= 0; --i) {
        optional_int o = stack_int_pop(&s);
        assert(o.present);
        assert(o.value == i);
    }

    stack_int_destroy(&s);
}