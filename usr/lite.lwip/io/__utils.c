#include "__utils.h"
#include "stm32f4xx_hal.h"


#if 0
void display(int8_t* b, int32_t sz, const int8_t* fmt,...)
{
  int32_t i = 0;
  va_list args;
  int8_t _msg[512];
	va_start(args, fmt);
	vsprintf(_msg, fmt, args);
  va_end(args);

  CRLF;
  PREFIX;
  printf("***************************************************");
  CRLF;
  PREFIX;
  printf("* %-47s *", _msg);
  CRLF;
  PREFIX;
  printf("***************************************************");
  CRLF;
  printf("|%08X|", i);
  for ( i=0 ; i<sz ; i++ )
  {
    if ( i &&  (i%8)==0 ) printf("  ");
    if ( i &&  (i%16)==0 )
    {
      CRLF;
      printf("|%08X|", i);
    }
    printf(" %02X", (uint8_t)*(b+i));
  }
  CRLF;
  PREFIX;
  printf("---------------------------------------------------");
  CRLF;
  CRLF;
}
#endif

int32_t xascii_to_hex(uint8_t* src, uint8_t* dst)
{
  int32_t i=0;
  for (i=0; *src ; src++, i++ )
  {
    if ( (*(src)>='A') && (*(src)<='Z') )
    {
      ( i&1 ) ? ((*dst |= (*(src) - 0x37)&0x0F ), dst++ ): (*dst=0, ( *dst |= ( (*(src) - 0x37)&0x0F) << 4 ));
    }
    else if ( (*(src)>='a') && (*(src)<='z') )
    {
      ( i&1 ) ? ((*dst |= (*(src) - 0x57)&0x0F ), dst++ ): (*dst=0, ( *dst |= ( (*(src) - 0x57)&0x0F) << 4 ));
    }
    else if ( (*(src)>='0') && (*(src)<='9') )
    {
      ( i&1 ) ? ((*dst |= (*(src) - 0x30)&0x0F ), dst++ ): (*dst=0, ( *dst |= ( (*(src) - 0x30)&0x0F) << 4 ));
    }
    else
    {
      i--;
    }
  }

  if ( i&1 )
  {
    *dst>>=4;
    dst++;
    *dst = 0;
  }
  return (i/2) + (i%2);
}
