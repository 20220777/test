#include <xm.h>
#include <locale.h>

XWND wnd;



#define TOP_TITLE   "sift.kit Tester"


/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/*                      Definition of the action color                         */
/*                                                                             */
/*                                                                             */
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
#define COLOR_SYSTEM_RUN                 RGB(0x00, 0x00, 0xFF)
#define COLOR_SYSTEM_DOWN                RGB(0xAA, 0x00, 0x00)
#define COLOR_CONNECTED                  RGB(0x00, 0xFF, 0x00)
#define COLOR_DISCONNECTED               RGB(0xFF, 0x00, 0x00)
#define COLOR_RCVD1                      RGB(0xFF, 0x99, 0x00)
#define COLOR_RCVD2                      RGB(0x33, 0xFF, 0x33)
#define COLOR_SENT1                      COLOR_RCVD1
#define COLOR_SENT2                      COLOR_RCVD2
#define COLOR_FAIL                       RGB(0xAA, 0xFF, 0x0F)
#define COLOR_IDLE                       (COLOR_SYSTEM_RUN|COLOR_CONNECTED)

#define COLOR_WHITE                      RGB(0xFF, 0xFF, 0xFF)
#define COLOR_CRITICAL                   RGB(0xFF, 0, 0)
#define COLOR_READY                      RGB(0xFF, 0xAA, 0x55)
#define COLOR_ON                         RGB(0, 0xFF, 0)
#define COLOR_OFF                        RGB(0xFF, 0x33, 0x33)



/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/*                                 Control widget                              */
/*                                                                             */
/*                                                                             */
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/


/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/*                             WND Subclassing                                 */
/*                                                                             */
/*                                                                             */
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/






/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/*                                   WND                                       */
/*                                                                             */
/*                                                                             */
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/



//
//LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
//{
//	HDC hdc;
//	PAINTSTRUCT ps;
//	HFONT font, oldfont;
//	char str[]="ÆùÆ® Test 1234";
//	HBRUSH MyBrush, OldBrush;
//	switch(iMessage) {
//	case WM_PAINT:
//		hdc=BeginPaint(hWnd, &ps);
//		MyBrush=CreateHatchBrush(HS_CROSS,RGB(0,0,255));
//		OldBrush=(HBRUSH)SelectObject(hdc,MyBrush);
//		Rectangle(hdc,50,50,400,200);
//		SelectObject(hdc,OldBrush);
//
//		font=CreateFont(30,0,0,0,0,0,0,0,HANGEUL_CHARSET,0,0,0,0,"±Ã¼­");
//		oldfont=(HFONT)SelectObject(hdc,font);
//		SetTextColor(hdc,RGB(255,0,0));
//		SetBkColor(hdc,RGB(255,255,0));
//		TextOut(hdc, 100,100,str,strlen(str));
//		SetBkMode(hdc,TRANSPARENT);
//		TextOut(hdc, 100, 150,str,strlen(str));
//
//		SelectObject(hdc,oldfont);
//		DeleteObject(MyBrush);
//		DeleteObject(font);
//		EndPaint(hWnd, &ps);
//		return 0;
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		return 0;
//	}
//	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
//}


void fxDrawText(HWND hwnd, XWND* p)
{
  //int32_t i = 0;
  //for ( i=0 ; i<MAX_XM_ITEM ; i++ )
  //{
  //  if ( p->item[i].hwnd == hwnd )
  //    SetText(p->item[i].hwnd, p->item[i].cap, strlen(p->item[i].cap));
  //}
  //if ( p->item[XM_BUTTON1].hwnd != 0 )
  //{
  //  p->item[XM_BUTTON1].hdc = BeginPaint(p->item[XM_BUTTON1].hwnd, &p->item[XM_BUTTON1].ps);
  //  TextOut(p->item[XM_BUTTON1].hdc, 100, 50, "10", 2);
  //  //GetClientRect(p->item[XM_BUTTON1].hwnd, &p->item[XM_BUTTON1].rct);
  //  //DrawText(p->item[XM_BUTTON1].hdc,10,-1,&p->item[XM_BUTTON1].rct,DT_VCENTER);
  //  EndPaint(p->item[XM_BUTTON1].hwnd, &p->item[XM_BUTTON1].ps);
  //}
}



void* fxWM_CTLCOLORBTN(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  return 0;
}



void* fxWM_CTLCOLORSTATIC(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  return 0;
}

