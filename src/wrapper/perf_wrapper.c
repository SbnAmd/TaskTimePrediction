#include "perf_wrapper.h"

/* Array of task status structs.  One for each thread.  Each thread has its own */
struct task_stat task_stat_arr[NUM_THREADS];

/* Stack for holding preempted tasks */
IntStack preemption_stack;

/* Mutex for accessing the stack */
pthread_mutex_t stack_mtx;

/* The array of benchmarks */
extern Func task_array[NUM_THREADS];

extern struct timespec g_start_time;
int event_open[NUM_THREADS] = {0};
extern int  stop;
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

    srand(time(NULL));

    /* Initializing the status of each thread */
    init_task_status(task_id, task_stat_arr);

#ifdef RECORD_PERF_COUNT
    init_perf_events(task_id);
#endif

    /* A simple barrier to ensure that all threads are ready before starting */
    barrier_wait(&barrier);
    usleep(10000);

    /* Main loop of the thread */
    while (!stop) {

        /* Check if any task is preempted.  If so, changes the status of the task. */
        old_task_id = check_status(task_id, task_stat_arr, &preemption_stack);


        /* Each thread runs its own workload.  The workload is a function pointer. */
        task_array[task_id]();


        /* After finishing the workload, the task status is updated. */
        return_status(task_id, old_task_id, task_stat_arr, &preemption_stack);

        /* To add some variation in execution time, we sleep for a random amount of time. */
        usleep(10000);
    }

#ifdef RECORD_PERF_COUNT
    // printf("Task[%d] executed %ld times, preempted %d times\n", task_id, task_stat_arr[task_id].instance, task_stat_arr[task_id].preemption);

    /* De initialize the perf events.  This will close the fds. */
    deinit_pe(task_id);
#endif

    /* De initialize the task status.  This will free the execution times array. */
    deinit_task_status(task_id, task_stat_arr);
}
