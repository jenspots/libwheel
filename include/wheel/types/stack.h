#include <wheel/def/wheel.h>

typedef struct stack stack;

stack stack_init();

void stack_push(stack* s, T element);

optional stack_pop(stack* s);

#include <wheel/undef/wheel.h>
