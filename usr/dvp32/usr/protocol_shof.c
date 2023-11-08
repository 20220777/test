#include <mcommon.h>
#include "protocol_shof.h"
#include <mprotocol.h>

#if 0
02 10 0F 01 00 42 00 42 00 42 01 03 0A 00 00 00 00 02 0A 03 0A
#endif

void* on_shof_protocol_check(char* b, int osz)
{
  int e = -1;

  if ( *(b+2)+5 == osz ) e = 0;

  return (void*)e;
}



#if 0
int on_shof_protocol_proc(int* SR, char* b, int sz, int* pos, char* out)
{
  int e = 0;
  int osz = 0;
  fprint_buffer("on_shof_protocol_proc",b,sz,0,16);
  e = on_protcol_check_HEX(&shof_protocol[0], shof_protocol[2], SR, b, sz, pos, out, &osz);

  fprint_buffer("on_shof_protocol_proc check",out,osz,0,16);
  if ( e > 0 )
  {
    WriteMessage(0, MAKELONG(BROADCAST, XWEBSOCKETD), out, osz);
  }

  return e;
}
#endif

int on_shof_protocol_proc(char* b, int sz, int* pos, char* out)
{
  int e = 0;
  int osz = 0;
	int i=0;
	char obuf[256][512];
	unsigned char oidx = 0;
  //fprint_buffer("on_shof_protocol_proc",b,sz,0,16);
	for ( ; ; )
	{
  	e = on_protcol_check(&shof_protocol[0], b+i, sz-i, pos, obuf[oidx], &osz, on_shof_protocol_check);

  	//fprint_buffer("on_shof_protocol_proc check",out,osz,0,16);
  	if ( e > 0 )
  	{
			i += e;
  		fprint_buffer("on_shof_protocol_proc check",obuf[oidx],osz,0,16);
    	//WriteMessage(0, MAKELONG(BROADCAST, XWEBSOCKETD), obuf[oidx], osz);
      PostMessage(gp->hwnd, XWM_TRANSFER, (WPARAM)sz, (LPARAM)b);

			oidx ++;
  	}
		else
		{
			break;
		}
	}

  return e;
}


int on_shof_protocol_request(char* b)
{
  static int equip_id = 0;
  int sz = 0;
  unsigned char crc;

  b[sz++] = 0x02;
  b[sz++] = 0xFF;//equip_id++;
  b[sz++] = 0x00;
  crc = (b[1]+b[2]);
  crc = (~crc) + 1;
  b[sz++] = crc;
  b[sz++] = 0x03;

  equip_id %= EQUIP_IDS_COUNT;

  return sz;
}
