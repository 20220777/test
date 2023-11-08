#include "wdrawwnd.h"
#include "resource.h"

static wDrawWnd* gp;



/*******************************************************************************
 * DrawSerial
 *******************************************************************************/
int DrawSerialStatus(void* t,void* fd, char* arg1,int arg2, int type, void* o)
{
  int e = 0;
  int r = 0;
  char port[32];
  char baud[32];
  char dbit[4];
  char sbit[4];
  char pbit[4];
  if ( type == 0x0C )  //// Open Complete
  {
    GetText(gp->hitem[EDIT_DRAW_SPORT], port, 32);
    GetText(gp->hitem[EDIT_DRAW_BAUD], baud, 32);
    GetText(gp->hitem[EDIT_DRAW_DBIT], dbit, 4);
    GetText(gp->hitem[EDIT_DRAW_SBIT], sbit, 4);
    GetText(gp->hitem[EDIT_DRAW_PBIT], pbit, 4);

    InsertLVText(gp->hitem[LIST_DRAW_READ], 0, "Serial Open : %s %s(bps) %s %s %s", port, baud, dbit, sbit, pbit);
    LogWrite(gp->hitem[CHECK_DRAW_SERIAL_LOG], &gp->log, "draw", "serial", "DrawSerial Open : %s %s(bps) %s %s %s", port, baud, dbit, sbit, pbit);
  }

  if ( type == 0xCC )  //// Close Complete
  {
    GetText(gp->hitem[EDIT_DRAW_SPORT], port, 32);
    GetText(gp->hitem[EDIT_DRAW_BAUD], baud, 32);
    GetText(gp->hitem[EDIT_DRAW_DBIT], dbit, 4);
    GetText(gp->hitem[EDIT_DRAW_SBIT], sbit, 4);
    GetText(gp->hitem[EDIT_DRAW_PBIT], pbit, 4);

    InsertLVText(gp->hitem[LIST_DRAW_READ], 0, "Serial Close : %s %s(bps) %s %s %s", port, baud, dbit, sbit, pbit);
    LogWrite(gp->hitem[CHECK_DRAW_SERIAL_LOG], &gp->log, "draw", "serial", "DrawSerial Close : %s %s(bps) %s %s %s", port, baud, dbit, sbit, pbit);
  }

  if ( type == 0x1B )  //// Input Before
  {
  }
  if ( type == 0x1A )  //// Input After
  {
  }

  if ( type == 0x0B )  //// Output Before
  {
  }
  if ( type == 0x0A )  //// Output After
  {
  }

  return e;
}

