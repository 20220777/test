#include <xm.h>

#define COUNT_MOD        0x7F

XWND wnd;


#define TOP_TITLE   TEXT("bitGridX Viewer. Powered by CODE X")


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
//void* SetBackgroundColor(HWND hwnd, COLORREF color)
//{
//  HDC                hdc;
//  HBRUSH             hbrsh, obrsh;
//  PAINTSTRUCT        ps;
//
//  hdc = BeginPaint(hwnd, &ps);
//  hbrsh = CreateSolidBrush(color);
//  //obrsh = (HBRUSH)SelectObject(hdc, hbrsh);
//  SetBkColor(hdc, color);
//  //Ellipse(hdc, 0, 0, 5, 5);
//  //SelectObject(hdc, obrsh);
//  //DeleteObject(hbrsh);
//  EndPaint(hwnd, &ps);
//  return (void*)obrsh;
//}
//
//void* SetBackgroundColor(XSubWnd* p, COLORREF color)
//{
//  p->hdc = BeginPaint(p->hwnd, &p->ps);
//  if ( p->hbrush ) DeleteObject(p->hbrush);
//  p->hbrush = CreateSolidBrush(color);
//  SetBkColor(p->hdc, color);
//  EndPaint(p->hwnd, &p->ps);
//  return (void*)p->hbrush;
//}

void* baseFont(int32_t sz)
{
  return CreateFont(sz,0,0,0,0,0,0,0,ANSI_CHARSET,3,2,1,	VARIABLE_PITCH | FW_BOLD,"Courier New");
}
//void* SetBackgroundColor(XSubWnd* p, COLORREF color)
//{
//  HDC memdc;
//  HBITMAP hbmp, obmp;
//  HFONT  hfont;
//
//  if ( p == 0 ) return 0;
//  if ( p->hwnd == 0 ) return 0;
//
//  GetClientRect(p->hwnd, &p->rct);
//
//  p->hdc = BeginPaint(p->hwnd, &p->ps);
//
//  SetBkMode(p->hdc, TRANSPARENT);
//  SetTextColor(p->hdc, RGB(0,0,0));
//  DrawText(p->hdc, "A", 1, &p->rct, DT_CENTER);
//
//  EndPaint(p->hwnd, &p->ps);
//  return (void*)0;
//}



void* SetBackgroundColor(XSubWnd* p, COLORREF color)
{
  HDC memdc;
  HBITMAP hbmp, obmp;
  HFONT  hfont;

  if ( p == 0 ) return 0;
  if ( p->hwnd == 0 ) return 0;

  GetClientRect(p->hwnd, &p->rct);

  p->hdc = BeginPaint(p->hwnd, &p->ps);
  if ( p->hbrush ) DeleteObject(p->hbrush);

  p->hbrush = CreateSolidBrush(color);
  memdc = CreateCompatibleDC(p->hdc);
  hbmp = CreateCompatibleBitmap(p->hdc, (p->rct.right)-(p->rct.left), (p->rct.bottom)-(p->rct.top));
  obmp = SelectObject(memdc, hbmp);

  SelectObject(memdc, obmp);

  DeleteObject(hbmp);
  DeleteDC(memdc);

  DeleteDC(p->hdc);
  EndPaint(p->hwnd, &p->ps);

  return (void*)p->hbrush;
}

//void* SetBackgroundColor(XSubWnd* p, COLORREF color)
//{
//  HDC memdc;
//  HBITMAP hbmp, obmp;
//
//  if ( p == 0 ) return 0;
//  if ( p->hwnd == 0 ) return 0;
//
//  GetClientRect(p->hwnd, &p->rct);
//
//
//  p->hdc = GetDC(p->hwnd);
//  if ( p->hbrush ) DeleteObject(p->hbrush);
//  p->hbrush = CreateSolidBrush(color);
//
//  memdc = CreateCompatibleDC(p->hdc);
//  hbmp = CreateCompatibleBitmap(p->hdc, (p->rct.right)-(p->rct.left), (p->rct.bottom)-(p->rct.top));
//
//  obmp = SelectObject(memdc, hbmp);
//
//  SetBkColor(memdc, color);
//
//  SelectObject(memdc, obmp);
//
//  DeleteObject(hbmp);
//  DeleteObject(memdc);
//
//  ReleaseDC(p->hwnd, p->hdc);
//  return (void*)p->hbrush;
//}
//
//
//void* SetBackgroundColor(XSubWnd* p, COLORREF color)
//{
//  HDC memdc;
//  HBITMAP hbmp, obmp;
//
//  if ( p == 0 ) return 0;
//  if ( p->hwnd == 0 ) return 0;
//  p->hdc = GetDC(p->hwnd);
//  if ( p->hbrush ) DeleteObject(p->hbrush);
//  p->hbrush = CreateSolidBrush(color);
//
//
//  SetBkColor(p->hdc, color);
//
//  ReleaseDC(p->hwnd, p->hdc);
//  return (void*)p->hbrush;
//}


//void* SetBackgroundColor(XSubWnd* p, COLORREF color)
//{
//  p->hdc = BeginPaint(p->hwnd, &p->ps);
//  Ellipse(p->hdc, 0, 0, 50, 50);
//  EndPaint(p->hwnd, &p->ps);
//  return (void*)0;
//}


