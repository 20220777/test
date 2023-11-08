#include "resource.h"
#include "wDraw.h"

static wDraw* gp;

/*******************************************************************************
 * DrawSerial
 *******************************************************************************/
int32_t DrawSerialStatus(void* t,void* fd, int8_t* arg1,int32_t arg2, int32_t type, void* o)
{
  int32_t e = 0;
  int32_t r = 0;
  int8_t port[32];
  int8_t baud[32];
  int8_t dbit[4];
  int8_t sbit[4];
  int8_t pbit[4];
  //if ( type == 0x0C )  //// Open Complete
  //{
  //  GetText(gp->item[EDIT_DRAW_SPORT], port, 32);
  //  GetText(gp->item[EDIT_DRAW_BAUD], baud, 32);
  //  GetText(gp->item[EDIT_DRAW_DBIT], dbit, 4);
  //  GetText(gp->item[EDIT_DRAW_SBIT], sbit, 4);
  //  GetText(gp->item[EDIT_DRAW_PBIT], pbit, 4);

  //  InsertLVText(gp->item[LIST_DRAW_READ], 0, "Serial Open : %s %s(bps) %s %s %s", port, baud, dbit, sbit, pbit);
  //  LogWrite(gp->item[CHECK_DRAW_SERIAL_LOG], &gp->log, "draw", "serial", "DrawSerial Open : %s %s(bps) %s %s %s", port, baud, dbit, sbit, pbit);
  //}

  //if ( type == 0xCC )  //// Close Complete
  //{
  //  GetText(gp->item[EDIT_DRAW_SPORT], port, 32);
  //  GetText(gp->item[EDIT_DRAW_BAUD], baud, 32);
  //  GetText(gp->item[EDIT_DRAW_DBIT], dbit, 4);
  //  GetText(gp->item[EDIT_DRAW_SBIT], sbit, 4);
  //  GetText(gp->item[EDIT_DRAW_PBIT], pbit, 4);

  //  InsertLVText(gp->item[LIST_DRAW_READ], 0, "Serial Close : %s %s(bps) %s %s %s", port, baud, dbit, sbit, pbit);
  //  LogWrite(gp->item[CHECK_DRAW_SERIAL_LOG], &gp->log, "draw", "serial", "DrawSerial Close : %s %s(bps) %s %s %s", port, baud, dbit, sbit, pbit);
  //}

  //if ( type == 0x1B )  //// Input Before
  //{
  //}
  //if ( type == 0x1A )  //// Input After
  //{
  //}

  //if ( type == 0x0B )  //// Output Before
  //{
  //}
  //if ( type == 0x0A )  //// Output After
  //{
  //}

  return e;
}

int32_t DrawSerialReadAck(void* t,void* fd, int8_t* arg1,int32_t arg2,int32_t type, void* o)
{
  int8_t st[32];
  int8_t vbuf[1024];

  int8_t b[1024];
  int32_t e = 0;
  int32_t w = 0;
  int32_t i = 0;
  float x, y;

  return 0;

}



