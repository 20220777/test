#if __NSHM__
#ifndef __NSHM_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __NSHM_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <__nliteio.h>
#if WIN32
#pragma pack(1)
#endif
typedef struct
{
  _liteio  io;
} cnshm;
#if WIN32
#pragma pack()
#endif


#if defined __cplusplus
extern "C"
#endif
void* __nshm_get(void* h, int32_t offset);

#if defined __cplusplus
extern "C"
#endif
int32_t __nshm_read(void* h, uint8_t* b, int32_t sz);


#if defined __cplusplus
extern "C"
#endif
int32_t __nshm_write(void* h, uint8_t* b, int32_t sz);

#if defined __cplusplus
extern "C"
#endif
int32_t __nshm_open(cnshm* p);

#if defined __cplusplus
extern "C"
#endif
int32_t __nshm_close(cnshm* p);

#endif
#endif