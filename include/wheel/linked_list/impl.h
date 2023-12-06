#include <stdint.h>

#include "header.h"
#include "wheel/wheel/def.h"

typedef struct ll {
    ll_node* head;
    ll_node* tail;
    uint64_t size;
} ll;

typedef struct ll_node {
    ll_node* prev;
    ll_node* next;
    LIBWHEEL_TYPE element;
} ll_node;

ll ll_init() {
    ll result = { .head = NULL, .tail = NULL };
    return result;
}

optional ll_head(ll *l) {
    if (l->head) {
        return optional_of(l->head->element);
    } else {
        return optional_empty();
    }
}

optional ll_tail(ll *l) {
    if (l->tail) {
        return optional_of(l->tail->element);
    } else {
        return optional_empty();
    }
}

optional ll_get(ll *l, uint64_t index) {
    ll_node* current = l->head;
    ll_node* next = NULL;

    for (uint64_t i = 0; i < index; ++i) {
        next = current->next;
        if (!next) {
            return optional_empty();
        }
        current = next;
    }

    return optional_of(current->element);
}

void ll_prepend(ll *l, LIBWHEEL_TYPE element) {
    ll_node* node = malloc(sizeof(ll_node));
    node->prev = NULL;
    node->element = element;
    node->next = NULL;

    if (l->size == 0) {
        l->head = node;
        l->tail = node;
        l->size = 1;
        return;
    }

    // Chain the previous head and the new node.
    assert(l->head->prev == NULL);
    l->head->prev = node;
    node->next = l->head;

    // Set the new node as head.
    l->head = node;
    l->size += 1;
}

void ll_append(ll *l, LIBWHEEL_TYPE element) {
    ll_node* node = malloc(sizeof(ll_node));
    node->prev = NULL;
    node->element = element;
    node->next = NULL;

    if (l->size == 0) {
        l->head = node;
        l->tail = node;
        l->size = 1;
        return;
    }

    // Chain the previous tail and the new node.
    assert(l->tail->next == NULL);
    l->tail->next = node;
    node->prev = l->tail;

    // Set the new node as tail.
    l->tail = node;
    l->size += 1;
}

void ll_insert_at(ll *l, uint64_t index, LIBWHEEL_TYPE element) {
    // Special cases, makes the rest a bit simpler.
    if (index == 0) {
        ll_prepend(l, element);
        return;
    } else if (index == l->size) {
        ll_append(l, element);
        return;
    }

    ll_node* current = l->head;
    assert(current);

    for (uint64_t i = 0; i < index; ++i) {
        current = current->next;
        assert(current);
    }

    ll_node* node = calloc(1, sizeof(ll_node));
    assert(node);
    node->element = element;
    node->prev = current;
    node->next = current->next;
    node->prev->next = node;
    node->next->prev = node;

    l->size += 1;
}

void ll_set(ll* l, uint64_t index, LIBWHEEL_TYPE value) {
    ll_node* current = l->head;
    ll_node* next = NULL;

    for (uint64_t i = 0; i < index; ++i) {
        next = current->next;
        assert(next);
        current = next;
    }

    destroy(current->element);
    current->element = value;
}

void ll_delete(ll l) {
    ll_node* current = l.head;
    ll_node* next = NULL;

    while (current != NULL) {
        next = current->next;
        destroy(current->element);
        free(current);
        current = next;
    }
}

#include "wheel/wheel/undef.h"
