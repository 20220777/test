#if __WIDGET__
#include "__wtray.h"

#if IDI_TRAY
static NOTIFYICONDATA    nid;
#endif


#if IDI_TRAY
void* OnInitTray(void* module, void* hwnd, int32_t id, int8_t* title)
{
  HMENU hmenu;

  nid.cbSize           = sizeof(NOTIFYICONDATA);
  nid.hWnd             = (HWND)hwnd; // 메인 윈도우 핸들
  nid.uID              = 0;
  nid.uFlags           = NIF_MESSAGE | NIF_ICON | NIF_TIP; // 플래그 설정
  nid.uCallbackMessage = XM_TRAY; // 콜백메시지 설정
  nid.hIcon            = LoadIcon((HINSTANCE)module,MAKEINTRESOURCE(id));

  sprintf(nid.szTip, title);

  Shell_NotifyIcon(NIM_ADD, &nid);

  if(nid.hIcon && DestroyIcon(nid.hIcon))	nid.hIcon = 0;

	hmenu = GetSystemMenu((HWND)hwnd,0);
	if (hmenu)
	{
		AppendMenu(hmenu, MF_SEPARATOR, 0, 0);
	}
  return 0;
}
#endif

#if IDI_TRAY
void* OnFinalTray()
{
	nid.uFlags = 0;
	Shell_NotifyIcon(NIM_DELETE, &nid);
	PostQuitMessage(WM_QUIT);
  return 0;
}
#endif

#if IDI_TRAY
void* OnXM_TRAY(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  POINT lpClickPoint;
  HMENU hPopMenu;

	switch(LOWORD(lparam)) 
	{   
		case WM_RBUTTONUP: 
			GetCursorPos(&lpClickPoint);
			hPopMenu = CreatePopupMenu();
			InsertMenu(hPopMenu,0xFFFFFFFF,MF_BYPOSITION|MF_STRING,XM_SHOW,("SHOW"));
			InsertMenu(hPopMenu,0xFFFFFFFF,MF_BYPOSITION|MF_STRING,XM_HIDE,("HIDE"));
			InsertMenu(hPopMenu,0xFFFFFFFF,MF_SEPARATOR,0,("SEP"));
			InsertMenu(hPopMenu,0xFFFFFFFF,MF_BYPOSITION|MF_STRING,XM_EXIT,("EXIT"));
			SetForegroundWindow(hwnd);
			TrackPopupMenu(hPopMenu,TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_BOTTOMALIGN,lpClickPoint.x, lpClickPoint.y,0,hwnd,0);
			return (void*)1;
    case WM_LBUTTONDBLCLK:
      ShowWindow(hwnd, SW_RESTORE);
      break;
	}
	return 0;
}
#endif



BOOL ontray_command(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  #if IDI_TRAY
  switch(LOWORD(wparam))
  {
	  case XM_SHOW:
		  ShowWindow(hwnd, SW_RESTORE);
		  break;
	  case XM_HIDE:
		  ShowWindow(hwnd, SW_HIDE);
		  break;
	  case XM_EXIT:
      OnFinalTray();
		  break;

    default:
      break;
  }
  #endif

  return 0;
}


BOOL ontray_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  switch(msg)
  {
    case WM_CLOSE:
      #if IDI_TRAY
      ShowWindow(hwnd, 0);
      #else
      PostQuitMessage(0);
      #endif
      break;

    case WM_DESTROY:
      #if IDI_TRAY
      OnFinalTray();
      #else
      PostQuitMessage(0);
      #endif
      break;      

    #if IDI_TRAY
    case XM_TRAY:
      return OnXM_TRAY(hwnd, msg, wparam, lparam);
      break;
    #endif
  }

  return 0;
}


void init_tray(HINSTANCE inst, HWND hwnd)
{
  #if IDI_TRAY
  int8_t title[128];
  sprintf(title, " (%d) running...", (int32_t)GetCurrentThreadId());
  OnInitTray( (void*)inst,(void*)hwnd,IDI_TRAY,title);
  #endif
}

#endif