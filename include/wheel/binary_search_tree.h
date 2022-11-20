#include <stdint.h>
#include <stdlib.h>
#include <wheel/macros.h>

#ifdef LIBWHEEL_KEY_TYPE
#define K LIBWHEEL_KEY_TYPE
#else
#warning "MACRO NOT DEFINED: LIBWHEEL_KEY_TYPE"
#endif

#ifdef LIBWHEEL_VALUE_TYPE
#define V LIBWHEEL_VALUE_TYPE
#else
#warning "MACRO NOT DEFINED: LIBWHEEL_VALUE_TYPE"
#endif

#ifndef LIBWHEEL_ALIAS
#warning "MACRO NOT DEFINED: LIBWHEEL_ALIAS"
#endif

#define binary_tree           LIBWHEEL_PREFIX(binary_tree)
#define binary_tree_init      LIBWHEEL_PREFIX(binary_tree_init)
#define binary_tree_insert    LIBWHEEL_PREFIX(binary_tree_insert)
#define binary_tree_search    LIBWHEEL_PREFIX(binary_tree_search)
#define binary_tree_node      LIBWHEEL_PREFIX(binary_tree_node)
#define binary_tree_node_init LIBWHEEL_PREFIX(binary_tree_node_init)
#define comparator            LIBWHEEL_PREFIX(comparator)

#ifndef LIBWHEEL_COMPARATOR
int comparator(const K a, const K b) { return b - a; }
#endif

typedef struct binary_tree binary_tree;
typedef struct binary_tree_node binary_tree_node;

typedef struct binary_tree {
    binary_tree_node* root;
    uint64_t size;
} binary_tree;

typedef struct binary_tree_node {
    binary_tree_node* parent;
    binary_tree_node* left;
    binary_tree_node* right;
    K key;
    V value;
} binary_tree_node;

binary_tree_node* binary_tree_node_init(K key, V value) {
    binary_tree_node* result = calloc(1, sizeof(binary_tree_node));
    result->key = key;
    result->value = value;
    return result;
}

binary_tree* binary_tree_init() {
    binary_tree* result = malloc(sizeof(binary_tree));
    result->root = NULL;
    result->size = 0;
    return result;
}

bool binary_tree_insert(binary_tree* tree, K key, V value) {
    binary_tree_node* current = tree->root;

    if (tree->root == NULL) {
        tree->root = binary_tree_node_init(key, value);
        tree->size = 1;
        return true;
    }

    while (1) {
        int cmp = comparator(current->key, key);

        if (cmp == 0) {
            return false;
        } else if (cmp < 0) {
            if (current->left == NULL) {
                current->left = binary_tree_node_init(key, value);
                current->left->parent = current;
                tree->size += 1;
                return true;
            }
            current = current->left;
        } else {
            if (current->right == NULL) {
                current->right = binary_tree_node_init(key, value);
                current->right->parent = current;
                tree->size += 1;
                return true;
            }
            current = current->right;
        }
    }
}

optional binary_tree_search(binary_tree* tree, K search_term) {
    binary_tree_node* current = tree->root;

    if (current == NULL) {
        return optional_empty();
    }

    while (1) {
        int cmp = comparator(current->key, search_term);

        if (cmp == 0) {
            return optional_of(current->value);
        } else if (cmp < 0 && current->left) {
            current = current->left;
        } else if (0 < cmp && current->right) {
            current = current->right;
        } else {
            return optional_empty();
        }
    }
}

#undef K
#undef V
#undef binary_tree
#undef binary_tree_init
#undef binary_tree_insert
#undef binary_tree_search
#undef binary_tree_node
#undef binary_tree_node_init
#undef comparator
