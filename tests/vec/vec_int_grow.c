#include <wheel/std/int.h>

int main() {
    vec_int v = vec_int_init();
    uint64_t initial_size = v.size;

    for (int i = 0; i < initial_size; ++i) {
        vec_int_set(&v, i, i);
    }

    assert(v.size == initial_size);

    for (int i = (int) initial_size; i < initial_size * 2; ++i) {
        vec_int_set(&v, i, i);
    }

    assert(v.size == initial_size * 2);

    for (int i = (int) initial_size * 2; i < initial_size * 3; ++i) {
        vec_int_set(&v, i, i);
    }

    assert(v.size == initial_size * 4);

    for (int i = 0; i < initial_size * 3; ++i) {
        optional_int result = vec_int_get(&v, i);
        assert(result.present);
        assert(result.value == i);
    }

    for (int i = (int) initial_size * 3; i < initial_size * 4; ++i) {
        optional_int result = vec_int_get(&v, i);
        assert(!result.present);
    }

    vec_int_destroy(&v);
}
