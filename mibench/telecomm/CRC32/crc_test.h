//
// Created by sbn on 5/26/25.
//

#ifndef CRC_TEST_H
#define CRC_TEST_H
#include "mi_def.h"
#define CRC_PREFIX_PATH  GLOB_PREFIX_PATH "telecomm/adpcm/data/"
#define CRC_INPUT_LARGE CRC_PREFIX_PATH "large.pcm"
#define CRC_INPUT_SMALL CRC_PREFIX_PATH "small.pcm"

int __crc(int argc, char *argv[]);

static inline void _crc_large() {
    __crc(2, (char *[]){"crc", CRC_INPUT_LARGE});
}

static inline void _crc_small() {
    __crc(2, (char *[]){"crc", CRC_INPUT_SMALL});
}


#endif //CRC_TEST_H
