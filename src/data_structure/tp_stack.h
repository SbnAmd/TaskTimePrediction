//
// Created by sbn on 7/22/25.
//

#ifndef TP_STACK_H
#define TP_STACK_H
#include "timepoint.h"

typedef struct {
    struct timepoint *data;
    int top;
    int capacity;
} TPStack;

void initStack(TPStack *stack);
void push(TPStack *stack, struct timepoint value);
struct timepoint pop(TPStack *stack);
struct timepoint peek(TPStack *stack);
bool isEmpty(TPStack *stack);
void freeStack(TPStack *stack);

#endif //TP_STACK_H
