#include "impl/int.h"
#include <assert.h>

int main() {
    trie_int *trie = trie_init_int();

    assert(trie_add_int(trie, "10.0.0.0"));
    assert(trie_add_int(trie, "10.0.0.1"));
    assert(trie_add_int(trie, "10.0.0.2"));
    assert(trie_add_int(trie, "10.0.0.3"));

    assert(trie_search_int(trie, "10.0.0.0"));
    assert(trie_search_int(trie, "10.0.0.1"));
    assert(trie_search_int(trie, "10.0.0.2"));
    assert(trie_search_int(trie, "10.0.0.3"));

    assert(!trie_add_int(trie, "10.0.0.0"));
    assert(!trie_add_int(trie, "10.0.0.1"));
    assert(!trie_add_int(trie, "10.0.0.2"));
    assert(!trie_add_int(trie, "10.0.0.3"));

    assert(trie_remove_int(trie, "10.0.0.0"));
    assert(trie_remove_int(trie, "10.0.0.1"));
    assert(trie_remove_int(trie, "10.0.0.2"));
    assert(trie_remove_int(trie, "10.0.0.3"));

    assert(!trie_search_int(trie, "10.0.0.0"));
    assert(!trie_search_int(trie, "10.0.0.1"));
    assert(!trie_search_int(trie, "10.0.0.2"));
    assert(!trie_search_int(trie, "10.0.0.3"));

    assert(!trie_remove_int(trie, "10.0.0.0"));
    assert(!trie_remove_int(trie, "10.0.0.1"));
    assert(!trie_remove_int(trie, "10.0.0.2"));
    assert(!trie_remove_int(trie, "10.0.0.3"));
}