//
// Created by sbn on 5/26/25.
//

#ifndef RIJNDAEL_H
#define RIJNDAEL_H
#define RIJNDAEL_PREFIX_PATH "/home/sbn/Work/Paper/perf_counter_exploit/mibench/security/rijndael/"
#define RIJNDAEL_INPUT_LARGE_ASC RIJNDAEL_PREFIX_PATH "input_large.asc"
#define RIJNDAEL_OUTPUT_LARGE_ENC RIJNDAEL_PREFIX_PATH "output_large.enc"
#define RIJNDAEL_OUTPUT_LARGE_DEC RIJNDAEL_PREFIX_PATH "output_large.dec"

#define RIJNDAEL_INPUT_SMALL_ASC RIJNDAEL_PREFIX_PATH "input_small.asc"
#define RIJNDAEL_OUTPUT_SMALL_ENC RIJNDAEL_PREFIX_PATH "output_small.enc"
#define RIJNDAEL_OUTPUT_SMALL_DEC RIJNDAEL_PREFIX_PATH "output_small.dec"

int __rijndael(int argc, char *argv[]);

static inline void _rijndael_large() {

    __rijndael(5, (char *[]) {
        "rijndael",
        RIJNDAEL_INPUT_LARGE_ASC,
        RIJNDAEL_OUTPUT_LARGE_ENC,
        "e",
        "1234567890abcdeffedcba09876543211234567890abcdeffedcba0987654321"
    });
    __rijndael(5, (char *[]) {
        "rijndael",
        RIJNDAEL_OUTPUT_LARGE_ENC,
        RIJNDAEL_OUTPUT_LARGE_DEC,
        "d",
        "1234567890abcdeffedcba09876543211234567890abcdeffedcba0987654321"
    });
}

static inline void _rijndael_small() {

    __rijndael(5, (char *[]) {
        "rijndael",
        RIJNDAEL_INPUT_SMALL_ASC,
        RIJNDAEL_OUTPUT_SMALL_ENC,
        "e",
        "1234567890abcdeffedcba09876543211234567890abcdeffedcba0987654321"
    });
    __rijndael(5, (char *[]) {
        "rijndael",
        RIJNDAEL_OUTPUT_SMALL_ENC,
        RIJNDAEL_OUTPUT_SMALL_DEC,
        "d",
        "1234567890abcdeffedcba09876543211234567890abcdeffedcba0987654321"
    });
}


#endif //RIJNDAEL_H
