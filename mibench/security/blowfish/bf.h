//
// Created by sbn on 5/26/25.
//

#ifndef BF_H
#define BF_H

#define PREFIX_PATH "/home/sbn/Work/Paper/perf_counter_exploit/mibench/security/blowfish/"
#define INPUT_LARGE_ASC  PREFIX_PATH "input_large.asc"
#define OUTPUT_LARGE_ENC  PREFIX_PATH "output_large.enc"
#define OUTPUT_LARGE_ASC  PREFIX_PATH "output_large.asc"

#define INPUT_SMALL_ASC  PREFIX_PATH "input_small.asc"
#define OUTPUT_SMALL_ENC  PREFIX_PATH "output_small.enc"
#define OUTPUT_SMALL_ASC  PREFIX_PATH "output_small.asc"

int __bf(int argc, char *argv[]);


void _bf_large() {
    __bf(5, (char *[]){"bf", "e", INPUT_LARGE_ASC, OUTPUT_LARGE_ENC, "1234567890abcdeffedcba0987654321"});
    __bf(5, (char *[]){"bf", "d", OUTPUT_LARGE_ENC, OUTPUT_LARGE_ASC, "1234567890abcdeffedcba0987654321"});
}

void _bf_small() {
    __bf(5, (char *[]){"bf", "e", INPUT_SMALL_ASC, OUTPUT_SMALL_ENC, "1234567890abcdeffedcba0987654321"});
    __bf(5, (char *[]){"bf", "d", OUTPUT_SMALL_ENC, OUTPUT_SMALL_ASC, "1234567890abcdeffedcba0987654321"});
}

#endif //BF_H
