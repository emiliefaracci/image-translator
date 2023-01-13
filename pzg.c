#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include "project2.h"


int main(int argc, char *argv[])
{
  copy(stdin, 4);
  struct tm *clock;
  time_t original_time;
  time(&original_time);
  clock = localtime(&original_time);
  makedate(clock);
  skip(stdin, 6);
  int width = dimensions(stdin);
  int height = dimensions(stdin);
  copy(stdin, 4);
  uint8_t gray = grays_noputc(stdin);
  unsigned char c = 3; putchar(c); //make grayscale
  copy(stdin, 3);
  while (c != '\0') {
    c = getc(stdin); putchar(c);
  }
  int runs = make_compact_long(stdin);
  int array[runs];
  for (int l = 0; l < runs; l++) {
    array[l] = make_compact_long(stdin);
  }
  unsigned char luminance; int i=0;
  struct rgb pixels[width*height]; //make rgb struct array with all the luminances
  for (int l=0; l<runs; l++) {
    if (gray==0) {
      luminance = (0.2126*getc(stdin) + 0.7152*getc(stdin) + 0.0722*getc(stdin));
    } else {
      c = getc(stdin); luminance = (0.2126*c +  0.7152*c + 0.0722*c);
    }
      while (array[l]>0) {
        pixels[i].r = luminance;
        pixels[i].g = luminance;
        pixels[i].b = luminance;
        array[l]--; i++;
      }
    }
    runs = 0; //read pixels[] to get amount of runs
    for (int i = 1; i<=width*height; i++) {
      if (rgb_eq(pixels[i], pixels[i-1]) == 0) {
        runs++;
      }
    }
    putout_long(runs);
    int run_array[runs]; //creating the array of runs
    int count = 1; int run_num = 0;
    for (int i = 1; i<=width*height; i++) {
      if (rgb_eq(pixels[i], pixels[i-1])) {
        count += 1;
      } else {
        run_array[run_num] = count;
        putout_long(count);
        run_num++; count = 1;
      }
    }
    int rgb_index = 0; // printing out the luminance value for each pixel
    for (int k = 0; k<runs; k++) {
        c = pixels[rgb_index].r; putchar(c);
        rgb_index += run_array[k];
    }
return 0;
}
