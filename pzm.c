#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include "project2.h"

int main(int argc, char *argv[])
{
  FILE *file;
  file = fopen(argv[1], "r");
  if (file) { 
    fprintf(stdout, "{\n\t\"filename\" : \"%s\",\n\t", argv[1]);
    skip(file, 4);
    int time = make_compact_short(file);
    int date = make_compact_long(file);
    fprintf(stdout, "\"date\" : %d,\n\t\"time\" : %d,\n\t", date, time);
    int width = make_compact_short(file);
    int height = make_compact_short(file);
    fprintf(stdout, "\"width\" : %d,\n\t\"height\" : %d,\n\t", width, height);
    skip(file, 4);
    fprintf(stdout, "\"grayscale\" : ");
    unsigned char c = getc(file);
    uint8_t grays = (c >> 1) & 01;
    if (grays) {
      fprintf(stdout, "true,\n\t\"rle\" : true,\n\t");
    } else {
      fprintf(stdout, "false,\n\t\"rle\" : true,\n\t");
    }
    skip(file, 3);
    fprintf(stdout, "\"description\" : \"");
    while (c != '\0') {
      c = getc(file);
      if (c != '\0')
      putchar(c);
    }
    fprintf(stdout, "\",\n\t\"runs\" : ");
    int runs = make_compact_long(file);
    fprintf(stdout, "%d,\n\t\"run-bytes\" : %d,\n\t", runs, (runs*4));
    if (grays) {
      fprintf(stdout, "\"pixel-bytes\" : %d\n}", runs);
    } else {
      fprintf(stdout, "\"pixel-bytes\" : %d\n}\n", (runs*3));
    }
    fclose(file);
  } else {
    fprintf(stderr, "file not found");
    exit(1);
  }
  return 0;
}
