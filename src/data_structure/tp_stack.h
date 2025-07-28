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

void initStack_tp(struct TPStack *stack);
void push_tp(struct TPStack *stack, struct timepoint value);
struct timepoint pop_tp(struct TPStack *stack);
struct timepoint peek_tp(struct TPStack *stack);
bool isEmpty_tp(struct TPStack *stack);
void freeStack_tp(struct TPStack *stack);

#endif //TP_STACK_H
