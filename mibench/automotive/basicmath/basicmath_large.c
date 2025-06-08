#include "basicmath.h"
#include "snipmath.h"
#include <math.h>
#include <stdio.h>
/* The printf's may be removed to isolate just the math calculations */

// int main(void)             // Function name changed to _basicmath_large
int _basicmath_large(void)
{
  FILE *out = fopen("basicmath_large.txt", "w");
  if (!out) {
    perror("fopen failed");
    return -1;
  }

  double  a1 = 1.0, b1 = -10.5, c1 = 32.0, d1 = -30.0;
  double  x[3];
  double X;
  int     solutions;
  int i;
  unsigned long l = 0x3fed0169L;
  struct int_sqrt q;
  long n = 0;

  fprintf(out, "********* CUBIC FUNCTIONS ***********\n");

  SolveCubic(a1, b1, c1, d1, &solutions, x);
  fprintf(out, "Solutions:");
  for(i=0;i<solutions;i++)
    fprintf(out, " %f",x[i]);
  fprintf(out, "\n");

  a1 = 1.0; b1 = -4.5; c1 = 17.0; d1 = -30.0;
  SolveCubic(a1, b1, c1, d1, &solutions, x);
  fprintf(out, "Solutions:");
  for(i=0;i<solutions;i++)
    fprintf(out, " %f",x[i]);
  fprintf(out, "\n");

  a1 = 1.0; b1 = -3.5; c1 = 22.0; d1 = -31.0;
  SolveCubic(a1, b1, c1, d1, &solutions, x);
  fprintf(out, "Solutions:");
  for(i=0;i<solutions;i++)
    fprintf(out, " %f",x[i]);
  fprintf(out, "\n");

  a1 = 1.0; b1 = -13.7; c1 = 1.0; d1 = -35.0;
  SolveCubic(a1, b1, c1, d1, &solutions, x);
  fprintf(out, "Solutions:");
  for(i=0;i<solutions;i++)
    fprintf(out, " %f",x[i]);
  fprintf(out, "\n");

  a1 = 3.0; b1 = 12.34; c1 = 5.0; d1 = 12.0;
  SolveCubic(a1, b1, c1, d1, &solutions, x);
  fprintf(out, "Solutions:");
  for(i=0;i<solutions;i++)
    fprintf(out, " %f",x[i]);
  fprintf(out, "\n");

  a1 = -8.0; b1 = -67.89; c1 = 6.0; d1 = -23.6;
  SolveCubic(a1, b1, c1, d1, &solutions, x);
  fprintf(out, "Solutions:");
  for(i=0;i<solutions;i++)
    fprintf(out, " %f",x[i]);
  fprintf(out, "\n");

  a1 = 45.0; b1 = 8.67; c1 = 7.5; d1 = 34.0;
  SolveCubic(a1, b1, c1, d1, &solutions, x);
  fprintf(out, "Solutions:");
  for(i=0;i<solutions;i++)
    fprintf(out, " %f",x[i]);
  fprintf(out, "\n");

  a1 = -12.0; b1 = -1.7; c1 = 5.3; d1 = 16.0;
  SolveCubic(a1, b1, c1, d1, &solutions, x);
  fprintf(out, "Solutions:");
  for(i=0;i<solutions;i++)
    fprintf(out, " %f",x[i]);
  fprintf(out, "\n");

  for(a1=1;a1<10;a1+=1) {
    for(b1=10;b1>0;b1-=.25) {
      for(c1=5;c1<15;c1+=0.61) {
        for(d1=-1;d1>-5;d1-=.451) {
          SolveCubic(a1, b1, c1, d1, &solutions, x);
          fprintf(out, "Solutions:");
          for(i=0;i<solutions;i++)
            fprintf(out, " %f",x[i]);
          fprintf(out, "\n");
        }
      }
    }
  }

  fprintf(out, "********* INTEGER SQR ROOTS ***********\n");
  for (i = 0; i < 100000; i+=2)
  {
    usqrt(i, &q);
    fprintf(out, "sqrt(%3d) = %2d\n", i, q.sqrt);
  }

  for (l = 0x3fed0169L; l < 0x3fed4169L; l++)
  {
    usqrt(l, &q);
    fprintf(out, "sqrt(%lX) = %X\n", l, q.sqrt);
  }

  fprintf(out, "********* ANGLE CONVERSION ***********\n");
  for (X = 0.0; X <= 360.0; X += .001)
    fprintf(out, "%3.0f degrees = %.12f radians\n", X, deg2rad(X));
  fprintf(out, "\n");

  for (X = 0.0; X <= (2 * PI + 1e-6); X += (PI / 5760))
    fprintf(out, "%.12f radians = %3.0f degrees\n", X, rad2deg(X));

  fclose(out);
  return 0;
}