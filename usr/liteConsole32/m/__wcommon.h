#ifndef __WCOMMON_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __WCOMMON_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <Windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <stdint.h>
#include <tchar.h>


#define STR_WRITE     ("WRITE")
#define STR_OPEN      ("OPEN")
#define STR_CLOSE     ("CLOSE")
#define TOP_LOG_PATH             ("log")
#define TOP_LOG_NAME             ("lite Console 32")




#if (defined WIN32 || defined WINCE)
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
}_WND;
#if (defined WIN32 || defined WINCE)
#pragma pack()
#endif



void SetFont(HWND hwnd, void* hdl);
void ResetText(HWND hwnd, int8_t* msg);
int32_t SetText(HWND hwnd, int8_t* msg, int32_t len);
int32_t SetWText(HWND hwnd, wchar_t* msg, int32_t len);
int32_t AppendText(HWND hwnd, int8_t* msg, int32_t len);
int32_t GetText(HWND hwnd, int8_t* msg, int32_t len);
int32_t GetComboText(HWND hwnd, int8_t* txt);
int32_t  ChangeComboIndex(HWND hwnd, int32_t index);

#if (defined WIN32 || defined WINCE)
#pragma pack(1)
#endif
typedef struct
{
  FILE* fp;
  int8_t pfname[80];
}wLog;
#if (defined WIN32 || defined WINCE)
#pragma pack()
#endif

void InitListView(HWND hwnd);
void ClearListView(HWND hwnd);
void InsertLVText(HWND hwnd,int32_t max,const int8_t* fmt, ...);
void LogWrite(HWND hwnd, wLog* p, int8_t* fname, int8_t* pfx, const int8_t* fmt, ...);
void LVLog(HWND lv, HWND logcheck, wLog* p, int8_t* fname, int8_t* pfx, const int8_t* fmt, ...);


#define LVLOG_LEVEL_0            0
#define LVLOG_LEVEL_5            5
#define LVLOG_LEVEL_10           10


#endif




#if 0//WIN32
#include <Windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <stdint.h>

#pragma comment(lib, "comctl32.lib")




#endif