int32_t DrawSerialRead(void* t,void* fd, int8_t* arg1,int32_t arg2,int32_t type, void* o)
{
  int8_t st[32];
  int8_t rbuf[1024];
  int8_t vbuf[1024];
  int32_t e = 0;
  int32_t w = 0;
  int32_t i = 0;


  *(arg1+arg2) = 0;

  //GetComboText(gp->item[COMBO_DRAW_DISPLAY_TYPE_R], st);


  ////if ( (uint8_t)(*arg1) == 0xEA )
  ////{
  ////  gp->srl.sz = 0;
  ////}

  ////gp->srl.rbuf[gp->srl.sz] = *arg1;
  ////if ((gp->srl.sz >=4) && (gp->srl.rbuf[gp->srl.rbuf[2] + 4] == 0x03))
  ////{
  ////  gp->srl.rbuf[gp->srl.rbuf[2] + 4] = 0;
  ////  gp->srl.rbuf[2] = 0;
  ////  e = gp->srl.sz+1;
  ////}
  ////gp->srl.sz++;

  ////if ( e > 0 )
  ////{
  ////  DrawSerialReadAck(t,fd,arg1,arg2,type,o);

  ////  if ( st[0] == 'A' )
  ////  {
  ////    InsertLVText(gp->item[LIST_DRAW_READ], gp->srl.rbuf);
  ////    LogWrite(gp->item[CHECK_DRAW_SERIAL_LOG], &gp->log, "draw", "serial", "%s\r\n", gp->srl.rbuf);

  ////  }
  ////  else
  ////  {
  ////    fprint_raw_buffer(0, gp->srl.rbuf, e, vbuf);
  ////    InsertLVText(gp->item[LIST_DRAW_READ], vbuf);
  ////    LogWrite(gp->item[CHECK_DRAW_SERIAL_LOG], &gp->log, "draw", "serial", "%s\r\n", gp->srl.rbuf);
  ////  }
  ////}
  return 0;
}

void DrawSerialWrite()
{
  int8_t st[32];
  int8_t smsg[1024];
  int8_t sbuf[1024];
  int32_t sz;
  int32_t e = 0;
  int32_t w = 0;
  ////EA 01 01 FF FF 03
  //GetComboText(gp->item[COMBO_DRAW_DISPLAY_TYPE_W], st);

  //sz = GetText(gp->item[EDIT_DRAW_WRITE], smsg, 1024);
  //smsg[sz] = 0;

  //if ( st[0] == 'A' )
  //{
  //  if ( SendMessage(gp->item[CHECK_DRAW_CR], BM_GETCHECK, 0, 0) == BST_CHECKED )
  //  {
  //    sprintf(smsg, "%s\r", smsg);
  //    sz+=1;
  //  }
  //  if ( SendMessage(gp->item[CHECK_DRAW_LF], BM_GETCHECK, 0, 0) == BST_CHECKED )
  //  {
  //    sprintf(smsg, "%s\n", smsg);
  //    sz+=1;
  //  }
  //  //e = (int32_t)WriteFile((HANDLE)gp->srl.fd, smsg, sz, (LPDWORD)&w, 0);
  //}
  //else
  //{
  //  if ( SendMessage(gp->item[CHECK_DRAW_CR], BM_GETCHECK, 0, 0) == BST_CHECKED )
  //  {
  //    sprintf(smsg, "%s 0D", smsg);
  //    sz+=3;
  //  }
  //  if ( SendMessage(gp->item[CHECK_DRAW_LF], BM_GETCHECK, 0, 0) == BST_CHECKED )
  //  {
  //    sprintf(smsg, "%s 0A", smsg);
  //    sz+=3;
  //  }
  //  e = str_to_hex(smsg, sz, ' ', sbuf);
  //  //e = (int32_t)WriteFile((HANDLE)gp->srl.fd, sbuf, e, (LPDWORD)&w, 0);


  //  ////for ( ; ; )
  //  //{
  //  //  int32_t i=0;
  //  //  int8_t b[32];

  //  //  //b[i++] = 0xEA;
  //  //  //b[i++] = 0x01;
  //  //  //b[i++] = 0x01;
  //  //  //b[i++] = 0xFF;
  //  //  //b[i++] = (byte)(~(b[1] + b[2] + b[3]) + 1);
  //  //  //b[i++] = 0x03;
  //  //  //InsertLVText(gp->item[LIST_DRAW_READ], smsg);

  //  //  //e = WriteFile((HANDLE)gp->srl.fd, b, i, &w, 0);

  //  //  //Sleep(100);

  //  //  i = 0;
  //  //  b[i++] = 0xEA;
  //  //  b[i++] = 0x05;
  //  //  b[i++] = 0x00;
  //  //  b[i++] = (byte)(~(b[1] + b[2]) + 1);
  //  //  b[i++] = 0x03;
  //  //  InsertLVText(gp->item[LIST_DRAW_READ], smsg);

  //  //  e = WriteFile((HANDLE)gp->srl.fd, b, i, &w, 0);
  //  //}



  //}

}

