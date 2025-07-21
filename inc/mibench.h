//
// Created by sbn on 5/25/25.
//

#ifndef MIBENCH_H
#define MIBENCH_H
// #define PREFIX_PATH  "/home/sbn/Work/Paper/perf_counter_exploit/mibench/"


#define NUM_MIBENCH_FUNCTIONS 51
// #include "def.h"

/* Automotive */
void basicmath_large();
void basicmath_small();

void bitcount_large();
void bitcount_small();

void qsort_large();
void qsort_small();

void susan_large();
void susan_small();

/* Consumer */
void JPEG_large();
void JPEG_small();

void lame_large();
void lame_small();

void mad_large();
void mad_small();

void tiff2bw_large();
void tiff2bw_small();

void tiff2rgba_large();
void tiff2rgba_small();

void tiffdither_large();
void tiffdither_small();

void tiffmedian_large();
void tiffmedian_small();

void lout_large();
void lout_small();

/* Network */

void dijkstra_large();
void dijkstra_small();

void patricia_large();
void patricia_small();

/* Office */

void gs_large();
void gs_small();

void ispell_large();
void ispell_small();

void say_large();
void say_small();

void stringsearch_large();
void stringsearch_small();

/* Security */

void bf_large();
void bf_small();

void pgp();

void rijndael_large();
void rijndael_small();

void sha_large();
void sha_small();

/* Telecom */

void rawaudio_large();
void rawaudio_small();

void crc_large();
void crc_small();

void fft_large();
void fft_small();

void gsm_large();
void gsm_small();

// fixme: the tests below have issues
// jpeg
// tiff
// gs
// ispell
// bf
// pgp
// rawaudio
static const char* mibench_function_names[32] = {
    /* Automotive */
    "basicmath_large",
    "basicmath_small",
    "bitcount_large",
    "bitcount_small",
    "QSort_large",
    "QSort_small",
    "susan_large",
    "susan_small",

    /* Consumer */
    // "JPEG_large",
    // "JPEG_small",
    // "lame_large",
    // "lame_small",
    // "mad_large",
    // "mad_small",
    // "tiff2bw_large",
    // "tiff2bw_small",
    // "tiff2rgba_large",
    // "tiff2rgba_small",
    // "tiffdither_large",
    // "tiffdither_small",
    // "tiffmedian_large",
    // "tiffmedian_small",
    // "lout_large",
    // "lout_small",

    /* Network */
    "dijkstra_large",
    "dijkstra_small",
    // "patricia_large",
    // "patricia_small",

    /* Office */
    // "gs_large",
    // "gs_small",
    // "ispell_large",
    // "ispell_small",
    // "say_large",
    // "say_small",
    "stringsearch_large",
    "stringsearch_small",

    /* Security */
    // "bf_large",
    // "bf_small",
    // "pgp",
    "rijndael_large",
    "rijndael_small",
    "sha_large",
    "sha_small",

    /* Telecom */
    // "rawaudio_large",
    // "rawaudio_small",
    "crc_large",
    "crc_small",
    "fft_large",
    "fft_small",
    "gsm_large",
    "gsm_small"
};

// Array of function pointers (type void (*)())
static void (*mibench_functions[32])() = {
    /* Automotive */
    basicmath_large,
    basicmath_small,
    bitcount_large,
    bitcount_small,
    qsort_large,
    qsort_small,
    susan_large,
    susan_small,

    /* Consumer */
    // JPEG_large,
    // JPEG_small,
    // lame_large,
    // lame_small,
    // mad_large,
    // mad_small,
    // tiff2bw_large,
    // tiff2bw_small,
    // tiff2rgba_large,
    // tiff2rgba_small,
    // tiffdither_large,
    // tiffdither_small,
    // tiffmedian_large,
    // tiffmedian_small,
    // lout_large,
    // lout_small,

    /* Network */
    dijkstra_large,
    dijkstra_small,
    // patricia_large,
    // patricia_small,

    /* Office */
    // gs_large,
    // gs_small,
    // ispell_large,
    // ispell_small,
    // say_large,
    // say_small,
    stringsearch_large,
    stringsearch_small,

    /* Security */
    // bf_large,
    // bf_small,
    // pgp,
    rijndael_large,
    rijndael_small,
    sha_large,
    sha_small,

    /* Telecom */
    // rawaudio_large,
    // rawaudio_small,
    crc_large,
    crc_small,
    fft_large,
    fft_small,
    gsm_large,
    gsm_small
};

#endif //MIBENCH_H
