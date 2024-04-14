#include <assert.h>
#include <wheel/std/string.h>

int main() {
    bst_string* s = bst_string_init();

    assert(bst_string_insert(s, strdup("bac")));
    assert(bst_string_insert(s, strdup("abc")));
    assert(bst_string_insert(s, strdup("cab")));

    assert(!bst_string_insert(s, "bac"));
    assert(!bst_string_insert(s, "abc"));
    assert(!bst_string_insert(s, "cab"));

    assert(bst_string_search(s, "bac").present);
    assert(bst_string_search(s, "abc").present);
    assert(bst_string_search(s, "cab").present);

    assert(!bst_string_search(s, "xac").present);
    assert(!bst_string_search(s, "axc").present);
    assert(!bst_string_search(s, "cax").present);

    bst_string_destroy(s);
}