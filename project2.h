#ifndef _PROJECT2_H_
#define _PROJECT2_H_

#include <stdint.h>

struct rgb {
  unsigned char r;
  unsigned char g;
  unsigned char b;
};

struct image {
  uint32_t w;
  uint32_t h;
  struct rgb *pixels; // array of length w*h
};

// an image's pixels are stored in "row order",
// with the top row first from left to right,
// then the next row underneath, etc.

/* implement these two utilities in project1-utils.c */

// compare two rgb structs for logical equality
int rgb_eq(struct rgb c1, struct rgb c2);

// check if image is all gray pixels
int img_grayscale(struct image *img);

/* you may add more utilities if you like, but don't change these two */

//take elements from a file byte by byte (2bytes) and compress into an integer
int make_compact_short(FILE *f);

//take an in int and print it out byte by byte (2bytes)
void putout_short(int n);

//take elements from a byte by byte (4bytes) and turn into an integer
int make_compact_long(FILE *f);

//take elements from a byte by byte (4bytes), turn into an integer, and copy bytes
int make_compact_long_copy(FILE *f);

//take an in int (4 bytes) and print it out the characters
void putout_long(int count);

//check bitmap for gray and put out the unsigned char to sdout
uint8_t grays(FILE *f);

//check bitmap and return an unsigned char
uint8_t grays_noputc(FILE *f);

//take in information from file and calculate dimesions and put out dimensions
int dimensions(FILE *f);

//copy function for pz to pz files, takes in chars and outputs them to stdout
void copy(FILE *f, int skip);

//skip "skip" amount of bytes b
void skip(FILE *f, int skip);

//take in a time struct and print out a date in the correct format
void makedate(struct tm *clock);



#endif
