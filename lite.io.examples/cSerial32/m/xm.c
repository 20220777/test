#include <xm.h>
#include <xcommon.h>
#include <imtif.h>
#include <nutil.h>

#define MAX_LIST_ITEM    0x7FFFFFFF
#define COUNT_MOD        0x7F


#if __WIN32__
#pragma pack(1)
#endif
typedef struct
{
  imtif _imtif;
  int32_t fd;
  uint8_t buf[32];
} cnserial;
#if __WIN32__
#pragma pack()
#endif


XWND wnd;



cnserial _nserial;

#define TOP_TITLE   TEXT("Won-Sok Yoo & Seung-Hyeok SHIN")


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

#define COLOR_READY                      RGB(0xFF, 0xAA, 0x55)
#define COLOR_ON                         RGB(0, 0xFF, 0)
#define COLOR_OFF                        RGB(0xFF, 0x33, 0x33);









/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/*                                  usr functions                              */
/*                                                                             */
/*                                                                             */
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/

//
//void findout_prime_numbers()
//{
//  long long prime[2]={0, };
//  long long result[MAX_BUF_SZ]={0, };
//  long long count = 0;
//  long long i = 0;
//  int8_t tmp[32];
//
//  GetText(wnd.item[EDIT_MIN_N].hwnd, tmp, 32);
//  prime[0] = atoll(tmp);
//
//  GetText(wnd.item[EDIT_MAX_N].hwnd, tmp, 32);
//  prime[1] = atoll(tmp);
//
//  count = __get_prime_set(prime, result, 0);
//
//  SendMessage(wnd.item[COMBO_PRIMES].hwnd, CB_RESETCONTENT, 0, 0);
//  for ( i=0 ; i<count ; i++ )
//  {
//    sprintf(tmp, "%lld", result[i]);
//    SendMessage(wnd.item[COMBO_PRIMES].hwnd, CB_ADDSTRING, 0, (LPARAM)tmp);
//  }
//  SendMessage(wnd.item[COMBO_PRIMES].hwnd, CB_SETCURSEL, 0, 0);
//}



int32_t nserial_connected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnserial* p = (cnserial*)o;
  printf(" nserial_connected   ->   %08X\r\n", sz);
  return 0;
}

int32_t nserial_disconnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnserial* p = (cnserial*)o;
  printf(" nserial_disconnected   ->   %08X \r\n", sz);

  return 0;
}


int32_t nserial_read(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnserial* p = (cnserial*)o;
  //printf(" nserial_read   ->   %08X [%s]\r\n", sz, b);

  GetText(wnd.item[COMBO_R_ASC_HEX].hwnd, wnd.item[COMBO_R_ASC_HEX].txt, MAX_TITLE);

  if ( wnd.item[COMBO_R_ASC_HEX].txt[0] == 'A' )
  {
    InsertLVText(wnd.item[LIST_READ].hwnd, MAX_LIST_ITEM, "%s", b);
  }
  else
  {
    int32_t s = 0;
    to_raw(b, sz, wnd.item[LIST_READ].txt, &s);
    InsertLVText(wnd.item[LIST_READ].hwnd, MAX_LIST_ITEM, "%s", wnd.item[LIST_READ].txt);
  }

  return 0;
}



int32_t nserial_open(cnserial* p)
{
  int32_t e = 0;
  int8_t _comport[32] = {0};
  int8_t _baudrate[32] = {0};
  int8_t _json[1024] = {0};
  int8_t _argv[3][256] = {0};

  p->_imtif.callback[IMTIF_CALLBACK_CONNECTED] = nserial_connected;
  p->_imtif.callback[IMTIF_CALLBACK_DISCONNECTED] = nserial_disconnected;
  p->_imtif.callback[IMTIF_CALLBACK_READ] = nserial_read;

  e = GetText(wnd.item[EDIT_COMPORT].hwnd, _comport, 32);
  e = GetText(wnd.item[EDIT_BAUDRATE].hwnd, _baudrate, 32);

  sprintf(_json, 
          "{"
            "\"PORT\":\"%s\","
            "\"BAUDRATE\":\"%s\","
            "\"DATABIT\":\"8\","
            "\"STOPBIT\":\"1\","
            "\"PARITYBIT\":\"0\","
            "\"SYNC\":\"DISABLE\""
          "}",
          _comport,
          _baudrate
  );

  e = p->fd = __serial_open(&p->_imtif.h, _json, p->buf, 1, p->_imtif.callback, p);
  return e;
}


