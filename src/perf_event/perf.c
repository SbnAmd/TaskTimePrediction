#include "perf.h"

extern uint64_t event_configs[NUM_EVENTS];
extern uint64_t hw_event_configs[NUM_HW_EVENTS];
extern uint64_t sw_event_configs[NUM_SW_EVENTS];
extern uint64_t cache_event_configs[NUM_CACHE_EVENTS];
extern IntStack preemption_stack;
extern struct task_stat task_stat_arr[NUM_THREADS];
extern int event_open[NUM_THREADS];
extern int g_stop;

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

/* Initializes the perf events for each thread */
void init_perf_events(int task_id) {
    struct perf_event_attr *pe = task_stat_arr[task_id].pe;
    int *fds = task_stat_arr[task_id].fds;

    // Clear the entire array of perf_event_attr
    memset(pe, 0, NUM_EVENTS * sizeof(struct perf_event_attr));

    int idx = 0;
    // Configure hardware events
    for (int i = 0; i < NUM_HW_EVENTS; ++i, ++idx) {
        pe[idx].type = PERF_TYPE_HARDWARE;
        pe[idx].size = sizeof(struct perf_event_attr);
        pe[idx].config = hw_event_configs[i];
        pe[idx].disabled = 1;
        pe[idx].exclude_kernel = 1;
        pe[idx].exclude_hv = 1;
    }
    // Configure software events
    for (int i = 0; i < NUM_SW_EVENTS; ++i, ++idx) {
        pe[idx].type = PERF_TYPE_SOFTWARE;
        pe[idx].size = sizeof(struct perf_event_attr);
        pe[idx].config = sw_event_configs[i];
        pe[idx].disabled = 1;
        pe[idx].exclude_kernel = 1;
        pe[idx].exclude_hv = 1;
    }
    // Configure cache events (assuming cache_event_configs is an array of structs with .cache, .op, .result)
    for (int i = 0; i < NUM_CACHE_EVENTS; ++i, ++idx) {
        pe[idx].type = PERF_TYPE_HW_CACHE;
        pe[idx].size = sizeof(struct perf_event_attr);
        // If cache_event_configs[i] is a struct, encode as below; otherwise, adjust as needed
        pe[idx].config = (cache_event_configs[i] << 16);
        pe[idx].disabled = 1;
        pe[idx].exclude_kernel = 1;
        pe[idx].exclude_hv = 1;
    }


    // Open perf events and group them
    for (int i = 0; i < NUM_EVENTS; ++i) {

        int group_fd = (i == 0) ? -1 : fds[0];
        fds[i] = (int)perf_event_open(&pe[i], 0, -1, group_fd, 0);
        printf("event[%d] task[%d] gstop = %d\n", i, task_id, g_stop);
        if (fds[i] == -1) {
            fprintf(stderr, "thread[%d] perf_event_open[%d] failed: %s\n",task_id, i, strerror(errno));
            // Consider handling error more gracefully if not in a thread
            pthread_exit(NULL);
        }
    }

    task_stat_arr[task_id].perf_open = 1;
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

        /* Reset the whole group */
        if (ioctl(task_stat_arr[task_id].fds[0], PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP) == -1) {
            handle_perf_event_error("Reset failed", task_id);
        }
    }
}

void enable_perf_counter(int task_id) {
    if (event_open[task_id] == 0) {

        /* Enable the whole group */
        if (ioctl(task_stat_arr[task_id].fds[0], PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP) == -1) {
            handle_perf_event_error("Enable failed", task_id);
        }
        task_stat_arr[task_id].perf_open = 1;
        event_open[task_id] = 1;
    }
}

void disable_perf_counter(int task_id) {
    if (event_open[task_id] == 1) {

        /* Disable the whole group */
        if (ioctl(task_stat_arr[task_id].fds[0], PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP) == -1) {
            handle_perf_event_error("Disable failed", task_id);
        }
        task_stat_arr[task_id].perf_open = 0;
        event_open[task_id] = 0;
    }
}

void read_perf_counter(int task_id) {
    struct {
        uint64_t nr;
        uint64_t values[NUM_EVENTS];
    } buffer;

    /* Selecting the group leader */
    int leader_fd = task_stat_arr[task_id].fds[0];  // fds[0] is the group leader

    /* Size of read */
    ssize_t expected_size = sizeof(buffer.nr) + sizeof(uint64_t) * NUM_EVENTS;

    /* Read the whole group */
    if (read(leader_fd, &buffer, expected_size) == -1) {
        perror("Group read failed");
        return;
    }

    /* Check how many events have been read */
    if (buffer.nr != NUM_EVENTS) {
        fprintf(stderr, "Unexpected number of events: %llu\n", buffer.nr);
        return;
    }

    // struct perf_param* p = &task_stat_arr[task_id].perf_parameters;
    // p->cycles         = buffer.values[0];
    // p->instructions   = buffer.values[1];
    // p->cache_misses   = buffer.values[2];
    // p->cache_refs     = buffer.values[3];
    // p->branch_misses  = buffer.values[4];
    // p->branch_refs    = buffer.values[5];
    // fixme : This is very unsafe, but it works for now
    /* Save result */
    memcpy(&task_stat_arr[task_id].perf_parameters[task_stat_arr[task_id].instance], buffer.values, sizeof(struct perf_param));
}

void append_perf_counter(int task_id) {

    uint64_t buffer1[NUM_EVENTS] = {0};

    struct {
        uint64_t nr;
        uint64_t values[NUM_EVENTS];
    } buffer;

    /* Selecting the group leader */
    int leader_fd = task_stat_arr[task_id].fds[0];  // fds[0] is the group leader

    /* Size of read */
    ssize_t expected_size = sizeof(buffer.nr) + sizeof(uint64_t) * NUM_EVENTS;

    /* Read the whole group */
    if (read(leader_fd, &buffer, expected_size) == -1) {
        perror("Group read failed");
        return;
    }

    /* Check how many events have been read */
    if (buffer.nr != NUM_EVENTS) {
        fprintf(stderr, "Unexpected number of events: %llu\n", buffer.nr);
        return;
    }

    // fixme : This is very unsafe, but it works for now
    memcpy(buffer1, &task_stat_arr[task_id].perf_parameters, sizeof(struct perf_param));
     /* Append */
    for (int i = 0; i < NUM_EVENTS; ++i) {
        buffer.values[i] += buffer1[i];
    }
    memcpy(&task_stat_arr[task_id].perf_parameters[task_stat_arr[task_id].instance], buffer.values, sizeof(struct perf_param));
}


