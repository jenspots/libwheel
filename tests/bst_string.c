#include "concrete/bst_string.h"
#include <assert.h>

int main() {
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
}