#include "utils.h"

void printArray(int32_t* p, int32_t count)
{
  int32_t i = 0;

  __TR__;
  for ( i=0 ; i<count ; i++ )
  {
    printf(" *(p+%04d) : %2d \r\n", i, *(p+i));
  }
  __TR__;
}


void assignArray(int32_t* p, int32_t count)
{
  int32_t i = 0;

  for ( i=0 ; i<count ; i++ )
  {
    *(p+i) = rand()%10;
  }
}


void printBuffer(int8_t* b, int32_t sz)
{
  int32_t i = 0;

  printf("|%08X|", i);
  for ( i=0 ; i<sz ; i++ )
  {
    if ( i &&  (i%8)==0 ) printf("  ");
    if ( i &&  (i%16)==0 )
    {
      printf("\r\n");
      printf("|%08X|", i);
    }
    printf(" %02X", (uint8_t)*(b+i));
  }

  printf("\r\n");
}