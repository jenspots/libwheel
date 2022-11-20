#include "concrete/binary_tree_int.h"
#include "concrete/binary_tree_string.h"

int main(int argc, char** argv) {
    binary_tree_string* bst_string = binary_tree_init_string();
    binary_tree_insert_string(bst_string, "bac", "1");
    binary_tree_insert_string(bst_string, "abc", "0");
    binary_tree_insert_string(bst_string, "cab", "2");

    binary_tree_int* bst_int = binary_tree_init_int();
    binary_tree_insert_int(bst_int, 0, 0);
    binary_tree_insert_int(bst_int, 1, 1);
    binary_tree_insert_int(bst_int, 2, 2);
    binary_tree_insert_int(bst_int, -1, -1);
}
