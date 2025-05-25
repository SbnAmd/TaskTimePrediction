//
// Created by sbn on 5/15/25.
//

#include "main.h"


int main(){

    set_current_thread_sched_fifo(99);

    printf("Starting the threads setup ...\n");

    fillPriorityArray();
    init_tasks();
    sleep(2);
    stop = 1;
    deinit();

    // run_sched_fifo_test();
    print_perf_events();

}
