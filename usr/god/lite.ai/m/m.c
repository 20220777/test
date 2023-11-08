#include "__bitmap.h"

#include <Windows.h>
#include <time.h>
#include "utils.h"
#include "mathematics.h"



#define SAMPLE_TITLE       "joker2"
#define CONVOLUTION_NAME   "convolution"
#define POOLING_NAME       "pooling"




void main()
{
  int32_t count = 16;
  int32_t i = 0;
  int32_t r = 0;

  long double* filter[3] = {0};

  uint8_t* pConvolution = 0;
  uint8_t* pPooling = 0;
  uint8_t* rawBMP = 0;
  uint8_t* serializedImage = 0;

  int32_t filterWH[2] = {0};
  int32_t convolutionWH[2] = {0};
  int32_t poolingWH[2] = {0};
  int32_t rawBMPWH[2] = {0};
  int32_t serializedWH[2] = {0};
  int32_t deserializedWH[2] = {0};

  int32_t size_with_padding = 0;
  int32_t stride = 1;

  BMPHdr  bmphdr = {0};

  uint8_t fname[1024] = {0};
  uint8_t dname[1024] = {0};
  time_t  tt = {0};
  struct tm* t = 0;

  FILE* fp = 0;
  



  fp = fopen("..\\imgs\\sample.bmp", "rb");

  r = fread(&bmphdr, sizeof(int8_t), sizeof(BMPHdr), fp);
  rawBMP = calloc(bmphdr.fhdr.total_size - sizeof(BMPHdr), sizeof(uint8_t));
  r = fread(rawBMP, sizeof(int8_t), bmphdr.fhdr.total_size - sizeof(BMPHdr), fp);

  __TR__;
  printBuffer(rawBMP, bmphdr.fhdr.total_size - sizeof(BMPHdr));

  size_with_padding = serializePaddingSize(&bmphdr, 1);

  // serialize
  serializedImage = calloc(size_with_padding, sizeof(uint8_t));

  {
    int32_t wh[2] = { 0};
    wh[0] = bmphdr.dhdr.width;
    wh[1] = bmphdr.dhdr.height;

    for( i=0 ; i<size_with_padding ; i++ ) *(serializedImage+i) = 0;
    r = __serialize_bitmap(rawBMP, wh, 24, 1, "rb", serializedImage);
    __TR__;
    printBuffer(serializedImage, r);
  }


  {
    int32_t wh[2] = { 0};
    wh[0] = bmphdr.dhdr.width;
    wh[1] = bmphdr.dhdr.height;

    for( i=0 ; i<size_with_padding ; i++ ) *(serializedImage+i) = 0;
    r = __serialize_bitmap(rawBMP, wh, 24, 1, "fb", serializedImage);

    __TR__;
    printBuffer(serializedImage, r);
  }

  __TR__;
  printBuffer(rawBMP, bmphdr.fhdr.total_size - sizeof(BMPHdr));


  {
    int32_t wh[2] = { 0};
    wh[0] = bmphdr.dhdr.width;
    wh[1] = bmphdr.dhdr.height;

    for( i=0 ; i<size_with_padding ; i++ ) *(serializedImage+i) = 0;
    r = __serialize_bitmap(rawBMP, wh, 24, 0, "rb", serializedImage);
    __TR__;
    printBuffer(serializedImage, r);
  }


  {
    int32_t wh[2] = { 0};
    wh[0] = bmphdr.dhdr.width;
    wh[1] = bmphdr.dhdr.height;

    for( i=0 ; i<size_with_padding ; i++ ) *(serializedImage+i) = 0;
    r = __serialize_bitmap(rawBMP, wh, 24, 0, "fb", serializedImage);

    __TR__;
    printBuffer(serializedImage, r);
  }


  __TR__;
  printBuffer(rawBMP, bmphdr.fhdr.total_size - sizeof(BMPHdr));


  {
    int32_t wh[2] = { 0};
    wh[0] = bmphdr.dhdr.width;
    wh[1] = bmphdr.dhdr.height;
    for( i=0 ; i<size_with_padding ; i++ ) *(serializedImage+i) = 0;
    r = __serialize_bitmap(rawBMP, wh, 24, 1, "r", serializedImage);
    __TR__;
    printBuffer(serializedImage, r);
  }


  {
    int32_t wh[2] = { 0};
    wh[0] = bmphdr.dhdr.width;
    wh[1] = bmphdr.dhdr.height;
    for( i=0 ; i<size_with_padding ; i++ ) *(serializedImage+i) = 0;
    r = __serialize_bitmap(rawBMP, wh, 24, 1, "f", serializedImage);

    __TR__;
    printBuffer(serializedImage, r);
  }

  __TR__;
  printBuffer(rawBMP, bmphdr.fhdr.total_size - sizeof(BMPHdr));


  {
    int32_t wh[2] = { 0};
    wh[0] = bmphdr.dhdr.width;
    wh[1] = bmphdr.dhdr.height;
    for( i=0 ; i<size_with_padding ; i++ ) *(serializedImage+i) = 0;
    r = __serialize_bitmap(rawBMP, wh, 24, 0, "r", serializedImage);
    __TR__;
    printBuffer(serializedImage, r);
  }


  {
    int32_t wh[2] = { 0};
    wh[0] = bmphdr.dhdr.width;
    wh[1] = bmphdr.dhdr.height;
    for( i=0 ; i<size_with_padding ; i++ ) *(serializedImage+i) = 0;
    r = __serialize_bitmap(rawBMP, wh, 24, 0, "f", serializedImage);

    __TR__;
    printBuffer(serializedImage, r);
  }

  free(rawBMP);
  



  fclose(fp);



  fclose(fp);

  srand(time(0));


  filterWH[0] = 3;
  filterWH[1] = 3;
  createFloatFilter(filterWH, &filter[RED]);
  createFloatFilter(filterWH, &filter[GREEN]);
  createFloatFilter(filterWH, &filter[BLUE]);

  //i=0;
  //*(filter[RED] + i) = *(filter[GREEN] + i) = *(filter[BLUE] + i) = -1.0; i++;
  //*(filter[RED] + i) = *(filter[GREEN] + i) = *(filter[BLUE] + i) =  0.0; i++;
  //*(filter[RED] + i) = *(filter[GREEN] + i) = *(filter[BLUE] + i) =  1.0; i++;
  //*(filter[RED] + i) = *(filter[GREEN] + i) = *(filter[BLUE] + i) = -1.0; i++;
  //*(filter[RED] + i) = *(filter[GREEN] + i) = *(filter[BLUE] + i) =  0.0; i++;
  //*(filter[RED] + i) = *(filter[GREEN] + i) = *(filter[BLUE] + i) =  1.0; i++;
  //*(filter[RED] + i) = *(filter[GREEN] + i) = *(filter[BLUE] + i) = -1.0; i++;
  //*(filter[RED] + i) = *(filter[GREEN] + i) = *(filter[BLUE] + i) =  0.0; i++;
  //*(filter[RED] + i) = *(filter[GREEN] + i) = *(filter[BLUE] + i) =  1.0; i++;


  for ( ; count>=0 ; count -- )
  {
    sprintf(fname, "%s.bmp", SAMPLE_TITLE);
    for ( i=0 ; i<5 ; i++ )
    {
      createFloatFilter(filterWH, &filter[RED]);
      createFloatFilter(filterWH, &filter[GREEN]);
      createFloatFilter(filterWH, &filter[BLUE]);

      tt = time(0);
      t = localtime(&tt);
      sprintf(dname, "%s_%02d%02d%02d%02d", SAMPLE_TITLE, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min);
      CreateDirectory(dname, 0);

      fp = fopen(fname, "rb");
      r = fread(&bmphdr, sizeof(int8_t), sizeof(BMPHdr), fp);
      rawBMP = calloc(bmphdr.fhdr.total_size - sizeof(BMPHdr), sizeof(uint8_t));
      r = fread(rawBMP, sizeof(int8_t), bmphdr.fhdr.total_size - sizeof(BMPHdr), fp);
      fclose(fp);

      size_with_padding = serializePaddingSize(&bmphdr, 1);

      // serialize
      serializedImage = calloc(size_with_padding, sizeof(uint8_t));
      r = serializePadding(&bmphdr, 1, rawBMP, serializedImage);
      free(rawBMP);

      serializedWH[0] = bmphdr.dhdr.width;
      serializedWH[1] = bmphdr.dhdr.height;

      pConvolution = calloc(bmphdr.fhdr.total_size - sizeof(BMPHdr), sizeof(uint8_t));
      r = convolutions(serializedImage, serializedWH, 1, stride, filter[RED],  filterWH, 'R', pConvolution, convolutionWH);
      r = convolutions(serializedImage, serializedWH, 1, stride, filter[GREEN],filterWH, 'G', pConvolution, convolutionWH);
      r = convolutions(serializedImage, serializedWH, 1, stride, filter[BLUE], filterWH, 'B', pConvolution, convolutionWH);

      free(serializedImage);

      {
        sprintf(fname, "%s\\%s_%d_%d_%02d_%02d.bmp", dname, CONVOLUTION_NAME, count, i, t->tm_min, t->tm_sec );
        fp = fopen(fname, "wb");

        rawBMP = calloc((convolutionWH[0]*3+BMP_PADDING(convolutionWH[0]))*convolutionWH[1], sizeof(uint8_t));
        r = deserializeBitmap(convolutionWH, 24, pConvolution, rawBMP);

        bmphdr.fhdr.total_size = sizeof(BMPHdr) + (convolutionWH[0]*3+BMP_PADDING(convolutionWH[0]))*convolutionWH[1];
        bmphdr.dhdr.bitcount = 24;
        bmphdr.dhdr.planes = 1;
        bmphdr.dhdr.width = convolutionWH[0];
        bmphdr.dhdr.height = convolutionWH[1];

        fwrite(&bmphdr, 54, 1, fp);
        fwrite(rawBMP, r, 1, fp);
        free(rawBMP);
        fclose(fp);
      }


      pPooling = calloc(convolutionWH[0]*convolutionWH[1]*3, sizeof(uint8_t));
      maxpooling(pConvolution, convolutionWH, stride*2, 'R', pPooling, poolingWH);
      maxpooling(pConvolution, convolutionWH, stride*2, 'G', pPooling, poolingWH);
      maxpooling(pConvolution, convolutionWH, stride*2, 'B', pPooling, poolingWH);


      {
        sprintf(fname, "%s\\%s_%d_%d_%02d_%02d.bmp", dname, POOLING_NAME, count, i, t->tm_min, t->tm_sec );
        fp = fopen(fname, "wb");

        rawBMP = calloc((poolingWH[0]*3+BMP_PADDING(poolingWH[0]))*poolingWH[1], sizeof(uint8_t));
        r = deserializeBitmap(poolingWH, 24, pPooling, rawBMP);

        bmphdr.fhdr.total_size = sizeof(BMPHdr) + (poolingWH[0]*3+BMP_PADDING(poolingWH[0]))*poolingWH[1];
        bmphdr.dhdr.bitcount = 24;
        bmphdr.dhdr.planes = 1;
        bmphdr.dhdr.width = poolingWH[0];
        bmphdr.dhdr.height = poolingWH[1];

        fwrite(&bmphdr, 54, 1, fp);
        fwrite(rawBMP, r, 1, fp);
        free(rawBMP);
        fclose(fp);
      }

      free(pConvolution);
      free(pPooling);
    }
  }


  free(filter[RED]);
  free(filter[GREEN]);
  free(filter[BLUE]);
  fclose(fp);
}






