int32_t DrawSerialOpen()
{
  int8_t port[32];
  int8_t baud[32];
  int8_t dbit[4];
  int8_t sbit[4];
  int8_t pbit[4];
  int32_t  sz = 1;//MAX_BUF_SZ;

  //GetText(gp->item[EDIT_DRAW_SPORT], port, 32);
  //GetText(gp->item[EDIT_DRAW_BAUD], baud, 32);
  //GetText(gp->item[EDIT_DRAW_DBIT], dbit, 4);
  //GetText(gp->item[EDIT_DRAW_SBIT], sbit, 4);
  //GetText(gp->item[EDIT_DRAW_PBIT], pbit, 4);

  ////gp->srl.m.pfxMTIF[ONSERIALREADEX] = DrawSerialRead;
  ////gp->srl.m.pfxMTIF[ONSERIALSTATUS] = DrawSerialStatus;

  ////memcpy(gp->srl.buf, &sz, sizeof(int32_t));
  ////gp->srl.fd = mtifSerialOpenEx(&gp->srl.m, port, baud, dbit, sbit, pbit, "0", gp->srl.buf, 0, (void*)&tdraw);

  ////return (int32_t)gp->srl.fd;
  return 0;
}

void DrawSerialClose()
{
  //mtifSerialCloseEx(&gp->srl.m, gp->srl.fd, gp->srl.buf);
}
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
/*******************************************************************************/
/*******************************************************************************/
void xdraw_wm_command(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int8_t temp[32];

  //switch(LOWORD(wparam))
  //{
  //  case IDC_BUTTON_DRAW_OPEN_CLOSE:
  //    GetText(gp->item[BUTTON_DRAW_OPEN_CLOSE], temp, 32);
  //    if ( strcmp(temp, STR_OPEN) == 0 )
  //    {
  //      if ( DrawSerialOpen()> 0 )
  //      {
  //        SetText(gp->item[BUTTON_DRAW_OPEN_CLOSE], STR_CLOSE, strlen(STR_CLOSE));
  //        InsertLVText(gp->item[LIST_DRAW_READ], 0, "Serial Open Success");
  //      }
  //      else
  //      {
  //        InsertLVText(gp->item[LIST_DRAW_READ], 0, "Serial Open Fail");
  //      }
  //    }
  //    else
  //    {
  //      SetText(gp->item[BUTTON_DRAW_OPEN_CLOSE], STR_OPEN, strlen(STR_OPEN));
  //      DrawSerialClose();
  //      InsertLVText(gp->item[LIST_DRAW_READ], 0, "Serial Close Success");
  //    }
  //    break;

  //  case IDC_BUTTON_DRAW_WRITE:
  //    DrawSerialWrite();
  //    break;

  //  case IDC_BUTTON_DRAW_CLEAR:
  //    SendMessage(gp->item[LIST_DRAW_READ], LVM_DELETEALLITEMS, 0, 0);
  //    break;



  //  case IDC_CHECK_DRAW_READ_YN:
  //    if ( SendMessage(gp->item[CHECK_DRAW_READ_YN], BM_GETCHECK, 0, 0) == BST_CHECKED )
  //    {
  //      gp->read_lock = 0x01;
  //    }
  //    else
  //    {
  //      gp->read_lock = 0x00;
  //    }

  //    break;

  //}
}





