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


#include <wcommon.h>
#include <wtray.h>

#include <wcrypt.h>
#include <wsifr.h>

//
//
//#include <CodeX.h>

//#include <wcommon.h>
//#include <mdbc.h>

//#include <wdraw.h>
//#include <wcodex.h>
//#include <wprime.h>


#include "resource.h"

#include <commctrl.h>

#pragma comment(lib, "comctl32.lib")

#define STR_WRITE     "WRITE"
#define STR_OPEN      "OPEN"
#define STR_CLOSE     "CLOSE"

#define MAX_LINE           1024//(1<<0x0F)
#define XWM_CALLBACK       (WM_USER+0x0001)
#define XWM_TRANSFER       (WM_USER+0x0002)


#define TAB_LEFT_MARGIN    12
#define TAB_TOP_MARGIN     8   

enum
{
  WCRYPT,
  WSIFR,
  WDRAW,
  WCODEX,
  WPRIME,
  MAX_TAB
};

enum
{
  TAB_CONTROL,
  MAX_TABS
};


static int32_t SHOW_MODE[MAX_TAB] = {SW_SHOW, 0};



#if defined WIN32
#pragma pack(1)
#endif
typedef struct
{
  HINSTANCE          hinst[2];
  HWND               hdlg;

  xWnd               item[MAX_TAB];
  HWND               tabwnd[MAX_TAB];
  RECT               rct;


  void*              h;


  wsifr              _sifr;


  //CodeX              codeX;


  //wDraw             wdraw;
  //wCodeX            wcodex;
  //wPrime            wprime;
}XWND;
#if defined WIN32
#pragma pack()
#endif





#endif
