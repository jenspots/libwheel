#ifndef LIBWHEEL_STACK_INT
#define LIBWHEEL_STACK_INT

#include "./int.h"
#include "./optional_int.h"
#include "./vec_int.h"

#define LIBWHEEL_TYPE  int
#define LIBWHEEL_ALIAS int

#include <wheel/stack.h>

#undef LIBWHEEL_ALIAS
#undef LIBWHEEL_TYPE

#endif // LIBWHEEL_STACK_INT