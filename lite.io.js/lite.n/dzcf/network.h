#ifndef __NETWORK_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __NETWORK_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <imtif.h>
#include <liteio.h>

#if __WIN32__
#pragma pack(1)
#endif
typedef struct
{
  uint8_t sts;
} stNetwork;
#if __WIN32__
#pragma pack()
#endif

int32_t nNetworkInfo(int32_t fd, int8_t* uri0, int8_t* uri1, int32_t (*f)(void*,int32_t,int8_t*,int32_t,void*,void*),void* o);

#endif
