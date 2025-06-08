
#include "helper_functions.h"

void init_task_status(int task_id, struct task_stat* task_stat_arr) {
    task_stat_arr[task_id].state = SUSPEND;
    task_stat_arr[task_id].perf_open = 0;
    task_stat_arr[task_id].instance = 0;

    task_stat_arr[task_id].execution_times = malloc(INSTANCE_LIMIT * sizeof(long));
    if (!task_stat_arr[task_id].execution_times) {
        fprintf(stderr, "Failed to allocate memory for execution times\n");
        exit(1);
    }
    memset(task_stat_arr[task_id].execution_times, 0, INSTANCE_LIMIT * sizeof(long));

    task_stat_arr[task_id].preemption = malloc(INSTANCE_LIMIT * sizeof(int));
    if (task_stat_arr[task_id].preemption == NULL) {
        fprintf(stderr, "Failed to allocate memory for preemptions\n");
        exit(1);
    }
    memset(task_stat_arr[task_id].preemption, 0, INSTANCE_LIMIT * sizeof(int));

    task_stat_arr[task_id].start_time = malloc(INSTANCE_LIMIT * sizeof(struct timespec));
    if (!task_stat_arr[task_id].start_time) {
        fprintf(stderr, "Failed to allocate memory for start_time\n");
        exit(1);
    }
    memset(task_stat_arr[task_id].start_time, 0, INSTANCE_LIMIT * sizeof(struct timespec));

    task_stat_arr[task_id].end_time = malloc(INSTANCE_LIMIT * sizeof(struct timespec));
    if (!task_stat_arr[task_id].end_time) {
        fprintf(stderr, "Failed to allocate memory for end_time\n");
        exit(1);
    }
    memset(task_stat_arr[task_id].end_time, 0, INSTANCE_LIMIT * sizeof(struct timespec));

    task_stat_arr[task_id].perf_parameters = malloc(INSTANCE_LIMIT * sizeof(struct perf_param));
    if (!task_stat_arr[task_id].perf_parameters) {
        fprintf(stderr, "Failed to allocate memory for perf_parameters\n");
        exit(1);
    }
    memset(task_stat_arr[task_id].perf_parameters, 0, INSTANCE_LIMIT * sizeof(struct perf_param));

}

int check_status(int task_id, struct task_stat* task_stat_arr, IntStack* preemption_stack) {
    RECORD_START_TIME(task_id);
    int old_task_id = isEmpty(preemption_stack) ? -1 : peek(preemption_stack);

    if (old_task_id != -1) {
        // printf("Preempting task[%d] with old task[%d]\n", task_id, old_task_id);
        task_stat_arr[old_task_id].state = BLOCK;
        task_stat_arr[old_task_id].preemption[task_stat_arr[task_id].instance] += 1;
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
    // fixme : can be computed later
    // task_stat_arr[task_id].execution_times[task_stat_arr[task_id].instance] = get_time_diff(task_stat_arr[task_id].start_time, task_stat_arr[task_id].end_time);
    task_stat_arr[task_id].instance += 1;

    // printf("Task[%d] inst %ld done at point %ld\n", task_id, task_stat_arr[task_id].instance, get_time_diff(g_start_time, end_time));
}

void deinit_task_status(int task_id, struct task_stat* task_stat_arr) {
    free(task_stat_arr[task_id].execution_times);
    free(task_stat_arr[task_id].preemption);
    free(task_stat_arr[task_id].start_time);
    free(task_stat_arr[task_id].end_time);
    free(task_stat_arr[task_id].perf_parameters);
}

void append_perf_to_file(
    FILE* file,
    int preemptions,
    struct timespec start_time,
    struct timespec end_time,
    long execution_time,
    const struct perf_param* perf
) {
    // Print as CSV line, matching the header order
    char buffer[1024];
    sprintf(buffer,
        "%d,%09ld,%09ld,%ld.%09ld,%09ld,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu\n",
        preemptions,
        (start_time.tv_sec*1000000000 + start_time.tv_nsec),
        (end_time.tv_sec*1000000000 + end_time.tv_nsec),
        execution_time,
        perf->cycles,
        perf->instructions,
        perf->cache_misses,
        perf->cache_refs,
        perf->branch_misses,
        perf->branch_refs,
        perf->stalled_cycles_frontend,
        perf->stalled_cycles_backend,
        perf->page_faults,
        perf->context_switches,
        perf->cpu_migrations,
        perf->page_faults_maj,
        perf->alignment_faults,
        perf->emulation_faults,
        perf->cache_result_access,
        perf->cache_result_miss
        );
        fputs(buffer, file);
}

void save_result(int task_id, struct task_stat* task_stat_arr) {
    char filename[256];
    char* header= {
        "Preemptions ,"
        "Start Time (ns) ,"
        "End Time (ns) ,"
        "Execution Time (ns) ,"
        "Cycles ,"
        "Instructions ,"
        "Cache Misses ,"
        "Cache Refs ,"
        "Branch Misses ,"
        "Branch Refs ,"
        "Stalled Cycles Frontend ,"
        "Stalled Cycles Backend ,"
        "Page Faults ,"
        "Context Switches ,"
        "CPU Migrations ,"
        "Page Faults Major ,"
        "Alignment Faults ,"
        "Emulation Faults ,"
        "Cache Result Access ,"
        "Cache Result Miss"
    };
    // extern const char* mibench_function_names[NUM_THREADS];
    snprintf(filename, sizeof(filename), "%sresult_%s.txt", PREFIX_LOG_PATH, mibench_function_names[task_id]);
    FILE* file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Failed to open file %s for writing\n", filename);
        return;
    }

    fputs(header,file);
    for (int i = 0; i < INSTANCE_LIMIT; i++) {
        int per = task_stat_arr[task_id].preemption[i];
        append_perf_to_file(
            file,
            task_stat_arr[task_id].preemption[i],
            task_stat_arr[task_id].start_time[i],
           task_stat_arr[task_id].end_time[i],
            EXECUTION_TIME(task_id, i),
            &task_stat_arr[task_id].perf_parameters[i]
            );




    }
    fclose(file);
}
