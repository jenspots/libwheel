#include "wheel/wheel/def.h"

typedef struct stack stack;

stack stack_init();

void stack_push(stack* s, T element);

optional stack_pop(stack* s);

void stack_delete(stack* s);

#include "wheel/wheel/undef.h"
