#ifndef LIBWHEEL_BST_STRING
#define LIBWHEEL_BST_STRING

#include "./optional_string.h"
#include "string.h"
#include <stdlib.h>

#define LIBWHEEL_KEY_TYPE   char*
#define LIBWHEEL_VALUE_TYPE char*
#define LIBWHEEL_ALIAS      string

#define LIBWHEEL_COMPARATOR
int comparator_string(const char* a, const char* b) {
    return strcmp(a, b);
}

#define LIBWHEEL_FREE_VALUE
void free_value_string(char* value) {
    free(value);
}

#include <wheel/bst.h>

#undef LIBWHEEL_KEY_TYPE
#undef LIBWHEEL_VALUE_TYPE
#undef LIBWHEEL_ALIAS
#undef LIBWHEEL_COMPARATOR
#undef LIBWHEEL_FREE_VALUE

#endif // LIBWHEEL_BST_STRING
