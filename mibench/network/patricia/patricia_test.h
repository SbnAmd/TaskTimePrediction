//
// Created by sbn on 5/25/25.
//

#ifndef PATRICIA_TEST_H
#define PATRICIA_TEST_H

#define PREFIX_PATH "/home/sbn/Work/Paper/perf_counter_exploit/mibench/network/patricia/"
#define INPUT_LARGE "large.udp"
#define INPUT_SMALL "small.udp"

int __patricia(int argc, char **argv);


void _patricia_large() {
    __patricia(2, (char*[]){"patricia", INPUT_LARGE});
}

void _patricia_small() {
    __patricia(2, (char*[]){"patricia", INPUT_SMALL});
}

#endif //PATRICIA_TEST_H
