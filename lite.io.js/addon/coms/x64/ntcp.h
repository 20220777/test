#if __NTCP__
#ifndef __NTCP_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __NTCP_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

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

  int8_t  conn_status;
} cntcp;
#if __WIN32__
#pragma pack()
#endif

#if defined __cplusplus
extern "C"
#endif
int32_t ntcp_closer(void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t ntcp_writer(void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);



#if defined __cplusplus
extern "C"
#endif
int32_t ntcp_open(cntcp* p);

#if defined __cplusplus
extern "C"
#endif
int32_t ntcp_close(cntcp* p);

#if defined __cplusplus
extern "C"
#endif
int32_t ntcp(struct cnLiteIO* p);

#if defined __cplusplus
extern "C"
#endif
void ntcp_loop(struct cnLiteIO* p);


#endif
#endif