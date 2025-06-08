//
// Created by sbn on 5/25/25.
//

#ifndef SUSAN_H
#define SUSAN_H
#include "mi_def.h"


#define SUSAN_PREFIX_PATH GLOB_PREFIX_PATH "automotive/susan/"
#define SUSAN_INPUT_FILE_LARGE SUSAN_PREFIX_PATH "input_large.pgm"
#define SUSAN_OUTPUT_FILE_LARGE_SMOOTHING SUSAN_PREFIX_PATH "output_large.smoothing.pgm"
#define SUSAN_OUTPUT_FILE_LARGE_EDGES SUSAN_PREFIX_PATH "output_large.edges.pgm"
#define SUSAN_OUTPUT_FILE_LARGE_CORNERS SUSAN_PREFIX_PATH "output_large.corners.pgm"

#define SUSAN_INPUT_FILE_SMALL SUSAN_PREFIX_PATH "input_small.pgm"
#define SUSAN_OUTPUT_FILE_SMALL_SMOOTHING SUSAN_PREFIX_PATH "output_small.smoothing.pgm"
#define SUSAN_OUTPUT_FILE_SMALL_EDGES SUSAN_PREFIX_PATH "output_small.edges.pgm"
#define SUSAN_OUTPUT_FILE_SMALL_CORNERS SUSAN_PREFIX_PATH "output_small.corners.pgm"


_susan(int argc,char* argv[]);


static inline void _susan_large() {
    _susan(4, (char *[]){"susan", SUSAN_INPUT_FILE_LARGE, SUSAN_OUTPUT_FILE_LARGE_SMOOTHING, "-s"});
    _susan(4, (char *[]){"susan", SUSAN_INPUT_FILE_LARGE, SUSAN_OUTPUT_FILE_LARGE_EDGES, "-e"});
    _susan(4, (char *[]){"susan", SUSAN_INPUT_FILE_LARGE, SUSAN_OUTPUT_FILE_LARGE_CORNERS, "-c"});
}

static inline  void _susan_small() {
    _susan(4, (char *[]){"susan", SUSAN_INPUT_FILE_SMALL, SUSAN_OUTPUT_FILE_SMALL_SMOOTHING, "-s"});
    _susan(4, (char *[]){"susan", SUSAN_INPUT_FILE_SMALL, SUSAN_OUTPUT_FILE_SMALL_EDGES, "-e"});
    _susan(4, (char *[]){"susan", SUSAN_INPUT_FILE_SMALL, SUSAN_OUTPUT_FILE_SMALL_CORNERS, "-c"});
}

#endif //SUSAN_H
