#ifndef __WDRAWWND_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __WDRAWWND_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <__wcommon.h>
#include <imtif.h>

#define WDRAW_AXIS_X_SZ      480
#define WDRAW_AXIS_Y_SZ      480
#define WDRAW_AXIS_X_C       240
#define WDRAW_AXIS_Y_C       240

#define WDRAW_GUIDE_X_SZ     255
#define WDRAW_GUIDE_Y_SZ     255
#define WDRAW_GUIDE_X_C      127
#define WDRAW_GUIDE_Y_C      127


enum
{
  STATIC_DRAW_AXIS = 0,
  EDIT_DRAW_ABS_COORD,
  EDIT_DRAW_ABS_COORD_PICK,
  EDIT_DRAW_ABS_COORD2,
  EDIT_DRAW_ABS_COORD_PICK2,
  EDIT_DRAW_REL_COORD,
  EDIT_DRAW_REL_COORD_PICK,
  EDIT_DRAW_REL_COORD2,
  EDIT_DRAW_REL_COORD_PICK2,
  EDIT_DRAW_SPORT,
  EDIT_DRAW_BAUD,
  EDIT_DRAW_DBIT,
  EDIT_DRAW_SBIT,
  EDIT_DRAW_PBIT,
  EDIT_DRAW_WRITE,
  COMBO_DRAW_DISPLAY_TYPE_W,
  COMBO_DRAW_DISPLAY_TYPE_R,
  BUTTON_DRAW_OPEN_CLOSE,
  BUTTON_DRAW_WRITE,
  CHECK_DRAW_CR,
  CHECK_DRAW_LF,
  CHECK_DRAW_SERIAL_LOG,
  CHECK_DRAW_SERIAL_ECHO,
  LIST_DRAW_READ,
  BUTTON_DRAW_CLEAR,
  CHECK_DRAW_READ_YN,
  MAX_DRAW_ITEM
};


#if (defined XWIN32 || defined WINCE)
#pragma pack(1)
#endif
typedef struct
{
  //MTIF*              pm;
  HWND hitem[MAX_DRAW_ITEM];
  WNDPROC oitem[MAX_DRAW_ITEM];
  HDC  hdc_cross;
  HBRUSH hbr;
  HPEN hpen;
  RECT rct[2];
  POINT pt;
  int coord[2];
  int xycoord[4][2];
  char strcoord[4][32];
  HCURSOR  hcursor;

  wLog             log;
  unsigned char  read_lock;
}wDrawWnd;
#if (defined XWIN32 || defined WINCE)
#pragma pack()
#endif


void* wdrawwnd_dlgproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
void* wdrawwnd_init(HWND hwnd, wDrawWnd* p);


#endif