int32_t nserial_close(cnserial* p)
{
  return __serial_close(&p->_imtif.h);
}





int32_t nserial_write(cnserial* p, int8_t* txt, int32_t sz)
{
  return __serial_write(p->_imtif.h, p->fd, txt, sz, 0, 0);
}



void COMPortOpen()
{
  int8_t ftxt[32] = {0};

  if ( GetText(wnd.item[BUTTON_OPEN].hwnd, ftxt, 32) > 0 )
  {
    if ( __compare_str(ftxt, "Open", 4 ) == 0 )
    {
      if ( nserial_open(&_nserial) > 0 )
      {
        SetText(wnd.item[BUTTON_OPEN].hwnd, "Close", 5);
      }
      else
      {
        nserial_close(&_nserial);
      }
    }
    else if ( __compare_str(ftxt, "Close", 5 ) == 0 )
    {
      nserial_close(&_nserial);
      SetText(wnd.item[BUTTON_OPEN].hwnd, "Open", 4);
    }
  }

}



void COMPortWrite()
{
  int8_t ftxt[512] = {0};
  int8_t htxt[1024] = {0};
  int32_t e = 0;

  GetText(wnd.item[COMBO_W_ASC_HEX].hwnd, wnd.item[COMBO_W_ASC_HEX].txt, MAX_TITLE);
  e = GetText(wnd.item[EDIT_TXT].hwnd, ftxt, 512);
  if ( wnd.item[COMBO_W_ASC_HEX].txt[0] == 'A' )
  {
    nserial_write(&_nserial, ftxt, e);
  }
  else
  {
    e = __string_to_hex(ftxt, htxt);
    htxt[e] = 0;
    nserial_write(&_nserial, htxt, e);
  }
}


void ListViewClear()
{
  ClearListView(wnd.item[LIST_READ].hwnd);
}
























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

void* SetBackgroundColor(xWnd* p, COLORREF color)
{
  HDC memdc;
  HBITMAP hbmp, obmp;

  if ( p == 0 ) return 0;
  if ( p->hwnd == 0 ) return 0;

  GetClientRect(p->hwnd, &p->rct);

  p->hdc = BeginPaint(p->hwnd, &p->ps);
  if ( p->hbrush ) DeleteObject(p->hbrush);
  p->hbrush = CreateSolidBrush(color);

  memdc = CreateCompatibleDC(p->hdc);
  hbmp = CreateCompatibleBitmap(p->hdc, (p->rct.right)-(p->rct.left), (p->rct.bottom)-(p->rct.top));

  obmp = SelectObject(memdc, hbmp);

  SetBkColor(memdc, color);

  SelectObject(memdc, obmp);

  DeleteObject(hbmp);
  DeleteObject(memdc);

  EndPaint(p->hwnd, &p->ps);
  return (void*)p->hbrush;
}


void* SetBkColorMessage(HWND hwnd, xWnd* p, COLORREF color)
{
  p->color[0] = color;
  PostMessage(hwnd, WM_CTLCOLORSTATIC, 0, color);
  InvalidateRect(hwnd, 0, TRUE);
  return 0;
}



void* DrawCircle(HWND hwnd)
{
  HDC                hdc;
  RECT               rct;
  HDC                memdc;
  HGDIOBJ            oldobj;
  HBRUSH             hbrsh;
  PAINTSTRUCT        ps;


  hdc = GetDC(hwnd);
  hbrsh = CreateSolidBrush(RGB(0xFF, 0, 0));
  oldobj = SelectObject(hdc, hbrsh);

  //Ellipse(hdc, 0, 0, 230, 230);


  SetClassLong(hwnd, GCL_HBRBACKGROUND, (LONG)hbrsh);

  
  SelectObject(hdc, oldobj);
  DeleteObject(hbrsh);
  ReleaseDC(hwnd, hdc);


  //GetClientRect(hwnd, &rct);
  //hdc = BeginPaint(hwnd, &ps);
  //hbrsh = CreateSolidBrush(RGB(0xFF, 0, 0));
  //odc = SelectObject(hdc, hbrsh);
  //
  //FillRect(hdc, &rct, hbrsh);
  ////Ellipse(hdc, rct.left, rct.top, rct.right, rct.bottom);
  //SelectObject(hdc, odc);
  //DeleteObject(odc);
  //EndPaint(hwnd, &ps);
  //DeleteObject(hbrsh);


  //hdc = GetDC(hwnd);
  ////memdc = CreateCompatibleDC(hdc);
  ////odc = SelectObject(memdc, memdc); 
  //Ellipse(hdc, 0, 0, 30, 30);

  ////SelectObject(hdc, odc);
  ////DeleteObject(memdc);
  //ReleaseDC(hwnd, hdc);
  //DeleteDC(hdc);

  return 0;
}








