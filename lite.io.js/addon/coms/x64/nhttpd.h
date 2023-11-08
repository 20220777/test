#if __NHTTPD__
#ifndef __NHTTPD_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __NHTTPD_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <imtif.h>
#include <liteio.h>

#if __WIN32__
#pragma pack(1)
#endif
typedef struct
{
  int8_t buf[4096];
  imtif _imtif;
  struct cnLiteIO* _ind;
  struct iInfo  _info;
  int8_t  conn_status;
} cnhttpd;
#if __WIN32__
#pragma pack()
#endif

#if defined __cplusplus
extern "C"
#endif
int32_t nhttpd_closer(void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);

#if defined __cplusplus
extern "C"
#endif
int32_t nhttpd_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);

#if defined __cplusplus
extern "C"
#endif
int32_t nhttpd_writer(void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);

#if defined __cplusplus
extern "C"
#endif
int32_t nhttpd_open(cnhttpd* p);

#if defined __cplusplus
extern "C"
#endif
int32_t nhttpd_close(cnhttpd* p);

#if defined __cplusplus
extern "C"
#endif
int32_t nhttpd(struct cnLiteIO* p);

#if defined __cplusplus
extern "C"
#endif
int32_t nhttpd_free(struct cnLiteIO* p);

#if defined __cplusplus
extern "C"
#endif
void nhttpd_loop(struct cnLiteIO* p);

#endif
#endif