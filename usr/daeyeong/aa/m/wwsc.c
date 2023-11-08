#include "wwsc.h"
#include "resource.h"

static wWSC* gp;


#if 0

/*******************************************************************************
* WebSocket
*******************************************************************************/
int wscWebSocketStatus(void* t, int sd, char* arg1, int arg2, char* arg3, int arg4, int id, int ecode, void* arg5, void* o)
{
  int _e = 0;
  char _ip[32];
  char _port[32];
  char _protocol[16];
  char _cstype[16];
  char _casttype[16];
  //int sz = MAX_BUF_SZ;

  //tagWSC* m = (tagWSC*)t;

  //InsertLVText(gp->hitem[LIST_WSC_LOG], "WebSocket Status %08X(%d) %d, %s, %08X(%d), %s, %d, %d", ecode, ecode, sd, arg2>0?arg1:"", arg2, arg2, arg4>0?arg3:"", arg4, id);


  //if (ecode == 0) ///// CLIENT CONNECTED
  //{
  //  m->ws.clnt[id].fd = sd;
  //  memcpy(m->ws.clnt[id].buf, &sz, sizeof(int));
  //  *((char**)arg1) = m->ws.clnt[id].buf;
  //  *((int**)arg5) = &m->ws.clnt[id].fd;
  //  InsertLVText(gp->hitem[LIST_WSC_LOG], "Connected CLIENT [%4d]: %d", id, sd);
  //}

  ////if (ecode == eDISCONNECTED || ecode == eCONNECTION_CLOSE || ecode == eCONNECTION_FAIL || ecode == -1)
  ////{
  ////  InsertLVText(gp->hitem[LIST_WSC_LOG], "Disconnected CLIENT [%d] [%4d]: %d", ecode, id, sd);
  ////}

  //if (ecode == 0xE000B0FF)
  //{
  //  *((char**)arg1) = (char*)m->wshdr;
  //}

  ////if (ecode == 0x0C)  //// Open Complete
  ////{
  ////}

  ////if (ecode == 0xCC)  //// Close Complete
  ////{
  ////}

  ////if (ecode == 0x1B)  //// Input Before
  ////{
  ////}
  ////if (ecode == 0x1A)  //// Input After
  ////{
  ////}

  ////if (ecode == 0x0B)  //// Output Before
  ////{
  ////}
  ////if (ecode == 0x0A)  //// Output After
  ////{
  ////}

  return _e;
}

int wscWebSocketRecvEx(void* t, int sd, char* arg1, int arg2, char* arg3, int arg4, int id, int ecode, void* arg5, void* o)
{
  return 0;
}


void wscWebSocketSend()
{
  unsigned char msg[1024];
  int sz = 0;
  int e = 0;
  int w = 0;
  int idx = 0;

  msg[sz++] = 0xFF;
  msg[sz++] = ((int)get_rand(gp->range))%2?0x2B:0x7B;
  msg[sz++] = 0x01;
  msg[sz++] = msg[1]==0x2B?((int)get_rand(gp->range))%3:get_rand(gp->range);
  msg[sz++] = get_rand(gp->range);
  msg[sz++] = 0xFF;

  //for (idx = 0; idx<FD_SETSIZE; idx++)
  //{
  //  if (gp->ws.clnt[idx].fd > 0)
  //  {
  //    e = mtifWebSocketSendEx(&gp->ws.m, gp->ws.clnt[idx].fd, (char*)msg, sz, ((unsigned char)*(msg + 0))>0x7F ? 0x02 : 0x01, 0, 1);
  //    if (e > 0)
  //    {
  //      sprintf((char*)msg, "%02X %02X %02X %02X %02X %02X", msg[0],msg[1],msg[2],msg[3],msg[4],msg[5]);
  //      InsertLVText(gp->hitem[LIST_WSC_LOG], "%d = send(%d, \"%s\", %d)", e, gp->ws.clnt[idx].fd, msg, strlen((char*)msg));
  //    }
  //  }
  //}
}


int wscWebSocketOpen()
{
  //int  _sz = MAX_BUF_SZ;

  //lock_init((void*)&gp->ws.crit);
  //gp->ws.m.pfxMTIF[ONWSRECVEX] = wscWebSocketRecvEx;
  //gp->ws.m.pfxMTIF[ONWSSTATUS] = wscWebSocketStatus;

  //memcpy(gp->ws.buf, &_sz, sizeof(int));
  //gp->ws.sd = mtifWebSocketOpenURLEx(&gp->ws.m, "http://127.0.0.1:7810/", "SERVER", 0, 0, 0, &mwsc);

  //return gp->ws.sd;

  return 0;
}

void wscWebSocketClose()
{
  //mtifWebSocketCloseEx(&gp->ws.m, 0);
  //lock_final((void*)&gp->ws.crit);
}
/*******************************************************************************/

void* on_wsc_timer(void* hwnd, int id, int arg0, int arg2)
{
  wscWebSocketSend();

  return 0;
}

