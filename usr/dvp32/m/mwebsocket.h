#ifndef __MWEBSOCKET_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __MWEBSOCKET_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <cCommon.h>
#include <mtifWebSocket.h>

#define MAX_FD                1024
#define WS_MAX_BUF_SZ         1024
#define WS_MAX_BUF_COUNT      64
#define WEBSOCKET_BUF_SFT     0x0A


typedef struct
{
	int fd;
	unsigned int ip;
	unsigned short port;
	unsigned char b[WS_MAX_BUF_COUNT][WS_MAX_BUF_SZ];
  xREG          REG;
}mtifWebSocketPackInfo;

typedef struct
{
	mtifWebSocketPackInfo info[MAX_FD];
}mtifWebSocketPack;

typedef struct
{
  int   a[4];  // fd sz  bp  fdp
} wsFDSet;

typedef struct
{
  int   fd;
} wsClientSet;

typedef struct
{
  xREG          REG;

  unsigned char mode;
  unsigned char b[WS_MAX_BUF_COUNT][WS_MAX_BUF_SZ];
  //unsigned char cb[WS_MAX_BUF_COUNT][WS_MAX_BUF_SZ];
  unsigned char iobuf[WS_MAX_BUF_SZ];
  int hdrsz;
  int fd;
  XMTIFWebSocket   m;

  wsFDSet*        fds;
  wsClientSet*    cs;

	mtifWebSocketPack pack;
  void* info;
  CRITICAL_SECTION crit;
}mtifWebSocket;


#endif
