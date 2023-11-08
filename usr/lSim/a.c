#include <a.h>
#include <locale.h>
#define COUNT_MOD        0x7F

XWND wnd;

#define TAB_LEFT_MARGIN    12
#define TAB_TOP_MARGIN     8   



//#define SIFR_MODULE      "sifr.kit.x86.dll" //"lite.sifr.x86.dll"
#define SIFR_MODULE      "lite.sifr.x86.dll"

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


//
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
//  if ( p->hbrush ) DeleteObject(p->hbrush);
//
//  p->hbrush = CreateSolidBrush(color);
//  memdc = CreateCompatibleDC(p->hdc);
//  hbmp = CreateCompatibleBitmap(p->hdc, (p->rct.right)-(p->rct.left), (p->rct.bottom)-(p->rct.top));
//  obmp = SelectObject(memdc, hbmp);
//
//  SelectObject(memdc, obmp);
//
//  DeleteObject(hbmp);
//  DeleteDC(memdc);
//
//  DeleteDC(p->hdc);
//  EndPaint(p->hwnd, &p->ps);
//
//  return (void*)p->hbrush;
//}

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


int32_t getEditHandleIndex(HWND h)
{
  int32_t i = 0;

  for ( i=_IDC_EDIT1 ; i<_IDC_EDIT_MAX ; i++ )
  {
    if ( h == wnd.item[i].hwnd ) break;
  }

  return i==_IDC_EDIT_MAX?-1:i;
}
int32_t getSpinHandleIndex(HWND h)
{
  int32_t i = 0;

  for ( i=_IDC_SPIN1 ; i<_IDC_SPIN_MAX ; i++ )
  {
    if ( h == wnd.item[i].hwnd ) break;
  }

  return i==_IDC_SPIN_MAX?-1:i;
}

void* SetBkColorMessage(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  //_WND* p = (_WND*)wparam;
  //p->color[0] = (COLORREF)lparam;
  //PostMessage(hwnd, msg, p, (COLORREF)lparam);
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
      //return (BOOL)SetBackgroundColor(&wnd.item[id], COLOR_READY);      ////////////////////////<<<<<<<<<<<<<<-----------------

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
  //int32_t idx = 0;

  //SHOW_MODE[_WMTIF]= SW_SHOW;

  //wnd.item[_WDRAWWND].hwnd = CreateDialogParam(wnd.hinst[0], MAKEINTRESOURCE(IDD_FORMVIEW_DRAW), wnd.tab, (DLGPROC)wdrawwnd_dlgproc, lparam);
  //SetParent(wnd.item[_WDRAWWND].hwnd, hwnd);
  //SetWindowPos(wnd.item[_WDRAWWND].hwnd, 0, wnd.rct.left+TAB_LEFT_MARGIN, wnd.rct.top+TAB_TOP_MARGIN, wnd.rct.right, wnd.rct.bottom, SWP_NOZORDER|SWP_SHOWWINDOW);
  //ShowWindow(wnd.item[_WDRAWWND].hwnd, SHOW_MODE[_WDRAWWND]);

  //wnd.item[_WMTIF].hwnd = CreateDialogParam(wnd.hinst[0], MAKEINTRESOURCE(IDD_FORMVIEW_MAIN), wnd.tab, (DLGPROC)wmtif_dlgproc, lparam);
  //SetParent(wnd.item[_WMTIF].hwnd, hwnd);
  //SetWindowPos(wnd.item[_WMTIF].hwnd, 0, wnd.rct.left+TAB_LEFT_MARGIN, wnd.rct.top+TAB_TOP_MARGIN, wnd.rct.right, wnd.rct.bottom, SWP_NOZORDER|SWP_SHOWWINDOW);
  //ShowWindow(wnd.item[_WMTIF].hwnd, SHOW_MODE[_WMTIF]);

  //wnd.item[_WPRIME].hwnd = CreateDialogParam(wnd.hinst[0], MAKEINTRESOURCE(IDD_FORMVIEW_PRIME), wnd.tab, (DLGPROC)wprime_dlgproc, lparam);
  //SetParent(wnd.item[_WPRIME].hwnd, hwnd);
  //SetWindowPos(wnd.item[_WPRIME].hwnd, 0, wnd.rct.left+TAB_LEFT_MARGIN, wnd.rct.top+TAB_TOP_MARGIN, wnd.rct.right, wnd.rct.bottom, SWP_NOZORDER|SWP_SHOWWINDOW);
  //ShowWindow(wnd.item[_WPRIME].hwnd, SHOW_MODE[_WPRIME]);

  //wnd.item[_WBITMAP].hwnd = CreateDialogParam(wnd.hinst[0], MAKEINTRESOURCE(IDD_FORMVIEW_BITMAP), wnd.tab, (DLGPROC)wbitmap_dlgproc, lparam);
  //SetParent(wnd.item[_WBITMAP].hwnd, hwnd);
  //SetWindowPos(wnd.item[_WBITMAP].hwnd, 0, wnd.rct.left + TAB_LEFT_MARGIN, wnd.rct.top + TAB_TOP_MARGIN, wnd.rct.right, wnd.rct.bottom, SWP_NOZORDER | SWP_SHOWWINDOW);
  //ShowWindow(wnd.item[_WBITMAP].hwnd, SHOW_MODE[_WBITMAP]);

  //wnd.item[_WWSC].hwnd = CreateDialogParam(wnd.hinst[0], MAKEINTRESOURCE(IDD_FORMVIEW_WSC), wnd.tab, (DLGPROC)wwsc_dlgproc, lparam);
  //SetParent(wnd.item[_WWSC].hwnd, hwnd);
  //SetWindowPos(wnd.item[_WWSC].hwnd, 0, wnd.rct.left + TAB_LEFT_MARGIN, wnd.rct.top + TAB_TOP_MARGIN, wnd.rct.right, wnd.rct.bottom, SWP_NOZORDER | SWP_SHOWWINDOW);
  //ShowWindow(wnd.item[_WWSC].hwnd, SHOW_MODE[_WWSC]);

  //wnd.item[_WWSGW].hwnd = CreateDialogParam(wnd.hinst[0], MAKEINTRESOURCE(IDD_FORMVIEW_WSGW), wnd.tab, (DLGPROC)wwsgw_dlgproc, lparam);
  //SetParent(wnd.item[_WWSGW].hwnd, hwnd);
  //SetWindowPos(wnd.item[_WWSGW].hwnd, 0, wnd.rct.left + TAB_LEFT_MARGIN, wnd.rct.top + TAB_TOP_MARGIN, wnd.rct.right, wnd.rct.bottom, SWP_NOZORDER | SWP_SHOWWINDOW);
  //ShowWindow(wnd.item[_WWSGW].hwnd, SHOW_MODE[_WWSGW]);


  //for ( idx=0; ; idx++)
  //{
  //  if ( SHOW_MODE[idx] == SW_SHOW )
  //  {
  //    break;
  //  }
  //}  
  //SendMessage(wnd.tab, TCM_SETCURSEL, (WPARAM)idx, 0);


  //InvalidateRect(wnd.tab, 0, TRUE);

}