void* fxWM_CREATE(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  return 0 ;
}

void* fxWM_DESTROY(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  //codeXend(&wnd.codeX);
  return 0;
}


int32_t OpenFileDialog(void* hwnd, int8_t* fname, int8_t* ext)
{
  OPENFILENAME ofn;
  memset(&ofn, 0, sizeof(OPENFILENAME));
  ofn.lStructSize = sizeof(OPENFILENAME);
  ofn.hwndOwner = (HWND)hwnd;
  ofn.hInstance = 0;
  ofn.lpstrFilter = (ext == 0 ? _T("All\0*.*\0") : ext);
  ofn.lpstrDefExt = _T("");
  ofn.lpstrFile = fname;
  ofn.nMaxFile = 256;
  ofn.lpstrInitialDir = _T(".");
  ofn.lpstrTitle = _T("File Open ...");
  if (GetOpenFileName(&ofn) == 0)
  {
    return -1;
  }
  return 0;
}

void genRandom(HWND hwnd)
{
  int32_t e = 0;
  uint8_t rbit[1024] = {0};
  wchar_t msg[2048] = {0};
  uint8_t _bit[1024] = {0};
  uint8_t tmp[32] = {0};
  int32_t bit_count = 0;

  GetText(wnd.item[_IDC_EDIT_RBIT].hwnd, msg, 32);
  wcstombs(tmp, msg, wcslen(msg));
  bit_count = atoi(tmp);
  e = wnd.sifr.__sifr_random(wnd.sifr.h, rbit, bit_count);
  if ( e > 0 )
  {
    hexasc(_bit, rbit, e/8);
    mbstowcs(msg, _bit, strlen(_bit));
    SetText(wnd.item[_IDC_EDIT_RAND].hwnd, msg, wcslen(msg));
    LVLog(wnd.item[_IDC_LIST_READ].hwnd, 0, 0, "log", "random", "generate random number");
  }
  else
  {
    LVLog(wnd.item[_IDC_LIST_READ].hwnd, 0, 0, "log", "random", "generate random number fail (%08X)", (uint32_t)e);
  }


}

void loadModule(HWND hwnd)
{
  wchar_t fname[2048] = {0};
  uint8_t _fname[1024] = {0};
  int32_t e = 0;
  if ( OpenFileDialog(hwnd, fname, _T("dll")) < 0 ) return;


  SetText(wnd.item[_IDC_EDIT_MODULE].hwnd, fname, wcslen(fname));


  wcstombs(_fname, fname, wcslen(fname));

  e = load_sifr_kit(hwnd, &wnd.sifr, _fname);
  if ( e > 0 )
  {
    LVLog(wnd.item[_IDC_LIST_READ].hwnd, 0, 0, "log", "module", "module Open SUCCESS");

    if ( wnd.sifr.__sifr_init == 0 )
    {
      LVLog(wnd.item[_IDC_LIST_READ].hwnd, 0, 0, "log", "module", "Invalid module, Open Fail");
      return;
    }
    if ( wnd.sifr.__sifr_init(&wnd.sifr.h, wnd.sifr.p, wnd.sifr.sz) >= 0 )
    {
      LVLog(wnd.item[_IDC_LIST_READ].hwnd, 0, 0, "log", "module", "module Load SUCCESS");
    }
    else
    {
      LVLog(wnd.item[_IDC_LIST_READ].hwnd, 0, 0, "log", "module", "module Load Fail");
    }
  }
  else
  {
    LVLog(wnd.item[_IDC_LIST_READ].hwnd, 0, 0, "log", "module", "module Open Fail");
  }
}




