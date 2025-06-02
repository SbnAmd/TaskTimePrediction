//
// Created by sbn on 5/20/25.
//

#include "../../barrier.h"


void barrier_init(barrier_t *barrier, int count) {
    barrier->count = count;
    barrier->waiting = 0;
    barrier->generation = 0;
    pthread_mutex_init(&barrier->mutex, NULL);
    pthread_cond_init(&barrier->cond, NULL);
}

void barrier_wait(barrier_t *barrier) {
    pthread_mutex_lock(&barrier->mutex);
    int gen = barrier->generation;

    barrier->waiting++;
    if (barrier->waiting == barrier->count) {
        // Last thread reached the barrier
        barrier->generation++;
        barrier->waiting = 0;
        pthread_cond_broadcast(&barrier->cond);
    } else {
        // Wait until all threads reach
        while (gen == barrier->generation)
            pthread_cond_wait(&barrier->cond, &barrier->mutex);
    }

    pthread_mutex_unlock(&barrier->mutex);
}

void barrier_destroy(barrier_t *barrier) {
    pthread_mutex_destroy(&barrier->mutex);
    pthread_cond_destroy(&barrier->cond);
}
