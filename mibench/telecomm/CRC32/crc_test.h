//
// Created by sbn on 5/26/25.
//

#ifndef CRC_TEST_H
#define CRC_TEST_H
#define PREFIX_PATH  "/home/sbn/Work/Paper/perf_counter_exploit/mibench/telecomm/adpcm/data/"
#define INPUT_LARGE PREFIX_PATH "large.pcm"
#define INPUT_SMALL PREFIX_PATH "small.pcm"

int __crc(int argc, char *argv[]);

void _crc_large() {
    __crc(2, (char *[]){"crc", INPUT_LARGE});
}

void _crc_small() {
    __crc(2, (char *[]){"crc", INPUT_SMALL});
}


#endif //CRC_TEST_H
