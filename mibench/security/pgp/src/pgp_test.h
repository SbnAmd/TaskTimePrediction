//
// Created by sbn on 5/26/25.
//

#ifndef PGP_TEST_H
#define PGP_TEST_H
#include "mi_def.h"
#define PGP_PREFIX_PATH GLOB_PREFIX_PATH "security/pgp/tests/"
#define PGP_INPUT_FILE PGP_PREFIX_PATH "testin.txt"
#define PGP_OUTPUT_FILE PGP_PREFIX_PATH "testout.txt.asc"

int __pgp(int argc, char *argv[]);

void _pgp() {
    __pgp(8, (char *[]) {
        "pgp",
        "-sa",
        "-z",
        "this is a test",
        "-u",
        "taustin@eecs.umich.edu",
        PGP_INPUT_FILE,
        "austin@umich.edu"
    });

    __pgp(6, (char *[]) {
        "pgp",
        "-z",
        "this is a test",
        "-u",
        "taustin@eecs.umich.edu",
        PGP_OUTPUT_FILE});
}

#endif //PGP_TEST_H
