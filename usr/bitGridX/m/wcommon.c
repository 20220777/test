#include "wcommon.h"
#include "ICodeX.h"
void SetFont(HWND hwnd, void* hdl)
{
  SendMessage(hwnd, WM_SETFONT, (WPARAM)hdl, (LPARAM)FALSE);
}

void ResetText(HWND hwnd, int8_t* msg)
{
  SendMessage(hwnd, EM_LIMITTEXT, (WPARAM)0xFFFFFFFF, 0);
  SendMessage(hwnd,  EM_SETSEL, 0, -1);
  if ( msg )
  {
    SendMessage(hwnd, EM_REPLACESEL, 1, (LPARAM)msg);
  }
  else
  {
    SendMessage(hwnd, WM_CLEAR, 0, 0);
  }
}

int32_t SetText(HWND hwnd, int8_t* msg, int32_t len)
{
  SendMessage(hwnd, EM_LIMITTEXT, (WPARAM)0xFFFFFFFF, 0);
  return SendMessage(hwnd,  WM_SETTEXT, len, (LPARAM)msg);
}

int32_t AppendText(HWND hwnd, int8_t* msg, int32_t len)
{
  int32_t s,e,sz;
  SendMessage(hwnd, EM_LIMITTEXT, (WPARAM)0xFFFFFFFF, 0);
  SendMessage(hwnd, EM_GETSEL, (WPARAM)&s, (LPARAM)&e);
  sz = GetWindowTextLength(hwnd);
  SendMessage(hwnd, EM_SETSEL, sz, sz);
  SendMessage(hwnd, EM_REPLACESEL, 1, (LPARAM)msg);
  return SendMessage(hwnd,  EM_SETSEL, s, e);
}

int32_t GetText(HWND hwnd, int8_t* msg, int32_t len)
{
  int32_t e = SendMessage(hwnd, WM_GETTEXT, len, (LPARAM)msg);
  msg[e] = 0;
  return e;
}

int32_t GetComboText(HWND hwnd, int8_t* txt)
{
  int32_t i=0;
  int32_t e=0;
  i=SendMessage(hwnd, CB_GETCURSEL, 0, 0);
  e = SendMessage(hwnd, CB_GETLBTEXT, i, (LPARAM)txt);
  *(txt+e) = 0;
  return e;
}

int32_t  ChangeComboIndex(HWND hwnd, int32_t index)
{
  SendMessage(hwnd, WM_SETFOCUS, 0, 0);
  SendMessage(hwnd, CB_SETCURSEL, index, 0);
  SendMessage(hwnd, WM_KILLFOCUS, 0, 0);
  return 0;
}

#if  1//WIN32

static int32_t LV_INC = 0;

void InitListView(HWND hwnd)
{
  LVCOLUMN lc;
  memset(&lc, 0, sizeof(LVCOLUMN));

  SendMessage(hwnd, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

  lc.mask = LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM;
  lc.cx = 30;
  lc.pszText = "no";
  SendMessage(hwnd, LVM_INSERTCOLUMN,0,(LPARAM)&lc);

  lc.cx = 900;
  lc.pszText = "Log";
  SendMessage(hwnd, LVM_INSERTCOLUMN,1,(LPARAM)&lc);
}

void ClearListView(HWND hwnd)
{
  SendMessage(hwnd, LVM_DELETEALLITEMS, 0, 0);
  LV_INC = 0;
}

void InsertLVText(HWND hwnd,int32_t max,const int8_t* fmt, ...)
{
  int32_t no;
  int32_t new_no = 0;
  int8_t _no[32];
  int8_t _msg[8192];
  va_list args;
  LVITEM li;

  memset(&li, 0, sizeof(LVITEM));

  no = (int32_t)SendMessage(hwnd, LVM_GETITEMCOUNT, 0, 0);

  no += LV_INC;
  new_no = no;
  if ( no>max )
  {
    //SendMessage(hwnd, LVM_DELETEALLITEMS, 0, 0);
    //no = 0;
    li.iItem = 1;
    LV_INC =  no-max;
    SendMessage(hwnd, LVM_DELETEITEM, 0, (LPARAM)&li);
    new_no = max;
  }
  sprintf(_no, "%d", no);

  li.mask = LVIF_TEXT;
  li.iItem = new_no;
  li.iSubItem = 0;
  li.pszText = _no;
  SendMessage(hwnd, LVM_INSERTITEM, 0, (LPARAM)&li);

	va_start(args, fmt);
	vsprintf(_msg, fmt, args);
  li.iSubItem = 1;
  li.pszText = _msg;
  SendMessage(hwnd, LVM_SETITEM, 0, (LPARAM)&li);
  va_end(args);

  memset(&li, 0, sizeof(LVITEM));
  li.stateMask = LVIS_FOCUSED|LVIS_SELECTED;
  li.state = LVIS_FOCUSED|LVIS_SELECTED;

  SendMessage(hwnd, LVM_SETITEMSTATE, -1, (LPARAM)(LVITEM*)&li);

  li.state = LVIS_FOCUSED|LVIS_SELECTED;
  SendMessage(hwnd, LVM_SETITEMSTATE, new_no, (LPARAM)(LVITEM*)&li);
  SendMessage(hwnd, LVM_ENSUREVISIBLE, new_no, MAKELPARAM(0,0));
}


void LogWrite(HWND hwnd, wLog* p, int8_t* fname, int8_t* pfx, const int8_t* fmt, ...)
{
  va_list args;
  int8_t _arg[8192];

  if ( SendMessage(hwnd, BM_GETCHECK, 0, 0) != BST_CHECKED )
  {
    return;
  }
	va_start(args, fmt);
	vsprintf(_arg, fmt, args);
  va_end(args);

  //log_write_ex("log", fname, p->pfname, (void**)&p->fp, pfx, 0, _arg);
}


void LVLog(HWND lv, HWND logcheck, int32_t max, wLog* p, int8_t* fname, int8_t* pfx, const int8_t* fmt, ...)
{
  #if LVLOG_LEVEL_10
  va_list args;
  int8_t _arg[8192];

	va_start(args, fmt);
	vsprintf(_arg, fmt, args);
  va_end(args);
  InsertLVText(lv, max, _arg);


  if ( logcheck == 0 ) return;
  if ( p == 0 ) return;
  if ( fname == 0 ) return;

  if ( SendMessage(logcheck, BM_GETCHECK, 0, 0) != BST_CHECKED )
  {
    return;
  }
  log_write_ex("log", fname, p->pfname, (void**)&p->fp, pfx, 0x1E000000, _arg);
  //Log(l, TOP_LOG_NAME, pfx, _arg);
  #endif
}

//
//FILE* LogWriteEx(int32_t id, int8_t* fname, int8_t* pfname, int8_t* pfx, const int8_t* fmt, ...)
//{
//  va_list args;
//  int8_t _arg[8192];
//
//  if ( SendMessage(mtif.hitem[id], BM_GETCHECK, 0, 0) != BST_CHECKED )
//  {
//    return;
//  }
//	va_start(args, fmt);
//	vsprintf(_arg, fmt, args);
//  va_end(args);
//
//  //Log(l, TOP_LOG_NAME, pfx, _arg);
//
//  return 0;
//
//}
//
#endif