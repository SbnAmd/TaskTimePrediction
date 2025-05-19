//
// Created by sbn on 5/19/25.
//

#ifndef STACK_H
#define STACK_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *data;
    int top;
    int capacity;
} IntStack;

void initStack(IntStack *stack);
void push(IntStack *stack, int value);
int pop(IntStack *stack);
int peek(IntStack *stack);
bool isEmpty(IntStack *stack);
void freeStack(IntStack *stack);

#endif //STACK_H
