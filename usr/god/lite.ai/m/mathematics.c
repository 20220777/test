#include "mathematics.h"

void printMatrix(int32_t* p, int8_t* sz)
{
  int8_t xy[2][8] = {0};
  int32_t rc[2] = {0};
  int32_t r=0;
  int32_t c=0;

  TO_COORD(sz, xy[0], xy[1]);

  rc[0] = (int32_t)atoll(xy[0]);
  rc[1] = (int32_t)atoll(xy[1]);

  for ( r=0 ; r<rc[0] ; r++ )
  {
    for ( c=0 ; c<rc[1] ; c++ )
    {
      printf("%4d ", *(p+r*(rc[1])+c));
    }
    printf("\r\n");
  }
}

void addMatrix(int32_t* a, int32_t* b, int8_t* sz, int32_t* s)
{
  int8_t xy[2][8] = {0};
  int32_t rc[2] = {0};
  int32_t r=0;
  int32_t c=0;

  TO_COORD(sz, xy[0], xy[1]);

  rc[0] = (int32_t)atoll(xy[0]);
  rc[1] = (int32_t)atoll(xy[1]);

  for ( r=0 ; r<rc[0] ; r++ )
  {
    for ( c=0 ; c<rc[1] ; c++ )
    {
      (*(s+r*(rc[1])+c)) = ( (*(a+(r*(rc[1]))+c)) + (*(b+(r*(rc[1]))+c)) );
    }
  }
}

void mulMatrix(int32_t* a, int8_t* asz, int32_t* b, int8_t* bsz, int32_t* s)
{
  int8_t axy[2][8] = {0};
  int8_t bxy[2][8] = {0};
  int32_t arc[2] = {0};
  int32_t brc[2] = {0};
  int32_t r=0;
  int32_t c=0;
  int32_t i=0;

  TO_COORD(asz, axy[0], axy[1]);
  TO_COORD(bsz, bxy[0], bxy[1]);

  arc[0] = (int32_t)atoll(axy[0]);
  arc[1] = (int32_t)atoll(axy[1]);
  brc[0] = (int32_t)atoll(bxy[0]);
  brc[1] = (int32_t)atoll(bxy[1]);


  for ( r=0 ; r<arc[0] ; r++ )
  {
    for ( c=0 ; c<brc[1] ; c++ )
    {
      *(s+r*brc[1]+c) = 0;
      for ( i=0 ; i<arc[1] ; i++ )
      {
        (*(s+r*(brc[1])+c)) += ( (*(a+(r*(arc[1])+i))) * (*(b+(i*(brc[1]))+c)) );
      }
    }
  }
}


void createMatrixI(int32_t* p, int8_t* sz)
{
  int8_t xy[2][8] = {0};
  int32_t rc[2] = {0};
  int32_t r=0;
  int32_t c=0;

  TO_COORD(sz, xy[0], xy[1]);

  rc[0] = (int32_t)atoll(xy[0]);
  rc[1] = (int32_t)atoll(xy[1]);

  printf("(%d, %d) \r\n", rc[0], rc[1]);

  for ( r=0 ; r<rc[0] ; r++ )
  {
    for ( c=0 ; c<rc[1] ; c++ )
    {
      if ( r==c ) *(p+r*(rc[1])+c) = 1;
      else *(p+r*(rc[1])+c) = 0;
    }
  }
}

void createMatrixO(int32_t* p, int8_t* sz)
{
  int8_t xy[2][8] = {0};
  int32_t rc[2] = {0};
  int32_t r=0;
  int32_t c=0;

  TO_COORD(sz, xy[0], xy[1]);

  rc[0] = (int32_t)atoll(xy[0]);
  rc[1] = (int32_t)atoll(xy[1]);

  printf("(%d, %d) \r\n", rc[0], rc[1]);

  for ( r=0 ; r<rc[0] ; r++ )
  {
    for ( c=0 ; c<rc[1] ; c++ )
    {
      *(p+r*(rc[1])+c) = 0;
    }
  }
}