void fxWM_INIT_TABCONTROL(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  //TCITEM tci = {0};
  //wnd.tab = GetDlgItem(hwnd, IDC_TAB_CONTROL);

  //tci.mask = TCIF_TEXT;

  //tci.pszText = _T("axis");
  //SendMessage(wnd.tab, TCM_INSERTITEM, (WPARAM)(int)_WDRAWWND, (LPARAM)&tci);

  //tci.pszText = _T("mtif");
  //SendMessage(wnd.tab, TCM_INSERTITEM, (WPARAM)(int)_WMTIF, (LPARAM)&tci);

  //tci.pszText = _T("prime");
  //SendMessage(wnd.tab, TCM_INSERTITEM, (WPARAM)(int)_WPRIME, (LPARAM)&tci);

  //tci.pszText = _T("bitmap");
  //SendMessage(wnd.tab, TCM_INSERTITEM, (WPARAM)(int)_WBITMAP, (LPARAM)&tci);

  //tci.pszText = _T("websocket client");
  //SendMessage(wnd.tab, TCM_INSERTITEM, (WPARAM)(int)_WWSC, (LPARAM)&tci);

  //tci.pszText = _T("websocket gateway");
  //SendMessage(wnd.tab, TCM_INSERTITEM, (WPARAM)(int)_WWSGW, (LPARAM)&tci);

  //GetClientRect(wnd.tab, &wnd.rct);
  //SendMessage(wnd.tab, TCM_ADJUSTRECT, FALSE, (LPARAM)&wnd.rct);
}



void* __socketConnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnsocket* p = (cnsocket*)o;
  int32_t idx = (extra==0)?0:(*(int32_t*)extra);



  LVLog(wnd.item[_IDC_LIST1].hwnd, 0, 2000, &wnd.log, "log", "socket", "connected ");


  return 0;
}







void* __socketDisconnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnsocket* p = (cnsocket*)o;
  //p->io.__f[IMTIF_CALLBACK_CONNECTED] = 0;

  return 0;
}
void* __socketStatus(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnsocket* p = (cnsocket*)o;
  int32_t idx = 0;


  if ( (sz&0xE000FF00) == 0xE0001000 ) return 0;
  LVLog(wnd.item[_IDC_LIST1].hwnd, wnd.item[_IDC_CHECK1].hwnd, 2000, &wnd.log, "log", "socket", "socket status %08X", (uint32_t)sz);


  switch(sz)
  {
    case 0xE000FDAA:
      idx = (extra==0)?0:(*(int32_t*)extra);
      wnd.sck.fds[idx] = fd;
      LVLog(wnd.item[_IDC_LIST1].hwnd, wnd.item[_IDC_CHECK1].hwnd, 2000, &wnd.log, "log", "socket", "client connected[%d] : %d", idx, fd);
      break;


    case 0xE400FDFA:
      idx = (extra==0)?0:(*(int32_t*)extra);
      wnd.sck.fds[idx] = fd;
      LVLog(wnd.item[_IDC_LIST1].hwnd, wnd.item[_IDC_CHECK1].hwnd, 2000, &wnd.log, "log", "socket", "client disconnected[%d] : %d", idx, fd);
      break;

  }

  return 0;
}
void* __socketRead(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnsocket* p = (cnsocket*)o;
  int32_t e = 0;
  int32_t buf[1024] = {0};

  e = __fprint_raw_buffer(0, b, sz, buf);


  LVLog(wnd.item[_IDC_LIST1].hwnd, wnd.item[_IDC_CHECK1].hwnd, 2000, &wnd.log, "log", "socket", "client[%d] - read (%4d) : %s", fd, sz, buf);

  //__fprintf_buffer(b, sz, 0, 16, "read (%5d) %08X(%5d)\r\n", fd, sz, sz);


  return 0;
}

#if 0
void CALLBACK OnTCPTimer(HWND hWnd, UINT nMsg, UINT_PTR nIDEvent, DWORD dwTime) 
{
  int32_t i = 0;
  int32_t e = 0;
  int8_t* buf[1024] = {0};
  uint8_t pkt[1024] = {0};
  int32_t sz = 0;

  pkt[sz] = 'I'; sz++;
  pkt[sz] = 'N'; sz++;
  pkt[sz] = 'T'; sz++;
  pkt[sz] = 'S'; sz++;

  for ( i=0 ; i<10 ; i++ )
  {
    pkt[sz] = 0x01; sz++;  //channel

    pkt[sz] = 0x01; sz++;  // GridOn

    pkt[sz] = 0x10; sz++;  // connected

    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;

    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;

    pkt[sz] = 0x10; sz++;

    pkt[sz] = 0x01; sz++;

    pkt[sz] = 0x01; sz++;

    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;

    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;


    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;


    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;

    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;

    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;

    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;

    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;

    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;

    pkt[sz] = 0x00; sz++;


    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;

    pkt[sz] = 0x00; sz++;

    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;
    pkt[sz] = 0x00; sz++;
  }

  e = __fprint_raw_buffer(0, pkt, sz, buf);

  for ( i=0 ; i<MAX_CLIENT ; i++ )
  {
    if ( wnd.sck.fds[i] > 0 )
    {
      LVLog(wnd.item[_IDC_LIST1].hwnd, wnd.item[_IDC_CHECK1].hwnd, 2000, &wnd.log, "log", "socket", "client[%d] - wrte (%4d) : %s", wnd.sck.fds[i], sz, buf);
      __nsocket_write(&wnd.sck, wnd.sck.fds[i], pkt, sz, 0, &wnd);
    }
  }
}
#endif




/************************************************************************************/
/**                                                                                **/
/**                                                                                **/
/**                                                                                **/
/**                                                                                **/
/**                                SIM PROTOCOL                                    **/
/**                                                                                **/
/**                                                                                **/
/**                                                                                **/
/**                                                                                **/
/**                                                                                **/
/************************************************************************************/
uint8_t to_8bit(uint8_t* txt, uint8_t* b)
{
  int32_t i=0;
  for ( i=0 ; i<8 ; i++ )
    *b |= (*(txt+i)=='1'?1<<(7-i):0);
  return *b;
}

int32_t spin_value(int32_t idx, uint32_t up_down)
{
  int32_t sz = 0;
  uint8_t out = 0;
  uint8_t bbuf[9] = {0};
  uint8_t txt[128] = {0};
  GetText(wnd.item[idx].hwnd, txt, 128);
  if ( idx==_IDC_EDIT1 || idx==_IDC_EDIT2 ) // binary
  {
    to_8bit(txt, &out);
    if ( up_down == 'U' || up_down == 'u' ) out<<=1;
    else out>>=1;
    sz = __digit_to_bin_buffer(out, bbuf);
  }
  else
  if ( idx==_IDC_EDIT3 || idx==_IDC_EDIT6 || idx==_IDC_EDIT18 || idx==_IDC_EDIT20 ) // hex
  {
    out = __hex_to_decimal(txt, strlen(txt));
    if ( up_down == 'U' || up_down == 'u' ) out++;
    else out--;
    sprintf(bbuf, "%02X", out);
    sz = 2;
  }
  else // decimal
  {
    sz = atoi(txt);
    if ( up_down == 'U' || up_down == 'u' ) sz++;
    else sz--;
    sprintf(bbuf, "%d", sz);
    sz = strlen(bbuf);
  }

  SetText(wnd.item[idx].hwnd, bbuf, sz);
}

