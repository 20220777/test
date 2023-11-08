#include <util.h>
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




///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////                                                                   //////
//////                                                                   //////
//////                           From KISA                               //////
//////                                                                   //////
//////                                                                   //////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************/
/*****************************************************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*****************************                ********************************/
/*******************************            **********************************/
/*********************************        ************************************/
/************************************   **************************************/
/************************************* ***************************************/
/*****************************************************************************/





int asc2hex(unsigned char *dst, const char *src)
{
    unsigned char temp = 0x00;
    int i = 0;

    while (src[i] != 0x00)
    {
        temp = 0x00;

        if ((src[i] >= 0x30) && (src[i] <= 0x39))
            temp = src[i] - '0';
        else if ((src[i] >= 0x41) && (src[i] <= 0x5A))
            temp = src[i] - 'A' + 10;
        else if ((src[i] >= 0x61) && (src[i] <= 0x7A))
            temp = src[i] - 'a' + 10;
        else
            temp = 0x00;

        (i & 1) ? (dst[i >> 1] ^= temp & 0x0F) : (dst[i >> 1] = 0, dst[i >> 1] = temp << 4);

        i++;
    }

    return ((i + 1) / 2);
}


void print_title(const char *title)
{
    printf("================================================\n");
    printf("  %s\n", title);
    printf("================================================\n");
}


void print_hex(const char *valName, const unsigned char *data, const int dataLen)
{
    int i = 0;

    printf("%s [%dbyte] :", valName, dataLen);
    for (i = 0; i < dataLen; i++)
    {
        if (!(i & 0x0F))
            printf("\n");
        printf(" %02X", data[i]);
    }
    printf("\n");
}

void print_result(const char *func, int ret)
{
    if (ret)
    {
        printf("================================================\n");
        printf("  %s Failure!\n", func);
        printf("================================================\n");

        exit(0);
    }
    else
    {
        printf("================================================\n");
        printf("  %s Success!\n", func);
        printf("================================================\n");
    }
}



void Byte2Word(unsigned int *dst, const unsigned char *src, const int srcLen)
{
    int i = 0;
    int remain = 0;

    for (i = 0; i < srcLen; i++)
    {
        remain = i & 3;

        if (remain == 0)
            dst[i >> 2]  = ((unsigned int)src[i] << 24);
        else if (remain == 1)
            dst[i >> 2] ^= ((unsigned int)src[i] << 16);
        else if (remain == 2)
            dst[i >> 2] ^= ((unsigned int)src[i] << 8);
        else
            dst[i >> 2] ^= ((unsigned int)src[i] & 0x000000FF);
    }
}

void Word2Byte(unsigned char *dst, const unsigned int *src, const int srcLen)
{
    int i = 0;
    int remain = 0;

    for (i = 0; i < srcLen; i++)
    {
        remain = i & 3;

        if (remain == 0)
            dst[i] = (unsigned char)(src[i >> 2] >> 24);
        else if (remain == 1)
            dst[i] = (unsigned char)(src[i >> 2] >> 16);
        else if (remain == 2)
            dst[i] = (unsigned char)(src[i >> 2] >> 8);
        else
            dst[i] = (unsigned char) src[i >> 2];
    }
}

