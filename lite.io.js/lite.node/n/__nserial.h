#if __NSERIAL__
#ifndef __NSERIAL_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __NSERIAL_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <__nliteio.h>
#if WIN32
#pragma pack(1)
#endif
typedef struct
{
  _liteio  io;
} cnserial;
#if WIN32
#pragma pack()
#endif

#if defined __cplusplus
extern "C"
#endif
int32_t __nserial_closer(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __nserial_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);

#if defined __cplusplus
extern "C"
#endif
int32_t __nserial_open(cnserial* p);

#if defined __cplusplus
extern "C"
#endif
int32_t __nserial_close(cnserial* p);

#endif
#endif