int32_t protocol_get_channel(uint8_t* pkt)
{
  uint8_t out = 0;
  uint8_t txt[128] = {0};
  GetText(wnd.item[_IDC_EDIT1].hwnd, txt, 128);
  *pkt = to_8bit(txt, &out);
  return 1;
}

int32_t protocol_get_response(uint8_t* pkt)
{
  uint8_t out = 0;
  uint8_t txt[128] = {0};
  GetText(wnd.item[_IDC_EDIT2].hwnd, txt, 128);
  *pkt = to_8bit(txt, &out);
  return 1;
}
int32_t protocol_get_status(uint8_t* pkt)
{
  uint8_t txt[128] = {0};
  GetText(wnd.item[_IDC_EDIT3].hwnd, txt, 128);
  *pkt = __hex_to_digit(txt);
  return 1;
}

int32_t protocol_get_cycle(uint8_t* pkt)
{
  uint8_t txt[128] = {0};
  GetText(wnd.item[_IDC_EDIT4].hwnd, txt, 128);
  *pkt = (atoi(txt)&0x000000FF);
  *(pkt+1) = (atoi(txt)&0x0000FF00)>>8;
  return 2;
}
int32_t protocol_get_step(uint8_t* pkt)
{
  uint8_t txt[128] = {0};
  GetText(wnd.item[_IDC_EDIT5].hwnd, txt, 128);
  *pkt = (atoi(txt)&0x000000FF);
  *(pkt+1) = (atoi(txt)&0x0000FF00)>>8;
  return 2;
}

int32_t protocol_get_typemode(uint8_t* pkt)
{
  uint8_t txt[128] = {0};
  GetText(wnd.item[_IDC_EDIT6].hwnd, txt, 128);
  *pkt = __hex_to_digit(txt);
  return 1;
}

int32_t protocol_get_cycleloop(uint8_t* pkt)
{
  uint8_t txt[128] = {0};
  GetText(wnd.item[_IDC_EDIT7].hwnd, txt, 128);
  *pkt = (atoi(txt)&0x000000FF);
  return 1;
}
int32_t protocol_get_steploop(uint8_t* pkt)
{
  uint8_t txt[128] = {0};
  GetText(wnd.item[_IDC_EDIT8].hwnd, txt, 128);
  *pkt = (atoi(txt)&0x000000FF);
  return 1;
}

int32_t protocol_get_voltage(uint8_t* pkt)
{
  uint8_t txt[128] = {0};
  GetText(wnd.item[_IDC_EDIT9].hwnd, txt, 128);
  *pkt = (atoi(txt)&0x000000FF);
  *(pkt+1) = (atoi(txt)&0x0000FF00)>>8;;
  *(pkt+2) = (atoi(txt)&0x00FF0000)>>16;
  return 3;
}


int32_t protocol_get_current(uint8_t* pkt)
{
  uint8_t txt[128] = {0};
  GetText(wnd.item[_IDC_EDIT10].hwnd, txt, 128);
  *pkt = (atoi(txt)&0x000000FF);
  *(pkt+1) = (atoi(txt)&0x0000FF00)>>8;;
  *(pkt+2) = (atoi(txt)&0x00FF0000)>>16;
  return 3;
}

int32_t protocol_get_daqtemp(uint8_t* pkt)
{
  uint8_t txt[128] = {0};
  GetText(wnd.item[_IDC_EDIT11].hwnd, txt, 128);
  *pkt = (atoi(txt)&0x000000FF);
  *(pkt+1) = (atoi(txt)&0x0000FF00)>>8;;
  *(pkt+2) = (atoi(txt)&0x00FF0000)>>16;
  return 3;
}

int32_t protocol_get_capacity(uint8_t* pkt)
{
  uint8_t txt[128] = {0};
  GetText(wnd.item[_IDC_EDIT12].hwnd, txt, 128);
  *pkt = (atoi(txt)&0x000000FF);
  *(pkt+1) = (atoi(txt)&0x0000FF00)>>8;;
  *(pkt+2) = (atoi(txt)&0x00FF0000)>>16;
  *(pkt+3) = (atoi(txt)&0xFF000000)>>24;
  return 4;
}

int32_t protocol_get_watthour(uint8_t* pkt)
{
  uint8_t txt[128] = {0};
  GetText(wnd.item[_IDC_EDIT13].hwnd, txt, 128);
  *pkt = (atoi(txt)&0x000000FF);
  *(pkt+1) = (atoi(txt)&0x0000FF00)>>8;;
  *(pkt+2) = (atoi(txt)&0x00FF0000)>>16;
  *(pkt+3) = (atoi(txt)&0xFF000000)>>24;
  return 4;
}

int32_t protocol_get_power(uint8_t* pkt)
{
  uint8_t txt[128] = {0};
  GetText(wnd.item[_IDC_EDIT14].hwnd, txt, 128);
  *pkt = (atoi(txt)&0x000000FF);
  *(pkt+1) = (atoi(txt)&0x0000FF00)>>8;;
  *(pkt+2) = (atoi(txt)&0x00FF0000)>>16;
  *(pkt+3) = (atoi(txt)&0xFF000000)>>24;
  return 4;
}

int32_t protocol_get_register(uint8_t* pkt)
{
  uint8_t txt[128] = {0};
  GetText(wnd.item[_IDC_EDIT15].hwnd, txt, 128);
  *pkt = (atoi(txt)&0x000000FF);
  *(pkt+1) = (atoi(txt)&0x0000FF00)>>8;
  *(pkt+2) = (atoi(txt)&0x00FF0000)>>16;
  return 3;
}

int32_t protocol_get_steptime(uint8_t* pkt)
{
  uint8_t txt[128] = {0};
  GetText(wnd.item[_IDC_EDIT16].hwnd, txt, 128);
  *pkt = (atoi(txt)&0x000000FF);
  *(pkt+1) = (atoi(txt)&0x0000FF00)>>8;;
  *(pkt+2) = (atoi(txt)&0x00FF0000)>>16;
  *(pkt+3) = (atoi(txt)&0xFF000000)>>24;
  return 4;
}


int32_t protocol_get_alarm(uint8_t* pkt)
{
  int32_t sz = 0;
  uint8_t txt[128] = {0};
  sz = GetText(wnd.item[_IDC_EDIT17].hwnd, txt, 128);
  memcpy(pkt, txt, sz);

  return 8;
}

int32_t protocol_get_stopcond_index(uint8_t* pkt)
{
  uint8_t txt[128] = {0};
  GetText(wnd.item[_IDC_EDIT18].hwnd, txt, 128);
  *pkt = __hex_to_digit(txt);
  return 1;
}

