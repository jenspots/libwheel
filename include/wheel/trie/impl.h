#include <stdbool.h>
#include <wheel/wheel/header.h>

#include <wheel/wheel/def.h>

#ifdef LIBWHEEL_TYPE
#define T LIBWHEEL_TYPE
#else
#warning "MACRO NOT DEFINED: LIBWHEEL_TYPE"
#endif

typedef struct trie_node {
    trie_node* left;
    trie_node* next;
    trie_node* right;

    const char* skip;
    uint64_t skip_length;

    bool prefix;
} trie_node;

bool trie_node_search(trie_node *node, const char *string) {
    assert(node);
    assert(node->skip_length);
    assert(string);

    while (true) {
        // Find the current node at the current depth
        while (node->skip[0] != string[0]) {
            if (string[0] < node->skip[0]) {
                if (node->left) {
                    node = node->left;
                } else {
                    return false;
                }
            } else {
                if (node->right) {
                    node = node->right;
                } else {
                    return false;
                }
            }
        }

        // The path to this node must be the same
        if (strncmp(node->skip, string, node->skip_length) != 0) {
            return false;
        }

        unsigned char key = string[node->skip_length];

        // We've matched the string completely
        if (key == '\0') {
            return node->prefix;
        }

        // We cannot go further
        if (!node->next) {
            return false;
        }

        string += node->skip_length;
        node = node->next;
    }
}

void trie_node_branch(trie_node *node, const char *string, uint64_t i) {
    assert(node);
    assert(node->skip_length);
    assert(string);

    // Create a new child
    trie_node* child = calloc(1, sizeof(trie_node));
    child->skip = node->skip + i;
    child->skip_length = node->skip_length - i;
    child->next = node->next;
    child->prefix = node->prefix;

    // Indien de toe te voegen string leeg is, markeren we bovenste top als
    // prefix.
    if (string[i] == '\0') {
        node->next = child;
        node->skip_length = i;
        node->prefix = true;
        return;
    }

    // De tweede nieuwe top.
    trie_node* branched = calloc(1, sizeof(trie_node));
    branched->skip = string + i;
    branched->skip_length = strlen(string + i);
    branched->prefix = true;

    // Pas de skip-lengte aan van de bovenste top.
    node->next = child;
    node->skip_length = i;
    node->prefix = false;

    // Voeg links of rechts toe.
    if (branched->skip[0] < child->skip[0]) {
        child->left = branched;
    } else {
        child->right = branched;
    }
}

bool trie_node_add(trie_node *node, const char *string) {
    assert(node);
    assert(node->skip_length);
    assert(string);

    while (true) {
        // Zoek de top die overeenkomt met de start van de string. Indien deze
        // niet bestaat wordt ze aangemaakt.
        while (node->skip[0] != string[0]) {
            if (string[0] < node->skip[0]) {
                if (node->left) {
                    node = node->left;
                } else {
                    node->left = calloc(1, sizeof(trie_node));
                    node->left->skip = string;
                    node->left->skip_length = strlen(string);
                    node->left->prefix = true;
                    return true;
                }
            } else {
                if (node->right) {
                    node = node->right;
                } else {
                    node->right = calloc(1, sizeof(trie_node));
                    node->right->skip = string;
                    node->right->skip_length = strlen(string);
                    node->right->prefix = true;
                    return true;
                }
            }
        }

        // Overloop de skip-string en roep node_branch op indien nodig.
        for (int i = 0; i < node->skip_length; ++i) {
            if (string[i] == '\0' || node->skip[i] != string[i]) {
                trie_node_branch(node, string, i);
                return true;
            }
        }

        // Indien de string eindigt in de top, schakel de prefix vlag in.
        if (string[node->skip_length] == '\0') {
            bool result = !node->prefix;
            node->prefix = true;
            return result;
        }

        // Indien er geen volgende top is wordt deze aangemaakt met de rest van
        // de toe te voegen string.
        if (!node->next) {
            node->next = calloc(1, sizeof(trie_node));
            node->next->skip = string + node->skip_length;
            node->next->skip_length = strlen(string + node->skip_length);
            node->next->prefix = true;
            return true;
        }

        // Analoog aan:
        // node_add(node->next, string + node->skip_length)
        string += node->skip_length;
        node = node->next;
    }
}

