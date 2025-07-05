//
// Created by sbn on 7/5/25.
//

#include "exe_ord.h"
#include "data_structure/stack.h"
#include "utils/thread_setup.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

IntStack thread_stack;
pthread_mutex_t mutex;
pthread_t threads[THREAD_COUNT];
int priority_array[THREAD_COUNT];
long workload_array[THREAD_COUNT];
int thread_ids[THREAD_COUNT];

struct thread_param thread_params[THREAD_COUNT];

// Fisher-Yates shuffle for int array
static void shuffle_int_array(int *array, int n)
{
    if (n > 1) {
        srand((unsigned int)time(NULL));
        for (int i = n - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
}

// Fisher-Yates shuffle for long array
static void shuffle_long_array(long *array, int n)
{
    if (n > 1) {
        srand((unsigned int)time(NULL));
        for (int i = n - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            long temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
}

// Generate a random long in the range [min, max]
static long random_long(long min, long max)
{
    if (max <= min) return min;
    // RAND_MAX may be less than the range, so combine two rand() calls
    unsigned long r = ((unsigned long)rand() << 32) | (unsigned long)rand();
    return min + (r % (max - min + 1));
}

void init_priorities(int* priority_array)
{
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        priority_array[i] = i+PRIORITY_OFFSET;
    }
    shuffle_int_array(priority_array, THREAD_COUNT);
}

void init_workloads(long* workload_array)
{
    for (int i = 0; i < THREAD_COUNT; i++)
    {
        workload_array[i] = random_long(10000, 10000000);
    }
    shuffle_long_array(workload_array, THREAD_COUNT);
}

void* workload_wrapper(void* arg)
{
    struct thread_param *params = (struct thread_param *)arg;
    int thread_id = params->thread_id;
    long workload = params->workload;

    // Ensure the thread ID is within bounds
    if (thread_id < 0 || thread_id >= THREAD_COUNT) {
        fprintf(stderr, "Invalid thread ID: %d\n", thread_id);
        return NULL;
    }

    // Simulate workload by sleeping for the specified duration
    usleep(100000);
    pthread_mutex_lock(&mutex);
    push(&thread_stack, thread_id);
    printf("Thread %d woke up workload of %ld loops\n", thread_id, workload);
    printstack(&thread_stack);
    pthread_mutex_unlock(&mutex);

    for (int j = 0 ; j < REPETITION; j++)
    {
        for (long i = 0; i < workload; i++);
        // usleep(workload);
    }


    pthread_mutex_lock(&mutex);
    printf("Thread %d finished\n", thread_id);
    if (!isEmpty(&thread_stack))
    {
        if (peek(&thread_stack) == thread_id)
            pop(&thread_stack);
        else
        {
            printf("Mismatch in thread stack, current thread ID: %d, expected: %d\n", thread_id, peek(&thread_stack));
            exit(1);
        }
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void setup()
{
    initStack(&thread_stack);
    init_priorities(priority_array);
    init_workloads(workload_array);

    for (int i = 0; i < THREAD_COUNT; i++) {
        thread_ids[i] = i;
        thread_params[i].thread_id = i;
        thread_params[i].workload = workload_array[i];
        create_thread(&threads[i], workload_wrapper, &thread_params[i],  priority_array[i], TEST_CORE);
        printf("Task[%d] with priority %d created\n", i, priority_array[i]);
    }

}

int main()
{

    setup();

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        pthread_join(threads[i], NULL);
    }

};