
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

//TODO:
void push(stack *s, node *new_node)
{
    add_first(&(s->top), new_node);
}

//TODO:
node* pop(stack *s)
{
    return remove_first(&(s->top));
}

//TODO:
int empty(stack *s)
{
    return s->top == NULL;
}

//TODO:
void clear_stack(stack *s)
{
    while(!empty(s)) // DO I NEED TO SET NULL CHECK
    {
        node * t = remove_first(&(s->top));
        free(t);
    }
}