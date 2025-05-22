#include "perf.h"

extern uint64_t event_configs[NUM_EVENTS];

void pin_thread_to_core(int core_id) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);

    int ret = pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
    if (ret != 0) {
        fprintf(stderr, "Failed to set affinity for core %d: %s\n", core_id, strerror(ret));
    }
}


long perf_event_open(struct perf_event_attr *hw_event, pid_t pid, int cpu, int group_fd, unsigned long flags)
{
    return syscall(__NR_perf_event_open, hw_event, pid, cpu, group_fd, flags);
}

void init_perf_events(int task_id, struct task_stat* task_stat_arr) {

    struct perf_event_attr *pe = task_stat_arr[task_id].pe;
    int *fds = task_stat_arr[task_id].fds;

    memset(pe, 0, sizeof(task_stat_arr[task_id].pe));
    for (int i = 0; i < NUM_EVENTS; ++i) {
        pe[i].type = PERF_TYPE_HARDWARE;
        pe[i].size = sizeof(struct perf_event_attr);
        pe[i].config = event_configs[i];
        pe[i].disabled = 1;  // Start all disabled
        pe[i].exclude_kernel = 1;
        pe[i].exclude_hv = 1;

        int group_fd = (i == 0) ? -1 : fds[0];  // First is leader
        fds[i] = (int)perf_event_open(&pe[i], 0, -1, group_fd, 0);
        if (fds[i] == -1) {
            fprintf(stderr, "perf_event_open failed: %s\n", strerror(errno));
            pthread_exit(NULL);
        }
    }
}

void deinit_pe(int task_id, struct task_stat* task_stat_arr) {
    for (int i = 0; i < NUM_EVENTS; ++i)
        close(task_stat_arr[task_id].fds[i]);
}

