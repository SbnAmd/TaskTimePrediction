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

void initStack_tp(TPStack *stack);
void push_tp(TPStack *stack, struct timepoint value);
struct timepoint pop_tp(TPStack *stack);
struct timepoint peek_tp(TPStack *stack);
bool isEmpty_tp(TPStack *stack);
void freeStack_tp(TPStack *stack);

#endif //TP_STACK_H