#if 0
void main()
{
  int32_t count = 16;
  int32_t i = 0;
  int32_t r = 0;

  long double* filter[3] = {0};

  uint8_t* pConvolution = 0;
  uint8_t* pPooling = 0;
  uint8_t* rawBMP = 0;
  uint8_t* serializedImage = 0;

  int32_t filterWH[2] = {0};
  int32_t convolutionWH[2] = {0};
  int32_t poolingWH[2] = {0};
  int32_t rawBMPWH[2] = {0};
  int32_t serializedWH[2] = {0};
  int32_t deserializedWH[2] = {0};

  int32_t size_with_padding = 0;
  int32_t stride = 1;

  BMPHdr  bmphdr = {0};

  uint8_t fname[1024] = {0};
  uint8_t dname[1024] = {0};
  time_t  tt = {0};
  struct tm* t = 0;

  FILE* fp = 0;
  //FILE* fp = fopen("..\\imgs\\sample.bmp", "rb");

  srand(time(0));


  filterWH[0] = 3;
  filterWH[1] = 3;
  createFloatFilter(filterWH, &filter[RED]);
  createFloatFilter(filterWH, &filter[GREEN]);
  createFloatFilter(filterWH, &filter[BLUE]);

  //i=0;
  //*(filter[RED] + i) = *(filter[GREEN] + i) = *(filter[BLUE] + i) = -1.0; i++;
  //*(filter[RED] + i) = *(filter[GREEN] + i) = *(filter[BLUE] + i) =  0.0; i++;
  //*(filter[RED] + i) = *(filter[GREEN] + i) = *(filter[BLUE] + i) =  1.0; i++;
  //*(filter[RED] + i) = *(filter[GREEN] + i) = *(filter[BLUE] + i) = -1.0; i++;
  //*(filter[RED] + i) = *(filter[GREEN] + i) = *(filter[BLUE] + i) =  0.0; i++;
  //*(filter[RED] + i) = *(filter[GREEN] + i) = *(filter[BLUE] + i) =  1.0; i++;
  //*(filter[RED] + i) = *(filter[GREEN] + i) = *(filter[BLUE] + i) = -1.0; i++;
  //*(filter[RED] + i) = *(filter[GREEN] + i) = *(filter[BLUE] + i) =  0.0; i++;
  //*(filter[RED] + i) = *(filter[GREEN] + i) = *(filter[BLUE] + i) =  1.0; i++;


  for ( ; count>=0 ; count -- )
  {
    sprintf(fname, "%s.bmp", SAMPLE_TITLE);
    for ( i=0 ; i<5 ; i++ )
    {
      createFloatFilter(filterWH, &filter[RED]);
      createFloatFilter(filterWH, &filter[GREEN]);
      createFloatFilter(filterWH, &filter[BLUE]);

      tt = time(0);
      t = localtime(&tt);
      sprintf(dname, "%s_%02d%02d%02d%02d", SAMPLE_TITLE, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min);
      CreateDirectory(dname, 0);

      fp = fopen(fname, "rb");
      r = fread(&bmphdr, sizeof(int8_t), sizeof(BMPHdr), fp);
      rawBMP = calloc(bmphdr.fhdr.total_size - sizeof(BMPHdr), sizeof(uint8_t));
      r = fread(rawBMP, sizeof(int8_t), bmphdr.fhdr.total_size - sizeof(BMPHdr), fp);
      fclose(fp);

      size_with_padding = serializePaddingSize(&bmphdr, 1);

      // serialize
      serializedImage = calloc(size_with_padding, sizeof(uint8_t));
      r = serializePadding(&bmphdr, 1, rawBMP, serializedImage);
      free(rawBMP);

      serializedWH[0] = bmphdr.dhdr.width;
      serializedWH[1] = bmphdr.dhdr.height;

      pConvolution = calloc(bmphdr.fhdr.total_size - sizeof(BMPHdr), sizeof(uint8_t));
      r = convolutions(serializedImage, serializedWH, 1, stride, filter[RED],  filterWH, 'R', pConvolution, convolutionWH);
      r = convolutions(serializedImage, serializedWH, 1, stride, filter[GREEN],filterWH, 'G', pConvolution, convolutionWH);
      r = convolutions(serializedImage, serializedWH, 1, stride, filter[BLUE], filterWH, 'B', pConvolution, convolutionWH);

      free(serializedImage);

      {
        sprintf(fname, "%s\\%s_%d_%d_%02d_%02d.bmp", dname, CONVOLUTION_NAME, count, i, t->tm_min, t->tm_sec );
        fp = fopen(fname, "wb");

        rawBMP = calloc((convolutionWH[0]*3+BMP_PADDING(convolutionWH[0]))*convolutionWH[1], sizeof(uint8_t));
        r = deserializeBitmap(convolutionWH, 24, pConvolution, rawBMP);

        bmphdr.fhdr.total_size = sizeof(BMPHdr) + (convolutionWH[0]*3+BMP_PADDING(convolutionWH[0]))*convolutionWH[1];
        bmphdr.dhdr.bitcount = 24;
        bmphdr.dhdr.planes = 1;
        bmphdr.dhdr.width = convolutionWH[0];
        bmphdr.dhdr.height = convolutionWH[1];

        fwrite(&bmphdr, 54, 1, fp);
        fwrite(rawBMP, r, 1, fp);
        free(rawBMP);
        fclose(fp);
      }


      pPooling = calloc(convolutionWH[0]*convolutionWH[1]*3, sizeof(uint8_t));
      maxpooling(pConvolution, convolutionWH, stride*2, 'R', pPooling, poolingWH);
      maxpooling(pConvolution, convolutionWH, stride*2, 'G', pPooling, poolingWH);
      maxpooling(pConvolution, convolutionWH, stride*2, 'B', pPooling, poolingWH);


      {
        sprintf(fname, "%s\\%s_%d_%d_%02d_%02d.bmp", dname, POOLING_NAME, count, i, t->tm_min, t->tm_sec );
        fp = fopen(fname, "wb");

        rawBMP = calloc((poolingWH[0]*3+BMP_PADDING(poolingWH[0]))*poolingWH[1], sizeof(uint8_t));
        r = deserializeBitmap(poolingWH, 24, pPooling, rawBMP);

        bmphdr.fhdr.total_size = sizeof(BMPHdr) + (poolingWH[0]*3+BMP_PADDING(poolingWH[0]))*poolingWH[1];
        bmphdr.dhdr.bitcount = 24;
        bmphdr.dhdr.planes = 1;
        bmphdr.dhdr.width = poolingWH[0];
        bmphdr.dhdr.height = poolingWH[1];

        fwrite(&bmphdr, 54, 1, fp);
        fwrite(rawBMP, r, 1, fp);
        free(rawBMP);
        fclose(fp);
      }

      free(pConvolution);
      free(pPooling);
    }
  }


  free(filter[RED]);
  free(filter[GREEN]);
  free(filter[BLUE]);
  fclose(fp);
}
#endif












