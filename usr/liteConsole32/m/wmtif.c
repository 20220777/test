#include "wmtif.h"
#include "resource.h"
#include "__util.h"

#define WMTIF_TIMER          WM_USER+1
#define WMTIF_NET_SIMUL_TIMER            1
#define WMTIF_WS_SIMUL_TIMER             WMTIF_NET_SIMUL_TIMER+1
#define WMTIF_SERIAL_SIMUL_TIMER         WMTIF_NET_SIMUL_TIMER+2


static wMTIF* gp;



#if 0


void change_list_count()
{
  char lcnt[32];
  int e = 0;
  e = GetText(gp->hitem[EDIT_LIST_COUNT], lcnt, 32);
  lcnt[e] = 0;
  gp->max_line = atoi(lcnt);
}



/*******************************************************************************
 *******************************************************************************
 *******************************************************************************
 *
 *
 * WebSocket
 *
 *
 *******************************************************************************
 *******************************************************************************
 *******************************************************************************/
void WebSocketClose()
{
  mtifWebSocketClose(&gp->pm->mws.m, gp->pm->mws.b);
  lock_final((void*)&gp->pm->mws.crit);
}
void WebSocketWrite(char* b, int s)
{
  char st[32];
  char smsg[1024];
  char sbuf[1024];
  int sz;
  int e = 0;
  int w = 0;
  int idx = 0;

  GetComboText(gp->hitem[COMBO_WS_DISPLAY_TYPE_W], st);
  if ( b == 0 )
  {
    sz = GetText(gp->hitem[EDIT_WS_WRITE], smsg, 1024);
    smsg[sz] = 0;
  }
  else
  {
    memcpy(smsg, b, s);
    sz = s;
    smsg[sz] = 0;
  }

  if ( st[0] == 'A' )
  {
    if ( SendMessage(gp->hitem[CHECK_WS_CR], BM_GETCHECK, 0, 0) == BST_CHECKED )
    {
      sprintf(smsg, "%s\r", smsg);
      sz+=1;
    }
    if ( SendMessage(gp->hitem[CHECK_WS_LF], BM_GETCHECK, 0, 0) == BST_CHECKED )
    {
      sprintf(smsg, "%s\n", smsg);
      sz+=1;
    }

    if ( ((mtifInfo*)gp->pm->mws.info)->arg[XWEBSOCKET][XM_CSTYPE][0] == 'C')
    {
      e = mtifWebSocketWrite(&gp->pm->mws.m, gp->pm->mws.fd, smsg, sz);
      if ( e > 0 )
      {
        change_list_count();
        LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_WS_LOG], gp->max_line, &gp->log, "log", "WebSocket", "%d = Write(%d, \"%s\", %d)", e, gp->pm->mws.fd, smsg, sz);
      }
    }
    else
    {
      for(idx=0 ; idx<FD_SETSIZE ; idx++ )
      {
        if ( gp->pm->mws.pack.info[idx].fd > 0 )
        {
          e = mtifWebSocketWrite(&gp->pm->mws.m, gp->pm->mws.pack.info[idx].fd, smsg, sz);
          if ( e > 0 )
          {
            change_list_count();
            LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_WS_LOG], gp->max_line, &gp->log, "log", "WebSocket", "%d = Write(%d, \"%s\", %d)", e, gp->pm->mws.pack.info[idx].fd, smsg, sz);
          }
        }
      }
    }
  }
  else
  {
    if ( SendMessage(gp->hitem[CHECK_WS_CR], BM_GETCHECK, 0, 0) == BST_CHECKED )
    {
      sprintf(smsg, "%s 0D", smsg);
      sz+=3;
    }
    if ( SendMessage(gp->hitem[CHECK_WS_LF], BM_GETCHECK, 0, 0) == BST_CHECKED )
    {
      sprintf(smsg, "%s 0A", smsg);
      sz+=3;
    }
    w = str_to_hex(smsg, sz, ' ', sbuf);

    if ( ((mtifInfo*)gp->pm->mws.info)->arg[XWEBSOCKET][XM_CSTYPE][0] == 'C')
    {
      e = mtifWebSocketWrite(&gp->pm->mws.m, gp->pm->mws.fd, sbuf, w);
      if ( e > 0 )
      {
        change_list_count();
        LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_WS_LOG], gp->max_line, &gp->log, "log", "WebSocket", "%d = Write(%d, \"%s\", %d)", e, gp->pm->mws.fd, smsg, sz);
      }
    }
    else
    {
      for(idx=0 ; idx<FD_SETSIZE ; idx++ )
      {
        if ( gp->pm->mws.pack.info[idx].fd > 0 )
        {
          e = mtifWebSocketWrite(&gp->pm->mws.m, gp->pm->mws.pack.info[idx].fd, sbuf, w);
          if ( e > 0 )
          {
            change_list_count();
            LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_WS_LOG], gp->max_line, &gp->log, "log", "WebSocket", "%d = Write(%d, \"%s\", %d)", e, gp->pm->mws.pack.info[idx].fd, smsg, sz);
          }
        }
      }
    }
  }
}

void* WebSocketStatus(void* t,int fd, unsigned char* b, int sz, void* extra, int err, void* o)
{
  int e = 0;
  int idx = (extra==0)?0:(*(int*)extra);

  change_list_count();
  LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_WS_LOG], gp->max_line, &gp->log, "log", "WebSocket", "WebSocket (%d:%d) %08X", ((mtifWebSocket*)o)->fd, fd, err);

  switch(err)
  {
    case 0xE000ACCB:
      if ( ((mtifInfo*)((mtifWebSocket*)o)->info)->arg[XWEBSOCKET][XM_CSTYPE][0]=='S' )
      {
        ((mtifWebSocket*)o)->pack.info[idx].fd = fd;
        ((mtifWebSocket*)o)->pack.info[idx].b[0][0] = 0x80|WEBSOCKET_BUF_SFT;
        *((char**)b) = ((mtifWebSocket*)o)->pack.info[idx].b[0];
      }
      break;

    case 0xE000101F:
      if ( ((mtifInfo*)((mtifWebSocket*)o)->info)->arg[XWEBSOCKET][XM_CSTYPE][0]=='S' )
      {
        int e = 0;
        ((mtifWebSocket*)o)->pack.info[idx].fd = 0;
        ((mtifWebSocket*)o)->pack.info[idx].b[0][0] = 0;
      }
      break;

    case 0xE000B0FF:
      *((char**)b) = ((mtifWebSocket*)o)->iobuf;
      break;

    case 0xE000109B:
      //((mtifWebSocket*)o)->pack.info[idx].buf[0] = WEBSOCKET_BUF_SFT;
      //*((char**)b) = ((mtifWebSocket*)o)->pack.info[idx].buf;
      //e = 1;
      break;

  }

  return (void*)e;
}
void* WebSocketRead(void* t,int fd, unsigned char* b, int sz, void* extra, int err, void* o)
{
  int e = 0;
  char st[32];
  char rbuf[4096];
  char vbuf[4096];

  if ( gp->read_lock ) return 0;

  if ( err <0 ) return 0;

  *(b+sz) = 0;

  GetComboText(gp->hitem[COMBO_WS_DISPLAY_TYPE_R], st);

  if ( st[0] == 'A' )
  {
    change_list_count(); 
    LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_WS_LOG], gp->max_line, &gp->log, "log", "WebSocket", "%s", b);

  }
  else
  {
    fprint_raw_buffer(0, b, sz, vbuf);
    change_list_count(); 
    LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_WS_LOG], gp->max_line, &gp->log, "log", "WebSocket", "%s", vbuf);
  }


  if ( ((mtifInfo*)((mtifWebSocket*)o)->info)->arg[XWEBSOCKET][XM_CSTYPE][0]=='S' )
  {
    if ( SendMessage(gp->hitem[CHECK_WS_ECHO], BM_GETCHECK, 0, 0) == BST_CHECKED )
    {
      e = mtifWebSocketWrite(&gp->pm->mws.m, fd, b, sz);
      if ( e > 0 )
      {
        change_list_count(); 
        LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_WS_LOG], gp->max_line, &gp->log, "log", "WebSocket", "%d = Write(%d, \"%s\", %d)", e, fd, b, sz);
      }

    }
  }

  return 0;
}


int WebSocketOpen()
{
  char _url[1024];
  GetText(gp->hitem[EDIT_WS_URL], _url, 1024);
  GetComboText(gp->hitem[COMBO_WS_CS], ((mtifInfo*)gp->pm->mws.info)->arg[XWEBSOCKET][XM_CSTYPE]);

  lock_init((void*)&gp->pm->mws.crit);
  gp->pm->mws.m.pfxMTIF[ONWSSTATUS] = WebSocketStatus;
  gp->pm->mws.m.pfxMTIF[ONWSREAD] = WebSocketRead;

  gp->pm->mws.b[0][0] = 0x80|WEBSOCKET_BUF_SFT;
  gp->pm->mws.fd = mtifWebSocketOpen(&gp->pm->mws.m, _url, ((mtifInfo*)gp->pm->mws.info)->arg[XWEBSOCKET][XM_CSTYPE], 0, gp->pm->mws.b[0], 0, (void*)&gp->pm->mws);
  return gp->pm->mws.fd;
}
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/


/*******************************************************************************
 *******************************************************************************
 *******************************************************************************
 *
 *
 * Socket
 *
 *
 *******************************************************************************
 *******************************************************************************
 *******************************************************************************/
int SocketAddClient(void* t, int fd, char* ip, short port)
{
  wMTIF* m = (wMTIF*)t;
  int idx=0;
  int e = -1;
  int _ip = 0;

  //lock((void*)&m->sck.crit);
  //for(idx=0 ; idx<FD_SETSIZE ; idx++ )
  //{
  //  if ( m->sck.clnt[idx].fd == 0 )
  //  {
  //    m->sck.clnt[idx].fd = fd;
  //    system_time(&m->sck.clnt[idx].timestamp);
  //    str_to_ip(ip, &_ip);
  //    m->sck.clnt[idx].ip[3] = (_ip&0x000000FF);
  //    m->sck.clnt[idx].ip[2] = (_ip&0x0000FF00)>>8;
  //    m->sck.clnt[idx].ip[1] = (_ip&0x00FF0000)>>16;
  //    m->sck.clnt[idx].ip[0] = (_ip&0xFF000000)>>24;
  //    m->sck.clnt[idx].port[1] = (port&0x00FF);
  //    m->sck.clnt[idx].port[0] = (port&0xFF00)>>8;
  //    lock_init((void*)&m->sck.clnt[idx].crit);
  //    e = 0;
  //    break;
  //  }
  //}
  //unlock((void*)&m->sck.crit);
  return e;
}

int SocketRemoveClient(void* t, int fd)
{
  wMTIF* m = (wMTIF*)t;
  int idx=0;
  int e = -1;
  //lock((void*)&m->sck.crit);

  //for(idx=0 ; idx<FD_SETSIZE ; idx++ )
  //{
  //  if ( fd == -1 )
  //  {
  //    m->sck.clnt[idx].timestamp = 0;
  //    m->sck.clnt[idx].fd = 0;
  //    lock_final((void*)&m->sck.clnt[idx].crit);
  //    e = 0;
  //  }
  //  else
  //  if ( m->sck.clnt[idx].fd == fd )
  //  {
  //    m->sck.clnt[idx].timestamp = 0;
  //    m->sck.clnt[idx].fd = 0;
  //    lock_final((void*)&m->sck.clnt[idx].crit);
  //    e = 0;
  //    break;
  //  }
  //}
  //unlock((void*)&m->sck.crit);
  return e;
}

#if 0
int SocketStatus(void* t,int sd, char* arg1, int arg2, char* arg3, int arg4, int id, int ecode,void* arg5, void* o)
{
  int _e = 0;
  char _ip[32];
  char _port[32];
  char _protocol[16];
  char _cstype[16];
  char _casttype[16];
  wMTIF* m = (wMTIF*)t;
  //int sz = MAX_BUF_SZ;

  //InsertLVText(gp->hitem[LIST_READ], "Socket Status : [%d] [%08X] ", ecode, ecode);

  //if ( ecode == 0 ) ///// CLIENT CONNECTED
  //{
  //  GetComboText(gp->hitem[COMBO_PROTOCOL], _protocol);
  //  GetComboText(gp->hitem[COMBO_CS], _cstype);

  //  if ( _protocol[0] == 'T' )
  //  {
  //    if ( _cstype[0] == 'S' )
  //    {    
  //      //SocketAddClient(t, sd, arg3, arg2);
  //      m->sck.clnt[id].fd = sd;
  //      memcpy(m->sck.clnt[id].buf, &sz, sizeof(int));
  //      *((char**)arg1) = m->sck.clnt[id].buf;
  //      *((int**)arg5) = &m->sck.clnt[id].fd;
  //      InsertLVText(gp->hitem[LIST_READ], "Client Connected : %d %d %s", sd, id, arg3);
  //      LogWrite(gp->hitem[CHECK_WS_LOG], &gp->log, "mtif", "socket", "Client Connected : %d %d %s %d", sd, id, arg3, arg4);
  //    }
  //    else
  //    {
  //      InsertLVText(gp->hitem[LIST_READ], "Connected : %d", sd);
  //      LogWrite(gp->hitem[CHECK_WS_LOG], &gp->log, "mtif", "socket", "Connected : %d", sd);
  //    }
  //  }
  //    
  //}

  //if ( ecode == eDISCONNECTED || ecode == eCONNECTION_CLOSE || ecode == eCONNECTION_FAIL )
  //{
  //  GetComboText(gp->hitem[COMBO_PROTOCOL], _protocol);
  //  GetComboText(gp->hitem[COMBO_CS], _cstype);
  //  if ( _protocol[0] == 'T' )
  //  {
  //    if ( _cstype[0] == 'S' )
  //    {    
  //      //SocketRemoveClient(t, sd);
  //      InsertLVText(gp->hitem[LIST_READ], "Client disonnected : %d", sd);
  //      LogWrite(gp->hitem[CHECK_WS_LOG], &gp->log, "mtif", "socket", "Client disonnected : %d", sd);
  //    }
  //    else
  //    {
  //      InsertLVText(gp->hitem[LIST_READ], "Disconnected : %d", sd);
  //      LogWrite(gp->hitem[CHECK_WS_LOG], &gp->log, "mtif", "socket", "Disconnected : %d", sd);
  //    }
  //  }
  //}

  //if ( ecode == -9006 )
  //{
  //  GetComboText(gp->hitem[COMBO_PROTOCOL], _protocol);
  //  GetComboText(gp->hitem[COMBO_CS], _cstype);
  //  if ( _protocol[0] == 'T' )
  //  {
  //    if ( _cstype[0] == 'S' )
  //    {    
  //    }
  //    else
  //    {
  //      InsertLVText(gp->hitem[LIST_READ], "Disconnected : %d", sd);
  //      LogWrite(gp->hitem[CHECK_WS_LOG], &gp->log, "mtif", "socket", "Disconnected : %d", sd);
  //    }
  //  }
  //}


  //if ( ecode == 0x0C )  //// Open Complete
  //{
  //  GetText(gp->hitem[EDIT_IP], _ip, 32);
  //  GetText(gp->hitem[EDIT_PORT], _port, 32);
  //  GetComboText(gp->hitem[COMBO_PROTOCOL], _protocol);
  //  GetComboText(gp->hitem[COMBO_CS], _cstype);
  //  GetComboText(gp->hitem[COMBO_CASTTYPE], _casttype);

  //  InsertLVText(gp->hitem[LIST_READ], "Open : %s %s %s %s %s", _ip, _port, _protocol, _cstype, _casttype);
  //  LogWrite(gp->hitem[CHECK_WS_LOG], &gp->log, "mtif", "socket", "Open : %s %s %s %s %s", _ip, _port, _protocol, _cstype, _casttype);
  //}

  //if ( ecode == 0xCC )  //// Close Complete
  //{
  //  GetText(gp->hitem[EDIT_IP], _ip, 32);
  //  GetText(gp->hitem[EDIT_PORT], _port, 32);
  //  GetComboText(gp->hitem[COMBO_PROTOCOL], _protocol);
  //  GetComboText(gp->hitem[COMBO_CS], _cstype);
  //  GetComboText(gp->hitem[COMBO_CASTTYPE], _casttype);

  //  InsertLVText(gp->hitem[LIST_READ], "Close : %s %s %s %s %s", _ip, _port, _protocol, _cstype, _casttype);
  //  LogWrite(gp->hitem[CHECK_WS_LOG], &gp->log, "mtif", "socket", "Close : %s %s %s %s %s", _ip, _port, _protocol, _cstype, _casttype);
  //}

  //if ( ecode == 0x1B )  //// Input Before
  //{
  //}
  //if ( ecode == 0x1A )  //// Input After
  //{
  //}

  //if ( ecode == 0x0B )  //// Output Before
  //{
  //}
  //if ( ecode == 0x0A )  //// Output After
  //{
  //}

  return _e;
}

