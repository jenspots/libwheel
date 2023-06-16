#include "wheel/misc/macros.h"

#define trie         LIBWHEEL_APPEND(trie)
#define trie_init    LIBWHEEL_DEFINE(trie, init)
#define trie_destroy LIBWHEEL_DEFINE(trie, destroy)
#define trie_search  LIBWHEEL_DEFINE(trie, search)
#define trie_add     LIBWHEEL_DEFINE(trie, add)
#define trie_remove  LIBWHEEL_DEFINE(trie, remove)
#define trie_size    LIBWHEEL_DEFINE(trie, size)

#define trie_node        LIBWHEEL_DEFINE(trie, node)
#define trie_node_free   LIBWHEEL_DEFINE(trie, node_free)
#define trie_node_search LIBWHEEL_DEFINE(trie, node_search)
#define trie_node_add    LIBWHEEL_DEFINE(trie, node_add)
#define trie_node_remove LIBWHEEL_DEFINE(trie, node_remove)
#define trie_node_branch LIBWHEEL_DEFINE(trie, node_branch)
