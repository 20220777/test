#include <xm.h>
#include <locale.h>
#define COUNT_MOD        0x7F

XWND wnd;

#define TAB_LEFT_MARGIN    12
#define TAB_TOP_MARGIN     8   


#define TOP_TITLE   "lite.link Console, 신승혁 & 유원석"


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
//void* SetBackgroundColor(_WND* p, COLORREF color)
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
//void* SetBackgroundColor(_WND* p, COLORREF color)
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



void* SetBackgroundColor(_WND* p, COLORREF color)
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

//void* SetBackgroundColor(_WND* p, COLORREF color)
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
//void* SetBackgroundColor(_WND* p, COLORREF color)
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


//void* SetBackgroundColor(_WND* p, COLORREF color)
//{
//  p->hdc = BeginPaint(p->hwnd, &p->ps);
//  Ellipse(p->hdc, 0, 0, 50, 50);
//  EndPaint(p->hwnd, &p->ps);
//  return (void*)0;
//}


void* SetBkColorMessage(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  _WND* p = (_WND*)wparam;
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
/*                                Serial Control                               */
/*                                                                             */
/*                                                                             */
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/


#define __NSERIAL_PORT__               "COM9"
#define __NSERIAL_BAUDRATE__           "115200"

//
//
//void __setLog(uint8_t* mbs, int32_t sz)
//{
//  int32_t e = 0;
//  wchar_t wcs[1024] = {0};
//
//  e = mbstowcs(wcs, mbs, sz);
//
//  //SetText(wnd.item[_IDC_EDIT1].hwnd, wcs, e);
//}
//
//
//uint8_t __bcc(uint8_t* p, int32_t sz)
//{
//  uint8_t r = 0;
//  int32_t i = 0;
//
//  for (i=0 ; i<sz ; i++ )
//  {
//    r ^= *(p+i);
//  }
//  return r;
//}
//
//uint8_t jmtBCC(uint8_t* p, int32_t sz)
//{
//  uint8_t r = 0;
//
//  r = __bcc(p, sz) & 0x0F;
//
//  return (r>=0&&r<=9)?r|0x30:0x41+r-0x0a;
//}
//
//
//int32_t checkAck(int8_t* b, int32_t sz)
//{
//  int32_t e = 0;
//  uint8_t r = 0;
//  uint32_t wid = 0;
//  wchar_t wcs[1024] = {0};
//  uint8_t mbs[512] = {0};
//
//
//  #if 0
//  if ( *b == 0x06 )
//  {
//    if ( *(b+7) == 'U' )
//    {
//      r = jmtBCC(b, sz-2);
//      if ( r == *(b+8) )
//      {
//        //SetBkColorMessage(wnd.item[_IDC_BUTTON_U].hwnd, WM_CTLCOLORBTN, &wnd.item[_IDC_BUTTON_U], RGB(0, 0xAA, 0) );
//      }
//      else
//      {
//        //SetBkColorMessage(wnd.item[_IDC_BUTTON_U].hwnd, WM_CTLCOLORBTN, &wnd.item[_IDC_BUTTON_U], COLOR_FAIL );
//      }
//    }
//    else if ( *(b+7) == 'D' )
//    {
//      r = jmtBCC(b, sz-2);
//      if ( r == *(b+8) )
//      {
//        //SetBkColorMessage(wnd.item[_IDC_BUTTON_S].hwnd, WM_CTLCOLORBTN, &wnd.item[_IDC_BUTTON_S], RGB(0xAA, 0, 0) );
//      }
//      else
//      {
//        //SetBkColorMessage(wnd.item[_IDC_BUTTON_S].hwnd, WM_CTLCOLORBTN, &wnd.item[_IDC_BUTTON_S], COLOR_FAIL );
//      }
//    }
//    else if ( *(b+7) == 'S' )
//    {
//      r = jmtBCC(b, sz-2);
//      if ( r == *(b+8) )
//      {
//        //SetBkColorMessage(wnd.item[_IDC_BUTTON_D].hwnd, WM_CTLCOLORBTN, &wnd.item[_IDC_BUTTON_D], RGB(0xAA, 0, 0xAA) );
//      }
//      else
//      {
//        //SetBkColorMessage(wnd.item[_IDC_BUTTON_D].hwnd, WM_CTLCOLORBTN, &wnd.item[_IDC_BUTTON_D], COLOR_FAIL);
//      }
//    }
//    else if ( *(b+7) == 'E' || *(b+7) == 'X')
//    {
//      r = jmtBCC(b, sz-2);
//
//      for ( wid = _IDC_BUTTON1 ; wid<=_IDC_BUTTON20 ; wid ++ )
//      {
//        if ( *(b+1)==wnd._nconfig.vid[wid][0] && *(b+2)==wnd._nconfig.vid[wid][1] )
//        {
//          break;
//        }
//      }
//      if ( wid >= _IDC_BUTTON1 && wid <= _IDC_BUTTON20 )
//      {
//        KillTimer(wnd.hdlg, wid);
//
//        if ( r == *(b+8) )
//        {
//          sprintf(mbs, "%s SUCCESS", wnd.item[wid].cap);
//          __setLog(mbs, strlen(mbs));
//          //SetBkColorMessage(wnd.item[wid].hwnd, WM_CTLCOLORBTN, &wnd.item[wid], RGB(0, 0, 0xAA) );
//          // OK
//        }
//        else
//        {
//          sprintf(mbs, "%s FAIL", wnd.item[wid].cap);
//          __setLog(mbs, strlen(mbs));
//          //SetBkColorMessage(wnd.item[wid].hwnd, WM_CTLCOLORBTN, &wnd.item[wid], COLOR_FAIL );
//          // FAIL
//        }
//      }
//    }
//  }
//  #endif
//  return e;
//}
//
//
//
//int32_t nserial_connected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
//{
//  cnserial* p = (cnserial*)o;
//  return 0;
//}
//
//int32_t nserial_disconnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
//{
//  cnserial* p = (cnserial*)o;
//  return 0;
//}
//
//
//
//
//int32_t nserial_read(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
//{
//  cnserial* p = (cnserial*)o;
//
//  wnd._nserial.rbuf[wnd._nserial.rdx] = *b;
//
//  wnd._nserial.rdx++;
//
//  if ( *b == 0x0d )
//  {
//    checkAck(wnd._nserial.rbuf, wnd._nserial.rdx);
//    wnd._nserial.rdx = 0;
//  }
//  return 0;
//}
//
//int32_t nserial_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
//{
//  cnserial* p = (cnserial*)o;
//  int32_t e = 0;
//
//  e=__serial_write(p->_imtif.h, fd, b, sz, 0, o);
//
//  return e;
//}
//
//int32_t nserial_open(cnserial* p)
//{
//  int32_t e = 0;
//  int32_t sz = 1;
//  int8_t _json[1024] = {0};
//  int8_t _argv[16][256] = {0};
//
//  p->_imtif.callback[IMTIF_CALLBACK_CONNECTED] = nserial_connected;
//  p->_imtif.callback[IMTIF_CALLBACK_DISCONNECTED] = nserial_disconnected;
//  p->_imtif.callback[IMTIF_CALLBACK_READ] = nserial_read;
//
//  sprintf(_json, 
//          "{"
//            "\"PORT\":\"%s\","
//            "\"BAUDRATE\":\"%s\","
//            "\"DATABIT\":\"8\","
//            "\"STOPBIT\":\"1\","
//            "\"PARITYBIT\":\"0\","
//            "\"BUF_SZ\":\"1\","
//            "\"SYNC\":\"DISABLE\""
//          "}",
//          wnd._nconfig.str[0],
//          wnd._nconfig.str[1]
//  );
//
//  sz = 1;
//
//  p->buf = (uint8_t*)calloc(sz, sizeof(uint8_t));
//  e = __serial_open(&p->_imtif.h, _json, p->buf, sz, p->_imtif.callback, p);
//
//  return e;
//}
//
//
//int32_t nserial_close(cnserial* p)
//{
//  int32_t e = 0;
//  __serial_close(&p->_imtif.h);
//  free(p->buf);
//  p->buf = 0;
//
//  return 0;
//}
//



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

  //if ( wnd.codeX.modul[XWEBSOCKET].fdset == 0 ) return ;

  //for(idx=0 ; idx<FD_SETSIZE ; idx++ )
  //{
  //  if ( (wnd.codeX.modul[XWEBSOCKET].fdset+idx)->a[0] > 0 )
  //  {
  //    #if LVLOG_LEVEL_0
  //    if ( SendMessage(wnd.item[XM_CHECK2].hwnd, BM_GETCHECK, 0, 0) == BST_CHECKED )
  //    {
  //      raw_buffer(b, sz, raw);
  //      LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "WebSocket", "WebSocket Write [%d] %s \r\n", (wnd.codeX.modul[XWEBSOCKET].fdset+idx)->a[0], raw);
  //    }
  //    #endif

  //    wnd.codeX.setMessage(wnd.codeX.h, (void*)MAKELONG(FDSCRPTR, XWEBSOCKET), (void*)(wnd.codeX.modul[XWEBSOCKET].fdset+idx)->a[0], 0);
  //    wnd.codeX.setMessage(wnd.codeX.h, (void*)MAKELONG(WRITE, XWEBSOCKET), (void*)b, (void*)sz);
  //  }

  //  ////LVLog(gp->item[LIST_WSGW_WS_LOG], gp->item[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "WebSocket", "Client[%d], %d, %08X \r\n", idx, gp->pm->mws.pack.info[idx].fd,gp->pm->mws.pack.info[idx].REG.SR);

  //  ////if ( (gp->pm->mws.pack.info[idx].fd > 0) && (gp->pm->mws.pack.info[idx].REG.SR&0x00000001) )
  //  //if ((gp->pm->mws.pack.info[idx].fd > 0) )//&& (gp->pm->mws.pack.info[idx].REG.SR & 0x00000001))
  //  //{
  //  //  //e = mtifWebSocketWrite(&gp->pm->mws.m, gp->pm->mws.pack.info[idx].fd, b, sz);
  //  //  e = mtifWebSocketWriteEx(&gp->pm->mws.m, gp->pm->mws.pack.info[idx].fd, b, sz, 0x02, 0, 0);
  //  //  if ( e > 0 )
  //  //  {
  //  //    #if LVLOG
  //  //    LVLog(gp->item[LIST_WSGW_WS_LOG], gp->item[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "WebSocket", "Client[%d], %d = Write(%d, \"%s\", %d) \r\n", idx, e, gp->pm->mws.pack.info[idx].fd, vbuf, sz);
  //  //    #endif
  //  //    //LVLog(gp->item[LIST_WSGW_WS_LOG], gp->item[CHECK_WSGW_LOG], &gp->log, "log", "WebSocket", "%d = Write(%d, \"%s\", %d)", e, gp->pm->mws.pack.info[idx].fd, b, sz);
  //  //  }
  //  //}
  //  //mcsleep(10);
  //}

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


  ////GetComboText(gp->item[COMBO_DISPLAY_TYPE_WSGW], st);

  //fprint_raw_buffer(0, (char*)lparam, (int)wparam, vbuf);
  //LVLog(gp->item[LIST_WSGW_WS_LOG], gp->item[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "WebSocket", "%s", vbuf);
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
  //wnd.protocol[2] = 'S';
  //wnd.codeX.setMessage(wnd.codeX.h, (void*)MAKELONG(WRITE, XSERIAL), (void*)wnd.protocol, (void*)4);
  //LVLog( wnd.item[XM_LIST1].hwnd, 0, MAX_LINE, &wnd.log, "log", "Serial", " [RES] Block %c Request \r\n", wnd.protocol[1]+1);
}


