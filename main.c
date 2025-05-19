//
// Created by sbn on 5/15/25.
//

#include "main.h"


int main(){

    printf("Starting the threads setup ...\n");

    fillPriorityArray();
    init_tasks();
    sleep(1);
    stop = 1;
    deinit();

}
