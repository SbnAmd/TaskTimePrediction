//
// Created by sbn on 7/22/25.
//

#ifndef TIMEPOINT_H
#define TIMEPOINT_H


#include <time.h>
#include "perf.h"


typedef struct {
    struct timespec time;
    struct perf_param perf_param;
    long preemption;
    char* task_name;
    int priority;

}timepoint_t;

typedef struct
{
    long duration;
    int interrupts;
    struct timespec start_time;
    char* name;
}timeslice_t;

typedef struct{
    timepoint_t *data;
    int top;
    int capacity;
} TPStack_t;

void reg_tp(timepoint_t* tp, long preemption, const char* task_name, int priority);
void save_time_slice(timepoint_t* end_tp, TPStack_t* tpstack, timeslice_t* ts_entry);

#endif //TIMEPOINT_H
