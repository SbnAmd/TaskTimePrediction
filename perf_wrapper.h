//
// Created by sbn on 5/16/25.
//

#ifndef PERF_WRAPPER_H
#define PERF_WRAPPER_H

#include "def.h"
#include "stack.h"
#include "barrier.h"
#include "perf.h"
int check_status(int task_id);
void return_status(int task_id, int old_task_id);
void* perf_wrapper(void* arg);

#endif //PERF_WRAPPER_H
