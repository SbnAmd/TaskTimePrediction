//
// Created by sbn on 5/22/25.
//

#ifndef TEST_SCHED_FIFO_H
#define TEST_SCHED_FIFO_H

#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include "../src/wrapper/perf_wrapper.h"

void* thread_func(void* arg);

int run_sched_fifo_test();



#endif //TEST_SCHED_FIFO_H
