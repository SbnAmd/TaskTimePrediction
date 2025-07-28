#include "perf_wrapper.h"

/* Array of task status structs.  One for each thread.  Each thread has its own */
struct task_stat task_stat_arr[NUM_THREADS];
timeslice_t** ptr_slice_array[NUM_THREADS];
/* Stack for holding preempted tasks */
IntStack preemption_stack;
TPStack_t tpstack;
long g_preemption_counter = 0;
/* Mutex for accessing the stack */
pthread_mutex_t stack_mtx;

/* The array of benchmarks */
extern Func task_array[NUM_THREADS];

// extern const char* mibench_function_names[NUM_THREADS];
// extern void (*mibench_functions[NUM_THREADS])();

extern struct timespec g_start_time;
int event_open[NUM_THREADS] = {0};
extern int  g_stop;
extern barrier_t barrier;
extern uint64_t event_configs[NUM_EVENTS];

void print_fds(int task_id) {
    for (int i = 0; i < NUM_EVENTS; ++i) {
        printf("Task_ID[%d] Event[%d] Fd = %d \n", task_id, i, task_stat_arr[task_id].fds[i]);
    }
}

void* perf_wrapper(void *arg) {
    int task_id = *((int*)arg);
    int old_task_id;
    long task_count = 0;
    srand(time(NULL));
    timeslice_t* timeslice_array = malloc(sizeof(timeslice_t) * TIMESLICE_LEN);
    timepoint_t tp;
    /* Initializing the status of each thread */
    init_task_status(task_id, task_stat_arr);

#ifdef RECORD_PERF_COUNT
    init_perf_events(task_id);
#endif

    /* A simple barrier to ensure that all threads are ready before starting */
    barrier_wait(&barrier);

    // usleep(10000);

    /* Main loop of the thread */
    while (!g_stop) {

        // todo : add lock
        if (!isEmpty(&preemption_stack))
        {
            g_preemption_counter++;
        }

        /* Register current timepoint */
        reg_tp(&tp, g_preemption_counter, mibench_function_names[task_id], task_id);
        push_tp(&tpstack, tp);

        /* Check if any task is preempted.  If so, changes the status of the task. */
        old_task_id = check_status(task_id, task_stat_arr, &preemption_stack);

        /* Each thread runs its own workload.  The workload is a function pointer. */
        mibench_functions[task_id]();

        /* After finishing the workload, the task status is updated. */
        return_status(task_id, old_task_id, task_stat_arr, &preemption_stack);

        /* Save timeslice */
        reg_tp(&tp, g_preemption_counter, mibench_function_names[task_id], task_id);
        save_time_slice(&tp, &tpstack, &timeslice_array[task_count]);
        pop_tp(&tpstack);

        /* To add some variation in execution time, we sleep for a random amount of time. */
        usleep(10000);
        task_count++;
    }


#ifdef RECORD_PERF_COUNT

    save_result(task_id, task_stat_arr);

    /* De initialize the perf events.  This will close the fds. */
    deinit_pe(task_id);
    fprintf(stderr, "Task[%d] executed %ld times\n",task_id, task_count);
#endif



    /* De initialize the task status.  This will free the execution times array. */
    deinit_task_status(task_id, task_stat_arr);
}
