#include "mibench.h"
#include "mi_def.h"
#ifdef PC
#include "/home/sbn/Work/Development/C/TaskExecution/mibench/automotive/basicmath/basicmath.h"
#include "/home/sbn/Work/Development/C/TaskExecution/mibench/automotive/bitcount/bitcnts.h"
#include "/home/sbn/Work/Development/C/TaskExecution/mibench/automotive/qsort/qsort.h"
#include "/home/sbn/Work/Development/C/TaskExecution/mibench/automotive/susan/susan.h"
#include "/home/sbn/Work/Development/C/TaskExecution/mibench/consumer/jpeg/jpeg-6a/jpeg.h"
#include "/home/sbn/Work/Development/C/TaskExecution/mibench/consumer/lame/lame3.70/main.h"
#include "/home/sbn/Work/Development/C/TaskExecution/mibench/consumer/mad/mad-0.14.2b/madplay.h"
#include "/home/sbn/Work/Development/C/TaskExecution/mibench/consumer/tiff-v3.5.4/tools/tiff.h"
#include "/home/sbn/Work/Development/C/TaskExecution/mibench/consumer/typeset/lout-3.24/lout.h"
#include "/home/sbn/Work/Development/C/TaskExecution/mibench/network/dijkstra/dijkstra.h"
#include "/home/sbn/Work/Development/C/TaskExecution/mibench/network/patricia/patricia_test.h"
// #include "/home/sbn/Work/Development/C/TaskExecution/mibench/office/ghostscript/src/gs.h"
#include "/home/sbn/Work/Development/C/TaskExecution/mibench/office/ispell/ispell_test.h"
#include "/home/sbn/Work/Development/C/TaskExecution/mibench/office/rsynth/say_test.h"
#include "/home/sbn/Work/Development/C/TaskExecution/mibench/office/stringsearch/stringsearch.h"
#include "/home/sbn/Work/Development/C/TaskExecution/mibench/security/blowfish/bf.h"
#include "/home/sbn/Work/Development/C/TaskExecution/mibench/security/pgp/src/pgp_test.h"
#include "/home/sbn/Work/Development/C/TaskExecution/mibench/security/rijndael/rijndael.h"
#include "/home/sbn/Work/Development/C/TaskExecution/mibench/security/sha/sha_test.h"
#include "/home/sbn/Work/Development/C/TaskExecution/mibench/telecomm/adpcm/src/rawaudio.h"
#include "/home/sbn/Work/Development/C/TaskExecution/mibench/telecomm/CRC32/crc_test.h"
#include "/home/sbn/Work/Development/C/TaskExecution/mibench/telecomm/FFT/fft.h"
#include "/home/sbn/Work/Development/C/TaskExecution/mibench/telecomm/gsm/src/gsm_test.h"
#else
#include "/home/sbn/Work/Paper/mibench/automotive/basicmath/basicmath.h"
#include "/home/sbn/Work/Paper/mibench/automotive/bitcount/bitcnts.h"
#include "/home/sbn/Work/Paper/mibench/automotive/qsort/qsort.h"
#include "/home/sbn/Work/Paper/mibench/automotive/susan/susan.h"
#include "/home/sbn/Work/Paper/mibench/consumer/jpeg/jpeg-6a/jpeg.h"
#include "/home/sbn/Work/Paper/mibench/consumer/lame/lame3.70/main.h"
#include "/home/sbn/Work/Paper/mibench/consumer/mad/mad-0.14.2b/madplay.h"
#include "/home/sbn/Work/Paper/mibench/consumer/tiff-v3.5.4/tools/tiff.h"
#include "/home/sbn/Work/Paper/mibench/consumer/typeset/lout-3.24/lout.h"
#include "/home/sbn/Work/Paper/mibench/network/dijkstra/dijkstra.h"
#include "/home/sbn/Work/Paper/mibench/network/patricia/patricia_test.h"
// #include "/home/sbn/Work/Paper/mibench/office/ghostscript/src/gs.h"
#include "/home/sbn/Work/Paper/mibench/office/ispell/ispell_test.h"
#include "/home/sbn/Work/Paper/mibench/office/rsynth/say_test.h"
#include "/home/sbn/Work/Paper/mibench/office/stringsearch/stringsearch.h"
#include "/home/sbn/Work/Paper/mibench/security/blowfish/bf.h"
#include "/home/sbn/Work/Paper/mibench/security/pgp/src/pgp_test.h"
#include "/home/sbn/Work/Paper/mibench/security/rijndael/rijndael.h"
#include "/home/sbn/Work/Paper/mibench/security/sha/sha_test.h"
#include "/home/sbn/Work/Paper/mibench/telecomm/adpcm/src/rawaudio.h"
#include "/home/sbn/Work/Paper/mibench/telecomm/CRC32/crc_test.h"
#include "/home/sbn/Work/Paper/mibench/telecomm/FFT/fft.h"
#include "/home/sbn/Work/Paper/mibench/telecomm/gsm/src/gsm_test.h"
#endif

