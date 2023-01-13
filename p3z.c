#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include "project2.h"
 
struct image *image_maker(FILE *f)
{
  struct image *img = (struct image *) malloc (sizeof (struct image));
  unsigned char file; int file_num; int w; int h; int i;
  fscanf(f, "%1c%d %d %d %d", &file, &file_num, &w, &h, &i);
  img->w = w;
  img->h = h;
  struct rgb *color = (struct rgb *) malloc (sizeof(struct rgb) * w * h);
  img->pixels = color;
  for (int i=0; i<(w*h); i++) {
    unsigned char r; unsigned char g; unsigned char b;
    fscanf(stdin, "%hhu %hhu %hhu ", &r, &g, &b);
    color[i].r = r;
    color[i].g = g;
    color[i].b = b;
  }
  return img;
}

unsigned char make_byte_eighteen(struct image *img)
{
  uint8_t bitmap = 0;
  if (img_grayscale(img)) {
    bitmap = 3; // for gray
  } else {
    bitmap = 1; // for rgb
  }
  return bitmap;
}


int main(int argc, char *argv[])
{
  unsigned char c;
  c = 'P'; putchar(c);
  c = 'Z'; putchar(c);
  c = '.'; putchar(c); putchar(c);

  //local time:
  struct tm *clock;
  time_t original_time;
  time(&original_time);
  clock = localtime(&original_time);
  unsigned char hour = clock->tm_hour;
  unsigned char min = clock->tm_min;
  unsigned char day = clock->tm_mday;
  unsigned char mon = clock->tm_mon + 1;
  int year = clock->tm_year + 1900;

  uint16_t hourdate = (hour*100) + min;
  c = hourdate >> 8; putchar(c);
  c = hourdate & 0XFF; putchar(c);

  uint32_t yeardate = (year * 10000) + (mon*100) + day;
  c = yeardate >> 24; putchar(c);
  c = (yeardate >> 16) & 0XFF; putchar(c);
  c = (yeardate >> 8) & 0XFF; putchar(c);
  c = yeardate & 0XFF; putchar(c);

  //make the image struct:
  struct image *img = image_maker(stdin);

  //width and height:
  uint16_t width = img->w;
  c = (width >> 8) & 0XFF; putchar(c);
  c = width & 0XFF; putchar(c);

  uint16_t height = img->h;
  c = (height >> 8) & 0XFF; putchar(c);
  c = height & 0XFF; putchar(c);

  int size = width*height;

  c = '.'; putchar(c); putchar(c); putchar(c); putchar(c);

  c = make_byte_eighteen(img); putchar(c);

  c = '.'; putchar(c); putchar(c); putchar(c);

  fprintf(stdout, "%s", argv[1]);
  c = '\0'; putchar(c);

  //number of runs:
  uint32_t runs = 0;
  for (int i = 1; i<=size; i++) {
    if (rgb_eq(img->pixels[i], img->pixels[i-1]) == 0) {
      runs++;
    }
  }
  c = runs >> 24; putchar(c);
  c = (runs >> 16) & 0XFF; putchar(c);
  c = (runs >> 8) & 0XFF; putchar(c);
  c = runs & 0XFF; putchar(c);

  //creating the array
  uint32_t run_array[runs];
  for (int i=0; i<runs; i++) {
    run_array[i] = 0;
  }
  int count = 1;
  int run_num = 0;
  for (int i = 1; i<=size; i++){
    if (rgb_eq(img->pixels[i], img->pixels[i-1])) {
      count += 1;
    } else {
      run_array[run_num] = count;
      run_num++;
      count = 1;
    }
  }

  //placing the counts in the array
  for (int j = 0; j<runs; j++) {
    c = run_array[j] >> 24; putchar(c);
    c = (run_array[j] >> 16) & 0XFF; putchar(c);
    c = (run_array[j] >> 8) & 0XFF; putchar(c);
    c = run_array[j] & 0XFF; putchar(c);
  }

  //adding the rgb values
  int rgb_index = 0;
  for (int k = 0; k<runs; k++) {
    if (img_grayscale(img) == 0) {
      c = img->pixels[rgb_index].r; putchar(c);
      c = img->pixels[rgb_index].g; putchar(c);
      c = img->pixels[rgb_index].b; putchar(c);
    } else {
      c = img->pixels[rgb_index].r; putchar(c);
    }
    rgb_index += run_array[k];
  }

  free(img->pixels);
  free(img);
  return 0;

}
