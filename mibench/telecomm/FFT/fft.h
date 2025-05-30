//
// Created by sbn on 5/26/25.
//

#ifndef FFT_H
#define FFT_H

int __fft(int argc, char *argv[]);

static inline void _fft_large() {
    __fft(3, (char *[]){"fft", "8", "32768"});
    __fft(4, (char *[]){"fft", "8", "32768", "-i"});
}

static inline void _fft_small() {
    __fft(3, (char *[]){"fft", "4", "4096"});
    __fft(4, (char *[]){"fft", "4", "8192", "-i"});
}

#endif //FFT_H
