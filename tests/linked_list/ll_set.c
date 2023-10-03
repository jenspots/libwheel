#include "../impl/int.h"

int main() {
    ll_int l = ll_int_init();

    /*
     * Initialize an empty list with `n` zero elements.
     */
    for (uint64_t i = 0; i < 64; ++i) {
        ll_int_append(&l, 0);
    }

    assert(l.size == 64);

    /*
     * Set the n-th element to `n`.
     */
    for (uint64_t i = 0; i < 64; ++i) {
        ll_int_set(&l, i, i);
    }

    /*
     * Check if all elements are correctly set.
     */
    ll_int_node *n = l.head;
    for (uint64_t i = 0; i < 64; ++i) {
        assert(n != NULL);
        assert(n->element == i);
        n = n->next;
    }
    assert(n == NULL);

    ll_int_delete(l);
}
