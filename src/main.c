//
// Created by sbn on 5/15/25.
//

#include "main.h"

int g_stop = 0;

int main(){
    //fixme : this must be commented
    // set_current_thread_sched_fifo(99);

    printf("Starting the threads setup ...\n");

    fillPriorityArray();
    init_tasks();
    // printf("gstop = %d\n", g_stop);
    sleep(5);
    g_stop = 1;
    deinit();

    // run_sched_fifo_test();
    // print_perf_events();

}
