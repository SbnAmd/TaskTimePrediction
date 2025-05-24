//
// Created by sbn on 5/24/25.
//

#include "utils.h"


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