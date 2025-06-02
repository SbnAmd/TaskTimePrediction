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

/* Initializes the perf events for each thread */
void init_perf_events(int task_id) {

    struct perf_event_attr *pe = task_stat_arr[task_id].pe;
    int *fds = task_stat_arr[task_id].fds;

    /* Reset the memory of event array */
    memset(pe, 0, sizeof(task_stat_arr[task_id].pe));

    /* Configuring and initializing and opening fd of each event */
    for (int i = 0; i < NUM_EVENTS; ++i) {
        pe[i].type = PERF_TYPE_HARDWARE;
        pe[i].size = sizeof(struct perf_event_attr);
        pe[i].config = event_configs[i];
        pe[i].disabled = 1;  // Start all disabled
        pe[i].exclude_kernel = 1;
        pe[i].exclude_hv = 1;

        /* Grouping events  */
        int group_fd = (i == 0) ? -1 : fds[0];  // First is leader
        fds[i] = (int)perf_event_open(&pe[i], 0, -1, group_fd, 0);
        if (fds[i] == -1) {
            fprintf(stderr, "perf_event_open failed: %s\n", strerror(errno));
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

// void read_perf_counter(int task_id) {
//     long long buffer[NUM_EVENTS];
//     for (int i = 0; i < NUM_EVENTS; ++i) {
//         if (read(task_stat_arr[task_id].fds[i], &buffer[i], sizeof(long long)) == -1) {
//             perror("Read failed");
//         }
//     }
//     memcpy(&task_stat_arr[task_id].perf_parameters, buffer, sizeof(struct perf_param));
// }

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
    memcpy(&task_stat_arr[task_id].perf_parameters, buffer.values, sizeof(struct perf_param));
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
    memcpy(&task_stat_arr[task_id].perf_parameters, buffer.values, sizeof(struct perf_param));
}