void* fxDrawBit(uint8_t* v, int32_t sz)
{
  int32_t i=0;
  int32_t idx = 0;
  if ( sz < 0 ) return 0;

  //if (  wnd.protocol[2] == 'R' )
  //{
  //  if ( v == 0 )
  //  {
  //    LVLog( wnd.item[XM_LIST1].hwnd, 0, MAX_LINE, &wnd.log, "log", "Serial", "No Response\r\n");
  //    for ( i=XM_STATIC_1, idx=0 ; i<=XM_STATIC_100 ; i+=4, idx++ )
  //    {
  //      wnd.item[i  ].SR = 0;
  //      wnd.item[i+1].SR = 0;
  //      wnd.item[i+2].SR = 0;
  //      wnd.item[i+3].SR = 0;
  //      SetBkColorMessage(wnd.item[i  ].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i  ], COLOR_READY);
  //      SetBkColorMessage(wnd.item[i+1].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+1], COLOR_READY);
  //      SetBkColorMessage(wnd.item[i+2].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+2], COLOR_READY);
  //      SetBkColorMessage(wnd.item[i+3].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+3], COLOR_READY);
  //    }
  //    return 0;
  //  }

  //  for ( i=XM_STATIC_1, idx=0 ; i<=XM_STATIC_100 ; i+=4, idx++ )
  //  {
  //    wnd.item[i  ].SR = (*(v+idx)&0x01)?1:0;
  //    wnd.item[i+1].SR = (*(v+idx)&0x02)?1:0;
  //    wnd.item[i+2].SR = (*(v+idx)&0x04)?1:0;
  //    wnd.item[i+3].SR = (*(v+idx)&0x08)?1:0;
  //    //SetBkColorMessage(wnd.item[i  ].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i  ], (*(v+idx)&0x01)?COLOR_WHITE:COLOR_READY);
  //    //SetBkColorMessage(wnd.item[i+1].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+1], (*(v+idx)&0x02)?COLOR_WHITE:COLOR_READY);
  //    //SetBkColorMessage(wnd.item[i+2].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+2], (*(v+idx)&0x04)?COLOR_WHITE:COLOR_READY);
  //    //SetBkColorMessage(wnd.item[i+3].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+3], (*(v+idx)&0x08)?COLOR_WHITE:COLOR_READY);
  //    //if ( wnd.item[i  ].SR == 1 ) SetBkColorMessage(wnd.item[i  ].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i  ], COLOR_READY);
  //    //if ( wnd.item[i+1].SR == 1 ) SetBkColorMessage(wnd.item[i+1].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+1], COLOR_READY);
  //    //if ( wnd.item[i+2].SR == 1 ) SetBkColorMessage(wnd.item[i+2].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+2], COLOR_READY);
  //    //if ( wnd.item[i+3].SR == 1 ) SetBkColorMessage(wnd.item[i+3].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+3], COLOR_READY);
  //  }
  //  fxResearch();
  //}
  //else
  //{
  //  //if ( v == 0 )
  //  //{
  //  //  LVLog( wnd.item[XM_LIST1].hwnd, 0, MAX_LINE, &wnd.log, "log", "Serial", "No Response\r\n");
  //  //  for ( i=XM_STATIC_1, idx=0 ; i<=XM_STATIC_100 ; i+=4, idx++ )
  //  //  {
  //  //    if ( wnd.item[i  ].SR == 1 ) SetBkColorMessage(wnd.item[i  ].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i  ], COLOR_READY);
  //  //    if ( wnd.item[i+1].SR == 1 ) SetBkColorMessage(wnd.item[i+1].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+1], COLOR_READY);
  //  //    if ( wnd.item[i+2].SR == 1 ) SetBkColorMessage(wnd.item[i+2].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+2], COLOR_READY);
  //  //    if ( wnd.item[i+3].SR == 1 ) SetBkColorMessage(wnd.item[i+3].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+3], COLOR_READY);
  //  //  }
  //  //  return 0;
  //  //}

  //  for ( i=XM_STATIC_1, idx=0 ; i<=XM_STATIC_100 ; i+=4, idx++ )
  //  {
  //    if ( wnd.item[i  ].SR == 1 ) SetBkColorMessage(wnd.item[i  ].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i  ], (*(v+idx)&0x01)?COLOR_ON:COLOR_CRITICAL);
  //    else                         SetBkColorMessage(wnd.item[i  ].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i  ], COLOR_READY);
  //    if ( wnd.item[i+1].SR == 1 ) SetBkColorMessage(wnd.item[i+1].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+1], (*(v+idx)&0x02)?COLOR_ON:COLOR_CRITICAL);
  //    else                         SetBkColorMessage(wnd.item[i  ].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+1], COLOR_READY);
  //    if ( wnd.item[i+2].SR == 1 ) SetBkColorMessage(wnd.item[i+2].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+2], (*(v+idx)&0x04)?COLOR_ON:COLOR_CRITICAL);
  //    else                         SetBkColorMessage(wnd.item[i  ].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+2], COLOR_READY);
  //    if ( wnd.item[i+3].SR == 1 ) SetBkColorMessage(wnd.item[i+3].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+3], (*(v+idx)&0x08)?COLOR_ON:COLOR_CRITICAL);
  //    else                         SetBkColorMessage(wnd.item[i  ].hwnd, WM_CTLCOLORSTATIC, &wnd.item[i+3], COLOR_READY);
  //  }
  //}
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
	//case READ:
 //   raw_buffer((int8_t*)wparam, (int32_t)lparam, raw);
 //   LVLog( wnd.item[XM_LIST1].hwnd, 0, MAX_LINE, &wnd.log, "log", "Serial", "SERIAL READ (%d) %s\r\n", (uint32_t)lparam, raw);
 //   sz = jmt_hex_strm((int8_t*)(wparam+2), ((int32_t)lparam)-3, v);
 //   wnd.rflag = 1;
 //   fxDrawBit(v, sz);
	//	break;
  }
  return 0;
}


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
 //   break;
	//case XWEBSOCKET:
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

