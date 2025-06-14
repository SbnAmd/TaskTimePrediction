#include "thread_setup.h"


pthread_t threads[NUM_THREADS];
pthread_t sched_thread;
int thread_ids[NUM_THREADS];
int sched_id;
int priority_array[NUM_THREADS];
barrier_t barrier;
extern IntStack preemption_stack;
struct timespec g_start_time;


void fillPriorityArray() {
    // Seed the random number generator (do this only once in your program)
    srand(time(NULL));

    for (int i = 0; i < NUM_THREADS; i++) {
        // Generate a random number within the specified range
        priority_array[i] = (rand() % (MAX_PRIORITY - MIN_PRIORITY + 1)) + MIN_PRIORITY;
    }
}

void init_tasks(){
    int ret;
    pin_thread_to_core(CORE);
    usleep(100000);
    initStack(&preemption_stack);
    barrier_init(&barrier, NUM_THREADS);

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;

        create_thread(&threads[i], perf_wrapper, &thread_ids[i],  priority_array[i], CORE);
        printf("Task[%d] (%s) with priority %d created\n", i, mibench_function_names[i], priority_array[i]);
        usleep(100);
    }

}

#ifdef SCHEDULER
void init_sched(){

    cpu_set_t cpuset;
    pthread_attr_t attr;
    struct sched_param schedparam;
    int thread_ids[NUM_THREADS];
    int ret;

    ret = pthread_attr_init(&attr);
    if (ret != 0) {
        perror("pthread_attr_init");
        exit(EXIT_FAILURE);
    }

    // Set the scheduling policy to FIFO
    ret = pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
    if (ret != 0) {
        perror("pthread_attr_setschedpolicy");
        exit(EXIT_FAILURE);
    }

     // Set the priority (important for FIFO scheduling)
    schedparam.sched_priority = SCHED_PRIO;
    ret = pthread_attr_setschedparam(&attr, &schedparam);
     if (ret != 0) {
        perror("pthread_attr_setschedparam");
        exit(EXIT_FAILURE);
    }


    // Create the sched thread
    ret = pthread_create(&sched_thread, &attr, my_thread_function, NULL);
    if (ret != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    // Set CPU affinity for each thread
    CPU_ZERO(&cpuset);
    CPU_SET(CORE+1, &cpuset); // Bind thread i to CPU i (0-indexed)
    ret = pthread_setaffinity_np(sched_thread, sizeof(cpu_set_t), &cpuset);
    if (ret != 0) {
        perror("pthread_setaffinity_np");
        // Don't exit, but print a warning.  Affinity setting can fail if the CPU
        // doesn't exist.  The program can still run, but without the desired affinity.
        fprintf(stderr, "Warning: Could not set CPU affinity for thread %d\n", i);
    }


    pthread_attr_destroy(&attr);
}
#endif


void deinit(){
    int ret;

#ifdef SCHEDULER
    ret = pthread_join(sched_thread, NULL);
        if (ret != 0) {
            perror("sched_thread join");
            exit(EXIT_FAILURE);
        }
#endif


    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        ret = pthread_join(threads[i], NULL);
        if (ret != 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }
    barrier_destroy(&barrier);
    printf("All threads completed.\n");

}



