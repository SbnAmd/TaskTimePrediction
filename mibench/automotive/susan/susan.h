//
// Created by sbn on 5/25/25.
//

#ifndef SUSAN_H
#define SUSAN_H

#define PREFIX_PATH "/home/sbn/mibench/automotive/susan/"
#define INPUT_FILE_LARGE PREFIX_PATH "input_large.pgm"
#define OUTPUT_FILE_LARGE_SMOOTHING PREFIX_PATH "output_large.smoothing.pgm"
#define OUTPUT_FILE_LARGE_EDGES PREFIX_PATH "output_large.edges.pgm"
#define OUTPUT_FILE_LARGE_CORNERS PREFIX_PATH "output_large.corners.pgm"

#define INPUT_FILE_SMALL PREFIX_PATH "input_small.pgm"
#define OUTPUT_FILE_SMALL_SMOOTHING PREFIX_PATH "output_small.smoothing.pgm"
#define OUTPUT_FILE_SMALL_EDGES PREFIX_PATH "output_small.edges.pgm"
#define OUTPUT_FILE_SMALL_CORNERS PREFIX_PATH "output_small.corners.pgm"


_susan(int argc,char* argv[]);


void _susan_large() {
    _susan(4, (char *[]){"susan", INPUT_FILE_LARGE, OUTPUT_FILE_LARGE_SMOOTHING, "-s"});
    _susan(4, (char *[]){"susan", INPUT_FILE_LARGE, OUTPUT_FILE_LARGE_EDGES, "-e"});
    _susan(4, (char *[]){"susan", INPUT_FILE_LARGE, OUTPUT_FILE_LARGE_CORNERS, "-c"});
}

void _susan_small() {
    _susan(4, (char *[]){"susan", INPUT_FILE_SMALL, OUTPUT_FILE_SMALL_SMOOTHING, "-s"});
    _susan(4, (char *[]){"susan", INPUT_FILE_SMALL, OUTPUT_FILE_SMALL_EDGES, "-e"});
    _susan(4, (char *[]){"susan", INPUT_FILE_SMALL, OUTPUT_FILE_SMALL_CORNERS, "-c"});
}

#endif //SUSAN_H
