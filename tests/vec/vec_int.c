#include <assert.h>
#include <wheel/std/int.h>

int main(int argc, char** argv) {
    vec_int v = vec_int_with_cap(5);
    assert(v.size == 5);
    for (int j = 0; j < 10; ++j) {
        vec_int_set(&v, j, j);
        optional_int o = vec_int_get(&v, j);
        assert(o.present);
        assert(o.value == j);
    }
    assert(v.size == 10);
    vec_int_destroy(&v);
}
