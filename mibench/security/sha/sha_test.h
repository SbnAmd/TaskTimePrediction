
#ifndef SHA_TEST_H
#define SHA_TEST_H

#define PREFIX_PATH "/home/sbn/Work/Paper/perf_counter_exploit/mibench/security/sha/"
#define INPUT_LARGE PREFIX_PATH "input_large.asc"
#define INPUT_SMALL PREFIX_PATH "input_small.asc"

int __sha(int argc, char **argv);

void _sha_large() {
    __sha(2, (char *[]){"sha", INPUT_LARGE});
}

void _sha_small() {
    __sha(2, (char *[]){"sha", INPUT_SMALL});
}


#endif //SHA_TEST_H
