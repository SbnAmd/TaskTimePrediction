//
// Created by sbn on 5/15/25.
//

#include "main.h"


int main(){

    printf("Starting the threads setup ...\n");

    fillPriorityArray();
    init_tasks();
    usleep(50000);
    stop = 1;
    deinit();

    // run_sched_fifo_test();

}
