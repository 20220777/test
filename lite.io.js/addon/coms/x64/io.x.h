/*****************************************************************************/
/*                                                                           */
/*            DVLab (Data Visualization Lab) CORE version 1.0                */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
/*  File Name         : io.x.h                                             */
/*                                                                           */
/*  Description       :                                                      */
/*                                                                           */
/*                                                                           */
/*  Issues / Problems : None                                                 */
/*                                                                           */
/*  Revision History  :                                                      */
/*                                                                           */
/*        DD MM YYYY   Author(s)        Changes (Describe the changes made)  */
/*        25 02 2019   Shin Seunghyeok  Draft                                */
/*                                                                           */
/*****************************************************************************/
#ifndef __IO_X_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __IO_X_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#if __LINUX__
#define MAKEWORD(a,b)      ((a&0x00FF)|((b&0x00FF)<<8))
#define MAKELONG(a,b)      ((a&0x0000FFFF)|((b&0x0000ffff)<<16))
#define LOWORD(l)           (l&0x0000FFFF)
#define HIWORD(l)          ((l&0xFFFF0000)>>16)
#define LOBYTE(w)           (w&0x00FF)
#define HIBYTE(w)          ((w&0xFF00)>>8)
#endif

#define MTIF                    0xFFFF

#define SYSTEM_STATUS            0xFFFF
#define SYSTEM_VERSION           0xFFFE
#define SYSTEM_CALLBACK          0xFFFD
#define SYSTEM_CLEAR             0xFFFC
#define SYSTEM_AUTHOR            0xFFFB
#define SYSTEM_MODULENAME        0xFFFA

//#define __BUFFER_PTR__           0x8000
#define __SET__                  0x9000
#define __GET__                  0xA000

enum
{
  SIFR_STATUS = 0xFFFF0000,          // 암호모듈 상태 값
  SIFR_STATUS_LOADED = SIFR_STATUS,  // 암호모듈이 정상적으로 Load된 상태
  SIFR_STATUS_NORMAL,                // 암호모듈이 검증대상 동작 상태
  SIFR_STATUS_INITIALIZED,           // 암호모듈이 정상적으로 초기화 된 상태
  SIFR_STATUS_KAT_CHECKED,           // KAT 완료된 상태
  SIFR_STATUS_INTEGRITY_CHECKED,     // 무결성 검증 완료된 상태
  SIFR_STATUS_SELF_CHECKED,          // 자가시험이 완료된 상태
  SIFR_STATUS_COND_CHECKED,          // 조건부 자가시험이 완료된 상태
  SIFR_STATUS_ERROR,                 // 간단한 오류 상태
  SIFR_STATUS_CRITICAL_ERROR,        // 심각한 오류 상태
};




///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////                                                                   //////
//////                                                                   //////
//////                  MAKELONG(_______, HIWORD )                       //////
//////                                                                   //////
//////                  PART of HIWORD                                   //////
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
  SIFR = 0,
  SIFR_ARIA = SIFR,
  SIFR_HIGHT,
  SIFR_LEA,
  SIFR_SEED,
  SIFR_LSH256,
  SIFR_LSH512,
  SIFR_SHA256,
  SIFR_DRBG,
  SIFR_HMAC_SHA256,
  MAX_SIFR,
  ENTIRE_SIFR = MAX_SIFR,
};


enum
{
  XMODULES = MAX_SIFR+1,
  XHTTP = XMODULES,
  XHTTPD,
  XPACKET,
  XPROTOCOL,
  XSERIAL,
  XSOCKET,
  XWEBSOCKET,
  XXML,
  XSHM,
  XSYSTEM,
  MAX_MODULES,
  ENTIRE_MODULES = MAX_MODULES,
};




