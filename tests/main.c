#include "concrete/binary_tree_int.h"
#include "concrete/binary_tree_string.h"
#include "concrete/vec_int.h"
#include <assert.h>
#include <string.h>

int main(int argc, char** argv) {
    bst_string* s = bst_init_string();
    assert(bst_insert_string(s, "bac", strdup("1")));
    assert(bst_insert_string(s, "abc", strdup("0")));
    assert(bst_insert_string(s, "cab", strdup("2")));

    assert(!bst_insert_string(s, "bac", strdup("1")));
    assert(!bst_insert_string(s, "abc", strdup("0")));
    assert(!bst_insert_string(s, "cab", strdup("2")));

    assert(bst_search_string(s, "bac").present);
    assert(bst_search_string(s, "abc").present);
    assert(bst_search_string(s, "cab").present);

    assert(!bst_search_string(s, "xac").present);
    assert(!bst_search_string(s, "axc").present);
    assert(!bst_search_string(s, "cax").present);

    bst_delete_string(s);

    bst_int* i = bst_init_int();
    assert(bst_insert_int(i, 1, 1));
    assert(bst_insert_int(i, 0, 0));
    assert(bst_insert_int(i, 2, 2));
    assert(!bst_insert_int(i, 1, 1));
    assert(!bst_insert_int(i, 0, 0));
    assert(!bst_insert_int(i, 2, 2));
    bst_delete_int(i);

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
