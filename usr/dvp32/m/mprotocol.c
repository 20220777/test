#include "mprotocol.h"
#include <mcommon.h>


/***
02 10 0F 01  00 42 00 42
00 42 01 03  0A 00 00 00
00 02 0A 03  0A
***/
int on_protcol_check_HEX(unsigned char* se, int maxsz, unsigned int* SR, char* b, int sz, int* pos, char* o, int* osz)
{
  int i = 0;
  int e = -1;
  //printf(" maxsz -> %d\r\n", maxsz);
  //printf(" sz    -> %d\r\n", sz);
  for (i = 0; i < sz; i++)
  {
    //printf(" %3d -> %3d,  %08X  ---> [%02X] \r\n", i, *pos, *SR, *(b+i) );
    if (((*SR & 0x80000001) == 0) && (*(b + i) == *(se + 0)))
    {
      *pos = 0;
      *SR |= 0x80000000;
    }

    if ((*SR) & 0x80000000)
    {
      *(o + (*pos)) = *(b + i);
      (*pos)++;
      *osz = *pos;
    }

    if (((*SR) & 0x80000000) && ((*(b + i) == *(se + 1)) && (*pos) == maxsz))
    {
      *SR |= 0x00000001;
    }
  }
  *pos %= maxsz;

  if (((*SR) & 0x80000001) == 0x80000001)
  {
    e = *pos;
    *pos = 0;
    *SR &= 0x7FFFFFFE;
  }
  return e;
}



int on_protcol_check(unsigned char* se, char* b, int sz, int* pos, char* o, int* osz, void* cbf(char*, int))
{
  int i = 0;
  int e = -1;
  int _pos = 0;

  #if DEBUG_LOCAL
  {
    char temp[1024];
    //fprint_buffer("on_protocol_check buffer", b, sz, 0, 16);
    fprint_raw_buffer("on_protocol_check buffer", b, sz, temp);
    OutputDebugString(temp);
    OutputDebugString("\r\n");
  }
  #endif



  for (i = 0; i < sz; i++)
  {
    for (; ((*pos) == 0) && (*(b + i) != 0) && (*(b + i) != *(se + 0)); i++);

    #if DEBUG_LOCAL
    {
      char temp[1024];
      //printf("[ %4d -> %4d, %02X ]\r\n", i, *pos, (unsigned char)*(b + i));
      sprintf(temp, "[ %4d -> %4d, %4d, %02X ]", i, *pos, _pos, (unsigned char)*(b + i));
      OutputDebugString(temp);
    }
    #endif

    if ((*pos) == 0)
    {
      if (*(b + i) == *(se + 0))
      {
        *(o + *(pos)) = *(b + i);
        _pos = i;
        (*pos)++;
        #if DEBUG_LOCAL
        OutputDebugString("STX \r\n");
        #endif
        continue;
      }
    }

    if (*pos)
    {
      *(o + *(pos)) = *(b + i);
      (*pos)++;
      if ( *(b + i) == *(se + 1) )
      {
        e = cbf(o, (*pos));
        if ( e == 0 )
        {

          #if DEBUG_LOCAL
          {
            char temp[1024];
            sprintf(temp, "ETX %d\r\n", (*pos));
            OutputDebugString(temp);
          }
          #endif

          #if DEBUG_LOCAL
          {
            char temp[1024];
            fprint_raw_buffer("on_protocol_check ETX", o, *pos, temp);
            OutputDebugString(temp);
            OutputDebugString("\r\n");
          }
          #endif

          //e = *pos;
          i++;
          e = i;
          (*osz) = *pos;
          (*pos) = 0;
          break;
        }
        else if ( e == -2 )
        {
          //i++;
          //(*osz) = *pos;
          (*pos) = 0;
        }
      }
    }
    #if DEBUG_LOCAL
    OutputDebugString("\r\n");
    #endif
  }


  #if  DEBUG_LOCAL
  //printf("[ %4d -> %4d, %4d, %4d ]\r\n", i, e, *pos, *osz);
  {
    char temp[1024];
    sprintf(temp, "[ %4d -> %4d, %4d, %4d, %4d, %4d ]\r\n", i, e, *pos, _pos, *osz, sz);
    OutputDebugString(temp);
  }
  #endif


  if (e < 0)
  {
    int oi = 0;
    for (i = _pos, oi = 0; oi < sz; oi++, i++)
    {
      *(o + oi) = *(b + i);
    }
    //(*pos)++;
    #if DEBUG_LOCAL
    {
      char temp[1024];
      fprint_raw_buffer("on_protocol_check ******", o, sz, temp);
      OutputDebugString(temp);
      OutputDebugString("\r\n");
    }
    #endif
  }
  return e;
}




