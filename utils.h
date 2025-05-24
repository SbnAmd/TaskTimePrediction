//
// Created by sbn on 5/24/25.
//

#ifndef UTILS_H
#define UTILS_H

#include "def.h"

void set_current_thread_sched_fifo(int priority);
void create_thread(pthread_t *thread, void *(*start_routine)(void *), void *arg, int priority, int core);


#endif //UTILS_H
