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


#include "resource.h"

#include <commctrl.h>

#pragma comment(lib, "comctl32.lib")

#define STR_WRITE     "WRITE"
#define STR_OPEN      "OPEN"
#define STR_CLOSE     "CLOSE"

#define MAX_LINE           1024//(1<<0x0F)
#define XWM_CALLBACK       (WM_USER+0x0001)
#define XWM_TRANSFER       (WM_USER+0x0002)

#define MAX_BUF_SZ     1024


#define TAB_LEFT_MARGIN    12
#define TAB_TOP_MARGIN     8   


enum
{
  BUTTON_OPEN,
  EDIT_COMPORT,
  EDIT_BAUDRATE,
  EDIT_TXT,
  BUTTON_WRITE,
  LIST_READ,
  BUTTON_CLEAR,
  COMBO_W_ASC_HEX,
  COMBO_R_ASC_HEX,
  CHECK_TMR,
  MAX_WIDGET
};

#if defined WIN32
#pragma pack(1)
#endif
typedef struct
{
  HINSTANCE          hinst[2];
  HWND               hdlg;

  xWnd               item[MAX_WIDGET];
  RECT               rct;

  void*              h;
}XWND;
#if defined WIN32
#pragma pack()
#endif





#endif
