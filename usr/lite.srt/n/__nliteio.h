#ifndef __NLITEIO_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __NLITEIO_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <stdint.h>
#include <common.h>

#if WIN32
#pragma pack(1)
#endif
typedef struct
{
  int32_t  argc;
  int8_t   argv[16][32];

  int32_t  fd;
  int8_t buf[4096];

  void* (*__f[IMTIF_FUNCTIONS])(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);

} _liteio;
#if WIN32
#pragma pack()
#endif

#endif