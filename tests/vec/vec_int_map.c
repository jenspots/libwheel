#include <wheel/std/int.h>

/**
 * Rocket science.
 */
int mul2(int i) {
    return 2 * i;
}

int main() {
    vec_int v = vec_int_init();

    // Set the first elements to 0..10.
    for (int i = 0; i < 10; ++i) {
        vec_int_set(&v, i, i);
    }

    // Double each value in the vector.
    vec_int_map(&v, &mul2);

    // Check if the values are properly updated.
    for (int i = 0; i < 10; ++i) {
        assert(vec_int_get(&v, i).value == 2 * i);
    }

    vec_int_destroy(&v);
}
