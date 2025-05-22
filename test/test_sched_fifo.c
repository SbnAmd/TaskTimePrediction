//
// Created by sbn on 5/22/25.
//

#include "test_sched_fifo.h"
extern barrier_t barrier;

void* thread_func(void* arg) {
    int prio = *(int*)arg;
    srand(time(NULL));
    barrier_wait(&barrier);
    printf("Thread with priority %d running\n", prio);
    while (1) {
        printf("Priority %d is running\n", prio);
        usleep((rand()*prio)%10000);
    }
    return NULL;
}

int run_sched_fifo_test() {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset); // Pin to core 0

    pthread_t threads[3];
    int prios[3] = {35, 30, 40};
    barrier_init(&barrier, 3);
    for (int i = 0; i < 3; i++) {
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
        pthread_attr_setschedpolicy(&attr, SCHED_FIFO);

        struct sched_param param;
        param.sched_priority = prios[i];
        pthread_attr_setschedparam(&attr, &param);

        pthread_create(&threads[i], &attr, thread_func, &prios[i]);
        pthread_setaffinity_np(threads[i], sizeof(cpu_set_t), &cpuset);
        pthread_attr_destroy(&attr);
        // usleep(1000); // Allow time to observe order
    }

    sleep(2);
    barrier_destroy(&barrier);
    return 0;
}

