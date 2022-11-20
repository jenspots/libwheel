#ifndef LIBWHEEL_BST_STRING
#define LIBWHEEL_BST_STRING

#include "./optional_string.h"
#include "string.h"

#define LIBWHEEL_VALUE_TYPE char*
#define LIBWHEEL_KEY_TYPE   char*
#define LIBWHEEL_ALIAS      string

#define LIBWHEEL_COMPARATOR
int comparator_string(const char* a, const char* b) {
    return strcmp(a, b);
}

#include <wheel/binary_search_tree.h>

#undef LIBWHEEL_KEY_TYPE
#undef LIBWHEEL_VALUE_TYPE
#undef LIBWHEEL_ALIAS
#undef LIBWHEEL_COMPARATOR

#endif // LIBWHEEL_BST_STRING
