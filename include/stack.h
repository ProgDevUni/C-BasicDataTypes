#include <stdbool.h>

#ifndef STACK_H
#define STACK_H

#define MAX_SIZE 100

typedef struct Stack{
    int arr[MAX_SIZE];
    int top;
} Stack;

void initStack(Stack *stack);
bool stack_isEmpty(Stack *stack);
bool stack_isFull(Stack *stack);
void stack_push(Stack *stack, int value);
int stack_pop(Stack *stack);
int stack_peek(Stack *stack);

#endif // STACK_H