void* SetBkColorMessage(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  XSubWnd* p = (XSubWnd*)wparam;
  p->color[0] = (COLORREF)lparam;
  PostMessage(hwnd, msg, p, (COLORREF)lparam);
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

void fxWebSocketRouting(int8_t* b, int32_t sz)
{
  int32_t e = 0;
  int32_t idx = 0;
  int8_t  raw[1024];

  if ( wnd.codeX.modul[XWEBSOCKET].fdset == 0 ) return ;

  for(idx=0 ; idx<FD_SETSIZE ; idx++ )
  {
    if ( (wnd.codeX.modul[XWEBSOCKET].fdset+idx)->a[0] > 0 )
    {
      #if LVLOG_LEVEL_0
      if ( SendMessage(wnd.item[XM_CHECK2].hwnd, BM_GETCHECK, 0, 0) == BST_CHECKED )
      {
        raw_buffer(b, sz, raw);
        LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "WebSocket", "WebSocket Write [%d] %s \r\n", (wnd.codeX.modul[XWEBSOCKET].fdset+idx)->a[0], raw);
      }
      #endif

      wnd.codeX.setMessage(wnd.codeX.h, (void*)MAKELONG(FDSCRPTR, XWEBSOCKET), (void*)(wnd.codeX.modul[XWEBSOCKET].fdset+idx)->a[0], 0);
      wnd.codeX.setMessage(wnd.codeX.h, (void*)MAKELONG(WRITE, XWEBSOCKET), (void*)b, (void*)sz);
    }

    ////LVLog(gp->hitem[LIST_WSGW_WS_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "WebSocket", "Client[%d], %d, %08X \r\n", idx, gp->pm->mws.pack.info[idx].fd,gp->pm->mws.pack.info[idx].REG.SR);

    ////if ( (gp->pm->mws.pack.info[idx].fd > 0) && (gp->pm->mws.pack.info[idx].REG.SR&0x00000001) )
    //if ((gp->pm->mws.pack.info[idx].fd > 0) )//&& (gp->pm->mws.pack.info[idx].REG.SR & 0x00000001))
    //{
    //  //e = mtifWebSocketWrite(&gp->pm->mws.m, gp->pm->mws.pack.info[idx].fd, b, sz);
    //  e = mtifWebSocketWriteEx(&gp->pm->mws.m, gp->pm->mws.pack.info[idx].fd, b, sz, 0x02, 0, 0);
    //  if ( e > 0 )
    //  {
    //    #if LVLOG
    //    LVLog(gp->hitem[LIST_WSGW_WS_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "WebSocket", "Client[%d], %d = Write(%d, \"%s\", %d) \r\n", idx, e, gp->pm->mws.pack.info[idx].fd, vbuf, sz);
    //    #endif
    //    //LVLog(gp->hitem[LIST_WSGW_WS_LOG], gp->hitem[CHECK_WSGW_LOG], &gp->log, "log", "WebSocket", "%d = Write(%d, \"%s\", %d)", e, gp->pm->mws.pack.info[idx].fd, b, sz);
    //  }
    //}
    //mcsleep(10);
  }

}

/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/*                                  ROUTING                                    */
/*                                                                             */
/*                                                                             */
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
void fxTransfer(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  //fxDBWrite((int8_t*)wparam, (int32_t)lparam);
  //fxWebSocketRouting((uint8_t*)wparam, (int32_t)lparam);


  ////GetComboText(gp->hitem[COMBO_DISPLAY_TYPE_WSGW], st);

  //fprint_raw_buffer(0, (char*)lparam, (int)wparam, vbuf);
  //LVLog(gp->hitem[LIST_WSGW_WS_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "WebSocket", "%s", vbuf);
}



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

void fxResearch()
{
  wnd.protocol[2] = 'S';
  wnd.codeX.setMessage(wnd.codeX.h, (void*)MAKELONG(WRITE, XSERIAL), (void*)wnd.protocol, (void*)4);
  LVLog( wnd.item[XM_LIST1].hwnd, 0, MAX_LINE, &wnd.log, "log", "Serial", " [RES] Block %c Request \r\n", wnd.protocol[1]+1);
}


