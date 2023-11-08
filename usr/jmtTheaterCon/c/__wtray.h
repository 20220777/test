#ifndef __WTRAY_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __WTRAY_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <resource.h>
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

#define IDI_TRAY IDI_ICON1
#if IDI_TRAY
#define XM_TRAY   (WM_USER|0xC000)
#define XM_SHOW   (WM_USER|0xD000)
#define XM_HIDE   (WM_USER|0xE000)
#define XM_EXIT   (WM_USER|0xF000)
#endif


void init_tray(HINSTANCE, HWND);
BOOL ontray_command(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
BOOL ontray_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

#endif