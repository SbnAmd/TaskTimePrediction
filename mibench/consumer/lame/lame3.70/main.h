//
// Created by sbn on 5/25/25.
//

#ifndef MAIN_H
#define MAIN_H


#define INPUT_FILE_LARGE "large.wav"
#define INPUT_FILE_SMALL "small.wav"
#define OUTPUT_FILE_LARGE "output_large.mp3"
#define OUTPUT_FILE_SMALL "output_small.mp3"

int _lame(int argc, char **argv);

void _lame_large() {
    _lame(3, (char *[]){"lame3.70/lame", INPUT_FILE_LARGE, OUTPUT_FILE_LARGE});
}

void _lame_small() {
    _lame(3, (char *[]){"lame3.70/lame", INPUT_FILE_LARGE, OUTPUT_FILE_SMALL});
}


#endif //MAIN_H