void* fxDrawBit(uint8_t* v, int32_t sz)
{
  int32_t i=0;
  int32_t idx = 0;
  if ( sz < 0 ) return 0;

  if (  wnd.protocol[2] == 'R' )
  {
    if ( v == 0 )
    {
      LVLog( wnd.item[XM_LIST1].hwnd, 0, MAX_LINE, &wnd.log, "log", "Serial", "No Response\r\n");
      for ( i=XM_STATIC_1, idx=0 ; i<=XM_STATIC_100 ; i+=4, idx++ )
      {
        wnd.item[i  ].SR = 0;
        wnd.item[i+1].SR = 0;
        wnd.item[i+2].SR = 0;
        wnd.item[i+3].SR = 0;
        SetBkColorMessage(wnd.item[i  ].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i  ], COLOR_READY);
        SetBkColorMessage(wnd.item[i+1].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+1], COLOR_READY);
        SetBkColorMessage(wnd.item[i+2].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+2], COLOR_READY);
        SetBkColorMessage(wnd.item[i+3].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+3], COLOR_READY);
      }
      return 0;
    }

    for ( i=XM_STATIC_1, idx=0 ; i<=XM_STATIC_100 ; i+=4, idx++ )
    {
      wnd.item[i  ].SR = (*(v+idx)&0x01)?1:0;
      wnd.item[i+1].SR = (*(v+idx)&0x02)?1:0;
      wnd.item[i+2].SR = (*(v+idx)&0x04)?1:0;
      wnd.item[i+3].SR = (*(v+idx)&0x08)?1:0;
      //SetBkColorMessage(wnd.item[i  ].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i  ], (*(v+idx)&0x01)?COLOR_WHITE:COLOR_READY);
      //SetBkColorMessage(wnd.item[i+1].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+1], (*(v+idx)&0x02)?COLOR_WHITE:COLOR_READY);
      //SetBkColorMessage(wnd.item[i+2].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+2], (*(v+idx)&0x04)?COLOR_WHITE:COLOR_READY);
      //SetBkColorMessage(wnd.item[i+3].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+3], (*(v+idx)&0x08)?COLOR_WHITE:COLOR_READY);
      //if ( wnd.item[i  ].SR == 1 ) SetBkColorMessage(wnd.item[i  ].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i  ], COLOR_READY);
      //if ( wnd.item[i+1].SR == 1 ) SetBkColorMessage(wnd.item[i+1].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+1], COLOR_READY);
      //if ( wnd.item[i+2].SR == 1 ) SetBkColorMessage(wnd.item[i+2].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+2], COLOR_READY);
      //if ( wnd.item[i+3].SR == 1 ) SetBkColorMessage(wnd.item[i+3].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+3], COLOR_READY);
    }
    fxResearch();
  }
  else
  {
    //if ( v == 0 )
    //{
    //  LVLog( wnd.item[XM_LIST1].hwnd, 0, MAX_LINE, &wnd.log, "log", "Serial", "No Response\r\n");
    //  for ( i=XM_STATIC_1, idx=0 ; i<=XM_STATIC_100 ; i+=4, idx++ )
    //  {
    //    if ( wnd.item[i  ].SR == 1 ) SetBkColorMessage(wnd.item[i  ].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i  ], COLOR_READY);
    //    if ( wnd.item[i+1].SR == 1 ) SetBkColorMessage(wnd.item[i+1].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+1], COLOR_READY);
    //    if ( wnd.item[i+2].SR == 1 ) SetBkColorMessage(wnd.item[i+2].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+2], COLOR_READY);
    //    if ( wnd.item[i+3].SR == 1 ) SetBkColorMessage(wnd.item[i+3].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+3], COLOR_READY);
    //  }
    //  return 0;
    //}

    for ( i=XM_STATIC_1, idx=0 ; i<=XM_STATIC_100 ; i+=4, idx++ )
    {
      if ( wnd.item[i  ].SR == 1 ) SetBkColorMessage(wnd.item[i  ].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i  ], (*(v+idx)&0x01)?COLOR_ON:COLOR_CRITICAL);
      else                         SetBkColorMessage(wnd.item[i  ].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i  ], COLOR_READY);
      if ( wnd.item[i+1].SR == 1 ) SetBkColorMessage(wnd.item[i+1].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+1], (*(v+idx)&0x02)?COLOR_ON:COLOR_CRITICAL);
      else                         SetBkColorMessage(wnd.item[i  ].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+1], COLOR_READY);
      if ( wnd.item[i+2].SR == 1 ) SetBkColorMessage(wnd.item[i+2].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+2], (*(v+idx)&0x04)?COLOR_ON:COLOR_CRITICAL);
      else                         SetBkColorMessage(wnd.item[i  ].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+2], COLOR_READY);
      if ( wnd.item[i+3].SR == 1 ) SetBkColorMessage(wnd.item[i+3].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+3], (*(v+idx)&0x08)?COLOR_ON:COLOR_CRITICAL);
      else                         SetBkColorMessage(wnd.item[i  ].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+3], COLOR_READY);
    }
  }
  return 0;
}



void* fxCallbackSerial(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int32_t fd=0;
  int8_t raw[1024];
  uint8_t v[32];
  int32_t sz = 0;
	switch( LOWORD((uint32_t)msg) )
	{
	case READ:
    raw_buffer((int8_t*)wparam, (int32_t)lparam, raw);
    LVLog( wnd.item[XM_LIST1].hwnd, 0, MAX_LINE, &wnd.log, "log", "Serial", "SERIAL READ (%d) %s\r\n", (uint32_t)lparam, raw);
    sz = jmt_hex_strm((int8_t*)(wparam+2), ((int32_t)lparam)-3, v);
    wnd.rflag = 1;
    fxDrawBit(v, sz);
		break;
  }
  return 0;
}