void matrixT(int32_t* a, int32_t* sz, int32_t* s)
{
  int8_t xy[2][8] = {0};
  int32_t rc[2] = {0};
  int32_t r=0;
  int32_t c=0;

  TO_COORD(sz, xy[0], xy[1]);

  rc[0] = (int32_t)atoll(xy[0]);
  rc[1] = (int32_t)atoll(xy[1]);

  for (r = 0; r < rc[0]; r++)
  {
    for (c = 0; c < rc[1]; c++)
    {
      *(s + (c*(rc[0]))+r) = *(a+(r*(rc[1]))+c);
    }
  }
}


int32_t matrixDet(int32_t* p, int8_t* sz)
{
  int8_t xy[2][8] = {0};
  int32_t rc[2] = {0};
  int32_t r = 0;
  int32_t c = 0;
  int32_t i = 0;

  int32_t v[2][2] = {0};

  TO_COORD(sz, xy[0], xy[1]);
  rc[0] = (int32_t)atoll(xy[0]);
  rc[1] = (int32_t)atoll(xy[1]);

  for (r = 0; r < rc[0]; r++)
  {
    v[0][0] = 1;
    for (c = 0; c < rc[1]; c++)
    {
      v[0][0] *= *(p+(c*(rc[0]) + (r+c)%(rc[1])));
    }
    v[0][1] += v[0][0];
  }
  for (r = rc[0]-1; r >= 0; r--)
  {
    v[1][0] = 1;
    for (c = 0; c < rc[1]; c++)
    {
      v[1][0] *= *(p+((rc[0]*rc[1])+(r*rc[0]-c*rc[0]+c))%(rc[0]*rc[1]));
    }
    v[1][1] += v[1][0];
  }
  return (v[0][1] - v[1][1]);
}







int32_t findMIN(int32_t* arr, int32_t sz, int32_t* min)
{
  sz--;
  *min = *(arr+sz);

  for ( ; sz>=0; sz--)
  {
    if ( *min > *(arr+sz ) ) *min = *(arr+sz);
  }

  return *min;
}




int32_t findMAX(int32_t* arr, int32_t sz, int32_t* max)
{
  sz--;
  *max = *(arr+sz);

  for ( ; sz>=0; sz--)
  {
    if ( *max < *(arr+sz ) ) *max = *(arr+sz);
  }

  return *max;
}



int32_t findMAX8bit(int8_t* arr, int32_t sz, int8_t* max)
{
  sz--;
  *max = *(arr+sz);

  for ( ; sz>=0; sz--)
  {
    if ( *max < *(arr+sz ) ) *max = *(arr+sz);
  }

  return *max;
}















void printBitmapHdr(uint8_t* p)
{
  int32_t e = 0;
  int8_t  sign[2] = {0};
  int32_t tsz = 0;
  int32_t offset = 0; //10(4)

  int32_t dhds = 0;
  int32_t wdth = 0;
  int32_t hght = 0;
  int16_t bpln = 0;
  int16_t bcnt = 0;   //18(4), 22(4), 28(2)
  int32_t sz = 0;



  sign[0] = *(p+0);
  sign[1] = *(p+1);
  memcpy(&tsz,   p+2,  sizeof(int32_t));
  memcpy(&offset, p+10, sizeof(int32_t));
  memcpy(&dhds,   p+14, sizeof(int32_t));
  memcpy(&wdth,   p+18, sizeof(int32_t));
  memcpy(&hght,   p+22, sizeof(int32_t));
  memcpy(&bpln,   p+26, sizeof(int16_t));
  memcpy(&bcnt,   p+28, sizeof(int16_t));
  memcpy(&sz,     p+34, sizeof(int32_t));


  printf(" sign          : %c%c \r\n", sign[0], sign[1]);
  printf(" total size    : %d \r\n", tsz);
  printf(" offset        : %d \r\n", offset);
  printf(" dib hd size   : %d \r\n", dhds);
  printf(" width         : %d \r\n", wdth);
  printf(" height        : %d \r\n", hght);
  printf(" bit planes    : %d \r\n", bpln);
  printf(" bit count     : %d \r\n", bcnt);
  printf(" image size    : %d \r\n", sz);


}

void readBitmapHdr(uint8_t* p, BMPHdr* h)
{
  memcpy(&h->fhdr, p, sizeof(BMPFHdr));
  memcpy(&h->dhdr, p+14, sizeof(DIBHdr));
}




