//
// Created by sbn on 5/19/25.
//

#include "stack.h"


#define INITIAL_CAPACITY 1000



// Function to initialize the stack
void initStack(IntStack *stack) {
    stack->capacity = INITIAL_CAPACITY;
    stack->top = -1;
    stack->data = (int *)malloc(sizeof(int) * stack->capacity);
    if (stack->data == NULL) {
        perror("Failed to allocate memory for stack");
        exit(EXIT_FAILURE);
    }
}

// Push value to stack
void push(IntStack *stack, int value) {
    if (stack->top + 1 >= stack->capacity) {
        stack->capacity *= 2;
        stack->data = (int *)realloc(stack->data, sizeof(int) * stack->capacity);
        if (stack->data == NULL) {
            perror("Failed to reallocate memory for stack");
            exit(EXIT_FAILURE);
        }
    }
    stack->data[++stack->top] = value;
}

// Pop value from stack
int pop(IntStack *stack) {
    if (stack->top < 0) {
        fprintf(stderr, "Stack underflow!\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top--];
}

// Peek top value
int peek(IntStack *stack) {
    if (stack->top < 0) {
        fprintf(stderr, "Stack is empty!\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top];
}

// Check if stack is empty
bool isEmpty(IntStack *stack) {
    return stack->top == -1;
}

// Free the stack
void freeStack(IntStack *stack) {
    free(stack->data);
    stack->data = NULL;
    stack->top = -1;
    stack->capacity = 0;
}

void printstack(IntStack *stack) {
    if (!isEmpty(stack)) {
        printf("Stack: ");
        for (int i = 0; i <= stack->top; i++) {
            printf("%d - ", stack->data[i]);
        }
        printf("\n");
    }
}

// Demo
/*int main() {
    IntStack stack;
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
