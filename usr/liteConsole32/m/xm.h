#pragma once
#ifndef __XM_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __XM_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__


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

#include <__wcommon.h>
#include <__wtray.h>
#include <imtif.h>
#include <__nliteio.h>

#include "wmtif.h"
#include "wdrawwnd.h"
#include "wprime.h"
#include "wbitmap.h"
#include "wwsc.h"
#include "wwsgw.h"

#define MAX_LINE           1024//(1<<0x0F)
#define XWM_CALLBACK       (WM_USER+0x0001)
#define XWM_TRANSFER       (WM_USER+0x0002)

#define TIMER_TM           300

enum
{
  _WDRAWWND,
  _WMTIF,
  _WPRIME,
  _WBITMAP,
  _WWSC,
  _WWSGW,
  _TAB_MAX
};


static int SHOW_MODE[_TAB_MAX] = {SW_HIDE,};

enum
{
  _IDC_BUTTON_1,

  _IDC_MAX
};


//
//#if __WIN32__
//#pragma pack(1)
//#endif
//typedef struct
//{
//  imtif _imtif;
//  uint8_t* buf;
//  uint8_t qstatus[20];
//  uint8_t qbuf[16];
//  uint8_t rbuf[16];
//  uint8_t rdx;
//  int32_t fd;
//} cnserial;
//#if __WIN32__
//#pragma pack()
//#endif
//
//#if (defined XWIN32 || defined WINCE)
//#pragma pack(1)
//#endif
//typedef struct
//{
//  uint8_t str[_IDC_MAX_ITEM][32];
//  uint8_t v[_IDC_MAX_ITEM][32];
//  uint8_t vid[_IDC_MAX_ITEM][8];
//}cnconfig;
//#if (defined XWIN32 || defined WINCE)
//#pragma pack()
//#endif
//


#if (defined WIN32 || defined WINCE)
#pragma pack(1)
#endif
typedef struct
{
  HINSTANCE          hinst[2];
  HWND               hdlg;

  HWND               tab;
  _WND               item[_TAB_MAX];

  wMTIF     wm;
  wBitmap   wb;
  wDrawWnd  wd;
  wPrime    wp;
  wWSC      ww;
  wWSGW     wg;

  void*              h;

  uint8_t           protocol[4];
  uint32_t          tmrid;
  uint32_t          rflag;

  RECT      rct;

}XWND;
#if (defined WIN32 || defined WINCE)
#pragma pack()
#endif


#endif
