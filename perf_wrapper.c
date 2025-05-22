#include "perf_wrapper.h"
#include "perf.h"


struct task_stat task_stat_arr[NUM_THREADS];
extern struct timespec g_start_time;
IntStack preemption_stack;
pthread_mutex_t stack_mtx;
int event_open[NUM_THREADS] = {0};
extern Func task_array[NUM_THREADS];
extern int  stop;
extern barrier_t barrier;
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
    //fixme
    // if (task_stat_arr[task_id].perf_open == 1) {
    if (event_open[task_id] == 0) {
        if (ioctl(task_stat_arr[task_id].fds[0], PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP) == -1) {
            perror("Reset failed");
            print_fds(task_id);
            printstack(&preemption_stack);
            exit(1 );
        }
    }

}

void enable_perf_counter(int task_id) {
    // ioctl(fds[0], PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
    //fixme
    // if (task_stat_arr[task_id].perf_open == 0) {
    if (event_open[task_id] == 0) {
        if (ioctl(task_stat_arr[task_id].fds[0], PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP) == -1) {
            perror("Enable failed");
            print_fds(task_id);
            printstack(&preemption_stack);
            exit(1);
        }
        task_stat_arr[task_id].perf_open = 1;
        event_open[task_id] = 1;

    }
}

void disable_perf_counter(int task_id) {
    // ioctl(fds[0], PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);
    //fixme
    // if (task_stat_arr[task_id].perf_open == 1) {
    if (event_open[task_id] == 1) {
        if (ioctl(task_stat_arr[task_id].fds[0], PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP) == -1) {
            perror("Disable failed");
            print_fds(task_id);
            printstack(&preemption_stack);
            exit(1);
        }
        task_stat_arr[task_id].perf_open = 0;
        event_open[task_id] = 0;
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

    if (old_task_id != -1) {
        printf("Preempting task[%d] with old task[%d]\n", task_id, old_task_id);
        task_stat_arr[old_task_id].state = BLOCK;
        task_stat_arr[old_task_id].preemption += 1;
    }

    task_stat_arr[task_id].state = RUN;

#ifdef RECORD_PERF_COUNT
    reset_perf_counter(task_id);
    enable_perf_counter(task_id);
#endif

    push(&preemption_stack, task_id);

    return old_task_id;
}

void return_status(int task_id, int old_task_id) {
    struct timespec end_time;

#ifdef RECORD_PERF_COUNT
    disable_perf_counter(task_id);
    read_perf_counter(task_id);
#endif
    if (task_id != peek(&preemption_stack)) {
        printf("task_id = %d, peek = %d\n", task_id, peek(&preemption_stack));
        printstack(&preemption_stack);
        exit(1);
    }
    pop(&preemption_stack);

    if (!isEmpty(&preemption_stack)) {
        old_task_id = peek(&preemption_stack);
#ifdef RECORD_PERF_COUNT
        reset_perf_counter(old_task_id);
        enable_perf_counter(old_task_id);
#endif
        task_stat_arr[old_task_id].state = RUN;
    }


    task_stat_arr[task_id].state = SUSPEND;
    task_stat_arr[task_id].execution_times[task_stat_arr[task_id].instance] = get_time_diff(task_stat_arr[task_id].start_time, task_stat_arr[task_id].end_time);
    task_stat_arr[task_id].instance += 1;
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    printf("Task[%d] inst %ld done at point %ld\n", task_id, task_stat_arr[task_id].instance, get_time_diff(g_start_time, end_time));

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
    barrier_wait(&barrier);
    usleep(10000);
#ifdef RECORD_PERF_COUNT
    init_pe(task_id);
#endif
    init_task_status(task_id);
    while (stop == 0) {

        old_task_id = check_status(task_id);
        clock_gettime(CLOCK_MONOTONIC, &task_stat_arr[task_id].start_time);

        // Simulated workload
        task_array[task_id]();
        // printf("Task[%d] running\n", task_id);

        clock_gettime(CLOCK_MONOTONIC, &task_stat_arr[task_id].end_time);
        return_status(task_id, old_task_id);

        usleep(1000);
    }
#ifdef RECORD_PERF_COUNT
    printf("Task[%d] executed %ld times, preempted %d times\n", task_id, task_stat_arr[task_id].instance, task_stat_arr[task_id].preemption);
    deinit_pe(task_id);
#endif
    deinit_task_status(task_id);
}