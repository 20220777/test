#if __NHTTPD__
#ifndef __NHTTPD_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __NHTTPD_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <__nliteio.h>

#define MAX_CLIENT    256
typedef struct
{
  int32_t fds[MAX_CLIENT];
  _liteio  io;
} cnhttpd;

#if defined __cplusplus
extern "C"
#endif
int32_t __nhttpd_closer(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __nhttpd_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);



#if defined __cplusplus
extern "C"
#endif
int32_t __nhttpd_open(cnhttpd* p);

#if defined __cplusplus
extern "C"
#endif
int32_t __nhttpd_close(cnhttpd* p);

#if defined __cplusplus
extern "C"
#endif
int32_t __nhttpd_close_fd(cnhttpd* p, int32_t fd);



#endif
#endif