void* fxCallback(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
   //LVLog( wnd.hitem[XM_LIST1], wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "Socket", " codeXStatusSocket --->  %04X %04X %08X\r\n", 0x0000FFFF&(uint32_t)msg, (0xFFFF0000&(uint32_t)msg)>>16, (uint32_t)lparam );



  switch( HIWORD((uint32_t)msg) )
  {
	case XHTTP:
    break;
	case XHTTPD:
    break;
	case XPACKET:
    break;
	case XPROTOCOL:
    break;
	case XSERIAL:
    fxCallbackSerial(hwnd, msg, wparam, lparam);
    break;
	case XSOCKET:
    break;
	case XWEBSOCKET:
    break;
	case XXML:
    break;
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
  int32_t xm_id = XM_STATIC_1;
  for ( ; xm_id < MAX_XM_ITEM ; xm_id++ )
  {
    if ( hwnd == wnd.item[xm_id].hwnd ) break;
  }
  return xm_id;
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


int32_t get_history(int8_t* fname, int8_t* contents, int32_t sz)
{
  FILE* fp;
  int32_t e = 0;
  fp = fopen(fname, "r");
  if ( fp == 0 ) return -1;
  e = fread(contents, 1, sz, fp);
  fclose(fp);

  *(contents+e) = 0;

  return e;
}

int32_t set_history(int8_t* fname, int8_t* contents, int32_t sz)
{
  FILE* fp;
  int32_t e = 0;
  fp = fopen(fname, "w");
  fwrite(contents, 1, sz, fp);
  fclose(fp);

  return e;
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


void init_window(HWND hwnd, XWND* p)
{
  int32_t xm_id=XM_STATIC_1, idc_id = IDC_STATIC_1;
  int8_t caps[512] = {0};
  int32_t sz = 0;
  p->hdlg = hwnd;


  for ( ; idc_id<=IDC_STATIC_100; idc_id++, xm_id++ )
  {
    p->item[xm_id].hwnd  = GetDlgItem(hwnd, idc_id);
    sprintf(p->item[xm_id].cap, "%d", xm_id);
    p->item[xm_id].font[1] = baseFont(16);
    //SetFont(p->item[xm_id].hwnd, p->item[xm_id].font[1]);
    ////SetBkColor(GetDC(p->item[xm_id].hwnd), COLOR_READY);
    //SetText(p->item[xm_id].hwnd, p->item[xm_id].cap, strlen(p->item[xm_id].cap));
    //////p->item[xm_id].wproc = SetWindowLong(p->item[xm_id].hwnd, GWL_WNDPROC, (LONG)fxStaticProc);
  }
  p->item[XM_BUTTON1].hwnd       = GetDlgItem(hwnd, IDC_BUTTON1);
  p->item[XM_BUTTON2].hwnd       = GetDlgItem(hwnd, IDC_BUTTON2);
  p->item[XM_BUTTON3].hwnd       = GetDlgItem(hwnd, IDC_BUTTON3);
  p->item[XM_BUTTON4].hwnd       = GetDlgItem(hwnd, IDC_BUTTON4);
  p->item[XM_BUTTON5].hwnd       = GetDlgItem(hwnd, IDC_BUTTON5);
  p->item[XM_BUTTON6].hwnd       = GetDlgItem(hwnd, IDC_BUTTON6);

  p->item[XM_EDIT1].hwnd         = GetDlgItem(hwnd, IDC_EDIT1);
  p->item[XM_EDIT2].hwnd         = GetDlgItem(hwnd, IDC_EDIT2);
  p->item[XM_EDIT3].hwnd         = GetDlgItem(hwnd, IDC_EDIT3);
  p->item[XM_EDIT4].hwnd         = GetDlgItem(hwnd, IDC_EDIT4);
  p->item[XM_EDIT5].hwnd         = GetDlgItem(hwnd, IDC_EDIT5);
  p->item[XM_EDIT6].hwnd         = GetDlgItem(hwnd, IDC_EDIT6);

  p->item[XM_LIST1].hwnd         = GetDlgItem(hwnd, IDC_LIST1);


  InitListView(p->item[XM_LIST1].hwnd);

  //SetFont(p->item[XM_BUTTON1].hwnd, baseFont(16));
  //SetFont(p->item[XM_BUTTON2].hwnd, baseFont(16));
  //SetFont(p->item[XM_BUTTON3].hwnd, baseFont(16));
  //SetFont(p->item[XM_BUTTON4].hwnd, baseFont(16));
  //SetFont(p->item[XM_BUTTON5].hwnd, baseFont(16));
  p->item[XM_BUTTON1].font[1] = baseFont(16);
  p->item[XM_BUTTON2].font[1] = baseFont(16);
  p->item[XM_BUTTON3].font[1] = baseFont(16);
  p->item[XM_BUTTON4].font[1] = baseFont(16);
  p->item[XM_BUTTON5].font[1] = baseFont(16);


  //SetText(p->item[XM_BUTTON1].hwnd, "D1", 2);
  //SetText(p->item[XM_BUTTON2].hwnd, "D2", 2);
  //SetText(p->item[XM_BUTTON3].hwnd, "D3", 2);
  //SetText(p->item[XM_BUTTON4].hwnd, "D4", 2);
  //SetText(p->item[XM_BUTTON5].hwnd, "D5", 2);

  sprintf(p->item[XM_BUTTON1].cap, "D1");
  sprintf(p->item[XM_BUTTON2].cap, "D2");
  sprintf(p->item[XM_BUTTON3].cap, "D3");
  sprintf(p->item[XM_BUTTON4].cap, "D4");
  sprintf(p->item[XM_BUTTON5].cap, "D5");

  SetBkColorMessage(wnd.item[XM_BUTTON1].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON1], RGB(0, 0, 0xAA) );
  SetBkColorMessage(wnd.item[XM_BUTTON2].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON2], RGB(0, 0, 0xAA) );
  SetBkColorMessage(wnd.item[XM_BUTTON3].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON3], RGB(0, 0, 0xAA) );
  SetBkColorMessage(wnd.item[XM_BUTTON4].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON4], RGB(0, 0, 0xAA) );
  SetBkColorMessage(wnd.item[XM_BUTTON5].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON5], RGB(0, 0, 0xAA) );


  SetText(p->item[XM_BUTTON6].hwnd, "OPEN", 4);
  SetFont(p->item[XM_BUTTON6].hwnd, baseFont(16));


  if ( (sz = get_history("port", caps, 512)) < 0 )
  {
    sprintf(caps, "COM1");
    sz = 4;
  }
  SetText(p->item[XM_EDIT1].hwnd, caps, sz);
  SetFont(p->item[XM_EDIT1].hwnd, baseFont(24));

  if ( (sz = get_history("d1", caps, 512)) < 0 )
  {
    sprintf(caps, "D1");
    sz = 4;
  }
  SetText(p->item[XM_EDIT2].hwnd, caps, sz);
  SetFont(p->item[XM_EDIT2].hwnd, baseFont(16));

  if ( (sz = get_history("d1", caps, 512)) < 0 )
  {
    sprintf(caps, "D1");
    sz = 4;
  }
  SetText(p->item[XM_EDIT2].hwnd, caps, sz);
  SetFont(p->item[XM_EDIT2].hwnd, baseFont(16));

  if ( (sz = get_history("d2", caps, 512)) < 0 )
  {
    sprintf(caps, "D2");
    sz = 4;
  }
  SetText(p->item[XM_EDIT3].hwnd, caps, sz);
  SetFont(p->item[XM_EDIT3].hwnd, baseFont(16));

  if ( (sz = get_history("d3", caps, 512)) < 0 )
  {
    sprintf(caps, "D3");
    sz = 4;
  }
  SetText(p->item[XM_EDIT4].hwnd, caps, sz);
  SetFont(p->item[XM_EDIT4].hwnd, baseFont(16));

  if ( (sz = get_history("d4", caps, 512)) < 0 )
  {
    sprintf(caps, "D4");
    sz = 4;
  }
  SetText(p->item[XM_EDIT5].hwnd, caps, sz);
  SetFont(p->item[XM_EDIT5].hwnd, baseFont(16));

  if ( (sz = get_history("d5", caps, 512)) < 0 )
  {
    sprintf(caps, "D5");
    sz = 4;
  }
  SetText(p->item[XM_EDIT6].hwnd, caps, sz);
  SetFont(p->item[XM_EDIT6].hwnd, baseFont(16));


  for ( xm_id=XM_STATIC_1, idc_id = IDC_STATIC_1; idc_id<=IDC_STATIC_100; idc_id++, xm_id++ )
  {
    wnd.item[xm_id].color[0] = COLOR_READY;
    SetBkColorMessage(wnd.item[xm_id].hwnd, WM_CTLCOLORSTATIC, &wnd.item[xm_id], COLOR_READY);
    //p->item[xm_id].wproc = SetWindowLong(p->item[xm_id].hwnd, GWL_WNDPROC, (LONG)fxStaticProc);
  }


}

