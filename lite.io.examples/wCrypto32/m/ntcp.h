#ifndef __NTCP_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __NTCP_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <stdint.h>
#include <imtif.h>

#if WIN32
#pragma pack(1)
#endif
typedef struct
{
  imtif _imtif;
  //struct cnLiteIO* _ind;

  int8_t  conn_status;
} cntcp;
#if WIN32
#pragma pack()
#endif

#if defined __cplusplus
extern "C"
#endif
int32_t ntcp_open(cntcp* p);

#endif
