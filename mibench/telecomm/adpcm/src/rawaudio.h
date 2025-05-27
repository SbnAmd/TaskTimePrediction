//
// Created by sbn on 5/26/25.
//

#ifndef RAWAUDIO_H
#define RAWAUDIO_H

#define PREFIX_PATH  "/home/sbn/Work/Paper/perf_counter_exploit/mibench/telecomm/adpcm/data/"

#define INPUT_LARGE_PCM PREFIX_PATH "large.pcm"
#define INPUT_LARGE_ADPCM PREFIX_PATH "large.adpcm"

#define SMALL_LARGE_PCM PREFIX_PATH "small.pcm"
#define SMALL_LARGE_ADPCM PREFIX_PATH "small.adpcm"


void _rawdaudio();
void _rawcaudio();

void _rawaudio_large() {
    _rawcaudio();
    _rawdaudio();
}

void _rawaudio_small() {
    _rawcaudio();
    _rawdaudio();
}

#endif //RAWAUDIO_H
