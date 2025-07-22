//
// Created by sbn on 7/22/25.
//

#ifndef TIMESLICE_H
#define TIMESLICE_H
#include <timepoint.h>

typedef struct timeslice
{
    long duration;
    int interrupts;
    struct timespec start_time;
    char* name;
};


#endif //TIMESLICE_H