int32_t serializeBitmap(BMPHdr* bmphdr, int8_t* img, int8_t* raw)
{
  int32_t i=0;
  int32_t dpth = bmphdr->dhdr.bitcount/8;
  int32_t w = bmphdr->dhdr.width;
  int32_t h = bmphdr->dhdr.height;

  for ( i=0 ; i<h ; i++ )
  {
    memcpy((raw+(w*dpth*i)), img+((BMP_PADDING(w)+w*dpth)*(h-i-1)), sizeof(uint8_t)*w*dpth);
  }
  return w*dpth*i;
}

int32_t deserializeBitmap(int32_t* wh, int32_t bcnt, int8_t* raw, int8_t* bmp)
{
  int32_t i=0;
  int32_t dpth = bcnt/8;

  for ( i=0 ; i<*(wh+1) ; i++ )
  {
    memcpy(bmp+((BMP_PADDING(*(wh+0))+(*(wh+0))*dpth)*((*(wh+1))-i-1)), raw+((*(wh+0))*dpth)*i, sizeof(uint8_t)*(*(wh+0))*dpth);
  }
  return (BMP_PADDING(*(wh+0))+(*(wh+0))*dpth)*i;
}




int32_t serializePaddingSize(BMPHdr* bmphdr, int32_t pwdth)
{
  return (bmphdr->dhdr.width+pwdth*2)*(bmphdr->dhdr.bitcount/8)*(bmphdr->dhdr.height+pwdth*2);
}

int32_t serializePadding(BMPHdr* bmphdr, int32_t pwdth, int8_t* img, int8_t* raw)
{
  int32_t j=0;
  int32_t i=0;
  int32_t dpth = bmphdr->dhdr.bitcount/8;
  int32_t w = bmphdr->dhdr.width;
  int32_t h = bmphdr->dhdr.height;

  j += (w + pwdth*2)*dpth;
  for ( i=0 ; i<h ; i++ )
  {
    j+=pwdth*dpth;
    memcpy((raw+(w*dpth*i)+j), img+((BMP_PADDING(w)+w*dpth)*(h-i-1)), sizeof(uint8_t)*w*dpth);
    j+=pwdth*dpth;
  }
  j += (w + pwdth*2)*dpth;

  return (w*dpth*i)+j;
}


void assignRandomBits(void* p, int32_t count, uint8_t type)
{
  count--;
  for ( ; count>=0 ; count-- )
  {
    if( type=='f' || type=='F' ) *(((long double*)p)+count) = (long double)(rand()%0x46)/100.0;
    else if ( type=='c' || type=='C' || type=='8' ) *(((uint8_t*)p)+count) = (uint8_t)(rand()%0x0F);
    else if ( type=='i' || type=='I' ) *(((uint32_t*)p)+count) = (uint32_t)(rand()%0x0F);
  }
}


void assign8bit(int8_t* p, int32_t count)
{
  count--;
  for ( ; count>=0 ; count-- )
  {
    *(p+count) = (uint8_t)(rand()%0x0F);
  }
}


void assign32bit(int32_t* p, int32_t count)
{
  count--;
  for ( ; count>=0 ; count-- )
  {
    *(p+count) = (uint32_t)(rand()%0x0F);
  }
}

void assignFloat(long double* p, int32_t count)
{
  count--;
  for ( ; count>=0 ; count-- )
  {
    *(p+count) = (long double)(rand()%0x46)/100.0;
  }
}


int32_t createFilter(int8_t* wh, int32_t** filter)
{
  int8_t xy[2][8] = {0};
  int32_t rc[2] = {0};

  TO_COORD(wh, xy[0], xy[1]);
  rc[0] = (int32_t)atoll(xy[0]);
  rc[1] = (int32_t)atoll(xy[1]);


  *filter = (int32_t*)calloc(rc[0]*rc[1], sizeof(int32_t));


  assignArray(*filter, rc[0]*rc[1]);

  return rc[0]*rc[1];
}

