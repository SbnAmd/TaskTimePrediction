//
// Created by sbn on 5/26/25.
//

#ifndef RIJNDAEL_H
#define RIJNDAEL_H
#define PREFIX_PATH "/home/sbn/Work/Paper/perf_counter_exploit/mibench/security/rijndael/"
#define INPUT_LARGE_ASC PREFIX_PATH "input_large.asc"
#define OUTPUT_LARGE_ENC PREFIX_PATH "output_large.enc"
#define OUTPUT_LARGE_DEC PREFIX_PATH "output_large.dec"

#define INPUT_SMALL_ASC PREFIX_PATH "input_small.asc"
#define OUTPUT_SMALL_ENC PREFIX_PATH "output_small.enc"
#define OUTPUT_SMALL_DEC PREFIX_PATH "output_small.dec"

int __rijndael(int argc, char *argv[]);

void _rijndael_large() {

    __rijndael(5, (char *[]) {
        "rijndael",
        INPUT_LARGE_ASC,
        OUTPUT_LARGE_ENC,
        "e",
        "1234567890abcdeffedcba09876543211234567890abcdeffedcba0987654321"
    });
    __rijndael(5, (char *[]) {
        "rijndael",
        OUTPUT_LARGE_ENC,
        OUTPUT_LARGE_DEC,
        "d",
        "1234567890abcdeffedcba09876543211234567890abcdeffedcba0987654321"
    });
}

void _rijndael_small() {

    __rijndael(5, (char *[]) {
        "rijndael",
        INPUT_SMALL_ASC,
        OUTPUT_SMALL_ENC,
        "e",
        "1234567890abcdeffedcba09876543211234567890abcdeffedcba0987654321"
    });
    __rijndael(5, (char *[]) {
        "rijndael",
        OUTPUT_SMALL_ENC,
        OUTPUT_SMALL_DEC,
        "d",
        "1234567890abcdeffedcba09876543211234567890abcdeffedcba0987654321"
    });
}


#endif //RIJNDAEL_H