int32_t protocol_get_stopcond_value(uint8_t* pkt)
{
  uint8_t txt[128] = {0};
  GetText(wnd.item[_IDC_EDIT19].hwnd, txt, 128);
  *pkt = (atoi(txt)&0x000000FF);
  *(pkt+1) = (atoi(txt)&0x0000FF00)>>8;;
  *(pkt+2) = (atoi(txt)&0x00FF0000)>>16;
  *(pkt+3) = (atoi(txt)&0xFF000000)>>24;
  return 4;
}

int32_t protocol_get_safecond_index(uint8_t* pkt)
{
  uint8_t txt[128] = {0};
  GetText(wnd.item[_IDC_EDIT20].hwnd, txt, 128);
  *pkt = __hex_to_digit(txt);
  return 1;
}

int32_t protocol_get_safecond_value(uint8_t* pkt)
{
  uint8_t txt[128] = {0};
  GetText(wnd.item[_IDC_EDIT21].hwnd, txt, 128);
  *pkt = (atoi(txt)&0x000000FF);
  *(pkt+1) = (atoi(txt)&0x0000FF00)>>8;;
  *(pkt+2) = (atoi(txt)&0x00FF0000)>>16;
  *(pkt+3) = (atoi(txt)&0xFF000000)>>24;
  return 4;
}

void onTCPWrite(uint8_t* pkt, int32_t sz) 
{
  int32_t i = 0;
  int32_t e = 0;
  int8_t buf[8192] = {0};
  pkt[0] = 'I';
  pkt[1] = 'N';
  pkt[2] = 'T';
  pkt[3] = 'S';

  e = __fprint_raw_buffer(0, pkt, sz, buf);

  for ( i=0 ; i<MAX_CLIENT ; i++ )
  {
    if ( wnd.sck.fds[i] > 0 )
    {
      LVLog(wnd.item[_IDC_LIST1].hwnd, wnd.item[_IDC_CHECK1].hwnd, 2000, &wnd.log, "log", "socket", "client[%d] - wrte (%4d) : %s", wnd.sck.fds[i], sz, buf);
      __nsocket_write(&wnd.sck, wnd.sck.fds[i], pkt, sz, 0, &wnd);
    }
  }
}
void CALLBACK OnTCPTimer(HWND hWnd, UINT nMsg, UINT_PTR nIDEvent, DWORD dwTime) 
{
  if ( wnd._pkt_sz == 0 ) wnd._pkt_sz += 4;
  wnd._pkt_sz += protocol_get_channel(&wnd._pkt[wnd._pkt_sz]);
  wnd._pkt_sz += protocol_get_response(&wnd._pkt[wnd._pkt_sz]);
  wnd._pkt_sz += protocol_get_status(&wnd._pkt[wnd._pkt_sz]);
  wnd._pkt_sz += protocol_get_cycle(&wnd._pkt[wnd._pkt_sz]);
  wnd._pkt_sz += protocol_get_step(&wnd._pkt[wnd._pkt_sz]);
  wnd._pkt_sz += protocol_get_typemode(&wnd._pkt[wnd._pkt_sz]);
  wnd._pkt_sz += protocol_get_cycleloop(&wnd._pkt[wnd._pkt_sz]);
  wnd._pkt_sz += protocol_get_steploop(&wnd._pkt[wnd._pkt_sz]);
  wnd._pkt_sz += protocol_get_voltage(&wnd._pkt[wnd._pkt_sz]);
  wnd._pkt_sz += protocol_get_current(&wnd._pkt[wnd._pkt_sz]);
  wnd._pkt_sz += protocol_get_daqtemp(&wnd._pkt[wnd._pkt_sz]);
  wnd._pkt_sz += protocol_get_capacity(&wnd._pkt[wnd._pkt_sz]);
  wnd._pkt_sz += protocol_get_watthour(&wnd._pkt[wnd._pkt_sz]);
  wnd._pkt_sz += protocol_get_power(&wnd._pkt[wnd._pkt_sz]);
  wnd._pkt_sz += protocol_get_register(&wnd._pkt[wnd._pkt_sz]);
  wnd._pkt_sz += protocol_get_steptime(&wnd._pkt[wnd._pkt_sz]);
  wnd._pkt_sz += protocol_get_alarm(&wnd._pkt[wnd._pkt_sz]);
  wnd._pkt_sz += protocol_get_stopcond_index(&wnd._pkt[wnd._pkt_sz]);
  wnd._pkt_sz += protocol_get_stopcond_value(&wnd._pkt[wnd._pkt_sz]);
  wnd._pkt_sz += protocol_get_safecond_index(&wnd._pkt[wnd._pkt_sz]);
  wnd._pkt_sz += protocol_get_safecond_value(&wnd._pkt[wnd._pkt_sz]);


  if ( wnd._pkt_sz == 56*10 + 4 )
  {
    onTCPWrite(wnd._pkt, wnd._pkt_sz);
    wnd._pkt_sz = 0;
  }
}





void tcpd()
{
  wnd.sck.io.__f[__CALLBACK_CONNECTED] = __socketConnected;
  wnd.sck.io.__f[__CALLBACK_DISCONNECTED] = __socketDisconnected;
  wnd.sck.io.__f[__CALLBACK_STATUS] = __socketStatus;
  wnd.sck.io.__f[__CALLBACK_READ] = __socketRead;
  wnd.sck.io.__o = &wnd;

  sprintf(wnd.sck.io.argv[SOCKET_IP], "%s", "127.0.0.1");
  sprintf(wnd.sck.io.argv[SOCKET_PORT], "%s", "49243");
  sprintf(wnd.sck.io.argv[SOCKET_PROTOCOL], "%s", "TCP");
  sprintf(wnd.sck.io.argv[SOCKET_CSTYPE], "%s", "SERVER");
  sprintf(wnd.sck.io.argv[SOCKET_CASTTYPE], "%s", "UNICAST");


  wnd.sck.io.fd = __nsocket_open(&wnd.sck);


  SetTimer(wnd.hdlg, 0, 10, OnTCPTimer);
}

int32_t loadBinary(int8_t* fname, uint8_t** p)
{
  FILE* fp = 0;
  int32_t sz = 0;

  fp = fopen(fname, "rb");
  fseek(fp, 0, SEEK_SET);
  fseek(fp, 0, SEEK_END);
  sz = ftell(fp);

  *p = (uint8_t*)calloc(sz, sizeof(uint8_t));
  fseek(fp, 0, SEEK_SET);
  fread(*p, sizeof(uint8_t), sz, fp);

  if(fp) fclose(fp);

  return sz;
}


