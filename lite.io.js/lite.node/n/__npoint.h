#ifndef __NPOINT_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __NPOINT_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <common.h>
#include <__nhttpd.h>
#include <__nserial.h>
#include <__nsocket.h>
#include <__nwebsocket.h>



typedef struct nArg
{
  uint32_t ecode;
  int32_t fd;
  uint8_t* bs;
  uint8_t* b;
  int32_t sz;
  int8_t* ext;
  int32_t asz;
} _nArg;

typedef struct iInfo
{
  uint8_t pth[128];
} _iInfo;


enum
{
  NHTTP,
  NHTTPD,
  NHTTPSD,
  NSERIAL,
  NSOCKET,
  NSHM,
  NTCP,
  NTCPD,
  NTCPSD,
  NWSC,
  NWSD,
  NMAX,
};

typedef struct _litePoint
{
  void*  hdl[NMAX];
  void*  obj;
  void*  arg;
  int32_t pids[64];
  int32_t (*fx[2])(void*,void*);
  void (*__loop[NMAX])(struct _litePoint*);
  int32_t (*__reader[NMAX])(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);
  int32_t (*__writer[NMAX])(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);
  int32_t (*__closer[NMAX])(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);
  int32_t (*__closefd[NMAX])(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);
  int32_t (*__iocall[NMAX])(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);
  int32_t  argc;
  int8_t** argv;

  #if __NSERIAL__
  cnserial      __serial;
  #endif

  #if __NHTTPD__
  cnhttpd       __httpd;
  #endif

  #if __NSOCKET__
  cnsocket      __socket;
  #endif

  #if __NWEBSOCKET__
  cnwebsocket   __websocket;
  #endif
} _litePoint;

#if __NHTTP__
#if defined __cplusplus
extern "C"
#endif
int32_t __liteio_http_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);

#if defined __cplusplus
extern "C"
#endif
int32_t __liteio_http_close(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);
#endif


#if __NHTTPD__
#if defined __cplusplus
extern "C"
#endif
int32_t __liteio_httpd_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);

#if defined __cplusplus
extern "C"
#endif
int32_t __liteio_httpd_close(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);
#endif


#if __NHTTPSD__
#if defined __cplusplus
extern "C"
#endif
int32_t __liteio_httpsd_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);

#if defined __cplusplus
extern "C"
#endif
int32_t __liteio_httpsd_close(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);
#endif




#if __NSERIAL__
#if defined __cplusplus
extern "C"
#endif
int32_t __liteio_serial_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);

#if defined __cplusplus
extern "C"
#endif
int32_t __liteio_serial_close(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);
#endif



#if __NSOCKET__
#if defined __cplusplus
extern "C"
#endif
int32_t __liteio_socket_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);

#if defined __cplusplus
extern "C"
#endif
int32_t __liteio_socket_close(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);
#endif



#if __NSHM__
#if defined __cplusplus
extern "C"
#endif
int32_t __liteio_shm_read(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);

#if defined __cplusplus
extern "C"
#endif
int32_t __liteio_shm_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);

#if defined __cplusplus
extern "C"
#endif
int32_t __liteio_shm_close(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);
#endif



#if __NTCP__
#if defined __cplusplus
extern "C"
#endif
int32_t __liteio_tcp_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);

#if defined __cplusplus
extern "C"
#endif
int32_t __liteio_tcp_close(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);
#endif


#if __NTCPD__
#if defined __cplusplus
extern "C"
#endif
int32_t __liteio_tcpd_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);

#if defined __cplusplus
extern "C"
#endif
int32_t __liteio_tcpd_close(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);
#endif




#if __NTCPSD__
#if defined __cplusplus
extern "C"
#endif
int32_t __liteio_tcpsd_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);

#if defined __cplusplus
extern "C"
#endif
int32_t __liteio_tcpsd_close(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);
#endif


#if __NWSC__
#if defined __cplusplus
extern "C"
#endif
int32_t __liteio_wsc_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);

#if defined __cplusplus
extern "C"
#endif
int32_t __liteio_wsc_close(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);
#endif


#if __NWSD__
#if defined __cplusplus
extern "C"
#endif
int32_t __liteio_wsd_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);

#if defined __cplusplus
extern "C"
#endif
int32_t __liteio_wsd_close(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);
#endif


#if defined __cplusplus
extern "C"
#endif
int32_t __liteio_call(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __initia(void** hdl, int32_t (*fx[])(void*,void*), void* o1, void* o2, int32_t argc, int8_t** argv);


#endif