int SocketRecvEx(void* t,int sd, char* arg1, int arg2, char* arg3, int arg4, int id, int ecode, void* arg5, void* o)
{
  char st[32];
  char rbuf[1024];
  char vbuf[1024];
  char _cstype[8];
  int e = 0;
  int idx = 0;
  if ( gp->read_lock ) return 0;

  *(arg1+arg2) = 0;

  GetComboText(gp->hitem[COMBO_DISPLAY_TYPE_NET_R], st);
  GetComboText(gp->hitem[COMBO_CS], _cstype);


  //if ( st[0] == 'A' )
  //{
  //  InsertLVText(gp->hitem[LIST_READ], arg1);
  //  LogWrite(gp->hitem[CHECK_NET_LOG], &gp->log, "mtif", "socket", arg1);
  //}
  //else
  //{
  //  fprint_raw_buffer(0, arg1, arg2, vbuf);
  //  InsertLVText(gp->hitem[LIST_READ], vbuf);
  //  LogWrite(gp->hitem[CHECK_NET_LOG], &gp->log, "mtif", "socket", vbuf);
  //}


  //if ( SendMessage(gp->hitem[CHECK_NET_ECHO], BM_GETCHECK, 0, 0) == BST_CHECKED )
  //{
  //  for(idx=0 ; idx<FD_SETSIZE ; idx++ )
  //  {
  //    if ( gp->sck.clnt[idx].fd > 0 )
  //    {
  //      e = mtifSocketSendEx(&gp->sck.m, gp->sck.clnt[idx].fd, arg1, arg2, 0, 0, 0);
  //      if ( e > 0 )
  //      {
  //        InsertLVText(gp->hitem[LIST_READ], "%d = send(%d, \"%s\", %d)", e, gp->sck.clnt[idx].fd, arg1, arg2);
  //        LogWrite(gp->hitem[CHECK_NET_LOG], &gp->log, "mtif", "socket", "%d = send(%d, \"%s\", %d)", e, gp->sck.clnt[idx].fd, arg1, arg2);
  //      }
  //    }
  //  }
  //}
  return 0;
}
#endif
void SocketClose()
{
  mtifSocketClose(&gp->pm->msck.m, gp->pm->msck.b[0]);
  lock_final((void*)&gp->pm->msck.crit);
}

void SocketSendTo(char* b, int s)
{
  char st[32];
  char smsg[1024];
  char sbuf[1024];
  int sz;
  int e = 0;
  int w = 0;
  int idx = 0;

  GetComboText(gp->hitem[COMBO_NET_DISPLAY_TYPE_W], st);
  if ( b == 0 )
  {
    sz = GetText(gp->hitem[EDIT_NET_WRITE], smsg, 1024);
    smsg[sz] = 0;
  }
  else
  {
    memcpy(smsg, b, s);
    sz = s;
    smsg[sz] = 0;
  }

  if ( st[0] == 'A' )
  {
    if ( SendMessage(gp->hitem[CHECK_NET_CR], BM_GETCHECK, 0, 0) == BST_CHECKED )
    {
      sprintf(smsg, "%s\r", smsg);
      sz+=1;
    }
    if ( SendMessage(gp->hitem[CHECK_NET_LF], BM_GETCHECK, 0, 0) == BST_CHECKED )
    {
      sprintf(smsg, "%s\n", smsg);
      sz+=1;
    }

    if ( ((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_CSTYPE][0]=='C' )
    {
      e = mtifSocketWriteTo(&gp->pm->msck.m, gp->pm->mhttp.fd, smsg, sz, ((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_IP], atoi(((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_PORT]));
      if ( e > 0 )
      {
        change_list_count();
        LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_NET_LOG], gp->max_line, &gp->log, "log", "Socket", "%d = writeto(%d, \"%s\", %d, \"%s\", %d)", e, gp->pm->msck.fd, smsg, sz, ((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_IP], atoi(((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_PORT]));
      }
    }
    else
    {
      for(idx=0 ; idx<FD_SETSIZE ; idx++ )
      {
        if ( gp->pm->msck.pack.info[idx].fd > 0 )
        {
          e = mtifSocketWrite(&gp->pm->msck.m, gp->pm->msck.pack.info[idx].fd, smsg, sz, ((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_IP], atoi(((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_PORT]));
          if ( e > 0 )
          {
            change_list_count();
            LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_NET_LOG], gp->max_line, &gp->log, "log", "Socket", "%d = writeto(%d, \"%s\", %d, \"%s\", %d)", e, gp->pm->msck.pack.info[idx].fd, smsg, sz, ((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_IP], atoi(((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_PORT]));
          }
        }
      }
    }
  }
  else if ( st[0] == 'H' )
  {
    if ( SendMessage(gp->hitem[CHECK_NET_CR], BM_GETCHECK, 0, 0) == BST_CHECKED )
    {
      sprintf(smsg, "%s 0D", smsg);
      sz+=3;
    }
    if ( SendMessage(gp->hitem[CHECK_NET_LF], BM_GETCHECK, 0, 0) == BST_CHECKED )
    {
      sprintf(smsg, "%s 0A", smsg);
      sz+=3;
    }
    w = str_to_hex(smsg, sz, ' ', sbuf);

    if ( ((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_CSTYPE][0]=='C' )
    {
      e = mtifSocketWriteTo(&gp->pm->msck.m, gp->pm->mhttp.fd, sbuf, w, ((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_IP], atoi(((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_PORT]));
      if ( e > 0 )
      {
        change_list_count();
        LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_NET_LOG], gp->max_line, &gp->log, "log", "Socket", "%d = writeto(%d, \"%s\", %d, \"%s\", %d)", e, gp->pm->msck.fd, smsg, sz, ((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_IP], atoi(((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_PORT]));
      }
    }
    else
    {
      for(idx=0 ; idx<FD_SETSIZE ; idx++ )
      {
        if ( gp->pm->msck.pack.info[idx].fd > 0 )
        {
          e = mtifSocketWriteTo(&gp->pm->msck.m, gp->pm->msck.pack.info[idx].fd, sbuf, w, ((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_IP], atoi(((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_PORT]));
          if ( e > 0 )
          {
            change_list_count();
            LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_NET_LOG], gp->max_line, &gp->log, "log", "Socket", "%d = writeto(%d, \"%s\", %d, \"%s\", %d)", e, gp->pm->msck.pack.info[idx].fd, smsg, sz, ((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_IP], atoi(((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_PORT]));
          }
        }
      }
    }
  }
}
void SocketSend(char* b, int s)
{
  char st[32];
  char smsg[1024];
  char sbuf[1024];
  int sz;
  int e = 0;
  int w = 0;
  int idx = 0;

  GetComboText(gp->hitem[COMBO_NET_DISPLAY_TYPE_W], st);
  if ( b == 0 )
  {
    sz = GetText(gp->hitem[EDIT_NET_WRITE], smsg, 1024);
    smsg[sz] = 0;
  }
  else
  {
    memcpy(smsg, b, s);
    sz = s;
    smsg[sz] = 0;
  }


  if ( st[0] == 'A' )
  {
    if ( SendMessage(gp->hitem[CHECK_NET_CR], BM_GETCHECK, 0, 0) == BST_CHECKED )
    {
      sprintf(smsg, "%s\r", smsg);
      sz+=1;
    }
    if ( SendMessage(gp->hitem[CHECK_NET_LF], BM_GETCHECK, 0, 0) == BST_CHECKED )
    {
      sprintf(smsg, "%s\n", smsg);
      sz+=1;
    }

    if ( ((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_CSTYPE][0]=='C' )
    {
      e = mtifSocketWrite(&gp->pm->msck.m, gp->pm->mhttp.fd, smsg, sz);//, ((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_IP], atoi(((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_PORT]));
      if ( e > 0 )
      {
        change_list_count();
        LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_NET_LOG], gp->max_line, &gp->log, "log", "Socket", "%d = write(%d, \"%s\", %d)", e, gp->pm->msck.fd, smsg, sz);
      }
    }
    else
    {
      for(idx=0 ; idx<FD_SETSIZE ; idx++ )
      {
        if ( gp->pm->msck.pack.info[idx].fd > 0 )
        {
          e = mtifSocketWrite(&gp->pm->msck.m, gp->pm->msck.pack.info[idx].fd, smsg, sz);
          if ( e > 0 )
          {
            change_list_count();
            LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_NET_LOG], gp->max_line, &gp->log, "log", "Socket", "%d = write(%d, \"%s\", %d)", e, gp->pm->msck.pack.info[idx].fd, smsg, sz);
          }
        }
      }
    }
  }
  else if ( st[0] == 'H' )
  {
    if ( SendMessage(gp->hitem[CHECK_NET_CR], BM_GETCHECK, 0, 0) == BST_CHECKED )
    {
      sprintf(smsg, "%s 0D", smsg);
      sz+=3;
    }
    if ( SendMessage(gp->hitem[CHECK_NET_LF], BM_GETCHECK, 0, 0) == BST_CHECKED )
    {
      sprintf(smsg, "%s 0A", smsg);
      sz+=3;
    }
    w = str_to_hex(smsg, sz, ' ', sbuf);

    if ( ((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_CSTYPE][0]=='C' )
    {
      e = mtifSocketWrite(&gp->pm->msck.m, gp->pm->mhttp.fd, sbuf, w);
      if ( e > 0 )
      {
        change_list_count();
        LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_NET_LOG], gp->max_line, &gp->log, "log", "Socket", "%d = write(%d, \"%s\", %d)", e, gp->pm->msck.fd, sbuf, w);
      }
    }
    else
    {
      for(idx=0 ; idx<FD_SETSIZE ; idx++ )
      {
        if ( gp->pm->msck.pack.info[idx].fd > 0 )
        {
          e = mtifSocketWrite(&gp->pm->msck.m, gp->pm->msck.pack.info[idx].fd, sbuf, w);
          if ( e > 0 )
          {
            change_list_count();
            LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_NET_LOG], gp->max_line, &gp->log, "log", "Socket", "%d = write(%d, \"%s\", %d)", e, gp->pm->msck.pack.info[idx].fd, sbuf, w);
          }
        }
      }
    }
  }
}





void SocketWrite(char* b, int sz)
{
  char tmp[32];
  GetComboText(gp->hitem[COMBO_NET_PROTOCOL], tmp);

  if ( tmp[0] == 'T' ) SocketSend(b, sz);
  else if ( tmp[0] == 'U' ) SocketSendTo(b, sz);
}



void* SocketStatus(void* t,int fd, unsigned char* b, int sz, void* extra, int err, void* o)
{
  int e = 0;
  int idx = (extra==0)?0:(*(int*)extra);

  change_list_count();
  LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_NET_LOG], gp->max_line, &gp->log, "log", "Socket", "Socket (%d) %08X", ((mtifSocket*)o)->fd, err);
  switch(err)
  {
    case 0xE000ACCB:
      if ( ((mtifInfo*)((mtifSocket*)o)->info)->arg[XSOCKET][XM_CSTYPE][0]=='S' )
      {
        ((mtifSocket*)o)->pack.info[idx].b[0][0] = 0x80|SOCKET_BUF_SFT;
        *(char**)b = ((mtifSocket*)o)->pack.info[idx].b[0];
        ((mtifSocket*)o)->pack.info[idx].fd = fd;
        change_list_count();
        LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_NET_LOG], gp->max_line, &gp->log, "log", "Socket", "Socket (%d:%d) %08X ACCEPT BEFORE", ((mtifSocket*)o)->fd, fd, err);
      }
      break;
    case 0xE000ACCA:
      if ( ((mtifInfo*)((mtifSocket*)o)->info)->arg[XSOCKET][XM_CSTYPE][0]=='S' )
      {
        change_list_count();
        LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_NET_LOG], gp->max_line, &gp->log, "log", "Socket", "Socket (%d) %08X ACCEPT AFTER", ((mtifSocket*)o)->fd, err);
      }
      break;

    case 0xE000101B:
      if ( ((mtifInfo*)((mtifSocket*)o)->info)->arg[XSOCKET][XM_CSTYPE][0]=='S' )
      {

      }
      //if(((mtifInfo*)((mtifSocket*)o)->info)->arg[XSOCKET][XM_CSTYPE][0]=='S')
      //{
      //  e=mtifSocketFDSet(&((mtifSocket*)o)->m,(void**)&(((mtifSocket*)o)->fds));
      //  display_fdset(((mtifSocket*)o)->fds,e);
      //  e = 0;
      //}
      break;
    case 0xE000101A:
      if ( ((mtifInfo*)((mtifSocket*)o)->info)->arg[XSOCKET][XM_CSTYPE][0]=='S' )
      {

      }
      //if(((mtifInfo*)((mtifSocket*)o)->info)->arg[XSOCKET][XM_CSTYPE][0]=='S')
      //{
      //  e=mtifSocketFDSet(&((mtifSocket*)o)->m,(void**)&(((mtifSocket*)o)->fds));
      //  display_fdset(((mtifSocket*)o)->fds,e);
      //  e = 0;
      //}
      break;
    case 0xE000500F:
    case 0xE000101F:
      if ( ((mtifInfo*)((mtifSocket*)o)->info)->arg[XSOCKET][XM_CSTYPE][0]=='S' )
      {
        change_list_count();
        LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_NET_LOG], gp->max_line, &gp->log, "log", "Socket", "Socket (%d:%d) %08X Disconnected", ((mtifSocket*)o)->fd, ((mtifSocket*)o)->pack.info[idx].fd, err);
        ((mtifSocket*)o)->pack.info[idx].b[0][0] = 0;
        ((mtifSocket*)o)->pack.info[idx].fd = -1;
      }
      if ( ((mtifInfo*)((mtifSocket*)o)->info)->arg[XSOCKET][XM_CSTYPE][0]=='C' )
      {
        change_list_count();
        LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_NET_LOG], gp->max_line, &gp->log, "log", "Socket", "Socket (%d) %08X Disconnected", ((mtifSocket*)o)->fd,  err);
        mtifSocketClose(&((mtifSocket*)o)->m, ((mtifSocket*)o)->b);
      }
      //if(((mtifInfo*)((mtifSocket*)o)->info)->arg[XSOCKET][XM_CSTYPE][0]=='C')
      //{
      //  xmsgq_set(o, MAKELONG(CLOSE, XSOCKET), 0, 0);
      //  xmsgq_set(o, MAKELONG(IDLE, XSOCKET), MAKELONG(OPEN, XSOCKET), (void*)((mtifInfo*)((mtifSocket*)o)->info)->arg[XSOCKET][XM_DELAY_0]);
      //}
      break;
    case 0xE000001B:
      if ( ((mtifInfo*)((mtifSocket*)o)->info)->arg[XSOCKET][XM_CSTYPE][0]=='S' )
      {

      }
      break;
    case 0xE000001A:
      if ( ((mtifInfo*)((mtifSocket*)o)->info)->arg[XSOCKET][XM_CSTYPE][0]=='S' )
      {

      }
      //if(((mtifInfo*)((mtifSocket*)o)->info)->arg[XSOCKET][XM_CSTYPE][0]=='S')
      //{
      //  if(((mtifInfo*)((mtifSocket*)o)->info)->arg[XSOCKET][XM_ECHOMODE][0]=='1')
      //  {
      //    xmsgq_set(o, MAKELONG(WRITE, XSOCKET), (void*)sz, extra);
      //  }
      //}
      break;
    case 0xE000109B:
      if ( ((mtifInfo*)((mtifSocket*)o)->info)->arg[XSOCKET][XM_CSTYPE][0]=='S' )
      {
        ((mtifSocket*)o)->pack.info[idx].b[0][0]=0x80|SOCKET_BUF_SFT;
        *(char**)b = ((mtifSocket*)o)->pack.info[idx].b;
        //e = 1;
      }
      break;
    case 0xE000C75B:
      change_list_count();
      LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_NET_LOG], gp->max_line, &gp->log, "log", "Socket", "Socket (%d) %08X Thread Close Before", ((mtifSocket*)o)->fd, err);
      break;
    case 0xE000C75A:
      change_list_count();
      LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_NET_LOG], gp->max_line, &gp->log, "log", "Socket", "Socket (%d) %08X Thread Close After", ((mtifSocket*)o)->fd, err);
      break;

  }

  return (void*)e;
}