#if 0
void main()
{
  int32_t i = 0;
  int32_t r = 0;

  long double* filter[3] = {0};

  uint8_t* pConvolution = 0;
  uint8_t* pPooling = 0;
  uint8_t* rawBMP = 0;
  uint8_t* serializedImage = 0;
  uint8_t* deserializedImage = 0;

  int32_t filterWH[2] = {0};
  int32_t convolutionWH[2] = {0};
  int32_t poolingWH[2] = {0};
  int32_t rawBMPWH[2] = {0};
  int32_t serializedWH[2] = {0};
  int32_t deserializedWH[2] = {0};

  int32_t size_with_padding = 0;
  int32_t stride = 1;

  BMPHdr  bmphdr = {0};

  uint8_t tmp[128] = {0};
  time_t  tt = {0};
  struct tm* t = 0;

  FILE* fp = fopen("joker.bmp", "rb");
  FILE* fcon = 0;
  FILE* fpool = 0;
  //FILE* fp = fopen("..\\imgs\\sample.bmp", "rb");

  srand(time(0));


  filterWH[0] = 3;
  filterWH[1] = 3;
  createFloatFilter(filterWH, &filter[RED]);
  createFloatFilter(filterWH, &filter[GREEN]);
  createFloatFilter(filterWH, &filter[BLUE]);


  // Read BMP
  r = fread(&bmphdr, sizeof(int8_t), sizeof(BMPHdr), fp);
  rawBMP = calloc(bmphdr.fhdr.total_size - sizeof(BMPHdr), sizeof(uint8_t));
  r = fread(rawBMP, sizeof(int8_t), bmphdr.fhdr.total_size - sizeof(BMPHdr), fp);





  tt = time(0);
  t = localtime(&tt);


  size_with_padding = serializePaddingSize(&bmphdr, 1);
  serializedImage = calloc(size_with_padding, sizeof(uint8_t));

  r = serializePadding(&bmphdr, 1, rawBMP, serializedImage);

  serializedWH[0] = bmphdr.dhdr.width;
  serializedWH[1] = bmphdr.dhdr.height;



  pConvolution = calloc(bmphdr.fhdr.total_size - sizeof(BMPHdr), sizeof(uint8_t));
  r = convolutions(serializedImage, serializedWH, 1, stride, filter[RED],  filterWH, 'R', pConvolution, convolutionWH);
  r = convolutions(serializedImage, serializedWH, 1, stride, filter[GREEN],filterWH, 'G', pConvolution, convolutionWH);
  r = convolutions(serializedImage, serializedWH, 1, stride, filter[BLUE], filterWH, 'B', pConvolution, convolutionWH);
  free(serializedImage);

  sprintf(tmp, "joker_a0-convolution_%02d_%02d_%02d_%02d_%02d.bmp", t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec );
  fcon = fopen(tmp, "wb");

  deserializedImage = calloc((convolutionWH[0]*3+BMP_PADDING(convolutionWH[0]))*convolutionWH[1], sizeof(uint8_t));
  r = deserializeBitmap(convolutionWH, 24, pConvolution, deserializedImage);

  bmphdr.fhdr.total_size = sizeof(BMPHdr) + (convolutionWH[0]*3+BMP_PADDING(convolutionWH[0]))*convolutionWH[1];
  bmphdr.dhdr.bitcount = 24;
  bmphdr.dhdr.planes = 1;
  bmphdr.dhdr.width = convolutionWH[0];
  bmphdr.dhdr.height = convolutionWH[1];

  fwrite(&bmphdr, 54, 1, fcon);
  fwrite(deserializedImage, r, 1, fcon);
  free(deserializedImage);
  fclose(fcon);



  pPooling = calloc(convolutionWH[0]*convolutionWH[1]*3, sizeof(uint8_t));
  maxpooling(pConvolution, convolutionWH, stride, 'R', pPooling, poolingWH);
  maxpooling(pConvolution, convolutionWH, stride, 'G', pPooling, poolingWH);
  maxpooling(pConvolution, convolutionWH, stride, 'B', pPooling, poolingWH);


  sprintf(tmp, "joker_a0-pooling_%02d_%02d_%02d_%02d_%02d.bmp", t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec );
  fpool = fopen(tmp, "wb");

  deserializedImage = calloc((poolingWH[0]*3+BMP_PADDING(poolingWH[0]))*poolingWH[1], sizeof(uint8_t));
  r = deserializeBitmap(poolingWH, 24, pPooling, deserializedImage);

  bmphdr.fhdr.total_size = sizeof(BMPHdr) + (poolingWH[0]*3+BMP_PADDING(poolingWH[0]))*poolingWH[1];
  bmphdr.dhdr.bitcount = 24;
  bmphdr.dhdr.planes = 1;
  bmphdr.dhdr.width = poolingWH[0];
  bmphdr.dhdr.height = poolingWH[1];

  fwrite(&bmphdr, 54, 1, fpool);
  fwrite(deserializedImage, r, 1, fpool);
  fclose(fpool);


  free(pConvolution);


  tt = time(0);
  t = localtime(&tt);


  size_with_padding = serializePaddingSize(&bmphdr, 1);
  serializedImage = calloc(size_with_padding, sizeof(uint8_t));

  r = serializePadding(&bmphdr, 1, deserializedImage, serializedImage);

  serializedWH[0] = bmphdr.dhdr.width;
  serializedWH[1] = bmphdr.dhdr.height;


  pConvolution = calloc(bmphdr.fhdr.total_size - sizeof(BMPHdr), sizeof(uint8_t));
  r = convolutions(serializedImage, serializedWH, 1, stride, filter[RED],  filterWH, 'R', pConvolution, convolutionWH);
  r = convolutions(serializedImage, serializedWH, 1, stride, filter[GREEN],filterWH, 'G', pConvolution, convolutionWH);
  r = convolutions(serializedImage, serializedWH, 1, stride, filter[BLUE], filterWH, 'B', pConvolution, convolutionWH);
  free(serializedImage);

  sprintf(tmp, "joker_a1-convolution_%02d_%02d_%02d_%02d_%02d.bmp", t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec );
  fcon = fopen(tmp, "wb");

  free(deserializedImage);
  deserializedImage = calloc((convolutionWH[0]*3+BMP_PADDING(convolutionWH[0]))*convolutionWH[1], sizeof(uint8_t));
  r = deserializeBitmap(convolutionWH, 24, pConvolution, deserializedImage);

  bmphdr.fhdr.total_size = sizeof(BMPHdr) + (convolutionWH[0]*3+BMP_PADDING(convolutionWH[0]))*convolutionWH[1];
  bmphdr.dhdr.bitcount = 24;
  bmphdr.dhdr.planes = 1;
  bmphdr.dhdr.width = convolutionWH[0];
  bmphdr.dhdr.height = convolutionWH[1];

  fwrite(&bmphdr, 54, 1, fcon);
  fwrite(deserializedImage, r, 1, fcon);
  free(deserializedImage);
  fclose(fcon);




  free(pPooling);

  pPooling = calloc(convolutionWH[0]*convolutionWH[1]*3, sizeof(uint8_t));
  maxpooling(pConvolution, convolutionWH, stride, 'R', pPooling, poolingWH);
  maxpooling(pConvolution, convolutionWH, stride, 'G', pPooling, poolingWH);
  maxpooling(pConvolution, convolutionWH, stride, 'B', pPooling, poolingWH);


  sprintf(tmp, "joker_a1-pooling_%02d_%02d_%02d_%02d_%02d.bmp", t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec );
  fpool = fopen(tmp, "wb");

  deserializedImage = calloc((poolingWH[0]*3+BMP_PADDING(poolingWH[0]))*poolingWH[1], sizeof(uint8_t));
  r = deserializeBitmap(poolingWH, 24, pPooling, deserializedImage);

  bmphdr.fhdr.total_size = sizeof(BMPHdr) + (poolingWH[0]*3+BMP_PADDING(poolingWH[0]))*poolingWH[1];
  bmphdr.dhdr.bitcount = 24;
  bmphdr.dhdr.planes = 1;
  bmphdr.dhdr.width = poolingWH[0];
  bmphdr.dhdr.height = poolingWH[1];

  fwrite(&bmphdr, 54, 1, fpool);
  fwrite(deserializedImage, r, 1, fpool);
  fclose(fpool);


  free(pConvolution);





  tt = time(0);
  t = localtime(&tt);


  size_with_padding = serializePaddingSize(&bmphdr, 1);
  serializedImage = calloc(size_with_padding, sizeof(uint8_t));

  r = serializePadding(&bmphdr, 1, deserializedImage, serializedImage);

  serializedWH[0] = bmphdr.dhdr.width;
  serializedWH[1] = bmphdr.dhdr.height;


  pConvolution = calloc(bmphdr.fhdr.total_size - sizeof(BMPHdr), sizeof(uint8_t));
  r = convolutions(serializedImage, serializedWH, 1, stride, filter[RED],  filterWH, 'R', pConvolution, convolutionWH);
  r = convolutions(serializedImage, serializedWH, 1, stride, filter[GREEN],filterWH, 'G', pConvolution, convolutionWH);
  r = convolutions(serializedImage, serializedWH, 1, stride, filter[BLUE], filterWH, 'B', pConvolution, convolutionWH);
  free(serializedImage);

  sprintf(tmp, "joker_a2-convolution_%02d_%02d_%02d_%02d_%02d.bmp", t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec );
  fcon = fopen(tmp, "wb");

  free(deserializedImage);
  deserializedImage = calloc((convolutionWH[0]*3+BMP_PADDING(convolutionWH[0]))*convolutionWH[1], sizeof(uint8_t));
  r = deserializeBitmap(convolutionWH, 24, pConvolution, deserializedImage);

  bmphdr.fhdr.total_size = sizeof(BMPHdr) + (convolutionWH[0]*3+BMP_PADDING(convolutionWH[0]))*convolutionWH[1];
  bmphdr.dhdr.bitcount = 24;
  bmphdr.dhdr.planes = 1;
  bmphdr.dhdr.width = convolutionWH[0];
  bmphdr.dhdr.height = convolutionWH[1];

  fwrite(&bmphdr, 54, 1, fcon);
  fwrite(deserializedImage, r, 1, fcon);
  free(deserializedImage);
  fclose(fcon);




  free(pPooling);

  pPooling = calloc(convolutionWH[0]*convolutionWH[1]*3, sizeof(uint8_t));
  maxpooling(pConvolution, convolutionWH, stride, 'R', pPooling, poolingWH);
  maxpooling(pConvolution, convolutionWH, stride, 'G', pPooling, poolingWH);
  maxpooling(pConvolution, convolutionWH, stride, 'B', pPooling, poolingWH);


  sprintf(tmp, "joker_a2-pooling_%02d_%02d_%02d_%02d_%02d.bmp", t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec );
  fpool = fopen(tmp, "wb");

  deserializedImage = calloc((poolingWH[0]*3+BMP_PADDING(poolingWH[0]))*poolingWH[1], sizeof(uint8_t));
  r = deserializeBitmap(poolingWH, 24, pPooling, deserializedImage);

  bmphdr.fhdr.total_size = sizeof(BMPHdr) + (poolingWH[0]*3+BMP_PADDING(poolingWH[0]))*poolingWH[1];
  bmphdr.dhdr.bitcount = 24;
  bmphdr.dhdr.planes = 1;
  bmphdr.dhdr.width = poolingWH[0];
  bmphdr.dhdr.height = poolingWH[1];

  fwrite(&bmphdr, 54, 1, fpool);
  fwrite(deserializedImage, r, 1, fpool);
  fclose(fpool);


  free(pConvolution);





  tt = time(0);
  t = localtime(&tt);


  size_with_padding = serializePaddingSize(&bmphdr, 1);
  serializedImage = calloc(size_with_padding, sizeof(uint8_t));

  r = serializePadding(&bmphdr, 1, deserializedImage, serializedImage);

  serializedWH[0] = bmphdr.dhdr.width;
  serializedWH[1] = bmphdr.dhdr.height;


  pConvolution = calloc(bmphdr.fhdr.total_size - sizeof(BMPHdr), sizeof(uint8_t));
  r = convolutions(serializedImage, serializedWH, 1, stride, filter[RED],  filterWH, 'R', pConvolution, convolutionWH);
  r = convolutions(serializedImage, serializedWH, 1, stride, filter[GREEN],filterWH, 'G', pConvolution, convolutionWH);
  r = convolutions(serializedImage, serializedWH, 1, stride, filter[BLUE], filterWH, 'B', pConvolution, convolutionWH);
  free(serializedImage);

  sprintf(tmp, "joker_a3-convolution_%02d_%02d_%02d_%02d_%02d.bmp", t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec );
  fcon = fopen(tmp, "wb");

  free(deserializedImage);
  deserializedImage = calloc((convolutionWH[0]*3+BMP_PADDING(convolutionWH[0]))*convolutionWH[1], sizeof(uint8_t));
  r = deserializeBitmap(convolutionWH, 24, pConvolution, deserializedImage);

  bmphdr.fhdr.total_size = sizeof(BMPHdr) + (convolutionWH[0]*3+BMP_PADDING(convolutionWH[0]))*convolutionWH[1];
  bmphdr.dhdr.bitcount = 24;
  bmphdr.dhdr.planes = 1;
  bmphdr.dhdr.width = convolutionWH[0];
  bmphdr.dhdr.height = convolutionWH[1];

  fwrite(&bmphdr, 54, 1, fcon);
  fwrite(deserializedImage, r, 1, fcon);
  free(deserializedImage);
  fclose(fcon);




  free(pPooling);

  pPooling = calloc(convolutionWH[0]*convolutionWH[1]*3, sizeof(uint8_t));
  maxpooling(pConvolution, convolutionWH, stride, 'R', pPooling, poolingWH);
  maxpooling(pConvolution, convolutionWH, stride, 'G', pPooling, poolingWH);
  maxpooling(pConvolution, convolutionWH, stride, 'B', pPooling, poolingWH);


  sprintf(tmp, "joker_a3-pooling_%02d_%02d_%02d_%02d_%02d.bmp", t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec );
  fpool = fopen(tmp, "wb");

  deserializedImage = calloc((poolingWH[0]*3+BMP_PADDING(poolingWH[0]))*poolingWH[1], sizeof(uint8_t));
  r = deserializeBitmap(poolingWH, 24, pPooling, deserializedImage);

  bmphdr.fhdr.total_size = sizeof(BMPHdr) + (poolingWH[0]*3+BMP_PADDING(poolingWH[0]))*poolingWH[1];
  bmphdr.dhdr.bitcount = 24;
  bmphdr.dhdr.planes = 1;
  bmphdr.dhdr.width = poolingWH[0];
  bmphdr.dhdr.height = poolingWH[1];

  fwrite(&bmphdr, 54, 1, fpool);
  fwrite(deserializedImage, r, 1, fpool);
  fclose(fpool);


  free(pConvolution);




  tt = time(0);
  t = localtime(&tt);


  size_with_padding = serializePaddingSize(&bmphdr, 1);
  serializedImage = calloc(size_with_padding, sizeof(uint8_t));

  r = serializePadding(&bmphdr, 1, deserializedImage, serializedImage);

  serializedWH[0] = bmphdr.dhdr.width;
  serializedWH[1] = bmphdr.dhdr.height;


  pConvolution = calloc(bmphdr.fhdr.total_size - sizeof(BMPHdr), sizeof(uint8_t));
  r = convolutions(serializedImage, serializedWH, 1, stride, filter[RED],  filterWH, 'R', pConvolution, convolutionWH);
  r = convolutions(serializedImage, serializedWH, 1, stride, filter[GREEN],filterWH, 'G', pConvolution, convolutionWH);
  r = convolutions(serializedImage, serializedWH, 1, stride, filter[BLUE], filterWH, 'B', pConvolution, convolutionWH);
  free(serializedImage);

  sprintf(tmp, "joker_a4-convolution_%02d_%02d_%02d_%02d_%02d.bmp", t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec );
  fcon = fopen(tmp, "wb");

  free(deserializedImage);
  deserializedImage = calloc((convolutionWH[0]*3+BMP_PADDING(convolutionWH[0]))*convolutionWH[1], sizeof(uint8_t));
  r = deserializeBitmap(convolutionWH, 24, pConvolution, deserializedImage);

  bmphdr.fhdr.total_size = sizeof(BMPHdr) + (convolutionWH[0]*3+BMP_PADDING(convolutionWH[0]))*convolutionWH[1];
  bmphdr.dhdr.bitcount = 24;
  bmphdr.dhdr.planes = 1;
  bmphdr.dhdr.width = convolutionWH[0];
  bmphdr.dhdr.height = convolutionWH[1];

  fwrite(&bmphdr, 54, 1, fcon);
  fwrite(deserializedImage, r, 1, fcon);
  free(deserializedImage);
  fclose(fcon);




  free(pPooling);

  pPooling = calloc(convolutionWH[0]*convolutionWH[1]*3, sizeof(uint8_t));
  maxpooling(pConvolution, convolutionWH, stride, 'R', pPooling, poolingWH);
  maxpooling(pConvolution, convolutionWH, stride, 'G', pPooling, poolingWH);
  maxpooling(pConvolution, convolutionWH, stride, 'B', pPooling, poolingWH);


  sprintf(tmp, "joker_a4-pooling_%02d_%02d_%02d_%02d_%02d.bmp", t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec );
  fpool = fopen(tmp, "wb");

  deserializedImage = calloc((poolingWH[0]*3+BMP_PADDING(poolingWH[0]))*poolingWH[1], sizeof(uint8_t));
  r = deserializeBitmap(poolingWH, 24, pPooling, deserializedImage);

  bmphdr.fhdr.total_size = sizeof(BMPHdr) + (poolingWH[0]*3+BMP_PADDING(poolingWH[0]))*poolingWH[1];
  bmphdr.dhdr.bitcount = 24;
  bmphdr.dhdr.planes = 1;
  bmphdr.dhdr.width = poolingWH[0];
  bmphdr.dhdr.height = poolingWH[1];

  fwrite(&bmphdr, 54, 1, fpool);
  fwrite(deserializedImage, r, 1, fpool);
  fclose(fpool);


  free(pConvolution);











  tt = time(0);
  t = localtime(&tt);


  size_with_padding = serializePaddingSize(&bmphdr, 1);
  serializedImage = calloc(size_with_padding, sizeof(uint8_t));

  r = serializePadding(&bmphdr, 1, deserializedImage, serializedImage);

  serializedWH[0] = bmphdr.dhdr.width;
  serializedWH[1] = bmphdr.dhdr.height;


  pConvolution = calloc(bmphdr.fhdr.total_size - sizeof(BMPHdr), sizeof(uint8_t));
  r = convolutions(serializedImage, serializedWH, 1, stride, filter[RED],  filterWH, 'R', pConvolution, convolutionWH);
  r = convolutions(serializedImage, serializedWH, 1, stride, filter[GREEN],filterWH, 'G', pConvolution, convolutionWH);
  r = convolutions(serializedImage, serializedWH, 1, stride, filter[BLUE], filterWH, 'B', pConvolution, convolutionWH);
  free(serializedImage);

  sprintf(tmp, "joker_a5-convolution_%02d_%02d_%02d_%02d_%02d.bmp", t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec );
  fcon = fopen(tmp, "wb");

  free(deserializedImage);
  deserializedImage = calloc((convolutionWH[0]*3+BMP_PADDING(convolutionWH[0]))*convolutionWH[1], sizeof(uint8_t));
  r = deserializeBitmap(convolutionWH, 24, pConvolution, deserializedImage);

  bmphdr.fhdr.total_size = sizeof(BMPHdr) + (convolutionWH[0]*3+BMP_PADDING(convolutionWH[0]))*convolutionWH[1];
  bmphdr.dhdr.bitcount = 24;
  bmphdr.dhdr.planes = 1;
  bmphdr.dhdr.width = convolutionWH[0];
  bmphdr.dhdr.height = convolutionWH[1];

  fwrite(&bmphdr, 54, 1, fcon);
  fwrite(deserializedImage, r, 1, fcon);
  free(deserializedImage);
  fclose(fcon);




  free(pPooling);

  pPooling = calloc(convolutionWH[0]*convolutionWH[1]*3, sizeof(uint8_t));
  maxpooling(pConvolution, convolutionWH, stride, 'R', pPooling, poolingWH);
  maxpooling(pConvolution, convolutionWH, stride, 'G', pPooling, poolingWH);
  maxpooling(pConvolution, convolutionWH, stride, 'B', pPooling, poolingWH);


  sprintf(tmp, "joker_a5-pooling_%02d_%02d_%02d_%02d_%02d.bmp", t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec );
  fpool = fopen(tmp, "wb");

  deserializedImage = calloc((poolingWH[0]*3+BMP_PADDING(poolingWH[0]))*poolingWH[1], sizeof(uint8_t));
  r = deserializeBitmap(poolingWH, 24, pPooling, deserializedImage);

  bmphdr.fhdr.total_size = sizeof(BMPHdr) + (poolingWH[0]*3+BMP_PADDING(poolingWH[0]))*poolingWH[1];
  bmphdr.dhdr.bitcount = 24;
  bmphdr.dhdr.planes = 1;
  bmphdr.dhdr.width = poolingWH[0];
  bmphdr.dhdr.height = poolingWH[1];

  fwrite(&bmphdr, 54, 1, fpool);
  fwrite(deserializedImage, r, 1, fpool);
  fclose(fpool);


  free(pConvolution);






















  tt = time(0);
  t = localtime(&tt);


  size_with_padding = serializePaddingSize(&bmphdr, 1);
  serializedImage = calloc(size_with_padding, sizeof(uint8_t));

  r = serializePadding(&bmphdr, 1, deserializedImage, serializedImage);

  serializedWH[0] = bmphdr.dhdr.width;
  serializedWH[1] = bmphdr.dhdr.height;


  pConvolution = calloc(bmphdr.fhdr.total_size - sizeof(BMPHdr), sizeof(uint8_t));
  r = convolutions(serializedImage, serializedWH, 1, stride, filter[RED],  filterWH, 'R', pConvolution, convolutionWH);
  r = convolutions(serializedImage, serializedWH, 1, stride, filter[GREEN],filterWH, 'G', pConvolution, convolutionWH);
  r = convolutions(serializedImage, serializedWH, 1, stride, filter[BLUE], filterWH, 'B', pConvolution, convolutionWH);
  free(serializedImage);

  sprintf(tmp, "joker_a6-convolution_%02d_%02d_%02d_%02d_%02d.bmp", t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec );
  fcon = fopen(tmp, "wb");

  free(deserializedImage);
  deserializedImage = calloc((convolutionWH[0]*3+BMP_PADDING(convolutionWH[0]))*convolutionWH[1], sizeof(uint8_t));
  r = deserializeBitmap(convolutionWH, 24, pConvolution, deserializedImage);

  bmphdr.fhdr.total_size = sizeof(BMPHdr) + (convolutionWH[0]*3+BMP_PADDING(convolutionWH[0]))*convolutionWH[1];
  bmphdr.dhdr.bitcount = 24;
  bmphdr.dhdr.planes = 1;
  bmphdr.dhdr.width = convolutionWH[0];
  bmphdr.dhdr.height = convolutionWH[1];

  fwrite(&bmphdr, 54, 1, fcon);
  fwrite(deserializedImage, r, 1, fcon);
  free(deserializedImage);
  fclose(fcon);




  free(pPooling);

  pPooling = calloc(convolutionWH[0]*convolutionWH[1]*3, sizeof(uint8_t));
  maxpooling(pConvolution, convolutionWH, stride, 'R', pPooling, poolingWH);
  maxpooling(pConvolution, convolutionWH, stride, 'G', pPooling, poolingWH);
  maxpooling(pConvolution, convolutionWH, stride, 'B', pPooling, poolingWH);


  sprintf(tmp, "joker_a6-pooling_%02d_%02d_%02d_%02d_%02d.bmp", t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec );
  fpool = fopen(tmp, "wb");

  deserializedImage = calloc((poolingWH[0]*3+BMP_PADDING(poolingWH[0]))*poolingWH[1], sizeof(uint8_t));
  r = deserializeBitmap(poolingWH, 24, pPooling, deserializedImage);

  bmphdr.fhdr.total_size = sizeof(BMPHdr) + (poolingWH[0]*3+BMP_PADDING(poolingWH[0]))*poolingWH[1];
  bmphdr.dhdr.bitcount = 24;
  bmphdr.dhdr.planes = 1;
  bmphdr.dhdr.width = poolingWH[0];
  bmphdr.dhdr.height = poolingWH[1];

  fwrite(&bmphdr, 54, 1, fpool);
  fwrite(deserializedImage, r, 1, fpool);
  fclose(fpool);


  free(pConvolution);





  tt = time(0);
  t = localtime(&tt);


  size_with_padding = serializePaddingSize(&bmphdr, 1);
  serializedImage = calloc(size_with_padding, sizeof(uint8_t));

  r = serializePadding(&bmphdr, 1, deserializedImage, serializedImage);

  serializedWH[0] = bmphdr.dhdr.width;
  serializedWH[1] = bmphdr.dhdr.height;


  pConvolution = calloc(bmphdr.fhdr.total_size - sizeof(BMPHdr), sizeof(uint8_t));
  r = convolutions(serializedImage, serializedWH, 1, stride, filter[RED],  filterWH, 'R', pConvolution, convolutionWH);
  r = convolutions(serializedImage, serializedWH, 1, stride, filter[GREEN],filterWH, 'G', pConvolution, convolutionWH);
  r = convolutions(serializedImage, serializedWH, 1, stride, filter[BLUE], filterWH, 'B', pConvolution, convolutionWH);
  free(serializedImage);

  sprintf(tmp, "joker_a7-convolution_%02d_%02d_%02d_%02d_%02d.bmp", t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec );
  fcon = fopen(tmp, "wb");

  free(deserializedImage);
  deserializedImage = calloc((convolutionWH[0]*3+BMP_PADDING(convolutionWH[0]))*convolutionWH[1], sizeof(uint8_t));
  r = deserializeBitmap(convolutionWH, 24, pConvolution, deserializedImage);

  bmphdr.fhdr.total_size = sizeof(BMPHdr) + (convolutionWH[0]*3+BMP_PADDING(convolutionWH[0]))*convolutionWH[1];
  bmphdr.dhdr.bitcount = 24;
  bmphdr.dhdr.planes = 1;
  bmphdr.dhdr.width = convolutionWH[0];
  bmphdr.dhdr.height = convolutionWH[1];

  fwrite(&bmphdr, 54, 1, fcon);
  fwrite(deserializedImage, r, 1, fcon);
  free(deserializedImage);
  fclose(fcon);




  free(pPooling);

  pPooling = calloc(convolutionWH[0]*convolutionWH[1]*3, sizeof(uint8_t));
  maxpooling(pConvolution, convolutionWH, stride, 'R', pPooling, poolingWH);
  maxpooling(pConvolution, convolutionWH, stride, 'G', pPooling, poolingWH);
  maxpooling(pConvolution, convolutionWH, stride, 'B', pPooling, poolingWH);


  sprintf(tmp, "joker_a7-pooling_%02d_%02d_%02d_%02d_%02d.bmp", t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec );
  fpool = fopen(tmp, "wb");

  deserializedImage = calloc((poolingWH[0]*3+BMP_PADDING(poolingWH[0]))*poolingWH[1], sizeof(uint8_t));
  r = deserializeBitmap(poolingWH, 24, pPooling, deserializedImage);

  bmphdr.fhdr.total_size = sizeof(BMPHdr) + (poolingWH[0]*3+BMP_PADDING(poolingWH[0]))*poolingWH[1];
  bmphdr.dhdr.bitcount = 24;
  bmphdr.dhdr.planes = 1;
  bmphdr.dhdr.width = poolingWH[0];
  bmphdr.dhdr.height = poolingWH[1];

  fwrite(&bmphdr, 54, 1, fpool);
  fwrite(deserializedImage, r, 1, fpool);
  fclose(fpool);


  free(pConvolution);










  tt = time(0);
  t = localtime(&tt);


  size_with_padding = serializePaddingSize(&bmphdr, 1);
  serializedImage = calloc(size_with_padding, sizeof(uint8_t));

  r = serializePadding(&bmphdr, 1, deserializedImage, serializedImage);

  serializedWH[0] = bmphdr.dhdr.width;
  serializedWH[1] = bmphdr.dhdr.height;


  pConvolution = calloc(bmphdr.fhdr.total_size - sizeof(BMPHdr), sizeof(uint8_t));
  r = convolutions(serializedImage, serializedWH, 1, stride, filter[RED],  filterWH, 'R', pConvolution, convolutionWH);
  r = convolutions(serializedImage, serializedWH, 1, stride, filter[GREEN],filterWH, 'G', pConvolution, convolutionWH);
  r = convolutions(serializedImage, serializedWH, 1, stride, filter[BLUE], filterWH, 'B', pConvolution, convolutionWH);
  free(serializedImage);

  sprintf(tmp, "joker_a8-convolution_%02d_%02d_%02d_%02d_%02d.bmp", t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec );
  fcon = fopen(tmp, "wb");

  free(deserializedImage);
  deserializedImage = calloc((convolutionWH[0]*3+BMP_PADDING(convolutionWH[0]))*convolutionWH[1], sizeof(uint8_t));
  r = deserializeBitmap(convolutionWH, 24, pConvolution, deserializedImage);

  bmphdr.fhdr.total_size = sizeof(BMPHdr) + (convolutionWH[0]*3+BMP_PADDING(convolutionWH[0]))*convolutionWH[1];
  bmphdr.dhdr.bitcount = 24;
  bmphdr.dhdr.planes = 1;
  bmphdr.dhdr.width = convolutionWH[0];
  bmphdr.dhdr.height = convolutionWH[1];

  fwrite(&bmphdr, 54, 1, fcon);
  fwrite(deserializedImage, r, 1, fcon);
  free(deserializedImage);
  fclose(fcon);




  free(pPooling);

  pPooling = calloc(convolutionWH[0]*convolutionWH[1]*3, sizeof(uint8_t));
  maxpooling(pConvolution, convolutionWH, stride, 'R', pPooling, poolingWH);
  maxpooling(pConvolution, convolutionWH, stride, 'G', pPooling, poolingWH);
  maxpooling(pConvolution, convolutionWH, stride, 'B', pPooling, poolingWH);


  sprintf(tmp, "joker_a8-pooling_%02d_%02d_%02d_%02d_%02d.bmp", t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec );
  fpool = fopen(tmp, "wb");

  deserializedImage = calloc((poolingWH[0]*3+BMP_PADDING(poolingWH[0]))*poolingWH[1], sizeof(uint8_t));
  r = deserializeBitmap(poolingWH, 24, pPooling, deserializedImage);

  bmphdr.fhdr.total_size = sizeof(BMPHdr) + (poolingWH[0]*3+BMP_PADDING(poolingWH[0]))*poolingWH[1];
  bmphdr.dhdr.bitcount = 24;
  bmphdr.dhdr.planes = 1;
  bmphdr.dhdr.width = poolingWH[0];
  bmphdr.dhdr.height = poolingWH[1];

  fwrite(&bmphdr, 54, 1, fpool);
  fwrite(deserializedImage, r, 1, fpool);
  fclose(fpool);


  free(pConvolution);








  tt = time(0);
  t = localtime(&tt);


  size_with_padding = serializePaddingSize(&bmphdr, 1);
  serializedImage = calloc(size_with_padding, sizeof(uint8_t));

  r = serializePadding(&bmphdr, 1, deserializedImage, serializedImage);

  serializedWH[0] = bmphdr.dhdr.width;
  serializedWH[1] = bmphdr.dhdr.height;


  pConvolution = calloc(bmphdr.fhdr.total_size - sizeof(BMPHdr), sizeof(uint8_t));
  r = convolutions(serializedImage, serializedWH, 1, stride, filter[RED],  filterWH, 'R', pConvolution, convolutionWH);
  r = convolutions(serializedImage, serializedWH, 1, stride, filter[GREEN],filterWH, 'G', pConvolution, convolutionWH);
  r = convolutions(serializedImage, serializedWH, 1, stride, filter[BLUE], filterWH, 'B', pConvolution, convolutionWH);
  free(serializedImage);

  sprintf(tmp, "joker_a9-convolution_%02d_%02d_%02d_%02d_%02d.bmp", t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec );
  fcon = fopen(tmp, "wb");

  free(deserializedImage);
  deserializedImage = calloc((convolutionWH[0]*3+BMP_PADDING(convolutionWH[0]))*convolutionWH[1], sizeof(uint8_t));
  r = deserializeBitmap(convolutionWH, 24, pConvolution, deserializedImage);

  bmphdr.fhdr.total_size = sizeof(BMPHdr) + (convolutionWH[0]*3+BMP_PADDING(convolutionWH[0]))*convolutionWH[1];
  bmphdr.dhdr.bitcount = 24;
  bmphdr.dhdr.planes = 1;
  bmphdr.dhdr.width = convolutionWH[0];
  bmphdr.dhdr.height = convolutionWH[1];

  fwrite(&bmphdr, 54, 1, fcon);
  fwrite(deserializedImage, r, 1, fcon);
  free(deserializedImage);
  fclose(fcon);




  free(pPooling);

  pPooling = calloc(convolutionWH[0]*convolutionWH[1]*3, sizeof(uint8_t));
  maxpooling(pConvolution, convolutionWH, stride, 'R', pPooling, poolingWH);
  maxpooling(pConvolution, convolutionWH, stride, 'G', pPooling, poolingWH);
  maxpooling(pConvolution, convolutionWH, stride, 'B', pPooling, poolingWH);


  sprintf(tmp, "joker_a9-pooling_%02d_%02d_%02d_%02d_%02d.bmp", t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec );
  fpool = fopen(tmp, "wb");

  deserializedImage = calloc((poolingWH[0]*3+BMP_PADDING(poolingWH[0]))*poolingWH[1], sizeof(uint8_t));
  r = deserializeBitmap(poolingWH, 24, pPooling, deserializedImage);

  bmphdr.fhdr.total_size = sizeof(BMPHdr) + (poolingWH[0]*3+BMP_PADDING(poolingWH[0]))*poolingWH[1];
  bmphdr.dhdr.bitcount = 24;
  bmphdr.dhdr.planes = 1;
  bmphdr.dhdr.width = poolingWH[0];
  bmphdr.dhdr.height = poolingWH[1];

  fwrite(&bmphdr, 54, 1, fpool);
  fwrite(deserializedImage, r, 1, fpool);
  fclose(fpool);


  free(pConvolution);






























  free(filter[RED]);
  free(filter[GREEN]);
  free(filter[BLUE]);
  free(pPooling);
  free(rawBMP);
  fclose(fp);
}



