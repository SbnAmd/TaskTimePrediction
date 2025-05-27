//
// Created by sbn on 5/25/25.
//

#ifndef SAY_TEST_H
#define SAY_TEST_H
#include <stddef.h>

#define PREFIX_PATH         "/home/sbn/Work/Paper/perf_counter_exploit/mibench/office/rsynth/"
#define INPUT_LARGE        PREFIX_PATH "largeinput.txt"
#define INPUT_SMALL        PREFIX_PATH "smallinput.txt"
#define OUTPUT_LARGE       PREFIX_PATH "large_output.au"
#define OUTPUT_SMALL       PREFIX_PATH "small_output.au"

int __say(int argc, char* argv[], char* env[]);


void _say_large() {
    __say(6, (char* []){"say", "-a", "-q", "-o", OUTPUT_LARGE, INPUT_LARGE}, NULL);
}

void _say_small() {
    __say(6, (char* []){"say", "-a", "-q", "-o", OUTPUT_SMALL, INPUT_SMALL}, NULL);
}


#endif //SAY_TEST_H
