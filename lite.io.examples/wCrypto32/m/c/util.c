#include <util.h>
#include <stdarg.h>

#if defined XWIN32
#include <Windows.h>
#endif


void raw_buffer(int8_t* b, int32_t sz, int8_t* o)
{
  int32_t i = 0;

  for ( i=0 ; i<sz ;i++ )
  {
    sprintf(o+(i*3), "%02X ", (uint8_t)*(b+i));
  }
  *(o+(i*3)) = 0;
}

void display(int8_t* title, int8_t* b, int32_t sz)
{
  int32_t i = 0;

  CRLF;
  PREFIX;
  printf("**************************************************");
  CRLF;
  PREFIX;
  printf("* %-46s *", title);
  CRLF;
  PREFIX;
  printf("**************************************************");
  CRLF;
  PREFIX;
  for ( i=0 ; i<sz ; i++ )
  {
    if ( i &&  (i%8)==0 ) printf("  ");
    if ( i &&  (i%16)==0 )
    {
      CRLF;
      PREFIX;
    }
    printf(" %02X", (uint8_t)*(b+i));
  }
  CRLF;
  PREFIX;
  printf("--------------------------------------------------");
  CRLF;
  CRLF;
}

void trace(const int8_t* fmt,...)
{
  va_list args;
  int8_t _msg[512];
  #if defined LINUX
  PREFIXN;
  #endif
	va_start(args, fmt);
  #if defined XWIN32
  vsprintf(_msg, fmt, args);
  #else
	vfprintf(stderr,fmt, args);
  fflush(stderr);
  #endif
  va_end(args);

  #if defined XWIN32
  OutputDebugString(_msg);
  #endif
 
}



int32_t hexsim(uint8_t* a, uint8_t* b)
{
  int32_t i = 0;
  srand(time(0));
  for (i = 0; *a; a++, b++, i++)
  {
    if ((*(a) == 'X') || (*(a) == 'x') || (*(a) == '?'))
    {
      *b = (rand() % 16);
      *b = (((*b >= 0) && (*b <= 9)) ? *b + 0x30 : *b + 0x37);
    }
    else if (*a != ' ')
    {
      *b = *a;
    }
    else
    {
      b--;
      i--;
    }
  }
  *b = 0;
  return i;
}


int32_t sample_protocol(int8_t* out)
{
  uint8_t sample[4096] = {0, };
  int32_t sz = 0;
  int32_t e = 0;

  hexsim(SAMPLE_PROTOCOL, sample);

  sz = string_to_hex(sample, out);
  *(out+sz) = 0;
  return sz;
}
