//
// Created by sbn on 5/16/25.
//

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "perf_wrapper.h"
#include "barrier.h"
#include "perf.h"
#include "utils.h"
#define MAX_PRIORITY 90
#define MIN_PRIORITY 30

void init_tasks();
void init_sched();
void deinit();
void fillPriorityArray();

#endif //SCHEDULER_H
