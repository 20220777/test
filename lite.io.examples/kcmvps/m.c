#include <common.h>
#include <xcommon.h>

#define _USE_MATH_DEFINES
#include <math.h>

#if 0
erf(x) = 1 - erfc(x)
#endif

#define   __E(x)           ((long double)x/2.0)
#define   __sigma(x)       (long double)sqrt(((long double)x/4.0))
#define   ____S(x)         ((x-__E(x))/__sigma(x))
#define   __S(x)           ((____S(x)<0) ? -1*____S(x):____S(x))
#define   __C               (2/sqrt(M_PI))


int32_t read_noise_source(int8_t* fname, uint8_t** p)
{
  int32_t e = 0;
  FILE* fp = 0;

  fp = fopen(fname, "r");

  fseek(fp, 0, SEEK_SET);
  fseek(fp, 0, SEEK_END);
  e = ftell(fp);

  fseek(fp, 0, SEEK_SET);

  *p = (uint8_t*)calloc(e, sizeof(uint8_t));
  fread(*p, sizeof(uint8_t), e, fp);

  fclose(fp);
  return e;
}


int32_t __count_bit(uint8_t p, uint8_t sample)
{
  int32_t e = 0;
  int32_t _i = 0;

  for ( _i=7 ; _i>=0 ; _i-- )
  {
    if ( ((p>>_i) & 0x01) == sample ) e++;
  }
  return e;
}

int32_t __count_bits(uint8_t* p, int32_t sz, uint8_t sample)
{
  int32_t e = 0;
  int32_t i = 0;
  int32_t _i = 0;

  for ( i=0 ; i<sz ; i++ )
  {
    e += __count_bit(*(p+i), sample);
  }
  
  return e;
}


#if 0
long double __erf(long double x, long double max)
{
  long double s = 0.0;
  int32_t i = 0;

  for ( i=0 ; i<max ; i++ )
  {
    s += (____pow(-1.0, i)*____pow(x, 2.0*(i/2)+1))/((2.0*i+1)*____factorial(i));
  }
  return __C*s;
}
#endif



long double __erf(long double x, long double dx)
{
  long double s = 0.0;
  long double i = 0.0;


  for ( i=0 ; i<x ; i+=dx )
  {
    s += exp( -1*(i*i) ) * dx; 
  }
  return __C*s;
}



void main()
{
  int32_t i = 0;
  int32_t sz = 0;
  uint8_t* p = 0;
  uint8_t* _p = 0;
  int32_t n = 0;

  sz = read_noise_source("w64_noise_cryptgenrand.txt", &p);


  //sz = 2;
  _p = (uint8_t*)calloc(sz/2, sizeof(uint8_t));

  *(p+sz) = 0;
 __string_to_hex(p, _p);

  printf(" %02X  %02X %02X", (uint8_t)*(_p+i), (uint8_t)__asc_to_hex("1B"), (uint8_t)__asc_to_hex("CF"));

  printf("\r\n");

  printf(" %d \r\n", __count_bit(0x03, 1));
  printf(" %d \r\n", __count_bit(0x03, 0));


  printf(" %d \r\n", __count_bits(_p, sz/2, 1));
  printf(" %d \r\n", __count_bits(_p, sz/2, 0));


  n = __count_bits(_p, sz/2, 1);

  printf("  %16.8Lf \r\n", __E(n));
  printf("  %16.8Lf \r\n", __sigma(n));
  printf("  %16.8Lf \r\n", __S(n));
  printf("  %16.8Lf \r\n", sqrt(2.0));
  printf("  %16.8Lf \r\n", __S(n)/sqrt(2.0));


  printf("  %16.8Lf \r\n", ____pow(-2, 3));
  printf("  %16.8Lf \r\n", __erf(__S(n)/sqrt(2.0), 0.001));
  printf("  %16.8Lf \r\n", erf(3));
  printf("  %16.8Lf \r\n", __erf(3, 0.1));


  printf("  %16.8Lf \r\n", 1.0 - __erf(__S(n)/sqrt(2.0), 0.001));


  free(_p);
  free(p);
  printf("\r\n");

}