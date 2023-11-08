#ifndef __MSOCKET_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __MSOCKET_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <cCommon.h>
#include <mtifSocket.h>

#define MAX_BUF_SZ            1024
#define MAX_BUF_COUNT         64
#define SOCKET_BUF_SFT        6
typedef struct
{
	int fd;
	unsigned int ip;
	unsigned short port;
	unsigned char pb[2048];
  unsigned char b[MAX_BUF_COUNT][MAX_BUF_SZ];
  unsigned int bi;
  unsigned int bpos;  /// 1:b,  0:pb
  xREG         REG;
}mtifSocketPackInfo;

typedef struct
{
	mtifSocketPackInfo info[FD_SETSIZE];
}mtifSocketPack;

typedef struct
{
  int   a[4];
} fdsetex;


typedef struct
{
  fdsetex*       fds;
  xREG           REG;
  unsigned char  mode;
  unsigned char  b[MAX_BUF_COUNT][MAX_BUF_SZ];
  int fd;
  XMTIFSocket    m;
	mtifSocketPack pack;
  void*          info;
  CRITICAL_SECTION crit;
}mtifSocket;


#endif