int32_t getWindowWNDID(HWND hwnd)
{
  int32_t wnd_id = 0;
  //for ( ; wnd_id < _IDC_MAX_ITEM ; wnd_id++ )
  //{
  //  if ( hwnd == wnd.item[wnd_id].hwnd ) break;
  //}
  return wnd_id;
}



void* fxStaticProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int32_t id = getWindowWNDID((HWND)lparam);
  switch(msg)
  {
    case WM_CTLCOLORSTATIC:
      return (BOOL)SetBackgroundColor(&wnd.item[id], COLOR_READY);

      //return (BOOL)SetBackgroundColor(&wnd.item[WND_STATIC1], (COLORREF)lparam);
      break;

    case WM_PAINT:
      InvalidateRect(hwnd, 0, TRUE);
      break;
  }



  return 0;//CallWindowProc(wnd.item[id].wproc, hwnd, msg, wparam, lparam);
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
  //int32_t xm_id=XM_STATIC_1, idc_id = IDC_STATIC_1;
  int32_t _idc_id = 0;
  int32_t idc_id = 0;
  int32_t i = 0;
  int32_t e = 0;
  wchar_t wcs[1024] = {0};

  int8_t caps[512] = {0};
  int32_t sz = 0;
  p->hdlg = hwnd;


  //p->item[_IDC_STATIC_1].hwnd = GetDlgItem(hwnd, IDC_STATIC_1);
  //p->item[_IDC_STATIC_2].hwnd = GetDlgItem(hwnd, IDC_STATIC_2);
  //p->item[_IDC_STATIC_3].hwnd = GetDlgItem(hwnd, IDC_STATIC_3);
  //p->item[_IDC_STATIC_4].hwnd = GetDlgItem(hwnd, IDC_STATIC_4);


  #if 0

  p->item[_IDC_EDIT1].hwnd = GetDlgItem(hwnd, IDC_EDIT1);
  SetFont(p->item[_IDC_EDIT1].hwnd, baseFont(24));


  for ( _idc_id=_IDC_BUTTON1, i=0 ; _idc_id < _IDC_MAX_ITEM ; _idc_id++, i++ )
  {
    p->item[_idc_id].hwnd = GetDlgItem(hwnd, IDC_BUTTON1+i);
    p->item[_idc_id].font[1] = baseFont(24);
  }
  p->item[_IDC_STATIC_1].hwnd = GetDlgItem(hwnd, IDC_STATIC_1);
  p->item[_IDC_STATIC_2].hwnd = GetDlgItem(hwnd, IDC_STATIC_2);
  p->item[_IDC_STATIC_3].hwnd = GetDlgItem(hwnd, IDC_STATIC_3);
  p->item[_IDC_STATIC_4].hwnd = GetDlgItem(hwnd, IDC_STATIC_4);
  p->item[_IDC_STATIC_5].hwnd = GetDlgItem(hwnd, IDC_STATIC_5);
  p->item[_IDC_STATIC_6].hwnd = GetDlgItem(hwnd, IDC_STATIC_6);


  sprintf(p->item[_IDC_BUTTON1].cap, p->_nconfig.v[_IDC_BUTTON1]);
  sprintf(p->item[_IDC_BUTTON2].cap, p->_nconfig.v[_IDC_BUTTON2]);
  sprintf(p->item[_IDC_BUTTON3].cap, p->_nconfig.v[_IDC_BUTTON3]);
  sprintf(p->item[_IDC_BUTTON4].cap, p->_nconfig.v[_IDC_BUTTON4]);
  sprintf(p->item[_IDC_BUTTON5].cap, p->_nconfig.v[_IDC_BUTTON5]);
  sprintf(p->item[_IDC_BUTTON6].cap, p->_nconfig.v[_IDC_BUTTON6]);
  sprintf(p->item[_IDC_BUTTON7].cap, p->_nconfig.v[_IDC_BUTTON7]);
  sprintf(p->item[_IDC_BUTTON8].cap, p->_nconfig.v[_IDC_BUTTON8]);
  sprintf(p->item[_IDC_BUTTON9].cap, p->_nconfig.v[_IDC_BUTTON9]);
  sprintf(p->item[_IDC_BUTTON10].cap, p->_nconfig.v[_IDC_BUTTON10]);
  sprintf(p->item[_IDC_BUTTON11].cap, p->_nconfig.v[_IDC_BUTTON11]);
  sprintf(p->item[_IDC_BUTTON12].cap, p->_nconfig.v[_IDC_BUTTON12]);
  sprintf(p->item[_IDC_BUTTON13].cap, p->_nconfig.v[_IDC_BUTTON13]);
  sprintf(p->item[_IDC_BUTTON14].cap, p->_nconfig.v[_IDC_BUTTON14]);
  sprintf(p->item[_IDC_BUTTON15].cap, p->_nconfig.v[_IDC_BUTTON15]);
  sprintf(p->item[_IDC_BUTTON16].cap, p->_nconfig.v[_IDC_BUTTON16]);
  sprintf(p->item[_IDC_BUTTON17].cap, p->_nconfig.v[_IDC_BUTTON17]);
  sprintf(p->item[_IDC_BUTTON18].cap, p->_nconfig.v[_IDC_BUTTON18]);
  sprintf(p->item[_IDC_BUTTON19].cap, p->_nconfig.v[_IDC_BUTTON19]);
  sprintf(p->item[_IDC_BUTTON20].cap, p->_nconfig.v[_IDC_BUTTON20]);

  sprintf(p->item[_IDC_BUTTON_U].cap, p->_nconfig.v[_IDC_BUTTON_U]);
  sprintf(p->item[_IDC_BUTTON_S].cap, p->_nconfig.v[_IDC_BUTTON_S]);
  sprintf(p->item[_IDC_BUTTON_D].cap, p->_nconfig.v[_IDC_BUTTON_D]);
  sprintf(p->item[_IDC_BUTTON_X].cap, p->_nconfig.v[_IDC_BUTTON_X]);


  sprintf(p->item[_IDC_STATIC_1].cap, p->_nconfig.v[_IDC_STATIC_1]);
  sprintf(p->item[_IDC_STATIC_2].cap, p->_nconfig.v[_IDC_STATIC_2]);

  memset(wcs, 0, 1024);
  e =  mbstowcs(wcs, p->item[_IDC_STATIC_1].cap, strlen(p->item[_IDC_STATIC_1].cap)+1);
  SetText(p->item[_IDC_STATIC_1].hwnd, wcs, e);
  SetFont(p->item[_IDC_STATIC_1].hwnd, baseFont(36));

  memset(wcs, 0, 1024);
  e =  mbstowcs(wcs, p->item[_IDC_STATIC_2].cap, strlen(p->item[_IDC_STATIC_2].cap)+1);
  SetText(p->item[_IDC_STATIC_2].hwnd, wcs, e);
  SetFont(p->item[_IDC_STATIC_2].hwnd, baseFont(36));

  //memset(wcs, 0, 1024);
  //e =  mbstowcs(wcs, p->item[_IDC_BUTTON1].cap, strlen(p->item[_IDC_BUTTON1].cap+1));
  //SetText(p->item[_IDC_BUTTON1].hwnd, wcs, e);
  //SetFont(p->item[_IDC_BUTTON1].hwnd, p->item[_IDC_BUTTON1].font[1]);


  for ( _idc_id=_IDC_BUTTON1, i=0 ; _idc_id <= _IDC_BUTTON_X ; _idc_id++, i++ )
  {
    memset(wcs, 0, 1024);
    e =  mbstowcs(wcs, p->item[_idc_id].cap, strlen(p->item[_idc_id].cap));
    SetText(p->item[_idc_id].hwnd, wcs, e);
    SetFont(p->item[_idc_id].hwnd, p->item[_idc_id].font[1]);
  }


  for ( _idc_id=_IDC_BUTTON1, i=0 ; _idc_id <= _IDC_BUTTON20 ; _idc_id++, i++ )
  {
    SetBkColorMessage(p->item[_idc_id].hwnd, WM_CTLCOLORBTN, &p->item[_idc_id], RGB(0, 0, 0xAA));
  }

  SetBkColorMessage(p->item[_IDC_BUTTON_U].hwnd, WM_CTLCOLORBTN, &p->item[_IDC_BUTTON_U], RGB(0  , 0xAA, 0));
  SetBkColorMessage(p->item[_IDC_BUTTON_S].hwnd, WM_CTLCOLORBTN, &p->item[_IDC_BUTTON_S], RGB(0xAA,    0, 0));
  SetBkColorMessage(p->item[_IDC_BUTTON_D].hwnd, WM_CTLCOLORBTN, &p->item[_IDC_BUTTON_D], RGB(0xAA, 0xAA, 0));
  SetBkColorMessage(p->item[_IDC_BUTTON_X].hwnd, WM_CTLCOLORBTN, &p->item[_IDC_BUTTON_X], RGB(0xAA,    0, 0xAA));

  #endif

}