void* init_window(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  wnd.item[_IDC_BUTTON_GEN].hwnd = GetDlgItem(hwnd, IDC_BUTTON_GEN);
  wnd.item[_IDC_BUTTON_LOAD].hwnd = GetDlgItem(hwnd, IDC_BUTTON_LOAD);
  wnd.item[_IDC_BUTTON_ENCODE].hwnd = GetDlgItem(hwnd, IDC_BUTTON_ENCODE);
  wnd.item[_IDC_BUTTON_DECODE].hwnd = GetDlgItem(hwnd, IDC_BUTTON_DECODE);

  wnd.item[_IDC_STATIC1].hwnd = GetDlgItem(hwnd, IDC_STATIC1);
  wnd.item[_IDC_STATIC2].hwnd = GetDlgItem(hwnd, IDC_STATIC2);
  wnd.item[_IDC_STATIC3].hwnd = GetDlgItem(hwnd, IDC_STATIC3);
  wnd.item[_IDC_STATIC4].hwnd = GetDlgItem(hwnd, IDC_STATIC4);
  wnd.item[_IDC_STATIC5].hwnd = GetDlgItem(hwnd, IDC_STATIC5);
  wnd.item[_IDC_STATIC6].hwnd = GetDlgItem(hwnd, IDC_STATIC6);
  wnd.item[_IDC_STATIC7].hwnd = GetDlgItem(hwnd, IDC_STATIC7);

  wnd.item[_IDC_EDIT_RAND].hwnd = GetDlgItem(hwnd, IDC_EDIT_RAND);
  wnd.item[_IDC_EDIT_RBIT].hwnd = GetDlgItem(hwnd, IDC_EDIT_RBIT);
  wnd.item[_IDC_EDIT_MODULE].hwnd = GetDlgItem(hwnd, IDC_EDIT_MODULE);
  wnd.item[_IDC_EDIT_KEY].hwnd = GetDlgItem(hwnd, IDC_EDIT_KEY);
  wnd.item[_IDC_EDIT_VECTOR].hwnd = GetDlgItem(hwnd, IDC_EDIT_VECTOR);
  wnd.item[_IDC_EDIT_PLAIN].hwnd = GetDlgItem(hwnd, IDC_EDIT_PLAIN);
  wnd.item[_IDC_EDIT_CIPHER].hwnd = GetDlgItem(hwnd, IDC_EDIT_CIPHER);

  wnd.item[_IDC_COMBO_TYPE].hwnd = GetDlgItem(hwnd, IDC_COMBO_TYPE);
  wnd.item[_IDC_COMBO_MODE].hwnd = GetDlgItem(hwnd, IDC_COMBO_MODE);

  wnd.item[_IDC_LIST_READ].hwnd = GetDlgItem(hwnd, IDC_LIST_READ);

  SetText(wnd.item[_IDC_BUTTON_LOAD].hwnd, _T("Load"), strlen("Load"));
  SetText(wnd.item[_IDC_STATIC2].hwnd, _T("암호모듈"), strlen("암호모듈"));


  SetText(wnd.item[_IDC_BUTTON_GEN].hwnd, _T("GEN"), strlen("GEN"));
  SetText(wnd.item[_IDC_STATIC1].hwnd, _T("난 수"), strlen("난 수"));
  SetText(wnd.item[_IDC_EDIT_RBIT].hwnd, _T("256"), strlen("256"));
  SetText(wnd.item[_IDC_BUTTON_ENCODE].hwnd, _T("ENCODE"), strlen("ENCODE"));
  SetText(wnd.item[_IDC_BUTTON_DECODE].hwnd, _T("DECODE"), strlen("DECODE"));



  SetText(wnd.item[_IDC_STATIC3].hwnd, _T("알고리즘"), strlen("알고리즘"));
  SetText(wnd.item[_IDC_STATIC4].hwnd, _T("키"), strlen("키"));
  SetText(wnd.item[_IDC_STATIC5].hwnd, _T("벡터"), strlen("벡터"));
  SetText(wnd.item[_IDC_STATIC6].hwnd, _T("평문"), strlen("평문"));
  SetText(wnd.item[_IDC_STATIC7].hwnd, _T("암호문"), strlen("암호문"));

	SendMessage(wnd.item[_IDC_COMBO_TYPE].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("ARIA"));
	SendMessage(wnd.item[_IDC_COMBO_TYPE].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("LEA"));
	SendMessage(wnd.item[_IDC_COMBO_TYPE].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("SEED"));
	SendMessage(wnd.item[_IDC_COMBO_TYPE].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("HIGHT"));
  SendMessage(wnd.item[_IDC_COMBO_TYPE].hwnd, CB_SETCURSEL, 0, 0 );

	SendMessage(wnd.item[_IDC_COMBO_MODE].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("ECB"));
	SendMessage(wnd.item[_IDC_COMBO_MODE].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("CBC"));
	SendMessage(wnd.item[_IDC_COMBO_MODE].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("CFB"));
	SendMessage(wnd.item[_IDC_COMBO_MODE].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("OFB"));
	SendMessage(wnd.item[_IDC_COMBO_MODE].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("CTR"));
  SendMessage(wnd.item[_IDC_COMBO_MODE].hwnd, CB_SETCURSEL, 0, 0 );

  InitListView(wnd.item[_IDC_LIST_READ].hwnd, 2048);

  return 0;
}