void* SocketRead(void* t,int fd, unsigned char* b, int sz, void* extra, int err, void* o)
{
  char st[32];
  char rbuf[1024];
  char vbuf[1024];
  int e = 0;
  int idx = 0;
  if ( gp->read_lock ) return 0;
  if ( sz <= 0 ) return 0;

  *(b+sz) = 0;

  GetComboText(gp->hitem[COMBO_NET_DISPLAY_TYPE_R], st);

  if ( st[0] == 'A' )
  {
    change_list_count();
    LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_NET_LOG], gp->max_line, &gp->log, "log", "Socket", "read (%d:%d) %s", ((mtifSocket*)o)->fd,fd, b);
  }
  else
  {
    fprint_raw_buffer(0, b, sz, vbuf);
    change_list_count();
    LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_NET_LOG], gp->max_line, &gp->log, "log", "Socket", "read (%d:%d) %s", ((mtifSocket*)o)->fd,fd, vbuf);
  }


  if ( SendMessage(gp->hitem[CHECK_NET_ECHO], BM_GETCHECK, 0, 0) == BST_CHECKED )
  {
    for(idx=0 ; idx<FD_SETSIZE ; idx++ )
    {
      if ( gp->pm->msck.pack.info[idx].fd > 0 )
      {
        e = mtifSocketWrite(&gp->pm->msck.m, gp->pm->msck.pack.info[idx].fd, b, sz);
        if ( e > 0 )
        {
          change_list_count();
          LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_NET_LOG], gp->max_line, &gp->log, "log", "Socket", "%d = write(%d, \"%s\", %d)", e, gp->pm->msck.pack.info[idx].fd, b, sz);
        }
      }
    }
  }

  return 0;
}



/*******************************************************************************/


/*******************************************************************************
 * Serial
 *******************************************************************************/
void* SerialStatus(void* t,void* fd, unsigned char* b,int sz,void* extra, int err, void* o)
{
  int e = 0;

  return e;
}

void* SerialRead(void* t,void* fd, unsigned char* b,int sz,void* extra, int err, void* o)
{
  char st[32];
  char rbuf[1024];
  char vbuf[1024];
  int e = 0;
  int w = 0;
  if ( gp->read_lock ) return 0;
  if ( err < 0 ) return SerialStatus(t,fd,b,sz,extra,err,o);

  *(b+sz) = 0;

  GetComboText(gp->hitem[COMBO_NET_DISPLAY_TYPE_R], st);

  if ( SendMessage(gp->hitem[CHECK_SERIAL_ROUTER], BM_GETCHECK, 0, 0) == BST_CHECKED )
  {
    change_list_count();
    LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_SERIAL_LOG], gp->max_line, &gp->log, "log", "Serial #1", "Serial #1 Read");
    if ( gp->pm->msrl[1].fd ) e = WriteFile((HANDLE)gp->pm->msrl[1].fd, b, sz, (LPDWORD)&w, 0);
  }

  if ( st[0] == 'A' )
  {
    change_list_count();
    LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_SERIAL_LOG], gp->max_line, &gp->log, "log", "Serial #1", "Serial #1 [I] %s", b);
  }
  else
  {
    fprint_raw_buffer(0, b, sz, vbuf);
    change_list_count();
    LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_SERIAL_LOG], gp->max_line, &gp->log, "log", "Serial #1", "Serial #1 [I] %s", vbuf);
  }
  return 0;
}

void SerialWrite(char* b, int s)
{
  char st[32];
  char smsg[1024];
  char sbuf[1024];
  int sz;
  int e = 0;
  int w = 0;
  
  GetComboText(gp->hitem[COMBO_SERIAL_DISPLAY_TYPE_W], st);

  if ( b == 0 )
  {
    sz = GetText(gp->hitem[EDIT_SERIAL_WRITE], smsg, 1024);
    smsg[sz] = 0;
  }
  else
  {
    memcpy(smsg, b, s);
    sz = s;
    smsg[sz] = 0;
  }
  if ( st[0] == 'A' )
  {
    if ( SendMessage(gp->hitem[CHECK_SERIAL_CR], BM_GETCHECK, 0, 0) == BST_CHECKED )
    {
      sprintf(smsg, "%s\r", smsg);
      sz+=1;
    }
    if ( SendMessage(gp->hitem[CHECK_SERIAL_LF], BM_GETCHECK, 0, 0) == BST_CHECKED )
    {
      sprintf(smsg, "%s\n", smsg);
      sz+=1;
    }
    e = WriteFile((HANDLE)gp->pm->msrl[0].fd, smsg, sz, (LPDWORD)&w, 0);
    change_list_count();
    LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_SERIAL_LOG], gp->max_line, &gp->log, "log", "Serial #1", "Serial #1 [O] %s", smsg);
  }
  else
  {
    if ( SendMessage(gp->hitem[CHECK_SERIAL_CR], BM_GETCHECK, 0, 0) == BST_CHECKED )
    {
      sprintf(smsg, "%s 0D", smsg);
      sz+=3;
    }
    if ( SendMessage(gp->hitem[CHECK_SERIAL_LF], BM_GETCHECK, 0, 0) == BST_CHECKED )
    {
      sprintf(smsg, "%s 0A", smsg);
      sz+=3;
    }
    e = str_to_hex(smsg, sz, ' ', sbuf);
    e = WriteFile((HANDLE)gp->pm->msrl[0].fd, sbuf, e, (LPDWORD)&w, 0);
    change_list_count();
    LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_SERIAL_LOG], gp->max_line, &gp->log, "log", "Serial #1", "Serial #1 [O] %s", smsg);
  }

}

int SerialOpen()
{
  GetText(gp->hitem[EDIT_SERIAL_PORT],   ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_PORT], 32);
  GetText(gp->hitem[EDIT_SERIAL_BAUDRATE],((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_BAUDRATE], 32);
  GetText(gp->hitem[EDIT_SERIAL_DBIT],    ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_DATABIT], 4);
  GetText(gp->hitem[EDIT_SERIAL_SBIT],    ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_STOPBIT], 4);
  GetText(gp->hitem[EDIT_SERIAL_PBIT],    ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_PARITYBIT], 4);

  gp->pm->msrl[0].m.pfxMTIF[ONSERIALREAD] = SerialRead;
  gp->pm->msrl[0].b[0] = 1;
  gp->pm->msrl[0].fd = mtifSerialOpen(&gp->pm->msrl[0].m, 
                                      ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_PORT],
                                      ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_BAUDRATE],
                                      ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_DATABIT],
                                      ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_STOPBIT],
                                      ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_PARITYBIT],"0", gp->pm->msrl[0].b, (void*)&gp->pm->msrl[0]);
  return (int)gp->pm->msrl[0].fd;
}

void SerialClose()
{
  mtifSerialClose(&gp->pm->msrl[0].m, gp->pm->msrl[0].fd, gp->pm->msrl[0].b);
}
/*******************************************************************************/
void* SerialStatus2(void* t,void* fd, unsigned char* b,int sz,void* extra, int err, void* o)
{
  int e = 0;
  int r = 0;
  return e;
}

void* SerialRead2(void* t,void* fd, unsigned char* b,int sz,void* extra, int err, void* o)
{
  char st[32];
  char rbuf[1024];
  char vbuf[1024];
  int e = 0;
  int w = 0;
  if ( gp->read_lock ) return 0;
  if ( err < 0 ) return SerialStatus2(t,fd,b,sz,extra,err,o);
  *(b+sz) = 0;

  GetComboText(gp->hitem[COMBO_SERIAL_DISPLAY_TYPE_R2], st);

  if ( SendMessage(gp->hitem[CHECK_SERIAL_ROUTER], BM_GETCHECK, 0, 0) == BST_CHECKED )
  {
    change_list_count();
    LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_SERIAL_LOG2], gp->max_line, &gp->log, "log", "Serial #2", "Serial #2 Read");
    if ( gp->pm->msrl[0].fd ) e = WriteFile((HANDLE)gp->pm->msrl[0].fd, b, sz, (LPDWORD)&w, 0);
  }


  if ( st[0] == 'A' )
  {
    change_list_count();
    LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_SERIAL_LOG2], gp->max_line, &gp->log, "log", "Serial #2", "Serial #2 [I] %s", b);
  }
  else
  {
    fprint_raw_buffer(0, b, sz, vbuf);
    change_list_count();
    LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_SERIAL_LOG2], gp->max_line, &gp->log, "log", "Serial #2", "Serial #2 [I] %s", vbuf);
  }
  return 0;
}

void SerialWrite2(char* b, int s)
{
  char st[32];
  char smsg[1024];
  char sbuf[1024];
  int sz;
  int e = 0;
  int w = 0;
  
  GetComboText(gp->hitem[COMBO_SERIAL_DISPLAY_TYPE_W2], st);

  if ( b == 0 )
  {
    sz = GetText(gp->hitem[EDIT_SERIAL_WRITE2], smsg, 1024);
    smsg[sz] = 0;
  }
  else
  {
    memcpy(smsg, b, s);
    sz = s;
    smsg[sz] = 0;
  }

  if ( st[0] == 'A' )
  {
    if ( SendMessage(gp->hitem[CHECK_SERIAL_CR2], BM_GETCHECK, 0, 0) == BST_CHECKED )
    {
      sprintf(smsg, "%s\r", smsg);
      sz+=1;
    }
    if ( SendMessage(gp->hitem[CHECK_SERIAL_LF2], BM_GETCHECK, 0, 0) == BST_CHECKED )
    {
      sprintf(smsg, "%s\n", smsg);
      sz+=1;
    }
    e = WriteFile((HANDLE)gp->pm->msrl[1].fd, smsg, sz, (LPDWORD)&w, 0);
    change_list_count();
    LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_SERIAL_LOG2], gp->max_line, &gp->log, "log", "Serial #2", "Serial #2 [O] %s", smsg);
  }
  else
  {
    if ( SendMessage(gp->hitem[CHECK_SERIAL_CR2], BM_GETCHECK, 0, 0) == BST_CHECKED )
    {
      sprintf(smsg, "%s 0D", smsg);
      sz+=3;
    }
    if ( SendMessage(gp->hitem[CHECK_SERIAL_LF2], BM_GETCHECK, 0, 0) == BST_CHECKED )
    {
      sprintf(smsg, "%s 0A", smsg);
      sz+=3;
    }
    e = str_to_hex(smsg, sz, ' ', sbuf);
    e = WriteFile((HANDLE)gp->pm->msrl[1].fd, sbuf, e, (LPDWORD)&w, 0);
    change_list_count();
    LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_SERIAL_LOG2], gp->max_line, &gp->log, "log", "Serial #2", "Serial #2 [O] %s", smsg);
  }

}

