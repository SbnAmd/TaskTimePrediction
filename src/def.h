//
// Created by sbn on 5/19/25.
//

#ifndef DEF_H
#define DEF_H


#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/syscall.h>
#include <sys/ioctl.h>
#include <linux/perf_event.h>
#include <asm/unistd.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <sched.h>
#define NUM_HW_EVENTS     6
#define NUM_SW_EVENTS     0//6
#define NUM_CACHE_EVENTS  0//2
#define NUM_EVENTS      (NUM_HW_EVENTS + NUM_SW_EVENTS + NUM_CACHE_EVENTS)
#define TASK_PRIO       50
#define SCHED_PRIO      80
#define NUM_THREADS     4
#define CORE            5
#define INSTANCE_LIMIT  200

#define RECORD_PERF_COUNT

#define PC
#ifdef PC
#define PREFIX_LOG_PATH "/home/sbn/Work/Development/C/TaskExecution/log/"
#else
#define PREFIX_LOG_PATH "/home/sbn/Work/Paper/perf_counter_exploit/log/"
#endif


#endif //DEF_H