int DrawSerialReadAck(void* t,void* fd, char* arg1,int arg2,int type, void* o)
{
  char st[32];
  char vbuf[1024];

  char b[1024];
  int e = 0;
  int w = 0;
  int i = 0;
  float x, y;

//  if ( gp->srl.rbuf[1] == 0x01 )
//  {
//    b[i++] = 0xEA;
//    b[i++] = 0x01;
//    b[i++] = 0x01;
//    b[i++] = 0x00;
//    b[i++] = (byte)(~(b[1] + b[2] + b[3]) + 1);
//    b[i++] = 0x03;
//    e = (int)WriteFile((HANDLE)gp->srl.fd, b, i, (LPDWORD)&w, 0);
//  }
//  else
//  if ( gp->srl.rbuf[1] == 0x05 )
//  {
//    b[i++] = 0xEA;
//    b[i++] = 0x05;
//    b[i++] = 0x05;
//    b[i++] = 0x01;
//    b[i++] = 0x00;
//
//    x = XDRAW_GUIDE_X_C-gp->xycoord[3][0];
//    y = XDRAW_GUIDE_Y_C-gp->xycoord[3][1];
//
//    //if ( (gp->xycoord[1][0]>=0) && (gp->xycoord[1][1]>=0) )
//    //{
//    //  x = XDRAW_GUIDE_X_C-gp->xycoord[2][0];
//    //  y = XDRAW_GUIDE_Y_C-gp->xycoord[2][1];
//    //}
//    //else
//    //if ( (gp->xycoord[1][0]<=0) && (gp->xycoord[1][1]>=0) )
//    //{
//    //  x = XDRAW_GUIDE_X_C-gp->xycoord[2][0];
//    //  y = XDRAW_GUIDE_Y_C-gp->xycoord[2][1];
//    //}
//    //else
//    //if ( (gp->xycoord[1][0]<=0) && (gp->xycoord[1][1]<=0) )
//    //{
//    //  x = XDRAW_GUIDE_X_C-gp->xycoord[2][0];
//    //  y = XDRAW_GUIDE_Y_C-gp->xycoord[2][1];
//    //}
//    //else
//    //if ( (gp->xycoord[1][0]>=0) && (gp->xycoord[1][1]<=0) )
//    //{
//    //  x = XDRAW_GUIDE_X_C-gp->xycoord[2][0];
//    //  y = XDRAW_GUIDE_Y_C-gp->xycoord[2][1];
//    //}
//    b[i++] = (unsigned char)x;
//    b[i++] = (unsigned char)y;
//    b[i++] = 0x00;
//    b[i++] = 0x00;
////    b[i++] = (byte)(~(b[1] + b[2] + b[3]) + 1);
//    b[i++] = 0x03;
//    e = (int)WriteFile((HANDLE)gp->srl.fd, b, i, (LPDWORD)&w, 0);
//  }
//
//  GetComboText(gp->hitem[COMBO_DRAW_DISPLAY_TYPE_R], st);
//
//  if ( st[0] == 'A' )
//  {
//    InsertLVText(gp->hitem[LIST_DRAW_READ], b);
//    LogWrite(gp->hitem[CHECK_DRAW_SERIAL_LOG], &gp->log, "draw", "serial", "%s\r\n", b);
//
//  }
//  else
//  {
//    fprint_raw_buffer(0, b, i, vbuf);
//    InsertLVText(gp->hitem[LIST_DRAW_READ], vbuf);
//    LogWrite(gp->hitem[CHECK_DRAW_SERIAL_LOG], &gp->log, "draw", "serial", "%s\r\n", b);
//  }

  return 0;

}



int DrawSerialRead(void* t,void* fd, char* arg1,int arg2,int type, void* o)
{
  char st[32];
  char rbuf[1024];
  char vbuf[1024];
  int e = 0;
  int w = 0;
  int i = 0;

  //if ( gp->read_lock ) return 0;

  *(arg1+arg2) = 0;

  GetComboText(gp->hitem[COMBO_DRAW_DISPLAY_TYPE_R], st);


  //if ( (unsigned char)(*arg1) == 0xEA )
  //{
  //  gp->srl.sz = 0;
  //}

  //gp->srl.rbuf[gp->srl.sz] = *arg1;
  //if ((gp->srl.sz >=4) && (gp->srl.rbuf[gp->srl.rbuf[2] + 4] == 0x03))
  //{
  //  gp->srl.rbuf[gp->srl.rbuf[2] + 4] = 0;
  //  gp->srl.rbuf[2] = 0;
  //  e = gp->srl.sz+1;
  //}
  //gp->srl.sz++;

  //if ( e > 0 )
  //{
  //  DrawSerialReadAck(t,fd,arg1,arg2,type,o);

  //  if ( st[0] == 'A' )
  //  {
  //    InsertLVText(gp->hitem[LIST_DRAW_READ], gp->srl.rbuf);
  //    LogWrite(gp->hitem[CHECK_DRAW_SERIAL_LOG], &gp->log, "draw", "serial", "%s\r\n", gp->srl.rbuf);

  //  }
  //  else
  //  {
  //    fprint_raw_buffer(0, gp->srl.rbuf, e, vbuf);
  //    InsertLVText(gp->hitem[LIST_DRAW_READ], vbuf);
  //    LogWrite(gp->hitem[CHECK_DRAW_SERIAL_LOG], &gp->log, "draw", "serial", "%s\r\n", gp->srl.rbuf);
  //  }
  //}
  return 0;
}

