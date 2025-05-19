#include "perf_wrapper.h"
#include "perf.h"


struct task_stat task_stat_arr[NUM_THREADS];

IntStack preemption_stack;

extern Func task_array[NUM_THREADS];
extern int  stop;

uint64_t event_configs[NUM_EVENTS] = {
    PERF_COUNT_HW_CPU_CYCLES,
    PERF_COUNT_HW_INSTRUCTIONS,
    PERF_COUNT_HW_CACHE_MISSES,
    PERF_COUNT_HW_CACHE_REFERENCES,
    PERF_COUNT_HW_BRANCH_MISSES,
    PERF_COUNT_HW_BRANCH_INSTRUCTIONS
};

void print_fds(int task_id) {
    for (int i = 0; i < NUM_EVENTS; ++i) {
        printf("Task_ID[%d] Event[%d] Fd = %d \n", task_id, i, task_stat_arr[task_id].fds[i]);
    }
}

long get_time_diff(struct timespec start, struct timespec end) {
    long diff = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);
    return diff;
}

void init_pe(int task_id) {

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

void reset_perf_counter(int task_id) {
    // ioctl(fds[0], PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);
    if (task_stat_arr[task_id].perf_open == 1) {
    // if (1) {
        if (ioctl(task_stat_arr[task_id].fds[0], PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP) == -1) {
            perror("Reset failed");
            print_fds(task_id);
            exit(1 );
        }
    }

}

void enable_perf_counter(int task_id) {
    // ioctl(fds[0], PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
    if (task_stat_arr[task_id].perf_open == 0) {
    // if (1) {
        if (ioctl(task_stat_arr[task_id].fds[0], PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP) == -1) {
            perror("Enable failed");
            print_fds(task_id);
            exit(1);
        }
        task_stat_arr[task_id].perf_open = 1;

    }
}

void disable_perf_counter(int task_id) {
    // ioctl(fds[0], PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);
    if (task_stat_arr[task_id].perf_open == 1) {
    // if (1) {
        if (ioctl(task_stat_arr[task_id].fds[0], PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP) == -1) {
            perror("Disable failed");
            print_fds(task_id);
            exit(1);
        }
        task_stat_arr[task_id].perf_open = 0;

    }
}

void read_perf_counter(int task_id) {
    long long buffer[NUM_EVENTS];
    for (int i = 0; i < NUM_EVENTS; ++i){
        // read(fds[i], &counts[i], sizeof(uint64_t));
        if (read(task_stat_arr[task_id].fds[i], &buffer[i], sizeof(long long)) == -1)
            perror("read failed");
    }
    memcpy(&task_stat_arr[task_id].perf_parameters, buffer, sizeof(struct perf_param));
}

void append_perf_counter(int task_id) {
    long long buffer[NUM_EVENTS]= {0};
    long long buffer1[NUM_EVENTS] = {0};

    memcpy(buffer1, &task_stat_arr[task_id].perf_parameters, sizeof(struct perf_param));
    for (int i = 0; i < NUM_EVENTS; ++i){
        // read(fds[i], &counts[i], sizeof(uint64_t));
        if (read(task_stat_arr[task_id].fds[i], &buffer[i], sizeof(long long)) == -1)
            perror("read failed");
        buffer[i] += buffer1[i];
    }
    memcpy(&task_stat_arr[task_id].perf_parameters, buffer, sizeof(struct perf_param));
}



int check_status(int task_id) {
    int old_task_id = -1;

    if (!isEmpty(&preemption_stack)) {
        old_task_id = peek(&preemption_stack);
    }
    push(&preemption_stack, task_id);

    if (old_task_id != -1) {
        // printf("Preempting task[%d] with old task[%d]\n", task_id, old_task_id);
        task_stat_arr[task_id].state = RUN;
        task_stat_arr[old_task_id].state = BLOCK;
        task_stat_arr[old_task_id].preemption += 1;
        // fixme
        disable_perf_counter(old_task_id);
        append_perf_counter(old_task_id);
    }else {
        task_stat_arr[task_id].state = RUN;
    }

    reset_perf_counter(task_id);
    enable_perf_counter(task_id);

    return old_task_id;
}

void return_status(int task_id, int old_task_id) {

    // if (old_task_id != -1) {
    //     //fixme
    //     reset_perf_counter(old_task_id);
    //     enable_perf_counter(old_task_id);
    //     task_stat_arr[old_task_id].state = RUN;
    // }
    disable_perf_counter(task_id);
    read_perf_counter(task_id);

    if (!isEmpty(&preemption_stack)) {
        pop(&preemption_stack);
        if (!isEmpty(&preemption_stack)) {
            old_task_id = peek(&preemption_stack);
            reset_perf_counter(old_task_id);
            enable_perf_counter(old_task_id);
            task_stat_arr[old_task_id].state = RUN;
        }
    }

    task_stat_arr[task_id].state = SUSPEND;
    task_stat_arr[task_id].execution_times[task_stat_arr[task_id].instance] = get_time_diff(task_stat_arr[task_id].start_time, task_stat_arr[task_id].end_time);
    task_stat_arr[task_id].instance += 1;


}

void init_task_status(int task_id) {
    task_stat_arr[task_id].state = SUSPEND;
    task_stat_arr[task_id].perf_open = 0;
    task_stat_arr[task_id].execution_times = malloc(INSTANCE_LIMIT * sizeof(long));
    if (task_stat_arr[task_id].execution_times == NULL) {
        printf("Failed to allocate memory for execution times\n");
        exit(1);
    }
}

void deinit_task_status(int task_id) {
    free(task_stat_arr[task_id].execution_times);
}


void* perf_wrapper(void* arg)
{
    int task_id = *((int*)arg);
    int old_task_id;
    printf("Task[%d] started \n", task_id);
    init_pe(task_id);
    init_task_status(task_id);
    while (stop == 0) {
        clock_gettime(CLOCK_MONOTONIC, &task_stat_arr[task_id].start_time);
        old_task_id = check_status(task_id);


        // Simulated workload

        task_array[task_id]();
        // printf("Task[%d] round %ld\n", task_id,cnt);

        clock_gettime(CLOCK_MONOTONIC, &task_stat_arr[task_id].end_time);
        return_status(task_id, old_task_id);
        usleep(1000);
    }
    printf("Task[%d] executed %ld times, preempted %d times\n", task_id, task_stat_arr[task_id].instance, task_stat_arr[task_id].preemption);
    deinit_pe(task_id);
    deinit_task_status(task_id);
}