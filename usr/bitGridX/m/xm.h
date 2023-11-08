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


#include <CodeX.h>

#include <wtray.h>
#include <wcommon.h>


#include "resource.h"



#include <protocol_jmt.h>

#define MAX_LINE           1024//(1<<0x0F)
#define XWM_CALLBACK       (WM_USER+0x0001)
#define XWM_TRANSFER       (WM_USER+0x0002)

#define TIMER_TM           7500


enum
{
  XM_STATIC_1,
  XM_STATIC_2,
  XM_STATIC_100=99,
  XM_BUTTON1,
  XM_BUTTON2,
  XM_BUTTON3,
  XM_BUTTON4,
  XM_BUTTON5,
  XM_BUTTON6,
  XM_EDIT1,
  XM_EDIT2,
  XM_EDIT3,
  XM_EDIT4,
  XM_EDIT5,
  XM_EDIT6,
  XM_LIST1,
  MAX_XM_ITEM
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

  XSubWnd            item[MAX_XM_ITEM];

  wLog               log;

  void*              h;
  CodeX              codeX;

  uint8_t           protocol[4];
  uint32_t          tmrid;
  uint32_t          rflag;
}XWND;
#if (defined XWIN32 || defined WINCE)
#pragma pack()
#endif


#endif
