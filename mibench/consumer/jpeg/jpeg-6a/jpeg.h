//
// Created by sbn on 5/25/25.
//

#ifndef JPEG_H
#define JPEG_H

#define JPEG_PREFIX_PATH "mibench/consumer/jpeg/"
#define JPEG_INPUT_FILE_LARGE JPEG_PREFIX_PATH "input_large.ppm"
#define JPEG_INPUT_FILE_SMALL JPEG_PREFIX_PATH "input_small.ppm"
#define JPEG_OUTPUT_FILE_LARGE_ENCODE JPEG_PREFIX_PATH "output_large_encode.jpeg"
#define JPEG_OUTPUT_FILE_LARGE_DECODE JPEG_PREFIX_PATH "output_large_decode.ppm"
#define JPEG_OUTPUT_FILE_SMALL_ENCODE JPEG_PREFIX_PATH "output_small_encode.jpeg"
#define JPEG_OUTPUT_FILE_SMALL_DECODE JPEG_PREFIX_PATH "output_small_decode.ppm"

int _cjpeg (int argc, char **argv);
int _djpeg(int argc, char **argv);


static inline void _jpeg_large() {
    _cjpeg(8, (char *[]){"jpeg-6a/cjpeg", "-dct", "int", "-progressive", "-opt", "-outfile", JPEG_OUTPUT_FILE_LARGE_ENCODE, JPEG_INPUT_FILE_LARGE});
    _djpeg(7, (char *[]){"jpeg-6a/djpeg", "-dct", "int", "-ppm", "-outfile", JPEG_OUTPUT_FILE_LARGE_DECODE, JPEG_INPUT_FILE_LARGE});
}

static inline void _jpeg_small() {
    _cjpeg(8, (char *[]){"jpeg-6a/cjpeg", "-dct", "int", "-progressive", "-opt", "-outfile", JPEG_OUTPUT_FILE_SMALL_ENCODE, JPEG_INPUT_FILE_SMALL});
    _djpeg(7, (char *[]){"jpeg-6a/djpeg", "-dct", "int", "-ppm", "-outfile", JPEG_OUTPUT_FILE_SMALL_DECODE, JPEG_INPUT_FILE_SMALL});
}

#endif //JPEG_H
