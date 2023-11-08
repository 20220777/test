/*****************************************************************************/
/*                                                                           */
/*            NCLab (Networked Control Lab) CORE version 1.0                 */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
/*  File Name         : imtif.h                                              */
/*                                                                           */
/*  Description       : This file contains all the necessary constants ,     */
/*                      type definitions according to CAST specifications,	 */
/*                      common system headers.                               */
/*                                                                           */
/*                                                                           */
/*  Issues / Problems : None                                                 */
/*                                                                           */
/*  Revision History  :                                                      */
/*                                                                           */
/*        DD MM YYYY   Author(s)        Changes (Describe the changes made)  */
/*        18 03 2021   Shin Seunghyeok  Draft                                */
/*                                                                           */
/*****************************************************************************/
#ifndef __IMTIF_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __IMTIF_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#include <stdint.h>
#include <icommon.h>
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////                                                                   //////
//////                                                                   //////
//////                          User Variable                            //////
//////                                                                   //////
//////                                                                   //////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************/
/*****************************************************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*****************************                ********************************/
/*******************************            **********************************/
/*********************************        ************************************/
/************************************   **************************************/
/************************************* ***************************************/
/*****************************************************************************/
enum
{
  IMTIF_CALLBACK_CONNECTED = 0,
  IMTIF_CALLBACK_DISCONNECTED,
  IMTIF_CALLBACK_OPEN,
  IMTIF_CALLBACK_CLOSE,
  IMTIF_CALLBACK_READ,
  IMTIF_CALLBACK_READFROM,
  IMTIF_CALLBACK_URI,
  IMTIF_CALLBACK_URI_NOT_FOUND,
  IMTIF_CALLBACK_POST,
  IMTIF_CALLBACK_GET,
  IMTIF_CALLBACK_SSL_TLS,
  IMTIF_CALLBACK_SSL_TLS_READ,
  IMTIF_CALLBACK_SSL_TLS_WRITE,
  IMTIF_CALLBACK_PRE_OPEN,
  IMTIF_CALLBACK,
  IMTIF_WRITE,
  IMTIF_FD,
  IMTIF_FDSET,
  IMTIF_FUNCTIONS,
};


#if __WIN32__
#pragma pack(1)
#endif
typedef struct
#if __PACKED__
__attribute__((packed))
#endif
{
  int32_t   a[4];  // fd sz  bp  fdp
} __imtifFDSET;
#if __WIN32__
#pragma pack()
#endif


#if __WIN32__
#pragma pack(1)
#endif
typedef struct
#if __PACKED__
__attribute__((packed))
#endif
{
  int32_t max;
  __imtifFDSET* fds;
} imtifFDSET;
#if __WIN32__
#pragma pack()
#endif

#if __WIN32__
#pragma pack(1)
#endif
typedef struct
#if __PACKED__
__attribute__((packed))
#endif
{
  void* h;
  void* o;
  int32_t (*callback[IMTIF_CALLBACK])(void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);
  void* (*log)(int8_t* pfx, const int8_t* fmt,...);

  imtifFDSET fdset;
} imtif;
#if __WIN32__
#pragma pack()
#endif