void DrawSerialWrite()
{
  char st[32];
  char smsg[1024];
  char sbuf[1024];
  int sz;
  int e = 0;
  int w = 0;
  //EA 01 01 FF FF 03
  GetComboText(gp->hitem[COMBO_DRAW_DISPLAY_TYPE_W], st);

  sz = GetText(gp->hitem[EDIT_DRAW_WRITE], smsg, 1024);
  smsg[sz] = 0;

  if ( st[0] == 'A' )
  {
    if ( SendMessage(gp->hitem[CHECK_DRAW_CR], BM_GETCHECK, 0, 0) == BST_CHECKED )
    {
      sprintf(smsg, "%s\r", smsg);
      sz+=1;
    }
    if ( SendMessage(gp->hitem[CHECK_DRAW_LF], BM_GETCHECK, 0, 0) == BST_CHECKED )
    {
      sprintf(smsg, "%s\n", smsg);
      sz+=1;
    }
    //e = (int)WriteFile((HANDLE)gp->srl.fd, smsg, sz, (LPDWORD)&w, 0);
  }
  else
  {
    if ( SendMessage(gp->hitem[CHECK_DRAW_CR], BM_GETCHECK, 0, 0) == BST_CHECKED )
    {
      sprintf(smsg, "%s 0D", smsg);
      sz+=3;
    }
    if ( SendMessage(gp->hitem[CHECK_DRAW_LF], BM_GETCHECK, 0, 0) == BST_CHECKED )
    {
      sprintf(smsg, "%s 0A", smsg);
      sz+=3;
    }
    e = str_to_hex(smsg, sz, ' ', sbuf);
    //e = (int)WriteFile((HANDLE)gp->srl.fd, sbuf, e, (LPDWORD)&w, 0);


    ////for ( ; ; )
    //{
    //  int i=0;
    //  char b[32];

    //  //b[i++] = 0xEA;
    //  //b[i++] = 0x01;
    //  //b[i++] = 0x01;
    //  //b[i++] = 0xFF;
    //  //b[i++] = (byte)(~(b[1] + b[2] + b[3]) + 1);
    //  //b[i++] = 0x03;
    //  //InsertLVText(gp->hitem[LIST_DRAW_READ], smsg);

    //  //e = WriteFile((HANDLE)gp->srl.fd, b, i, &w, 0);

    //  //Sleep(100);

    //  i = 0;
    //  b[i++] = 0xEA;
    //  b[i++] = 0x05;
    //  b[i++] = 0x00;
    //  b[i++] = (byte)(~(b[1] + b[2]) + 1);
    //  b[i++] = 0x03;
    //  InsertLVText(gp->hitem[LIST_DRAW_READ], smsg);

    //  e = WriteFile((HANDLE)gp->srl.fd, b, i, &w, 0);
    //}



  }

}

int DrawSerialOpen()
{
  char port[32];
  char baud[32];
  char dbit[4];
  char sbit[4];
  char pbit[4];
  int  sz = 1;//MAX_BUF_SZ;

  GetText(gp->hitem[EDIT_DRAW_SPORT], port, 32);
  GetText(gp->hitem[EDIT_DRAW_BAUD], baud, 32);
  GetText(gp->hitem[EDIT_DRAW_DBIT], dbit, 4);
  GetText(gp->hitem[EDIT_DRAW_SBIT], sbit, 4);
  GetText(gp->hitem[EDIT_DRAW_PBIT], pbit, 4);

  //gp->srl.m.pfxMTIF[ONSERIALREADEX] = DrawSerialRead;
  //gp->srl.m.pfxMTIF[ONSERIALSTATUS] = DrawSerialStatus;

  //memcpy(gp->srl.buf, &sz, sizeof(int));
  //gp->srl.fd = mtifSerialOpenEx(&gp->srl.m, port, baud, dbit, sbit, pbit, "0", gp->srl.buf, 0, (void*)&tdraw);

  //return (int)gp->srl.fd;
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
  char temp[32];

  switch(LOWORD(wparam))
  {
    case IDC_BUTTON_DRAW_OPEN_CLOSE:
      GetText(gp->hitem[BUTTON_DRAW_OPEN_CLOSE], temp, 32);
      if ( strcmp(temp, STR_OPEN) == 0 )
      {
        if ( DrawSerialOpen()> 0 )
        {
          SetText(gp->hitem[BUTTON_DRAW_OPEN_CLOSE], STR_CLOSE, strlen(STR_CLOSE));
          InsertLVText(gp->hitem[LIST_DRAW_READ], 0, "Serial Open Success");
        }
        else
        {
          InsertLVText(gp->hitem[LIST_DRAW_READ], 0, "Serial Open Fail");
        }
      }
      else
      {
        SetText(gp->hitem[BUTTON_DRAW_OPEN_CLOSE], STR_OPEN, strlen(STR_OPEN));
        DrawSerialClose();
        InsertLVText(gp->hitem[LIST_DRAW_READ], 0, "Serial Close Success");
      }
      break;

    case IDC_BUTTON_DRAW_WRITE:
      DrawSerialWrite();
      break;

    case IDC_BUTTON_DRAW_CLEAR:
      SendMessage(gp->hitem[LIST_DRAW_READ], LVM_DELETEALLITEMS, 0, 0);
      break;



    case IDC_CHECK_DRAW_READ_YN:
      if ( SendMessage(gp->hitem[CHECK_DRAW_READ_YN], BM_GETCHECK, 0, 0) == BST_CHECKED )
      {
        gp->read_lock = 0x01;
      }
      else
      {
        gp->read_lock = 0x00;
      }

      break;

  }
}





