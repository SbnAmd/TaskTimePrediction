#include "qsort.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define UNLIMIT
#define MAXARRAY 60000 /* this number, if too large, will cause a seg. fault!! */

struct myStringStruct {
  char qstring[128];
};

int compare_small(const void *elem1, const void *elem2)
{
  int result;
  
  result = strcmp((*((struct myStringStruct *)elem1)).qstring, (*((struct myStringStruct *)elem2)).qstring);

  return (result < 0) ? 1 : ((result == 0) ? 0 : -1);
}


// int main(int argc, char *argv[]) {           // Function name changed to _qsort_small to avoid conflict with main()
int __qsort_small(int argc, char *argv[]) {
  struct myStringStruct array[MAXARRAY];
  FILE *input_fp, *output_fp;
  int i, count = 0;

  output_fp = fopen("qsort_small_output.txt", "w");
  if (!output_fp) {
    perror("Error opening output file");
    exit(1);
  }

  if (argc < 2) {
    fprintf(output_fp, "Usage: qsort_small <file>\n");
    fclose(output_fp);
    exit(1);
  }

  input_fp = fopen(argv[1], "r");
  if (!input_fp) {
    fprintf(output_fp, "Error: Cannot open input file '%s'\n", argv[1]);
    fclose(output_fp);
    exit(1);
  }

  while ((fscanf(input_fp, "%s", array[count].qstring) == 1) && (count < MAXARRAY)) {
    count++;
  }

  fclose(input_fp);

  fprintf(output_fp, "\nSorting %d elements.\n\n", count);

  qsort(array, count, sizeof(struct myStringStruct), compare_small);

  for (i = 0; i < count; i++) {
    fprintf(output_fp, "%s\n", array[i].qstring);
  }

  fclose(output_fp);
  return 0;
}
