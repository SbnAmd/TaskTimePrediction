#pragma once
#include "../def.h"
#include "../data_structure/stack.h"

enum STATUS {
    RUN,
    BLOCK,
    SUSPEND
};

/* This order must be kept and not changed */
struct perf_param{
    uint64_t cycles;
    uint64_t instructions;
    uint64_t cache_misses;
    uint64_t cache_refs;
    uint64_t branch_misses;
    uint64_t branch_refs;
    uint64_t stalled_cycles_frontend;
    uint64_t stalled_cycles_backend;
    uint64_t page_faults;
    uint64_t context_switches;
    uint64_t cpu_migrations;
    uint64_t page_faults_maj;
    uint64_t alignment_faults;
    uint64_t emulation_faults;
    uint64_t cache_result_access;
    uint64_t cache_result_miss;
};

struct task_stat
{
    int id;
    long instance;
    int* preemption;
    struct timespec* start_time;
    struct timespec* end_time;
    enum STATUS state;
    // PERF vars
    int perf_open;
    int fds[NUM_EVENTS];
    struct perf_event_attr pe[NUM_EVENTS];
    struct perf_param* perf_parameters;
    long* execution_times;
};

typedef void (*Func)();
void pin_thread_to_core(int core_id);
long perf_event_open(struct perf_event_attr *hw_event, pid_t pid, int cpu, int group_fd, unsigned long flags);
void init_perf_events(int task_id);
void deinit_pe(int task_id);
void handle_perf_event_error(const char* action, int task_id);
void reset_perf_counter(int task_id);
void enable_perf_counter(int task_id);
void disable_perf_counter(int task_id);
void read_perf_counter(int task_id);
void append_perf_counter(int task_id);