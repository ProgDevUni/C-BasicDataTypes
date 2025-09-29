#include <stdio.h>
#include <stdbool.h>
#include "stack.h"

void initStack(Stack *stack) {
    stack->top = -1;
}

bool stack_isEmpty(Stack *stack) {
    return stack->top == -1;
}

bool stack_isFull(Stack *stack) {
    return stack->top == MAX_SIZE-1;
}

void stack_push(Stack *stack, int value) {
    if (stack_isFull(stack)) {
        printf("Stack overflow\n");
        return;
    }

    stack->arr[++stack->top] = value;
}

int stack_pop(Stack *stack) {
    if (stack_isEmpty(stack)) {
        printf("Stack is empty");
        return -1;
    }
    return stack->arr[stack->top--];
}

int stack_peek(Stack *stack) {
    if (stack_isEmpty(stack)) {
        printf("Stack is empty");
        return -1;
    }
    return stack->arr[stack->top];
}