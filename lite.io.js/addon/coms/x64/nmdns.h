#ifndef __NMDNS_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __NMDNS_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <imtif.h>
#include <liteio.h>


#if __WIN32__
#pragma pack(1)
#endif
typedef struct
{
  imtif _imtif;
  struct cnLiteIO* _ind;

  uint8_t pkt[128];
} cnmdns;
#if __WIN32__
#pragma pack()
#endif

#if defined __cplusplus
extern "C"
#endif
int32_t nmdns_open(cnmdns* p);

#if defined __cplusplus
extern "C"
#endif
int32_t nmdns_close(cnmdns* p);

#if defined __cplusplus
extern "C"
#endif
int32_t nmdns(struct cnLiteIO* p);

#if defined __cplusplus
extern "C"
#endif
void nmdns_loop(struct cnLiteIO* p);


#endif
