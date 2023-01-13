#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include "project2.h"

int rgb_eq(struct rgb c1, struct rgb c2)
{
  if ((c1.r == c2.r) && (c1.g == c2.g) && (c1.b == c2.b)) {
    return 1;
  } else {
    return 0;
  }
}

int img_grayscale(struct image *img)
{
  int len = img->w * img->h;
  if (img->pixels == NULL) {
    fprintf(stderr, "Error: no pixels");
    exit(1);
  }
  int i = 0;
  int bool = 0;
  while (i<len) {
    if (img->pixels[i].r == img->pixels[i].g && img->pixels[i].g == img->pixels[i].b) {
      bool = 1;
      i++;
    } else {
      bool = 0;
      i++;
    }
  }
  return bool;
}

int make_compact_short(FILE *f)
{
  uint16_t one = (getc(f) << 8);
  unsigned char two = getc(f);
  int total = one + two;
  return total;
}

void putout_short(int n)
{
  unsigned char c = n >> 8; putchar(c);
  c = n & 0XFF; putchar(c);
  return;
}


int make_compact_long(FILE *f)
{
  uint32_t one = (getc(f) << 24);
  uint32_t two = getc(f) << 16;
  uint32_t three = getc(f) << 8;
  uint32_t four = getc(f);
  int n_runs = one + two + three + four;
  return n_runs;
}


int make_compact_long_copy(FILE *f)
{
  unsigned char c = getc(f); putchar(c);
  uint32_t one = (c << 24);
  c = getc(f); putchar(c);
  uint32_t two = c << 16;
  c = getc(f); putchar(c);
  uint32_t three = c << 8;
  c = getc(f); putchar(c);
  uint32_t four = c;
  int n_runs = one + two + three + four;
  return n_runs;
}

void putout_long(int count)
{
  unsigned char c;
  c = count >> 24; putchar(c);
  c = (count >> 16) & 0XFF; putchar(c);
  c = (count >> 8) & 0XFF; putchar(c);
  c = count & 0XFF; putchar(c);
  return;
}

uint8_t grays(FILE *f)
{
  unsigned char c = getc(f); putchar(c);
  uint8_t grays = (c >> 1) & 01;
  return grays;
}

uint8_t grays_noputc(FILE *f)
{
  unsigned char c = getc(f);
  uint8_t grays = (c >> 1) & 01;
  return grays;
}

int dimensions(FILE *f)
{
  unsigned char c = getc(f); putchar(c);
  uint16_t first = (c << 8);
  c = getc(f); putchar(c);
  unsigned char second = c;
  int dimension = first + second;
  return dimension;
}

void copy(FILE *f, int skip)
{
  unsigned char c;
  for (int i=0; i<skip; i++) {
    c = getc(f); putchar(c);
  }
}

void skip(FILE *f, int skip)
{
  unsigned char c;
  for (int i=0; i<skip; i++) {
    c = getc(f);
  }
}

void makedate(struct tm *clock)
{
  int year = clock->tm_year + 1900;
  uint16_t hd = ((clock->tm_hour)*100) + clock->tm_min;
  putout_short(hd);
  uint32_t yd = (year * 10000) + ((clock->tm_mon + 1)*100) + clock->tm_mday;
  putout_long(yd);
}
