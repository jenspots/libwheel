#include "impl/int.h"
#include <assert.h>

int main() {
    stack_int s = stack_init_int();

    for (int i = 0; i <= 100; ++i) {
        stack_push_int(&s, i);
    }

    for (int i = 100; i >= 0; --i) {
        optional_int o = stack_pop_int(&s);
        assert(o.present);
        assert(o.value == i);
    }
}