void wDrawStaticPaint(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  gp->hdc_cross = GetDC(gp->item[STATIC_DRAW_AXIS].hwnd);

  gp->hpen = CreatePen(0 ,1, RGB(0xFF,0,0));
  SelectObject(gp->hdc_cross,gp->hpen); 

  MoveToEx(gp->hdc_cross, gp->rct[1].left+WDRAW_AXIS_X_C, gp->rct[1].top, 0);
  LineTo(gp->hdc_cross, gp->rct[1].left+WDRAW_AXIS_X_C, gp->rct[1].top+WDRAW_AXIS_Y_SZ);
  MoveToEx(gp->hdc_cross, gp->rct[1].left, gp->rct[1].top+WDRAW_AXIS_Y_C, 0);
  LineTo(gp->hdc_cross, gp->rct[1].left+WDRAW_AXIS_X_SZ, gp->rct[1].top+WDRAW_AXIS_Y_C);

  DeleteObject(gp->hpen);


  gp->hpen = CreatePen(3 ,1, RGB(0xFF,0xFF,0));
  SelectObject(gp->hdc_cross,gp->hpen); 

  MoveToEx(gp->hdc_cross, gp->rct[1].left+(WDRAW_AXIS_X_C-WDRAW_GUIDE_X_C), gp->rct[1].top+(WDRAW_AXIS_Y_C-WDRAW_GUIDE_Y_C), 0);
    LineTo(gp->hdc_cross, gp->rct[1].left+(WDRAW_AXIS_X_C-WDRAW_GUIDE_X_C), gp->rct[1].top+(WDRAW_AXIS_Y_C+WDRAW_GUIDE_Y_C));
    LineTo(gp->hdc_cross, gp->rct[1].left+(WDRAW_AXIS_X_C+WDRAW_GUIDE_X_C), gp->rct[1].top+(WDRAW_AXIS_Y_C+WDRAW_GUIDE_Y_C));
    LineTo(gp->hdc_cross, gp->rct[1].left+(WDRAW_AXIS_X_C+WDRAW_GUIDE_X_C), gp->rct[1].top+(WDRAW_AXIS_Y_C-WDRAW_GUIDE_Y_C));
    LineTo(gp->hdc_cross, gp->rct[1].left+(WDRAW_AXIS_X_C-WDRAW_GUIDE_X_C), gp->rct[1].top+(WDRAW_AXIS_Y_C-WDRAW_GUIDE_Y_C));

  DeleteObject(gp->hpen);

  ReleaseDC(gp->item[STATIC_DRAW_AXIS].hwnd, gp->hdc_cross);
}

void wDrawCoordPick()
{
  SendMessage(gp->item[EDIT_DRAW_ABS_COORD_PICK].hwnd, WM_SETTEXT, (WPARAM)strlen(gp->strcoord[0]), (LPARAM)gp->strcoord[0]);
  SendMessage(gp->item[EDIT_DRAW_ABS_COORD_PICK2].hwnd, WM_SETTEXT, (WPARAM)strlen(gp->strcoord[1]), (LPARAM)gp->strcoord[1]);
  SendMessage(gp->item[EDIT_DRAW_REL_COORD_PICK].hwnd, WM_SETTEXT, (WPARAM)strlen(gp->strcoord[2]), (LPARAM)gp->strcoord[2]);
  SendMessage(gp->item[EDIT_DRAW_REL_COORD_PICK2].hwnd, WM_SETTEXT, (WPARAM)strlen(gp->strcoord[3]), (LPARAM)gp->strcoord[3]);
}

