
#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include "stack.h"
#include "perf.h"
#include <stdio.h>
#include "utils.h"
#include "mibench.h"

#define PREFIX_LOG_PATH "/home/sbn/Work/Paper/perf_counter_exploit/log/"
#define RECORD_START_TIME(task_id) clock_gettime(CLOCK_MONOTONIC, &task_stat_arr[task_id].start_time[task_stat_arr[task_id].instance])
#define RECORD_END_TIME(task_id) clock_gettime(CLOCK_MONOTONIC, &task_stat_arr[task_id].end_time[task_stat_arr[task_id].instance])
#define START_ABS_TIME(task_id, inst) (long)(task_stat_arr[task_id].start_time[inst].tv_nsec + (task_stat_arr[task_id].start_time[inst].tv_sec * 1000000000))
#define END_ABS_TIME(task_id, inst) (long)(task_stat_arr[task_id].end_time[inst].tv_nsec + (task_stat_arr[task_id].end_time[inst].tv_sec * 1000000000))
#define EXECUTION_TIME(task_id, inst) (END_ABS_TIME(task_id, inst) - START_ABS_TIME(task_id, inst))

int check_status(int task_id, struct task_stat* task_stat_arr, IntStack* preemption_stack);
void return_status(int task_id, int old_task_id, struct task_stat* task_stat_arr, IntStack* preemption_stack);
void init_task_status(int task_id, struct task_stat* task_stat_arr);
void deinit_task_status(int task_id, struct task_stat* task_stat_arr);
void save_result(int task_id, struct task_stat* task_stat_arr);


#endif //HELPER_FUNCTIONS_H
