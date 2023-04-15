#include "impl/int.h"
#include <assert.h>

int main() {
    trie_int *trie = trie_init_int();

    uint64_t a = 10000000000;
    uint64_t b = 10000000001;
    uint64_t c = 10000000002;
    uint64_t d = 10000000003;

    assert(!trie_add_int(trie, "10.0.0.0", a).present);
    assert(!trie_add_int(trie, "10.0.0.1", b).present);
    assert(!trie_add_int(trie, "10.0.0.2", c).present);
    assert(!trie_add_int(trie, "10.0.0.3", d).present);

    assert(trie_search_int(trie, "10.0.0.0").value == a);
    assert(trie_search_int(trie, "10.0.0.1").value == b);
    assert(trie_search_int(trie, "10.0.0.2").value == c);
    assert(trie_search_int(trie, "10.0.0.3").value == d);

    assert(trie_add_int(trie, "10.0.0.0", a).value == a);
    assert(trie_add_int(trie, "10.0.0.1", b).value == b);
    assert(trie_add_int(trie, "10.0.0.2", c).value == c);
    assert(trie_add_int(trie, "10.0.0.3", d).value == d);

    assert(trie_remove_int(trie, "10.0.0.0").value == a);
    assert(trie_remove_int(trie, "10.0.0.1").value == b);
    assert(trie_remove_int(trie, "10.0.0.2").value == c);
    assert(trie_remove_int(trie, "10.0.0.3").value == d);

    assert(!trie_search_int(trie, "10.0.0.0").present);
    assert(!trie_search_int(trie, "10.0.0.1").present);
    assert(!trie_search_int(trie, "10.0.0.2").present);
    assert(!trie_search_int(trie, "10.0.0.3").present);

    assert(!trie_remove_int(trie, "10.0.0.0").present);
    assert(!trie_remove_int(trie, "10.0.0.1").present);
    assert(!trie_remove_int(trie, "10.0.0.2").present);
    assert(!trie_remove_int(trie, "10.0.0.3").present);
}