#ifndef __MATHEMATICS_H__
#define __MATHEMATICS_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <utils.h>

#define BMP_PADDING(pxl)      (pxl%sizeof(uint32_t))

#define TO_COORD(arg,x,y)                                  \
{                                                          \
int8_t* p=arg;                                             \
int8_t* t=x;                                               \
do {                                                       \
  *t = *p;                                                 \
  if ( (*p=='X') || (*p=='x') ) {                          \
    *t = 0;                                                \
    p++;                                                   \
    t=y;                                                   \
    continue;                                              \
  }                                                        \
  t++;                                                     \
  p++;                                                     \
  *t = 0;                                                  \
} while(*p);                                               \
}


enum
{
  RED,
  GREEN,
  BLUE,
};


#pragma pack(1)
typedef struct
{
  uint8_t  sign[2];
  uint32_t total_size;
  uint16_t reserved1;
  uint16_t reserved2;
  uint32_t offset;
} BMPFHdr;
#pragma pack()


#pragma pack(1)
typedef struct
{
  uint32_t  size;
  uint32_t width;
  uint32_t height;
  uint16_t planes;
  uint16_t bitcount;
  uint32_t compression;
  uint32_t size_of_image;
  uint32_t reserved[4];
} DIBHdr;
#pragma pack()


#pragma pack(1)
typedef struct
{
  BMPFHdr  fhdr;
  DIBHdr   dhdr;
} BMPHdr;
#pragma pack()



void printMatrix(int32_t* p, int8_t* sz);

void addMatrix(int32_t* a, int32_t* b, int8_t* sz, int32_t* s);
void mulMatrix(int32_t* a, int8_t* asz, int32_t* b, int8_t* bsz, int32_t* s);
void createMatrixI(int32_t* p, int8_t* sz);
void createMatrixO(int32_t* p, int8_t* sz);
int32_t matrixDet(int32_t* p, int8_t* sz);


int32_t findMIN(int32_t* arr, int32_t sz, int32_t* min);
int32_t findMAX(int32_t* arr, int32_t sz, int32_t* max);
int32_t findMAX8bit(int8_t* arr, int32_t sz, int8_t* max);



void printBitmapHdr(uint8_t* p);
void readBitmapHdr(uint8_t* p, BMPHdr* h);
int32_t serializeBitmap(BMPHdr* bmphdr, int8_t* img, int8_t* raw);
int32_t deserializeBitmap(int32_t* wh, int32_t bcnt, int8_t* raw, int8_t* bmp);

int32_t serializePaddingSize(BMPHdr* bmphdr, int32_t pwdth);
int32_t serializePadding(BMPHdr* bmphdr, int32_t pwdth, int8_t* img, int8_t* raw);



void assign8bit(int8_t* p, int32_t count);
void assign32bit(int32_t* p, int32_t count);
void assignFloat(long double* p, int32_t count);


int32_t createFilter(int8_t* wh, int32_t** filter);

void assignFloat(long double* p, int32_t count);

void printFloatFilter(int32_t* wh, long double* filter);
int32_t createFloatFilter(int32_t* wh, long double** filter);

int32_t convolutionProduct(uint8_t* input, int32_t* iwh, int32_t padding, int32_t stride, uint32_t* filter, int32_t* fwh, int8_t ft, uint8_t* output, int32_t* owh);
int32_t convolutions(uint8_t* input, int32_t* iwh, int32_t padding, int32_t stride, long double* filter, int32_t* fwh, int8_t ft, uint8_t* output, int32_t* owh);
int32_t maxpooling(uint8_t* input, int32_t* iwh, int32_t stride, int8_t ft, uint8_t* output, int32_t* owh);



#endif
