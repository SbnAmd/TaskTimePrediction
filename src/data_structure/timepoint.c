//
// Created by sbn on 7/22/25.
//

#include "timepoint.h"


void add_to_tp_stack(struct timepoint* tp, long preemption, char* task_name, int priority, TPStack* tpstack)
{
    clock_gettime(CLOCK_MONOTONIC, &tp->time);

    //todo : add perf event
    tp->preemption = preemption;
    tp->task_name = task_name;
    tp->priority = priority;

    push(tpstack, *tp);
}

struct timeslice create_timeslice(struct timeslice* ts, struct timepoint* start_tp, struct timepoint* end_tp)
{
    ts->duration = (end_tp->time.tv_sec - start_tp->time.tv_sec) * 1000000000 + (end_tp->time.tv_nsec - start_tp->time.tv_nsec);

}

void save_time_slice(struct timepoint* tp, TPStack* tpstack, struct timeslice* ts_entry)
{
    struct timepoint ltp = peek(tpstack);

    if (tp->priority != ltp.priority || strcmp(tp->task_name, ltp.task_name)!=0)
    {
        perror("TPStack task msmatch!");
        exit(1);
    }

    *ts_entry = create_timeslice(ts_entry, &ltp, tp);
}