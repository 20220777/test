#if __NTCPD__
#ifndef __NTCPD_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __NTCPD_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <imtif.h>
#include <liteio.h>

#if __WIN32__
#pragma pack(1)
#endif
typedef struct
{
  imtif _imtif;
  struct cnLiteIO* _ind;

  uint8_t b[4096];

  int8_t  conn_status;
} cntcpd;
#if __WIN32__
#pragma pack()
#endif


#if defined __cplusplus
extern "C"
#endif
int32_t ntcpd_closer(void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t ntcpd_writer(void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);




#if defined __cplusplus
extern "C"
#endif
int32_t ntcpd_open(cntcpd* p);

#if defined __cplusplus
extern "C"
#endif
int32_t ntcpd_close(cntcpd* p);

#if defined __cplusplus
extern "C"
#endif
int32_t ntcpd(struct cnLiteIO* p);

#if defined __cplusplus
extern "C"
#endif
void ntcpd_loop(struct cnLiteIO* p);


#endif
#endif