void* fxWM_INITDIALOG(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int8_t _top_title[256] = {0};
  wchar_t wcs[1024] = {0};
  int32_t e = 0;

  init_window(hwnd, msg, wparam, lparam);

  __on_center(0, hwnd);

  sprintf(_top_title, "%s : (%d) ", TOP_TITLE, (int32_t)GetCurrentThreadId());

  e = MultiByteToWideChar(CP_ACP, 0, _top_title, -1, wcs, strlen(_top_title)+1);

  SetWindowText(hwnd, wcs);


  return (void*)TRUE;
}




void CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime)
{
  KillTimer(hWnd, nIDEvent);
}



void* fxWM_COMMAND(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  switch(LOWORD(wparam))
  {
    case IDC_BUTTON_GEN:
      genRandom(hwnd);
      break;

    case IDC_BUTTON_LOAD:
      loadModule(hwnd);
      break;


    default:
      ontray_command(hwnd, msg, wparam, lparam);
      break;
  }

  return (void*)TRUE;
}



void* fxWM_NOTIFY(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  return (void*)TRUE;
}

void* fxWM_DRAWITEM(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{

  return (void*)TRUE;
}


void* fxWM_PAINT(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  fxDrawText(hwnd, &wnd);
  InvalidateRect(hwnd, 0, TRUE);
  return (void*)0;
}

static uint8_t tmr = 0;

BOOL CALLBACK dlgproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  uint8_t r = 0;
  switch(msg)
  {
    case WM_INITDIALOG:
      r = (BOOL)fxWM_INITDIALOG(hwnd, msg, wparam, lparam);
      break;

    case WM_CREATE:
      r = (BOOL)fxWM_CREATE(hwnd, msg, wparam, lparam);
      break;

    case WM_COMMAND:
      r = (BOOL)fxWM_COMMAND(hwnd, msg, wparam, lparam);
      break;

    case WM_NOTIFY:
      r = (BOOL)fxWM_NOTIFY(hwnd, msg, wparam, lparam);
      break;

    case WM_PAINT:
      return (BOOL)fxWM_PAINT(hwnd, msg, wparam, lparam);
      break;

    case WM_DRAWITEM:
      (BOOL)fxWM_DRAWITEM(hwnd, msg, wparam, lparam);
      break;


    case WM_CTLCOLORBTN:
      SetTextColor((HDC)wparam, RGB(255,255,255));
      SetBkMode((HDC)wparam, TRANSPARENT);
      return (BOOL)fxWM_CTLCOLORBTN(hwnd, msg, wparam, lparam);
      break;

    case WM_CTLCOLORSTATIC:
      SetTextColor((HDC)wparam, RGB(0,0,0));
      SetBkMode((HDC)wparam, TRANSPARENT);
      return (BOOL)fxWM_CTLCOLORSTATIC(hwnd, msg, wparam, lparam);

      break;


    case WM_TIMER:
      //if ( tmr%2 )
      //{
      //  SetBkColorMessage(hwnd, &wnd.item[XM_STATIC2], RGB(0, 0xFF,0));
      //}
      //else
      //{
      //  SetBkColorMessage(hwnd, &wnd.item[XM_STATIC2], RGB(0xFF, 0xFF,0));
      //}
      //tmr++;
      //InvalidateRect(hwnd, 0, TRUE);      
      break;




    case XWM_TRANSFER:
      //fxTransfer(hwnd, msg, wparam, lparam);
      break;


    case WM_CLOSE:
    case WM_DESTROY:
      PostQuitMessage(0);

    default:
      return ontray_proc(hwnd, msg, wparam, lparam);
      break;
  }

  return r;
}



void setup(HINSTANCE hinst, HINSTANCE hpinst, LPSTR cmd, int32_t nshow)
{
  wnd.hinst[0] = hinst;
  wnd.hinst[1] = hpinst;

}


int32_t WINAPI WinMain(HINSTANCE hinst, HINSTANCE hpinst, LPSTR cmd, int32_t nshow)
{
  setup(hinst, hpinst, cmd, nshow);


  setlocale(LC_ALL, "Korean");
  DialogBox(hinst, (LPCSTR)IDD_DIALOG1, HWND_DESKTOP, (DLGPROC)dlgproc);
  return TRUE;
}
