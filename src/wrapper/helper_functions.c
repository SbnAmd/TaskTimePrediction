
#include "helper_functions.h"

void init_task_status(int task_id, struct task_stat* task_stat_arr) {
    task_stat_arr[task_id].state = SUSPEND;
    task_stat_arr[task_id].perf_open = 0;
    task_stat_arr[task_id].execution_times = malloc(INSTANCE_LIMIT * sizeof(long));
    if (!task_stat_arr[task_id].execution_times) {
        fprintf(stderr, "Failed to allocate memory for execution times\n");
        exit(1);
    }
}

int check_status(int task_id, struct task_stat* task_stat_arr, IntStack* preemption_stack) {
    RECORD_START_TIME(task_id);
    int old_task_id = isEmpty(preemption_stack) ? -1 : peek(preemption_stack);

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

    push(preemption_stack, task_id);
    return old_task_id;
}

void return_status(int task_id, int old_task_id, struct task_stat* task_stat_arr, IntStack* preemption_stack) {
    struct timespec end_time;

#ifdef RECORD_PERF_COUNT
    disable_perf_counter(task_id);
    read_perf_counter(task_id);
#endif

    if (task_id != peek(preemption_stack)) {
        fprintf(stderr, "Task ID mismatch: task_id = %d, peek = %d\n", task_id, peek(preemption_stack));
        printstack(preemption_stack);
        exit(1);
    }
    pop(preemption_stack);

    if (!isEmpty(preemption_stack)) {
        old_task_id = peek(preemption_stack);
#ifdef RECORD_PERF_COUNT
        reset_perf_counter(old_task_id);
        enable_perf_counter(old_task_id);
#endif
        task_stat_arr[old_task_id].state = RUN;
    }
    RECORD_END_TIME(task_id);
    task_stat_arr[task_id].state = SUSPEND;
    task_stat_arr[task_id].execution_times[task_stat_arr[task_id].instance] = get_time_diff(task_stat_arr[task_id].start_time, task_stat_arr[task_id].end_time);
    task_stat_arr[task_id].instance += 1;

    // printf("Task[%d] inst %ld done at point %ld\n", task_id, task_stat_arr[task_id].instance, get_time_diff(g_start_time, end_time));
}

void deinit_task_status(int task_id, struct task_stat* task_stat_arr) {
    free(task_stat_arr[task_id].execution_times);
}