#endif




#if 0
void main()
{
  int32_t w = 0;
  int32_t h = 0;
  FILE* fp = fopen("postion.txt", "w");

  for ( h=0 ; h<15; h++ )
  {
    for ( w=0 ; w<7*3 ; w++ )
    {
      if ( w && w%3==0 ) fprintf(fp, "  ");
      fprintf(fp, "%4d ", w+h*21);
    }
    fprintf(fp,"\r\n");
  }
  
  fclose(fp);

}
#endif










#if 0
void main()
{
  int32_t i = 0;
  long double* filter[3] = {0};
  uint8_t* p = 0;
  uint8_t* padRaw = 0;
  uint8_t* fimg = 0;
  uint8_t* rawBMP = 0;
  uint8_t* poolImg = 0;
  int32_t fsz[2] = {0};
  int32_t pwh[2] = {0};

  int32_t sz = 0;
  int32_t qsz = 0;
  int32_t r = 0;
  int8_t  tmp[32] = {0};
  int32_t wh[2] = {0};
  int32_t fwh[2] = {0};
  BMPHdr  bmphdr = {0};
  FILE* fp = fopen("joker.bmp", "rb");
  //FILE* fp = fopen("..\\imgs\\sample.bmp", "rb");

  srand(time(0));

  r = fread(&bmphdr, sizeof(int8_t), sizeof(BMPHdr), fp);

  p = calloc(bmphdr.fhdr.total_size - sizeof(BMPHdr), sizeof(uint8_t));
  fimg = calloc(bmphdr.fhdr.total_size - sizeof(BMPHdr), sizeof(uint8_t));

  qsz = serializePaddingSize(&bmphdr, 1);
  padRaw = calloc(qsz, sizeof(uint8_t));

  r = fread(p, sizeof(int8_t), bmphdr.fhdr.total_size - sizeof(BMPHdr), fp);

  r = serializePadding(&bmphdr, 1, p, padRaw);

  wh[0] = 3;
  wh[1] = 3;
  createFloatFilter(wh, &filter[RED]);
  createFloatFilter(wh, &filter[GREEN]);
  createFloatFilter(wh, &filter[BLUE]);

  wh[0] = bmphdr.dhdr.width;
  wh[1] = bmphdr.dhdr.height;
  fwh[0] = 3;
  fwh[1] = 3;
  r = convolutions(padRaw, wh, 1, 1, filter[RED],  fwh, 'R', fimg, fsz);
  r = convolutions(padRaw, wh, 1, 1, filter[GREEN],fwh, 'G', fimg, fsz);
  r = convolutions(padRaw, wh, 1, 1, filter[BLUE], fwh, 'B', fimg, fsz);



  poolImg = calloc(fsz[0]*fsz[1]*3, sizeof(uint8_t));


  maxpooling(fimg, fsz, 1, fwh, 'R', poolImg, pwh);
  maxpooling(fimg, fsz, 1, fwh, 'G', poolImg, pwh);
  maxpooling(fimg, fsz, 1, fwh, 'B', poolImg, pwh);


  {
    uint8_t* b = 0;
    int32_t wh[2] = {0};
    FILE* ft = fopen("joker+conv+1.bmp", "wb");

    wh[0] = bmphdr.dhdr.width;
    wh[1] = bmphdr.dhdr.height;
    b = calloc(bmphdr.fhdr.total_size, sizeof(uint32_t));

    rawBMP = calloc((fsz[0]*3+BMP_PADDING(fsz[0]))*fsz[1], sizeof(uint8_t));
    r = deserializeBitmap(fsz, 24, fimg, rawBMP);

    fwrite(&bmphdr, 54, 1, ft);
    fwrite(rawBMP, r, 1, ft);
    free(b);
    fclose(ft);

  }

  {
    uint8_t* b = 0;
    int32_t wh[2] = {0};
    FILE* ft = fopen("joker+pool+1.bmp", "wb");


    bmphdr.dhdr.width = pwh[0];
    bmphdr.dhdr.height = pwh[1];
    b = calloc(bmphdr.fhdr.total_size, sizeof(uint32_t));

    rawBMP = calloc((fsz[0]*3+BMP_PADDING(fsz[0]))*fsz[1], sizeof(uint8_t));
    r = deserializeBitmap(pwh, 24, poolImg, rawBMP);

    fwrite(&bmphdr, 54, 1, ft);
    fwrite(rawBMP, r, 1, ft);
    free(b);
    fclose(ft);

  }



  free(filter[RED]);
  free(filter[GREEN]);
  free(filter[BLUE]);
  free(padRaw);
  free(p);
  free(fimg);
  fclose(fp);
}
#endif










































