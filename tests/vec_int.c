#include "concrete/bst_int.h"
#include "concrete/vec_int.h"
#include <assert.h>

int main(int argc, char** argv) {
    vec_int v = vec_with_cap_int(5);
    assert(v.size == 5);
    for (int j = 0; j < 10; ++j) {
        vec_set_int(&v, j, j);
        optional_int o = vec_get_int(&v, j);
        assert(o.present);
        assert(o.value == j);
    }
    assert(v.size == 10);
    vec_delete_int(&v);
}
