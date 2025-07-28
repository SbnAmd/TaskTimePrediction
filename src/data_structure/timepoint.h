//
// Created by sbn on 7/22/25.
//

#ifndef TIMEPOINT_H
#define TIMEPOINT_H


#include <time.h>
#include "perf.h"
#include "tp_stack.h"
#include "timeslice.h"

struct timepoint
{
    struct timespec time;
    struct perf_param perf_param;
    long preemption;
    char* task_name;
    int priority;

};

void reg_tp(struct timepoint* tp, long preemption, const char* task_name, int priority);
void save_time_slice(struct timepoint* end_tp, struct TPStack* tpstack, struct timeslice* ts_entry);

#endif //TIMEPOINT_H
