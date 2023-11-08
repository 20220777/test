#ifndef __NZIGBEE_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __NZIGBEE_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <imtif.h>
#include <liteio.h>

#if __WIN32__
#pragma pack(1)
#endif
typedef struct
{
  imtif _imtif;
  struct cnLiteIO* _ind;

  int32_t fd;
  uint8_t buf[128];
  int32_t sz;
  uint8_t SR;
  int32_t idx;
} cnzigbee;
#if __WIN32__
#pragma pack()
#endif

#if defined __cplusplus
extern "C"
#endif
int32_t nzigbee_open(cnzigbee* p);

#if defined __cplusplus
extern "C"
#endif
int32_t nzigbee_close(cnzigbee* p);

#if defined __cplusplus
extern "C"
#endif
int32_t nzigbee(struct cnLiteIO* p);

#if defined __cplusplus
extern "C"
#endif
void nzigbee_loop(struct cnLiteIO* p);


#endif
