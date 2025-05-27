#include <stdio.h>
#include "../mibench.h"

// extern static const char* mibench_function_names[NUM_MIBENCH_FUNCTIONS];
// extern static void (*mibench_functions[NUM_MIBENCH_FUNCTIONS])();

int main() {

    for (int i = 0; i < NUM_MIBENCH_FUNCTIONS; i++) {
        printf("Testing function[%d] : %s\n", i, mibench_function_names[i]);
        mibench_functions[i]();
    }

    return 0;
}