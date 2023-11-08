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
#include <__util.h>
#include <imtif.h>

#include <_sifr.h>

#define MAX_LINE           1024//(1<<0x0F)
#define XWM_CALLBACK       (WM_USER+0x0001)
#define XWM_TRANSFER       (WM_USER+0x0002)

#define TIMER_TM           300


enum
{
  _IDC_STATIC1,
  _IDC_STATIC2,
  _IDC_STATIC3,
  _IDC_STATIC4,
  _IDC_STATIC5,
  _IDC_STATIC6,
  _IDC_STATIC7,
  _IDC_EDIT_RAND,
  _IDC_EDIT_RBIT,
  _IDC_EDIT_MODULE,
  _IDC_EDIT_KEY,
  _IDC_EDIT_VECTOR,
  _IDC_EDIT_PLAIN,
  _IDC_EDIT_CIPHER,
  _IDC_BUTTON_GEN,
  _IDC_BUTTON_LOAD,
  _IDC_BUTTON_ENCODE,
  _IDC_BUTTON_DECODE,
  _IDC_COMBO_TYPE,
  _IDC_COMBO_MODE,
  _IDC_LIST_READ,
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

#if (defined XWIN32 || defined WINCE)
#pragma pack(1)
#endif
typedef struct
{
  HINSTANCE          hinst[2];
  HWND               hdlg;

  XSubWnd            item[_IDC_MAX];

  void*              h;

  uint8_t           protocol[4];
  uint32_t          tmrid;
  uint32_t          rflag;

  uint32_t          max_line;

  _sifr               sifr;

}XWND;
#if (defined XWIN32 || defined WINCE)
#pragma pack()
#endif


#endif
