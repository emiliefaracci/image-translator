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
  int ow = make_compact_short(stdin);
  int w =ow*2;
  putout_short(w);
  dimensions(stdin);
  copy(stdin, 4);
  int gray = grays(stdin);
  copy(stdin, 3);
  unsigned char c = '0';
  while (c != '\0') {
    c = getc(stdin); putchar(c);
  }
  int runs = make_compact_long_copy(stdin);
  int count;
  for (int l = 0; l < runs; l++) {
    count = make_compact_long(stdin)*2;
    putout_long(count);
  }
  unsigned char r, g, b;
  for (int l = 0; l<runs; l++) {
      if (gray==0) {
        r = getc(stdin); putchar(r);
        g = getc(stdin); putchar(g);
        b = getc(stdin); putchar(b);
      } else {
        r = getc(stdin); putchar(r);
      }
  }
  return 0;
}
