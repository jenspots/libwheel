#include <wheel/std/int.h>

int main() {
    vec_int v = vec_int_init();
    optional_int result = vec_int_head(&v);
    assert(!result.present);

    vec_int_set(&v, 0, 1);
    result = vec_int_head(&v);
    assert(result.present);
    assert(result.value == 1);

    vec_int_set(&v, 1, 2);
    result = vec_int_head(&v);
    assert(result.present);
    assert(result.value == 1);

    vec_int_destroy(&v);
}
