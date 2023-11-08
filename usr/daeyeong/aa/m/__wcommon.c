#include "__wcommon.h"

static uint32_t    gLIST_MAX_COUNT = 2048;


void SetFont(HWND hwnd, void* hdl)
{
  SendMessage(hwnd, WM_SETFONT, (WPARAM)hdl, (LPARAM)FALSE);
}

void ResetText(HWND hwnd, int8_t* msg)
{
  #if defined UNICODE
  wchar_t _msg[1024] = {0};
  int32_t s = 0;
  #endif

  SendMessage(hwnd, EM_LIMITTEXT, (WPARAM)0xFFFFFFFF, 0);
  SendMessage(hwnd,  EM_SETSEL, 0, -1);

  #if defined UNICODE
  if ( msg )
  {
    s = mbstowcs(_msg, msg, strlen(msg));
    SendMessage(hwnd, EM_REPLACESEL, 1, (LPARAM)_msg);
  }
  else
  {
    SendMessage(hwnd, WM_CLEAR, 0, 0);
  }
  #else
  if ( msg )
  {
    SendMessage(hwnd, EM_REPLACESEL, 1, (LPARAM)msg);
  }
  else
  {
    SendMessage(hwnd, WM_CLEAR, 0, 0);
  }
  #endif
}

int32_t SetText(HWND hwnd, int8_t* msg, int32_t len)
{
  #if defined UNICODE
  wchar_t _msg[1024] = {0};
  int32_t s = 0;
  #endif
  SendMessage(hwnd, EM_LIMITTEXT, (WPARAM)0xFFFFFFFF, 0);


  #if defined UNICODE
  s = mbstowcs(_msg, msg, len);
  return SendMessage(hwnd,  WM_SETTEXT, s, (LPARAM)_msg);
  #else
  return SendMessage(hwnd,  WM_SETTEXT, len, (LPARAM)msg);
  #endif
}

int32_t SetWText(HWND hwnd, wchar_t* msg, int32_t len)
{
  SendMessage(hwnd, EM_LIMITTEXT, (WPARAM)0xFFFFFFFF, 0);
  return SendMessage(hwnd,  WM_SETTEXT, len, (LPARAM)msg);
}

int32_t AppendText(HWND hwnd, int8_t* msg, int32_t len)
{
  #if defined UNICODE
  wchar_t _msg[1024] = {0};
  #endif
  int32_t s,e,sz;
  SendMessage(hwnd, EM_LIMITTEXT, (WPARAM)0xFFFFFFFF, 0);
  SendMessage(hwnd, EM_GETSEL, (WPARAM)&s, (LPARAM)&e);
  sz = GetWindowTextLength(hwnd);
  SendMessage(hwnd, EM_SETSEL, sz, sz);

  #if defined UNICODE
  s = mbstowcs(_msg, msg, len);
  SendMessage(hwnd, EM_REPLACESEL, 1, (LPARAM)_msg);
  #else
  SendMessage(hwnd, EM_REPLACESEL, 1, (LPARAM)msg);
  #endif
  return SendMessage(hwnd,  EM_SETSEL, s, e);
}

int32_t GetText(HWND hwnd, int8_t* msg, int32_t len)
{
  #if defined UNICODE
  wchar_t _msg[1024] = {0};
  #endif
  int32_t e = 0;

  #if defined UNICODE
  e = SendMessage(hwnd, WM_GETTEXT, 1024, (LPARAM)_msg);
  e  = wcstombs(msg, _msg, e);
  #else
  e = SendMessage(hwnd, WM_GETTEXT, len, (LPARAM)msg);
  #endif
  msg[e] = 0;
  return e;
}

int32_t GetComboText(HWND hwnd, int8_t* txt)
{
  #if defined UNICODE
  wchar_t _msg[1024] = {0};
  #endif
  int32_t i=0;
  int32_t e=0;
  i=SendMessage(hwnd, CB_GETCURSEL, 0, 0);

  #if defined UNICODE
  e = SendMessage(hwnd, CB_GETLBTEXT, i, (LPARAM)_msg);
  e  = wcstombs(txt, _msg, e);
  #else
  e = SendMessage(hwnd, CB_GETLBTEXT, i, (LPARAM)txt);
  #endif

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

void InitListView(HWND hwnd, int32_t max_count)
{
  LVCOLUMN lc;
  memset(&lc, 0, sizeof(LVCOLUMN));

  SendMessage(hwnd, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

  lc.mask = LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM;
  lc.cx = 30;
  lc.pszText = _T("no");
  SendMessage(hwnd, LVM_INSERTCOLUMN,0,(LPARAM)&lc);

  lc.cx = 900;
  lc.pszText = _T("Log");
  SendMessage(hwnd, LVM_INSERTCOLUMN,1,(LPARAM)&lc);

  gLIST_MAX_COUNT= max_count;
}

void ClearListView(HWND hwnd)
{
  SendMessage(hwnd, LVM_DELETEALLITEMS, 0, 0);
  LV_INC = 0;
}
void InsertLVText(HWND hwnd, const int8_t* fmt, ...)
{
  int32_t no;
  int32_t new_no = 0;
  int8_t _no[32];
  int8_t _msg[8192] = {0};
  wchar_t _args[8192] = {0};
  va_list args;
  LVITEM li;

  memset(&li, 0, sizeof(LVITEM));

  no = (int32_t)SendMessage(hwnd, LVM_GETITEMCOUNT, 0, 0);

  no += LV_INC;
  new_no = no;
  if ( no>gLIST_MAX_COUNT )
  {
    //SendMessage(hwnd, LVM_DELETEALLITEMS, 0, 0);
    //no = 0;
    li.iItem = 1;
    LV_INC =  no-gLIST_MAX_COUNT;
    SendMessage(hwnd, LVM_DELETEITEM, 0, (LPARAM)&li);
    new_no = gLIST_MAX_COUNT;
  }

  
  sprintf(_no, "%d", no);

  li.mask = LVIF_TEXT;
  li.iItem = new_no;
  li.iSubItem = 0;
  #if defined UNICODE
  mbstowcs(_args, _no, strlen(_no));
  li.pszText = _args;
  #else
  li.pszText = _no;
  #endif
  SendMessage(hwnd, LVM_INSERTITEM, 0, (LPARAM)&li);

	va_start(args, fmt);
	vsprintf(_msg, fmt, args);
  li.iSubItem = 1;
  #if defined UNICODE
  mbstowcs(_args, _msg, strlen(_msg));
  li.pszText = _args;
  #else
  li.pszText = _msg;
  #endif
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

void LVLog(HWND lv, HWND logcheck, wLog* p, int8_t* fname, int8_t* pfx, const int8_t* fmt, ...)
{
  #if LVLOG_LEVEL_10
  va_list args;
  int8_t _arg[8192];
  int32_t idx = 0;

	va_start(args, fmt);
	vsprintf(_arg, fmt, args);
  va_end(args);


  InsertLVText(lv,_arg);


  if ( logcheck == 0 ) return;
  if ( p == 0 ) return;
  if ( fname == 0 ) return;

  if ( SendMessage(logcheck, BM_GETCHECK, 0, 0) != BST_CHECKED )
  {
    return;
  }
  __log_write_ex("log", fname, p->pfname, (void**)&p->fp, pfx, 0x1E000000, _arg);
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