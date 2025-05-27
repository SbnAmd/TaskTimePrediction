//
// Created by sbn on 5/25/25.
//

#ifndef GS_H
#define GS_H
#define PREFIX_PATH          "/home/sbn/Work/Paper/perf_counter_exploit/mibench/office/ghostscript/data/"
#define INPUT_LARGE          PREFIX_PATH "large.ps"
#define OUTPUT_LARGE         "-sOutputFile=" PREFIX_PATH "output_large.ppm"

#define INPUT_SMALL          PREFIX_PATH "small.ps"
#define OUTPUT_SMALL         "-sOutputFile=" PREFIX_PATH "output_small.ppm"

int __gs(int argc, char *argv[]);


int _gs_large() {
    __gs(6, (char*[]) {
        "rc/gs",
        "-sDEVICE=ppm",
        "-dNOPAUSE",
        "-q",
        OUTPUT_LARGE,
        "--",
        INPUT_LARGE
    });
}

int _gs_small() {
    __gs(6, (char*[]) {
        "rc/gs",
        "-sDEVICE=ppm",
        "-dNOPAUSE",
        "-q",
        OUTPUT_SMALL,
        "--",
        INPUT_SMALL
    });
}

#endif //GS_H
