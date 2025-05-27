//
// Created by sbn on 5/26/25.
//

#ifndef PGP_TEST_H
#define PGP_TEST_H
#define PREFIX_PATH "/home/sbn/Work/Paper/perf_counter_exploit/mibench/security/pgp/tests/"
#define INPUT_FILE PREFIX_PATH "testin.txt"
#define OUTPUT_FILE PREFIX_PATH "testout.txt.asc"

int __pgp(int argc, char *argv[]);

void _pgp() {
    __pgp(8, (char *[]) {
        "pgp",
        "-sa",
        "-z",
        "this is a test",
        "-u",
        "taustin@eecs.umich.edu",
        "testin.txt",
        "austin@umich.edu"
    });

    __pgp(6, (char *[]) {
        "pgp",
        "-z",
        "this is a test",
        "-u",
        "taustin@eecs.umich.edu",
        "testout.txt.asc"});
}

#endif //PGP_TEST_H