int SerialOpen2()
{
  GetText(gp->hitem[EDIT_SERIAL_PORT2],   ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_PORT], 32);
  GetText(gp->hitem[EDIT_SERIAL_BAUDRATE2],((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_BAUDRATE], 32);
  GetText(gp->hitem[EDIT_SERIAL_DBIT2],    ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_DATABIT], 4);
  GetText(gp->hitem[EDIT_SERIAL_SBIT2],    ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_STOPBIT], 4);
  GetText(gp->hitem[EDIT_SERIAL_PBIT2],    ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_PARITYBIT], 4);

  gp->pm->msrl[1].m.pfxMTIF[ONSERIALREAD] = SerialRead2;
  gp->pm->msrl[1].b[0] = 1;
  gp->pm->msrl[1].fd = mtifSerialOpen(&gp->pm->msrl[1].m, 
                                      ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_PORT],
                                      ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_BAUDRATE],
                                      ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_DATABIT],
                                      ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_STOPBIT],
                                      ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_PARITYBIT],"0", gp->pm->msrl[1].b, (void*)&gp->pm->msrl[1]);
  return (int)gp->pm->msrl[1].fd;
}

void SerialClose2()
{
  mtifSerialClose(&gp->pm->msrl[1].m, gp->pm->msrl[1].fd, gp->pm->msrl[1].b);
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




void wmtif_net_simul_write(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  char temp[32];
  GetText(gp->hitem[BUTTON_NET_OPEN_CLOSE], temp, 32);
  if ( strcmp(temp, STR_CLOSE) == 0 )
  {
    ChangeComboIndex(gp->hitem[COMBO_NET_DISPLAY_TYPE_W], 1);
    ChangeComboIndex(gp->hitem[COMBO_NET_DISPLAY_TYPE_R], 1);
    SocketWrite((char*)wparam, (int)lparam);
  }
}
void wmtif_ws_simul_write(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  char temp[32];
  GetText(gp->hitem[BUTTON_WS_OPEN_CLOSE], temp, 32);
  if ( strcmp(temp, STR_CLOSE) == 0 )
  {
    ChangeComboIndex(gp->hitem[COMBO_WS_DISPLAY_TYPE_W], 1);
    ChangeComboIndex(gp->hitem[COMBO_WS_DISPLAY_TYPE_R], 1);
    WebSocketWrite((char*)wparam, (int)lparam);
  }
}

void wmtif_serial_simul_write(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  char temp[32];
  GetText(gp->hitem[BUTTON_SERIAL_OPEN_CLOSE], temp, 32);
  if ( strcmp(temp, STR_CLOSE) == 0 )
  {
    ChangeComboIndex(gp->hitem[COMBO_SERIAL_DISPLAY_TYPE_W], 1);
    ChangeComboIndex(gp->hitem[COMBO_SERIAL_DISPLAY_TYPE_R], 1);
    SerialWrite((char*)wparam, (int)lparam);
  }
}



void wmtif_net_simul_request(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  char tmp[512];
  char sim[512];
  int e = 0;
  e = GetText(gp->hitem[EDIT_NET_WRITE], tmp, 512);
  if ( e > 0 )
  {
    tmp[e] = 0;
    e = hexsim(tmp, sim);
    sim[e] = 0;
    change_list_count();
    LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_NET_LOG], gp->max_line, &gp->log, "log", "%s", sim);
    wmtif_net_simul_write(hwnd, msg, sim, e);
  }
  else
  {
    SetText(gp->hitem[EDIT_NET_WRITE], "02 AA XX XX XX XX XX XX XX XX 03", 32);
  }
}

void wmtif_ws_simul_request(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  char tmp[512];
  char sim[512];
  int e = 0;
  e = GetText(gp->hitem[EDIT_WS_WRITE], tmp, 512);
  if ( e > 0 )
  {
    tmp[e] = 0;
    e = hexsim(tmp, sim);
    sim[e] = 0;
    change_list_count();
    LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_WS_LOG], gp->max_line, &gp->log, "log", "%s", sim);
    wmtif_ws_simul_write(hwnd, msg, sim, e);
  }
  else
  {
    SetText(gp->hitem[EDIT_WS_WRITE], "02 BB XX XX XX XX XX XX XX XX 03", 32);
  }
}

void wmtif_serial_simul_request(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  char tmp[512];
  char sim[512];
  int e = 0;
  e = GetText(gp->hitem[EDIT_SERIAL_WRITE], tmp, 512);
  if ( e > 0 )
  {
    tmp[e] = 0;
    e = hexsim(tmp, sim);
    sim[e] = 0;
    change_list_count();
    LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_SERIAL_LOG], gp->max_line, &gp->log, "log", "%s", sim);
    wmtif_serial_simul_write(hwnd, msg, sim, e);
  }
  else
  {
    SetText(gp->hitem[EDIT_SERIAL_WRITE], "02 CC XX XX XX XX XX XX XX XX 03", 32);
  }
}


void* on_simul_timer(void* hwnd, int msg, int id, int tm)
{
  PostMessage(hwnd, WMTIF_TIMER, MAKEWORD(id, 0), 0);
}





void fIDC_BUTTON_NET_OPEN_CLOSE(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  char temp[32];

  GetText(gp->hitem[BUTTON_NET_OPEN_CLOSE], temp, 32);
  if ( strcmp(temp, STR_OPEN) == 0 )
  {
    if ( SocketOpen()> 0 )
    {
      SetText(gp->hitem[BUTTON_NET_OPEN_CLOSE], STR_CLOSE, strlen(STR_CLOSE));
      change_list_count();
      LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_NET_LOG], gp->max_line, &gp->log, "log", "Socket", "Socket (%d) Open Success %s %s %s %s %s",
                              gp->pm->msck.fd,
                              ((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_IP],
                              ((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_PORT],
                              ((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_CSTYPE],
                              ((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_PROTO],
                              ((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_CASTTYPE]);
    }
    else
    {
      change_list_count();
      LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_NET_LOG], gp->max_line, &gp->log, "log", "Socket", "Socket (%d) Open Fail %s %s %s %s %s",
                              gp->pm->msck.fd,
                              ((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_IP],
                              ((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_PORT],
                              ((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_CSTYPE],
                              ((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_PROTO],
                              ((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_CASTTYPE]);
    }
  }
  else
  {
    SetText(gp->hitem[BUTTON_NET_OPEN_CLOSE], STR_OPEN, strlen(STR_OPEN));
    SocketClose();
    change_list_count();
    LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_NET_LOG], gp->max_line, &gp->log, "log", "Socket", "Socket (%d) Closed %s %s %s %s %s",
                            gp->pm->msck.fd,
                            ((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_IP],
                            ((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_PORT],
                            ((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_CSTYPE],
                            ((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_PROTO],
                            ((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_CASTTYPE]);
  }

}


void fIDC_BUTTON_WS_OPEN_CLOSE(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  char temp[32];
  GetText(gp->hitem[BUTTON_WS_OPEN_CLOSE], temp, 32);
  if ( strcmp(temp, STR_OPEN) == 0 )
  {
    if ( WebSocketOpen()> 0 )
    {
      SetText(gp->hitem[BUTTON_WS_OPEN_CLOSE], STR_CLOSE, strlen(STR_CLOSE));
      change_list_count();
      LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_WS_LOG], gp->max_line, &gp->log, "log", "WebSocket", "WebSocket Open SUCCESS");
    }
    else
    {
      change_list_count();
      LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_WS_LOG], gp->max_line, &gp->log, "log", "WebSocket", "WebSocket Open FAIL");
    }
  }
  else
  {
    SetText(gp->hitem[BUTTON_WS_OPEN_CLOSE], STR_OPEN, strlen(STR_OPEN));
    WebSocketClose();
    change_list_count();
    LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_WS_LOG], gp->max_line, &gp->log, "log", "WebSocket", "WebSocket Open SUCCESS");
  }
}


void fIDC_BUTTON_SERIAL_OPEN_CLOSE(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  char temp[32];

  GetText(gp->hitem[BUTTON_SERIAL_OPEN_CLOSE], temp, 32);
  if ( strcmp(temp, STR_OPEN) == 0 )
  {
    if ( SerialOpen()> 0 )
    {
      SetText(gp->hitem[BUTTON_SERIAL_OPEN_CLOSE], STR_CLOSE, strlen(STR_CLOSE));
      change_list_count();
      LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_SERIAL_LOG], gp->max_line, &gp->log, "log", "Serial #1", "Serial #1 (%d) Open Success %s %s %s %s %s",
                              gp->pm->msrl[0].fd,
                              ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_PORT],
                              ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_BAUDRATE],
                              ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_DATABIT],
                              ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_STOPBIT],
                              ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_PARITYBIT]);
    }
    else
    {
      change_list_count();
      LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_SERIAL_LOG], gp->max_line, &gp->log, "log", "Serial #1", "Serial #1 (%d) Open Fail %s %s %s %s %s",
                              gp->pm->msrl[0].fd,
                              ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_PORT],
                              ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_BAUDRATE],
                              ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_DATABIT],
                              ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_STOPBIT],
                              ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_PARITYBIT]);
    }
  }
  else
  {
    SetText(gp->hitem[BUTTON_SERIAL_OPEN_CLOSE], STR_OPEN, strlen(STR_OPEN));
    SerialClose();
    change_list_count();
    LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_SERIAL_LOG], gp->max_line, &gp->log, "log", "Serial #1", "Serial #1 (%d) Closed %s %s %s %s %s",
                            gp->pm->msrl[0].fd,
                            ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_PORT],
                            ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_BAUDRATE],
                            ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_DATABIT],
                            ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_STOPBIT],
                            ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_PARITYBIT]);
  }
}

void fIDC_BUTTON_SERIAL_OPEN_CLOSE2(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  char temp[32];

  GetText(gp->hitem[BUTTON_SERIAL_OPEN_CLOSE2], temp, 32);
  if ( strcmp(temp, STR_OPEN) == 0 )
  {
    if ( SerialOpen2()> 0 )
    {
      SetText(gp->hitem[BUTTON_SERIAL_OPEN_CLOSE2], STR_CLOSE, strlen(STR_CLOSE));
      change_list_count();
      LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_SERIAL_LOG2], gp->max_line, &gp->log, "log", "Serial #2", "Serial #2 (%d) Open Success %s %s %s %s %s",
                              gp->pm->msrl[1].fd,
                              ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_PORT],
                              ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_BAUDRATE],
                              ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_DATABIT],
                              ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_STOPBIT],
                              ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_PARITYBIT]);
    }
    else
    {
      change_list_count();
      LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_SERIAL_LOG2], gp->max_line, &gp->log, "log", "Serial #2", "Serial #2 (%d) Open Fail %s %s %s %s %s",
                              gp->pm->msrl[1].fd,
                              ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_PORT],
                              ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_BAUDRATE],
                              ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_DATABIT],
                              ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_STOPBIT],
                              ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_PARITYBIT]);
    }
  }
  else
  {
    SetText(gp->hitem[BUTTON_SERIAL_OPEN_CLOSE2], STR_OPEN, strlen(STR_OPEN));
    SerialClose2();
    change_list_count();
    LVLog(gp->hitem[LIST_READ], gp->hitem[CHECK_SERIAL_LOG2], gp->max_line, &gp->log, "log", "Serial #2", "Serial #2 (%d) Closed %s %s %s %s %s",
                            gp->pm->msrl[1].fd,
                            ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_PORT],
                            ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_BAUDRATE],
                            ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_DATABIT],
                            ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_STOPBIT],
                            ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_PARITYBIT]);
  }
}


void wmtif_command(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  char tmp[32];
  switch(LOWORD(wparam))
  {
    case IDC_BUTTON_NET_OPEN_CLOSE:
      fIDC_BUTTON_NET_OPEN_CLOSE(hwnd, msg, wparam, lparam);
      break;

    case IDC_BUTTON_WS_OPEN_CLOSE:
      fIDC_BUTTON_WS_OPEN_CLOSE(hwnd, msg, wparam, lparam);
      break;

    case IDC_BUTTON_SERIAL_OPEN_CLOSE:
      fIDC_BUTTON_SERIAL_OPEN_CLOSE(hwnd, msg, wparam, lparam);
      break;

    case IDC_BUTTON_SERIAL_OPEN_CLOSE2:
      fIDC_BUTTON_SERIAL_OPEN_CLOSE2(hwnd, msg, wparam, lparam);
      break;

    case IDC_BUTTON_NET_WRITE:
      SocketWrite(0,0);
      break;

    case IDC_BUTTON_WS_WRITE:
      WebSocketWrite(0,0);
      break;

    case IDC_BUTTON_SERIAL_WRITE:
      SerialWrite(0, 0);
      break;

    case IDC_BUTTON_SERIAL_WRITE2:
      SerialWrite2(0, 0);
      break;

    case IDC_BUTTON_CLEAR:
      ClearListView(gp->hitem[LIST_READ]);
      break;

    case IDC_CHECK_READ_YN:
      if ( SendMessage(gp->hitem[CHECK_READ_YN], BM_GETCHECK, 0, 0) == BST_CHECKED )
      {
        gp->read_lock = 0x01;
      }
      else
      {
        gp->read_lock = 0x00;
      }
      break;

    case IDC_CHECK_NET_SIMULA:
      GetText(gp->hitem[EDIT_NET_MSEC], tmp, 32);
      if ( SendMessage(gp->hitem[CHECK_NET_SIMUL], BM_GETCHECK, 0, 0) == BST_CHECKED )
      {
        set_timer(hwnd, WMTIF_NET_SIMUL_TIMER, atoi(tmp), on_simul_timer);
      }
      else
      {
        kill_timer(hwnd, WMTIF_NET_SIMUL_TIMER);
      }
      break;

    case IDC_CHECK_WS_SIMULA:
      GetText(gp->hitem[EDIT_WS_MSEC], tmp, 32);
      if ( SendMessage(gp->hitem[CHECK_WS_SIMUL], BM_GETCHECK, 0, 0) == BST_CHECKED )
      {
        set_timer(hwnd, WMTIF_WS_SIMUL_TIMER, atoi(tmp), on_simul_timer);
      }
      else
      {
        kill_timer(hwnd, WMTIF_WS_SIMUL_TIMER);
      }
      break;
    case IDC_CHECK_SERIAL_SIMULA:
      GetText(gp->hitem[EDIT_SERIAL_MSEC], tmp, 32);
      if ( SendMessage(gp->hitem[CHECK_SERIAL_SIMUL], BM_GETCHECK, 0, 0) == BST_CHECKED )
      {
        set_timer(hwnd, WMTIF_SERIAL_SIMUL_TIMER, atoi(tmp), on_simul_timer);
      }
      else
      {
        kill_timer(hwnd, WMTIF_SERIAL_SIMUL_TIMER);
      }
      break;



  }    
}