#if 0
void main()
{
  int32_t i = 0;
  long double* filter[3] = {0};
  uint8_t* p = 0;
  uint8_t* padRaw = 0;
  uint8_t* fimg = 0;
  uint8_t* rawBMP = 0;
  int32_t fsz[2] = {0};

  int32_t sz = 0;
  int32_t qsz = 0;
  int32_t r = 0;
  int8_t  tmp[32] = {0};
  int32_t wh[2] = {0};
  int32_t fwh[2] = {0};
  BMPHdr  bmphdr = {0};
  FILE* fp = fopen("joker.bmp", "rb");
  //FILE* fp = fopen("..\\imgs\\sample.bmp", "rb");

  srand(time(0));

  r = fread(&bmphdr, sizeof(int8_t), sizeof(BMPHdr), fp);

  p = calloc(bmphdr.fhdr.total_size - sizeof(BMPHdr), sizeof(uint8_t));
  fimg = calloc(bmphdr.fhdr.total_size - sizeof(BMPHdr), sizeof(uint8_t));

  qsz = serializePaddingSize(&bmphdr, 1);
  padRaw = calloc(qsz, sizeof(uint8_t));

  r = fread(p, sizeof(int8_t), bmphdr.fhdr.total_size - sizeof(BMPHdr), fp);

  r = serializePadding(&bmphdr, 1, p, padRaw);

  wh[0] = 3;
  wh[1] = 3;
  createFloatFilter(wh, &filter[RED]);
  createFloatFilter(wh, &filter[GREEN]);
  createFloatFilter(wh, &filter[BLUE]);

  wh[0] = bmphdr.dhdr.width;
  wh[1] = bmphdr.dhdr.height;
  fwh[0] = 3;
  fwh[1] = 3;
  r = convolutions(padRaw, wh, 1, 1, filter[RED],  fwh, 'R', fimg, fsz);
  r = convolutions(padRaw, wh, 1, 1, filter[GREEN],fwh, 'G', fimg, fsz);
  r = convolutions(padRaw, wh, 1, 1, filter[BLUE], fwh, 'B', fimg, fsz);


  {
    uint8_t* b = 0;
    int32_t wh[2] = {0};
    FILE* ft = fopen("joker+f77.bmp", "wb");

    wh[0] = bmphdr.dhdr.width;
    wh[1] = bmphdr.dhdr.height;
    b = calloc(bmphdr.fhdr.total_size, sizeof(uint32_t));

    rawBMP = calloc((fsz[0]*3+BMP_PADDING(fsz[0]))*fsz[1], sizeof(uint8_t));
    r = deserializeBitmap(fsz, 24, fimg, rawBMP);

    //r = x__write_raw('f', rawBMP, fsz, bmphdr.dhdr.bitcount, b);


    fwrite(&bmphdr, 54, 1, ft);
    fwrite(rawBMP, r, 1, ft);



    //__TR__;
    //printBuffer(b, r);



    //fwrite(b, sizeof(uint8_t), r, ft);

    free(b);
    fclose(ft);

  }




  free(filter[RED]);
  free(filter[GREEN]);
  free(filter[BLUE]);
  free(padRaw);
  free(p);
  free(fimg);
  fclose(fp);
}

