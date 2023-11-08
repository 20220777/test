#include <xm.h>
#include "protocol_jmt.h"
#include <mprotocol.h>
#include <util.h>


void* on_jmt_protocol_check(void* o, int8_t* b, int32_t sz, int32_t code)
{
  int32_t e = -1;
  CodeX* p = (CodeX*)o;

	if ( code == 0 )
	{
    #if DEBUG_LOCAL
		display("on_jmt_protocol_check",b,sz);
    #endif
  	p->callback(p->obj, MAKELONG(READ, XSERIAL), (void*)b, (void*)sz);

	}
  else
  {
    e = 0;
  }
  return (void*)e;
}


uint8_t jmt_hex(uint8_t* in)
{
  uint8_t v = 0;
  if ( *(in+0) == '3' ) 
  {
    if ( (*(in+1)>='0') && (*(in+1)<='9') ) 
    {
      v = *(in+1)-0x30;
    }
  }
  else if ( *(in+0) == '4' ) 
  {
    if ( (*(in+1)>='1') && (*(in+1)<='6') ) 
    {
      v = *(in+1)-0x30 + 0x0A;
    }
  }

  return v;
}


uint8_t jmt_hex_strm(int8_t* in, int32_t sz, int8_t* out)
{
  int32_t i = 0;
  int32_t j = 0;
  uint8_t v[2] = {0};
  for ( i=0, j=0 ; i<sz ; i++ )
  {
    if ( (*(in+i)>='0') && (*(in+i)<='9') )
    {
      *(out+j) = *(in+i)-0x30;
      j++;
    }
    else if ( (*(in+i)>='A') && (*(in+i)<='F') )
    {
      *(out+j) = *(in+i)-0x41+0x0A;
      j++;
    }
  }
  *(out+j) = 0;
  return j;
}
