#ifndef __WTRAY_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __WTRAY_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include "windows.h"
#include "resource.h"

#define IDI_TRAY IDI_ICON1
#if IDI_TRAY
#define XM_TRAY   WM_USER+1
#define XM_SHOW   WM_USER+2
#define XM_HIDE   WM_USER+3
#define XM_EXIT   WM_USER+4
#endif


void init_tray(HINSTANCE, HWND);
BOOL ontray_command(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
BOOL ontray_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

#endif