void wdrawwnd_static_paint(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  gp->hdc_cross = GetDC(gp->hitem[STATIC_DRAW_AXIS]);

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

  ReleaseDC(gp->hitem[STATIC_DRAW_AXIS], gp->hdc_cross);
}

void wdrawwnd_coord_pick()
{
  SendMessage(gp->hitem[EDIT_DRAW_ABS_COORD_PICK], WM_SETTEXT, (WPARAM)strlen(gp->strcoord[0]), (LPARAM)gp->strcoord[0]);
  SendMessage(gp->hitem[EDIT_DRAW_ABS_COORD_PICK2], WM_SETTEXT, (WPARAM)strlen(gp->strcoord[1]), (LPARAM)gp->strcoord[1]);
  SendMessage(gp->hitem[EDIT_DRAW_REL_COORD_PICK], WM_SETTEXT, (WPARAM)strlen(gp->strcoord[2]), (LPARAM)gp->strcoord[2]);
  SendMessage(gp->hitem[EDIT_DRAW_REL_COORD_PICK2], WM_SETTEXT, (WPARAM)strlen(gp->strcoord[3]), (LPARAM)gp->strcoord[3]);
}

void wdrawwnd_coord_display(int x, int y)
{
  gp->xycoord[0][0] = x;
  gp->xycoord[0][1] = y;
  sprintf(gp->strcoord[0], "(%d, %d),  (%02X, %02X)", gp->xycoord[0][0], gp->xycoord[0][1], (unsigned char)gp->xycoord[0][0], (unsigned char)gp->xycoord[0][1]);
  SendMessage(gp->hitem[EDIT_DRAW_ABS_COORD], WM_SETTEXT, (WPARAM)strlen(gp->strcoord[0]), (LPARAM)gp->strcoord[0]);

  gp->xycoord[1][0] = x - WDRAW_AXIS_X_C;
  gp->xycoord[1][1] = WDRAW_GUIDE_Y_C - (y - ( gp->rct[1].top+(WDRAW_AXIS_Y_C-WDRAW_GUIDE_Y_C) ));
  sprintf(gp->strcoord[1], "(%d, %d),  (%02X, %02X)", gp->xycoord[1][0], gp->xycoord[1][1], (unsigned char)gp->xycoord[1][0], (unsigned char)gp->xycoord[1][1]);
  SendMessage(gp->hitem[EDIT_DRAW_ABS_COORD2], WM_SETTEXT, (WPARAM)strlen(gp->strcoord[1]), (LPARAM)gp->strcoord[1]);

  gp->xycoord[2][0] = x - WDRAW_AXIS_X_C;
  gp->xycoord[2][1] = y - (gp->rct[1].top+(WDRAW_AXIS_Y_C-WDRAW_GUIDE_Y_C));
  sprintf(gp->strcoord[2], "(%d, %d),  (%02X, %02X)", gp->xycoord[2][0], gp->xycoord[2][1], (unsigned char)gp->xycoord[2][0], (unsigned char)gp->xycoord[2][1]);
  SendMessage(gp->hitem[EDIT_DRAW_REL_COORD], WM_SETTEXT, (WPARAM)strlen(gp->strcoord[2]), (LPARAM)gp->strcoord[2]);

  gp->xycoord[3][0] = x - (gp->rct[1].left+(WDRAW_AXIS_X_C-WDRAW_GUIDE_X_C));
  gp->xycoord[3][1] = y - (gp->rct[1].top+(WDRAW_AXIS_Y_C-WDRAW_GUIDE_Y_C));
  sprintf(gp->strcoord[3], "(%d, %d),  (%02X, %02X)", gp->xycoord[3][0], gp->xycoord[3][1], (unsigned char)gp->xycoord[3][0], (unsigned char)gp->xycoord[3][1]);
  SendMessage(gp->hitem[EDIT_DRAW_REL_COORD2], WM_SETTEXT, (WPARAM)strlen(gp->strcoord[3]), (LPARAM)gp->strcoord[3]);
}

