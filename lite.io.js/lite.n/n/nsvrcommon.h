#ifndef __NSVRCOMMON_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __NSVRCOMMON_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <imtif.h>
#include <liteio.h>

#if __WIN32__
#pragma pack(1)
#endif
typedef struct
#if __PACKED__
__attribute__((packed))
#endif
{
  uint32_t   a[4];  // fd sz  bp  fdp
} nClients;
#if __WIN32__
#pragma pack()
#endif


#endif