void* fxWM_CTLCOLORBTN(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int32_t id = getWindowXMID((HWND)lparam);

  if ( !((id>=XM_BUTTON1) && (id<=XM_BUTTON5)) )
  {
    return 0;
  }
  //SetText((HWND)lparam, wnd.item[id].cap, strlen(wnd.item[id].cap));
  

  return SetBackgroundColor(&wnd.item[id], wnd.item[id].color[0]);
}



void* fxWM_CTLCOLORSTATIC(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  //XSubWnd* p = (XSubWnd*)wparam;
  //return SetBackgroundColor(p, p->color[0]);

  int32_t id = getWindowXMID((HWND)lparam);
  SetText((HWND)lparam, wnd.item[id].cap, strlen(wnd.item[id].cap));

  return SetBackgroundColor(&wnd.item[id], wnd.item[id].color[0]);
  //if ( (HWND)lparam == wnd.item[XM_STATIC1].hwnd )
  //{
  //  return SetBackgroundColor(&wnd.item[XM_STATIC1], wnd.item[XM_STATIC1].color[0]);
  //}
  //else if ( (HWND)lparam == wnd.item[XM_STATIC2].hwnd )
  //{
  //  return SetBackgroundColor(&wnd.item[XM_STATIC2], wnd.item[XM_STATIC2].color[0]);
  //}
  //else if ( (HWND)lparam == wnd.item[XM_STATIC3].hwnd )
  //{
  //  return SetBackgroundColor(&wnd.item[XM_STATIC3], wnd.item[XM_STATIC3].color[0]);
  //}
  return 0;
}

void* fxWM_CREATE(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  return 0 ;
}

