//
// Created by sbn on 7/22/25.
//

#include "tp_stack.h"

#define INITIAL_CAPACITY 10000000



// Function to initialize the stack
void initStack_tp(TPStack *stack) {
    stack->capacity = INITIAL_CAPACITY;
    stack->top = -1;
    stack->data = (struct timepoint*)malloc(sizeof(struct timepoint) * stack->capacity);
    if (stack->data == NULL) {
        perror("Failed to allocate memory for timepoint stack");
        exit(EXIT_FAILURE);
    }
}

// Push value to stack
void push_tp(TPStack *stack, struct timepoint value) {
    if (stack->top + 1 >= stack->capacity) {
        stack->capacity *= 2;
        stack->data = (struct timepoint *)realloc(stack->data, sizeof(struct timepoint) * stack->capacity);
        if (stack->data == NULL) {
            perror("Failed to reallocate memory for timepoint stack");
            exit(EXIT_FAILURE);
        }
    }
    stack->data[++stack->top] = value;
}

// Pop value from stack
struct timepoint pop_tp(TPStack *stack) {
    if (stack->top < 0) {
        fprintf(stderr, "Stack underflow!\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top--];
}

// Peek top value
struct timepoint peek_tp(TPStack *stack) {
    if (stack->top < 0) {
        fprintf(stderr, "Stack is empty!\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top];
}

// Check if stack is empty
bool isEmpty_tp(TPStack *stack) {
    return stack->top == -1;
}

// Free the stack
void freeStack_tp(TPStack *stack) {
    free(stack->data);
    stack->data = NULL;
    stack->top = -1;
    stack->capacity = 0;
}

// Demo
/*int main() {
    TPStack stack;
    initStack(&stack);

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    printf("Top of stack: %d\n", peek(&stack));
    printf("Popped: %d\n", pop(&stack));
    printf("Popped: %d\n", pop(&stack));

    if (!isEmpty(&stack)) {
        printf("Top of stack now: %d\n", peek(&stack));
    }

    freeStack(&stack);
    return 0;
}*/
