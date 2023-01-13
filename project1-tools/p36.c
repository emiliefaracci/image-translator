#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include "project1.h"

int main(int argc, char *argv[])
{

  unsigned char file; int file_num; int w; int h; int i;
  fscanf(stdin, "%1c%d %d %d %d", &file, &file_num, &w, &h, &i);
  fprintf(stdout, "%1c6\n%d %d\n%d\n", file, w, h, i);

  for (int i=0; i<(w*h); i++) {
    uint8_t r; uint8_t g; uint8_t b;
    fscanf(stdin, "%hhu %hhu %hhu ", &r, &g, &b);
    fprintf(stdout, "%c%c%c", r, g, b);
  }
  fprintf(stdout, "\n");
  return 0;
}
