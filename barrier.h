//
// Created by sbn on 5/20/25.
//

#ifndef BARRIER_H
#define BARRIER_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int count;
    int waiting;
    int generation;
} barrier_t;

void barrier_init(barrier_t *barrier, int count);
void barrier_wait(barrier_t *barrier);
void barrier_destroy(barrier_t *barrier);

#endif //BARRIER_H
