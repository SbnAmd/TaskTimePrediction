#pragma once
#include "def.h"

enum STATUS {
    RUN,
    BLOCK,
    SUSPEND
};

// enum IDX{
//     IDX_INSTRUCTIONS,
//     IDX_CPU_CYCLES,
//     IDX_CACHE_MISSES
// };


struct perf_param{
    long cycles;
    long instructions;
    long cache_misses;
    long cache_refs;
    long branch_misses;
    long branch_refs;
};

struct task_stat
{
    int id;
    long instance;
    int preemption;
    struct timespec start_time;
    struct timespec end_time;
    enum STATUS state;
    // PERF vars
    int perf_open;
    int fds[NUM_EVENTS];
    struct perf_event_attr pe[NUM_EVENTS];
    struct perf_param perf_parameters;
    long* execution_times;
};

typedef void (*Func)();
void pin_thread_to_core(int core_id);
long perf_event_open(struct perf_event_attr *hw_event, pid_t pid, int cpu, int group_fd, unsigned long flags);
void init_perf_events(int task_id, struct task_stat* task_stat_arr);