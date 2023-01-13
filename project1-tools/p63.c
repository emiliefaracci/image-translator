#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include "project1.h"

int main(int argc, char *argv[])
{

  unsigned char file; int file_num; int w; int h; int i;
  fscanf(stdin, "%1c%d %d %d %d ", &file, &file_num, &w, &h, &i);
  fprintf(stdout, "%1c3\n%d %d\n%d\n", file, w, h, i);

  int c = getc(stdin);
  while (c != EOF) {
    fprintf(stdout, "%d ", c);
    c = getc(stdin);
  }
  fprintf(stdout, "\n");
  return 0;
}