void* fxWM_CTLCOLORBTN(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int32_t id = getWindowWNDID((HWND)lparam);

  //if ( !((id>=_IDC_BUTTON1) && (id<=_IDC_BUTTON_X)) )
  //{
  //  return 0;
  //}
  ////SetText((HWND)lparam, wnd.item[id].cap, strlen(wnd.item[id].cap));
  return 0;//SetBackgroundColor(&wnd.item[id], wnd.item[id].color[0]);
}



void* fxWM_CTLCOLORSTATIC(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int32_t id = getWindowWNDID((HWND)lparam);
  //if ( (id>=_IDC_STATIC_1) && (id<=_IDC_STATIC_2) )
  //{
  //  return 0;
  //}

  return 0;//SetBackgroundColor(&wnd.item[id], wnd.item[id].color[0]);
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
//
//void load_config()
//{
//  int32_t e = 0;
//  uint8_t value[128] = {0};
//  uint8_t path[1024] = {0};
//  FILE* fp = 0;
//  __get_prefix(path);
//  sprintf(path, "%s\\config.ini", path);
//
//  fp = fopen(path, "rb");
//  if ( fp == 0 )
//  {
//    fp = fopen(path, "wb");
//    fwprintf(fp, L"%s", config_ini);  
//    //e = fwrite(config_ini, sizeof(wchar_t), sizeof(config_ini)+1, fp);
//  }
//  fclose(fp);
//
//
//  e = __get_ini_value(path, "serial", "port", wnd._nconfig.str[0]);
//  e = __get_ini_value(path, "serial", "baudrate", wnd._nconfig.str[1]);
//
//  e = __get_ini_value(path, "title", "t1", wnd._nconfig.v[_IDC_STATIC_1]);
//  e = __get_ini_value(path, "title", "t2", wnd._nconfig.v[_IDC_STATIC_2]);
//
//
//  e = __get_ini_value(path, "part1", "b1", wnd._nconfig.v[_IDC_BUTTON1]);
//  e = __get_ini_value(path, "part1", "b2", wnd._nconfig.v[_IDC_BUTTON2]);
//  e = __get_ini_value(path, "part1", "b3", wnd._nconfig.v[_IDC_BUTTON3]);
//  e = __get_ini_value(path, "part1", "b4", wnd._nconfig.v[_IDC_BUTTON4]);
//  e = __get_ini_value(path, "part1", "b5", wnd._nconfig.v[_IDC_BUTTON5]);
//  e = __get_ini_value(path, "part1", "b6", wnd._nconfig.v[_IDC_BUTTON6]);
//  e = __get_ini_value(path, "part1", "b7", wnd._nconfig.v[_IDC_BUTTON7]);
//  e = __get_ini_value(path, "part1", "b8", wnd._nconfig.v[_IDC_BUTTON8]);
//  e = __get_ini_value(path, "part1", "b9", wnd._nconfig.v[_IDC_BUTTON9]);
//  e = __get_ini_value(path, "part1", "b10", wnd._nconfig.v[_IDC_BUTTON10]);
//  e = __get_ini_value(path, "part1", "b11", wnd._nconfig.v[_IDC_BUTTON11]);
//  e = __get_ini_value(path, "part1", "b12", wnd._nconfig.v[_IDC_BUTTON12]);
//
//  e = __get_ini_value(path, "part1", "b1_id", wnd._nconfig.vid[_IDC_BUTTON1]);
//  e = __get_ini_value(path, "part1", "b2_id", wnd._nconfig.vid[_IDC_BUTTON2]);
//  e = __get_ini_value(path, "part1", "b3_id", wnd._nconfig.vid[_IDC_BUTTON3]);
//  e = __get_ini_value(path, "part1", "b4_id", wnd._nconfig.vid[_IDC_BUTTON4]);
//  e = __get_ini_value(path, "part1", "b5_id", wnd._nconfig.vid[_IDC_BUTTON5]);
//  e = __get_ini_value(path, "part1", "b6_id", wnd._nconfig.vid[_IDC_BUTTON6]);
//  e = __get_ini_value(path, "part1", "b7_id", wnd._nconfig.vid[_IDC_BUTTON7]);
//  e = __get_ini_value(path, "part1", "b8_id", wnd._nconfig.vid[_IDC_BUTTON8]);
//  e = __get_ini_value(path, "part1", "b9_id", wnd._nconfig.vid[_IDC_BUTTON9]);
//  e = __get_ini_value(path, "part1", "b10_id", wnd._nconfig.vid[_IDC_BUTTON10]);
//  e = __get_ini_value(path, "part1", "b11_id", wnd._nconfig.vid[_IDC_BUTTON11]);
//  e = __get_ini_value(path, "part1", "b12_id", wnd._nconfig.vid[_IDC_BUTTON12]);
//
//  e = __get_ini_value(path, "part2", "b1", wnd._nconfig.v[_IDC_BUTTON13]);
//  e = __get_ini_value(path, "part2", "b2", wnd._nconfig.v[_IDC_BUTTON14]);
//  e = __get_ini_value(path, "part2", "b3", wnd._nconfig.v[_IDC_BUTTON15]);
//  e = __get_ini_value(path, "part2", "b4", wnd._nconfig.v[_IDC_BUTTON16]);
//  e = __get_ini_value(path, "part2", "b5", wnd._nconfig.v[_IDC_BUTTON17]);
//  e = __get_ini_value(path, "part2", "b6", wnd._nconfig.v[_IDC_BUTTON18]);
//  e = __get_ini_value(path, "part2", "b7", wnd._nconfig.v[_IDC_BUTTON19]);
//  e = __get_ini_value(path, "part2", "b8", wnd._nconfig.v[_IDC_BUTTON20]);
//
//  e = __get_ini_value(path, "part2", "b1_id", wnd._nconfig.vid[_IDC_BUTTON13]);
//  e = __get_ini_value(path, "part2", "b2_id", wnd._nconfig.vid[_IDC_BUTTON14]);
//  e = __get_ini_value(path, "part2", "b3_id", wnd._nconfig.vid[_IDC_BUTTON15]);
//  e = __get_ini_value(path, "part2", "b4_id", wnd._nconfig.vid[_IDC_BUTTON16]);
//  e = __get_ini_value(path, "part2", "b5_id", wnd._nconfig.vid[_IDC_BUTTON17]);
//  e = __get_ini_value(path, "part2", "b6_id", wnd._nconfig.vid[_IDC_BUTTON18]);
//  e = __get_ini_value(path, "part2", "b7_id", wnd._nconfig.vid[_IDC_BUTTON19]);
//  e = __get_ini_value(path, "part2", "b8_id", wnd._nconfig.vid[_IDC_BUTTON20]);
//
//
//
//  e = __get_ini_value(path, "part3", "b1", wnd._nconfig.v[_IDC_BUTTON_U]);
//  e = __get_ini_value(path, "part3", "b2", wnd._nconfig.v[_IDC_BUTTON_S]);
//  e = __get_ini_value(path, "part3", "b3", wnd._nconfig.v[_IDC_BUTTON_D]);
//  e = __get_ini_value(path, "part3", "b4", wnd._nconfig.v[_IDC_BUTTON_X]);
//}
//

//void init_status()
//{
//  int32_t i = 0;
//
//  for ( i=0 ;i<20 ; i++ )
//  {
//    wnd._nserial.qstatus[i] = 'X';
//  }
//}

void fxWM_DRAW_TABCONTROL(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int32_t idx = 0;

  SHOW_MODE[_WMTIF]= SW_SHOW;

  wnd.item[_WDRAWWND].hwnd = CreateDialogParam(wnd.hinst[0], MAKEINTRESOURCE(IDD_FORMVIEW_DRAW), wnd.tab, (DLGPROC)wdrawwnd_dlgproc, lparam);
  SetParent(wnd.item[_WDRAWWND].hwnd, hwnd);
  SetWindowPos(wnd.item[_WDRAWWND].hwnd, 0, wnd.rct.left+TAB_LEFT_MARGIN, wnd.rct.top+TAB_TOP_MARGIN, wnd.rct.right, wnd.rct.bottom, SWP_NOZORDER|SWP_SHOWWINDOW);
  ShowWindow(wnd.item[_WDRAWWND].hwnd, SHOW_MODE[_WDRAWWND]);

  wnd.item[_WMTIF].hwnd = CreateDialogParam(wnd.hinst[0], MAKEINTRESOURCE(IDD_FORMVIEW_MAIN), wnd.tab, (DLGPROC)wmtif_dlgproc, lparam);
  SetParent(wnd.item[_WMTIF].hwnd, hwnd);
  SetWindowPos(wnd.item[_WMTIF].hwnd, 0, wnd.rct.left+TAB_LEFT_MARGIN, wnd.rct.top+TAB_TOP_MARGIN, wnd.rct.right, wnd.rct.bottom, SWP_NOZORDER|SWP_SHOWWINDOW);
  ShowWindow(wnd.item[_WMTIF].hwnd, SHOW_MODE[_WMTIF]);

  wnd.item[_WPRIME].hwnd = CreateDialogParam(wnd.hinst[0], MAKEINTRESOURCE(IDD_FORMVIEW_PRIME), wnd.tab, (DLGPROC)wprime_dlgproc, lparam);
  SetParent(wnd.item[_WPRIME].hwnd, hwnd);
  SetWindowPos(wnd.item[_WPRIME].hwnd, 0, wnd.rct.left+TAB_LEFT_MARGIN, wnd.rct.top+TAB_TOP_MARGIN, wnd.rct.right, wnd.rct.bottom, SWP_NOZORDER|SWP_SHOWWINDOW);
  ShowWindow(wnd.item[_WPRIME].hwnd, SHOW_MODE[_WPRIME]);

  wnd.item[_WBITMAP].hwnd = CreateDialogParam(wnd.hinst[0], MAKEINTRESOURCE(IDD_FORMVIEW_BITMAP), wnd.tab, (DLGPROC)wbitmap_dlgproc, lparam);
  SetParent(wnd.item[_WBITMAP].hwnd, hwnd);
  SetWindowPos(wnd.item[_WBITMAP].hwnd, 0, wnd.rct.left + TAB_LEFT_MARGIN, wnd.rct.top + TAB_TOP_MARGIN, wnd.rct.right, wnd.rct.bottom, SWP_NOZORDER | SWP_SHOWWINDOW);
  ShowWindow(wnd.item[_WBITMAP].hwnd, SHOW_MODE[_WBITMAP]);

  wnd.item[_WWSC].hwnd = CreateDialogParam(wnd.hinst[0], MAKEINTRESOURCE(IDD_FORMVIEW_WSC), wnd.tab, (DLGPROC)wwsc_dlgproc, lparam);
  SetParent(wnd.item[_WWSC].hwnd, hwnd);
  SetWindowPos(wnd.item[_WWSC].hwnd, 0, wnd.rct.left + TAB_LEFT_MARGIN, wnd.rct.top + TAB_TOP_MARGIN, wnd.rct.right, wnd.rct.bottom, SWP_NOZORDER | SWP_SHOWWINDOW);
  ShowWindow(wnd.item[_WWSC].hwnd, SHOW_MODE[_WWSC]);

  wnd.item[_WWSGW].hwnd = CreateDialogParam(wnd.hinst[0], MAKEINTRESOURCE(IDD_FORMVIEW_WSGW), wnd.tab, (DLGPROC)wwsgw_dlgproc, lparam);
  SetParent(wnd.item[_WWSGW].hwnd, hwnd);
  SetWindowPos(wnd.item[_WWSGW].hwnd, 0, wnd.rct.left + TAB_LEFT_MARGIN, wnd.rct.top + TAB_TOP_MARGIN, wnd.rct.right, wnd.rct.bottom, SWP_NOZORDER | SWP_SHOWWINDOW);
  ShowWindow(wnd.item[_WWSGW].hwnd, SHOW_MODE[_WWSGW]);


  for ( idx=0; ; idx++)
  {
    if ( SHOW_MODE[idx] == SW_SHOW )
    {
      break;
    }
  }  
  SendMessage(wnd.tab, TCM_SETCURSEL, (WPARAM)idx, 0);


  InvalidateRect(wnd.tab, 0, TRUE);

}

void fxWM_INIT_TABCONTROL(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  TCITEM tci = {0};
  wnd.tab = GetDlgItem(hwnd, IDC_TAB_CONTROL);

  tci.mask = TCIF_TEXT;

  tci.pszText = _T("axis");
  SendMessage(wnd.tab, TCM_INSERTITEM, (WPARAM)(int)_WDRAWWND, (LPARAM)&tci);

  tci.pszText = _T("mtif");
  SendMessage(wnd.tab, TCM_INSERTITEM, (WPARAM)(int)_WMTIF, (LPARAM)&tci);

  tci.pszText = _T("prime");
  SendMessage(wnd.tab, TCM_INSERTITEM, (WPARAM)(int)_WPRIME, (LPARAM)&tci);

  tci.pszText = _T("bitmap");
  SendMessage(wnd.tab, TCM_INSERTITEM, (WPARAM)(int)_WBITMAP, (LPARAM)&tci);

  tci.pszText = _T("websocket client");
  SendMessage(wnd.tab, TCM_INSERTITEM, (WPARAM)(int)_WWSC, (LPARAM)&tci);

  tci.pszText = _T("websocket gateway");
  SendMessage(wnd.tab, TCM_INSERTITEM, (WPARAM)(int)_WWSGW, (LPARAM)&tci);

  GetClientRect(wnd.tab, &wnd.rct);
  SendMessage(wnd.tab, TCM_ADJUSTRECT, FALSE, (LPARAM)&wnd.rct);
}


void* fxWM_INITDIALOG(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int32_t _index = 0;
  int8_t _top_title[256] = {0};
  wchar_t wcs[1024] = {0};
  int32_t e = 0;


  fxWM_INIT_TABCONTROL(hwnd, msg, wparam, lparam);
  fxWM_DRAW_TABCONTROL(hwnd, msg, wparam, lparam);


  #if 0



  mtif_create(&wnd.mtif);
  wnd.wd.pm = &wnd.mtif;
  wnd.wm.pm = &wnd.mtif;
  wnd.wp.pm = &wnd.mtif;
  wnd.wb.pm = &wnd.mtif;
  wnd.ww.pm = &wnd.mtif;
  wnd.wg.pm = &wnd.mtif;

  #endif





  wdrawwnd_init(wnd.item[_WDRAWWND].hwnd, &wnd.wd);
  wmtif_init(wnd.item[_WMTIF].hwnd, &wnd.wm);
  wprime_init(wnd.item[_WPRIME].hwnd, &wnd.wp);
  wbitmap_init(wnd.item[_WBITMAP].hwnd, &wnd.wb);
  wwsc_init(wnd.item[_WWSC].hwnd, &wnd.ww);
  wwsgw_init(wnd.item[_WWSGW].hwnd, &wnd.wg);


  __on_center(0, hwnd);
  sprintf(_top_title, "%s : (%d) ", TOP_TITLE, (int32_t)GetCurrentThreadId());
  e = MultiByteToWideChar(CP_ACP, 0, _top_title, -1, wcs, strlen(_top_title)+1);
  SetWindowText(hwnd, wcs);

 

  return (void*)TRUE;
}




void CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime)
{
  uint8_t mbs[512] = {0};
  //sprintf(mbs, "%s FAIL", wnd.item[nIDEvent].cap);
  //__setLog(mbs, strlen(mbs));
  KillTimer(hWnd, nIDEvent);
}


