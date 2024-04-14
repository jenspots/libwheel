#include <wheel/std/int.h>

bool is_even(int i) {
    return i % 2 == 0;
}

int main() {
    vec_int v = vec_int_init();

    // Set the first elements to 0..10.
    for (int i = 0; i < 10; ++i) {
        vec_int_set(&v, i, i);
    }

    // Only keep the even numbers.
    vec_int_filter(&v, &is_even);

    // Check if the values are properly updated.
    for (int i = 0; i < 10; i += 2) {
        assert(vec_int_get(&v, i).present);
        assert(!vec_int_get(&v, i + 1).present);
    }

    vec_int_destroy(&v);
}
