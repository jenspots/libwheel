#include <wheel/std/int.h>

int main() {
    // Create [0, 1, 2, 3, 4]
    vec_int v = vec_int_init();
    for (int i = 0; i < 5; ++i) {
        vec_int_set(&v, i, i);
    }

    // Iterate over the vector and assert that the values are correct.
    vec_int_iter it = vec_int_begin(&v);
    while (vec_int_next(&it)) {
        int result = vec_int_iget(&it);
        assert(result == it.index);
    }

    // The same but in reverse.
    it = vec_int_rbegin(&v);
    while (vec_int_next(&it)) {
        int result = vec_int_iget(&it);
        assert(result == it.index);
    }

    // Remove vector.
    vec_int_destroy(&v);
}
