#include "qsort.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define UNLIMIT
#define MAXARRAY 60000 /* this number, if too large, will cause a seg. fault!! */

struct my3DVertexStruct {
  int x, y, z;
  double distance;
};

int compare_large(const void *elem1, const void *elem2)
{
  /* D = [(x1 - x2)^2 + (y1 - y2)^2 + (z1 - z2)^2]^(1/2) */
  /* sort based on distances from the origin... */

  double distance1, distance2;

  distance1 = (*((struct my3DVertexStruct *)elem1)).distance;
  distance2 = (*((struct my3DVertexStruct *)elem2)).distance;

  return (distance1 > distance2) ? 1 : ((distance1 == distance2) ? 0 : -1);
}


// int  main(int argc, char *argv[]) {        // Function name changed to avoid conflict with main()
int __qsort_large(int argc, char *argv[]) {
  struct my3DVertexStruct array[MAXARRAY];
  FILE *input_fp, *output_fp;
  int i, count = 0;
  int x, y, z;

  output_fp = fopen("qsort_large_output.txt", "w");
  if (!output_fp) {
    perror("Error opening output file");
    exit(1);
  }

  if (argc < 2) {
    fprintf(output_fp, "Usage: qsort_large <file>\n");
    fclose(output_fp);
    exit(1);
  }

  input_fp = fopen(argv[1], "r");
  if (!input_fp) {
    fprintf(output_fp, "Error: Cannot open input file '%s'\n", argv[1]);
    fclose(output_fp);
    exit(1);
  }

  while ((fscanf(input_fp, "%d", &x) == 1) &&
         (fscanf(input_fp, "%d", &y) == 1) &&
         (fscanf(input_fp, "%d", &z) == 1) &&
         (count < MAXARRAY)) {
    array[count].x = x;
    array[count].y = y;
    array[count].z = z;
    array[count].distance = sqrt((double)(x * x + y * y + z * z));
    count++;
         }
  // fixme
  fclose(input_fp);

  fprintf(output_fp, "\nSorting %d vectors based on distance from the origin.\n\n", count);

  qsort(array, count, sizeof(struct my3DVertexStruct), compare_large);

  for (i = 0; i < count; i++) {
    fprintf(output_fp, "%d %d %d\n", array[i].x, array[i].y, array[i].z);
  }

  fclose(output_fp);
  return 0;
}
