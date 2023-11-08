#ifndef __NLITEIO_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __NLITEIO_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <common.h>
#include <__common.h>

enum
{
  HTTP_URL = 0,
  HTTP_PORT,
  HTTP_HOME,
  HTTP_INDEX,
  SOCKET_IP = 0,
  SOCKET_PORT,
  SOCKET_CSTYPE,
  SOCKET_PROTOCOL,
  SOCKET_CASTTYPE,
  SERIAL_PORT = 0,
  SERIAL_BAUDRATE,
  SERIAL_DATABIT,
  SERIAL_STOPBIT,
  SERIAL_PARITYBIT,
  SIZE_OF_BUFFER,
  MAX_INFO=32,
};



#if WIN32
#pragma pack(1)
#endif
typedef struct
{
  void*    h;
  int32_t  argc;
  int8_t   argv[MAX_INFO][32];

  int32_t  fd;
  int8_t buf[4096];

  void* (*__f[__FUNCTIONS])(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);
  void* __o;

} _liteio;
#if WIN32
#pragma pack()
#endif

#endif