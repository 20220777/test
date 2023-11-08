#ifndef __WCOMMON_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __WCOMMON_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#if __WIDGET__

#include <Windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <stdint.h>

void SetFont(HWND hwnd, void* hdl);
void ResetText(HWND hwnd, int8_t* msg);
int32_t SetText(HWND hwnd, int8_t* msg, int32_t len);
int32_t AppendText(HWND hwnd, int8_t* msg, int32_t len);
int32_t GetText(HWND hwnd, int8_t* msg, int32_t len);
int32_t GetComboText(HWND hwnd, int8_t* txt);
int32_t  ChangeComboIndex(HWND hwnd, int32_t index);

#if (defined XWIN32 || defined WINCE)
#pragma pack(1)
#endif
typedef struct
{
  FILE* fp;
  int8_t pfname[80];
}wLog;
#if (defined XWIN32 || defined WINCE)
#pragma pack()
#endif

void InitListView(HWND hwnd);
void ClearListView(HWND hwnd);
void InsertLVText(HWND hwnd,int32_t max,const int8_t* fmt, ...);
void LogWrite(HWND hwnd, wLog* p, int8_t* fname, int8_t* pfx, const int8_t* fmt, ...);
void LVLog(HWND lv, HWND logcheck, int32_t max, wLog* p, int8_t* fname, int8_t* pfx, const int8_t* fmt, ...);


#define LVLOG_LEVEL_0            0
#define LVLOG_LEVEL_5            5
#define LVLOG_LEVEL_10           10


#endif



#endif