void sifr()
{
  int32_t e = 0;

  //#if defined LINUX
  //_crpt.sz = loadBinary(SIFR_MODULE, &_crpt.p);
  //#endif

  //#if defined WIN32
  //wnd._crpt.sz = loadBinary(SIFR_MODULE, &wnd._crpt.p);
  //#endif

  #if defined LINUX
  wnd._crpt.hdl = dlopen(SIFR_MODULE, RTLD_LAZY);
  if ( wnd._crpt.hdl == 0 )
  {
    printf("dlopen Fail %s\r\n", dlerror());
    return;
  }
  wnd._crpt.__sifr_init               = dlsym(wnd._crpt.hdl,"__sifr_init");
  wnd._crpt.__sifr_release            = dlsym(wnd._crpt.hdl,"__sifr_release");
  wnd._crpt.__sifr_version            = dlsym(wnd._crpt.hdl,"__sifr_version");
  wnd._crpt.__sifr_author             = dlsym(wnd._crpt.hdl,"__sifr_author");
  wnd._crpt.__sifr_module             = dlsym(wnd._crpt.hdl,"__sifr_module");
  wnd._crpt.__sifr_set_callback       = dlsym(wnd._crpt.hdl,"__sifr_set_callback");

  wnd._crpt.__sifr_base64             = dlsym(wnd._crpt.hdl,"__sifr_base64");

  wnd._crpt.__sifr_noise_source       = dlsym(wnd._crpt.hdl,"__sifr_noise_source");
  wnd._crpt.__sifr_entropy            = dlsym(wnd._crpt.hdl,"__sifr_entropy");
  wnd._crpt.__sifr_drbg               = dlsym(wnd._crpt.hdl,"__sifr_drbg");
  wnd._crpt.__sifr_random             = dlsym(wnd._crpt.hdl,"__sifr_random");
  wnd._crpt.__sifr_key                = dlsym(wnd._crpt.hdl,"__sifr_key");
  wnd._crpt.__sifr_self_check         = dlsym(wnd._crpt.hdl,"__sifr_self_check");
  wnd._crpt.__sifr_kat_check          = dlsym(wnd._crpt.hdl,"__sifr_kat_check");
  wnd._crpt.__sifr_integrity_check    = dlsym(wnd._crpt.hdl,"__sifr_integrity_check");

  wnd._crpt.__sifr_mem_clear          = dlsym(wnd._crpt.hdl,"__sifr_mem_clear");


  wnd._crpt.__sifr_last_status        = dlsym(wnd._crpt.hdl,"__sifr_last_status");
  wnd._crpt.__sifr_last_status_string = dlsym(wnd._crpt.hdl,"__sifr_last_status_string");


  wnd._crpt.__sifr_aria_ecb_encode  = dlsym(wnd._crpt.hdl,"__sifr_aria_ecb_encode");
  wnd._crpt.__sifr_aria_ecb_decode  = dlsym(wnd._crpt.hdl,"__sifr_aria_ecb_decode");
  wnd._crpt.__sifr_aria_cfb_encode  = dlsym(wnd._crpt.hdl,"__sifr_aria_cfb_encode");
  wnd._crpt.__sifr_aria_cfb_decode  = dlsym(wnd._crpt.hdl,"__sifr_aria_cfb_decode");
  wnd._crpt.__sifr_aria_cfb_encode  = dlsym(wnd._crpt.hdl,"__sifr_aria_cfb_encode");
  wnd._crpt.__sifr_aria_cfb_decode  = dlsym(wnd._crpt.hdl,"__sifr_aria_cfb_decode");
  wnd._crpt.__sifr_aria_ofb_encode  = dlsym(wnd._crpt.hdl,"__sifr_aria_ofb_encode");
  wnd._crpt.__sifr_aria_ofb_decode  = dlsym(wnd._crpt.hdl,"__sifr_aria_ofb_decode");
  wnd._crpt.__sifr_aria_ctr_encode  = dlsym(wnd._crpt.hdl,"__sifr_aria_ctr_encode");
  wnd._crpt.__sifr_aria_ctr_decode  = dlsym(wnd._crpt.hdl,"__sifr_aria_ctr_decode");
  wnd._crpt.__sifr_aria_ccm_encode  = dlsym(wnd._crpt.hdl,"__sifr_aria_ccm_encode");
  wnd._crpt.__sifr_aria_ccm_decode  = dlsym(wnd._crpt.hdl,"__sifr_aria_ccm_decode");

  wnd._crpt.__sifr_lea_ecb_encode  = dlsym(wnd._crpt.hdl,"__sifr_lea_ecb_encode");
  wnd._crpt.__sifr_lea_ecb_decode  = dlsym(wnd._crpt.hdl,"__sifr_lea_ecb_decode");
  wnd._crpt.__sifr_lea_cfb_encode  = dlsym(wnd._crpt.hdl,"__sifr_lea_cfb_encode");
  wnd._crpt.__sifr_lea_cfb_decode  = dlsym(wnd._crpt.hdl,"__sifr_lea_cfb_decode");
  wnd._crpt.__sifr_lea_cfb_encode  = dlsym(wnd._crpt.hdl,"__sifr_lea_cfb_encode");
  wnd._crpt.__sifr_lea_cfb_decode  = dlsym(wnd._crpt.hdl,"__sifr_lea_cfb_decode");
  wnd._crpt.__sifr_lea_ofb_encode  = dlsym(wnd._crpt.hdl,"__sifr_lea_ofb_encode");
  wnd._crpt.__sifr_lea_ofb_decode  = dlsym(wnd._crpt.hdl,"__sifr_lea_ofb_decode");
  wnd._crpt.__sifr_lea_ctr_encode  = dlsym(wnd._crpt.hdl,"__sifr_lea_ctr_encode");
  wnd._crpt.__sifr_lea_ctr_decode  = dlsym(wnd._crpt.hdl,"__sifr_lea_ctr_decode");

  wnd._crpt.__sifr_seed_ecb_encode  = dlsym(wnd._crpt.hdl,"__sifr_seed_ecb_encode");
  wnd._crpt.__sifr_seed_ecb_decode  = dlsym(wnd._crpt.hdl,"__sifr_seed_ecb_decode");
  wnd._crpt.__sifr_seed_cfb_encode  = dlsym(wnd._crpt.hdl,"__sifr_seed_cfb_encode");
  wnd._crpt.__sifr_seed_cfb_decode  = dlsym(wnd._crpt.hdl,"__sifr_seed_cfb_decode");
  wnd._crpt.__sifr_seed_cfb_encode  = dlsym(wnd._crpt.hdl,"__sifr_seed_cfb_encode");
  wnd._crpt.__sifr_seed_cfb_decode  = dlsym(wnd._crpt.hdl,"__sifr_seed_cfb_decode");
  wnd._crpt.__sifr_seed_ofb_encode  = dlsym(wnd._crpt.hdl,"__sifr_seed_ofb_encode");
  wnd._crpt.__sifr_seed_ofb_decode  = dlsym(wnd._crpt.hdl,"__sifr_seed_ofb_decode");
  wnd._crpt.__sifr_seed_ctr_encode  = dlsym(wnd._crpt.hdl,"__sifr_seed_ctr_encode");
  wnd._crpt.__sifr_seed_ctr_decode  = dlsym(wnd._crpt.hdl,"__sifr_seed_ctr_decode");

  wnd._crpt.__sifr_hight_ecb_encode  = dlsym(wnd._crpt.hdl,"__sifr_hight_ecb_encode");
  wnd._crpt.__sifr_hight_ecb_decode  = dlsym(wnd._crpt.hdl,"__sifr_hight_ecb_decode");
  wnd._crpt.__sifr_hight_cfb_encode  = dlsym(wnd._crpt.hdl,"__sifr_hight_cfb_encode");
  wnd._crpt.__sifr_hight_cfb_decode  = dlsym(wnd._crpt.hdl,"__sifr_hight_cfb_decode");
  wnd._crpt.__sifr_hight_cfb_encode  = dlsym(wnd._crpt.hdl,"__sifr_hight_cfb_encode");
  wnd._crpt.__sifr_hight_cfb_decode  = dlsym(wnd._crpt.hdl,"__sifr_hight_cfb_decode");
  wnd._crpt.__sifr_hight_ofb_encode  = dlsym(wnd._crpt.hdl,"__sifr_hight_ofb_encode");
  wnd._crpt.__sifr_hight_ofb_decode  = dlsym(wnd._crpt.hdl,"__sifr_hight_ofb_decode");
  wnd._crpt.__sifr_hight_ctr_encode  = dlsym(wnd._crpt.hdl,"__sifr_hight_ctr_encode");
  wnd._crpt.__sifr_hight_ctr_decode  = dlsym(wnd._crpt.hdl,"__sifr_hight_ctr_decode");

  wnd._crpt.__sifr_sha2    = dlsym(wnd._crpt.hdl,"__sifr_sha2");
  wnd._crpt.__sifr_hmac    = dlsym(wnd._crpt.hdl,"__sifr_hmac");
  wnd._crpt.__sifr_lsh256_224  = dlsym(wnd._crpt.hdl,"__sifr_lsh256_224");
  wnd._crpt.__sifr_lsh256_256  = dlsym(wnd._crpt.hdl,"__sifr_lsh256_256");
  wnd._crpt.__sifr_lsh512_224  = dlsym(wnd._crpt.hdl,"__sifr_lsh512_224");
  wnd._crpt.__sifr_lsh512_256  = dlsym(wnd._crpt.hdl,"__sifr_lsh512_256");
  wnd._crpt.__sifr_lsh512_384  = dlsym(wnd._crpt.hdl,"__sifr_lsh512_384");
  wnd._crpt.__sifr_lsh512_512  = dlsym(wnd._crpt.hdl,"__sifr_lsh512_512");

  wnd._crpt.setMessage  = dlsym(wnd._crpt.hdl,"__setMessage");
  wnd._crpt.putMessage  = dlsym(wnd._crpt.hdl,"__putMessage");
  #endif

  #if defined WIN32
  wnd._crpt.hdl = LoadLibrary(SIFR_MODULE);
  if ( wnd._crpt.hdl == 0 )
  {
    printf("LoadLibrary Fail\r\n");
    return;
  }
  *(FARPROC*)&wnd._crpt.__sifr_initia           = GetProcAddress(wnd._crpt.hdl,"__sifr_initia");
  *(FARPROC*)&wnd._crpt.__sifr_finelia          = GetProcAddress(wnd._crpt.hdl,"__sifr_finelia");
  *(FARPROC*)&wnd._crpt.__sifr_init             = GetProcAddress(wnd._crpt.hdl,"__sifr_init");
  *(FARPROC*)&wnd._crpt.__sifr_release          = GetProcAddress(wnd._crpt.hdl,"__sifr_release");
  *(FARPROC*)&wnd._crpt.__sifr_version          = GetProcAddress(wnd._crpt.hdl,"__sifr_version");
  *(FARPROC*)&wnd._crpt.__sifr_author           = GetProcAddress(wnd._crpt.hdl,"__sifr_author");
  *(FARPROC*)&wnd._crpt.__sifr_module           = GetProcAddress(wnd._crpt.hdl,"__sifr_module");
  *(FARPROC*)&wnd._crpt.__sifr_set_callback     = GetProcAddress(wnd._crpt.hdl,"__sifr_set_callback");

  *(FARPROC*)&wnd._crpt.__sifr_base64           = GetProcAddress(wnd._crpt.hdl,"__sifr_base64");

  *(FARPROC*)&wnd._crpt.__sifr_noise_source     = GetProcAddress(wnd._crpt.hdl,"__sifr_noise_source");
  *(FARPROC*)&wnd._crpt.__sifr_entropy          = GetProcAddress(wnd._crpt.hdl,"__sifr_entropy");
  *(FARPROC*)&wnd._crpt.__sifr_drbg             = GetProcAddress(wnd._crpt.hdl,"__sifr_drbg");
  *(FARPROC*)&wnd._crpt.__sifr_random           = GetProcAddress(wnd._crpt.hdl,"__sifr_random");
  *(FARPROC*)&wnd._crpt.__sifr_key              = GetProcAddress(wnd._crpt.hdl,"__sifr_key");
  *(FARPROC*)&wnd._crpt.__sifr_self_check       = GetProcAddress(wnd._crpt.hdl,"__sifr_self_check");
  *(FARPROC*)&wnd._crpt.__sifr_kat_check        = GetProcAddress(wnd._crpt.hdl,"__sifr_kat_check");
  *(FARPROC*)&wnd._crpt.__sifr_integrity_check  = GetProcAddress(wnd._crpt.hdl,"__sifr_integrity_check");

  *(FARPROC*)&wnd._crpt.__sifr_mem_clear        = GetProcAddress(wnd._crpt.hdl,"__sifr_mem_clear");

  *(FARPROC*)&wnd._crpt.__sifr_last_status         = GetProcAddress(wnd._crpt.hdl,"__sifr_last_status");
  *(FARPROC*)&wnd._crpt.__sifr_last_status_string  = GetProcAddress(wnd._crpt.hdl,"__sifr_last_status_string");

  *(FARPROC*)&wnd._crpt.__sifr_aria_ecb_encode  = GetProcAddress(wnd._crpt.hdl,"__sifr_aria_ecb_encode");
  *(FARPROC*)&wnd._crpt.__sifr_aria_ecb_decode  = GetProcAddress(wnd._crpt.hdl,"__sifr_aria_ecb_decode");
  *(FARPROC*)&wnd._crpt.__sifr_aria_cbc_encode  = GetProcAddress(wnd._crpt.hdl,"__sifr_aria_cbc_encode");
  *(FARPROC*)&wnd._crpt.__sifr_aria_cbc_decode  = GetProcAddress(wnd._crpt.hdl,"__sifr_aria_cbc_decode");
  *(FARPROC*)&wnd._crpt.__sifr_aria_cfb_encode  = GetProcAddress(wnd._crpt.hdl,"__sifr_aria_cfb_encode");
  *(FARPROC*)&wnd._crpt.__sifr_aria_cfb_decode  = GetProcAddress(wnd._crpt.hdl,"__sifr_aria_cfb_decode");
  *(FARPROC*)&wnd._crpt.__sifr_aria_ofb_encode  = GetProcAddress(wnd._crpt.hdl,"__sifr_aria_ofb_encode");
  *(FARPROC*)&wnd._crpt.__sifr_aria_ofb_decode  = GetProcAddress(wnd._crpt.hdl,"__sifr_aria_ofb_decode");
  *(FARPROC*)&wnd._crpt.__sifr_aria_ctr_encode  = GetProcAddress(wnd._crpt.hdl,"__sifr_aria_ctr_encode");
  *(FARPROC*)&wnd._crpt.__sifr_aria_ctr_decode  = GetProcAddress(wnd._crpt.hdl,"__sifr_aria_ctr_decode");
  *(FARPROC*)&wnd._crpt.__sifr_aria_ccm_encode  = GetProcAddress(wnd._crpt.hdl,"__sifr_aria_ccm_encode");
  *(FARPROC*)&wnd._crpt.__sifr_aria_ccm_decode  = GetProcAddress(wnd._crpt.hdl,"__sifr_aria_ccm_decode");

  *(FARPROC*)&wnd._crpt.__sifr_lea_ecb_encode  = GetProcAddress(wnd._crpt.hdl,"__sifr_lea_ecb_encode");
  *(FARPROC*)&wnd._crpt.__sifr_lea_ecb_decode  = GetProcAddress(wnd._crpt.hdl,"__sifr_lea_ecb_decode");
  *(FARPROC*)&wnd._crpt.__sifr_lea_cbc_encode  = GetProcAddress(wnd._crpt.hdl,"__sifr_lea_cbc_encode");
  *(FARPROC*)&wnd._crpt.__sifr_lea_cbc_decode  = GetProcAddress(wnd._crpt.hdl,"__sifr_lea_cbc_decode");
  *(FARPROC*)&wnd._crpt.__sifr_lea_cfb_encode  = GetProcAddress(wnd._crpt.hdl,"__sifr_lea_cfb_encode");
  *(FARPROC*)&wnd._crpt.__sifr_lea_cfb_decode  = GetProcAddress(wnd._crpt.hdl,"__sifr_lea_cfb_decode");
  *(FARPROC*)&wnd._crpt.__sifr_lea_ofb_encode  = GetProcAddress(wnd._crpt.hdl,"__sifr_lea_ofb_encode");
  *(FARPROC*)&wnd._crpt.__sifr_lea_ofb_decode  = GetProcAddress(wnd._crpt.hdl,"__sifr_lea_ofb_decode");
  *(FARPROC*)&wnd._crpt.__sifr_lea_ctr_encode  = GetProcAddress(wnd._crpt.hdl,"__sifr_lea_ctr_encode");
  *(FARPROC*)&wnd._crpt.__sifr_lea_ctr_decode  = GetProcAddress(wnd._crpt.hdl,"__sifr_lea_ctr_decode");

  *(FARPROC*)&wnd._crpt.__sifr_seed_ecb_encode  = GetProcAddress(wnd._crpt.hdl,"__sifr_seed_ecb_encode");
  *(FARPROC*)&wnd._crpt.__sifr_seed_ecb_decode  = GetProcAddress(wnd._crpt.hdl,"__sifr_seed_ecb_decode");
  *(FARPROC*)&wnd._crpt.__sifr_seed_cbc_encode  = GetProcAddress(wnd._crpt.hdl,"__sifr_seed_cbc_encode");
  *(FARPROC*)&wnd._crpt.__sifr_seed_cbc_decode  = GetProcAddress(wnd._crpt.hdl,"__sifr_seed_cbc_decode");
  *(FARPROC*)&wnd._crpt.__sifr_seed_cfb_encode  = GetProcAddress(wnd._crpt.hdl,"__sifr_seed_cfb_encode");
  *(FARPROC*)&wnd._crpt.__sifr_seed_cfb_decode  = GetProcAddress(wnd._crpt.hdl,"__sifr_seed_cfb_decode");
  *(FARPROC*)&wnd._crpt.__sifr_seed_ofb_encode  = GetProcAddress(wnd._crpt.hdl,"__sifr_seed_ofb_encode");
  *(FARPROC*)&wnd._crpt.__sifr_seed_ofb_decode  = GetProcAddress(wnd._crpt.hdl,"__sifr_seed_ofb_decode");
  *(FARPROC*)&wnd._crpt.__sifr_seed_ctr_encode  = GetProcAddress(wnd._crpt.hdl,"__sifr_seed_ctr_encode");
  *(FARPROC*)&wnd._crpt.__sifr_seed_ctr_decode  = GetProcAddress(wnd._crpt.hdl,"__sifr_seed_ctr_decode");

  *(FARPROC*)&wnd._crpt.__sifr_hight_ecb_encode  = GetProcAddress(wnd._crpt.hdl,"__sifr_hight_ecb_encode");
  *(FARPROC*)&wnd._crpt.__sifr_hight_ecb_decode  = GetProcAddress(wnd._crpt.hdl,"__sifr_hight_ecb_decode");
  *(FARPROC*)&wnd._crpt.__sifr_hight_cbc_encode  = GetProcAddress(wnd._crpt.hdl,"__sifr_hight_cbc_encode");
  *(FARPROC*)&wnd._crpt.__sifr_hight_cbc_decode  = GetProcAddress(wnd._crpt.hdl,"__sifr_hight_cbc_decode");
  *(FARPROC*)&wnd._crpt.__sifr_hight_cfb_encode  = GetProcAddress(wnd._crpt.hdl,"__sifr_hight_cfb_encode");
  *(FARPROC*)&wnd._crpt.__sifr_hight_cfb_decode  = GetProcAddress(wnd._crpt.hdl,"__sifr_hight_cfb_decode");
  *(FARPROC*)&wnd._crpt.__sifr_hight_ofb_encode  = GetProcAddress(wnd._crpt.hdl,"__sifr_hight_ofb_encode");
  *(FARPROC*)&wnd._crpt.__sifr_hight_ofb_decode  = GetProcAddress(wnd._crpt.hdl,"__sifr_hight_ofb_decode");
  *(FARPROC*)&wnd._crpt.__sifr_hight_ctr_encode  = GetProcAddress(wnd._crpt.hdl,"__sifr_hight_ctr_encode");
  *(FARPROC*)&wnd._crpt.__sifr_hight_ctr_decode  = GetProcAddress(wnd._crpt.hdl,"__sifr_hight_ctr_decode");

  *(FARPROC*)&wnd._crpt.__sifr_sha2    = GetProcAddress(wnd._crpt.hdl,"__sifr_sha2");
  *(FARPROC*)&wnd._crpt.__sifr_hmac    = GetProcAddress(wnd._crpt.hdl,"__sifr_hmac");
  *(FARPROC*)&wnd._crpt.__sifr_lsh256_224  = GetProcAddress(wnd._crpt.hdl,"__sifr_lsh256_224");
  *(FARPROC*)&wnd._crpt.__sifr_lsh256_256  = GetProcAddress(wnd._crpt.hdl,"__sifr_lsh256_256");
  *(FARPROC*)&wnd._crpt.__sifr_lsh512_224  = GetProcAddress(wnd._crpt.hdl,"__sifr_lsh512_224");
  *(FARPROC*)&wnd._crpt.__sifr_lsh512_256  = GetProcAddress(wnd._crpt.hdl,"__sifr_lsh512_256");
  *(FARPROC*)&wnd._crpt.__sifr_lsh512_384  = GetProcAddress(wnd._crpt.hdl,"__sifr_lsh512_384");
  *(FARPROC*)&wnd._crpt.__sifr_lsh512_512  = GetProcAddress(wnd._crpt.hdl,"__sifr_lsh512_512");
  #endif



  e = wnd._crpt.__sifr_initia(&wnd._crpt.h, "gLmp3mWd+2BnbK97Sk7H8wTKnTqVR692UCgPNrcpXCE=", SIFR_MODULE);
  LVLog(wnd.item[_IDC_LIST1].hwnd, wnd.item[_IDC_CHECK1].hwnd, 2000, &wnd.log, "log", "sifr", "sifr load : %s",e>0?"SUCCESS":"FAIL");
}


