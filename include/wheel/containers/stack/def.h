#include "wheel/misc/macros.h"

#define stack        LIBWHEEL_APPEND(stack)
#define stack_init   LIBWHEEL_DEFINE(stack, init)
#define stack_push   LIBWHEEL_DEFINE(stack, push)
#define stack_peek   LIBWHEEL_DEFINE(stack, peek)
#define stack_pop    LIBWHEEL_DEFINE(stack, pop)
#define stack_delete LIBWHEEL_DEFINE(stack, destroy)
