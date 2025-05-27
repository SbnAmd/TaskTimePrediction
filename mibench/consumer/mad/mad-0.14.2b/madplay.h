//
// Created by sbn on 5/25/25.
//

#ifndef MADPLAY_H
#define MADPLAY_H
#define PREFIX_PATH "/home/sbn/Work/Paper/perf_counter_exploit/mibench/consumer/mad/"
#define INPUT_FILE_LARGE PREFIX_PATH "large.mp3"
#define INPUT_FILE_SMALL PREFIX_PATH "small.mp3"
#define OUTPUT_FILE_LARGE "--output=wave:" PREFIX_PATH "output_large.wav"
#define OUTPUT_FILE_SMALL "--output=wave:" PREFIX_PATH "output_small.wav"

int _mad(int argc, char *argv[]);


void _mad_large() {
    _mad(5, (char *[]){"mad-0.14.2b/madplay", "--time=30", "--output=wave:output_large.wav", "-v", "large.mp3"});
}

void _mad_small() {
    _mad(5, (char *[]){"mad-0.14.2b/madplay", "--time=4", "--output=wave:output_small.wav", "-v", "small.mp3"});
}

#endif //MADPLAY_H