void wDrawCoordDisplay(int32_t x, int32_t y)
{
  gp->xycoord[0][0] = x;
  gp->xycoord[0][1] = y;
  sprintf(gp->strcoord[0], "(%d, %d),  (%02X, %02X)", gp->xycoord[0][0], gp->xycoord[0][1], (uint8_t)gp->xycoord[0][0], (uint8_t)gp->xycoord[0][1]);
  SendMessage(gp->item[EDIT_DRAW_ABS_COORD].hwnd, WM_SETTEXT, (WPARAM)strlen(gp->strcoord[0]), (LPARAM)gp->strcoord[0]);

  gp->xycoord[1][0] = x - WDRAW_AXIS_X_C;
  gp->xycoord[1][1] = WDRAW_GUIDE_Y_C - (y - ( gp->rct[1].top+(WDRAW_AXIS_Y_C-WDRAW_GUIDE_Y_C) ));
  sprintf(gp->strcoord[1], "(%d, %d),  (%02X, %02X)", gp->xycoord[1][0], gp->xycoord[1][1], (uint8_t)gp->xycoord[1][0], (uint8_t)gp->xycoord[1][1]);
  SendMessage(gp->item[EDIT_DRAW_ABS_COORD2].hwnd, WM_SETTEXT, (WPARAM)strlen(gp->strcoord[1]), (LPARAM)gp->strcoord[1]);

  gp->xycoord[2][0] = x - WDRAW_AXIS_X_C;
  gp->xycoord[2][1] = y - (gp->rct[1].top+(WDRAW_AXIS_Y_C-WDRAW_GUIDE_Y_C));
  sprintf(gp->strcoord[2], "(%d, %d),  (%02X, %02X)", gp->xycoord[2][0], gp->xycoord[2][1], (uint8_t)gp->xycoord[2][0], (uint8_t)gp->xycoord[2][1]);
  SendMessage(gp->item[EDIT_DRAW_REL_COORD].hwnd, WM_SETTEXT, (WPARAM)strlen(gp->strcoord[2]), (LPARAM)gp->strcoord[2]);

  gp->xycoord[3][0] = x - (gp->rct[1].left+(WDRAW_AXIS_X_C-WDRAW_GUIDE_X_C));
  gp->xycoord[3][1] = y - (gp->rct[1].top+(WDRAW_AXIS_Y_C-WDRAW_GUIDE_Y_C));
  sprintf(gp->strcoord[3], "(%d, %d),  (%02X, %02X)", gp->xycoord[3][0], gp->xycoord[3][1], (uint8_t)gp->xycoord[3][0], (uint8_t)gp->xycoord[3][1]);
  SendMessage(gp->item[EDIT_DRAW_REL_COORD2].hwnd, WM_SETTEXT, (WPARAM)strlen(gp->strcoord[3]), (LPARAM)gp->strcoord[3]);
}

void wDrawCoord(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  gp->coord[0] = LOWORD(lparam);
  gp->coord[1] = HIWORD(lparam);
  wDrawCoordDisplay(gp->coord[0], gp->coord[1]);
}