void wwsc_command(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  char temp[3][32];

  switch (LOWORD(wparam))
  {
  case IDC_BUTTON_WSC_START:
    GetText(gp->hitem[EDIT_WSC_BEGIN], temp[0], 32);
    GetText(gp->hitem[EDIT_WSC_END], temp[1], 32);
    GetText(gp->hitem[BUTTON_WSC_START], temp[2], 32);
    if ( strncmp(temp[2], "START", 5) == 0 )
    {
      if (wscWebSocketOpen() < 0)
      {
        InsertLVText(gp->hitem[LIST_WSC_LOG], 0, "Simulation Start Fail( %s ~ %s )", temp[0], temp[1]);
      }
      else
      {
        gp->range[0] = (long double)str_to_long(temp[0], strlen(temp[0]));
        gp->range[1] = (long double)str_to_long(temp[1], strlen(temp[1]));
        InsertLVText(gp->hitem[LIST_WSC_LOG], 0, "Simulation Start ( %s ~ %s )", temp[0], temp[1]);
        SetText(gp->hitem[BUTTON_WSC_START], "STOP", 4);
        EnableWindow(gp->hitem[BUTTON_WSC_TIMER], TRUE);
      }
    }
    else
    {
      GetText(gp->hitem[EDIT_WSC_BEGIN], temp[0], 32);
      GetText(gp->hitem[EDIT_WSC_END], temp[1], 32);
      InsertLVText(gp->hitem[LIST_WSC_LOG], 0, "Simulation Stop ( %s ~ %s )", temp[0], temp[1]);
      wscWebSocketClose();
      SetText(gp->hitem[BUTTON_WSC_START], "START", 5);
      EnableWindow(gp->hitem[BUTTON_WSC_TIMER], FALSE);
      SetText(gp->hitem[BUTTON_WSC_TIMER], "TIMER", 5);
      kill_timer(hwnd, 0);
    }
    break;

  case IDC_BUTTON_WSC_TIMER:
      GetText(gp->hitem[EDIT_WSC_TIMER], temp[0], 32);
      GetText(gp->hitem[BUTTON_WSC_TIMER], temp[1], 32);
      if ( strncmp(temp[1], "TIMER", 5) == 0 )
      {
        SetText(gp->hitem[BUTTON_WSC_TIMER], "STOP", 4);
        set_timer(hwnd, 0, atoi(temp[0]), on_wsc_timer);
      }
      else
      {
        SetText(gp->hitem[BUTTON_WSC_TIMER], "TIMER", 5);
        kill_timer(hwnd, 0);
      }
    break;

  case IDC_BUTTON_WSC_CLEAR:
      ClearListView(gp->hitem[LIST_WSC_LOG]);
    break;

  }
}

void* wwsc_dlgproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  switch (msg)
  {
  case WM_COMMAND:
    wwsc_command(hwnd, msg, wparam, lparam);
    break;

  default:
    break;
  }

  return 0;
}


void* wwsc_init(HWND hwnd, wWSC* p)
{
  int e;

  gp = p;

  //memset(&mwsc, 0, sizeof(tagWSC));

  //e = mtifSocketCreateEx(&gp->sck.m);
  //e = mtifWebSocketCreateEx(&gp->ws.m);


  gp->hitem[BUTTON_WSC_START] = GetDlgItem(hwnd, IDC_BUTTON_WSC_START);
  gp->hitem[BUTTON_WSC_TIMER] = GetDlgItem(hwnd, IDC_BUTTON_WSC_TIMER);
  gp->hitem[BUTTON_WSC_CLEAR] = GetDlgItem(hwnd, IDC_BUTTON_WSC_CLEAR);
  gp->hitem[EDIT_WSC_BEGIN] = GetDlgItem(hwnd, IDC_EDIT_WSC_BEGIN);
  gp->hitem[EDIT_WSC_END] = GetDlgItem(hwnd, IDC_EDIT_WSC_END);
  gp->hitem[EDIT_WSC_TIMER] = GetDlgItem(hwnd, IDC_EDIT_WSC_TIMER);
  gp->hitem[LIST_WSC_LOG] = GetDlgItem(hwnd, IDC_LIST_WSC_LOG);

  SetText(gp->hitem[BUTTON_WSC_START], "START", 5);
  SetText(gp->hitem[BUTTON_WSC_TIMER], "TIMER", 5);
  SetText(gp->hitem[BUTTON_WSC_CLEAR], "CLEAR", 5);

  SetText(gp->hitem[EDIT_WSC_BEGIN], "0", 1);
  SetText(gp->hitem[EDIT_WSC_END], "99", 2);
  SetText(gp->hitem[EDIT_WSC_TIMER], "1000", 4);

  EnableWindow(gp->hitem[BUTTON_WSC_TIMER], FALSE);

  InitListView(gp->hitem[LIST_WSC_LOG]);

  return 0;
}
#endif


void* wwsc_dlgproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  return 0;
}

void* wwsc_init(HWND hwnd, wWSC* p)
{
  return 0;
}