void* fxWM_INITDIALOG(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int32_t _index = 0;
  int8_t _top_title[256] = {0};
  wchar_t wcs[1024] = {0};
  int32_t e = 0;

  wnd.hdlg = hwnd;

  for ( _index=_IDC_EDIT1 ; _index<=_IDC_EDIT21 ; _index++ )
  {
    wnd.item[_index].hwnd = GetDlgItem(hwnd, IDC_EDIT1+_index);
  }
  for ( _index=0 ; _index<=(_IDC_SPIN21-_IDC_SPIN1) ; _index++ )
  {
    wnd.item[_IDC_SPIN1+_index].hwnd = GetDlgItem(hwnd, IDC_SPIN1+_index);
  }

  for ( _index=_IDC_EDIT1 ; _index<=_IDC_EDIT21 ; _index++ )
  {
    wnd.item[_index].hlink = &wnd.item[_IDC_SPIN1+_index].hwnd;
    wnd.item[_IDC_SPIN1+_index].hlink = &wnd.item[_index].hwnd;
  }


  wnd.item[_IDC_LIST1].hwnd = GetDlgItem(hwnd, IDC_LIST1);
  wnd.item[_IDC_CHECK1].hwnd = GetDlgItem(hwnd, IDC_CHECK1);

  //wnd.item[_IDC_BUTTON1].font[1] = baseFont(24);


  SetText(wnd.item[_IDC_EDIT1].hwnd, "00000001", strlen("00000001"));
  SetText(wnd.item[_IDC_EDIT2].hwnd, "00000001", strlen("00000001"));
  SetText(wnd.item[_IDC_EDIT3].hwnd, "10", strlen("XX"));
  SetText(wnd.item[_IDC_EDIT4].hwnd, "0", strlen("X")); // 0 ~ 65535
  SetText(wnd.item[_IDC_EDIT5].hwnd, "0", strlen("X")); // 0 ~ 65535
  SetText(wnd.item[_IDC_EDIT6].hwnd, "0", strlen("X")); // 00 ~ FF
  SetText(wnd.item[_IDC_EDIT7].hwnd, "0", strlen("X")); // 0 ~ 65535
  SetText(wnd.item[_IDC_EDIT8].hwnd, "0", strlen("X")); // 0 ~ 65535


  SetText(wnd.item[_IDC_EDIT9].hwnd, "0", strlen("X")); // 00(+), 11(-) mV
  SetText(wnd.item[_IDC_EDIT10].hwnd, "0", strlen("X")); // 00(+), 11(-) mA
  SetText(wnd.item[_IDC_EDIT11].hwnd, "0", strlen("X")); // Temp
  SetText(wnd.item[_IDC_EDIT12].hwnd, "0", strlen("X")); // Ah
  SetText(wnd.item[_IDC_EDIT13].hwnd, "0", strlen("X")); // Wh
  SetText(wnd.item[_IDC_EDIT14].hwnd, "0", strlen("X")); // W
  SetText(wnd.item[_IDC_EDIT15].hwnd, "0", strlen("X")); // R
  SetText(wnd.item[_IDC_EDIT16].hwnd, "0", strlen("X")); // Step Time
  SetText(wnd.item[_IDC_EDIT17].hwnd, "0", strlen("X")); // Alarm
  SetText(wnd.item[_IDC_EDIT18].hwnd, "0", strlen("X")); // 00 ~ FF      Stop Cond Index
  SetText(wnd.item[_IDC_EDIT19].hwnd, "0", strlen("X")); // 0 ~ FFFFFFFF Stop Cond Value
  SetText(wnd.item[_IDC_EDIT20].hwnd, "0", strlen("X")); // 00 ~ FF      Safe Cond Index
  SetText(wnd.item[_IDC_EDIT21].hwnd, "0", strlen("X")); // 0 ~ FFFFFFFF Safe Cond Value


  SendMessage(wnd.item[_IDC_SPIN1].hwnd, SBM_SETPOS, 0, 7);
  SendMessage(wnd.item[_IDC_SPIN2].hwnd, SBM_SETPOS, 0, 7);

  SendMessage(wnd.item[_IDC_CHECK1].hwnd, BM_SETCHECK, BST_CHECKED, 0);

  InitListView(wnd.item[_IDC_LIST1].hwnd);

  tcpd();

  sifr();

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
      //ontray_command(hwnd, msg, wparam, lparam);
      break;
  }

  return (void*)TRUE;
}



