#include "perf.h"

extern uint64_t event_configs[NUM_EVENTS];
extern IntStack preemption_stack;
extern struct task_stat task_stat_arr[NUM_THREADS];
extern int event_open[NUM_THREADS];

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


void init_perf_events(int task_id) {

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

void deinit_pe(int task_id) {
    for (int i = 0; i < NUM_EVENTS; ++i)
        close(task_stat_arr[task_id].fds[i]);
}

void handle_perf_event_error(const char* action, int task_id) {
    perror(action);
//    print_fds(task_id);
    printstack(&preemption_stack);
    exit(1);
}

void reset_perf_counter(int task_id) {
    if (event_open[task_id] == 0) {
        if (ioctl(task_stat_arr[task_id].fds[0], PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP) == -1) {
            handle_perf_event_error("Reset failed", task_id);
        }
    }
}

void enable_perf_counter(int task_id) {
    if (event_open[task_id] == 0) {
        if (ioctl(task_stat_arr[task_id].fds[0], PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP) == -1) {
            handle_perf_event_error("Enable failed", task_id);
        }
        task_stat_arr[task_id].perf_open = 1;
        event_open[task_id] = 1;
    }
}

void disable_perf_counter(int task_id) {
    if (event_open[task_id] == 1) {
        if (ioctl(task_stat_arr[task_id].fds[0], PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP) == -1) {
            handle_perf_event_error("Disable failed", task_id);
        }
        task_stat_arr[task_id].perf_open = 0;
        event_open[task_id] = 0;
    }
}

void read_perf_counter(int task_id) {
    long long buffer[NUM_EVENTS];
    for (int i = 0; i < NUM_EVENTS; ++i) {
        if (read(task_stat_arr[task_id].fds[i], &buffer[i], sizeof(long long)) == -1) {
            perror("Read failed");
        }
    }
    memcpy(&task_stat_arr[task_id].perf_parameters, buffer, sizeof(struct perf_param));
}

void append_perf_counter(int task_id) {
    long long buffer[NUM_EVENTS] = {0};
    long long buffer1[NUM_EVENTS] = {0};

    memcpy(buffer1, &task_stat_arr[task_id].perf_parameters, sizeof(struct perf_param));
    for (int i = 0; i < NUM_EVENTS; ++i) {
        if (read(task_stat_arr[task_id].fds[i], &buffer[i], sizeof(long long)) == -1) {
            perror("Read failed");
        }
        buffer[i] += buffer1[i];
    }
    memcpy(&task_stat_arr[task_id].perf_parameters, buffer, sizeof(struct perf_param));
}

