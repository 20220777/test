#ifndef __WSIFR_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __WSIFR_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <Windows.h>
#include "wcommon.h"

enum
{
  BUTTON_SIFR_INIT,
  MAX_SIFR_ITEM
};


#if defined WIN32
#pragma pack(1)
#endif
typedef struct
{
  xWnd item[MAX_SIFR_ITEM];
  WNDPROC oitem[MAX_SIFR_ITEM];
}wsifr;
#if defined WIN32
#pragma pack()
#endif


void* wsifrDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
void* wsifrInit(HWND hwnd, wsifr* p);


#endif