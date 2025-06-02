//
// Created by sbn on 5/24/25.
//

#include "utils.h"

extern struct task_stat task_stat_arr[NUM_THREADS];

void set_current_thread_sched_fifo(int priority) {
    pthread_attr_t attr;
    struct sched_param schedparam;
    int ret;

    ret = pthread_attr_init(&attr);
    if (ret != 0) {
        perror("pthread_attr_init");
        exit(EXIT_FAILURE);
    }

    // Set the scheduling policy to FIFO
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    ret = pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
    if (ret != 0) {
        perror("pthread_attr_setschedpolicy");
        exit(EXIT_FAILURE);
    }

    // Set the priority (important for FIFO scheduling)
    schedparam.sched_priority = priority;
    ret = pthread_attr_setschedparam(&attr, &schedparam);
    if (ret != 0) {
        perror("pthread_attr_setschedparam");
        exit(EXIT_FAILURE);
    }

    ret = pthread_setschedparam(pthread_self(), SCHED_FIFO, &schedparam);
    if (ret != 0) {
        perror("pthread_setschedparam");
        exit(EXIT_FAILURE);
    }
}

void create_thread(pthread_t *thread, void *(*start_routine)(void *), void *arg, int priority, int core) {
    pthread_attr_t attr;
    struct sched_param schedparam;
    cpu_set_t cpuset;
    int ret;

    ret = pthread_attr_init(&attr);
    if (ret != 0) {
        perror("pthread_attr_init");
        exit(EXIT_FAILURE);
    }

    // Set the scheduling policy to FIFO
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    ret = pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
    if (ret != 0) {
        perror("pthread_attr_setschedpolicy");
        exit(EXIT_FAILURE);
    }

    // Set the priority (important for FIFO scheduling)
    schedparam.sched_priority = priority;
    ret = pthread_attr_setschedparam(&attr, &schedparam);
    if (ret != 0) {
        perror("pthread_attr_setschedparam");
        exit(EXIT_FAILURE);
    }

    // Create the thread
    ret = pthread_create(thread, &attr, start_routine, arg);
    if (ret != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    // Set CPU affinity for the thread
    CPU_ZERO(&cpuset);
    CPU_SET(core, &cpuset); // Bind thread i to CPU i (0-indexed)
    ret = pthread_setaffinity_np(*thread, sizeof(cpu_set_t), &cpuset);
    if (ret != 0) {
        perror("pthread_setaffinity_np");
        fprintf(stderr, "Warning: Could not set CPU affinity for thread %d\n", core);
    }

    pthread_attr_destroy(&attr);
}


void print_perf_events() {
    for (int task_id = 0; task_id < NUM_THREADS; ++task_id) {
        printf("Recorded Perf Events of task[%d] ----------- \n", task_id);
        printf("\tCycles : %ld\n", task_stat_arr[task_id].perf_parameters.cycles);
        printf("\tInstructions : %ld\n", task_stat_arr[task_id].perf_parameters.instructions);
        printf("\tCache Misses : %ld\n", task_stat_arr[task_id].perf_parameters.cache_misses);
        printf("\tCache References : %ld\n", task_stat_arr[task_id].perf_parameters.cache_refs);
        printf("\tBranch Misses : %ld\n", task_stat_arr[task_id].perf_parameters.branch_misses);
        printf("\tBranch References : %ld\n", task_stat_arr[task_id].perf_parameters.branch_refs);
        printf("\n\n");
    }
}

long get_time_diff(struct timespec start, struct timespec end) {
    long diff = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);
    return diff;
}
