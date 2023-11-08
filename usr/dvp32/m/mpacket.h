#ifndef __MPACKET_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __MPACKET_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <cCommon.h>
#include <mtifPacket.h>

#define MAX_BUF_SZ            1024
#define PACKET_BUF_SFT        10

typedef struct
{
  xREG           REG;
  int            fd;
  unsigned char  b[MAX_BUF_SZ];
  XMTIFPacket    m;
  void* info;
}mtifPacket;


#endif