///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////                                                                   //////
//////                                                                   //////
//////                  MAKELONG( LOWORD, _________ )                    //////
//////                                                                   //////
//////                  PART of LOWORD                                   //////
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
  SIFR_PARAMETER = 0,
  PARAM_KEY = SIFR_PARAMETER,
  PARAM_VECTOR,
  PARAM_INPUT,
  PARAM_OUTPUT,
  PARAM_OUTPUT_SZ,
  PARAM_MACSZ,
  PARAM_BITSZ,
  PARAM_SIZE,
  PARAM_NONCE,
  PARAM_CUTOFF_0,
  PARAM_CUTOFF_1,
  PARAM_ENTROPY_0,
  PARAM_ENTROPY_1,
  PARAM_STRING_0,
  PARAM_STRING_1,
  PARAM_STRING_2,
  PARAM_STRING_3,
  PARAM_STRING_4,
  PARAM_STRING_5,
  PARAM_STRING_6,
  PARAM_STRING_7,
  PARAM_CLEAR,
  MAX_SIFR_PARAMETER = (PARAM_CLEAR+1),
};

enum
{
  SIFR_MESSAGE = MAX_SIFR_PARAMETER + 1,
  ECB_ENCODE,
  CBC_ENCODE,
  CFB_ENCODE,
  OFB_ENCODE,
  CTR_ENCODE,
  ECB_DECODE,
  CBC_DECODE,
  CFB_DECODE,
  OFB_DECODE,
  CTR_DECODE,
  CCM_ENCODE,
  CCM_DECODE,
  GCM_ENCODE,
  GCM_DECODE,
  CMAC,
  HASH,
  GENERATE,
  REMOVE_PADDING,
  SELF_CHECK,
  INTEGRITY_CHECK,
  KAT_CHECK,
  SIFR_RELEASE,
  SIFR_NOISE_0,
  SIFR_NOISE_1,
  SIFR_NOISE_2,
  SIFR_NOISE_S,
  CHECK_DRBG_STATUS,
  CHECK_RCT,
  CHECK_APT,
  RESEED,
  SIFR_UPDATE,
  BASE64_ENCODE,
  BASE64_DECODE,
  MAX_SIFR_MESSAGE,
};

enum
{
  XMODULE_PARAMETER = MAX_SIFR_MESSAGE + 1,
  XM_SECRET = XMODULE_PARAMETER,
  XM_ID,
  XM_ENABLE,
  XM_SYNC,
  XM_BLOCK,
  XM_DELAY_0,
  XM_DELAY_1,
  XM_DELAY_2,
  XM_TIMEOUT,
  XM_CONFIG,
  XM_DST_IP,
  XM_DST_PORT,
  XM_IP,
  XM_IFNAME,
  XM_PORT,
  XM_PROTO,
  XM_CSTYPE,
  XM_CASTTYPE,
  XM_URL,
  XM_URI,
  XM_CONTENTS,
  XM_HOME,
  XM_INDEX,
  XM_MAX_FD,
  XM_DESC,
  XM_BAUDRATE,
  XM_DATABIT,
  XM_STOPBIT,
  XM_PARITYBIT,
  XM_BLOCKMODE,
  XM_ECHOMODE,
  XM_AP_SSID,
  XM_AP_PW,
  XM_EST,
  XM_ESTID,
  XM_EPT,
  XM_ESI,
  XM_ESP,
  XM_KEY,
  XM_SIZE,
  XM_COUNT,
  XM_BUFFER,
  XM_CLEAR,
  XM_USR,
  MAX_XMODULE_PARAMETER = (XM_USR+1),
};

enum
{
  XM_MESSAGE = MAX_XMODULE_PARAMETER + 1,
  ENABLE,
  DISABLE,
  INIT,
  RELEASE,
  OPEN,
  CLOSE,
  CLOSE_SOCKET,
  BROADCAST,
  FDSCRPTR,
  FDSCRPTRS,
  IP_PORT,
  REQUEST,
  RESPONSE,
  WRITE,
  WRITETO,
  READ,
  READFROM,
  READER,
  WRITER,
  IO_CLOSER,
  IO_ACCEPTER,
  HTTP_NOT_FOUND,
  HTTP_URI,
  METHOD_GET,
  METHOD_POST,
  IDLE,
  READY,
  CONNECT,
  DISCONNECT,
  RUNNING,
  READING,
  WRITING,
  COMPLETE,
  REFERENCE,
  ASYNC_START,
  ASYNC_STOP,
  OBJECT_PTR,
  MAX_XM_MESSAGE,
};




#endif