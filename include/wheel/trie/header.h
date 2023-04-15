#include "wheel/wheel/def.h"

typedef struct trie_node trie_node;

optional trie_node_search(trie_node *node, const char *string);

void trie_node_branch(trie_node *node, const char *string, uint64_t i, T value);

optional trie_node_add(trie_node *node, const char *string, T value);

optional trie_node_remove(trie_node **root, trie_node *node, const char *string);

typedef struct trie trie;

trie* trie_init();

void trie_destroy(trie*);

optional trie_search(trie*, const char* string);

optional trie_add(trie*, const char* string, T value);

optional trie_remove(trie*, const char* string);

uint64_t trie_size(trie *trie);

#include "wheel/wheel/undef.h"
