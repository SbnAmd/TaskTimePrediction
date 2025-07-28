//
// Created by sbn on 7/22/25.
//

#include "tp_stack.h"

#define INITIAL_CAPACITY 10000000



// Function to initialize the stack
void initStack_tp(TPStack_t *stack) {
    stack->capacity = INITIAL_CAPACITY;
    stack->top = -1;
    stack->data = (timepoint_t*)malloc(sizeof(timepoint_t) * stack->capacity);
    if (stack->data == NULL) {
        perror("Failed to allocate memory for timepoint stack");
        exit(EXIT_FAILURE);
    }
}

// Push value to stack
void push_tp(TPStack_t *stack, timepoint_t value) {
    if (stack->top + 1 >= stack->capacity) {
        stack->capacity *= 2;
        stack->data = (timepoint_t *)realloc(stack->data, sizeof(timepoint_t) * stack->capacity);
        if (stack->data == NULL) {
            perror("Failed to reallocate memory for timepoint stack");
            exit(EXIT_FAILURE);
        }
    }
    stack->data[++stack->top] = value;
}

// Pop value from stack
timepoint_t pop_tp(TPStack_t *stack) {
    if (stack->top < 0) {
        fprintf(stderr, "Stack underflow!\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top--];
}

// Peek top value
timepoint_t peek_tp(TPStack_t *stack) {
    if (stack->top < 0) {
        fprintf(stderr, "Stack is empty!\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top];
}

// Check if stack is empty
bool isEmpty_tp(TPStack_t *stack) {
    return stack->top == -1;
}

// Free the stack
void freeStack_tp(TPStack_t *stack) {
    free(stack->data);
    stack->data = NULL;
    stack->top = -1;
    stack->capacity = 0;
}
