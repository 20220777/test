#include <__util.h>
#include <stdarg.h>

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

int32_t ascii_to_hex(uint8_t* src, uint8_t* dst)
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


int32_t hexasc(uint8_t* dst, uint8_t* src, int32_t sz)
{
  int32_t i =0;
  for (i=0 ; i<sz ; i++ )
  {
    sprintf(dst+2*i, "%02X", *(src+i));
  }
  return i;
}

int32_t hexTo(int8_t* a) {
    int32_t i = 0;
    int32_t hex = 0;

    if (*(a + 1) == 0) return 0x80000000;

    for (i = 0; i < 2; i++)
    {
        if (*(a + i) >= '0' && *(a + i) <= '9')
        {
            //printf("0   %d", (*(a + i) - '0') * (16 - 15 * i));
            //printf("\n\n");
            hex += (*(a + i) - '0') * (16 - 15 * i);
        }
        else if (*(a + i) >= 'a' && *(a + i) < 'g')
        {
            //printf("a   %d",(*(a + i) - 'a' + 10) * (16-15 * i));
            //printf("\n\n");
            hex += (*(a + i) - 'a' + 10) * (16 - 15 * i);
        }
        else if (*(a + i) >= 'A' && *(a + i) < 'G')
        {
            hex += (*(a + i) - 'A' + 10) * (16 - 15 * i);
        }
    }

    if (*(a + 1) == 0) hex /= 16;

    return hex;

}

int32_t toHex(int8_t* a, uint8_t* result, int32_t* count) {
    int32_t i = 0;
    int32_t hex = 0;

    while (1)
    {

        hex = hexTo(a + i);

        if (hex < 0) {
            printf("Not a hex value\r\n");
            exit(0);
        }

        *(result + *count) = hex;
        *count += 1;

        //printf("count = %d", *count);
        //printf("result[%d] => %X\n", *count, result[*count]);

        if (!*(a + i + 2)) 	break;
        i += 2;
    }
}

void bigNumToArray(uint8_t* a, int32_t count, uint32_t* p)
{
    int32_t i = 0, j = 0;
    uint32_t num = 0;

    for (i = 0; i <= count; i += 8)
    {
        for (j = 3; j >= 0; j--)
        {
            num += hexTo(a + i + 2 * (3 - j)) << 8 * j;
            //printf("%X\n", num);
        }
        *(p + (i / 8)) = num;
        num = 0;
    }
}