void wmtif_timer(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  switch(LOWORD(wparam))
  {
    case WMTIF_NET_SIMUL_TIMER:
      wmtif_net_simul_request(hwnd, msg, wparam, lparam);
      break;
    case WMTIF_WS_SIMUL_TIMER:
      wmtif_ws_simul_request(hwnd, msg, wparam, lparam);
      break;
    case WMTIF_SERIAL_SIMUL_TIMER:
      wmtif_serial_simul_request(hwnd, msg, wparam, lparam);
      break;
  }

}


void* wmtif_dlgproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  switch(msg)
  {

  #if 0
    case WM_COMMAND:
      wmtif_command(hwnd, msg, wparam, lparam);
      break;
    case WMTIF_TIMER:
      wmtif_timer(hwnd, msg, wparam, lparam);
      break;
    default:
      break;    
  #endif
  }

  return 0;
}


void* wmtif_init(HWND hwnd, wMTIF* p)
{
  int e = 0;

  gp = p;

  gp->hitem[EDIT_NET_IP] = GetDlgItem(hwnd, IDC_EDIT_NET_IP);
  gp->hitem[EDIT_NET_PORT] = GetDlgItem(hwnd, IDC_EDIT_NET_PORT);
  gp->hitem[COMBO_NET_PROTOCOL] = GetDlgItem(hwnd, IDC_COMBO_NET_PROTOCOL);
  gp->hitem[COMBO_NET_CS] = GetDlgItem(hwnd, IDC_COMBO_NET_CS);
  gp->hitem[COMBO_NET_CASTTYPE] = GetDlgItem(hwnd, IDC_COMBO_NET_CASTTYPE);
  gp->hitem[BUTTON_NET_OPEN_CLOSE] = GetDlgItem(hwnd, IDC_BUTTON_NET_OPEN_CLOSE);
  gp->hitem[EDIT_NET_WRITE] = GetDlgItem(hwnd, IDC_EDIT_NET_WRITE);
  gp->hitem[BUTTON_NET_WRITE] = GetDlgItem(hwnd, IDC_BUTTON_NET_WRITE);
  gp->hitem[CHECK_NET_CR] = GetDlgItem(hwnd, IDC_CHECK_NET_CR);
  gp->hitem[CHECK_NET_LF] = GetDlgItem(hwnd, IDC_CHECK_NET_LF);
  gp->hitem[COMBO_NET_DISPLAY_TYPE_W] = GetDlgItem(hwnd, IDC_COMBO_NET_DISPLAY_TYPE_W);
  gp->hitem[COMBO_NET_DISPLAY_TYPE_R] = GetDlgItem(hwnd, IDC_COMBO_NET_DISPLAY_TYPE_R);
  gp->hitem[EDIT_SERIAL_PORT] = GetDlgItem(hwnd, IDC_EDIT_SERIAL_PORT);
  gp->hitem[EDIT_SERIAL_BAUDRATE] = GetDlgItem(hwnd, IDC_EDIT_SERIAL_BAUD);
  gp->hitem[EDIT_SERIAL_DBIT] = GetDlgItem(hwnd, IDC_EDIT_SERIAL_DBIT);
  gp->hitem[EDIT_SERIAL_SBIT] = GetDlgItem(hwnd, IDC_EDIT_SERIAL_SBIT);
  gp->hitem[EDIT_SERIAL_PBIT] = GetDlgItem(hwnd, IDC_EDIT_SERIAL_PBIT);
  gp->hitem[BUTTON_SERIAL_OPEN_CLOSE] = GetDlgItem(hwnd, IDC_BUTTON_SERIAL_OPEN_CLOSE);
  gp->hitem[COMBO_SERIAL_DISPLAY_TYPE_R] = GetDlgItem(hwnd, IDC_COMBO_SERIAL_DISPLAY_TYPE_R);
  gp->hitem[COMBO_SERIAL_DISPLAY_TYPE_W] = GetDlgItem(hwnd, IDC_COMBO_SERIAL_DISPLAY_TYPE_W);
  gp->hitem[EDIT_SERIAL_WRITE] = GetDlgItem(hwnd, IDC_EDIT_SERIAL_WRITE);
  gp->hitem[BUTTON_SERIAL_WRITE] = GetDlgItem(hwnd, IDC_BUTTON_SERIAL_WRITE);
  gp->hitem[CHECK_SERIAL_CR] = GetDlgItem(hwnd, IDC_CHECK_SERIAL_CR);
  gp->hitem[CHECK_SERIAL_LF] = GetDlgItem(hwnd, IDC_CHECK_SERIAL_LF);
  gp->hitem[CHECK_SERIAL_ROUTER] = GetDlgItem(hwnd, IDC_CHECK_SERIAL_ROUTER);
  gp->hitem[EDIT_SERIAL_PORT2] = GetDlgItem(hwnd, IDC_EDIT_SERIAL_PORT2);
  gp->hitem[EDIT_SERIAL_BAUDRATE2] = GetDlgItem(hwnd, IDC_EDIT_SERIAL_BAUD2);
  gp->hitem[EDIT_SERIAL_DBIT2] = GetDlgItem(hwnd, IDC_EDIT_SERIAL_DBIT2);
  gp->hitem[EDIT_SERIAL_SBIT2] = GetDlgItem(hwnd, IDC_EDIT_SERIAL_SBIT2);
  gp->hitem[EDIT_SERIAL_PBIT2] = GetDlgItem(hwnd, IDC_EDIT_SERIAL_PBIT2);
  gp->hitem[BUTTON_SERIAL_OPEN_CLOSE2] = GetDlgItem(hwnd, IDC_BUTTON_SERIAL_OPEN_CLOSE2);
  gp->hitem[COMBO_SERIAL_DISPLAY_TYPE_R2] = GetDlgItem(hwnd, IDC_COMBO_SERIAL_DISPLAY_TYPE_R2);
  gp->hitem[COMBO_SERIAL_DISPLAY_TYPE_W2] = GetDlgItem(hwnd, IDC_COMBO_SERIAL_DISPLAY_TYPE_W2);
  gp->hitem[EDIT_SERIAL_WRITE2] = GetDlgItem(hwnd, IDC_EDIT_SERIAL_WRITE2);
  gp->hitem[BUTTON_SERIAL_WRITE2] = GetDlgItem(hwnd, IDC_BUTTON_SERIAL_WRITE2);
  gp->hitem[CHECK_SERIAL_CR2] = GetDlgItem(hwnd, IDC_CHECK_SERIAL_CR2);
  gp->hitem[CHECK_SERIAL_LF2] = GetDlgItem(hwnd, IDC_CHECK_SERIAL_LF2);
  gp->hitem[LIST_READ] = GetDlgItem(hwnd, IDC_LIST_READ);
  gp->hitem[CHECK_READ_YN] = GetDlgItem(hwnd, IDC_CHECK_READ_YN);
  gp->hitem[BUTTON_CLEAR] = GetDlgItem(hwnd, IDC_BUTTON_CLEAR);
  gp->hitem[COMBO_WS_CS] = GetDlgItem(hwnd, IDC_COMBO_WS_CS);
  gp->hitem[EDIT_WS_URL] = GetDlgItem(hwnd, IDC_EDIT_WS_URL);
  gp->hitem[COMBO_WS_DISPLAY_TYPE_W] = GetDlgItem(hwnd, IDC_COMBO_WS_DISPLAY_TYPE_W);
  gp->hitem[COMBO_WS_DISPLAY_TYPE_R] = GetDlgItem(hwnd, IDC_COMBO_WS_DISPLAY_TYPE_R);
  gp->hitem[BUTTON_WS_OPEN_CLOSE] = GetDlgItem(hwnd, IDC_BUTTON_WS_OPEN_CLOSE);
	gp->hitem[EDIT_WS_WRITE] = GetDlgItem(hwnd, IDC_EDIT_WS_WRITE);
	gp->hitem[CHECK_WS_CR] = GetDlgItem(hwnd, IDC_CHECK_WS_CR);
	gp->hitem[CHECK_WS_LF] = GetDlgItem(hwnd, IDC_CHECK_WS_LF);
	gp->hitem[BUTTON_WS_WRITE] = GetDlgItem(hwnd, IDC_BUTTON_WS_WRITE);
  gp->hitem[CHECK_NET_LOG] = GetDlgItem(hwnd, IDC_CHECK_NET_LOG);
  gp->hitem[CHECK_WS_LOG] = GetDlgItem(hwnd, IDC_CHECK_WS_LOG);
  gp->hitem[CHECK_SERIAL_LOG] = GetDlgItem(hwnd, IDC_CHECK_SERIAL_LOG);
  gp->hitem[CHECK_SERIAL_LOG2] = GetDlgItem(hwnd, IDC_CHECK_SERIAL_LOG2);
  gp->hitem[CHECK_NET_ECHO] = GetDlgItem(hwnd, IDC_CHECK_NET_ECHO);
  gp->hitem[CHECK_WS_ECHO] = GetDlgItem(hwnd, IDC_CHECK_WS_ECHO);
  gp->hitem[CHECK_SERIAL_ECHO] = GetDlgItem(hwnd, IDC_CHECK_SERIAL_ECHO);
  gp->hitem[CHECK_SERIAL_ECHO2] = GetDlgItem(hwnd, IDC_CHECK_SERIAL_ECHO2);
  gp->hitem[EDIT_SERIAL_MSEC] = GetDlgItem(hwnd, IDC_EDIT_SERIAL_MSEC);
  gp->hitem[CHECK_SERIAL_SIMUL] = GetDlgItem(hwnd, IDC_CHECK_SERIAL_SIMULA);
  gp->hitem[CHECK_NET_SIMUL] = GetDlgItem(hwnd, IDC_CHECK_NET_SIMULA);
  gp->hitem[CHECK_WS_SIMUL] = GetDlgItem(hwnd, IDC_CHECK_WS_SIMULA);
  gp->hitem[CHECK_NET_STX] = GetDlgItem(hwnd, IDC_CHECK_NET_STX);
  gp->hitem[CHECK_NET_ETX] = GetDlgItem(hwnd, IDC_CHECK_NET_ETX);
  gp->hitem[CHECK_WS_STX] = GetDlgItem(hwnd, IDC_CHECK_WS_STX);
  gp->hitem[CHECK_WS_ETX] = GetDlgItem(hwnd, IDC_CHECK_WS_ETX);
  gp->hitem[CHECK_SERIAL_STX] = GetDlgItem(hwnd, IDC_CHECK_SERIAL_STX);
  gp->hitem[CHECK_SERIAL_ETX] = GetDlgItem(hwnd, IDC_CHECK_SERIAL_ETX);
  gp->hitem[CHECK_SERIAL_STX2] = GetDlgItem(hwnd, IDC_CHECK_SERIAL_STX2);
  gp->hitem[CHECK_SERIAL_ETX2] = GetDlgItem(hwnd, IDC_CHECK_SERIAL_ETX2);
  gp->hitem[EDIT_NET_MSEC] = GetDlgItem(hwnd, IDC_EDIT_NET_MSEC);
  gp->hitem[EDIT_WS_MSEC] = GetDlgItem(hwnd, IDC_EDIT_WS_MSEC);
  gp->hitem[EDIT_LIST_COUNT] = GetDlgItem(hwnd, IDC_EDIT_LIST_COUNT);


  SetText(gp->hitem[EDIT_NET_IP], "127.0.0.1", strlen("127.0.0.1"));
  SetText(gp->hitem[EDIT_NET_PORT], "7810", strlen("7810"));
  SetText(gp->hitem[BUTTON_NET_WRITE], "SEND", strlen("SEND"));
  SetText(gp->hitem[BUTTON_NET_OPEN_CLOSE], STR_OPEN, strlen(STR_OPEN));
  SetText(gp->hitem[BUTTON_SERIAL_WRITE], "WRITE", strlen("WRITE"));
  SetText(gp->hitem[BUTTON_WS_OPEN_CLOSE], STR_OPEN, strlen(STR_OPEN));
  SetText(gp->hitem[BUTTON_CLEAR], "CLEAR", strlen("CLEAR"));
  SetText(gp->hitem[EDIT_WS_URL], "http://127.0.0.1:7810/", strlen("http://127.0.0.1:7810/"));
  SetText(gp->hitem[BUTTON_WS_OPEN_CLOSE], STR_OPEN, strlen(STR_OPEN));
  SetText(gp->hitem[BUTTON_WS_WRITE], "SEND", strlen("SEND"));

  ResetText(gp->hitem[EDIT_SERIAL_PORT], "COM1");
  ResetText(gp->hitem[EDIT_SERIAL_BAUDRATE], "115200");
  ResetText(gp->hitem[EDIT_SERIAL_DBIT], "8");
  ResetText(gp->hitem[EDIT_SERIAL_SBIT], "1");
  ResetText(gp->hitem[EDIT_SERIAL_PBIT], "0");

  ResetText(gp->hitem[EDIT_SERIAL_PORT2], "COM2");
  ResetText(gp->hitem[EDIT_SERIAL_BAUDRATE2], "115200");
  ResetText(gp->hitem[EDIT_SERIAL_DBIT2], "8");
  ResetText(gp->hitem[EDIT_SERIAL_SBIT2], "1");
  ResetText(gp->hitem[EDIT_SERIAL_PBIT2], "0");


  ResetText(gp->hitem[EDIT_NET_MSEC], "1000");
  ResetText(gp->hitem[EDIT_WS_MSEC], "1000");
  ResetText(gp->hitem[EDIT_SERIAL_MSEC], "1000");

  ResetText(gp->hitem[EDIT_LIST_COUNT], "2000");

  SendMessage(gp->hitem[COMBO_NET_PROTOCOL], CB_ADDSTRING, 0, (LPARAM)"TCP");
  SendMessage(gp->hitem[COMBO_NET_PROTOCOL], CB_ADDSTRING, 0, (LPARAM)"UDP");
  SendMessage(gp->hitem[COMBO_NET_PROTOCOL], CB_SETCURSEL, 0, 0 );

  SendMessage(gp->hitem[COMBO_NET_CS], CB_ADDSTRING, 0, (LPARAM)"SERVER");
  SendMessage(gp->hitem[COMBO_NET_CS], CB_ADDSTRING, 0, (LPARAM)"CLIENT");
  SendMessage(gp->hitem[COMBO_NET_CS], CB_SETCURSEL, 0, 0 );

  SendMessage(gp->hitem[COMBO_WS_CS], CB_ADDSTRING, 0, (LPARAM)"SERVER");
  SendMessage(gp->hitem[COMBO_WS_CS], CB_ADDSTRING, 0, (LPARAM)"CLIENT");
  SendMessage(gp->hitem[COMBO_WS_CS], CB_SETCURSEL, 0, 0 );

  SendMessage(gp->hitem[COMBO_NET_CASTTYPE], CB_ADDSTRING, 0, (LPARAM)"UNICAST");
  SendMessage(gp->hitem[COMBO_NET_CASTTYPE], CB_ADDSTRING, 0, (LPARAM)"BROADCAST");
  SendMessage(gp->hitem[COMBO_NET_CASTTYPE], CB_ADDSTRING, 0, (LPARAM)"MULTICAST");
  SendMessage(gp->hitem[COMBO_NET_CASTTYPE], CB_SETCURSEL, 0, 0 );

	SendMessage(gp->hitem[COMBO_NET_DISPLAY_TYPE_W], CB_ADDSTRING, 0, (LPARAM)"ASCII");
	SendMessage(gp->hitem[COMBO_NET_DISPLAY_TYPE_W], CB_ADDSTRING, 0, (LPARAM)"HEX");
  SendMessage(gp->hitem[COMBO_NET_DISPLAY_TYPE_W], CB_SETCURSEL, 0, 0 );

	SendMessage(gp->hitem[COMBO_NET_DISPLAY_TYPE_R], CB_ADDSTRING, 0, (LPARAM)"ASCII");
	SendMessage(gp->hitem[COMBO_NET_DISPLAY_TYPE_R], CB_ADDSTRING, 0, (LPARAM)"HEX");
  SendMessage(gp->hitem[COMBO_NET_DISPLAY_TYPE_R], CB_SETCURSEL, 0, 0 );

	SendMessage(gp->hitem[COMBO_WS_DISPLAY_TYPE_W], CB_ADDSTRING, 0, (LPARAM)"ASCII");
	SendMessage(gp->hitem[COMBO_WS_DISPLAY_TYPE_W], CB_ADDSTRING, 0, (LPARAM)"HEX");
  SendMessage(gp->hitem[COMBO_WS_DISPLAY_TYPE_W], CB_SETCURSEL, 0, 0 );

	SendMessage(gp->hitem[COMBO_WS_DISPLAY_TYPE_R], CB_ADDSTRING, 0, (LPARAM)"ASCII");
	SendMessage(gp->hitem[COMBO_WS_DISPLAY_TYPE_R], CB_ADDSTRING, 0, (LPARAM)"HEX");
  SendMessage(gp->hitem[COMBO_WS_DISPLAY_TYPE_R], CB_SETCURSEL, 0, 0 );

	SendMessage(gp->hitem[COMBO_SERIAL_DISPLAY_TYPE_W], CB_ADDSTRING, 0, (LPARAM)"ASCII");
	SendMessage(gp->hitem[COMBO_SERIAL_DISPLAY_TYPE_W], CB_ADDSTRING, 0, (LPARAM)"HEX");
  SendMessage(gp->hitem[COMBO_SERIAL_DISPLAY_TYPE_W], CB_SETCURSEL, 0, 0 );

	SendMessage(gp->hitem[COMBO_SERIAL_DISPLAY_TYPE_R], CB_ADDSTRING, 0, (LPARAM)"ASCII");
	SendMessage(gp->hitem[COMBO_SERIAL_DISPLAY_TYPE_R], CB_ADDSTRING, 0, (LPARAM)"HEX");
  SendMessage(gp->hitem[COMBO_SERIAL_DISPLAY_TYPE_R], CB_SETCURSEL, 0, 0 );

	SendMessage(gp->hitem[COMBO_SERIAL_DISPLAY_TYPE_W2], CB_ADDSTRING, 0, (LPARAM)"ASCII");
	SendMessage(gp->hitem[COMBO_SERIAL_DISPLAY_TYPE_W2], CB_ADDSTRING, 0, (LPARAM)"HEX");
  SendMessage(gp->hitem[COMBO_SERIAL_DISPLAY_TYPE_W2], CB_SETCURSEL, 0, 0 );

	SendMessage(gp->hitem[COMBO_SERIAL_DISPLAY_TYPE_R2], CB_ADDSTRING, 0, (LPARAM)"ASCII");
	SendMessage(gp->hitem[COMBO_SERIAL_DISPLAY_TYPE_R2], CB_ADDSTRING, 0, (LPARAM)"HEX");
  SendMessage(gp->hitem[COMBO_SERIAL_DISPLAY_TYPE_R2], CB_SETCURSEL, 0, 0 );


  InitListView(gp->hitem[LIST_READ]);
  return 0;
}
#endif


