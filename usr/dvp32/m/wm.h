#ifndef __WM_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __WM_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include "wmtab.h"
#include <usermode.h>

#include "mcommon.h"
#include "wcommon.h"
#include "wmtif.h"
#include "wdrawwnd.h"
#include "wprime.h"
#include "wbitmap.h"
#include "wwsc.h"
#include "wwsgw.h"
#include "wtray.h"

#include "resource.h"


#define LOAD_LIBRARY      "xmtif.x86.dll"

#define TAB_LEFT_MARGIN    12
#define TAB_TOP_MARGIN     8   


#pragma comment(lib, "mtif.x86.lib")
#pragma comment(lib, "libxcore.x86.lib")
#pragma comment(lib, "libxwidget.x86.lib")



enum
{
  TAB_CONTROL,
  MAX_TABS
};


static int SHOW_MODE[MAX_TAB] = {SW_HIDE,};



#if (defined XWIN32 || defined WINCE)
#pragma pack(1)
#endif
typedef struct
{
  MTIF      mtif;

  wLog      log;
  HINSTANCE hinst[2];
  HWND      hdlg;
  HWND      htabwnd[MAX_TAB];
  HWND      hitem[MAX_TABS];
  RECT      rct;

  wMTIF     wm;
  wBitmap   wb;
  wDrawWnd  wd;
  wPrime    wp;
  wWSC      ww;
  wWSGW     wg;
}XWND;
#if (defined XWIN32 || defined WINCE)
#pragma pack()
#endif


#endif