////
////void wDraw_abs_coord(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
////{
////  int32_t x;
////  int32_t y;
////  int8_t tmp[32];
////
////  x = LOWORD(lparam);
////  y = HIWORD(lparam);
////  sprintf(tmp, "(%d, %d),  (%02X, %02X)", x, y, (uint8_t)x, (uint8_t)y);
////  SendMessage(gp->item[EDIT_DRAW_ABS_COORD], WM_SETTEXT, (WPARAM)strlen(tmp), (LPARAM)tmp);
////}
////void wDraw_abs_coord_pick(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
////{
////  int32_t x;
////  int32_t y;
////  int8_t tmp[32];
////
////  x = LOWORD(lparam);
////  y = HIWORD(lparam);
////  sprintf(tmp, "(%d, %d),  (%02X, %02X)", x, y, (uint8_t)x, (uint8_t)y);
////  SendMessage(gp->item[EDIT_DRAW_ABS_COORD_PICK], WM_SETTEXT, (WPARAM)strlen(tmp), (LPARAM)tmp);
////}
////void wDraw_rel_coord(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
////{
////  int32_t x;
////  int32_t y;
////  int8_t tmp[32];
////
////  x = LOWORD(lparam) - XDRAW_AXIS_X_C;
////  y = XDRAW_AXIS_Y_SZ - ((HIWORD(lparam) + XDRAW_AXIS_Y_C));
////  sprintf(tmp, "(%d, %d),  (%02X, %02X)", x, y, (uint8_t)x, (uint8_t)y);
////  SendMessage(gp->item[EDIT_DRAW_REL_COORD], WM_SETTEXT, (WPARAM)strlen(tmp), (LPARAM)tmp);
////}
////void wDraw_rel_coord_pick(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
////{
////  int32_t x;
////  int32_t y;
////  int8_t tmp[32];
////
////  x = LOWORD(lparam) - XDRAW_AXIS_X_C;
////  y = XDRAW_AXIS_Y_SZ - ((HIWORD(lparam) + XDRAW_AXIS_Y_C));
////  sprintf(tmp, "(%d, %d),  (%02X, %02X)", x, y, (uint8_t)x, (uint8_t)y);
////  SendMessage(gp->item[EDIT_DRAW_REL_COORD_PICK], WM_SETTEXT, (WPARAM)strlen(tmp), (LPARAM)tmp);
////}
////void wDraw_rel_coord2(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
////{
////  int32_t x;
////  int32_t y;
////  int8_t tmp[32];
////
////  x = LOWORD(lparam) - (gp->rct[1].left+(XDRAW_AXIS_X_C-XDRAW_GUIDE_X_C));
////  y = HIWORD(lparam) - (gp->rct[1].top+(XDRAW_AXIS_Y_C-XDRAW_GUIDE_Y_C));
////  sprintf(tmp, "(%d, %d),  (%02X, %02X)", x, y, (uint8_t)x, (uint8_t)y);
////  SendMessage(gp->item[EDIT_DRAW_REL_COORD2], WM_SETTEXT, (WPARAM)strlen(tmp), (LPARAM)tmp);
////}
////void wDraw_rel_coord_pick2(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
////{
////  int32_t x;
////  int32_t y;
////  int8_t tmp[32];
////
////  x = LOWORD(lparam) - (gp->rct[1].left+(XDRAW_AXIS_X_C-XDRAW_GUIDE_X_C));
////  y = HIWORD(lparam) - (gp->rct[1].top+(XDRAW_AXIS_Y_C-XDRAW_GUIDE_Y_C));
////  sprintf(tmp, "(%d, %d),  (%02X, %02X)", x, y, (uint8_t)x, (uint8_t)y);
////  SendMessage(gp->item[EDIT_DRAW_REL_COORD_PICK2], WM_SETTEXT, (WPARAM)strlen(tmp), (LPARAM)tmp);
////}


LRESULT CALLBACK wDrawStaticCallback(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int32_t hitCode = 0; 
  POINT mpt;
  RECT rct;

  HBRUSH hbr;
  HDC hdc;
  memset(&hbr, 0, sizeof(HBRUSH));

  CallWindowProc(gp->oitem[STATIC_DRAW_AXIS], hwnd, msg, wparam, lparam);
  switch(msg)
  {
    case WM_NCHITTEST:
      hitCode = DefWindowProc(hwnd, msg, wparam, lparam);
      if ( hitCode == HTCLIENT )
      {
        //gp->hcursor = LoadCursor(0, IDC_CROSS);
        return hitCode;
      }
      //gp->hcursor = LoadCursor(0, IDC_ARROW);
  
      break;

    case WM_LBUTTONDOWN:
      wDrawCoordPick();
      break;

    case WM_MOUSEMOVE:
      wDrawCoord(hwnd, msg, wparam, lparam);
      break;

    case WM_PAINT:
      wDrawStaticPaint(hwnd, msg, wparam, lparam);
      break;

    default:
      break;
  }
  return TRUE;//CallWindowProc(gp->oitem[STATIC_DRAW_AXIS], hwnd, msg, wparam, lparam);
}

void* wDrawDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  HDC hdc;
  switch(msg)
  {
    case WM_COMMAND:
      //xdraw_wm_command(hwnd, msg, wparam, lparam);
      break;

    case WM_CTLCOLORSTATIC:
      if (
           ( (HWND)lparam == gp->item[EDIT_DRAW_ABS_COORD].hwnd ) || 
           ( (HWND)lparam == gp->item[EDIT_DRAW_ABS_COORD_PICK].hwnd ) ||
           ( (HWND)lparam == gp->item[EDIT_DRAW_ABS_COORD2].hwnd ) || 
           ( (HWND)lparam == gp->item[EDIT_DRAW_ABS_COORD_PICK2].hwnd ) ||
           ( (HWND)lparam == gp->item[EDIT_DRAW_REL_COORD].hwnd ) || 
           ( (HWND)lparam == gp->item[EDIT_DRAW_REL_COORD_PICK].hwnd ) ||
           ( (HWND)lparam == gp->item[EDIT_DRAW_REL_COORD2].hwnd ) || 
           ( (HWND)lparam == gp->item[EDIT_DRAW_REL_COORD_PICK2].hwnd )
       )
      {
        hdc = (HDC)wparam;
        SetTextColor(hdc, RGB(255,255,0));
        SetBkColor(hdc, RGB(0,0,0));
        return (void*)gp->hbr;
      }
      break;


    default:
      break;
  }

  return 0;
}