void* setClient(int32_t fd)
{
  int32_t i = 0;

  for ( i=0 ; i<MAX_CLIENT ; i++ )
  {
    if ( gp->__socket.fds[i] <= 0 )
    {
      gp->__socket.fds[i] = fd;
      break;
    }
  }
  return 0;
}

void* resetClient(int32_t fd)
{
  int32_t i = 0;

  for ( i=0 ; i<MAX_CLIENT ; i++ )
  {
    if ( gp->__socket.fds[i] == fd )
    {
      gp->__socket.fds[i] = 0;
      break;
    }
  }
  return 0;
}



void* __websocketConnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnwebsocket* p = (cnwebsocket*)o;
  int32_t idx = (extra==0)?0:(*(int32_t*)extra);

  LVLog(gp->item[_IDC_LIST_READ].hwnd, 0, 0, "log", "websocket", "websocket (%d) connected(%d)", fd, idx);

  if ( gp->__websocket.io.argv[3][0] == 'S' )
  {
    //setClient(fd);
  }
  return 0;
}

void* __websocketDisconnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnwebsocket* p = (cnwebsocket*)o;
  LVLog(gp->item[_IDC_LIST_READ].hwnd, 0, 0, "log", "websocket", "websocket (%d) disonnected", fd);

  if ( gp->__websocket.io.argv[3][0] == 'S' )
  {
    //resetClient(fd);
  }

  return 0;
}


void* __websocketRead(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnwebsocket* p = (cnwebsocket*)o;
  int32_t e = 0;
  int32_t s = 0;
  uint8_t temp[1024] = {0};

  s = GetComboText(gp->item[_IDC_COMBO_WS_DISPLAY_TYPE_R].hwnd, temp);
  if ( temp[0] == 'H' )
  {
    s = ascii_to_hex(b, temp);
    LVLog(gp->item[_IDC_LIST_READ].hwnd, 0, 0, "log", "websocket", "websocket (%d) read - %s", fd, temp);
  }
  else
  {
    LVLog(gp->item[_IDC_LIST_READ].hwnd, 0, 0, "log", "websocket", "websocket (%d) read - %s", fd, b);
  }

  return 0;
}

void* __socketConnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnsocket* p = (cnsocket*)o;
  int32_t idx = (extra==0)?0:(*(int32_t*)extra);

  LVLog(gp->item[_IDC_LIST_READ].hwnd, 0, 0, "log", "socket", "socket (%d) connected(%d)", fd, idx);

  if ( gp->__socket.io.argv[3][0] == 'S' )
  {
    setClient(fd);
  }
  return 0;
}

void* __socketDisconnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnsocket* p = (cnsocket*)o;
  LVLog(gp->item[_IDC_LIST_READ].hwnd, 0, 0, "log", "socket", "socket (%d) disonnected", fd);

  if ( gp->__socket.io.argv[3][0] == 'S' )
  {
    resetClient(fd);
  }

  return 0;
}


void* __socketRead(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnsocket* p = (cnsocket*)o;
  int32_t e = 0;
  int32_t s = 0;
  uint8_t temp[1024] = {0};

  s = GetComboText(gp->item[_IDC_COMBO_NET_DISPLAY_TYPE_R].hwnd, temp);
  if ( temp[0] == 'H' )
  {

    s = hexasc(temp, b, sz);
    LVLog(gp->item[_IDC_LIST_READ].hwnd, 0, 0, "log", "socket", "socket (%d) read - %s", fd, temp);
  }
  else
  {
    LVLog(gp->item[_IDC_LIST_READ].hwnd, 0, 0, "log", "socket", "socket (%d) read - %s", fd, b);
  }

  return 0;
}

void* __serialConnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnsocket* p = (cnsocket*)o;
  int32_t idx = (extra==0)?0:(*(int32_t*)extra);

  LVLog(gp->item[_IDC_LIST_READ].hwnd, 0, 0, "log", "serial", "socket (%d) connected(%d)", fd, idx);
  return 0;
}

void* __serialDisconnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnsocket* p = (cnsocket*)o;
  LVLog(gp->item[_IDC_LIST_READ].hwnd, 0, 0, "log", "serial", "socket (%d) disonnected", fd);

  return 0;
}


void* __serialRead(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnsocket* p = (cnsocket*)o;
  uint8_t temp[1024] = {0};
  int32_t s = 0;
  
  GetText(gp->item[_IDC_COMBO_SERIAL_DISPLAY_TYPE_R].hwnd, temp, 32);

  if ( temp[0] == 'A' )
  {
    LVLog(gp->item[_IDC_LIST_READ].hwnd, 0, 0, "log", "serial", "socket (%d) read (%d)- %s", fd, sz, b);
  }
  else
  {
    memset(temp, 0, 32);
    s = ascii_to_hex(b, temp);
    LVLog(gp->item[_IDC_LIST_READ].hwnd, 0, 0, "log", "serial", "socket (%d) read (%d)- %s", fd, s, temp);
  }  

  return 0;
}


void* wmtif_IDC_BUTTON_NET_WRITE(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int32_t i = 0;
  int32_t e = 0;
  int32_t s = 0;
  uint8_t temp[1024] = {0};
  uint8_t tmp[1024] = {0};

  s = GetText(gp->item[_IDC_EDIT_NET_WRITE].hwnd, temp, 1024);
  GetText(gp->item[_IDC_COMBO_NET_DISPLAY_TYPE_W].hwnd, tmp, 32);

  if ( gp->__socket.io.argv[3][0] == 'C' )
  {
    if ( tmp[0] == 'A' )
    {
      e = nsocket_write(&gp->__socket, gp->__socket.io.fd, temp, s, 0, &gp->__socket);
    }
    else
    {
      s = ascii_to_hex(temp, tmp);
      e = nsocket_write(&gp->__socket, gp->__socket.io.fd, tmp, s, 0, &gp->__socket);
    }  
  }
  else
  {
    if ( tmp[0] == 'A' )
    {
      for ( i=0 ; i<MAX_CLIENT ; i++ )
      {
        if ( gp->__socket.fds[i] >= 0 )
        {
          e = nsocket_write(&gp->__socket, gp->__socket.fds[i], temp, s, 0, &gp->__socket);
        }
      }
    }
    else
    {
      s = ascii_to_hex(temp, tmp);
      for ( i=0 ; i<MAX_CLIENT ; i++ )
      {
        if ( gp->__socket.fds[i] >= 0 )
        {
          e = nsocket_write(&gp->__socket, gp->__socket.fds[i], tmp, s, 0, &gp->__socket);
        }
      }

    }
  }

  return e;
}




void* wmtif_IDC_BUTTON_NET_OPEN_CLOSE(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  wchar_t tmp[64] = {0};
  uint8_t temp[32] = {0};
  int32_t e = 0;

  GetText(gp->item[_IDC_BUTTON_NET_OPEN_CLOSE].hwnd, temp, 32);
  e = GetText(gp->item[_IDC_EDIT_NET_IP].hwnd, gp->__socket.io.argv[0], 32);
  e = GetText(gp->item[_IDC_EDIT_NET_PORT].hwnd, gp->__socket.io.argv[1], 32);
  e = GetComboText(gp->item[_IDC_COMBO_NET_PROTOCOL].hwnd, gp->__socket.io.argv[2]);
  e = GetComboText(gp->item[_IDC_COMBO_NET_CS].hwnd, gp->__socket.io.argv[3]);
  e = GetComboText(gp->item[_IDC_COMBO_NET_CASTTYPE].hwnd, gp->__socket.io.argv[4]);
  if ( strcmp(temp, STR_OPEN) == 0 )
  {
    gp->__socket.io.fd = e = nsocket_open(&gp->__socket);
    if ( e > 0 )
    {
      gp->__socket.io.__f[IMTIF_CALLBACK_CONNECTED] = __socketConnected;
      gp->__socket.io.__f[IMTIF_CALLBACK_DISCONNECTED] = __socketDisconnected;
      gp->__socket.io.__f[IMTIF_CALLBACK_READ] = __socketRead;
      SetText(gp->item[_IDC_BUTTON_NET_OPEN_CLOSE].hwnd, STR_CLOSE, strlen(STR_CLOSE));
      LVLog(gp->item[_IDC_LIST_READ].hwnd, 0, 0, "log", "socket", "socket (%d) open success %s %s %s %s %s",
                              gp->__socket.io.fd,
                              gp->__socket.io.argv[0],
                              gp->__socket.io.argv[1],
                              gp->__socket.io.argv[2],
                              gp->__socket.io.argv[3],
                              gp->__socket.io.argv[4]);
    }
    else
    {
      LVLog(gp->item[_IDC_LIST_READ].hwnd, 0, 0, "log", "socket", "socket (%d) open fail %s %s %s %s %s",
                              gp->__socket.io.fd,
                              gp->__socket.io.argv[0],
                              gp->__socket.io.argv[1],
                              gp->__socket.io.argv[2],
                              gp->__socket.io.argv[3],
                              gp->__socket.io.argv[4]);
      gp->__socket.io.__f[IMTIF_CALLBACK_CONNECTED] = 0;
      gp->__socket.io.__f[IMTIF_CALLBACK_DISCONNECTED] = 0;
      gp->__socket.io.__f[IMTIF_CALLBACK_READ] = 0;
    }
  }
  else
  {

    nsocket_close(&gp->__socket);
    SetText(gp->item[_IDC_BUTTON_NET_OPEN_CLOSE].hwnd, STR_OPEN, strlen(STR_OPEN));
    LVLog(gp->item[_IDC_LIST_READ].hwnd, 0, 0, "log", "socket", "socket (%d) close success %s %s %s %s %s",
                            gp->__socket.io.fd,
                            gp->__socket.io.argv[0],
                            gp->__socket.io.argv[1],
                            gp->__socket.io.argv[2],
                            gp->__socket.io.argv[3],
                            gp->__socket.io.argv[4]);

    gp->__socket.io.__f[IMTIF_CALLBACK_CONNECTED] = 0;
    gp->__socket.io.__f[IMTIF_CALLBACK_DISCONNECTED] = 0;
    gp->__socket.io.__f[IMTIF_CALLBACK_READ] = 0;
  }

  return e;
}


