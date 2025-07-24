//
// Created by sbn on 7/22/25.
//

#include "timepoint.h"

void reg_tp(struct timepoint* tp, long preemption, char* task_name, int priority)
{
    clock_gettime(CLOCK_MONOTONIC, &tp->time);

    //todo : add perf event
    tp->preemption = preemption;
    tp->task_name = task_name;
    tp->priority = priority;
}

void add_to_tp_stack(struct timepoint* tp, TPStack* tpstack)
{
    push_tp(tpstack, *tp);
}

void create_timeslice(struct timeslice* ts, struct timepoint* start_tp, struct timepoint* end_tp)
{
    ts->duration = (end_tp->time.tv_sec - start_tp->time.tv_sec) * 1000000000 + (end_tp->time.tv_nsec - start_tp->time.tv_nsec);
    ts->interrupts = (int)(end_tp->preemption - start_tp->preemption);
    ts->start_time = start_tp->time;
    ts->name = strdup(start_tp->task_name);
}

void save_time_slice(struct timepoint* end_tp, TPStack* tpstack, struct timeslice* ts_entry)
{
    struct timepoint ltp = peek_tp(tpstack);

    if (end_tp->priority != ltp.priority || strcmp(end_tp->task_name, ltp.task_name)!=0)
    {
        perror("TPStack task mismatch!");
        exit(1);
    }

    create_timeslice(ts_entry, &ltp, end_tp);
}