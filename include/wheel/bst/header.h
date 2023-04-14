#include <stdbool.h>

#include "wheel/wheel/def.h"

typedef struct bst bst;

typedef struct bst_node bst_node;

bst_node* bst_node_init(LIBWHEEL_TYPE element);

bst* bst_init();

void bst_node_delete(bst_node* node);

void bst_node_remove(bst* tree, bst_node* node);

void bst_delete(bst* tree);

bool bst_insert(bst* tree, LIBWHEEL_TYPE element);

optional bst_search(bst* tree, LIBWHEEL_TYPE element);

bool bst_remove(bst* tree, LIBWHEEL_TYPE element);

#include "wheel/wheel/undef.h"
