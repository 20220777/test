#ifndef __WWEBSOCKETCLIENT_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __WWEBSOCKETCLIENT_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include "wcommon.h"
#include "mcommon.h"
#include <xmath.h>

enum
{
  EDIT_WSC_END,
  EDIT_WSC_BEGIN,
  EDIT_WSC_TIMER,
  BUTTON_WSC_START,
  BUTTON_WSC_TIMER,
  LIST_WSC_LOG,
  BUTTON_WSC_CLEAR,
  MAX_WSC_ITEM
};

#if (defined XWIN32 || defined WINCE)
#pragma pack(1)
#endif
typedef struct
{
  MTIF*              pm;
  unsigned char      wshdr[1024];
  unsigned char  read_lock;
  HWND          hitem[MAX_WSC_ITEM];

  long double range[2];
}wWSC;
#if (defined XWIN32 || defined WINCE)
#pragma pack()
#endif

void* wwsc_dlgproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
void* wwsc_init(HWND hwnd, wWSC* p);

#endif
