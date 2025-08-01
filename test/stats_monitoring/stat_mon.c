
#include "stat_mon.h"

#include <stdio.h>
#include <unistd.h>

int task_matrix[NUM_EXECUTIONS][NUM_THREADS];
long delay_matrix[NUM_EXECUTIONS][NUM_THREADS];
pthread_t threads[NUM_THREADS];
int priority_array[NUM_THREADS];
int thread_ids[NUM_THREADS];
int g_stop;
TPStack_t tpstack;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
long g_preemption_counter = 0;
// Fisher-Yates shuffle for int array
static void shuffle_int_array(int *array, int n)
{
    if (n > 1) {

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
        // srand((unsigned int)time(NULL));
        for (int i = n - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            long temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
}

void print_matrix(int* ptr, long rows, long cols)
{
    for (long i = 0 ; i < rows; i++)
    {
        for (long j = 0 ; j < cols; j++)
        {
            printf("%d\t", (int)ptr[i*cols + j]);
        }
        printf("\n");
    }
}

void init_task_matrix()
{
    int task_id_array[NUM_THREADS] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};//, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21};

    for (long i = 0; i < NUM_EXECUTIONS; i++)
    {
        for (int j = 0; j < NUM_THREADS; j++)
        {
            task_matrix[i][j] = task_id_array[j];
        }
        shuffle_int_array(task_matrix[i], NUM_THREADS);
    }

}

void init_delay_matrix()
{
    long delay_array[NUM_THREADS] = {0, 1000, 200, 3000, 400, 5000, 600, 7000, 800, 9000};//, 100, 1100, 1200, 1300, 1400, 15000, 16000, 17000, 18000, 19000, 20000, 21000};

    for (long i = 0; i < NUM_EXECUTIONS; i++)
    {
        for (int j = 0; j < NUM_THREADS; j++)
        {
            delay_matrix[i][j] = delay_array[j];
        }
        shuffle_long_array(delay_array, NUM_THREADS);
    }
}

void init_priorities(int* priority_array)
{
    for (int i = 0; i < NUM_THREADS; i++)
    {
        priority_array[i] = i+PRIORITY_OFFSET;
    }
    shuffle_int_array(priority_array, NUM_THREADS);
}

void* thread_task(void *arg)
{
    int task_id = *((int*) arg);
    // long execution_counter = 0;
    initStack_tp(&tpstack);
    if (task_id >= NUM_THREADS)
    {
        perror("The Task_id exceeded NUM_THREADS");
        exit(1);
    }
    timeslice_t* timeslice_array = malloc(sizeof(timeslice_t) * TIMESLICE_LEN);
    timepoint_t tp;

    // printf("Task id %d\n", task_id);
    for (long i = 0; i < NUM_EXECUTIONS; i++)
    {
        /* Register current timepoint */
        pthread_mutex_lock(&mutex);
        reg_tp(&tp, g_preemption_counter, mibench_function_names[task_id], task_id);
        push_tp(&tpstack, tp);
        printf("**Pushed task %s with prio %d\n", tp.task_name, tp.priority);
        pthread_mutex_unlock(&mutex);

        // usleep(delay_matrix[i][task_id]);
        mibench_functions[task_matrix[i][task_id]]();

        pthread_mutex_lock(&mutex);
        reg_tp(&tp, g_preemption_counter, mibench_function_names[task_id], task_id);
        save_time_slice(&tp, &tpstack, &timeslice_array[i]);
        pop_tp(&tpstack);
        printf("//Poped task %s with prio %d\n", tp.task_name, tp.priority);
        pthread_mutex_unlock(&mutex);

        printf("Task[%d] %s, instance %ld\n", task_id, mibench_function_names[task_matrix[i][task_id]], i);
        printf("Task_ID[%d] \n\t Slice[%d]\n\t\t duration = %ld\n", task_id, i, timeslice_array[i].duration);
    }

    printf("Thread[%d], finished\n", task_id);
}

void setup()
{
    srand((unsigned int)time(NULL));
    // initStack(&thread_stack);
    // print_matrix(task_matrix, NUM_EXECUTIONS, NUM_THREADS);
    init_delay_matrix();
    init_task_matrix();
    init_priorities(priority_array);

    print_matrix(task_matrix, NUM_EXECUTIONS, NUM_THREADS);

    for (int i = 0; i < NUM_THREADS; i++)
    {
        thread_ids[i] = i;
        create_thread(&threads[i], thread_task, &thread_ids[i], priority_array[i], CORE);
        pthread_detach(threads[i]);
        printf("Task[%d] with priority %d created\n", i, priority_array[i]);
    }
}

int main()
{
    struct sched_param param;

    // pin_thread_to_core(CORE);
    // sleep(1);
    // param.sched_priority = 60;
    // if (sched_setscheduler(0, SCHED_FIFO, &param) == -1) {
    //     perror("sched_setscheduler");
    //     exit(EXIT_FAILURE);
    // }

    setup();
    // sleep(5);
    // for (int i = 0; i < 1000; i++)
    // {
    //     usleep(5000);
    //     sched_yield();
    // }
    usleep(5000000);
    // for (int i = 0; i < NUM_THREADS; i++)
    // {
    //     pthread_join(threads[i], NULL);
    // }
    g_stop = 1;
    usleep(500000);
    printf("Exiting main thread\n");
    return 0;

};