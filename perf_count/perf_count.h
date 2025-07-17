
#ifndef PERF_COUNT_H
#define PERF_COUNT_H

#define _GNU_SOURCE

#include <unistd.h>
#include <linux/perf_event.h>
#include <asm/unistd_64.h>
#include <pthread.h>
#include <string.h>
#include <sys/ioctl.h>
#include "../data_structure/stack.h"

long perf_event_open(struct perf_event_attr *hw_event, pid_t pid, int cpu, int group_fd, unsigned long flags);
void pin_thread_to_core(int core_id);
void reset_perf_counter(int fd);
void enable_perf_counter(int fd);
void disable_perf_counter(int fd);
void read_perf_counter(int fd, size_t expected_size, void *raw_buf, int event_count);
#endif //PERF_COUNT_H