#endif













































#if 0
void main()
{
  int32_t arr[32] = {0};
  int32_t min = 0;

  srand(time(0));
  assign32bit(arr, 32);

  printArray(arr, 32);

  findMIN(arr, 32, &min); 

  printf(" min -> %d \r\n", min);
}
#endif


#if 0
void main()
{
  long double* filter = 0;
  int32_t wh[2] = {3, 3};

  srand(time(0));

  createFloatFilter(wh, &filter);

  //printBuffer(filter, 9*sizeof(long double));
  printFloatFilter(wh, filter);

  free(filter);
}
#endif


#if 0
void main()
{
  int32_t i = 0;
  uint32_t* filter[3] = {0};
  uint8_t* p = 0;
  uint8_t* padRaw = 0;
  uint8_t* fimg = 0;
  uint8_t* rawBMP = 0;
  int32_t fsz[2] = {0};

  int32_t sz = 0;
  int32_t qsz = 0;
  int32_t r = 0;
  int8_t  tmp[32] = {0};
  int32_t wh[2] = {0};
  int32_t fwh[2] = {0};
  BMPHdr  bmphdr = {0};
  FILE* fp = fopen("joker.bmp", "rb");
  //FILE* fp = fopen("..\\imgs\\sample.bmp", "rb");

  srand(time(0));

  r = fread(&bmphdr, sizeof(int8_t), sizeof(BMPHdr), fp);

  p = calloc(bmphdr.fhdr.total_size - sizeof(BMPHdr), sizeof(uint8_t));
  fimg = calloc(bmphdr.fhdr.total_size - sizeof(BMPHdr), sizeof(uint8_t));

  qsz = serializePaddingSize(&bmphdr, 1);
  padRaw = calloc(qsz, sizeof(uint8_t));

  r = fread(p, sizeof(int8_t), bmphdr.fhdr.total_size - sizeof(BMPHdr), fp);

  r = serializePadding(&bmphdr, 1, p, padRaw);

  createFilter("3X3", &filter[RED]);
  createFilter("3X3", &filter[GREEN]);
  createFilter("3X3", &filter[BLUE]);

  wh[0] = bmphdr.dhdr.width;
  wh[1] = bmphdr.dhdr.height;
  fwh[0] = 3;
  fwh[1] = 3;
  r = convolutionProduct(padRaw, wh, 1, 1, filter[RED],  fwh, 'R', fimg, fsz);
  r = convolutionProduct(padRaw, wh, 1, 1, filter[GREEN],fwh, 'G', fimg, fsz);
  r = convolutionProduct(padRaw, wh, 1, 1, filter[BLUE], fwh, 'B', fimg, fsz);


  {
    uint8_t* b = 0;
    int32_t wh[2] = {0};
    FILE* ft = fopen("joker+ff7.bmp", "wb");

    wh[0] = bmphdr.dhdr.width;
    wh[1] = bmphdr.dhdr.height;
    b = calloc(bmphdr.fhdr.total_size, sizeof(uint32_t));

    rawBMP = calloc((fsz[0]*3+BMP_PADDING(fsz[0]))*fsz[1], sizeof(uint8_t));
    r = deserializeBitmap(fsz, 24, fimg, rawBMP);

    //r = x__write_raw('f', rawBMP, fsz, bmphdr.dhdr.bitcount, b);


    fwrite(&bmphdr, 54, 1, ft);
    fwrite(rawBMP, r, 1, ft);



    //__TR__;
    //printBuffer(b, r);



    //fwrite(b, sizeof(uint8_t), r, ft);

    free(b);
    fclose(ft);

  }




  free(filter[RED]);
  free(filter[GREEN]);
  free(filter[BLUE]);
  free(padRaw);
  free(p);
  free(fimg);
  fclose(fp);
}

