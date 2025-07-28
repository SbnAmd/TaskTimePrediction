//
// Created by sbn on 7/22/25.
//

#ifndef TP_STACK_H
#define TP_STACK_H
#include "timepoint.h"



void initStack_tp(TPStack_t *stack);
void push_tp(TPStack_t *stack, timepoint_t value);
timepoint_t pop_tp(TPStack_t *stack);
timepoint_t peek_tp(TPStack_t *stack);
bool isEmpty_tp(TPStack_t *stack);
void freeStack_tp(TPStack_t *stack);

#endif //TP_STACK_H
