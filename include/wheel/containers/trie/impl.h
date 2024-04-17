#include <stdbool.h>

#include "header.h"
#include "wheel/wheel/def.h"

typedef struct trie_node {
    trie_node* left;
    trie_node* next;
    trie_node* right;

    const char* skip;
    uint64_t skip_length;

    optional value;
} trie_node;

optional trie_node_search(trie_node* node, const char* string) {
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
                    return optional_empty();
                }
            } else {
                if (node->right) {
                    node = node->right;
                } else {
                    return optional_empty();
                }
            }
        }

        // The path to this node must be the same
        if (strncmp(node->skip, string, node->skip_length) != 0) {
            return optional_empty();
        }

        unsigned char key = string[node->skip_length];

        // We've matched the string completely
        if (key == '\0') {
            return node->value;
        }

        // We cannot go further
        if (!node->next) {
            return optional_empty();
        }

        string += node->skip_length;
        node = node->next;
    }
}

void trie_node_branch(trie_node* node, const char* string, uint64_t i, LIBWHEEL_TYPE value) {
    assert(node);
    assert(node->skip_length);
    assert(string);

    // Create a new child
    trie_node* child = calloc(1, sizeof(trie_node));
    child->skip = node->skip + i;
    child->skip_length = node->skip_length - i;
    child->next = node->next;
    child->value = node->value;

    // Indien de toe te voegen string leeg is, markeren we bovenste top als
    // prefix.
    if (string[i] == '\0') {
        node->next = child;
        node->skip_length = i;
        node->value = optional_of(value);
        return;
    }

    // De tweede nieuwe top.
    trie_node* branched = calloc(1, sizeof(trie_node));
    branched->skip = string + i;
    branched->skip_length = strlen(string + i);
    branched->value = optional_of(value);
    ;

    // Pas de skip-lengte aan van de bovenste top.
    node->next = child;
    node->skip_length = i;
    node->value = optional_empty();

    // Voeg links of rechts toe.
    if (branched->skip[0] < child->skip[0]) {
        child->left = branched;
    } else {
        child->right = branched;
    }
}

optional trie_node_add(trie_node* node, const char* string, LIBWHEEL_TYPE value) {
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
                    node->left->value = optional_of(value);
                    return optional_empty();
                }
            } else {
                if (node->right) {
                    node = node->right;
                } else {
                    node->right = calloc(1, sizeof(trie_node));
                    node->right->skip = string;
                    node->right->skip_length = strlen(string);
                    node->right->value = optional_of(value);
                    return optional_empty();
                }
            }
        }

        // Overloop de skip-string en roep node_branch op indien nodig.
        for (uint64_t i = 0; i < node->skip_length; ++i) {
            if (string[i] == '\0' || node->skip[i] != string[i]) {
                trie_node_branch(node, string, i, value);
                return optional_empty();
            }
        }

        // Indien de string eindigt in de top, schakel de prefix vlag in.
        if (string[node->skip_length] == '\0') {
            optional result = node->value;
            node->value = optional_of(value);
            return result;
        }

        // Indien er geen volgende top is wordt deze aangemaakt met de rest van
        // de toe te voegen string.
        if (!node->next) {
            node->next = calloc(1, sizeof(trie_node));
            node->next->skip = string + node->skip_length;
            node->next->skip_length = strlen(string + node->skip_length);
            node->next->value = optional_of(value);
            return optional_empty();
        }

        // Analoog aan:
        // node_add(node->next, string + node->skip_length)
        string += node->skip_length;
        node = node->next;
    }
}

optional trie_node_remove(trie_node** root, trie_node* node, const char* string) {
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
                return optional_empty();
            }
        } else {
            if (node->right) {
                root = &node->right;
                node = node->right;
            } else {
                return optional_empty();
            }
        }
    }

    // De skip string moet overeen komen.
    if (strncmp(node->skip, string, node->skip_length) != 0) {
        return optional_empty();
    }

    unsigned char key = string[node->skip_length];

    // Indien de toe te voegen string eindigt in de huidige top.
    if (key == '\0') {
        optional result = node->value;

        // Indien er geen volgende top is vervangen we de huidige top door
        // het linker- en/of rechterkind.
        if (node->next == NULL) {
            if (node->right) {
                *root = node->right;
                trie_node* tmp = node->right;
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
            trie_node* old_next = node->next;
            node->skip = node->next->skip - node->skip_length;
            node->skip_length += node->next->skip_length;
            node->value = node->next->value;

            if (node->next->right) {
                trie_node* tmp = node->next->right;
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
        return optional_empty();
    }

    optional recursive = trie_node_remove(&node->next, node->next, string + node->skip_length);

    if (recursive.present) {
        // Indien de huidige top geen prefix is, en node->next geen linker- of
        // rechterkind heeft kunnen we de twee toppen samen voegen.
        if (!node->value.present && !node->next->left && !node->next->right && node->next) {
            trie_node* tmp = node->next;
            node->skip = node->next->skip - node->skip_length;
            node->skip_length += node->next->skip_length;
            node->value = node->next->value;
            node->next = node->next->next;
            free(tmp);
        }
    }

    return recursive;
}

typedef struct trie {
    trie_node* root;
    uint64_t size;
    optional empty;
} trie;

trie* trie_init() {
    return calloc(1, sizeof(trie));
};

optional trie_search(trie* trie, const char* string) {
    if (string[0] == '\0') {
        return trie->empty;
    }

    if (trie->root == NULL) {
        return optional_empty();
    }

    return trie_node_search(trie->root, string);
}

optional trie_add(trie* trie, const char* string, LIBWHEEL_TYPE value) {
    if (string[0] == '\0') {
        optional previous = trie->empty;
        trie->empty = optional_of(value);
        if (!previous.present) {
            trie->size += 1;
        }
        return previous;
    }

    if (trie->root == NULL) {
        trie->root = calloc(1, sizeof(trie_node));
        trie->root->skip = string;
        trie->root->skip_length = strlen(trie->root->skip);
        trie->root->value = optional_of(value);
        trie->size += 1;
        return optional_empty();
    }

    optional previous = trie_node_add(trie->root, string, value);
    if (!previous.present) {
        trie->size += 1;
    } else {
    }
    return previous;
}

optional trie_remove(trie* trie, const char* string) {
    assert(trie);
    assert(string);

    if (string[0] == '\0') {
        optional result = trie->empty;
        if (result.present) {
            trie->size -= 1;
            trie->empty.present = false;
        }
        return result;
    }

    if (trie->root == NULL) {
        assert((trie->empty.present && trie->size == 1) || (!trie->empty.present && trie->size == 0));
        return optional_empty();
    }

    optional result = trie_node_remove(&trie->root, trie->root, string);
    if (result.present) {
        trie->size -= 1;
    }
    return result;
}

uint64_t trie_size(trie* trie) {
    return trie->size;
}

#include "wheel/wheel/undef.h"
