#include <assert.h>

#include "../impl/int.h"

int main() {
    bst_int* i = bst_int_init();
    assert(bst_int_insert(i, 1));
    assert(bst_int_insert(i, 0));
    assert(bst_int_insert(i, 2));
    assert(!bst_int_insert(i, 1));
    assert(!bst_int_insert(i, 0));
    assert(!bst_int_insert(i, 2));
    bst_int_delete(i);
}
