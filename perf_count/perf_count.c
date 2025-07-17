
#include "perf_count.h"

#include <stdint.h>


long perf_event_open(struct perf_event_attr *hw_event, pid_t pid, int cpu, int group_fd, unsigned long flags)
{
    return syscall(__NR_perf_event_open, hw_event, pid, cpu, group_fd, flags);
}

void pin_thread_to_core(int core_id) {
    cpu_set_t cpuset;

    if (core_id < 0 || core_id >= 8) {
        perror("Wrong core id");
        exit(1);
    }

    CPU_ZERO(&cpuset);
    CPU_SET(core_id, &cpuset);

    int ret = pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
    if (ret != 0) {
        fprintf(stderr, "Failed to set affinity for core %d: %s\n", core_id, strerror(ret));
    }
}

void handle_perf_event_error(const char* action) {

    perror(action);
    exit(1);

}

void reset_perf_counter(int fd) {

    /* Reset the whole group */
    if (ioctl(fd, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP) == -1) {
        handle_perf_event_error("Reset failed");
    }

}

void enable_perf_counter(int fd) {

    /* Enable the whole group */
    if (ioctl(fd, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP) == -1) {
        handle_perf_event_error("Enable failed");
    }

}

void disable_perf_counter(int fd) {

    /* Disable the whole group */
    if (ioctl(fd, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP) == -1) {
        handle_perf_event_error("Disable failed");
    }

}

void read_perf_counter(int fd, size_t expected_size, void *raw_buf, int event_count) {

    if (!raw_buf) {
        perror("malloc failed");
        return;
    }

    /* Read the whole group */
    if (read(fd, raw_buf, expected_size) == -1) {
        perror("Group read failed");
        return;
    }

    /* Check how many events have been read */
    uint64_t nr = *(uint64_t *)raw_buf;
    if (nr != event_count || event_count < 0) {
        fprintf(stderr, "Unexpected number of events: %llu\n", nr);
    }
}