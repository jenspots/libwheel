#include "wheel/misc/macros.h"

#define LIBWHEEL_NAMESPACE trie
#define trie         LIBWHEEL_PREFIX(trie)

#define trie_init    LIBWHEEL_DEFINE(init)
#define trie_destroy LIBWHEEL_DEFINE(destroy)
#define trie_search  LIBWHEEL_DEFINE(search)
#define trie_add     LIBWHEEL_DEFINE(add)
#define trie_remove  LIBWHEEL_DEFINE(remove)
#define trie_size    LIBWHEEL_DEFINE(size)

#define trie_node        LIBWHEEL_DEFINE(node)
#define trie_node_free   LIBWHEEL_DEFINE(node_free)
#define trie_node_search LIBWHEEL_DEFINE(node_search)
#define trie_node_add    LIBWHEEL_DEFINE(node_add)
#define trie_node_remove LIBWHEEL_DEFINE(node_remove)
#define trie_node_branch LIBWHEEL_DEFINE(node_branch)
