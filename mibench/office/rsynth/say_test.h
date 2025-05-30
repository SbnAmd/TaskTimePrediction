//
// Created by sbn on 5/25/25.
//

#ifndef SAY_TEST_H
#define SAY_TEST_H
#include <stddef.h>

#define SAY_PREFIX_PATH         "/home/sbn/Work/Paper/perf_counter_exploit/mibench/office/rsynth/"
#define SAY_INPUT_LARGE        SAY_PREFIX_PATH "largeinput.txt"
#define SAY_INPUT_SMALL        SAY_PREFIX_PATH "smallinput.txt"
#define SAY_OUTPUT_LARGE       SAY_PREFIX_PATH "large_output.au"
#define SAY_OUTPUT_SMALL       SAY_PREFIX_PATH "small_output.au"

int __say(int argc, char* argv[], char* env[]);


static inline void _say_large() {
    __say(6, (char* []){"say", "-a", "-q", "-o", SAY_OUTPUT_LARGE, SAY_INPUT_LARGE}, NULL);
}

static inline void _say_small() {
    __say(6, (char* []){"say", "-a", "-q", "-o", SAY_OUTPUT_SMALL, SAY_INPUT_SMALL}, NULL);
}


#endif //SAY_TEST_H
