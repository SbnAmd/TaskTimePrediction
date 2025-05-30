
#ifndef SHA_TEST_H
#define SHA_TEST_H

#define SHA_PREFIX_PATH "/home/sbn/Work/Paper/perf_counter_exploit/mibench/security/sha/"
#define SHA_INPUT_LARGE SHA_PREFIX_PATH "input_large.asc"
#define SHA_INPUT_SMALL SHA_PREFIX_PATH "input_small.asc"

int __sha(int argc, char **argv);

static inline void _sha_large() {
    __sha(2, (char *[]){"sha", SHA_INPUT_LARGE});
}

static inline void _sha_small() {
    __sha(2, (char *[]){"sha", SHA_INPUT_SMALL});
}


#endif //SHA_TEST_H
