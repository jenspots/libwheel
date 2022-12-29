#include "concrete/bst_int.h"

int main() {
    bst_int* i = bst_init_int();
    assert(bst_insert_int(i, 1, 1));
    assert(bst_insert_int(i, 0, 0));
    assert(bst_insert_int(i, 2, 2));
    assert(!bst_insert_int(i, 1, 1));
    assert(!bst_insert_int(i, 0, 0));
    assert(!bst_insert_int(i, 2, 2));
    bst_delete_int(i);
}