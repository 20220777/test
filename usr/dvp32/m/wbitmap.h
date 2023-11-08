#ifndef __WBITMAP_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __WBITMAP_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__


#include "wcommon.h"
#include "mcommon.h"
#include <xmath.h>
#include <ximage.h>


enum
{
  BUTTON_BITMAP_FILEOPEN,
  EDIT_BITMAP_FILE,
  STATIC_BITMAP_VIEW,
  BUTTON_BITMAP_CONVERT,
  EDIT_BITMAP_BMPHDR,
  EDIT_BITMAP_DIBHDR,
  EDIT_BITMAP_HEX,
  MAX_BITMAP_ITEM
};


#if (defined XWIN32 || defined WINCE)
#pragma pack(1)
#endif
typedef struct
{
  MTIF*              pm;
  wLog          log;
  HWND          hitem[MAX_BITMAP_ITEM];
  char          fname[256];

  ximage*       pimg;

}wBitmap;
#if (defined XWIN32 || defined WINCE)
#pragma pack()
#endif

void* wbitmap_dlgproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
void* wbitmap_init(HWND hwnd, wBitmap* p);
#endif