void* wmtif_IDC_BUTTON_WS_OPEN_CLOSE(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  wchar_t tmp[64] = {0};
  uint8_t temp[32] = {0};
  int32_t e = 0;

  GetText(gp->item[_IDC_BUTTON_WS_OPEN_CLOSE].hwnd, temp, 32);
  e = GetText(gp->item[_IDC_EDIT_WS_URL].hwnd, gp->__websocket.io.argv[0], 32);
  if ( strcmp(temp, STR_OPEN) == 0 )
  {
    gp->__websocket.io.fd = e = nwebsocket_open(&gp->__websocket);
    if ( e > 0 )
    {
      gp->__websocket.io.__f[IMTIF_CALLBACK_CONNECTED] = __websocketConnected;
      gp->__websocket.io.__f[IMTIF_CALLBACK_DISCONNECTED] = __websocketDisconnected;
      gp->__websocket.io.__f[IMTIF_CALLBACK_READ] = __websocketRead;
      SetText(gp->item[_IDC_BUTTON_NET_OPEN_CLOSE].hwnd, STR_CLOSE, strlen(STR_CLOSE));
      LVLog(gp->item[_IDC_LIST_READ].hwnd, 0, 0, "log", "websocket", "websocket (%d) open success %s",
                              gp->__websocket.io.fd,
                              gp->__websocket.io.argv[0]);
    }
    else
    {
      LVLog(gp->item[_IDC_LIST_READ].hwnd, 0, 0, "log", "websocket", "websocket (%d) open fail %s",
                              gp->__websocket.io.fd,
                              gp->__websocket.io.argv[0]);
      gp->__websocket.io.__f[IMTIF_CALLBACK_CONNECTED] = 0;
      gp->__websocket.io.__f[IMTIF_CALLBACK_DISCONNECTED] = 0;
      gp->__websocket.io.__f[IMTIF_CALLBACK_READ] = 0;
    }
  }
  else
  {

    nwebsocket_close(&gp->__websocket);
    SetText(gp->item[_IDC_BUTTON_WS_OPEN_CLOSE].hwnd, STR_OPEN, strlen(STR_OPEN));
    LVLog(gp->item[_IDC_LIST_READ].hwnd, 0, 0, "log", "websocket", "websocket (%d) close success %s",
                            gp->__socket.io.fd,
                            gp->__socket.io.argv[0]);

    gp->__websocket.io.__f[IMTIF_CALLBACK_CONNECTED] = 0;
    gp->__websocket.io.__f[IMTIF_CALLBACK_DISCONNECTED] = 0;
    gp->__websocket.io.__f[IMTIF_CALLBACK_READ] = 0;
  }

  return e;
}




void* wmtif_IDC_BUTTON_SERIAL_WRITE(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int32_t e = 0;
  int32_t s = 0;
  uint8_t temp[1024] = {0};
  uint8_t tmp[1024] = {0};

  s = GetText(gp->item[_IDC_EDIT_SERIAL_WRITE].hwnd, temp, 1024);
  GetText(gp->item[_IDC_COMBO_SERIAL_DISPLAY_TYPE_W].hwnd, tmp, 32);

  if ( tmp[0] == 'A' )
  {
    e = nserial_write(&gp->__serial[0], gp->__serial[0].io.fd, temp, s, 0, &gp->__serial[0]);
  }
  else
  {
    s = ascii_to_hex(temp, tmp);
    e = nserial_write(&gp->__serial[0], gp->__serial[0].io.fd, tmp, s, 0, &gp->__serial[0]);
  }

  return e;
}



void* wmtif_IDC_BUTTON_SERIAL_OPEN_CLOSE(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  uint8_t temp[32] = {0};
  int32_t e = 0;

  GetText(gp->item[_IDC_EDIT_SERIAL_PORT].hwnd,     gp->__serial[0].io.argv[0], 32);
  GetText(gp->item[_IDC_EDIT_SERIAL_BAUDRATE].hwnd, gp->__serial[0].io.argv[1], 32);
  GetText(gp->item[_IDC_EDIT_SERIAL_DBIT].hwnd,     gp->__serial[0].io.argv[2], 32);
  GetText(gp->item[_IDC_EDIT_SERIAL_SBIT].hwnd,     gp->__serial[0].io.argv[3], 32);
  GetText(gp->item[_IDC_EDIT_SERIAL_PBIT].hwnd,     gp->__serial[0].io.argv[4], 32);
  GetText(gp->item[_IDC_BUTTON_SERIAL_OPEN_CLOSE].hwnd, temp, 32);
  if ( strcmp(temp, STR_OPEN) == 0 )
  {
    gp->__serial[0].io.__f[IMTIF_CALLBACK_CONNECTED] = __serialConnected;
    gp->__serial[0].io.__f[IMTIF_CALLBACK_DISCONNECTED] = __serialDisconnected;
    gp->__serial[0].io.__f[IMTIF_CALLBACK_READ] = __serialRead;
    e = nserial_open(&gp->__serial[0]);
    if ( e > 0 )
    {
      SetText(gp->item[_IDC_BUTTON_SERIAL_OPEN_CLOSE].hwnd, STR_CLOSE, strlen(STR_CLOSE));
    }
    else
    {
      gp->__serial[0].io.__f[IMTIF_CALLBACK_CONNECTED] = 0;
      gp->__serial[0].io.__f[IMTIF_CALLBACK_DISCONNECTED] = 0;
      gp->__serial[0].io.__f[IMTIF_CALLBACK_READ] = 0;
    }
  }
  else
  {
    nserial_close(&gp->__serial[0]);
    SetText(gp->item[_IDC_BUTTON_SERIAL_OPEN_CLOSE].hwnd, STR_OPEN, strlen(STR_OPEN));
    gp->__serial[0].io.__f[IMTIF_CALLBACK_CONNECTED] = 0;
    gp->__serial[0].io.__f[IMTIF_CALLBACK_DISCONNECTED] = 0;
    gp->__serial[0].io.__f[IMTIF_CALLBACK_READ] = 0;
  }
  return e;
}



void* wmtif_WM_COMMAND(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int32_t e = 0;
  switch(LOWORD(wparam))
  {
    case IDC_BUTTON_SERIAL_OPEN_CLOSE:
      wmtif_IDC_BUTTON_SERIAL_OPEN_CLOSE(hwnd, msg, wparam, lparam);
      break;

    case IDC_BUTTON_NET_OPEN_CLOSE:
      wmtif_IDC_BUTTON_NET_OPEN_CLOSE(hwnd, msg, wparam, lparam);
      break;


    case IDC_BUTTON_WS_OPEN_CLOSE:
      wmtif_IDC_BUTTON_WS_OPEN_CLOSE(hwnd, msg, wparam, lparam);
      break;

    case IDC_BUTTON_NET_WRITE:
      wmtif_IDC_BUTTON_NET_WRITE(hwnd, msg, wparam, lparam);
      break;

    case IDC_BUTTON_SERIAL_WRITE:
      wmtif_IDC_BUTTON_SERIAL_WRITE(hwnd, msg, wparam, lparam);
      break;
  }
  return 0;
}


void* wmtif_WM_CREATE(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int32_t e = 0;

  return 0;
}
void* wmtif_WM_INITDIALOG(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int32_t e = 0;





  return 0;
}


void* wmtif_dlgproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  uint8_t r = 0;

  switch(msg)
  {
    case WM_INITDIALOG:
      r = (BOOL)wmtif_WM_INITDIALOG(hwnd, msg, wparam, lparam);
      break;

    case WM_CREATE:
      r = (BOOL)wmtif_WM_CREATE(hwnd, msg, wparam, lparam);
      break;

    case WM_COMMAND:
      r = (BOOL)wmtif_WM_COMMAND(hwnd, msg, wparam, lparam);
      break;
  }
  return 0;
}

