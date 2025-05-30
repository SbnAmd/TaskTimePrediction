//
// Created by sbn on 5/26/25.
//

#ifndef BF_H
#define BF_H

#define BF_PREFIX_PATH "/home/sbn/Work/Paper/perf_counter_exploit/mibench/security/blowfish/"
#define BF_INPUT_LARGE_ASC  BF_PREFIX_PATH "input_large.asc"
#define BF_OUTPUT_LARGE_ENC  BF_PREFIX_PATH "output_large.enc"
#define BF_OUTPUT_LARGE_ASC  BF_PREFIX_PATH "output_large.asc"

#define BF_INPUT_SMALL_ASC  BF_PREFIX_PATH "input_small.asc"
#define BF_OUTPUT_SMALL_ENC  BF_PREFIX_PATH "output_small.enc"
#define BF_OUTPUT_SMALL_ASC  BF_PREFIX_PATH "output_small.asc"

int __bf(int argc, char *argv[]);


static inline void _bf_large() {
    __bf(5, (char *[]){"bf", "e", BF_INPUT_LARGE_ASC, BF_OUTPUT_LARGE_ENC, "1234567890abcdeffedcba0987654321"});
    __bf(5, (char *[]){"bf", "d", BF_OUTPUT_LARGE_ENC, BF_OUTPUT_LARGE_ASC, "1234567890abcdeffedcba0987654321"});
}

static inline void _bf_small() {
    __bf(5, (char *[]){"bf", "e", BF_INPUT_SMALL_ASC, BF_OUTPUT_SMALL_ENC, "1234567890abcdeffedcba0987654321"});
    __bf(5, (char *[]){"bf", "d", BF_OUTPUT_SMALL_ENC, BF_OUTPUT_SMALL_ASC, "1234567890abcdeffedcba0987654321"});
}

#endif //BF_H
