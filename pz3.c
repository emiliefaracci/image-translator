#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include "project2.h"

int make_compact(FILE *f)
{ 
  uint32_t run_1 = (getc(f) << 24);
  uint32_t run_2 = getc(f) << 16;
  uint32_t run_3 = getc(f) << 8;
  uint32_t run_4 = getc(f);
  int n_runs = run_1 + run_2 + run_3 + run_4;
  return n_runs;
}

int main(int argc, char *argv[])
{
  int c;
  for (int i = 0; i<10; i++) {
    c = getc(stdin);
  }
  fprintf(stdout, "P3\n");

  //width:
  uint16_t width_one = (getc(stdin) << 8);
  unsigned char width_two = getc(stdin);
  int width = width_one + width_two;
  fprintf(stdout, "%d ", width);

  //height:
  uint16_t height_one = (getc(stdin) << 8);
  unsigned char height_two = getc(stdin);
  int height = height_one + height_two;
  fprintf(stdout, "%d\n255\n", height);

  for (int i = 0; i<4; i++) {
    c = getc(stdin);
  }

  //byte 18:
  c = getc(stdin);
  uint8_t grays = (c >> 1) & 01;

  for (int i = 0; i<3; i++) {
    c = getc(stdin);
  }

  while(c != '\0') {
    c = getc(stdin);
  }

  //number of runs:
  int n_runs = make_compact_long(stdin);

  //initialize array of run length with counts:
  uint32_t array[n_runs];
  for (int i=0; i<n_runs; i++) {
    array[i] = 0;
  }
  for (int k = 0; k < n_runs; k++)
  {
    array[k] = make_compact_long(stdin);
  }

  if (grays) {
    for(int m=0; m < n_runs; m++) {
      int color_rgb = getc(stdin);
      int count = array[m];
      while (count>0) {
        fprintf(stdout, "%d %d %d ", color_rgb, color_rgb, color_rgb);
        count--;
      }
    }
  } else {
    for(int m=0; m < n_runs; m++) {
      int red = getc(stdin);
      int green = getc(stdin);
      int blue = getc(stdin);
      int count = array[m];
      while (count>0) {
        fprintf(stdout, "%d %d %d ", red, green, blue);
        count--;
      }
    }
  }

  return 0;
}
