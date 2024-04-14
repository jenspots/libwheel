#include <assert.h>
#include <wheel/std/int.h>

int main() {
    trie_int* trie = trie_int_init();

    int a = 100000000;
    int b = 100000001;
    int c = 100000002;
    int d = 100000003;

    assert(!trie_int_add(trie, "10.0.0.0", a).present);
    assert(!trie_int_add(trie, "10.0.0.1", b).present);
    assert(!trie_int_add(trie, "10.0.0.2", c).present);
    assert(!trie_int_add(trie, "10.0.0.3", d).present);

    assert(trie_int_search(trie, "10.0.0.0").value == a);
    assert(trie_int_search(trie, "10.0.0.1").value == b);
    assert(trie_int_search(trie, "10.0.0.2").value == c);
    assert(trie_int_search(trie, "10.0.0.3").value == d);

    assert(trie_int_add(trie, "10.0.0.0", a).value == a);
    assert(trie_int_add(trie, "10.0.0.1", b).value == b);
    assert(trie_int_add(trie, "10.0.0.2", c).value == c);
    assert(trie_int_add(trie, "10.0.0.3", d).value == d);

    assert(trie_int_remove(trie, "10.0.0.0").value == a);
    assert(trie_int_remove(trie, "10.0.0.1").value == b);
    assert(trie_int_remove(trie, "10.0.0.2").value == c);
    assert(trie_int_remove(trie, "10.0.0.3").value == d);

    assert(!trie_int_search(trie, "10.0.0.0").present);
    assert(!trie_int_search(trie, "10.0.0.1").present);
    assert(!trie_int_search(trie, "10.0.0.2").present);
    assert(!trie_int_search(trie, "10.0.0.3").present);

    assert(!trie_int_remove(trie, "10.0.0.0").present);
    assert(!trie_int_remove(trie, "10.0.0.1").present);
    assert(!trie_int_remove(trie, "10.0.0.2").present);
    assert(!trie_int_remove(trie, "10.0.0.3").present);
}