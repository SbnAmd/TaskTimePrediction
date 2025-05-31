//
// Created by sbn on 5/25/25.
//

#ifndef QSORT_H
#define QSORT_H

#define QSORT_PREFIX_PATH "/home/sbn/Work/Paper/perf_counter_exploit/mibench/automotive/qsort/"
#define QSORT_INPUT_FILE_LARGE QSORT_PREFIX_PATH "input_large.dat"
#define QSORT_INPUT_FILE_SMALL QSORT_PREFIX_PATH "input_small.dat"

int __qsort_large(int argc, char *argv[]);
int __qsort_small(int argc, char *argv[]);

static inline void _qsort_large() {
    __qsort_large(2, (char *[]){"qsort_large", QSORT_INPUT_FILE_LARGE});
}

static inline void _qsort_small() {
    __qsort_small(2, (char *[]){"qsort_small", QSORT_INPUT_FILE_SMALL});
}


#endif //QSORT_H