void printFloatFilter(int32_t* wh, long double* filter)
{
  int32_t w, h;

  for ( h=0 ; h<*(wh+1) ; h++ )
  {
    for ( w=0 ; w<*(wh+0) ; w++ )
    {
      printf("%8.2Lf ", *(filter+w+h*(*(wh+0))));
    }
    printf("\r\n");
  }
}



int32_t createFloatFilter(int32_t* wh, long double** filter)
{
  *filter = (long double*)calloc((*(wh+0))*(*(wh+1)), sizeof(long double));

  assignFloat(*filter, (*(wh+0))*(*(wh+1)));

  return (*(wh+0))*(*(wh+1));
}


int32_t convolutionProduct(uint8_t* input, int32_t* iwh, int32_t padding, int32_t stride, uint32_t* filter, int32_t* fwh, int8_t ft, uint8_t* output, int32_t* owh)
{
  int32_t e = 0;
  int32_t w= 0;
  int32_t h = 0;

  int32_t wdth = 0;
  int32_t dpth = 3;

  wdth = ((*(iwh+0))+(padding*2))*dpth;

  *(owh+0) = ((*(iwh+0))+2*padding-(*(fwh+0)))/stride + 1;
  *(owh+1) = ((*(iwh+1))+2*padding-(*(fwh+1)))/stride + 1;


  for ( h=0 ; h<*(iwh+1) ; h++ )
  {
    for ( w=0 ; w<*(iwh+0) ; w++ )
    {
      #if 1
      printf(" %4d : %4d, %4d, %4d ,  %4d, %4d, %4d,  %4d, %4d, %4d\r\n"
             "      : %4d, %4d, %4d ,  %4d, %4d, %4d,  %4d, %4d, %4d\r\n",
              h*((*(owh+0))*dpth)+w*dpth+(ft=='R'?2:ft=='G'?1:0),
              h*wdth+ w   *dpth*stride       +(ft=='R'?2:ft=='G'?1:0),
              h*wdth+(w+1)*dpth*stride       +(ft=='R'?2:ft=='G'?1:0),
              h*wdth+(w+2)*dpth*stride       +(ft=='R'?2:ft=='G'?1:0),
              h*wdth+ w   *dpth*stride+wdth  +(ft=='R'?2:ft=='G'?1:0),
              h*wdth+(w+1)*dpth*stride+wdth  +(ft=='R'?2:ft=='G'?1:0),
              h*wdth+(w+2)*dpth*stride+wdth  +(ft=='R'?2:ft=='G'?1:0),
              h*wdth+ w   *dpth*stride+wdth*2+(ft=='R'?2:ft=='G'?1:0),
              h*wdth+(w+1)*dpth*stride+wdth*2+(ft=='R'?2:ft=='G'?1:0),
              h*wdth+(w+2)*dpth*stride+wdth*2+(ft=='R'?2:ft=='G'?1:0),
              0,
              1,
              2,
              (*(fwh+0))+0,
              (*(fwh+0))+1,
              (*(fwh+0))+2,
              (*(fwh+0))*2+0,
              (*(fwh+0))*2+1,
              (*(fwh+0))*2+2);
      #endif


      #if 0
      *(output+h*((*(owh+0))*dpth)+w*dpth+(ft=='R'?2:ft=='G'?1:0)) = 
            (*(input+h*wdth+ w   *dpth*stride       +(ft=='R'?2:ft=='G'?1:0))) * (*(filter+0))
          + (*(input+h*wdth+(w+1)*dpth*stride       +(ft=='R'?2:ft=='G'?1:0))) * (*(filter+1))
          + (*(input+h*wdth+(w+2)*dpth*stride       +(ft=='R'?2:ft=='G'?1:0))) * (*(filter+2))
          + (*(input+h*wdth+ w   *dpth*stride+wdth  +(ft=='R'?2:ft=='G'?1:0))) * (*(filter+(*(fwh+0))+0))
          + (*(input+h*wdth+(w+1)*dpth*stride+wdth  +(ft=='R'?2:ft=='G'?1:0))) * (*(filter+(*(fwh+0))+1))
          + (*(input+h*wdth+(w+2)*dpth*stride+wdth  +(ft=='R'?2:ft=='G'?1:0))) * (*(filter+(*(fwh+0))+2))
          + (*(input+h*wdth+ w   *dpth*stride+wdth*2+(ft=='R'?2:ft=='G'?1:0))) * (*(filter+(*(fwh+0))*2+0))
          + (*(input+h*wdth+(w+1)*dpth*stride+wdth*2+(ft=='R'?2:ft=='G'?1:0))) * (*(filter+(*(fwh+0))*2+1))
          + (*(input+h*wdth+(w+2)*dpth*stride+wdth*2+(ft=='R'?2:ft=='G'?1:0))) * (*(filter+(*(fwh+0))*2+2));
      #endif
    }

  }
  return (*(owh+0))*dpth*(*(owh+1));
}



