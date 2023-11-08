/*****************************************************************************/
/*                                                                           */
/*            NCLab (Networked Control Lab) CORE version 1.0                 */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
/*  File Name         : icommon.h                                            */
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
#ifndef ____COMMON_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define ____COMMON_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#include <stdint.h>
#include <common.h>

#define DEBUG                      0


enum
{
  __CALLBACK_CONNECTED = 0,
  __CALLBACK_DISCONNECTED,
  __CALLBACK_OPEN,
  __CALLBACK_CLOSE,
  __CALLBACK_STATUS,
  __CALLBACK_READ,
  __CALLBACK_READFROM,
  __CALLBACK_URI,
  __CALLBACK_URI_NOT_FOUND,
  __CALLBACK_POST,
  __CALLBACK_GET,
  __CALLBACK_SSL_TLS,
  __CALLBACK_SSL_TLS_READ,
  __CALLBACK_SSL_TLS_WRITE,
  __CALLBACK_PRE_OPEN,
  __CALLBACK,
  __IO_I,
  __IO_O,
	__IO_CLOSE,
	__IO_ACCEPT,
  __WRITE,
  __FD,
  __FDSET,
  __FUNCTIONS,
};

enum
{
  __PARAM_MKEY = 0,
  __PARAM_MSIZE,
  __PARAM_COMPORT,
  __PARAM_BAUDRATE,
  __PARAM_STOPBIT,
  __PARAM_PARITYBIT,
  __PARAM_DATABIT,
  __PARAM_URL,
  __PARAM_HOME,
  __PARAM_INDEX,
  __PARAM_IP,
  __PARAM_PORT,
  __PARAM_CSTYPE,
  __PARAM_PROTOCOL,
  __PARAM_CASTTYPE,
  __PARAM_TIMEOUT,
  __PARAM_BLOCK,
  __PARAM_SYNC,
  __PARAM_MAX_FD,
  __PARAM_BUF_SZ,
  __PARAM_SECRETKEY,
  __PARAMS
};

#if __WIN32__
#pragma pack(1)
#endif
typedef struct
#if __LINUX__
__attribute((packed))
#endif
{
  void*    h;

  int32_t  fd;
  uint8_t* b;
  int32_t  sz;
  void*    o;
  int32_t (*f[__FUNCTIONS])(void*,int32_t,int8_t*,int32_t,void*,void*);

  #if __LINUX__
  pthread_mutex_t crit;
  #endif
  #if __WIN32__
  CRITICAL_SECTION  crit;
  #endif

}__vinfo;
#if __WIN32__
#pragma pack()
#endif


#define DIST_SZ         1024
#define MAX_DCOUNT      2
#define MAX_INDEX       8
#define REQ_SZ          1024
#define REQ_COUNT       64

#define __HTTPD_DEBUG__      0



#if 1
#if __WIN32__
#pragma pack(1)
#endif
typedef struct
#if __PACKED__
__attribute__((packed))
#endif
{
  int32_t  fd;
  uint32_t SR;
  //int8_t*  pfld;
  uint32_t hdrsz;
  __buffer  _buf;

  int8_t hdr[2*REQ_SZ];
  int8_t mthval[2][2*REQ_SZ];

}
__ioClientInfo;
#if __WIN32__
#pragma pack()
#endif
#endif

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



#endif



#if 0
@sc create WAAS_NODE binpath= "[EXEC] --m service --d WAAS_NODE --s WAAS_NODE --X [code.X.x86.dll] --l [LOG PATH] -- e d2" start= auto
@sc start WAAS_NODE

@sc stop WAAS_NODE
@sc delete WAAS_NODE
#endif



#if 0
#!/bin/bash

# cd /lib/systemd/system
# ln -s /usr/local/node/x32/node.c.service .
# systemctl status node.c.service
# systemctl daemon-reload
# systemctl enable node.c.service
# systemctl start node.c.service


# node.c.service
HOME=`pwd`
$HOME/pkg/node.c.$1.out --m console --d WAAS_NODE --s WAAS_NODE --X $HOME/pkg/code.X.$1.so --p $HOME/pkg/$1 --l /usr/local/node/log --e d7

#endif