void* wmtif_init(HWND hwnd, wMTIF* p)
{
  gp = p;

  gp->item[_IDC_EDIT_NET_IP].hwnd = GetDlgItem(hwnd, IDC_EDIT_NET_IP);
  gp->item[_IDC_EDIT_NET_PORT].hwnd = GetDlgItem(hwnd, IDC_EDIT_NET_PORT);
  gp->item[_IDC_COMBO_NET_PROTOCOL].hwnd = GetDlgItem(hwnd, IDC_COMBO_NET_PROTOCOL);
  gp->item[_IDC_COMBO_NET_CS].hwnd = GetDlgItem(hwnd, IDC_COMBO_NET_CS);
  gp->item[_IDC_COMBO_NET_CASTTYPE].hwnd = GetDlgItem(hwnd, IDC_COMBO_NET_CASTTYPE);
  gp->item[_IDC_BUTTON_NET_OPEN_CLOSE].hwnd = GetDlgItem(hwnd, IDC_BUTTON_NET_OPEN_CLOSE);
  gp->item[_IDC_EDIT_NET_WRITE].hwnd = GetDlgItem(hwnd, IDC_EDIT_NET_WRITE);
  gp->item[_IDC_BUTTON_NET_WRITE].hwnd = GetDlgItem(hwnd, IDC_BUTTON_NET_WRITE);
  gp->item[_IDC_CHECK_NET_CR].hwnd = GetDlgItem(hwnd, IDC_CHECK_NET_CR);
  gp->item[_IDC_CHECK_NET_LF].hwnd = GetDlgItem(hwnd, IDC_CHECK_NET_LF);
  gp->item[_IDC_COMBO_NET_DISPLAY_TYPE_W].hwnd = GetDlgItem(hwnd, IDC_COMBO_NET_DISPLAY_TYPE_W);
  gp->item[_IDC_COMBO_NET_DISPLAY_TYPE_R].hwnd = GetDlgItem(hwnd, IDC_COMBO_NET_DISPLAY_TYPE_R);
  gp->item[_IDC_EDIT_SERIAL_PORT].hwnd = GetDlgItem(hwnd, IDC_EDIT_SERIAL_PORT);
  gp->item[_IDC_EDIT_SERIAL_BAUDRATE].hwnd = GetDlgItem(hwnd, IDC_EDIT_SERIAL_BAUD);
  gp->item[_IDC_EDIT_SERIAL_DBIT].hwnd = GetDlgItem(hwnd, IDC_EDIT_SERIAL_DBIT);
  gp->item[_IDC_EDIT_SERIAL_SBIT].hwnd = GetDlgItem(hwnd, IDC_EDIT_SERIAL_SBIT);
  gp->item[_IDC_EDIT_SERIAL_PBIT].hwnd = GetDlgItem(hwnd, IDC_EDIT_SERIAL_PBIT);
  gp->item[_IDC_BUTTON_SERIAL_OPEN_CLOSE].hwnd = GetDlgItem(hwnd, IDC_BUTTON_SERIAL_OPEN_CLOSE);
  gp->item[_IDC_COMBO_SERIAL_DISPLAY_TYPE_R].hwnd = GetDlgItem(hwnd, IDC_COMBO_SERIAL_DISPLAY_TYPE_R);
  gp->item[_IDC_COMBO_SERIAL_DISPLAY_TYPE_W].hwnd = GetDlgItem(hwnd, IDC_COMBO_SERIAL_DISPLAY_TYPE_W);
  gp->item[_IDC_EDIT_SERIAL_WRITE].hwnd = GetDlgItem(hwnd, IDC_EDIT_SERIAL_WRITE);
  gp->item[_IDC_BUTTON_SERIAL_WRITE].hwnd = GetDlgItem(hwnd, IDC_BUTTON_SERIAL_WRITE);
  gp->item[_IDC_CHECK_SERIAL_CR].hwnd = GetDlgItem(hwnd, IDC_CHECK_SERIAL_CR);
  gp->item[_IDC_CHECK_SERIAL_LF].hwnd = GetDlgItem(hwnd, IDC_CHECK_SERIAL_LF);
  gp->item[_IDC_CHECK_SERIAL_ROUTER].hwnd = GetDlgItem(hwnd, IDC_CHECK_SERIAL_ROUTER);
  gp->item[_IDC_EDIT_SERIAL_PORT2].hwnd = GetDlgItem(hwnd, IDC_EDIT_SERIAL_PORT2);
  gp->item[_IDC_EDIT_SERIAL_BAUDRATE2].hwnd = GetDlgItem(hwnd, IDC_EDIT_SERIAL_BAUD2);
  gp->item[_IDC_EDIT_SERIAL_DBIT2].hwnd = GetDlgItem(hwnd, IDC_EDIT_SERIAL_DBIT2);
  gp->item[_IDC_EDIT_SERIAL_SBIT2].hwnd = GetDlgItem(hwnd, IDC_EDIT_SERIAL_SBIT2);
  gp->item[_IDC_EDIT_SERIAL_PBIT2].hwnd = GetDlgItem(hwnd, IDC_EDIT_SERIAL_PBIT2);
  gp->item[_IDC_BUTTON_SERIAL_OPEN_CLOSE2].hwnd = GetDlgItem(hwnd, IDC_BUTTON_SERIAL_OPEN_CLOSE2);
  gp->item[_IDC_COMBO_SERIAL_DISPLAY_TYPE_R2].hwnd = GetDlgItem(hwnd, IDC_COMBO_SERIAL_DISPLAY_TYPE_R2);
  gp->item[_IDC_COMBO_SERIAL_DISPLAY_TYPE_W2].hwnd = GetDlgItem(hwnd, IDC_COMBO_SERIAL_DISPLAY_TYPE_W2);
  gp->item[_IDC_EDIT_SERIAL_WRITE2].hwnd = GetDlgItem(hwnd, IDC_EDIT_SERIAL_WRITE2);
  gp->item[_IDC_BUTTON_SERIAL_WRITE2].hwnd = GetDlgItem(hwnd, IDC_BUTTON_SERIAL_WRITE2);
  gp->item[_IDC_CHECK_SERIAL_CR2].hwnd = GetDlgItem(hwnd, IDC_CHECK_SERIAL_CR2);
  gp->item[_IDC_CHECK_SERIAL_LF2].hwnd = GetDlgItem(hwnd, IDC_CHECK_SERIAL_LF2);
  gp->item[_IDC_LIST_READ].hwnd = GetDlgItem(hwnd, IDC_LIST_READ);
  gp->item[_IDC_CHECK_READ_YN].hwnd = GetDlgItem(hwnd, IDC_CHECK_READ_YN);
  gp->item[_IDC_BUTTON_CLEAR].hwnd = GetDlgItem(hwnd, IDC_BUTTON_CLEAR);
  gp->item[_IDC_COMBO_WS_CS].hwnd = GetDlgItem(hwnd, IDC_COMBO_WS_CS);
  gp->item[_IDC_EDIT_WS_URL].hwnd = GetDlgItem(hwnd, IDC_EDIT_WS_URL);
  gp->item[_IDC_COMBO_WS_DISPLAY_TYPE_W].hwnd = GetDlgItem(hwnd, IDC_COMBO_WS_DISPLAY_TYPE_W);
  gp->item[_IDC_COMBO_WS_DISPLAY_TYPE_R].hwnd = GetDlgItem(hwnd, IDC_COMBO_WS_DISPLAY_TYPE_R);
  gp->item[_IDC_BUTTON_WS_OPEN_CLOSE].hwnd = GetDlgItem(hwnd, IDC_BUTTON_WS_OPEN_CLOSE);
	gp->item[_IDC_EDIT_WS_WRITE].hwnd = GetDlgItem(hwnd, IDC_EDIT_WS_WRITE);
	gp->item[_IDC_CHECK_WS_CR].hwnd = GetDlgItem(hwnd, IDC_CHECK_WS_CR);
	gp->item[_IDC_CHECK_WS_LF].hwnd = GetDlgItem(hwnd, IDC_CHECK_WS_LF);
	gp->item[_IDC_BUTTON_WS_WRITE].hwnd = GetDlgItem(hwnd, IDC_BUTTON_WS_WRITE);
  gp->item[_IDC_CHECK_NET_LOG].hwnd = GetDlgItem(hwnd, IDC_CHECK_NET_LOG);
  gp->item[_IDC_CHECK_WS_LOG].hwnd = GetDlgItem(hwnd, IDC_CHECK_WS_LOG);
  gp->item[_IDC_CHECK_SERIAL_LOG].hwnd = GetDlgItem(hwnd, IDC_CHECK_SERIAL_LOG);
  gp->item[_IDC_CHECK_SERIAL_LOG2].hwnd = GetDlgItem(hwnd, IDC_CHECK_SERIAL_LOG2);
  gp->item[_IDC_CHECK_NET_ECHO].hwnd = GetDlgItem(hwnd, IDC_CHECK_NET_ECHO);
  gp->item[_IDC_CHECK_WS_ECHO].hwnd = GetDlgItem(hwnd, IDC_CHECK_WS_ECHO);
  gp->item[_IDC_CHECK_SERIAL_ECHO].hwnd = GetDlgItem(hwnd, IDC_CHECK_SERIAL_ECHO);
  gp->item[_IDC_CHECK_SERIAL_ECHO2].hwnd = GetDlgItem(hwnd, IDC_CHECK_SERIAL_ECHO2);
  gp->item[_IDC_EDIT_SERIAL_MSEC].hwnd = GetDlgItem(hwnd, IDC_EDIT_SERIAL_MSEC);
  gp->item[_IDC_CHECK_SERIAL_SIMUL].hwnd = GetDlgItem(hwnd, IDC_CHECK_SERIAL_SIMULA);
  gp->item[_IDC_CHECK_NET_SIMUL].hwnd = GetDlgItem(hwnd, IDC_CHECK_NET_SIMULA);
  gp->item[_IDC_CHECK_WS_SIMUL].hwnd = GetDlgItem(hwnd, IDC_CHECK_WS_SIMULA);
  gp->item[_IDC_CHECK_NET_STX].hwnd = GetDlgItem(hwnd, IDC_CHECK_NET_STX);
  gp->item[_IDC_CHECK_NET_ETX].hwnd = GetDlgItem(hwnd, IDC_CHECK_NET_ETX);
  gp->item[_IDC_CHECK_WS_STX].hwnd = GetDlgItem(hwnd, IDC_CHECK_WS_STX);
  gp->item[_IDC_CHECK_WS_ETX].hwnd = GetDlgItem(hwnd, IDC_CHECK_WS_ETX);
  gp->item[_IDC_CHECK_SERIAL_STX].hwnd = GetDlgItem(hwnd, IDC_CHECK_SERIAL_STX);
  gp->item[_IDC_CHECK_SERIAL_ETX].hwnd = GetDlgItem(hwnd, IDC_CHECK_SERIAL_ETX);
  gp->item[_IDC_CHECK_SERIAL_STX2].hwnd = GetDlgItem(hwnd, IDC_CHECK_SERIAL_STX2);
  gp->item[_IDC_CHECK_SERIAL_ETX2].hwnd = GetDlgItem(hwnd, IDC_CHECK_SERIAL_ETX2);
  gp->item[_IDC_EDIT_NET_MSEC].hwnd = GetDlgItem(hwnd, IDC_EDIT_NET_MSEC);
  gp->item[_IDC_EDIT_WS_MSEC].hwnd = GetDlgItem(hwnd, IDC_EDIT_WS_MSEC);
  gp->item[_IDC_EDIT_LIST_COUNT].hwnd = GetDlgItem(hwnd, IDC_EDIT_LIST_COUNT);


  SetText(gp->item[_IDC_EDIT_NET_IP].hwnd, ("192.168.0.106"), strlen("192.168.0.106"));
  SetText(gp->item[_IDC_EDIT_NET_PORT].hwnd, ("502"), strlen("502"));
  SetText(gp->item[_IDC_BUTTON_NET_WRITE].hwnd, ("SEND"), strlen("SEND"));
  SetText(gp->item[_IDC_BUTTON_NET_OPEN_CLOSE].hwnd, STR_OPEN, strlen(STR_OPEN));
  SetText(gp->item[_IDC_BUTTON_SERIAL_WRITE].hwnd, ("WRITE"), strlen("WRITE"));
  SetText(gp->item[_IDC_BUTTON_WS_OPEN_CLOSE].hwnd, STR_OPEN, strlen(STR_OPEN));
  SetText(gp->item[_IDC_BUTTON_CLEAR].hwnd, ("CLEAR"), strlen("CLEAR"));
  SetText(gp->item[_IDC_EDIT_WS_URL].hwnd, ("http://127.0.0.1:8090/"), strlen("http://127.0.0.1:8090/"));
  SetText(gp->item[_IDC_BUTTON_WS_OPEN_CLOSE].hwnd, STR_OPEN, strlen(STR_OPEN));
  SetText(gp->item[_IDC_BUTTON_WS_WRITE].hwnd, ("SEND"), strlen("SEND"));

  ResetText(gp->item[_IDC_EDIT_SERIAL_PORT].hwnd, ("COM4"));
  ResetText(gp->item[_IDC_EDIT_SERIAL_BAUDRATE].hwnd, ("115200"));
  ResetText(gp->item[_IDC_EDIT_SERIAL_DBIT].hwnd, ("8"));
  ResetText(gp->item[_IDC_EDIT_SERIAL_SBIT].hwnd, ("1"));
  ResetText(gp->item[_IDC_EDIT_SERIAL_PBIT].hwnd, ("0"));
  ResetText(gp->item[_IDC_EDIT_SERIAL_PORT2].hwnd, ("COM2"));
  ResetText(gp->item[_IDC_EDIT_SERIAL_BAUDRATE2].hwnd, ("115200"));
  ResetText(gp->item[_IDC_EDIT_SERIAL_DBIT2].hwnd, ("8"));
  ResetText(gp->item[_IDC_EDIT_SERIAL_SBIT2].hwnd, ("1"));
  ResetText(gp->item[_IDC_EDIT_SERIAL_PBIT2].hwnd, ("0"));
  ResetText(gp->item[_IDC_EDIT_NET_MSEC].hwnd, ("1000"));
  ResetText(gp->item[_IDC_EDIT_WS_MSEC].hwnd, ("1000"));
  ResetText(gp->item[_IDC_EDIT_SERIAL_MSEC].hwnd, ("1000"));
  ResetText(gp->item[_IDC_EDIT_LIST_COUNT].hwnd, ("2000"));

  SendMessage(gp->item[_IDC_COMBO_NET_PROTOCOL].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("TCP"));
  SendMessage(gp->item[_IDC_COMBO_NET_PROTOCOL].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("UDP"));
  SendMessage(gp->item[_IDC_COMBO_NET_PROTOCOL].hwnd, CB_SETCURSEL, 0, 0 );
  SendMessage(gp->item[_IDC_COMBO_NET_CS].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("SERVER"));
  SendMessage(gp->item[_IDC_COMBO_NET_CS].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("CLIENT"));
  SendMessage(gp->item[_IDC_COMBO_NET_CS].hwnd, CB_SETCURSEL, 1, 0 );
  SendMessage(gp->item[_IDC_COMBO_WS_CS].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("SERVER"));
  SendMessage(gp->item[_IDC_COMBO_WS_CS].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("CLIENT"));
  SendMessage(gp->item[_IDC_COMBO_WS_CS].hwnd, CB_SETCURSEL, 0, 0 );
  SendMessage(gp->item[_IDC_COMBO_NET_CASTTYPE].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("UNICAST"));
  SendMessage(gp->item[_IDC_COMBO_NET_CASTTYPE].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("BROADCAST"));
  SendMessage(gp->item[_IDC_COMBO_NET_CASTTYPE].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("MULTICAST"));
  SendMessage(gp->item[_IDC_COMBO_NET_CASTTYPE].hwnd, CB_SETCURSEL, 0, 0 );
	SendMessage(gp->item[_IDC_COMBO_NET_DISPLAY_TYPE_W].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("ASCII"));
	SendMessage(gp->item[_IDC_COMBO_NET_DISPLAY_TYPE_W].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("HEX"));
  SendMessage(gp->item[_IDC_COMBO_NET_DISPLAY_TYPE_W].hwnd, CB_SETCURSEL, 1, 0 );
	SendMessage(gp->item[_IDC_COMBO_NET_DISPLAY_TYPE_R].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("ASCII"));
	SendMessage(gp->item[_IDC_COMBO_NET_DISPLAY_TYPE_R].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("HEX"));
  SendMessage(gp->item[_IDC_COMBO_NET_DISPLAY_TYPE_R].hwnd, CB_SETCURSEL, 1, 0 );
	SendMessage(gp->item[_IDC_COMBO_WS_DISPLAY_TYPE_W].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("ASCII"));
	SendMessage(gp->item[_IDC_COMBO_WS_DISPLAY_TYPE_W].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("HEX"));
  SendMessage(gp->item[_IDC_COMBO_WS_DISPLAY_TYPE_W].hwnd, CB_SETCURSEL, 0, 0 );
	SendMessage(gp->item[_IDC_COMBO_WS_DISPLAY_TYPE_R].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("ASCII"));
	SendMessage(gp->item[_IDC_COMBO_WS_DISPLAY_TYPE_R].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("HEX"));
  SendMessage(gp->item[_IDC_COMBO_WS_DISPLAY_TYPE_R].hwnd, CB_SETCURSEL, 0, 0 );
	SendMessage(gp->item[_IDC_COMBO_SERIAL_DISPLAY_TYPE_W].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("ASCII"));
	SendMessage(gp->item[_IDC_COMBO_SERIAL_DISPLAY_TYPE_W].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("HEX"));
  SendMessage(gp->item[_IDC_COMBO_SERIAL_DISPLAY_TYPE_W].hwnd, CB_SETCURSEL, 0, 0 );
	SendMessage(gp->item[_IDC_COMBO_SERIAL_DISPLAY_TYPE_R].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("ASCII"));
	SendMessage(gp->item[_IDC_COMBO_SERIAL_DISPLAY_TYPE_R].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("HEX"));
  SendMessage(gp->item[_IDC_COMBO_SERIAL_DISPLAY_TYPE_R].hwnd, CB_SETCURSEL, 0, 0 );
	SendMessage(gp->item[_IDC_COMBO_SERIAL_DISPLAY_TYPE_W2].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("ASCII"));
	SendMessage(gp->item[_IDC_COMBO_SERIAL_DISPLAY_TYPE_W2].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("HEX"));
  SendMessage(gp->item[_IDC_COMBO_SERIAL_DISPLAY_TYPE_W2].hwnd, CB_SETCURSEL, 0, 0 );
	SendMessage(gp->item[_IDC_COMBO_SERIAL_DISPLAY_TYPE_R2].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("ASCII"));
	SendMessage(gp->item[_IDC_COMBO_SERIAL_DISPLAY_TYPE_R2].hwnd, CB_ADDSTRING, 0, (LPARAM)_T("HEX"));
  SendMessage(gp->item[_IDC_COMBO_SERIAL_DISPLAY_TYPE_R2].hwnd, CB_SETCURSEL, 0, 0 );

  InitListView(gp->item[_IDC_LIST_READ].hwnd, 4096);

  return 0;
}

