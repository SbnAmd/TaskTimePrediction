//
// Created by sbn on 5/26/25.
//

#ifndef RAWAUDIO_H
#define RAWAUDIO_H

#define RAWAUDIO_PREFIX_PATH  "/home/sbn/Work/Paper/perf_counter_exploit/mibench/telecomm/adpcm/data/"

#define RAWAUDIO_INPUT_LARGE_PCM RAWAUDIO_PREFIX_PATH "large.pcm"
#define RAWAUDIO_INPUT_LARGE_ADPCM RAWAUDIO_PREFIX_PATH "large.adpcm"

#define RAWAUDIO_SMALL_LARGE_PCM RAWAUDIO_PREFIX_PATH "small.pcm"
#define RAWAUDIO_SMALL_LARGE_ADPCM RAWAUDIO_PREFIX_PATH "small.adpcm"


void _rawdaudio();
void _rawcaudio();

static inline void _rawaudio_large() {
    _rawcaudio();
    _rawdaudio();
}

static inline void _rawaudio_small() {
    _rawcaudio();
    _rawdaudio();
}

#endif //RAWAUDIO_H