int32_t convolutions(uint8_t* input, int32_t* iwh, int32_t padding, int32_t stride, long double* filter, int32_t* fwh, int8_t ft, uint8_t* output, int32_t* owh)
{
  int32_t e = 0;
  int32_t w= 0;
  int32_t h = 0;

  int32_t wdth = 0;
  int32_t dpth = 3;

  wdth = ((*(iwh+0))+(padding*2))*dpth;

  *(owh+0) = ((*(iwh+0))+2*padding-(*(fwh+0)))/stride + 1;
  *(owh+1) = ((*(iwh+1))+2*padding-(*(fwh+1)))/stride + 1;


  for ( h=0 ; h<*(iwh+1) ; h++ )
  {
    for ( w=0 ; w<*(iwh+0) ; w+=(stride) )
    {
      #if 0
      printf(" %4d : %4d, %4d, %4d ,  %4d, %4d, %4d,  %4d, %4d, %4d\r\n"
             "      : %4d, %4d, %4d ,  %4d, %4d, %4d,  %4d, %4d, %4d\r\n",
              h*((*(owh+0))*dpth)+w*dpth+(ft=='R'?2:ft=='G'?1:0),
              h*wdth+ w   *dpth       +(ft=='R'?2:ft=='G'?1:0),
              h*wdth+(w+1)*dpth       +(ft=='R'?2:ft=='G'?1:0),
              h*wdth+(w+2)*dpth       +(ft=='R'?2:ft=='G'?1:0),
              h*wdth+ w   *dpth+wdth  +(ft=='R'?2:ft=='G'?1:0),
              h*wdth+(w+1)*dpth+wdth  +(ft=='R'?2:ft=='G'?1:0),
              h*wdth+(w+2)*dpth+wdth  +(ft=='R'?2:ft=='G'?1:0),
              h*wdth+ w   *dpth+wdth*2+(ft=='R'?2:ft=='G'?1:0),
              h*wdth+(w+1)*dpth+wdth*2+(ft=='R'?2:ft=='G'?1:0),
              h*wdth+(w+2)*dpth+wdth*2+(ft=='R'?2:ft=='G'?1:0),
              0,
              1,
              2,
              (*(fwh+0))+0,
              (*(fwh+0))+1,
              (*(fwh+0))+2,
              (*(fwh+0))*2+0,
              (*(fwh+0))*2+1,
              (*(fwh+0))*2+2);
      #endif


      #if 1
      *(output+h*((*(owh+0))*dpth)+w*dpth+(ft=='R'?2:ft=='G'?1:0)) = 
            (*(input+h*wdth+ w   *dpth       +(ft=='R'?2:ft=='G'?1:0))) * (*(filter+0))
          + (*(input+h*wdth+(w+1)*dpth       +(ft=='R'?2:ft=='G'?1:0))) * (*(filter+1))
          + (*(input+h*wdth+(w+2)*dpth       +(ft=='R'?2:ft=='G'?1:0))) * (*(filter+2))
          + (*(input+h*wdth+ w   *dpth+wdth  +(ft=='R'?2:ft=='G'?1:0))) * (*(filter+(*(fwh+0))+0))
          + (*(input+h*wdth+(w+1)*dpth+wdth  +(ft=='R'?2:ft=='G'?1:0))) * (*(filter+(*(fwh+0))+1))
          + (*(input+h*wdth+(w+2)*dpth+wdth  +(ft=='R'?2:ft=='G'?1:0))) * (*(filter+(*(fwh+0))+2))
          + (*(input+h*wdth+ w   *dpth+wdth*2+(ft=='R'?2:ft=='G'?1:0))) * (*(filter+(*(fwh+0))*2+0))
          + (*(input+h*wdth+(w+1)*dpth+wdth*2+(ft=='R'?2:ft=='G'?1:0))) * (*(filter+(*(fwh+0))*2+1))
          + (*(input+h*wdth+(w+2)*dpth+wdth*2+(ft=='R'?2:ft=='G'?1:0))) * (*(filter+(*(fwh+0))*2+2));
      #endif
    }

  }

  return (*(owh+0))*dpth*(*(owh+1));
}



