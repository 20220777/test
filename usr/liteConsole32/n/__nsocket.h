#if __NSOCKET__
#ifndef __NSOCKET_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __NSOCKET_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <__nliteio.h>
#include <imtif.h>

#define MAX_CLIENT    256
typedef struct
{
  int32_t fds[MAX_CLIENT];
  _liteio  io;
  imtif  _imtif;
} cnsocket;

#if defined __cplusplus
extern "C"
#endif
int32_t nsocket_closer(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t nsocket_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);



#if defined __cplusplus
extern "C"
#endif
int32_t nsocket_open(cnsocket* p);

#if defined __cplusplus
extern "C"
#endif
int32_t nsocket_close(cnsocket* p);



#endif
#endif