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

#define MAX_LINE           1024//(1<<0x0F)
#define XWM_CALLBACK       (WM_USER+0x0001)
#define XWM_TRANSFER       (WM_USER+0x0002)

#define TIMER_TM           300


enum
{
  _IDC_STATIC_1,
  _IDC_STATIC_2,
  _IDC_STATIC_3,
  _IDC_STATIC_4,
  _IDC_STATIC_5,
  _IDC_STATIC_6,
  _IDC_EDIT1,
  _IDC_BUTTON1,
  _IDC_BUTTON2,
  _IDC_BUTTON3,
  _IDC_BUTTON4,
  _IDC_BUTTON5,
  _IDC_BUTTON6,
  _IDC_BUTTON7,
  _IDC_BUTTON8,
  _IDC_BUTTON9,
  _IDC_BUTTON10,
  _IDC_BUTTON11,
  _IDC_BUTTON12,
  _IDC_BUTTON13,
  _IDC_BUTTON14,
  _IDC_BUTTON15,
  _IDC_BUTTON16,
  _IDC_BUTTON17,
  _IDC_BUTTON18,
  _IDC_BUTTON19,
  _IDC_BUTTON20,
  _IDC_BUTTON_U,
  _IDC_BUTTON_S,
  _IDC_BUTTON_D,
  _IDC_BUTTON_X,
  _IDC_MAX_ITEM
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
  WNDPROC            wproc;
  RECT               rct;
  COLORREF           color[2]; //0: Background, 1:Forground
  HFONT              font[2]; //0: oldfont, 1:working font
  uint8_t            count;  
  int8_t             cap[32];
  uint8_t            SR;
}XSubWnd;
#if (defined XWIN32 || defined WINCE)
#pragma pack()
#endif


#if __WIN32__
#pragma pack(1)
#endif
typedef struct
{
  imtif _imtif;
  uint8_t* buf;
  uint8_t qstatus[20];
  uint8_t qbuf[16];
  uint8_t rbuf[16];
  uint8_t rdx;
  int32_t fd;
} cnserial;
#if __WIN32__
#pragma pack()
#endif

#if (defined XWIN32 || defined WINCE)
#pragma pack(1)
#endif
typedef struct
{
  uint8_t str[_IDC_MAX_ITEM][32];
  uint8_t v[_IDC_MAX_ITEM][32];
  uint8_t vid[_IDC_MAX_ITEM][8];
}cnconfig;
#if (defined XWIN32 || defined WINCE)
#pragma pack()
#endif



#if (defined XWIN32 || defined WINCE)
#pragma pack(1)
#endif
typedef struct
{
  HINSTANCE          hinst[2];
  HWND               hdlg;

  XSubWnd            item[_IDC_MAX_ITEM];

  void*              h;

  uint8_t           protocol[4];
  uint32_t          tmrid;
  uint32_t          rflag;

  cnserial          _nserial;
  cnconfig          _nconfig;
}XWND;
#if (defined XWIN32 || defined WINCE)
#pragma pack()
#endif


#endif