void* wDrawInit(HWND hwnd, wDraw* p)
{
  int32_t e;

  gp = p;

  gp->hbr = CreateSolidBrush(RGB(0,0,0));

  gp->item[EDIT_DRAW_ABS_COORD].hwnd = GetDlgItem(hwnd, IDC_EDIT_DRAW_ABS_COORD);
  gp->item[EDIT_DRAW_ABS_COORD_PICK].hwnd = GetDlgItem(hwnd, IDC_EDIT_DRAW_ABS_COORD_PICK);
  gp->item[EDIT_DRAW_ABS_COORD2].hwnd = GetDlgItem(hwnd, IDC_EDIT_DRAW_ABS_COORD2);
  gp->item[EDIT_DRAW_ABS_COORD_PICK2].hwnd = GetDlgItem(hwnd, IDC_EDIT_DRAW_ABS_COORD_PICK2);
  gp->item[EDIT_DRAW_REL_COORD].hwnd = GetDlgItem(hwnd, IDC_EDIT_DRAW_REL_COORD);
  gp->item[EDIT_DRAW_REL_COORD_PICK].hwnd = GetDlgItem(hwnd, IDC_EDIT_DRAW_REL_COORD_PICK);
  gp->item[EDIT_DRAW_REL_COORD2].hwnd = GetDlgItem(hwnd, IDC_EDIT_DRAW_REL_COORD2);
  gp->item[EDIT_DRAW_REL_COORD_PICK2].hwnd = GetDlgItem(hwnd, IDC_EDIT_DRAW_REL_COORD_PICK2);
  gp->item[STATIC_DRAW_AXIS].hwnd = GetDlgItem(hwnd, IDC_STATIC_DRAW_AXIS);

  gp->item[EDIT_DRAW_SPORT].hwnd = GetDlgItem(hwnd, IDC_EDIT_DRAW_SPORT);
  gp->item[EDIT_DRAW_BAUD].hwnd = GetDlgItem(hwnd, IDC_EDIT_DRAW_BAUD);
  gp->item[EDIT_DRAW_DBIT].hwnd = GetDlgItem(hwnd, IDC_EDIT_DRAW_DBIT);
  gp->item[EDIT_DRAW_SBIT].hwnd = GetDlgItem(hwnd, IDC_EDIT_DRAW_SBIT);
  gp->item[EDIT_DRAW_PBIT].hwnd = GetDlgItem(hwnd, IDC_EDIT_DRAW_PBIT);
  gp->item[BUTTON_DRAW_OPEN_CLOSE].hwnd = GetDlgItem(hwnd, IDC_BUTTON_DRAW_OPEN_CLOSE);
  gp->item[COMBO_DRAW_DISPLAY_TYPE_R].hwnd = GetDlgItem(hwnd, IDC_COMBO_DRAW_DISPLAY_TYPE_R);
  gp->item[COMBO_DRAW_DISPLAY_TYPE_W].hwnd = GetDlgItem(hwnd, IDC_COMBO_DRAW_DISPLAY_TYPE_W);
  gp->item[EDIT_DRAW_WRITE].hwnd = GetDlgItem(hwnd, IDC_EDIT_DRAW_WRITE);
  gp->item[BUTTON_DRAW_WRITE].hwnd = GetDlgItem(hwnd, IDC_BUTTON_DRAW_WRITE);
  gp->item[CHECK_DRAW_CR].hwnd = GetDlgItem(hwnd, IDC_CHECK_DRAW_CR);
  gp->item[CHECK_DRAW_LF].hwnd = GetDlgItem(hwnd, IDC_CHECK_DRAW_LF);
  gp->item[CHECK_DRAW_SERIAL_LOG].hwnd = GetDlgItem(hwnd, IDC_CHECK_DRAW_SERIAL_LOG);
  gp->item[CHECK_DRAW_SERIAL_ECHO].hwnd = GetDlgItem(hwnd, IDC_CHECK_DRAW_SERIAL_ECHO);
  gp->item[LIST_DRAW_READ].hwnd = GetDlgItem(hwnd, IDC_LIST_DRAW_READ);
  gp->item[BUTTON_DRAW_CLEAR].hwnd = GetDlgItem(hwnd, IDC_BUTTON_DRAW_CLEAR);
  gp->item[CHECK_DRAW_READ_YN].hwnd = GetDlgItem(hwnd, IDC_CHECK_DRAW_READ_YN);


  ResetText(gp->item[EDIT_DRAW_SPORT].hwnd, "COM1");
  ResetText(gp->item[EDIT_DRAW_BAUD].hwnd, "115200");
  ResetText(gp->item[EDIT_DRAW_DBIT].hwnd, "8");
  ResetText(gp->item[EDIT_DRAW_SBIT].hwnd, "1");
  ResetText(gp->item[EDIT_DRAW_PBIT].hwnd, "0");

  SetText(gp->item[BUTTON_DRAW_OPEN_CLOSE].hwnd, "OPEN", strlen("OPEN"));
  SetText(gp->item[BUTTON_DRAW_OPEN_CLOSE].hwnd, "OPEN", strlen("OPEN"));


	SendMessage(gp->item[COMBO_DRAW_DISPLAY_TYPE_R].hwnd, CB_ADDSTRING, 0, (LPARAM)"ASCII");
	SendMessage(gp->item[COMBO_DRAW_DISPLAY_TYPE_R].hwnd, CB_ADDSTRING, 0, (LPARAM)"HEX");
  SendMessage(gp->item[COMBO_DRAW_DISPLAY_TYPE_R].hwnd, CB_SETCURSEL, 1, 0 );

	SendMessage(gp->item[COMBO_DRAW_DISPLAY_TYPE_W].hwnd, CB_ADDSTRING, 0, (LPARAM)"ASCII");
	SendMessage(gp->item[COMBO_DRAW_DISPLAY_TYPE_W].hwnd, CB_ADDSTRING, 0, (LPARAM)"HEX");
  SendMessage(gp->item[COMBO_DRAW_DISPLAY_TYPE_W].hwnd, CB_SETCURSEL, 1, 0 );


  GetClientRect(gp->item[STATIC_DRAW_AXIS].hwnd, &gp->rct[0]);

  GetWindowRect(hwnd, &gp->rct[1]);
  ScreenToClient(hwnd, (LPPOINT)&gp->rct[1]);

  gp->oitem[STATIC_DRAW_AXIS] = (WNDPROC)SetWindowLongPtr(gp->item[STATIC_DRAW_AXIS].hwnd, GWLP_WNDPROC, (LONG)wDrawStaticCallback);

  InitListView(gp->item[LIST_DRAW_READ].hwnd);

  return 0;
}