void* fxWM_VSCROLL(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int32_t idx = 0;
  uint32_t pos = 0;
  //LVLog(wnd.item[_IDC_LIST1].hwnd, wnd.item[_IDC_CHECK1].hwnd, 2000, &wnd.log, "log", "vscroll", "%d:%d - %x:%x", HIWORD(wparam),LOWORD(wparam),wnd.item[_IDC_SPIN1].hwnd, lparam);

  switch( LOWORD(wparam) )
  {
      case SB_ENDSCROLL :
        idx = getSpinHandleIndex((HWND)lparam);
        pos = HIWORD(wparam);
        if ( pos > wnd.item[idx].pos ) spin_value(idx-_IDC_SPIN1, 'D');
        else spin_value(idx-_IDC_SPIN1, 'U');
        wnd.item[idx].pos = pos;
        break;
  }

  //switch(LOWORD(lparam))
  //{
  //  case IDC_SPIN1:
  //    break;


  //  case IDC_SPIN2:
  //    
  //    break;


  //  case IDC_SPIN3:
  //    
  //    break;

  //  default:
  //    //ontray_command(hwnd, msg, wparam, lparam);
  //    break;
  //}

  return (void*)TRUE;
}

void* fxWM_NOTIFY(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  //LVLog(wnd.item[_IDC_LIST1].hwnd, wnd.item[_IDC_CHECK1].hwnd, 2000, &wnd.log, "log", "vscroll", "%d:%d - %d:%d", HIWORD(wparam),LOWORD(wparam),HIWORD(lparam),LOWORD(lparam));

  //int32_t idx = SendMessage(wnd.tab, TCM_GETCURSEL, 0, 0);
  //int32_t i=0;

  //for ( i=0 ; i<_TAB_MAX ; i++ )
  //{
  //  ShowWindow(wnd.item[i].hwnd, (idx==i)?SW_SHOW:SW_HIDE);
  //}
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

    case WM_VSCROLL:
      r = (BOOL)fxWM_VSCROLL(hwnd, msg, wparam, lparam);
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
      //return ontray_proc(hwnd, msg, wparam, lparam);
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