#if 0
int on_protcol_check(unsigned char* se, char* b, int sz, int* pos, char* o, int* osz, void* cbf(char*, int))
{
  int i = 0;
  int e = -1;
  int _pos = 0;

#if DEBUG_LOCAL
  {
    char temp[1024];
    //fprint_buffer("on_protocol_check buffer", b, sz, 0, 16);
    fprint_raw_buffer("on_protocol_check buffer", b, sz, temp);
    OutputDebugString(temp);
    OutputDebugString("\r\n");
  }
#endif

  for (i = 0; i < sz; i++)
  {
#if DEBUG_LOCAL
    {
      char temp[1024];
      //printf("[ %4d -> %4d, %02X ]\r\n", i, *pos, (unsigned char)*(b + i));
      sprintf(temp, "[ %4d -> %4d, %4d, %02X ]", i, *pos, _pos, (unsigned char)*(b + i));
      OutputDebugString(temp);
    }
#endif
    if ((*pos) == 0)
    {
      if (*(b + i) == *(se + 0))
      {
        *(o + *(pos)) = *(b + i);
        _pos = i;
        (*pos)++;
#if DEBUG_LOCAL
        OutputDebugString("STX \r\n");
#endif
        continue;
      }
    }

    if (*pos)
    {
      *(o + *(pos)) = *(b + i);
      (*pos)++;
      if (*(b + i) == *(se + 1))
      {
        if (cbf(o, (*pos)) == 0)
        {

#if DEBUG_LOCAL
          {
            char temp[1024];
            sprintf(temp, "ETX %d\r\n", (*pos));
            OutputDebugString(temp);
          }
#endif

#if DEBUG_LOCAL
          {
            char temp[1024];
            fprint_raw_buffer("on_protocol_check ETX", o, *pos, temp);
            OutputDebugString(temp);
            OutputDebugString("\r\n");
          }
#endif

          //e = *pos;
          i++;
          e = i;
          (*osz) = *pos;
          (*pos) = 0;
          break;
        }
      }
    }
#if DEBUG_LOCAL
    OutputDebugString("\r\n");
#endif
  }


#if  DEBUG_LOCAL
  //printf("[ %4d -> %4d, %4d, %4d ]\r\n", i, e, *pos, *osz);
  {
    char temp[1024];
    sprintf(temp, "[ %4d -> %4d, %4d, %4d, %4d, %4d ]\r\n", i, e, *pos, _pos, *osz, sz);
    OutputDebugString(temp);
  }
#endif


  if (e < 0)
  {
    int oi = 0;
    for (i = 0, oi = 0; oi < sz; oi++, i++)
    {
      *(o + oi) = *(b + i);
    }
    //(*pos)++;
#if DEBUG_LOCAL
    {
      char temp[1024];
      fprint_raw_buffer("on_protocol_check ******", o, sz, temp);
      OutputDebugString(temp);
      OutputDebugString("\r\n");
    }
#endif
  }
  return e;
}
#endif

#if 0
int on_protcol_check(unsigned char* se, char* b, int sz, int* pos, char* o, int* osz, void* cbf(char*, int))
{
  int i = 0;
  int e = -1;
  {
    char tmp[4096];
    fprint_raw_buffer("bbuf", b, sz, tmp);
    OutputDebugString(tmp);
    OutputDebugString("\r\n");
  }

  if ( *(pos+0) )
  {
    char tmp[4096];
    fprint_raw_buffer("****", o - *(pos + 0), 32, tmp);
    OutputDebugString(tmp);
    OutputDebugString("\r\n");
  }


  for (i = 0; i < sz; i++)
  {
    if ((*(pos+0) == 0) && (*(b + i) == *(se + 0)))
    {
      *(pos + 0) = 0;
      *(o + *(pos + 0)) = *(b + i);
      (*(pos + 0))++;
      continue;
    }

    if (*(pos+0))
    {
      *(o + *(pos + 0)) = *(b + i);
      (*(pos + 0))++;

      if (*(b + i) == *(se + 1))
      {
        if (cbf(o, *(pos + 0)) == 0)
        {
          e = ++i;
          *osz = *(pos + 0);
          *(pos + 0) = 0;
          break;
        }
      }
    }
  }


  if ( i && *(pos + 0))
  {
    int oi = 0;
    for ( i = *(pos + 0), oi = 0 ;oi<sz ; oi++, i++)
    {
      *(o+oi) = *(b+i);
    }
    //*(pos + 0) = _pos;

    {
      char tmp[4096];
      fprint_raw_buffer("obuf", o, *osz, tmp);
      OutputDebugString(tmp);
      OutputDebugString("\r\n");
    }

  }


  return e;
}
#endif