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

int check_status(int task_id) {
    int old_task_id = isEmpty(&preemption_stack) ? -1 : peek(&preemption_stack);

    if (old_task_id != -1) {
        // printf("Preempting task[%d] with old task[%d]\n", task_id, old_task_id);
        task_stat_arr[old_task_id].state = BLOCK;
        task_stat_arr[old_task_id].preemption += 1;
#ifdef RECORD_PERF_COUNT
        disable_perf_counter(old_task_id);
        append_perf_counter(old_task_id);
#endif
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
        fprintf(stderr, "Task ID mismatch: task_id = %d, peek = %d\n", task_id, peek(&preemption_stack));
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
    // printf("Task[%d] inst %ld done at point %ld\n", task_id, task_stat_arr[task_id].instance, get_time_diff(g_start_time, end_time));
}

void init_task_status(int task_id) {
    task_stat_arr[task_id].state = SUSPEND;
    task_stat_arr[task_id].perf_open = 0;
    task_stat_arr[task_id].execution_times = malloc(INSTANCE_LIMIT * sizeof(long));
    if (!task_stat_arr[task_id].execution_times) {
        fprintf(stderr, "Failed to allocate memory for execution times\n");
        exit(1);
    }
}

void deinit_task_status(int task_id) {
    free(task_stat_arr[task_id].execution_times);
}

void* perf_wrapper(void* arg) {
    int task_id = *((int*)arg);
    int old_task_id;

    srand(time(NULL));
    barrier_wait(&barrier);
    usleep(10000);

#ifdef RECORD_PERF_COUNT
    init_perf_events(task_id);
#endif

    init_task_status(task_id);

    while (!stop) {
        old_task_id = check_status(task_id);
        clock_gettime(CLOCK_MONOTONIC, &task_stat_arr[task_id].start_time);

        task_array[task_id]();  // Simulated workload

        clock_gettime(CLOCK_MONOTONIC, &task_stat_arr[task_id].end_time);
        return_status(task_id, old_task_id);

        usleep(10000);
        // usleep((rand())%500);
    }

#ifdef RECORD_PERF_COUNT
    // printf("Task[%d] executed %ld times, preempted %d times\n", task_id, task_stat_arr[task_id].instance, task_stat_arr[task_id].preemption);
    deinit_pe(task_id);
#endif

    deinit_task_status(task_id);
}