void* fxWM_DESTROY(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  codeXend(&wnd.codeX);
  return 0;
}

void* fxWM_INITDIALOG(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int32_t _index = 0;
  int8_t _top_title[256];


  wnd.tmrid = -1;
  init_window(hwnd, &wnd);


  sprintf(_top_title, TEXT("%s : (%d) "), TOP_TITLE, (int32_t)GetCurrentThreadId());
  SetWindowText(hwnd, _top_title);

  init_tray(wnd.hinst[0], hwnd);

  //loadInterface(wnd.h);
  //codeXmain(wnd.h, &wnd.codeX);
 

  return (void*)TRUE;
}


void CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime)
{
  if ( wnd.rflag == 1 )
  {
    wnd.rflag = 0;
  }
  else
  {
    fxDrawBit(0, 0);
  }
  wnd.protocol[0] = 0x02;
  wnd.protocol[1] = 0x30 + nIDEvent - 1;
  wnd.protocol[2] = 'R';
  wnd.protocol[3] = 0x0D;
  wnd.codeX.setMessage(wnd.codeX.h, (void*)MAKELONG(WRITE, XSERIAL), (void*)wnd.protocol, (void*)4);
  LVLog( wnd.item[XM_LIST1].hwnd, 0, MAX_LINE, &wnd.log, "log", "Serial", " [TMR] Block %d Request \r\n", nIDEvent);
}


void SaveCaption()
{
  int32_t e = 0;
  int8_t caption[512] = {0};

  e = GetText(wnd.item[XM_EDIT2].hwnd, caption, 512);
  set_history("D1", caption, e);

  e = GetText(wnd.item[XM_EDIT3].hwnd, caption, 512);
  set_history("D2", caption, e);

  e = GetText(wnd.item[XM_EDIT4].hwnd, caption, 512);
  set_history("D3", caption, e);

  e = GetText(wnd.item[XM_EDIT5].hwnd, caption, 512);
  set_history("D4", caption, e);

  e = GetText(wnd.item[XM_EDIT6].hwnd, caption, 512);
  set_history("D5", caption, e);
}

