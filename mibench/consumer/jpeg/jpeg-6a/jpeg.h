//
// Created by sbn on 5/25/25.
//

#ifndef JPEG_H
#define JPEG_H

#define PREFIX_PATH "mibench/consumer/jpeg/"
#define INPUT_FILE_LARGE PREFIX_PATH "input_large.ppm"
#define INPUT_FILE_SMALL PREFIX_PATH "input_small.ppm"
#define OUTPUT_FILE_LARGE_ENCODE PREFIX_PATH "output_large_encode.jpeg"
#define OUTPUT_FILE_LARGE_DECODE PREFIX_PATH "output_large_decode.ppm"
#define OUTPUT_FILE_SMALL_ENCODE PREFIX_PATH "output_small_encode.jpeg"
#define OUTPUT_FILE_SMALL_DECODE PREFIX_PATH "output_small_decode.ppm"

int _cjpeg (int argc, char **argv);
int _djpeg(int argc, char **argv);


void _jpeg_large() {
    _cjpeg(8, (char *[]){"jpeg-6a/cjpeg", "-dct", "int", "-progressive", "-opt", "-outfile", OUTPUT_FILE_LARGE_ENCODE, INPUT_FILE_LARGE});
    _djpeg(7, (char *[]){"jpeg-6a/djpeg", "-dct", "int", "-ppm", "-outfile", OUTPUT_FILE_LARGE_DECODE, INPUT_FILE_LARGE});
}

void _jpeg_small() {
    _cjpeg(8, (char *[]){"jpeg-6a/cjpeg", "-dct", "int", "-progressive", "-opt", "-outfile", OUTPUT_FILE_SMALL_ENCODE, INPUT_FILE_SMALL});
    _djpeg(7, (char *[]){"jpeg-6a/djpeg", "-dct", "int", "-ppm", "-outfile", OUTPUT_FILE_SMALL_DECODE, INPUT_FILE_SMALL});
}

#endif //JPEG_H