/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/* WebSocket                                                                   */
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
/*                                 CODE X                                      */
/*                                                                             */
/*                                                                             */
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/




void* fxCallback(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
   //LVLog( wnd.item[XM_LIST1], wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "Socket", " codeXStatusSocket --->  %04X %04X %08X\r\n", 0x0000FFFF&(uint32_t)msg, (0xFFFF0000&(uint32_t)msg)>>16, (uint32_t)lparam );



  switch( HIWORD((uint32_t)msg) )
  {
	//case XHTTP:
 //   break;
	//case XHTTPD:
 //   break;
	//case XPACKET:
 //   break;
	//case XPROTOCOL:
 //   break;
	//case XSERIAL:
 //   fxCallbackSerial(hwnd, msg, wparam, lparam);
 //   break;
	//case XSOCKET:
 //   fxCallbackSocket(hwnd, msg, wparam, lparam);
 //   break;
	//case XWEBSOCKET:
 //   fxCallbackWebSocket(hwnd, msg, wparam, lparam);
 //   break;
	//case XXML:
 //   break;
  }

	return 0;
}




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

int32_t getWindowXMID(HWND hwnd)
{
  //int32_t xm_id = XM_STATIC_1;
  //for ( ; xm_id < MAX_XM_ITEM ; xm_id++ )
  //{
  //  if ( hwnd == wnd.item[xm_id].hwnd ) break;
  //}
  //return xm_id;
  return 0;
}



void* fxStaticProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int32_t id = getWindowXMID((HWND)lparam);
  switch(msg)
  {
    case WM_CTLCOLORSTATIC:
      return (BOOL)SetBackgroundColor(&wnd.item[id], COLOR_READY);

      //return (BOOL)SetBackgroundColor(&wnd.item[XM_STATIC1], (COLORREF)lparam);
      break;

    case WM_PAINT:
      InvalidateRect(hwnd, 0, TRUE);
      break;
  }



  return CallWindowProc(wnd.item[id].wproc, hwnd, msg, wparam, lparam);
}




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
void* fxInitWindow(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int32_t i = 0;

  //wnd.tabwnd[WCRYPT] = CreateDialogParam(wnd.hinst[0], MAKEINTRESOURCE(IDD_FORMVIEW_CRYPT), wnd.item[TAB_CONTROL].hwnd, (DLGPROC)wcryptDlgProc, lparam);
  //SetParent(wnd.tabwnd[WCRYPT], hwnd);
  //SetWindowPos(wnd.tabwnd[WCRYPT], 0, wnd.rct.left+TAB_LEFT_MARGIN, wnd.rct.top+TAB_TOP_MARGIN, wnd.rct.right, wnd.rct.bottom, SWP_NOZORDER|SWP_SHOWWINDOW);
  //ShowWindow(wnd.tabwnd[WCRYPT], SHOW_MODE[WCRYPT]);



  //wnd.tabwnd[WSIFR] = CreateDialogParam(wnd.hinst[0], MAKEINTRESOURCE(IDD_FORMVIEW_SIFR), wnd.item[TAB_CONTROL].hwnd, (DLGPROC)wsifrDlgProc, lparam);
  //SetParent(wnd.tabwnd[WSIFR], hwnd);
  //SetWindowPos(wnd.tabwnd[WSIFR], 0, wnd.rct.left+TAB_LEFT_MARGIN, wnd.rct.top+TAB_TOP_MARGIN, wnd.rct.right, wnd.rct.bottom, SWP_NOZORDER|SWP_SHOWWINDOW);
  //ShowWindow(wnd.tabwnd[WSIFR], SHOW_MODE[WSIFR]);

  //wnd.tabwnd[WCODEX] = CreateDialogParam(wnd.hinst[0], MAKEINTRESOURCE(IDD_FORMVIEW_CODEX), wnd.item[TAB_CONTROL].hwnd, (DLGPROC)wCodeXDlgProc, lparam);
  //SetParent(wnd.tabwnd[WCODEX], hwnd);
  //SetWindowPos(wnd.tabwnd[WCODEX], 0, wnd.rct.left+TAB_LEFT_MARGIN, wnd.rct.top+TAB_TOP_MARGIN, wnd.rct.right, wnd.rct.bottom, SWP_NOZORDER|SWP_SHOWWINDOW);
  //ShowWindow(wnd.tabwnd[WCODEX], SHOW_MODE[WCODEX]);

  //wnd.tabwnd[WPRIME] = CreateDialogParam(wnd.hinst[0], MAKEINTRESOURCE(IDD_FORMVIEW_PRIME), wnd.item[TAB_CONTROL].hwnd, (DLGPROC)wPrimeDlgProc, lparam);
  //SetParent(wnd.tabwnd[WPRIME], hwnd);
  //SetWindowPos(wnd.tabwnd[WPRIME], 0, wnd.rct.left+TAB_LEFT_MARGIN, wnd.rct.top+TAB_TOP_MARGIN, wnd.rct.right, wnd.rct.bottom, SWP_NOZORDER|SWP_SHOWWINDOW);
  //ShowWindow(wnd.tabwnd[WPRIME], SHOW_MODE[WPRIME]);

  //for ( i=0; ; i++)
  //{
  //  if ( SHOW_MODE[i] == SW_SHOW )
  //  {
  //    break;
  //  }
  //}  
  //SendMessage(wnd.tabwnd[TAB_CONTROL], TCM_SETCURSEL, (WPARAM)i, 0);

  //InvalidateRect(wnd.tabwnd[TAB_CONTROL], 0, TRUE);

  //wsifrInit(wnd.tabwnd[WDRAW], &wnd._sifr);
  ////wCodeXInit(wnd.tabwnd[WCODEX], &wnd.wcodex);
  ////wPrimeInit(wnd.tabwnd[WPRIME], &wnd.wprime);






  return 0;
}