#endif



#if 0
void main()
{
  int32_t i = 0;
  uint32_t* filter[3] = {0};
  uint8_t* p = 0;
  uint8_t* padRaw = 0;
  uint8_t* fimg = 0;
  uint8_t* rawBMP = 0;
  int32_t fsz[2] = {0};

  int32_t sz = 0;
  int32_t qsz = 0;
  int32_t r = 0;
  int8_t  tmp[32] = {0};
  int32_t wh[2] = {0};
  int32_t fwh[2] = {0};
  BMPHdr  bmphdr = {0};
  FILE* fp = fopen("joker.bmp", "rb");
  //FILE* fp = fopen("..\\imgs\\sample.bmp", "rb");

  srand(time(0));

  r = fread(&bmphdr, sizeof(int8_t), sizeof(BMPHdr), fp);

  p = calloc(bmphdr.fhdr.total_size - sizeof(BMPHdr), sizeof(uint8_t));
  fimg = calloc(bmphdr.fhdr.total_size - sizeof(BMPHdr), sizeof(uint8_t));

  qsz = serializePaddingSize(&bmphdr, 1);
  padRaw = calloc(qsz, sizeof(uint8_t));

  r = fread(p, sizeof(int8_t), bmphdr.fhdr.total_size - sizeof(BMPHdr), fp);

  r = serializePadding(&bmphdr, 1, p, padRaw);

  createFilter("3X3", &filter[RED]);
  createFilter("3X3", &filter[GREEN]);
  createFilter("3X3", &filter[BLUE]);

  wh[0] = bmphdr.dhdr.width;
  wh[1] = bmphdr.dhdr.height;
  fwh[0] = 3;
  fwh[1] = 3;
  r = convolutionProduct(padRaw, wh, 1, 1, filter[RED],  fwh, 'R', fimg, fsz);
  r = convolutionProduct(padRaw, wh, 1, 1, filter[GREEN],fwh, 'G', fimg, fsz);
  r = convolutionProduct(padRaw, wh, 1, 1, filter[BLUE], fwh, 'B', fimg, fsz);


  {
    uint8_t* b = 0;
    int32_t wh[2] = {0};
    FILE* ft = fopen("joker+ff7.bmp", "wb");

    wh[0] = bmphdr.dhdr.width;
    wh[1] = bmphdr.dhdr.height;
    b = calloc(bmphdr.fhdr.total_size, sizeof(uint32_t));

    rawBMP = calloc((fsz[0]*3+BMP_PADDING(fsz[0]))*fsz[1], sizeof(uint8_t));
    r = deserializeBitmap(fsz, 24, fimg, rawBMP);

    //r = x__write_raw('f', rawBMP, fsz, bmphdr.dhdr.bitcount, b);


    fwrite(&bmphdr, 54, 1, ft);
    fwrite(rawBMP, r, 1, ft);



    //__TR__;
    //printBuffer(b, r);



    //fwrite(b, sizeof(uint8_t), r, ft);

    free(b);
    fclose(ft);

  }




  free(filter[RED]);
  free(filter[GREEN]);
  free(filter[BLUE]);
  free(padRaw);
  free(p);
  free(fimg);
  fclose(fp);
}

#endif


#if 0
void main()
{
  int32_t i = 0;
  uint8_t* filter[3] = {0};
  uint8_t* p = 0;
  uint8_t* padRaw = 0;
  uint8_t* fimg = 0;
  uint8_t* rawBMP = 0;
  int32_t fsz[2] = {0};

  int32_t sz = 0;
  int32_t qsz = 0;
  int32_t r = 0;
  int8_t  tmp[32] = {0};
  BMPHdr  bmphdr = {0};
  FILE* fp = fopen("joker.bmp", "rb");
  //FILE* fp = fopen("..\\imgs\\sample.bmp", "rb");

  srand(time(0));

  r = fread(&bmphdr, sizeof(int8_t), sizeof(BMPHdr), fp);

  p = calloc(bmphdr.fhdr.total_size - sizeof(BMPHdr), sizeof(uint8_t));
  fimg = calloc(bmphdr.fhdr.total_size - sizeof(BMPHdr), sizeof(uint8_t));

  qsz = serializePaddingSize(&bmphdr, 1);

  padRaw = calloc(qsz, sizeof(uint8_t));
  r = fread(p, sizeof(int8_t), bmphdr.fhdr.total_size - sizeof(BMPHdr), fp);

  serializePadding(&bmphdr, 1, p, padRaw);

  createFilter("3X3", &filter[RED]);
  createFilter("3X3", &filter[GREEN]);
  createFilter("3X3", &filter[BLUE]);


  #if 0
  i = 0;
  *( filter[RED] + i ) = *( filter[GREEN] + i ) = *( filter[BLUE] + i ) = -1; i++;
  *( filter[RED] + i ) = *( filter[GREEN] + i ) = *( filter[BLUE] + i ) =  0; i++;
  *( filter[RED] + i ) = *( filter[GREEN] + i ) = *( filter[BLUE] + i ) =  1; i++;
  *( filter[RED] + i ) = *( filter[GREEN] + i ) = *( filter[BLUE] + i ) = -2; i++;
  *( filter[RED] + i ) = *( filter[GREEN] + i ) = *( filter[BLUE] + i ) =  0; i++;
  *( filter[RED] + i ) = *( filter[GREEN] + i ) = *( filter[BLUE] + i ) =  2; i++;
  *( filter[RED] + i ) = *( filter[GREEN] + i ) = *( filter[BLUE] + i ) = -1; i++;
  *( filter[RED] + i ) = *( filter[GREEN] + i ) = *( filter[BLUE] + i ) =  0; i++;
  *( filter[RED] + i ) = *( filter[GREEN] + i ) = *( filter[BLUE] + i ) =  1; i++;
  #endif

  //for ( i=0 ; i<9 ; i++ )
  //{
  //  if ( i%2 ) *( filter[RED] + i ) = *( filter[GREEN] + i ) = *( filter[BLUE] + i ) = 0;
  //  else *( filter[RED] + i ) = *( filter[GREEN] + i ) = *( filter[BLUE] + i ) = 1;
  //}


  sprintf(tmp, "%dX%d", bmphdr.dhdr.width, bmphdr.dhdr.height);

  r = convolutionProduct(padRaw, tmp, 1, 1, filter[RED], 'R', "3X3", fimg, fsz);
  r = convolutionProduct(padRaw, tmp, 1, 1, filter[RED], 'G', "3X3", fimg, fsz);
  r = convolutionProduct(padRaw, tmp, 1, 1, filter[RED], 'B', "3X3", fimg, fsz);

  {
    uint8_t* b = 0;
    int32_t wh[2] = {0};
    FILE* ft = fopen("joker+featured.bmp", "wb");

    wh[0] = bmphdr.dhdr.width;
    wh[1] = bmphdr.dhdr.height;
    b = calloc(bmphdr.fhdr.total_size, sizeof(uint32_t));

    rawBMP = calloc((fsz[0]*3+BMP_PADDING(fsz[0]))*fsz[1], sizeof(uint8_t));
    r = deserializeBitmap(fsz, 24, fimg, rawBMP);

    r = __write_raw('f', rawBMP, fsz, bmphdr.dhdr.bitcount, b);

    fwrite(b, sizeof(uint8_t), r, ft);

    free(b);
    fclose(ft);

  }

  free(filter[RED]);
  free(filter[GREEN]);
  free(filter[BLUE]);
  free(padRaw);
  free(p);
  free(fimg);
  fclose(fp);
}
#endif







































