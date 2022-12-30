#ifndef LIBWHEEL_BST_STRING
#define LIBWHEEL_BST_STRING

#include "./optional_string.h"
#include "string.h"
#include <stdlib.h>

#define LIBWHEEL_TYPE  char*
#define LIBWHEEL_ALIAS string

#include <wheel/bst.h>

#undef LIBWHEEL_TYPE
#undef LIBWHEEL_ALIAS

#endif // LIBWHEEL_BST_STRING