void* fxIDC_BUTTON1(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int8_t caption[512] = {0};
  SaveCaption();

  GetText(wnd.item[XM_BUTTON6].hwnd, caption, 512);
  if ( caption[0] == 'O' ) return 0;



  wnd.protocol[0] = 0x02;
  wnd.protocol[1] = 0x30;
  wnd.protocol[2] = 'R';
  wnd.protocol[3] = 0x0D;

  fxDrawBit(0, 0);

  wnd.codeX.setMessage(wnd.codeX.h, (void*)MAKELONG(WRITE, XSERIAL), (void*)wnd.protocol, (void*)4);

  if ( wnd.tmrid > 0 )  KillTimer(hwnd, wnd.tmrid);
  SetTimer(hwnd, 1, TIMER_TM, TimerProc);
  wnd.tmrid = 1;

  LVLog( wnd.item[XM_LIST1].hwnd, 0, MAX_LINE, &wnd.log, "log", "Serial", " [BTN] Block %d Request \r\n", wnd.tmrid);

  SetBkColorMessage(wnd.item[XM_BUTTON1].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON1], RGB(0, 0xFF, 0) );
  SetBkColorMessage(wnd.item[XM_BUTTON2].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON2], RGB(0, 0, 0xAA) );
  SetBkColorMessage(wnd.item[XM_BUTTON3].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON3], RGB(0, 0, 0xAA) );
  SetBkColorMessage(wnd.item[XM_BUTTON4].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON4], RGB(0, 0, 0xAA) );
  SetBkColorMessage(wnd.item[XM_BUTTON5].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON5], RGB(0, 0, 0xAA) );


  return (void*)TRUE;
}
void* fxIDC_BUTTON2(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int8_t caption[512] = {0};
  SaveCaption();

  GetText(wnd.item[XM_BUTTON6].hwnd, caption, 512);
  if ( caption[0] == 'O' ) return 0;

  wnd.protocol[0] = 0x02;
  wnd.protocol[1] = 0x31;
  wnd.protocol[2] = 'R';
  wnd.protocol[3] = 0x0D;

  fxDrawBit(0, 0);
  wnd.codeX.setMessage(wnd.codeX.h, (void*)MAKELONG(WRITE, XSERIAL), (void*)wnd.protocol, (void*)4);

  if ( wnd.tmrid > 0 )  KillTimer(hwnd, wnd.tmrid);
  SetTimer(hwnd, 2, TIMER_TM, TimerProc);
  wnd.tmrid = 2;

  LVLog( wnd.item[XM_LIST1].hwnd, 0, MAX_LINE, &wnd.log, "log", "Serial", " [BTN] Block %d Request \r\n", wnd.tmrid);

  SetBkColorMessage(wnd.item[XM_BUTTON1].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON1], RGB(0, 0, 0xAA) );
  SetBkColorMessage(wnd.item[XM_BUTTON2].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON2], RGB(0, 0xFF, 0) );
  SetBkColorMessage(wnd.item[XM_BUTTON3].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON3], RGB(0, 0, 0xAA) );
  SetBkColorMessage(wnd.item[XM_BUTTON4].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON4], RGB(0, 0, 0xAA) );
  SetBkColorMessage(wnd.item[XM_BUTTON5].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON5], RGB(0, 0, 0xAA) );

  return (void*)TRUE;
}
void* fxIDC_BUTTON3(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int8_t caption[512] = {0};
  SaveCaption();

  GetText(wnd.item[XM_BUTTON6].hwnd, caption, 512);
  if ( caption[0] == 'O' ) return 0;

  wnd.protocol[0] = 0x02;
  wnd.protocol[1] = 0x32;
  wnd.protocol[2] = 'R';
  wnd.protocol[3] = 0x0D;

  fxDrawBit(0, 0);
  wnd.codeX.setMessage(wnd.codeX.h, (void*)MAKELONG(WRITE, XSERIAL), (void*)wnd.protocol, (void*)4);

  if ( wnd.tmrid > 0 )  KillTimer(hwnd, wnd.tmrid);
  SetTimer(hwnd, 3, TIMER_TM, TimerProc);
  wnd.tmrid = 3;

  LVLog( wnd.item[XM_LIST1].hwnd, 0, MAX_LINE, &wnd.log, "log", "Serial", " [BTN] Block %d Request \r\n", wnd.tmrid);

  SetBkColorMessage(wnd.item[XM_BUTTON1].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON1], RGB(0, 0, 0xAA) );
  SetBkColorMessage(wnd.item[XM_BUTTON2].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON2], RGB(0, 0, 0xAA) );
  SetBkColorMessage(wnd.item[XM_BUTTON3].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON3], RGB(0, 0xFF, 0) );
  SetBkColorMessage(wnd.item[XM_BUTTON4].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON4], RGB(0, 0, 0xAA) );
  SetBkColorMessage(wnd.item[XM_BUTTON5].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON5], RGB(0, 0, 0xAA) );

  return (void*)TRUE;
}
void* fxIDC_BUTTON4(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int8_t caption[512] = {0};
  SaveCaption();

  GetText(wnd.item[XM_BUTTON6].hwnd, caption, 512);
  if ( caption[0] == 'O' ) return 0;

  wnd.protocol[0] = 0x02;
  wnd.protocol[1] = 0x33;
  wnd.protocol[2] = 'R';
  wnd.protocol[3] = 0x0D;

  fxDrawBit(0, 0);
  wnd.codeX.setMessage(wnd.codeX.h, (void*)MAKELONG(WRITE, XSERIAL), (void*)wnd.protocol, (void*)4);

  if ( wnd.tmrid > 0 )  KillTimer(hwnd, wnd.tmrid);
  SetTimer(hwnd, 4, TIMER_TM, TimerProc);
  wnd.tmrid = 4;

  LVLog( wnd.item[XM_LIST1].hwnd, 0, MAX_LINE, &wnd.log, "log", "Serial", " [BTN] Block %d Request \r\n", wnd.tmrid);

  SetBkColorMessage(wnd.item[XM_BUTTON1].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON1], RGB(0, 0, 0xAA) );
  SetBkColorMessage(wnd.item[XM_BUTTON2].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON2], RGB(0, 0, 0xAA) );
  SetBkColorMessage(wnd.item[XM_BUTTON3].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON3], RGB(0, 0, 0xAA) );
  SetBkColorMessage(wnd.item[XM_BUTTON4].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON4], RGB(0, 0xFF, 0) );
  SetBkColorMessage(wnd.item[XM_BUTTON5].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON5], RGB(0, 0, 0xAA) );

  return (void*)TRUE;
}
void* fxIDC_BUTTON5(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int8_t caption[512] = {0};
  SaveCaption();

  GetText(wnd.item[XM_BUTTON6].hwnd, caption, 512);
  if ( caption[0] == 'O' ) return 0;

 
  wnd.protocol[0] = 0x02;
  wnd.protocol[1] = 0x34;
  wnd.protocol[2] = 'R';
  wnd.protocol[3] = 0x0D;

  fxDrawBit(0, 0);
  wnd.codeX.setMessage(wnd.codeX.h, (void*)MAKELONG(WRITE, XSERIAL), (void*)wnd.protocol, (void*)4);

  if ( wnd.tmrid > 0 )  KillTimer(hwnd, wnd.tmrid);
  SetTimer(hwnd, 5, TIMER_TM, TimerProc);
  wnd.tmrid = 5;

  LVLog( wnd.item[XM_LIST1].hwnd, 0, MAX_LINE, &wnd.log, "log", "Serial", " [BTN] Block %d Request \r\n", wnd.tmrid);

  SetBkColorMessage(wnd.item[XM_BUTTON1].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON1], RGB(0, 0, 0xAA) );
  SetBkColorMessage(wnd.item[XM_BUTTON2].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON2], RGB(0, 0, 0xAA) );
  SetBkColorMessage(wnd.item[XM_BUTTON3].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON3], RGB(0, 0, 0xAA) );
  SetBkColorMessage(wnd.item[XM_BUTTON4].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON4], RGB(0, 0, 0xAA) );
  SetBkColorMessage(wnd.item[XM_BUTTON5].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON5], RGB(0, 0xFF, 0) );

  return (void*)TRUE;
}
void* fxIDC_BUTTON6(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int8_t caption[32] = {0};
  int8_t port[32] = {0};
  int32_t e = 0;
  int32_t fd = 0;

  SaveCaption();

  GetText(wnd.item[XM_BUTTON6].hwnd, caption, 32);

  if ( caption[0] == 'O' )
  {
    e = GetText(wnd.item[XM_EDIT1].hwnd, port, 32);
    set_history("port", port, e);
    wnd.codeX.setMessage(wnd.codeX.h, (void*)MAKELONG(XM_PORT, XSERIAL), (void*)port, (void*)e);
    wnd.codeX.setMessage(wnd.codeX.h, (void*)MAKELONG(ENABLE, XSERIAL), 0, 0);
    wnd.codeX.getMessage(wnd.codeX.h, (void*)MAKELONG(FDSCRPTR, XSERIAL), &fd, 4);
    if ( fd > 0 )
    {
      SetText(wnd.item[XM_BUTTON6].hwnd, (void*)"CLOSE", (void*)5);
      LVLog( wnd.item[XM_LIST1].hwnd, 0, MAX_LINE, &wnd.log, "log", "Serial", "SERIAL PORT OPEN SUCCESS (%s)\r\n", port);
    }
    else
    {
      LVLog( wnd.item[XM_LIST1].hwnd, 0, MAX_LINE, &wnd.log, "log", "Serial", "SERIAL PORT OPEN FAIL (%s)\r\n", port);
    }
  }
  else
  {
    if ( wnd.tmrid > 0 )  KillTimer(hwnd, wnd.tmrid);
    fxDrawBit(0, 0);

    SetBkColorMessage(wnd.item[XM_BUTTON1].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON1], RGB(0, 0, 0xAA) );
    SetBkColorMessage(wnd.item[XM_BUTTON2].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON2], RGB(0, 0, 0xAA) );
    SetBkColorMessage(wnd.item[XM_BUTTON3].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON3], RGB(0, 0, 0xAA) );
    SetBkColorMessage(wnd.item[XM_BUTTON4].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON4], RGB(0, 0, 0xAA) );
    SetBkColorMessage(wnd.item[XM_BUTTON5].hwnd, WM_CTLCOLORBTN, &wnd.item[XM_BUTTON5], RGB(0, 0, 0xAA) );

    e = GetText(wnd.item[XM_EDIT1].hwnd, port, 32);
    SetText(wnd.item[XM_BUTTON6].hwnd, (void*)"OPEN", (void*)4);
    wnd.codeX.setMessage(wnd.codeX.h, (void*)MAKELONG(DISABLE, XSERIAL), 0, 0);
    LVLog( wnd.item[XM_LIST1].hwnd, 0, MAX_LINE, &wnd.log, "log", "Serial", "SERIAL PORT CLOSED (%s)\r\n", port);
  }
  return (void*)TRUE;
}


