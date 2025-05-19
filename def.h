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

#define NUM_EVENTS      6
#define TASK_PRIO       50
#define SCHED_PRIO      80
#define NUM_THREADS     10
#define CORE            5
#define INSTANCE_LIMIT  2000


#endif //DEF_H
