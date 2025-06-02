
#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include "stack.h"
#include "perf.h"
#include "utils.h"

#define RECORD_START_TIME(task_id) clock_gettime(CLOCK_MONOTONIC, &task_stat_arr[task_id].start_time)
#define RECORD_END_TIME(task_id) clock_gettime(CLOCK_MONOTONIC, &task_stat_arr[task_id].end_time)


int check_status(int task_id, struct task_stat* task_stat_arr, IntStack* preemption_stack);
void return_status(int task_id, int old_task_id, struct task_stat* task_stat_arr, IntStack* preemption_stack);
void init_task_status(int task_id, struct task_stat* task_stat_arr);
void deinit_task_status(int task_id, struct task_stat* task_stat_arr);


#endif //HELPER_FUNCTIONS_H
