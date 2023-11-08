#pragma once
#ifndef __A_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __A_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__


#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <winsock2.h>
#include <mstcpip.h>
#include <winreg.h>
#include <iphlpapi.h>
#include <sys/timeb.h>
#include <process.h>
#include <time.h>
#include <Windows.h>
#include "resource.h"

#include <__nsocket.h>
#include "__wcommon.h"


#define MAX_LINE           1024//(1<<0x0F)
#define XWM_CALLBACK       (WM_USER+0x0001)
#define XWM_TRANSFER       (WM_USER+0x0002)

#define TIMER_TM           300

enum
{
  _IDC_EDIT1,
  _IDC_EDIT2,
  _IDC_EDIT3,
  _IDC_EDIT4,
  _IDC_EDIT5,
  _IDC_EDIT6,
  _IDC_EDIT7,
  _IDC_EDIT8,
  _IDC_EDIT9,
  _IDC_EDIT10,
  _IDC_EDIT11,
  _IDC_EDIT12,
  _IDC_EDIT13,
  _IDC_EDIT14,
  _IDC_EDIT15,
  _IDC_EDIT16,
  _IDC_EDIT17,
  _IDC_EDIT18,
  _IDC_EDIT19,
  _IDC_EDIT20,
  _IDC_EDIT21,
  _IDC_EDIT_MAX,
  _IDC_SPIN1,
  _IDC_SPIN2,
  _IDC_SPIN3,
  _IDC_SPIN4,
  _IDC_SPIN5,
  _IDC_SPIN6,
  _IDC_SPIN7,
  _IDC_SPIN8,
  _IDC_SPIN9,
  _IDC_SPIN10,
  _IDC_SPIN11,
  _IDC_SPIN12,
  _IDC_SPIN13,
  _IDC_SPIN14,
  _IDC_SPIN15,
  _IDC_SPIN16,
  _IDC_SPIN17,
  _IDC_SPIN18,
  _IDC_SPIN19,
  _IDC_SPIN20,
  _IDC_SPIN21,
  _IDC_SPIN_MAX,
  _IDC_LIST1,
  _IDC_CHECK1,
  _IDC_MAX
};



#if (defined XWIN32 || defined WINCE)
#pragma pack(1)
#endif
typedef struct
{
  HDC                hdc;
  HBRUSH             hbrush;
  PAINTSTRUCT        ps;
  HWND               hwnd;
  HWND*              hlink;
  uint32_t           pos;
  WNDPROC            wproc;
  RECT               rct;
  COLORREF           color[2]; //0: Background, 1:Forground
  HFONT              font[2]; //0: oldfont, 1:working font
  uint8_t            count;  
  int8_t             cap[32];
  uint8_t            SR;
}HITEM;
#if (defined XWIN32 || defined WINCE)
#pragma pack()
#endif


#if defined WIN32
#pragma pack(1)
#endif
typedef struct
#if defined LINUX
__attribute__((packed))
#endif
{
  void*    h;
  void*    hdl;
  uint8_t* p;
  int32_t  sz;
  int32_t (*__sifr_initia)(void**,int8_t*);
  int32_t (*__sifr_finelia)(void**);
  int32_t (*__sifr_init)(void**,int8_t*,int32_t);
  int32_t (*__sifr_release)(void**);
  int32_t (*__sifr_last_status)(void*,int32_t*);
  int8_t*  (*__sifr_last_status_string)(int32_t*);
  int32_t (*__sifr_version)(void**,int8_t*,int32_t);
  int32_t (*__sifr_author)(void**,int8_t*,int32_t);
  int32_t (*__sifr_module)(void**,int8_t*,int32_t);

  int32_t (*__sifr_integrity_check)(void* h,int8_t*,int32_t);
  int32_t (*__sifr_kat_check)(void* h);
  int32_t (*__sifr_self_check)(void* h,int8_t*,int32_t);

  int32_t (*__sifr_set_callback)(void* h, void* callback, void* o);
  int32_t (*__sifr_base64)(void* h, uint8_t* in, int32_t isz, uint8_t mode, uint8_t* out);


  int32_t (*__sifr_mem_clear)(void* h,int8_t*,int32_t);


  int32_t (*__sifr_noise_source)(uint8_t who, uint8_t* o, int32_t s);

  int32_t (*__sifr_entropy)(void* h, uint32_t who, uint8_t* o, int32_t sz);
  int32_t (*__sifr_drbg)(void* h, uint8_t mode, uint8_t df, void* o, void* w, void* l);
  int32_t (*__sifr_random)(void* h, void* o, void* w, void* l);
  int32_t (*__sifr_key)(void* h, void* o, void* w, void* l);
  //int32_t (*__sifr_drbg)(void* h, uint8_t mode, uint8_t df, uint8_t* str0, int32_t ssz0, uint8_t* str1, int32_t ssz1, uint8_t* out, int32_t osz);

  int32_t (*__sifr_aria_ecb_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_aria_ecb_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_aria_cbc_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_aria_cbc_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_aria_cfb_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_aria_cfb_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_aria_ofb_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_aria_ofb_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_aria_ctr_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_aria_ctr_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_aria_ccm_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_aria_ccm_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);

  int32_t (*__sifr_lea_ecb_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_lea_ecb_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_lea_cbc_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_lea_cbc_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_lea_cfb_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_lea_cfb_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_lea_ofb_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_lea_ofb_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_lea_ctr_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_lea_ctr_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);

  int32_t (*__sifr_seed_ecb_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_seed_ecb_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_seed_cbc_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_seed_cbc_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_seed_cfb_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_seed_cfb_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_seed_ofb_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_seed_ofb_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_seed_ctr_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_seed_ctr_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);

  int32_t (*__sifr_hight_ecb_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_hight_ecb_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_hight_cbc_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_hight_cbc_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_hight_cfb_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_hight_cfb_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_hight_ofb_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_hight_ofb_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_hight_ctr_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);
  int32_t (*__sifr_hight_ctr_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback(void*,uint8_t*,int32_t), void* obj);

  int32_t (*__sifr_sha2)(void* h, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_hmac)(void* h, uint8_t* key, int32_t ksz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);

  int32_t (*__sifr_lsh256_224)(void* h, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_lsh256_256)(void* h, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_lsh512_224)(void* h, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_lsh512_256)(void* h, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_lsh512_384)(void* h, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_lsh512_512)(void* h, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);

} cCrypto32;
#if defined WIN32
#pragma pack()
#endif



#if (defined WIN32 || defined WINCE)
#pragma pack(1)
#endif
typedef struct
{
  wLog               log;

  cnsocket           sck;
  HINSTANCE          hinst[2];
  HWND               hdlg;
  HITEM              item[_IDC_MAX];

  cCrypto32          _crpt;
  
  uint8_t           protocol[4];
  uint32_t          tmrid;
  uint32_t          rflag;

  RECT      rct;


  int32_t           _pkt_sz;
  uint8_t           _pkt[1024];
}XWND;
#if (defined WIN32 || defined WINCE)
#pragma pack()
#endif


#endif