void* fxWM_CTLCOLORSTATIC(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  //int32_t id = getWindowXMID((HWND)lparam);

  //return SetBackgroundColor(&wnd.item[id], wnd.item[id].color[0]);
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



//void* fxWM_INIT_TABCONTROL(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
//{
//  TCITEM tci = {0};
//  wnd.item[TAB_CONTROL].hwnd = GetDlgItem(hwnd, IDC_TAB_CONTROL);
//
//  tci.mask = TCIF_TEXT;
//
//
//  tci.pszText = "crypt";
//  SendMessage(wnd.item[TAB_CONTROL].hwnd, TCM_INSERTITEM, (WPARAM)(int32_t)WCRYPT, (LPARAM)&tci);
//
//  tci.pszText = "sifr";
//  SendMessage(wnd.item[TAB_CONTROL].hwnd, TCM_INSERTITEM, (WPARAM)(int32_t)WSIFR, (LPARAM)&tci);
//
//  //tci.pszText = "code X";
//  //SendMessage(wnd.item[TAB_CONTROL].hwnd, TCM_INSERTITEM, (WPARAM)(int32_t)WCODEX, (LPARAM)&tci);
//
//  //tci.pszText = "prime";
//  //SendMessage(wnd.item[TAB_CONTROL].hwnd, TCM_INSERTITEM, (WPARAM)(int32_t)WPRIME, (LPARAM)&tci);
//
//
//  GetClientRect(wnd.item[TAB_CONTROL].hwnd, &wnd.rct);
//  SendMessage(wnd.item[TAB_CONTROL].hwnd, TCM_ADJUSTRECT, FALSE, (LPARAM)&wnd.rct);
//}
//


void* fxWM_INITDIALOG(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int8_t _top_title[256];

  sprintf(_top_title, TEXT("%s : (%d) "), TOP_TITLE, (int32_t)GetCurrentThreadId());
  SetWindowText(hwnd, _top_title);

  wnd.item[BUTTON_OPEN].hwnd = GetDlgItem(hwnd, IDC_BUTTON_OPEN);
  wnd.item[BUTTON_WRITE].hwnd = GetDlgItem(hwnd, IDC_BUTTON_WRITE);
  wnd.item[BUTTON_CLEAR].hwnd = GetDlgItem(hwnd, IDC_BUTTON_CLEAR);
  wnd.item[EDIT_COMPORT].hwnd = GetDlgItem(hwnd, IDC_EDIT_COMPORT);
  wnd.item[EDIT_BAUDRATE].hwnd = GetDlgItem(hwnd, IDC_EDIT_BAUDRATE);
  wnd.item[EDIT_TXT].hwnd = GetDlgItem(hwnd, IDC_EDIT_TXT);
  wnd.item[COMBO_W_ASC_HEX].hwnd = GetDlgItem(hwnd, IDC_COMBO_W_ASC_HEX);
  wnd.item[COMBO_R_ASC_HEX].hwnd = GetDlgItem(hwnd, IDC_COMBO_R_ASC_HEX);
  wnd.item[CHECK_TMR].hwnd = GetDlgItem(hwnd, IDC_CHECK_TMR);
  wnd.item[LIST_READ].hwnd = GetDlgItem(hwnd, IDC_LIST_READ);

  SetText(wnd.item[BUTTON_OPEN].hwnd, "Open", 4);
  SetText(wnd.item[BUTTON_WRITE].hwnd, "Write", 5);
  SetText(wnd.item[BUTTON_CLEAR].hwnd, "Clear", 5);
  SetText(wnd.item[EDIT_COMPORT].hwnd, "COM3", 4);
  SetText(wnd.item[EDIT_BAUDRATE].hwnd, "115200", 115200);

  SendMessage(wnd.item[COMBO_W_ASC_HEX].hwnd, CB_ADDSTRING, 0, (LPARAM)"ASCII");
  SendMessage(wnd.item[COMBO_W_ASC_HEX].hwnd, CB_ADDSTRING, 0, (LPARAM)"HEXA");
  SendMessage(wnd.item[COMBO_W_ASC_HEX].hwnd, CB_SETCURSEL, 0, 0 );

  SendMessage(wnd.item[COMBO_R_ASC_HEX].hwnd, CB_ADDSTRING, 0, (LPARAM)"ASCII");
  SendMessage(wnd.item[COMBO_R_ASC_HEX].hwnd, CB_ADDSTRING, 0, (LPARAM)"HEXA");
  SendMessage(wnd.item[COMBO_R_ASC_HEX].hwnd, CB_SETCURSEL, 0, 0 );

  InitListView(wnd.item[LIST_READ].hwnd);


  return (void*)TRUE;
}


void* fxWM_COMMAND(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  switch(LOWORD(wparam))
  {
    case IDC_BUTTON_OPEN:
      COMPortOpen();
      break;

    case IDC_BUTTON_WRITE:
      COMPortWrite();
      break;

    case IDC_BUTTON_CLEAR:
      ListViewClear();
      break;

    default:
      break;
  }

  return (void*)TRUE;
}


void* fxWM_PAINT(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{

  InvalidateRect(hwnd, 0, TRUE);
  return (void*)0;
}

static uint8_t tmr = 0;

BOOL CALLBACK dlgproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  switch(msg)
  {
    case WM_INITDIALOG:
      //SetTimer(hwnd, 1, 1000, 0);
      return (BOOL)fxWM_INITDIALOG(hwnd, msg, wparam, lparam);

    case WM_CREATE:
      return (BOOL)fxWM_CREATE(hwnd, msg, wparam, lparam);

    case WM_COMMAND:
      return (BOOL)fxWM_COMMAND(hwnd, msg, wparam, lparam);

    case WM_PAINT:
      return (BOOL)fxWM_PAINT(hwnd, msg, wparam, lparam);
      break;


    case WM_CTLCOLORSTATIC:
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

    case WM_CLOSE:
    case WM_DESTROY:
      PostQuitMessage(0);
      break;

    default:
      //return onTrayProc(hwnd, msg, wparam, lparam);
      break;
  }

  return 0;
}



void setup(HINSTANCE hinst, HINSTANCE hpinst, LPSTR cmd, int32_t nshow)
{
  wnd.hinst[0] = hinst;
  wnd.hinst[1] = hpinst;

  //memset(&wnd.codeX, 0, sizeof(CodeX));

  //wnd.codeX.callback = fxCallback;
  //wnd.codeX.obj = &wnd;
}


int32_t WINAPI WinMain(HINSTANCE hinst, HINSTANCE hpinst, LPSTR cmd, int32_t nshow)
{
  setup(hinst, hpinst, cmd, nshow);

  DialogBox(hinst, (LPCSTR)IDD_DIALOG1, HWND_DESKTOP, (DLGPROC)dlgproc);
  return TRUE;
}
