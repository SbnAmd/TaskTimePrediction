#include <stdio.h>
#include "../../inc/mibench.h"

int main() {

    // for (int i = 0; i < NUM_MIBENCH_FUNCTIONS; i++) {
    for (int i = 0; i < 28; i++) {
        printf("Testing function[%d] : %s\n", i, mibench_function_names[i]);
        mibench_functions[i]();
    }

    return 0;
}