int32_t maxpooling(uint8_t* input, int32_t* iwh, int32_t stride, int8_t ft, uint8_t* output, int32_t* owh)
{
  int32_t e = 0;
  int32_t w= 0;
  int32_t h = 0;

  int32_t wdth = 0;
  int32_t dpth = 3;

  int32_t i = 0;

  int32_t max = 0;
  uint8_t* pool = calloc(9, sizeof(uint8_t));


  *(owh+0) = *(iwh+0)-stride*2;
  *(owh+1) = *(iwh+1)-stride*2;

  wdth = *(iwh+0)*dpth;

  for ( h=0 ; h<*(owh+1) ; h++ )
  {
    for ( w=0 ; w<*(owh+0) ; w++ )
    {
      #if 0
      printf(" %4d : %4d, %4d, %4d ,  %4d, %4d, %4d,  %4d, %4d, %4d\r\n",
              h*((*(owh+0))*dpth)+w*dpth+(ft=='R'?2:ft=='G'?1:0),
              h*wdth+ w   *dpth       +(ft=='R'?2:ft=='G'?1:0),
              h*wdth+(w+1)*dpth       +(ft=='R'?2:ft=='G'?1:0),
              h*wdth+(w+2)*dpth       +(ft=='R'?2:ft=='G'?1:0),
              h*wdth+ w   *dpth+wdth  +(ft=='R'?2:ft=='G'?1:0),
              h*wdth+(w+1)*dpth+wdth  +(ft=='R'?2:ft=='G'?1:0),
              h*wdth+(w+2)*dpth+wdth  +(ft=='R'?2:ft=='G'?1:0),
              h*wdth+ w   *dpth+wdth*2+(ft=='R'?2:ft=='G'?1:0),
              h*wdth+(w+1)*dpth+wdth*2+(ft=='R'?2:ft=='G'?1:0),
              h*wdth+(w+2)*dpth+wdth*2+(ft=='R'?2:ft=='G'?1:0)
      );
      #endif
      i = 0;
      *(pool + i) = *(input + h*wdth+ w   *dpth       +(ft=='R'?2:ft=='G'?1:0)); i++;
      *(pool + i) = *(input + h*wdth+(w+1)*dpth       +(ft=='R'?2:ft=='G'?1:0)); i++;
      *(pool + i) = *(input + h*wdth+(w+2)*dpth       +(ft=='R'?2:ft=='G'?1:0)); i++;
      *(pool + i) = *(input + h*wdth+ w   *dpth+wdth  +(ft=='R'?2:ft=='G'?1:0)); i++;
      *(pool + i) = *(input + h*wdth+(w+1)*dpth+wdth  +(ft=='R'?2:ft=='G'?1:0)); i++;
      *(pool + i) = *(input + h*wdth+(w+2)*dpth+wdth  +(ft=='R'?2:ft=='G'?1:0)); i++;
      *(pool + i) = *(input + h*wdth+ w   *dpth+wdth*2+(ft=='R'?2:ft=='G'?1:0)); i++;
      *(pool + i) = *(input + h*wdth+(w+1)*dpth+wdth*2+(ft=='R'?2:ft=='G'?1:0)); i++;
      *(pool + i) = *(input + h*wdth+(w+2)*dpth+wdth*2+(ft=='R'?2:ft=='G'?1:0)); i++;

       *(output + h*((*(owh+0))*dpth)+w*dpth+(ft=='R'?2:ft=='G'?1:0)) = findMAX8bit(pool, i, &max);
    }
  }
  free(pool);

  return (*(owh+0))*dpth*(*(owh+1));
}
