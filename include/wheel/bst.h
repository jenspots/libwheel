#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <wheel/types/interface.h>
#include <wheel/types/bst.h>

#include <wheel/def/wheel.h>

#ifdef LIBWHEEL_TYPE
#define T LIBWHEEL_TYPE
#else
#warning "MACRO NOT DEFINED: LIBWHEEL_KEY_TYPE"
#endif

typedef struct bst {
    bst_node* root;
    uint64_t size;
} bst;

typedef struct bst_node {
    bst_node* parent;
    bst_node* left;
    bst_node* right;
    T element;
} bst_node;

bst_node* bst_node_init(T element) {
    bst_node* result = calloc(1, sizeof(bst_node));
    result->element = element;
    return result;
}

bst* bst_init() {
    bst* result = malloc(sizeof(bst));
    result->root = NULL;
    result->size = 0;
    return result;
}

void bst_node_delete(bst_node* node) {
    assert(node);
    destroy(node->element);
    free(node);
}

void bst_node_remove(bst* tree, bst_node* node) {
    assert(tree);
    assert(node);

    bst_node* parent = node->parent;

    if (node->left && node->right) {
        return;
    }

    if (parent) {
        bst_node** adoption = NULL;

        if (parent->left == node) {
            adoption = &parent->left;
        } else {
            adoption = &parent->right;
        }

        if (node->left) {
            *adoption = node->left;
            node->left->parent = parent;
        } else if (node->right) {
            *adoption = node->right;
            node->right->parent = parent;
        }
    }

    bst_node_delete(node);
}

void bst_delete(bst* tree) {
    assert(tree);

    bst_node* node = tree->root;
    bst_node* tmp;

    while (node) {
        if (node->left) {
            node = node->left;
        } else if (node->right) {
            node = node->right;
        } else {
            if (node->parent && node->parent->left == node) {
                node->parent->left = NULL;
            } else if (node->parent && node->parent->right == node) {
                node->parent->right = NULL;
            }
            tmp = node;
            node = node->parent;
            bst_node_delete(tmp);
        }
    }

    free(tree);
}

bool bst_insert(bst* tree, T element) {
    assert(tree);

    bst_node* current = tree->root;

    if (tree->root == NULL) {
        tree->root = bst_node_init(element);
        tree->size = 1;
        return true;
    }

    while (1) {
        int cmp = compare(current->element, element);

        if (cmp == 0) {
            return false;
        } else if (cmp < 0) {
            if (current->left == NULL) {
                current->left = bst_node_init(element);
                current->left->parent = current;
                tree->size += 1;
                return true;
            }
            current = current->left;
        } else {
            if (current->right == NULL) {
                current->right = bst_node_init(element);
                current->right->parent = current;
                tree->size += 1;
                return true;
            }
            current = current->right;
        }
    }
}

optional bst_search(bst* tree, T element) {
    assert(tree);

    bst_node* current = tree->root;

    if (current == NULL) {
        return optional_empty();
    }

    while (1) {
        int cmp = compare(current->element, element);

        if (cmp == 0) {
            return optional_of(current->element);
        } else if (cmp < 0 && current->left) {
            current = current->left;
        } else if (0 < cmp && current->right) {
            current = current->right;
        } else {
            return optional_empty();
        }
    }
}

bool bst_remove(bst* tree, T element) {
    assert(tree);

    bst_node* current = tree->root;

    while (1) {
        int cmp = compare(current->element, element);

        if (cmp == 0) {
            bst_node_remove(tree, current);
            return true;
        } else if (cmp < 0 && current->left) {
            current = current->left;
        } else if (0 < cmp && current->right) {
            current = current->right;
        } else {
            return false;
        }
    }
}

#include <wheel/undef/wheel.h>