void* fxWM_COMMAND(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  switch(LOWORD(wparam))
  {
    case IDC_BUTTON1:
      fxIDC_BUTTON1(hwnd, msg, wparam, lparam);
      break;
    case IDC_BUTTON2:
      fxIDC_BUTTON2(hwnd, msg, wparam, lparam);
      break;
    case IDC_BUTTON3:
      fxIDC_BUTTON3(hwnd, msg, wparam, lparam);
      break;
    case IDC_BUTTON4:
      fxIDC_BUTTON4(hwnd, msg, wparam, lparam);
      break;
    case IDC_BUTTON5:
      fxIDC_BUTTON5(hwnd, msg, wparam, lparam);
      break;

    case IDC_BUTTON6:
      fxIDC_BUTTON6(hwnd, msg, wparam, lparam);
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
  int32_t id = 0;
  LPDRAWITEMSTRUCT lpdis =(LPDRAWITEMSTRUCT)lparam;
  switch ( lpdis->CtlID )
  {
    case IDC_BUTTON1: id=XM_BUTTON1;
      break;
    case IDC_BUTTON2: id=XM_BUTTON2;
      break;
    case IDC_BUTTON3: id=XM_BUTTON3;
      break;
    case IDC_BUTTON4: id=XM_BUTTON4;
      break;
    case IDC_BUTTON5: id=XM_BUTTON5;
      break;
  }

  if ( (id>=XM_BUTTON1) && (id<=XM_BUTTON5) )
  {
    DrawText(lpdis->hDC, wnd.item[id].cap, -1, &wnd.item[id].rct, DT_CENTER|DT_VCENTER);
  }

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
      SetTextColor((HDC)wparam, RGB(255,255,255));
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

  memset(&wnd.codeX, 0, sizeof(CodeX));

  //wnd.codeX.callback = fxCallback;
  //wnd.codeX.obj = &wnd;
}


int32_t WINAPI WinMain(HINSTANCE hinst, HINSTANCE hpinst, LPSTR cmd, int32_t nshow)
{
  setup(hinst, hpinst, cmd, nshow);

  DialogBox(hinst, (LPCSTR)IDD_DIALOG1, HWND_DESKTOP, (DLGPROC)dlgproc);
  return TRUE;
}