void wdrawwnd_coord(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  gp->coord[0] = LOWORD(lparam);
  gp->coord[1] = HIWORD(lparam);
  wdrawwnd_coord_display(gp->coord[0], gp->coord[1]);
}

//
//void wdrawwnd_abs_coord(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
//{
//  int x;
//  int y;
//  char tmp[32];
//
//  x = LOWORD(lparam);
//  y = HIWORD(lparam);
//  sprintf(tmp, "(%d, %d),  (%02X, %02X)", x, y, (unsigned char)x, (unsigned char)y);
//  SendMessage(gp->hitem[EDIT_DRAW_ABS_COORD], WM_SETTEXT, (WPARAM)strlen(tmp), (LPARAM)tmp);
//}
//void wdrawwnd_abs_coord_pick(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
//{
//  int x;
//  int y;
//  char tmp[32];
//
//  x = LOWORD(lparam);
//  y = HIWORD(lparam);
//  sprintf(tmp, "(%d, %d),  (%02X, %02X)", x, y, (unsigned char)x, (unsigned char)y);
//  SendMessage(gp->hitem[EDIT_DRAW_ABS_COORD_PICK], WM_SETTEXT, (WPARAM)strlen(tmp), (LPARAM)tmp);
//}
//void wdrawwnd_rel_coord(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
//{
//  int x;
//  int y;
//  char tmp[32];
//
//  x = LOWORD(lparam) - XDRAW_AXIS_X_C;
//  y = XDRAW_AXIS_Y_SZ - ((HIWORD(lparam) + XDRAW_AXIS_Y_C));
//  sprintf(tmp, "(%d, %d),  (%02X, %02X)", x, y, (unsigned char)x, (unsigned char)y);
//  SendMessage(gp->hitem[EDIT_DRAW_REL_COORD], WM_SETTEXT, (WPARAM)strlen(tmp), (LPARAM)tmp);
//}
//void wdrawwnd_rel_coord_pick(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
//{
//  int x;
//  int y;
//  char tmp[32];
//
//  x = LOWORD(lparam) - XDRAW_AXIS_X_C;
//  y = XDRAW_AXIS_Y_SZ - ((HIWORD(lparam) + XDRAW_AXIS_Y_C));
//  sprintf(tmp, "(%d, %d),  (%02X, %02X)", x, y, (unsigned char)x, (unsigned char)y);
//  SendMessage(gp->hitem[EDIT_DRAW_REL_COORD_PICK], WM_SETTEXT, (WPARAM)strlen(tmp), (LPARAM)tmp);
//}
//void wdrawwnd_rel_coord2(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
//{
//  int x;
//  int y;
//  char tmp[32];
//
//  x = LOWORD(lparam) - (gp->rct[1].left+(XDRAW_AXIS_X_C-XDRAW_GUIDE_X_C));
//  y = HIWORD(lparam) - (gp->rct[1].top+(XDRAW_AXIS_Y_C-XDRAW_GUIDE_Y_C));
//  sprintf(tmp, "(%d, %d),  (%02X, %02X)", x, y, (unsigned char)x, (unsigned char)y);
//  SendMessage(gp->hitem[EDIT_DRAW_REL_COORD2], WM_SETTEXT, (WPARAM)strlen(tmp), (LPARAM)tmp);
//}
//void wdrawwnd_rel_coord_pick2(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
//{
//  int x;
//  int y;
//  char tmp[32];
//
//  x = LOWORD(lparam) - (gp->rct[1].left+(XDRAW_AXIS_X_C-XDRAW_GUIDE_X_C));
//  y = HIWORD(lparam) - (gp->rct[1].top+(XDRAW_AXIS_Y_C-XDRAW_GUIDE_Y_C));
//  sprintf(tmp, "(%d, %d),  (%02X, %02X)", x, y, (unsigned char)x, (unsigned char)y);
//  SendMessage(gp->hitem[EDIT_DRAW_REL_COORD_PICK2], WM_SETTEXT, (WPARAM)strlen(tmp), (LPARAM)tmp);
//}


