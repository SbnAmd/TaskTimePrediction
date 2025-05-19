//
// Created by sbn on 5/16/25.
//

#ifndef PERF_WRAPPER_H
#define PERF_WRAPPER_H

#include "def.h"
#include "stack.h"


void init_pe(int task_id);
void deinit_pe(int task_id);
void reset_perf_counter(int task_id);
void enable_perf_counter(int task_id);
void disable_perf_counter(int task_id);
void read_perf_counter(int task_id);
void append_perf_counter(int task_id);
int check_status(int task_id);
void return_status(int task_id, int old_task_id);
void* perf_wrapper(void* arg);

#endif //PERF_WRAPPER_H
