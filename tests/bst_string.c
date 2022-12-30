#include "concrete/bst_string.h"
#include <assert.h>

int main() {
    bst_string* s = bst_init_string();

    assert(bst_insert_string(s, strdup("bac")));
    assert(bst_insert_string(s, strdup("abc")));
    assert(bst_insert_string(s, strdup("cab")));

    assert(!bst_insert_string(s, "bac"));
    assert(!bst_insert_string(s, "abc"));
    assert(!bst_insert_string(s, "cab"));

    assert(bst_search_string(s, "bac").present);
    assert(bst_search_string(s, "abc").present);
    assert(bst_search_string(s, "cab").present);

    assert(!bst_search_string(s, "xac").present);
    assert(!bst_search_string(s, "axc").present);
    assert(!bst_search_string(s, "cax").present);

    bst_delete_string(s);
}