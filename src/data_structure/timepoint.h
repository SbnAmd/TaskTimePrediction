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


#endif //TIMEPOINT_H
