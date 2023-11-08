#if __NWSD__
#ifndef __NWSD_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __NWSD_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <imtif.h>
#include <liteio.h>
#include <nsvrcommon.h>

#if __WIN32__
#pragma pack(1)
#endif
typedef struct
{
  int8_t buf[4096];
  imtif _imtif;
  struct cnLiteIO* _ind;

  nClients* clnt;  

  int8_t  conn_status;
} cnwsd;
#if __WIN32__
#pragma pack()
#endif


#if defined __cplusplus
extern "C"
#endif
int32_t nwsd_closer(void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t nwsd_writer(void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);



#if defined __cplusplus
extern "C"
#endif
int32_t nwsd_open(cnwsd* p);

#if defined __cplusplus
extern "C"
#endif
int32_t nwsd_close(cnwsd* p);

#if defined __cplusplus
extern "C"
#endif
int32_t nwsd(struct cnLiteIO* p);

#if defined __cplusplus
extern "C"
#endif
int32_t nwsd_free(struct cnLiteIO* p);


#if defined __cplusplus
extern "C"
#endif
void nwsd_loop(struct cnLiteIO* p);


#endif
#endif