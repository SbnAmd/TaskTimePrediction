#include "snipmath.h"
#include <math.h>
#include <stdio.h>
/* The printf's may be removed to isolate just the math calculations */

// int main(void)               // Function name changed to _basicmath_small
int _basicmath_small(void)
{
  FILE *fp = fopen("basicmath_small_output.txt", "w");
  if (!fp) {
    perror("Failed to open output file");
    return -1;
  }

  double  a1 = 1.0, b1 = -10.5, c1 = 32.0, d1 = -30.0;
  double  a2 = 1.0, b2 = -4.5, c2 = 17.0, d2 = -30.0;
  double  a3 = 1.0, b3 = -3.5, c3 = 22.0, d3 = -31.0;
  double  a4 = 1.0, b4 = -13.7, c4 = 1.0, d4 = -35.0;
  double  x[3];
  double X;
  int     solutions;
  int i;
  unsigned long l = 0x3fed0169L;
  struct int_sqrt q;
  long n = 0;

  fprintf(fp, "********* CUBIC FUNCTIONS ***********\n");
  SolveCubic(a1, b1, c1, d1, &solutions, x);
  fprintf(fp, "Solutions:");
  for(i=0;i<solutions;i++)
    fprintf(fp, " %f",x[i]);
  fprintf(fp, "\n");

  SolveCubic(a2, b2, c2, d2, &solutions, x);
  fprintf(fp, "Solutions:");
  for(i=0;i<solutions;i++)
    fprintf(fp, " %f",x[i]);
  fprintf(fp, "\n");

  SolveCubic(a3, b3, c3, d3, &solutions, x);
  fprintf(fp, "Solutions:");
  for(i=0;i<solutions;i++)
    fprintf(fp, " %f",x[i]);
  fprintf(fp, "\n");

  SolveCubic(a4, b4, c4, d4, &solutions, x);
  fprintf(fp, "Solutions:");
  for(i=0;i<solutions;i++)
    fprintf(fp, " %f",x[i]);
  fprintf(fp, "\n");

  for(a1=1;a1<10;a1++) {
    for(b1=10;b1>0;b1--) {
      for(c1=5;c1<15;c1+=0.5) {
        for(d1=-1;d1>-11;d1--) {
          SolveCubic(a1, b1, c1, d1, &solutions, x);
          fprintf(fp, "Solutions:");
          for(i=0;i<solutions;i++)
            fprintf(fp, " %f",x[i]);
          fprintf(fp, "\n");
        }
      }
    }
  }

  fprintf(fp, "********* INTEGER SQR ROOTS ***********\n");
  for (i = 0; i < 1001; ++i)
  {
    usqrt(i, &q);
    fprintf(fp, "sqrt(%3d) = %2d\n", i, q.sqrt);
  }

  usqrt(l, &q);
  fprintf(fp, "\nsqrt(%lX) = %X\n", l, q.sqrt);

  fprintf(fp, "********* ANGLE CONVERSION ***********\n");
  for (X = 0.0; X <= 360.0; X += 1.0)
    fprintf(fp, "%3.0f degrees = %.12f radians\n", X, deg2rad(X));

  fprintf(fp, "\n");
  for (X = 0.0; X <= (2 * PI + 1e-6); X += (PI / 180))
    fprintf(fp, "%.12f radians = %3.0f degrees\n", X, rad2deg(X));

  fclose(fp);
  return 0;
}