void basicmath_large() {
    // Implementation of the large basic math benchmark
    _basicmath_large();
    // Add your code here
}

void basicmath_small() {
    // Implementation of the small basic math benchmark
    _basicmath_small();
    // Add your code here
}

void qsort_large() {
    // Implementation of the large qsort benchmark
    _qsort_large();
}

void qsort_small() {
    // Implementation of the small qsort benchmark
    _qsort_small();
}

void susan_large() {
    // Implementation of the large susan benchmark
    _susan_large();
}

void susan_small() {
    // Implementation of the small susan benchmark
    _susan_small();
}

void bitcount_large() {
    // Implementation of the large bitcount benchmark
    _bitcnts_large_();
}

void bitcount_small() {
    // Implementation of the small bitcount benchmark
    _bitcnts_small_();
}

void JPEG_large() {
    _jpeg_large();
}

void JPEG_small() {
    _jpeg_small();
}

void mad_large() {
    _mad_large();
}

void mad_small() {
    _mad_small();
}

void lame_large() {
    _lame_large();
}

void lame_small() {
    _lame_small();
}

void tiff2bw_large() {
    _tiff2bw_large();
}

void tiff2bw_small() {
    _tiff2bw_small();
}

void tiff2rgba_large() {
    _tiff2rgba_large();
}

void tiff2rgba_small() {
    _tiff2rgba_small();
}

void tiffdither_large() {
    _tiffdither_large();
}

void tiffdither_small() {
    _tiffdither_small();
}

void tiffmedian_large() {
    _tiffmedian_large();
}

void tiffmedian_small() {
    _tiffmedian_small();
}

void lout_large() {
    _lout_large();
}

void lout_small() {
    _lout_small();
}

void dijkstra_large() {
    _dijkstra_large();
}

void dijkstra_small() {
    _dijkstra_small();
}

void patricia_large() {
    _patricia_large();
}

void patricia_small() {
    _patricia_small();
}

// void gs_large() {
//     _gs_large();
// }
//
// void gs_small() {
//     _gs_small();
// }

void ispell_large() {
    _ispell_large();
}

void ispell_small() {
    _ispell_small();
}

void say_large() {
    _say_large();
}

void say_small() {
    _say_small();
}

void stringsearch_large() {
    _stringsearch_large();
}

void stringsearch_small() {
    _stringsearch_small();
}

void bf_large() {
    _bf_large();
}

void bf_small() {
    _bf_small();
}

void sha_large() {
    _sha_large();
}

void sha_small() {
    _sha_small();
}

void pgp() {
    _pgp();
}

void rijndael_large() {
    _rijndael_large();
}

void rijndael_small() {
    _rijndael_small();
}

void rawaudio_large() {
    _rawaudio_large();
}

void rawaudio_small() {
    _rawaudio_small();
}

void crc_large() {
    _crc_large();
}

void crc_small() {
    _crc_small();
}

void fft_large() {
    _fft_large();
}

void fft_small() {
    _fft_small();
}

void gsm_large() {
    _toast_large();
}

void gsm_small() {
    _toast_small();
}

