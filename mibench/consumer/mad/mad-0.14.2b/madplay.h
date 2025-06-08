//
// Created by sbn on 5/25/25.
//

#ifndef MADPLAY_H
#define MADPLAY_H

#include "mi_def.h"

#define MAD_PREFIX_PATH GLOB_PREFIX_PATH "consumer/mad/"
#define MAD_INPUT_FILE_LARGE MAD_PREFIX_PATH "large.mp3"
#define MAD_INPUT_FILE_SMALL MAD_PREFIX_PATH "small.mp3"
#define MAD_OUTPUT_FILE_LARGE "--output=wave:" MAD_PREFIX_PATH "output_large.wav"
#define MAD_OUTPUT_FILE_SMALL "--output=wave:" MAD_PREFIX_PATH "output_small.wav"

void _mad(int argc, char *argv[]);


static inline void _mad_large() {
    _mad(5, (char *[]){"mad-0.14.2b/madplay", "--time=30", MAD_OUTPUT_FILE_LARGE, "-v", MAD_INPUT_FILE_LARGE});
}

static inline void _mad_small() {
    _mad(5, (char *[]){"mad-0.14.2b/madplay", "--time=4", MAD_OUTPUT_FILE_SMALL, "-v", MAD_INPUT_FILE_SMALL});
}

#endif //MADPLAY_H
