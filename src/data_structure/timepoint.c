//
// Created by sbn on 7/22/25.
//

#include "timepoint.h"

#include "tp_stack.h"

void reg_tp(timepoint_t* tp, long preemption, const char* task_name, int priority)
{
    clock_gettime(CLOCK_MONOTONIC, &tp->time);

    //todo : add perf event
    tp->preemption = preemption;
    tp->task_name = task_name;
    tp->priority = priority;
}


void create_timeslice(timeslice_t* ts, timepoint_t* start_tp, timepoint_t* end_tp)
{
    ts->duration = (end_tp->time.tv_sec - start_tp->time.tv_sec) * 1000000000 + (end_tp->time.tv_nsec - start_tp->time.tv_nsec);
    ts->interrupts = (int)(end_tp->preemption - start_tp->preemption);
    ts->start_time = start_tp->time;
    ts->name = strdup(start_tp->task_name);
}

void save_time_slice(timepoint_t* end_tp, TPStack_t* tpstack, timeslice_t* ts_entry)
{
    timepoint_t ltp = peek_tp(tpstack);

    if (end_tp->priority != ltp.priority || strcmp(end_tp->task_name, ltp.task_name)!=0)
    {
        perror("TPStack task mismatch!");
        exit(1);
    }

    create_timeslice(ts_entry, &ltp, end_tp);
}