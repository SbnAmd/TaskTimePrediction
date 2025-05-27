//
// Created by sbn on 5/25/25.
//

#ifndef QSORT_H
#define QSORT_H

#define PREFIX_PATH "/home/sbn/mibench/automotive/qsort/"
#define INPUT_FILE_LARGE PREFIX_PATH "input_large.dat"
#define INPUT_FILE_SMALL PREFIX_PATH "input_small.dat"

int __qsort_large(int argc, char *argv[]);
int __qsort_small(int argc, char *argv[]);

void _qsort_large() {
    __qsort_large(2, (char *[]){"qsort_large", INPUT_FILE_LARGE});
}

void _qsort_small() {
    __qsort_small(2, (char *[]){"qsort_small", INPUT_FILE_SMALL});
}


#endif //QSORT_H
