#if __NTCPSD__
#ifndef __NTCPSD_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __NTCPSD_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <imtif.h>
#include <liteio.h>

#if __WIN32__
#pragma pack(1)
#endif
typedef struct
{
  imtif _imtif;
  struct cnLiteIO* _ind;

  int8_t  conn_status;
} cntcpsd;
#if __WIN32__
#pragma pack()
#endif

#if defined __cplusplus
extern "C"
#endif
int32_t ntcpsd_closer(void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t ntcpsd_writer(void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);



#if defined __cplusplus
extern "C"
#endif
int32_t ntcpsd_open(cntcpsd* p);

#if defined __cplusplus
extern "C"
#endif
int32_t ntcpsd_close(cntcpsd* p);

#if defined __cplusplus
extern "C"
#endif
int32_t ntcpsd(struct cnLiteIO* p);

#if defined __cplusplus
extern "C"
#endif
void ntcpsd_loop(struct cnLiteIO* p);


#endif
#endif