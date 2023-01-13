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
  uint8_t gray = grays(stdin);
  copy(stdin, 3);
  unsigned char c = 'a'; //initializing as != '\0'
  while (c != '\0') {
    c = getc(stdin); putchar(c);
  }
  int runs = make_compact_long(stdin);
  int arr[runs]; //array of counts
  for (int i=0; i<runs; i ++) {
    arr[i] = make_compact_long(stdin);
  }
  int count; unsigned char r, g, b; int i = 0;
  struct rgb pixels[width*height]; //fill in with each rgb value of image
  if (gray == 0) {
    for(int m=0; m < runs; m++) {
      r = getc(stdin);
      g = getc(stdin);
      b = getc(stdin);
      count = arr[m];
      while (count>0) {
        pixels[i].r = r;
        pixels[i].g = g;
        pixels[i].b = b;
        i++; count--;
      }
    }
  } else {
    for (int t=0; t < runs; t++) {
      c = getc(stdin);
      count = arr[t];
      while (count>0) {
        pixels[i].r = c;
        pixels[i].g = c;
        pixels[i].b = c;
        i++; count--;
      }
    }
  }
  int index = width;
  while (index<(width*height)) { //switching rgb in place for each width in array
  for (int low=(index-width), high=index-1; low<high; low++, high--)
    {
    struct rgb curr = pixels[high];
    pixels[high] = pixels[low];
    pixels[low] = curr;
    }
  index += width;
  }
  runs = 0; //read that array to get amount of runs
  for (int i = 1; i<=width*height; i++) {
    if (rgb_eq(pixels[i], pixels[i-1]) == 0) {
      runs++;
    }
  }
  putout_long(runs);
  int run_array[runs]; //creating the array of runs
  count = 1; int run_num = 0;
  for (int i = 1; i<=width*height; i++) {
    if (rgb_eq(pixels[i], pixels[i-1])) {
      count += 1;
    } else {
      run_array[run_num] = count;
      putout_long(count);
      run_num++;
      count = 1;
    }
  }
  int rgb_index = 0; //adding the rgb values
  for (int k = 0; k<runs; k++) {
    if (gray == 0) {
      c = pixels[rgb_index].r; putchar(c);
      c = pixels[rgb_index].g; putchar(c);
      c = pixels[rgb_index].b; putchar(c);
    } else {
      c = pixels[rgb_index].r; putchar(c);
    }
    rgb_index += run_array[k];
  }
  return 0;
}
