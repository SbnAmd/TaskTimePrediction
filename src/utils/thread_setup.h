//
// Created by sbn on 5/16/25.
//

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "../wrapper/perf_wrapper.h"
#include "../data_structure/barrier.h"
#include "../perf_event/perf.h"
#include "utils.h"
#include "tp_stack.h"
#define MAX_PRIORITY 90
#define MIN_PRIORITY 30

void init_tasks();
void init_sched();
void deinit();
void fillPriorityArray();

#endif //SCHEDULER_H