#if 0
void main()
{
  uint8_t* p = 0;
  uint8_t* q = 0;
  uint8_t* b = 0;
  int32_t sz = 0;
  int32_t r = 0;
  int32_t wh[2] = {0};
  BMPHdr  bmphdr = {0};

  FILE* fp = fopen("joker.bmp", "rb");

  r = fread(&bmphdr, sizeof(int8_t), sizeof(BMPHdr), fp);
  printf(" sizeof(BMPHdr), read r -> %d \r\n", r);

  p = calloc(bmphdr.fhdr.total_size - sizeof(BMPHdr), sizeof(uint8_t));
  q = calloc(bmphdr.fhdr.total_size                 , sizeof(uint8_t));

  r = fread(p, sizeof(int8_t), bmphdr.fhdr.total_size - sizeof(BMPHdr), fp);
  printf(" bmphdr.fhdr.total_size - sizeof(BMPHdr), read r -> %d \r\n", r);

  //printBuffer(p, r);

  r = serializeBitmap(&bmphdr, p, q);

  //__TR__;
  //printBuffer(q, r);


  wh[0] = bmphdr.dhdr.width;
  wh[1] = bmphdr.dhdr.height;

  b = calloc(bmphdr.fhdr.total_size - sizeof(BMPHdr), sizeof(uint8_t));

  r = deserializeBitmap(wh, 24, q, b);



  {
    uint8_t* _bmp = 0;
    int32_t wh[2] = {0};
    FILE* ft = fopen("joker+revoke.bmp", "wb");

    wh[0] = bmphdr.dhdr.width;
    wh[1] = bmphdr.dhdr.height;
    _bmp = calloc(bmphdr.fhdr.total_size, sizeof(uint32_t));

    r = __write_raw('f', b, wh, bmphdr.dhdr.bitcount, _bmp);

    fwrite(_bmp, sizeof(uint8_t), r, ft);

    free(_bmp);
    fclose(ft);

  }
  {
    uint8_t* _bmp = 0;
    int32_t wh[2] = {0};
    FILE* ft = fopen("joker+rrevoke.bmp", "wb");

    wh[0] = bmphdr.dhdr.width;
    wh[1] = bmphdr.dhdr.height;
    _bmp = calloc(bmphdr.fhdr.total_size, sizeof(uint32_t));

    r = __write_raw('r', b, wh, bmphdr.dhdr.bitcount, _bmp);

    fwrite(_bmp, sizeof(uint8_t), r, ft);

    free(_bmp);
    fclose(ft);

  }


  //__TR__;
  //printBuffer(b, r);

  free(b);
  free(q);
  free(p);
  fclose(fp);
}
#endif

#if 0

void main()
{
  int32_t i = 0;
  uint8_t* filter[3] = {0};
  uint8_t* p = 0;
  uint8_t* q = 0;
  uint8_t* fimg = 0;
  int32_t fsz[2] = {0};

  int32_t sz = 0;
  int32_t qsz = 0;
  int32_t r = 0;
  int8_t  tmp[32] = {0};
  BMPHdr  bmphdr = {0};
  FILE* fp = fopen("joker.bmp", "rb");
  //FILE* fp = fopen("..\\imgs\\sample.bmp", "rb");

  srand(time(0));

  r = fread(&bmphdr, sizeof(int8_t), sizeof(BMPHdr), fp);

  p = calloc(bmphdr.fhdr.total_size - sizeof(BMPHdr), sizeof(uint8_t));
  fimg = calloc(bmphdr.fhdr.total_size - sizeof(BMPHdr), sizeof(uint8_t));

  qsz = serializePaddingSize(&bmphdr, 1);

  q = calloc(qsz, sizeof(uint8_t));
  r = fread(p, sizeof(int8_t), bmphdr.fhdr.total_size - sizeof(BMPHdr), fp);


  printBuffer(p, 128);

  serializePadding(&bmphdr, 1, p, q);

  createFilter("3X3", &filter[RED]);
  createFilter("3X3", &filter[GREEN]);
  createFilter("3X3", &filter[BLUE]);


  //for ( i=0 ; i<9 ; i++ )
  //{
  //  *(filter[RED]+i) = *(filter[GREEN]+i)= *(filter[BLUE]+i) = 1;
  //}


  sprintf(tmp, "%dX%d", bmphdr.dhdr.width, bmphdr.dhdr.height);


  printBuffer(filter[RED], 9);

  convolutionProduct(q, tmp, 1, 1, filter[RED], 'R', "3X3", fimg, fsz);
  convolutionProduct(q, tmp, 1, 1, filter[RED], 'G', "3X3", fimg, fsz);
  convolutionProduct(q, tmp, 1, 1, filter[RED], 'B', "3X3", fimg, fsz);

  {
    uint8_t* b = 0;
    int32_t wh[2] = {0};
    FILE* ft = fopen("joker+featured.bmp", "wb");

    wh[0] = bmphdr.dhdr.width;
    wh[1] = bmphdr.dhdr.height;
    b = calloc(bmphdr.fhdr.total_size, sizeof(uint32_t));

    r = __write_raw('f', fimg, fsz, bmphdr.dhdr.bitcount, b);

    fwrite(b, sizeof(uint8_t), r, ft);

    free(b);
    fclose(ft);

  }

  free(filter[RED]);
  free(filter[GREEN]);
  free(filter[BLUE]);
  free(q);
  free(p);
  free(fimg);
  fclose(fp);
}


#endif










































#if 0
void main()
{
  int32_t i = 0;
  FILE* fp = fopen("sample_15X13.bmp", "wb");

  uint8_t hdr[54] = {0};
  uint8_t* bdy = 0;
  #if 0
  15X13
  #endif
  int32_t offset = 54;
  int32_t dibsz = 40;
  int32_t wdth = 15;
  int32_t hght = 13;
  int32_t bitplane = 1;
  int32_t bitcount = 24;
  int32_t dpth = bitcount/8;
  int32_t padding = wdth%sizeof(uint32_t);
  int32_t sz  = (wdth*dpth + padding)*hght;
  int32_t tsz = sz + 54;


  bdy = (uint8_t*)calloc(sz, sizeof(int8_t));


  hdr[0] = 'B';
  hdr[1] = 'M';
  memcpy(&hdr[2], &tsz, sizeof(int32_t));
  memcpy(&hdr[10], &offset, sizeof(int32_t));

  memcpy(&hdr[14], &dibsz, sizeof(int32_t));
  memcpy(&hdr[18], &wdth, sizeof(int32_t));
  memcpy(&hdr[22], &hght, sizeof(int32_t));
  memcpy(&hdr[26], &bitplane, sizeof(int16_t));
  memcpy(&hdr[28], &bitcount, sizeof(int16_t));
  memcpy(&hdr[34], &sz, sizeof(int32_t));
  

  for ( i=0 ; i<sz ;i++ )
  {
    *(bdy+i) = i%0xFF + 1;
  }  



  fwrite(hdr, 54, sizeof(int8_t), fp);
  fwrite(bdy, sz, sizeof(int8_t), fp);

  free(bdy);

  fclose(fp);
}
#endif






































































#if 0
void main()
{
  uint8_t* p = 0;
  uint8_t* q = 0;
  int32_t sz = 0;
  int32_t qsz = 0;
  int32_t r = 0;
  BMPHdr  bmphdr = {0};

  FILE* fp = fopen("..\\imgs\\sample.bmp", "rb");

  r = fread(&bmphdr, sizeof(int8_t), sizeof(BMPHdr), fp);
  printf(" sizeof(BMPHdr), read r -> %d \r\n", r);

  p = calloc(bmphdr.fhdr.total_size - sizeof(BMPHdr), sizeof(uint8_t));

  qsz = serializePaddingSize(&bmphdr, 1);
  printf(" serializePaddingSize -> %d \r\n", qsz);

  q = calloc(qsz, sizeof(uint8_t));

  r = fread(p, sizeof(int8_t), bmphdr.fhdr.total_size - sizeof(BMPHdr), fp);
  printf(" bmphdr.fhdr.total_size - sizeof(BMPHdr), read r -> %d \r\n", r);

  printBuffer(p, 128);

  //serializeBitmap(&bmphdr, p, q);
  serializePadding(&bmphdr, 1, p, q);

  __TR__;
  printBuffer(q, 128);


  {
    uint8_t* b = 0;
    int32_t wh[2] = {0};
    FILE* ft = fopen("joker+TT.bmp", "wb");

    wh[0] = bmphdr.dhdr.width;
    wh[1] = bmphdr.dhdr.height;
    b = calloc(bmphdr.fhdr.total_size, sizeof(uint32_t));

    r = __write_raw('f', q, wh, bmphdr.dhdr.bitcount, b);

    fwrite(b, sizeof(uint8_t), r, ft);

    free(b);
    fclose(ft);

  }

  {
    uint8_t* b = 0;
    int32_t wh[2] = {0};
    FILE* ft = fopen("joker+TTTT.bmp", "wb");

    wh[0] = bmphdr.dhdr.width;
    wh[1] = bmphdr.dhdr.height;
    b = calloc(bmphdr.fhdr.total_size, sizeof(uint32_t));

    r = __write_raw('r', q, wh, bmphdr.dhdr.bitcount, b);

    fwrite(b, sizeof(uint8_t), r, ft);

    free(b);
    fclose(ft);

  }


  free(q);
  free(p);
  fclose(fp);

}

#endif



#if 0

void main()
{

  uint8_t* p = 0;
  int32_t sz = 0;
  int32_t r = 0;
  BMPHdr  bmphdr = {0};

  FILE* fp = fopen("joker3.bmp", "rb");

  sz = 32*(32*3+(32%4)) + 54;

  p = calloc(sz, sizeof(int8_t));

  r = fread(p, sizeof(int8_t), sz, fp);


  readBitmapHdr(p, &bmphdr);

  printf(" sign          : %c%c \r\n", bmphdr.fhdr.sign[0], bmphdr.fhdr.sign[1]);
  printf(" total size    : %d \r\n", bmphdr.fhdr.total_size);
  printf(" offset        : %d \r\n", bmphdr.fhdr.offset);
  printf(" dib hd size   : %d \r\n", bmphdr.dhdr.size);
  printf(" width         : %d \r\n", bmphdr.dhdr.width);
  printf(" height        : %d \r\n", bmphdr.dhdr.height);
  printf(" bit planes    : %d \r\n", bmphdr.dhdr.planes);
  printf(" bit count     : %d \r\n", bmphdr.dhdr.bitcount);
  printf(" image size    : %d \r\n", bmphdr.dhdr.size);


  free(p);
  fclose(fp);

}
#endif


#if 0
void main(int argc, char** argv)
{
  uint8_t* p = 0;
  uint8_t* q = 0;
  uint8_t* b = 0;
  int32_t sz = 0;
  int32_t r = 0;
  int32_t xy[2] = {0};
  int32_t wh[2] = {0};

  FILE* fp = fopen("joker3.bmp", "rb");
  FILE* ft = fopen("joker3-rt3-6.bmp", "wb");

  sz = (564*3+(564%4))*1002;

  p = calloc(sz, sizeof(int8_t));
  q = calloc(sz, sizeof(int8_t));
  b = calloc(sz, sizeof(int8_t));

  r = fread(p, sizeof(int8_t), sz, fp);


  printBuffer(p, 128);


  //xy[0] = 100;
  //xy[1] = 120;
  //wh[0] = 257;
  //wh[1] = 300;

  //r = rread_raw(p, xy, wh, &q);
  //r = write_raw_bitmap(q, wh, 24, b);


  //r = fwrite(b, r, sizeof(int8_t), ft);



  free(p);
  free(q);
  fclose(fp);
  fclose(ft);

}
#endif