LRESULT CALLBACK wdrawwnd_static_callback(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int hitCode = 0; 
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
      wdrawwnd_coord_pick();
      break;
    case WM_MOUSEMOVE:
      wdrawwnd_coord(hwnd, msg, wparam, lparam);
      break;

    case WM_PAINT:
      wdrawwnd_static_paint(hwnd, msg, wparam, lparam);
      break;

    default:
      break;
  }
  return TRUE;//CallWindowProc(gp->oitem[STATIC_DRAW_AXIS], hwnd, msg, wparam, lparam);
}

void* wdrawwnd_dlgproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  HDC hdc;
  switch(msg)
  {
    case WM_COMMAND:
      //xdraw_wm_command(hwnd, msg, wparam, lparam);
      break;

    case WM_CTLCOLORSTATIC:
      if (
           ( (HWND)lparam == gp->hitem[EDIT_DRAW_ABS_COORD] ) || 
           ( (HWND)lparam == gp->hitem[EDIT_DRAW_ABS_COORD_PICK] ) ||
           ( (HWND)lparam == gp->hitem[EDIT_DRAW_ABS_COORD2] ) || 
           ( (HWND)lparam == gp->hitem[EDIT_DRAW_ABS_COORD_PICK2] ) ||
           ( (HWND)lparam == gp->hitem[EDIT_DRAW_REL_COORD] ) || 
           ( (HWND)lparam == gp->hitem[EDIT_DRAW_REL_COORD_PICK] ) ||
           ( (HWND)lparam == gp->hitem[EDIT_DRAW_REL_COORD2] ) || 
           ( (HWND)lparam == gp->hitem[EDIT_DRAW_REL_COORD_PICK2] )
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



void* wdrawwnd_init(HWND hwnd, wDrawWnd* p)
{
  int e;

  gp = p;
  //e = mtifSerialCreateEx(&gp->srl.m);


  gp->hbr = CreateSolidBrush(RGB(0,0,0));

  gp->hitem[EDIT_DRAW_ABS_COORD] = GetDlgItem(hwnd, IDC_EDIT_DRAW_ABS_COORD);
  gp->hitem[EDIT_DRAW_ABS_COORD_PICK] = GetDlgItem(hwnd, IDC_EDIT_DRAW_ABS_COORD_PICK);
  gp->hitem[EDIT_DRAW_ABS_COORD2] = GetDlgItem(hwnd, IDC_EDIT_DRAW_ABS_COORD2);
  gp->hitem[EDIT_DRAW_ABS_COORD_PICK2] = GetDlgItem(hwnd, IDC_EDIT_DRAW_ABS_COORD_PICK2);
  gp->hitem[EDIT_DRAW_REL_COORD] = GetDlgItem(hwnd, IDC_EDIT_DRAW_REL_COORD);
  gp->hitem[EDIT_DRAW_REL_COORD_PICK] = GetDlgItem(hwnd, IDC_EDIT_DRAW_REL_COORD_PICK);
  gp->hitem[EDIT_DRAW_REL_COORD2] = GetDlgItem(hwnd, IDC_EDIT_DRAW_REL_COORD2);
  gp->hitem[EDIT_DRAW_REL_COORD_PICK2] = GetDlgItem(hwnd, IDC_EDIT_DRAW_REL_COORD_PICK2);
  gp->hitem[STATIC_DRAW_AXIS] = GetDlgItem(hwnd, IDC_STATIC_DRAW_AXIS);

  gp->hitem[EDIT_DRAW_SPORT] = GetDlgItem(hwnd, IDC_EDIT_DRAW_SPORT);
  gp->hitem[EDIT_DRAW_BAUD] = GetDlgItem(hwnd, IDC_EDIT_DRAW_BAUD);
  gp->hitem[EDIT_DRAW_DBIT] = GetDlgItem(hwnd, IDC_EDIT_DRAW_DBIT);
  gp->hitem[EDIT_DRAW_SBIT] = GetDlgItem(hwnd, IDC_EDIT_DRAW_SBIT);
  gp->hitem[EDIT_DRAW_PBIT] = GetDlgItem(hwnd, IDC_EDIT_DRAW_PBIT);
  gp->hitem[BUTTON_DRAW_OPEN_CLOSE] = GetDlgItem(hwnd, IDC_BUTTON_DRAW_OPEN_CLOSE);
  gp->hitem[COMBO_DRAW_DISPLAY_TYPE_R] = GetDlgItem(hwnd, IDC_COMBO_DRAW_DISPLAY_TYPE_R);
  gp->hitem[COMBO_DRAW_DISPLAY_TYPE_W] = GetDlgItem(hwnd, IDC_COMBO_DRAW_DISPLAY_TYPE_W);
  gp->hitem[EDIT_DRAW_WRITE] = GetDlgItem(hwnd, IDC_EDIT_DRAW_WRITE);
  gp->hitem[BUTTON_DRAW_WRITE] = GetDlgItem(hwnd, IDC_BUTTON_DRAW_WRITE);
  gp->hitem[CHECK_DRAW_CR] = GetDlgItem(hwnd, IDC_CHECK_DRAW_CR);
  gp->hitem[CHECK_DRAW_LF] = GetDlgItem(hwnd, IDC_CHECK_DRAW_LF);
  gp->hitem[CHECK_DRAW_SERIAL_LOG] = GetDlgItem(hwnd, IDC_CHECK_DRAW_SERIAL_LOG);
  gp->hitem[CHECK_DRAW_SERIAL_ECHO] = GetDlgItem(hwnd, IDC_CHECK_DRAW_SERIAL_ECHO);
  gp->hitem[LIST_DRAW_READ] = GetDlgItem(hwnd, IDC_LIST_DRAW_READ);
  gp->hitem[BUTTON_DRAW_CLEAR] = GetDlgItem(hwnd, IDC_BUTTON_DRAW_CLEAR);
  gp->hitem[CHECK_DRAW_READ_YN] = GetDlgItem(hwnd, IDC_CHECK_DRAW_READ_YN);


  ResetText(gp->hitem[EDIT_DRAW_SPORT], "COM1");
  ResetText(gp->hitem[EDIT_DRAW_BAUD], "115200");
  ResetText(gp->hitem[EDIT_DRAW_DBIT], "8");
  ResetText(gp->hitem[EDIT_DRAW_SBIT], "1");
  ResetText(gp->hitem[EDIT_DRAW_PBIT], "0");

  SetText(gp->hitem[BUTTON_DRAW_OPEN_CLOSE], "OPEN", strlen("OPEN"));
  SetText(gp->hitem[BUTTON_DRAW_OPEN_CLOSE], "OPEN", strlen("OPEN"));


	SendMessage(gp->hitem[COMBO_DRAW_DISPLAY_TYPE_R], CB_ADDSTRING, 0, (LPARAM)"ASCII");
	SendMessage(gp->hitem[COMBO_DRAW_DISPLAY_TYPE_R], CB_ADDSTRING, 0, (LPARAM)"HEX");
  SendMessage(gp->hitem[COMBO_DRAW_DISPLAY_TYPE_R], CB_SETCURSEL, 1, 0 );

	SendMessage(gp->hitem[COMBO_DRAW_DISPLAY_TYPE_W], CB_ADDSTRING, 0, (LPARAM)"ASCII");
	SendMessage(gp->hitem[COMBO_DRAW_DISPLAY_TYPE_W], CB_ADDSTRING, 0, (LPARAM)"HEX");
  SendMessage(gp->hitem[COMBO_DRAW_DISPLAY_TYPE_W], CB_SETCURSEL, 1, 0 );


  GetClientRect(gp->hitem[STATIC_DRAW_AXIS], &gp->rct[0]);

  GetWindowRect(hwnd, &gp->rct[1]);
  ScreenToClient(hwnd, (LPPOINT)&gp->rct[1]);

  gp->oitem[STATIC_DRAW_AXIS] = (WNDPROC)SetWindowLongPtr(gp->hitem[STATIC_DRAW_AXIS], GWLP_WNDPROC, (LONG)wdrawwnd_static_callback);

  InitListView(gp->hitem[LIST_DRAW_READ]);

  return 0;
}

