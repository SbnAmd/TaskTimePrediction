//
// Created by sbn on 5/25/25.
//

#ifndef MIBENCH_H
#define MIBENCH_H

#include "automotive/basicmath/basicmath.h"
#include "automotive/bitcount/bitcnts.h"
#include "automotive/qsort/qsort.h"
#include "automotive/susan/susan.h"
#include "consumer/jpeg/jpeg-6a/jpeg.h"
#include "consumer/lame/lame3.70/main.h"
#include "consumer/mad/mad-0.14.2b/madplay.h"
#include "consumer/tiff-v3.5.4/tools/tiff.h"
#include "consumer/typeset/lout-3.24/lout.h"

/* Automotive */
void basicmath_large();
void basicmath_small();

void bitcount_large();
void bitcount_small();

void QSort_large();
void QSort_small();

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

#endif //MIBENCH_H
