//
// Created by sbn on 5/24/25.
//

#ifndef UTILS_H
#define UTILS_H

#include "def.h"
#include "perf.h"
void set_current_thread_sched_fifo(int priority);
void create_thread(pthread_t *thread, void *(*start_routine)(void *), void *arg, int priority, int core);
void print_perf_events();
long get_time_diff(struct timespec start, struct timespec end);

#endif //UTILS_H
