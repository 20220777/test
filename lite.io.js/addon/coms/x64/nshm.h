#if __NSHM__
#ifndef __NSHM_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __NSHM_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <imtif.h>
#include <liteio.h>

#define __SHM_BSIZE__    8192

#if __WIN32__
#pragma pack(1)
#endif
typedef struct
{
  uint8_t* p;
  //int8_t buf[__SHM_BSIZE__];
  imtif _imtif;
  struct cnLiteIO* _ind;
  struct iInfo  _info;
} cnshm;
#if __WIN32__
#pragma pack()
#endif


#if defined __cplusplus
extern "C"
#endif
int32_t nshm_closer(void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t nshm_writer(void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);

#if defined __cplusplus
extern "C"
#endif
int32_t nshm_reader(void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);



#if defined __cplusplus
extern "C"
#endif
int32_t nshm_read(void* h, int8_t* b, int32_t sz);


#if defined __cplusplus
extern "C"
#endif
int32_t nshm_write(void* h, int8_t* b, int32_t sz);

#if defined __cplusplus
extern "C"
#endif
int32_t nshm_open(cnshm* p);

#if defined __cplusplus
extern "C"
#endif
int32_t nshm_close(cnshm* p);

#if defined __cplusplus
extern "C"
#endif
int32_t nshm(struct cnLiteIO* p);

#if defined __cplusplus
extern "C"
#endif
int32_t nshm_free(struct cnLiteIO* p);

#if defined __cplusplus
extern "C"
#endif
void nshm_loop(struct cnLiteIO* p);

#endif
#endif