/* +++Date last modified: 05-Jul-1997 */

/*
**  BITCNTS.C - Test program for bit counting functions
**
**  public domain by Bob Stout & Auke Reitsma
*/

#include "bitcnts.h"
#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include <limits.h>
#include <time.h>
#include <float.h>
#include "bitops.h"

#define FUNCS  7

static int CDECL bit_shifter(long int x);

// int main(int argc, char *argv[])             // Function name changed to _bitcnts to avoid conflict with main()
void _bitcnts(int argc, char *argv[])
{
  FILE *fp = fopen("bitcnts_output.txt", "w");
  if (!fp) {
    perror("Failed to open output file");
    exit(1);
  }

  clock_t start, stop;
  double ct, cmin = DBL_MAX, cmax = 0;
  int i, cminix = 0, cmaxix = 0;
  long j, n, seed;
  int iterations;

  static int (* CDECL pBitCntFunc[FUNCS])(long) = {
    bit_count,
    bitcount,
    ntbl_bitcnt,
    ntbl_bitcount,
    // btbl_bitcnt, // commented out
    BW_btbl_bitcount,
    AR_btbl_bitcount,
    bit_shifter
  };

  static char *text[FUNCS] = {
    "Optimized 1 bit/loop counter",
    "Ratko's mystery algorithm",
    "Recursive bit count by nybbles",
    "Non-recursive bit count by nybbles",
    // "Recursive bit count by bytes",
    "Non-recursive bit count by bytes (BW)",
    "Non-recursive bit count by bytes (AR)",
    "Shift and count bits"
  };

  if (argc < 2) {
    fprintf(fp, "Usage: bitcnts <iterations>\n");
    fclose(fp);
    exit(1);
  }

  iterations = atoi(argv[1]);

  fprintf(fp, "Bit counter algorithm benchmark\n\n");

  for (i = 0; i < FUNCS; i++) {
    start = clock();
    for (j = n = 0, seed = rand(); j < iterations; j++, seed += 13)
      n += pBitCntFunc[i](seed);
    stop = clock();

    ct = (stop - start) / (double)CLOCKS_PER_SEC;

    if (ct < cmin) {
      cmin = ct;
      cminix = i;
    }
    if (ct > cmax) {
      cmax = ct;
      cmaxix = i;
    }

    fprintf(fp, "%-38s> Time: %7.3f sec.; Bits: %ld\n", text[i], ct, n);
  }

  fprintf(fp, "\nBest  > %s\n", text[cminix]);
  fprintf(fp, "Worst > %s\n", text[cmaxix]);

  fclose(fp);
}

static int CDECL bit_shifter(long int x)
{
  int i, n;
  
  for (i = n = 0; x && (i < (sizeof(long) * CHAR_BIT)); ++i, x >>= 1)
    n += (int)(x & 1L);
  return n;
}
