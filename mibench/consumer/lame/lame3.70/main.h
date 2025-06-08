//
// Created by sbn on 5/25/25.
//

#ifndef MAIN_H
#define MAIN_H
#include "mi_def.h"

#define LAME_PREFIX_PATH GLOB_PREFIX_PATH "consumer/lame/"
#define LAME_INPUT_FILE_LARGE LAME_PREFIX_PATH "large.wav"
#define LAME_INPUT_FILE_SMALL LAME_PREFIX_PATH "small.wav"
#define LAME_OUTPUT_FILE_LARGE LAME_PREFIX_PATH "output_large.mp3"
#define LAME_OUTPUT_FILE_SMALL LAME_PREFIX_PATH "output_small.mp3"

int _lame(int argc, char **argv);

static inline void _lame_large() {
    _lame(3, (char *[]){"lame3.70/lame", LAME_INPUT_FILE_LARGE, LAME_OUTPUT_FILE_LARGE});
}

static inline void _lame_small() {
    _lame(3, (char *[]){"lame3.70/lame", LAME_INPUT_FILE_SMALL, LAME_OUTPUT_FILE_SMALL});
}


#endif //MAIN_H
