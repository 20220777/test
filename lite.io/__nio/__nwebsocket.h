#if __NWEBSOCKET__
#ifndef __NWEBSOCKET_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __NWEBSOCKET_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <__nliteio.h>

typedef struct
{
  _liteio  io;
  int32_t fds[MAX_CLIENT];
  uint8_t b[MAX_CLIENT][2][1024];
  __buffer*   buf;
} cnwebsocket;

#if defined __cplusplus
extern "C"
#endif
int32_t __nwebsocket_closer(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __nwebsocket_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);



#if defined __cplusplus
extern "C"
#endif
int32_t __nwebsocket_open(cnwebsocket* p);

#if defined __cplusplus
extern "C"
#endif
int32_t __nwebsocket_close(cnwebsocket* p);

#if defined __cplusplus
extern "C"
#endif
int32_t __nwebsocket_close_fd(cnwebsocket* p, int32_t fd);


#endif
#endif