#include <wheel/std/int.h>

int main() {
    vec_int v = vec_int_init();
    int* result = vec_int_last_ptr(&v);
    assert(result == NULL);

    vec_int_set(&v, 0, 1);
    result = vec_int_last_ptr(&v);
    assert(result != NULL);
    assert(*result == 1);

    vec_int_set(&v, 1, 2);
    result = vec_int_last_ptr(&v);
    assert(result != NULL);
    assert(*result == 2);

    vec_int_destroy(&v);
}