bool trie_node_remove(trie_node **root, trie_node *node, const char *string) {
    assert(root);
    assert(*root);
    assert((*root)->skip_length);
    assert(node);
    assert(string);

    // Zoek de top die overeenkomt met de string op het huidig niveau.
    while (node->skip[0] != string[0]) {
        if (string[0] < node->skip[0]) {
            if (node->left) {
                root = &node->left;
                node = node->left;
            } else {
                return false;
            }
        } else {
            if (node->right) {
                root = &node->right;
                node = node->right;
            } else {
                return false;
            }
        }
    }

    // De skip string moet overeen komen.
    if (strncmp(node->skip, string, node->skip_length) != 0) {
        return false;
    }

    unsigned char key = string[node->skip_length];

    // Indien de toe te voegen string eindigt in de huidige top.
    if (key == '\0') {
        bool result = node->prefix;
        node->prefix = false;

        // Indien er geen volgende top is vervangen we de huidige top door
        // het linker- en/of rechterkind.
        if (node->next == NULL) {
            if (node->right) {
                *root = node->right;
                trie_node *tmp = node->right;
                while (tmp->left) {
                    tmp = tmp->left;
                }
                tmp->left = node->left;
            } else {
                *root = node->left; // mag null zijn
            }
            free(node);
        }

        // Indien er wel een volgende top is, dan voegen we deze twee toppen
        // samen. Hiervoor dienen node->next->left en node->next->right opnieuw
        // toe te voegen aan de deelbomen node->left en node->right.
        else {
            trie_node *old_next = node->next;
            node->skip = node->next->skip - node->skip_length;
            node->skip_length += node->next->skip_length;
            node->prefix = node->next->prefix;

            if (node->next->right) {
                trie_node *tmp = node->next->right;
                while (tmp->left) {
                    tmp = tmp->left;
                }
                tmp->left = node->next->left;
                node->next = node->next->right;
            } else {
                node->next = node->next->left; // mag null zijn
            }
            free(old_next);
        }

        return result;
    }

    // De te verwijderen string loopt verder langs volgens node->next.
    if (!node->next) {
        return false;
    }

    if (trie_node_remove(&node->next, node->next, string + node->skip_length)) {
        // Indien de huidige top geen prefix is, en node->next geen linker- of
        // rechterkind heeft kunnen we de twee toppen samen voegen.
        if (!node->prefix && !node->next->left && !node->next->right && node->next) {
            trie_node *tmp = node->next;
            node->skip = node->next->skip - node->skip_length;
            node->skip_length += node->next->skip_length;
            node->prefix = node->next->prefix;
            node->next = node->next->next;
            free(tmp);
        }
        return true;
    }
    return false;
}

typedef struct trie {
    trie_node* root;
    uint64_t size;
    bool empty_string;
} trie;

trie* trie_init() {
    return calloc(1, sizeof(trie));
};

bool trie_search(trie *trie, const char *string) {
    if (string[0] == '\0') {
        return trie->empty_string;
    }

    if (trie->root == NULL) {
        return false;
    }

    return trie_node_search(trie->root, string);
}

bool trie_add(trie *trie, const char *string) {
    if (string[0] == '\0') {
        if (!trie->empty_string) {
            trie->empty_string = true;
            trie->size += 1;
            return true;
        } else {
            return false;
        }
    }

    if (trie->root == NULL) {
        trie->root = calloc(1, sizeof(trie_node));
        trie->root->skip = string;
        trie->root->skip_length = strlen(trie->root->skip);
        trie->root->prefix = true;
        trie->size += 1;
        return true;
    }

    if (trie_node_add(trie->root, string)) {
        trie->size += 1;
        return true;
    } else {
        return false;
    }
}

bool trie_remove(trie *trie, const char *string) {
    assert(trie);
    assert(string);

    if (string[0] == '\0') {
        if (trie->empty_string) {
            trie->empty_string = false;
            trie->size -= 1;
            return true;
        } else {
            return false;
        }
    }

    if (trie->root == NULL) {
        assert((trie->empty_string && trie->size == 1) || (!trie->empty_string && trie->size == 0));
        return false;
    }

    if (trie_node_remove(&trie->root, trie->root, string)) {
        trie->size -= 1;
        return true;
    } else {
        return false;
    }
}

uint64_t trie_size(trie *trie) {
    return trie->size;
}

#include <wheel/wheel/undef.h>
