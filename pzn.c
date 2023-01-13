#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include "project2.h"


int main(int argc, char *argv[])
{ 
  unsigned char c = '0';
  copy(stdin, 4);
  struct tm *clock;
  time_t original_time;
  time(&original_time);
  clock = localtime(&original_time);
  makedate(clock); //put in the time
  skip(stdin, 6);
  dimensions(stdin); dimensions(stdin);
  copy(stdin, 4);
  uint8_t gray = grays(stdin);
  copy(stdin, 3);
  while (c != '\0') {
    c = getc(stdin); putchar(c);
  }
  int runs = make_compact_long_copy(stdin);
  for (int l = 0; l < runs; l++) {
    make_compact_long_copy(stdin);
  }
  unsigned char r; unsigned char g; unsigned char b;
  for (int l = 0; l<runs; l++) {
    if (gray==0) {
      r = getc(stdin); putchar(255-r);
      g = getc(stdin); putchar(255-g);
      b = getc(stdin); putchar(255-b);
    } else {
        c = getc(stdin); putchar(255-c);
    }
  }
  return 0;
}