///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////                                                                   //////
//////                                                                   //////
//////                            Socket                                 //////
//////                                                                   //////
//////                                                                   //////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************/
/*****************************************************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*****************************                ********************************/
/*******************************            **********************************/
/*********************************        ************************************/
/************************************   **************************************/
/************************************* ***************************************/
/*****************************************************************************/
#if __IO__
#if __STATIC__
#if defined __cplusplus
extern "C"
#endif
int32_t __socket_fd        (void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __socket_fdset     (void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __socket_read      (void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __socket_readfrom  (void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __socket_write     (void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __socket_writeto   (void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __socket_set_reader(void* h, uint8_t* mode, int32_t (*f[])(void*,int32_t,int8_t*,int32_t,void*,void*), void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __socket_open      (void** h, int8_t* a, int8_t* b, int32_t sz, int32_t (*f[])(void*,int32_t,int8_t*,int32_t,void*,void*), void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __socket_close     (void** h);
#endif
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////                                                                   //////
//////                                                                   //////
//////                              HTTP                                 //////
//////                                                                   //////
//////                                                                   //////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************/
/*****************************************************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*****************************                ********************************/
/*******************************            **********************************/
/*********************************        ************************************/
/************************************   **************************************/
/************************************* ***************************************/
/*****************************************************************************/
#if __IO__
#if __STATIC__
#if defined __cplusplus
extern "C"
#endif
int32_t __http_fd        (void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __http_fdset     (void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __http_read      (void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __http_write     (void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __http_set_reader(void* h, uint8_t* mode, int32_t (*f[])(void*,int32_t,int8_t*,int32_t,void*,void*), void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __http_open      (void** h, int8_t* a, int8_t* b, int32_t sz, int32_t (*f[])(void*,int32_t,int8_t*,int32_t,void*,void*), void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __http_close     (void** h);
#endif
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////                                                                   //////
//////                                                                   //////
//////                              HTTPD                                //////
//////                                                                   //////
//////                                                                   //////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************/
/*****************************************************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*****************************                ********************************/
/*******************************            **********************************/
/*********************************        ************************************/
/************************************   **************************************/
/************************************* ***************************************/
/*****************************************************************************/
#if __IO__
#if __STATIC__
#if defined __cplusplus
extern "C"
#endif
int32_t __httpd_fd        (void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __httpd_fdset     (void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __httpd_read      (void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __httpd_write     (void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __httpd_set_reader(void* h, uint8_t* mode, int32_t (*f[])(void*,int32_t,int8_t*,int32_t,void*,void*), void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __httpd_open      (void** h, int8_t* a, int8_t* b, int32_t sz, int32_t (*f[])(void*,int32_t,int8_t*,int32_t,void*,void*), void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __httpd_close     (void** h);


#if defined __cplusplus
extern "C"
#endif
int32_t __httpd_close_fd  (void* h, int32_t fd);
#endif
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////                                                                   //////
//////                                                                   //////
//////                              HTTPS                                //////
//////                                                                   //////
//////                                                                   //////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************/
/*****************************************************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*****************************                ********************************/
/*******************************            **********************************/
/*********************************        ************************************/
/************************************   **************************************/
/************************************* ***************************************/
/*****************************************************************************/
#if __IO__
#if __SSL_TLS__
#if __STATIC__
#if defined __cplusplus
extern "C"
#endif
int32_t __httpsd_fd        (void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __httpsd_fdset     (void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __httpsd_read      (void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __httpsd_write     (void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __httpsd_set_reader(void* h, uint8_t* mode, int32_t (*f[])(void*,int32_t,int8_t*,int32_t,void*,void*), void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __httpsd_open      (void** h, int8_t* a, int8_t* b, int32_t sz, int32_t (*f[])(void*,int32_t,int8_t*,int32_t,void*,void*), void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __httpsd_close     (void** h);
#endif
#endif
#endif
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////                                                                   //////
//////                                                                   //////
//////                           WebSocket                               //////
//////                                                                   //////
//////                                                                   //////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************/
/*****************************************************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*****************************                ********************************/
/*******************************            **********************************/
/*********************************        ************************************/
/************************************   **************************************/
/************************************* ***************************************/
/*****************************************************************************/
#if __IO__
#if __STATIC__
#if defined __cplusplus
extern "C"
#endif
int32_t __ws_fd        (void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __ws_fdset     (void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __ws_read      (void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __ws_write     (void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __ws_set_reader(void* h, uint8_t* mode, int32_t (*f[])(void*,int32_t,int8_t*,int32_t,void*,void*), void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __ws_open      (void** h, int8_t* a, int8_t* b, int32_t sz, int32_t (*f[])(void*,int32_t,int8_t*,int32_t,void*,void*), void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __ws_close     (void** h);
#endif
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////                                                                   //////
//////                                                                   //////
//////                             Serial                                //////
//////                                                                   //////
//////                                                                   //////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************/
/*****************************************************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*****************************                ********************************/
/*******************************            **********************************/
/*********************************        ************************************/
/************************************   **************************************/
/************************************* ***************************************/
/*****************************************************************************/
#if __IO__
#if __STATIC__
#if defined __cplusplus
extern "C"
#endif
int32_t __serial_fd        (void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __serial_read      (void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __serial_write     (void* h, int32_t fd, int8_t* b, int32_t sz, void* moreinfo, void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __serial_set_reader(void* h, uint8_t* mode, int32_t (*f[])(void*,int32_t,int8_t*,int32_t,void*,void*), void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __serial_open      (void** h, int8_t* a, int8_t* b, int32_t sz, int32_t (*f[])(void*,int32_t,int8_t*,int32_t,void*,void*), void* o);


#if defined __cplusplus
extern "C"
#endif
int32_t __serial_close     (void** h);
#endif
#endif


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////                                                                   //////
//////                                                                   //////
//////                              SHM                                  //////
//////                                                                   //////
//////                                                                   //////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************/
/*****************************************************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*****************************                ********************************/
/*******************************            **********************************/
/*********************************        ************************************/
/************************************   **************************************/
/************************************* ***************************************/
/*****************************************************************************/
#if __IO__
#if __STATIC__
#if defined __cplusplus
extern "C"
#endif
int32_t __shm_get(void* h, void** p);


#if defined __cplusplus
extern "C"
#endif
int32_t __shm_read(void* h, int8_t* b, int32_t sz);


#if defined __cplusplus
extern "C"
#endif
int32_t __shm_write(void* h, int8_t* b, int32_t sz);


#if defined __cplusplus
extern "C"
#endif
int32_t __shm_open(void** h, int8_t* argv);


#if defined __cplusplus
extern "C"
#endif
int32_t __shm_close(void** h);
#endif
#endif




#endif