void SaveCaption()
{
  int32_t e = 0;
  int8_t caption[512] = {0};

  //e = GetText(wnd.item[XM_EDIT2].hwnd, caption, 512);
  //set_history("D1", caption, e);

  //e = GetText(wnd.item[XM_EDIT3].hwnd, caption, 512);
  //set_history("D2", caption, e);

  //e = GetText(wnd.item[XM_EDIT4].hwnd, caption, 512);
  //set_history("D3", caption, e);

  //e = GetText(wnd.item[XM_EDIT5].hwnd, caption, 512);
  //set_history("D4", caption, e);

  //e = GetText(wnd.item[XM_EDIT6].hwnd, caption, 512);
  //set_history("D5", caption, e);
}


#if 0
void* fxIDC_BUTTON20(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int8_t caption[512] = {0};
  int32_t _idc_id = _IDC_BUTTON20;
  int32_t e = 0;
  int32_t i = 0;
  int32_t w = 0;

  if ( wnd._nserial.fd > 0 )
  {
    wnd._nserial.qbuf[i] = '#'; i++;
    wnd._nserial.qbuf[i] = wnd._nconfig.vid[_idc_id][0]; i++;
    wnd._nserial.qbuf[i] = wnd._nconfig.vid[_idc_id][1]; i++;
    wnd._nserial.qbuf[i] = '0'; i++;
    wnd._nserial.qbuf[i] = '0'; i++;
    wnd._nserial.qbuf[i] = '0'; i++;
    wnd._nserial.qbuf[i] = '0'; i++;
    if ( wnd._nserial.qstatus[19] == 'X' ) wnd._nserial.qstatus[19] = wnd._nserial.qbuf[i] = 'E';
    else wnd._nserial.qstatus[19] = wnd._nserial.qbuf[i] = 'X';
    i++;
    wnd._nserial.qbuf[i] = jmtBCC(wnd._nserial.qbuf, i); i++;
    wnd._nserial.qbuf[i] = 0x0d; i++;
    e = nserial_write(&wnd._nserial, wnd._nserial.fd, wnd._nserial.qbuf, i, 0, &wnd._nserial);
    if ( e > 0 ) SetTimer(hwnd, _idc_id, TIMER_TM, TimerProc);
  }

  if ( wnd._nserial.qstatus[19] == 'E' )  SetBkColorMessage(wnd.item[_idc_id].hwnd, WM_CTLCOLORBTN, &wnd.item[_idc_id], RGB(0, 0, 0xFF) );
  else SetBkColorMessage(wnd.item[_idc_id].hwnd, WM_CTLCOLORBTN, &wnd.item[_idc_id], RGB(0, 0, 0xAA) );

  return (void*)TRUE;
}

#endif

void* fxWM_COMMAND(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  switch(LOWORD(wparam))
  {
    default:
      ontray_command(hwnd, msg, wparam, lparam);
      break;
  }

  return (void*)TRUE;
}



void* fxWM_NOTIFY(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int32_t idx = SendMessage(wnd.tab, TCM_GETCURSEL, 0, 0);
  int32_t i=0;

  for ( i=0 ; i<_TAB_MAX ; i++ )
  {
    ShowWindow(wnd.item[i].hwnd, (idx==i)?SW_SHOW:SW_HIDE);
  }
  return (void*)TRUE;
}

void* fxWM_DRAWITEM(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int32_t e = 0;
  int32_t id = 0;
  uint8_t caps[64] = {0};
  wchar_t wcs[1024] = {0};
  LPDRAWITEMSTRUCT lpdis =(LPDRAWITEMSTRUCT)lparam;
  switch ( lpdis->CtlID )
  {

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
      //nserial_close(&wnd._nserial);
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
  DialogBox(hinst, (LPCSTR)IDD_DIALOG, HWND_DESKTOP, (DLGPROC)dlgproc);
  return TRUE;
}
