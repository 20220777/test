#include "wwsgw.h"
#include <resource.h>
//#include "mprotocol.h"

/**
02 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 03
**/

#define XWM_REQ          WM_USER+1
#define XWM_TRANSFER     WM_USER+2

static wWSGW* gp;

#define LVLOG    1

#if 0
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/* Socket -> DB, WebSocket                                                     */
/*                                                                             */
/*                                                                             */
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/


void wwsgw_transfer(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
void wwsgw_request(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);


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

void wsgWebSocketRouting(char* b, int sz)
{
  char st[32];
  char vbuf[4096];
  int e = 0;
  int w = 0;
  int idx = 0;


  fprint_raw_buffer(0, b, sz, vbuf);
  //OutputDebugString(vbuf);
  //OutputDebugString("\r\n");

  for(idx=0 ; idx<FD_SETSIZE ; idx++ )
  {
    //LVLog(gp->hitem[LIST_WSGW_WS_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "WebSocket", "Client[%d], %d, %08X \r\n", idx, gp->pm->mws.pack.info[idx].fd,gp->pm->mws.pack.info[idx].REG.SR);

    //if ( (gp->pm->mws.pack.info[idx].fd > 0) && (gp->pm->mws.pack.info[idx].REG.SR&0x00000001) )
    if ((gp->pm->mws.pack.info[idx].fd > 0) )//&& (gp->pm->mws.pack.info[idx].REG.SR & 0x00000001))
    {
      //e = mtifWebSocketWrite(&gp->pm->mws.m, gp->pm->mws.pack.info[idx].fd, b, sz);
      e = mtifWebSocketWriteEx(&gp->pm->mws.m, gp->pm->mws.pack.info[idx].fd, b, sz, 0x02, 0, 0);
      if ( e > 0 )
      {
        #if LVLOG
        LVLog(gp->hitem[LIST_WSGW_WS_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "WebSocket", "Client[%d], %d = Write(%d, \"%s\", %d) \r\n", idx, e, gp->pm->mws.pack.info[idx].fd, vbuf, sz);
        #endif
        //LVLog(gp->hitem[LIST_WSGW_WS_LOG], gp->hitem[CHECK_WSGW_LOG], &gp->log, "log", "WebSocket", "%d = Write(%d, \"%s\", %d)", e, gp->pm->mws.pack.info[idx].fd, b, sz);
      }
    }
    mcsleep(10);
  }


  //if ( ((mtifInfo*)gp->pm->mws.info)->arg[XWEBSOCKET][XM_CSTYPE][0] == 'C')
  //{
  //  e = mtifWebSocketWrite(&gp->pm->mws.m, gp->pm->mws.fd, b, sz);
  //  if ( e > 0 )
  //  {
  //    //LVLog(gp->hitem[LIST_WSGW_WS_LOG], gp->hitem[CHECK_WSGW_LOG], &gp->log, "log", "WebSocket", "%d = Write(%d, \"%s\", %d)", e, gp->pm->mws.fd, sbuf, w);
  //    //LVLog(gp->hitem[LIST_WSGW_WS_LOG], gp->hitem[CHECK_WSGW_LOG], &gp->log, "log", "WebSocket", "%d = Write(%d, \"%s\", %d)", e, gp->pm->mws.fd, b, sz);
  //  }
  //}
  //else
  //{
  //  for(idx=0 ; idx<FD_SETSIZE ; idx++ )
  //  {
  //    if ( gp->pm->mws.pack.info[idx].fd > 0 )
  //    {
  //      e = mtifWebSocketWrite(&gp->pm->mws.m, gp->pm->mws.pack.info[idx].fd, b, sz);
  //      if ( e > 0 )
  //      {
  //        //LVLog(gp->hitem[LIST_WSGW_WS_LOG], gp->hitem[CHECK_WSGW_LOG], &gp->log, "log", "WebSocket", "%d = Write(%d, \"%s\", %d)", e, gp->pm->mws.pack.info[idx].fd, sbuf, w);
  //        //LVLog(gp->hitem[LIST_WSGW_WS_LOG], gp->hitem[CHECK_WSGW_LOG], &gp->log, "log", "WebSocket", "%d = Write(%d, \"%s\", %d)", e, gp->pm->mws.pack.info[idx].fd, b, sz);
  //      }
  //    }
  //  }
  //}





  //GetComboText(gp->hitem[COMBO_DISPLAY_TYPE_WSGW], st);

  //if ( st[0] == 'A' )
  //{
  //  w = str_to_hex(b, sz, ' ', sbuf);
  //  if ( ((mtifInfo*)gp->pm->mws.info)->arg[XWEBSOCKET][XM_CSTYPE][0] == 'C')
  //  {
  //    e = mtifWebSocketWrite(&gp->pm->mws.m, gp->pm->mws.fd, b, sz);
  //    if ( e > 0 )
  //    {
  //      LVLog(gp->hitem[LIST_WSGW_WS_LOG], gp->hitem[CHECK_WSGW_LOG], &gp->log, "log", "WebSocket", "%d = Write(%d, \"%s\", %d)", e, gp->pm->mws.fd, sbuf, w);
  //      //LVLog(gp->hitem[LIST_WSGW_WS_LOG], gp->hitem[CHECK_WSGW_LOG], &gp->log, "log", "WebSocket", "%d = Write(%d, \"%s\", %d)", e, gp->pm->mws.fd, b, sz);
  //    }
  //  }
  //  else
  //  {
  //    for(idx=0 ; idx<FD_SETSIZE ; idx++ )
  //    {
  //      if ( gp->pm->mws.pack.info[idx].fd > 0 )
  //      {
  //        e = mtifWebSocketWrite(&gp->pm->mws.m, gp->pm->mws.pack.info[idx].fd, b, sz);
  //        if ( e > 0 )
  //        {
  //          LVLog(gp->hitem[LIST_WSGW_WS_LOG], gp->hitem[CHECK_WSGW_LOG], &gp->log, "log", "WebSocket", "%d = Write(%d, \"%s\", %d)", e, gp->pm->mws.pack.info[idx].fd, sbuf, w);
  //          //LVLog(gp->hitem[LIST_WSGW_WS_LOG], gp->hitem[CHECK_WSGW_LOG], &gp->log, "log", "WebSocket", "%d = Write(%d, \"%s\", %d)", e, gp->pm->mws.pack.info[idx].fd, b, sz);
  //        }
  //      }
  //    }
  //  }
  //}
  //else
  //{
  //  w = str_to_hex(b, sz, ' ', sbuf);

  //  if ( ((mtifInfo*)gp->pm->mws.info)->arg[XWEBSOCKET][XM_CSTYPE][0] == 'C')
  //  {
  //    e = mtifWebSocketWrite(&gp->pm->mws.m, gp->pm->mws.fd, sbuf, w);
  //    if ( e > 0 )
  //    {
  //      LVLog(gp->hitem[LIST_WSGW_WS_LOG], gp->hitem[CHECK_WSGW_LOG], &gp->log, "log", "WebSocket", "%d = Write(%d, \"%s\", %d)", e, gp->pm->mws.fd, sbuf, w);
  //    }
  //  }
  //  else
  //  {
  //    for(idx=0 ; idx<FD_SETSIZE ; idx++ )
  //    {
  //      if ( gp->pm->mws.pack.info[idx].fd > 0 )
  //      {
  //        e = mtifWebSocketWrite(&gp->pm->mws.m, gp->pm->mws.pack.info[idx].fd, sbuf, w);
  //        if ( e > 0 )
  //        {
  //          LVLog(gp->hitem[LIST_WSGW_WS_LOG], gp->hitem[CHECK_WSGW_LOG], &gp->log, "log", "WebSocket", "%d = Write(%d, \"%s\", %d)", e, gp->pm->mws.pack.info[idx].fd, sbuf, w);
  //        }
  //      }
  //    }
  //  }
  //}
}

void wsgWebSocketClose()
{
  mtifWebSocketClose(&gp->pm->mws.m, gp->pm->mws.b);
  lock_final((void*)&gp->pm->mws.crit);
}

void wsgWebSocketWrite()
{
  char st[32];
  char smsg[1024];
  char sbuf[1024];
  int sz;
  int e = 0;
  int w = 0;
  int idx = 0;

  ////sz = GetText(gp->hitem[EDIT_WS_SEND], smsg, 1024);
  ////smsg[sz] = 0;

  //if ( st[0] == 'A' )
  //{
  //  if ( ((mtifInfo*)gp->pm->mws.info)->arg[XWEBSOCKET][XM_CSTYPE][0] == 'C')
  //  {
  //    e = mtifWebSocketWrite(&gp->pm->mws.m, gp->pm->mws.fd, smsg, sz);
  //    if ( e > 0 )
  //    {
  //      LVLog(gp->hitem[LIST_WSGW_WS_LOG], gp->hitem[CHECK_WSGW_LOG], &gp->log, "log", "WebSocket", "%d = Write(%d, \"%s\", %d)", e, gp->pm->mws.fd, smsg, sz);
  //    }
  //  }
  //  else
  //  {
  //    for(idx=0 ; idx<FD_SETSIZE ; idx++ )
  //    {
  //      if ( gp->pm->mws.pack.info[idx].fd > 0 )
  //      {
  //        e = mtifWebSocketWrite(&gp->pm->mws.m, gp->pm->mws.pack.info[idx].fd, smsg, sz);
  //        if ( e > 0 )
  //        {
  //          LVLog(gp->hitem[LIST_WSGW_WS_LOG], gp->hitem[CHECK_WSGW_LOG], &gp->log, "log", "WebSocket", "%d = Write(%d, \"%s\", %d)", e, gp->pm->mws.pack.info[idx].fd, smsg, sz);
  //        }
  //      }
  //    }
  //  }
  //}
  //else
  //{
  //  w = str_to_hex(smsg, sz, ' ', sbuf);
  //  if ( ((mtifInfo*)gp->pm->mws.info)->arg[XWEBSOCKET][XM_CSTYPE][0] == 'C')
  //  {
  //    e = mtifWebSocketWrite(&gp->pm->mws.m, gp->pm->mws.fd, sbuf, w);
  //    if ( e > 0 )
  //    {
  //      LVLog(gp->hitem[LIST_WSGW_WS_LOG], gp->hitem[CHECK_WSGW_LOG], &gp->log, "log", "WebSocket", "%d = Write(%d, \"%s\", %d)", e, gp->pm->mws.fd, smsg, sz);
  //    }
  //  }
  //  else
  //  {
  //    for(idx=0 ; idx<FD_SETSIZE ; idx++ )
  //    {
  //      if ( gp->pm->mws.pack.info[idx].fd > 0 )
  //      {
  //        e = mtifWebSocketWrite(&gp->pm->mws.m, gp->pm->mws.pack.info[idx].fd, sbuf, w);
  //        if ( e > 0 )
  //        {
  //          LVLog(gp->hitem[LIST_WSGW_WS_LOG], gp->hitem[CHECK_WSGW_LOG], &gp->log, "log", "WebSocket", "%d = Write(%d, \"%s\", %d)", e, gp->pm->mws.pack.info[idx].fd, smsg, sz);
  //        }
  //      }
  //    }
  //  }
  //}
}

void* wsgWebSocketStatus(void* t,int fd, unsigned char* b, int sz, void* extra, int err, void* o)
{
  int e = 0;

  int idx = (extra==0)?0:(*(int*)extra);

  #if LVLOG
  LVLog(gp->hitem[LIST_WSGW_WS_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "WebSocket", "WebSocket (%d) %08X Client[%d] \r\n", ((mtifWebSocket*)o)->fd, err, idx);
  #endif

  switch(err)
  {
    case 0xE000ACCB:
      if ( ((mtifInfo*)((mtifWebSocket*)o)->info)->arg[XWEBSOCKET][XM_CSTYPE][0]=='S' )
      {
        ((mtifWebSocket*)o)->pack.info[idx].fd = fd;
        ((mtifWebSocket*)o)->pack.info[idx].b[0][0] = 0x80|WEBSOCKET_BUF_SFT;
        *((char**)b) = ((mtifWebSocket*)o)->pack.info[idx].b[0];
        #if LVLOG
        LVLog(gp->hitem[LIST_WSGW_WS_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "WebSocket", "WebSocket (%d) %08X Client[%d] Accepted %d \r\n", ((mtifWebSocket*)o)->fd, err, idx, fd);
        #endif
      }
      break;

    case 0xE000ACC0:
      break;

    case 0xE000ACCA: // Handshaked
      ((mtifWebSocket*)o)->pack.info[idx].REG.SR |= 0x00000001;
      #if LVLOG
      LVLog(gp->hitem[LIST_WSGW_WS_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "WebSocket", "WebSocket (%d) %08X Client[%d:%d] HandShaked \r\n", ((mtifWebSocket*)o)->fd, err, idx, fd);
      #endif
      break;

    case 0xE000AC30: // HandShake ACK
      #if LVLOG
      LVLog(gp->hitem[LIST_WSGW_WS_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "WebSocket", "WebSocket (%d) %08X Client[%d:%d] HandShake ACK \r\n", ((mtifWebSocket*)o)->fd, err, idx, fd);
      #endif
      break;

    case 0xE000101F:
      if ( ((mtifInfo*)((mtifWebSocket*)o)->info)->arg[XWEBSOCKET][XM_CSTYPE][0]=='S' )
      {
        #if LVLOG
        LVLog(gp->hitem[LIST_WSGW_WS_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "WebSocket", "WebSocket (%d) %08X Client[%d] Disconnected %d \r\n", ((mtifWebSocket*)o)->fd, err, idx, ((mtifWebSocket*)o)->pack.info[idx].fd);
        #endif
        ((mtifWebSocket*)o)->pack.info[idx].fd = 0;
        ((mtifWebSocket*)o)->pack.info[idx].b[0][0] = 0;
        ((mtifWebSocket*)o)->pack.info[idx].REG.SR = 0x00000000;
      }
      break;

    case 0xE000B0FF:
      *((char**)b) = ((mtifWebSocket*)o)->iobuf;
      e = 1;
      break;

    case 0xE000109B:
      //((mtifWebSocket*)o)->pack.info[idx].buf[0] = WEBSOCKET_BUF_SFT;
      //*((char**)b) = ((mtifWebSocket*)o)->pack.info[idx].buf;
      //e = 1;
      break;

  }

  return (void*)e;
}
void* wsgWebSocketRead(void* t,int fd, unsigned char* b, int sz, void* extra, int err, void* o)
{
  char st[32];
  char rbuf[4096];
  char vbuf[4096];

  if ( gp->read_lock ) return 0;

  if ( err <=0 ) return 0;

  *(b+sz) = 0;

  fprint_raw_buffer(0, b, sz, vbuf);
  #if LVLOG    
  LVLog(gp->hitem[LIST_WSGW_WS_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "WebSocket", "%s \r\n", vbuf);
  #endif
  return 0;
}
int wsgWebSocketOpen()
{
  char _url[256];

  GetText(gp->hitem[EDIT_WSGW_WS_PORT], ((mtifInfo*)gp->pm->mws.info)->arg[XWEBSOCKET][XM_PORT], 32);

  sprintf(((mtifInfo*)gp->pm->mws.info)->arg[XWEBSOCKET][XM_CSTYPE], "SERVER");
  sprintf(_url, "http://127.0.0.1:%s/", ((mtifInfo*)gp->pm->mws.info)->arg[XWEBSOCKET][XM_PORT]);

  lock_init((void*)&gp->pm->mws.crit);
  gp->pm->mws.m.pfxMTIF[ONWSSTATUS] = wsgWebSocketStatus;
  gp->pm->mws.m.pfxMTIF[ONWSREAD] = wsgWebSocketRead;

  gp->pm->mws.b[0][0] = 0x8A;
  gp->pm->mws.fd = mtifWebSocketOpen(&gp->pm->mws.m, _url, "SERVER", 0, gp->pm->mws.b[0], 0, (void*)&gp->pm->mws);
  return gp->pm->mws.fd;
}
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/


void* on_req_timer(void* hwnd, int msg, int id, int tm)
{
  //LVLog(gp->hitem[LIST_WSGW_TCP_LOG], gp->hitem[CHECK_WSGW_LOG], &gp->log, "log", "timer", "event %d", gp->ecount++);

  #if LVLOG
  LVLog(gp->hitem[LIST_WSGW_TCP_LOG], 0, MAX_LINE, &gp->log, "log", "timer", "event %d \r\n", gp->ecount++);
  #endif
  PostMessage(gp->hwnd, XWM_REQ, 0, 0);
}
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/* Socket                                                                      */
/*                                                                             */
/*                                                                             */
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
int wsgSocketClose()
{
  mtifSocketClose(&gp->pm->msck.m, gp->pm->msck.b);
  lock_final((void*)&gp->pm->msck.crit);
  return 0;
}

void wsgSocketRequest(unsigned char did)
{
  char st[32];
  unsigned char b[1024];
  char vbuf[1024];
  int sz = 0;
  int e = 0;
  int w = 0;
  int idx = 0;
  unsigned char crc;


  b[sz++] = 0x02;
  b[sz++] = 0xFF;//did;
  b[sz++] = 0x00;
  crc = (b[1]+b[2]);
  crc = (~crc) + 1;
  b[sz++] = crc;
  b[sz++] = 0x03;

  w = fprint_raw_buffer(0, b, sz, vbuf);


  for(idx=0 ; idx<FD_SETSIZE ; idx++ )
  {

    if ( (gp->pm->msck.pack.info[idx].REG.SR&0x00000001) == 0 )
    if ( (gp->pm->msck.pack.info[idx].fd > 0) )
    {
      #if DEBUG_LOCAL
      {
        char dbg[32];
        sprintf(dbg, "Request to %4d....\r\n", gp->pm->msck.pack.info[idx].fd);
        OutputDebugString(dbg);
      }
      #endif
      e = mtifSocketWrite(&gp->pm->msck.m, gp->pm->msck.pack.info[idx].fd, b, sz);
      if ( e > 0 )
      {
        gp->pm->msck.pack.info[idx].REG.SR |= 0x00000001;
        #if LVLOG
        LVLog(gp->hitem[LIST_WSGW_TCP_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "Socket", "%d = write(%d, \"%s\", %d) \r\n", e, gp->pm->msck.pack.info[idx].fd, vbuf, sz);
        #endif
      }
    }
  }

}

void wsgSocketWrite()
{
  char st[32];
  char smsg[1024];
  char sbuf[1024];
  int sz;
  int e = 0;
  int w = 0;
  int idx = 0;


  //if ( st[0] == 'A' )
  //{
  //  for(idx=0 ; idx<FD_SETSIZE ; idx++ )
  //  {
  //    if ( gp->pm->msck.pack.info[idx].fd > 0 )
  //    {
  //      e = mtifSocketWrite(&gp->pm->msck.m, gp->pm->msck.pack.info[idx].fd, smsg, sz);
  //      if ( e > 0 )
  //      {
  //        LVLog(gp->hitem[LIST_WSGW_TCP_LOG], gp->hitem[LIST_WSGW_WS_LOG], &gp->log, "log", "Socket", "%d = write(%d, \"%s\", %d)", e, gp->pm->msck.pack.info[idx].fd, smsg, sz);
  //      }
  //    }
  //  }
  //}
  //else
  //{
  //  w = str_to_hex(smsg, sz, ' ', sbuf);
  //  for(idx=0 ; idx<FD_SETSIZE ; idx++ )
  //  {
  //    if ( gp->pm->msck.pack.info[idx].fd > 0 )
  //    {
  //      e = mtifSocketWrite(&gp->pm->msck.m, gp->pm->msck.pack.info[idx].fd, sbuf, w);
  //      if ( e > 0 )
  //      {
  //        LVLog(gp->hitem[LIST_WSGW_TCP_LOG], gp->hitem[LIST_WSGW_WS_LOG], &gp->log, "log", "Socket", "%d = write(%d, \"%s\", %d)", e, gp->pm->msck.pack.info[idx].fd, sbuf, w);
  //      }
  //    }
  //  }
  //}
}

void* wsgSocketStatus(void* t,int fd, unsigned char* b, int sz, void* extra, int err, void* o)
{
  int e = 0;
  int idx = (extra==0)?0:(*(int*)extra);

  if ( gp->read_lock ) return 0;

  //LVLog(gp->hitem[LIST_WSGW_TCP_LOG], gp->hitem[CHECK_WSGW_LOG], &gp->log, "log", "Socket", "Socket (%d) %08X", ((mtifSocket*)o)->fd, err);
  switch(err)
  {
    case 0xE000ACCB:
      if ( ((mtifInfo*)((mtifSocket*)o)->info)->arg[XSOCKET][XM_CSTYPE][0]=='S' )
      {
        ((mtifSocket*)o)->pack.info[idx].b[0][0] = 0x80|SOCKET_BUF_SFT;
        *(char**)b = ((mtifSocket*)o)->pack.info[idx].b[0];
        ((mtifSocket*)o)->pack.info[idx].fd = fd;
        #if LVLOG
        LVLog(gp->hitem[LIST_WSGW_TCP_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "Socket", "Socket (%d:%d) %08X ACCEPT BEFORE \r\n", ((mtifSocket*)o)->fd, fd, err);
        #endif
      }
      break;
    case 0xE000ACCA:
      if ( ((mtifInfo*)((mtifSocket*)o)->info)->arg[XSOCKET][XM_CSTYPE][0]=='S' )
      {
        #if LVLOG
        LVLog(gp->hitem[LIST_WSGW_TCP_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "Socket", "Socket (%d) %08X ACCEPT AFTER \r\n", ((mtifSocket*)o)->fd, err);
        #endif
        //PostMessage(gp->hwnd, XWM_REQ, 0, 0);
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
        #if LVLOG
        LVLog(gp->hitem[LIST_WSGW_TCP_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "Socket", "Socket (%d:%d) %08X Disconnected \r\n", ((mtifSocket*)o)->fd, ((mtifSocket*)o)->pack.info[idx].fd, err);
        #endif
        ((mtifSocket*)o)->pack.info[idx].b[0][0] = 0;
        ((mtifSocket*)o)->pack.info[idx].fd = -1;
      }
      if ( ((mtifInfo*)((mtifSocket*)o)->info)->arg[XSOCKET][XM_CSTYPE][0]=='C' )
      {
        #if LVLOG
        LVLog(gp->hitem[LIST_WSGW_TCP_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "Socket", "Socket (%d) %08X Disconnected \r\n", ((mtifSocket*)o)->fd,  err);
        #endif
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
        ((mtifSocket*)o)->pack.info[idx].REG.SR&=0xFFFFFFFE;
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
        ((mtifSocket*)o)->pack.info[idx].bi ++;
        ((mtifSocket*)o)->pack.info[idx].bi %= MAX_BUF_COUNT;
        ((mtifSocket*)o)->pack.info[idx].b[((mtifSocket*)o)->pack.info[idx].bi][0]=0x80|SOCKET_BUF_SFT;
        *(char**)b = ((mtifSocket*)o)->pack.info[idx].b[((mtifSocket*)o)->pack.info[idx].bi];
        e = 1;
      }
      break;
    case 0xE000C75B:
      #if LVLOG
      LVLog(gp->hitem[LIST_WSGW_TCP_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "Socket", "Socket (%d) %08X Thread Close Before \r\n", ((mtifSocket*)o)->fd, err);
      #endif
      break;
    case 0xE000C75A:
      #if LVLOG
      LVLog(gp->hitem[LIST_WSGW_TCP_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "Socket", "Socket (%d) %08X Thread Close After \r\n", ((mtifSocket*)o)->fd, err);
      #endif
      break;
  }

  return (void*)e;
}



void* on_shof_protocol_check(char* b, int osz)
{
  int e = -1;

  //if ( (*(b + 2) + 3 <= osz) && (*(b + 2) + 5 >= osz) ) e = 0;
  if ((*(b + 2) + 3 <= osz) )
  {
    if ( *(b+2) == 0x0F )
    {
      e = 0;
    }
    else
    {
      e = -2;
    }
  }
  
  //else if ((*(b + 2) + 4 < osz) ) e = -2;

  return (void*)e;
}

int on_shof_protocol_validation(char* b, int sz)
{
  int i = 0;
  unsigned char crc = 0;
  int e = 0;

  for ( i=1 ; i<sz-2 ; i++ )
  {
    crc += (unsigned char)(*(b+i));
  }

  #if DEBUG_LOCAL
  {
    char dbg[64];
    sprintf(dbg, "CHECKSUM -> %02X [%02X]\r\n", (unsigned char)((~crc) + 1), (unsigned char)*(b+i));
    OutputDebugString(dbg);
  }
  #endif



  if ((unsigned char)((~crc) + 1) != (unsigned char)(*(b+i)) )
  {
    e = -1;
  }
  return e;
}

int on_shof_protocol_proc(char* b, int sz, int* pos, char* out)
{
  int e = 0;
  int osz = 0;
  int i = 0;
  char temp[8192];

  //fprint_buffer("on_shof_protocol_proc",b,sz,0,16);
  for (; ; )
  {
    e = on_protcol_check(&shof_protocol[0], b + i, sz - i, pos, out, &osz, on_shof_protocol_check);

    //{
    //  char temp[1024];
    //  sprintf(temp, " e -> %d , %d , %d , %d \r\n", e, i, *pos, osz);
    //  OutputDebugString(temp);
    //}

    //fprint_buffer("on_shof_protocol_proc check",out,osz,0,16);
    if (e > 0)
    {
      i += e;
      //////wwsgw_transfer(0, 0, (WPARAM)osz, (LPARAM)&out[*oidx]);

      if ( on_shof_protocol_validation(&out[*pos], osz) < 0 )
      {
        #if DEBUG_LOCAL
        OutputDebugString("[CHECKSUM FAIL] ");
        OutputDebugString(temp);
        OutputDebugString("\r\n");
        #endif
        #if LVLOG
        fprint_raw_buffer("pchk", b, sz, temp);

        LVLog(gp->hitem[LIST_WSGW_TCP_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "Socket", "[CHECKSUM FAIL] %s\r\n", temp);
        #endif
        //mcsleep(1000);
      }
      else
      {
        //#if DEBUG_LOCAL
        //OutputDebugString("[CHECKSUM PASS] ");
        //OutputDebugString(temp);
        //OutputDebugString("\r\n");
        //#endif
        #if LVLOG
        LVLog(gp->hitem[LIST_WSGW_TCP_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "Socket", "[CHECKSUM PASS]\r\n");
        #endif
        PostMessage(gp->hwnd, XWM_TRANSFER, (WPARAM)osz, (LPARAM)&out[*pos]);
      }
      //{
      //  char tmp[4096];
      //  fprint_raw_buffer("out ", &out[_pos], osz, tmp);
      //  OutputDebugString(tmp);
      //  OutputDebugString("\r\n");
      //}

    }
    else
    {
      //OutputDebugString("break \r\n");
      break;
    }
    //mcsleep(100);

  }

  //{
  //  char tmp[32];
  //  sprintf(tmp, "e -> %d, %d, %d, %d\r\n", e, *(pos+0), *(pos+1), sz);
  //  OutputDebugString(tmp);
  //}



  return e;
}

void* wsgSocketRead(void* t,int fd, unsigned char* b, int sz, void* extra, int err, void* o)
{
  char st[32];
  int osz = 0;
  char rbuf[1024];
  char vbuf[1024];
  int e = 0;
  int idx = 0;
  if ( gp->read_lock ) return 0;
  if ( sz <= 0 ) return 0;

  *(b+sz) = 0;

  //fprint_raw_buffer(0, b, sz, vbuf);
  //#if DEBUG_LOCAL
  //{
  //  char tmp[4096];
  //  fprint_raw_buffer("read ", b, sz, tmp);
  //  OutputDebugString(tmp);
  //  OutputDebugString("\r\n");
  //}
  //#endif

  //#if LVLOG
  //LVLog(gp->hitem[LIST_WSGW_TCP_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "Socket", "read (%d:%d) %s \r\n", ((mtifSocket*)o)->fd, fd, vbuf);
  //#endif

  //((mtifSocket*)o)->pack.info[idx].bpos[1] = 0;
  e = on_shof_protocol_proc(b, sz, &((mtifSocket*)o)->pack.info[idx].bpos, ((mtifSocket*)o)->pack.info[idx].pb);

  //PostMessage(gp->hwnd, XWM_REQ, 0, 0);

  //e = on_protcol_check(&shof_protocol[0], b, sz, &((mtifSocket*)o)->pack.info[idx].bpos, ((mtifSocket*)o)->pack.info[idx].pb, &osz, on_shof_protocol_check);
  //e = on_protcol_check_HEX(&shof_protocol[0], shof_protocol[2], &gp->REG.SR, b, sz, &((mtifSocket*)o)->pack.info[idx].bpos,  ((mtifSocket*)o)->pack.info[idx].pb);

  //#if LVLOG
  //if ( e<0 ) LVLog(gp->hitem[LIST_WSGW_TCP_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "Socket", "read (%d:%d) NOT Completed \r\n", ((mtifSocket*)o)->fd,fd);
  //else LVLog(gp->hitem[LIST_WSGW_TCP_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "Socket", "read (%d:%d) Completed (%d) \r\n", ((mtifSocket*)o)->fd,fd, sz);
  //#endif

  //fprint_raw_buffer(0, b, sz, vbuf);

  //PostMessage(gp->hwnd, XWM_TRANSFER, (WPARAM)sz, (LPARAM)b);


  return 0;
}


int wsgSocketOpen()
{
  char msec[32];
  GetText(gp->hitem[EDIT_WSGW_TCP_PORT], ((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_PORT], 32);
  sprintf(((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_CSTYPE], "SERVER");

  lock_init((void*)&gp->pm->msck.crit);

  gp->pm->msck.m.pfxMTIF[ONSOCKETSTATUS] = wsgSocketStatus;
  gp->pm->msck.m.pfxMTIF[ONSOCKETREAD] = wsgSocketRead;

  gp->pm->msck.b[0][0] =  0x80|SOCKET_BUF_SFT;
  gp->pm->msck.fd = mtifSocketOpen(&gp->pm->msck.m, "127.0.0.1", ((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_PORT], ((mtifInfo*)gp->pm->msck.info)->arg[XSOCKET][XM_CSTYPE], "TCP", "UNICAST", gp->pm->msck.b[0], (void*)&gp->pm->msck);

  GetText(gp->hitem[EDIT_WSGW_MSEC], msec, 32);
  //set_timer(gp->hwnd, 1, atoi(msec), on_req_timer);
  //SendMessage(gp->hitem[CHECK_WSGW_REQ], BM_SETCHECK, BST_CHECKED, 0);

  return gp->pm->msck.fd;
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
/*                                                                             */
/*                                                                             */
/* DBC                                                                         */
/*                                                                             */
/*                                                                             */
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
#define STATUS_0      "OFF"
#define STATUS_1      "IDLE"
#define STATUS_2      "ON"





int wsgMakeQuery(unsigned char* p, unsigned char* tag, unsigned char* v, char* query)
{
  int e = 0;
  time_t t = time(0);

  sprintf(query,
          "update Machine_Parameter_Out "
          "set "
          "status_log = '%s' "
          "date_time = '%d' "
          "where machine_code = 'UL%02d' "
          "and parameter_code = '%s'",
          v, t, *(p+1), tag);

  return e;
}

int getDevID(unsigned char id, char* did)
{
  if (id == 0x0B) sprintf(did, "UL01");
  else if (id == 0x0C) sprintf(did, "UL02");
  else if (id == 0x0D) sprintf(did, "UL03");
  else if (id == 0x0E) sprintf(did, "UL04");
  else if (id == 0x15) sprintf(did, "UL05");
  else if (id == 0x1F) sprintf(did, "UL06");
  else if (id == 0x29) sprintf(did, "UL07");
  else if (id == 0x33) sprintf(did, "UL08");
  else if (id == 0x3D) sprintf(did, "UL09");
  else if (id == 0x47) sprintf(did, "UL10");

  else if (id == 0x51) sprintf(did, "UL11");
  else if (id == 0x52) sprintf(did, "UL12");
  else if (id == 0x53) sprintf(did, "UL13");
  else if (id == 0x54) sprintf(did, "UL14");

  else if (id == 0x5B) sprintf(did, "UL15");
  else if (id == 0x65) sprintf(did, "UL16");
  else if (id == 0x6F) sprintf(did, "UL17");
  else if (id == 0x70) sprintf(did, "UL18");

  else if (id == 0x79) sprintf(did, "UL19");
  else if (id == 0x7A) sprintf(did, "UL20");

  else if (id == 0x83) sprintf(did, "UL21");
  else if (id == 0x8D) sprintf(did, "UL22");
  else if (id == 0x8E) sprintf(did, "UL23");
  else if (id == 0x97) sprintf(did, "UL24");
  else if (id == 0x98) sprintf(did, "UL25");
  else if (id == 0xA1) sprintf(did, "UL26");
  else if (id == 0xA2) sprintf(did, "UL27");

  else if (id == 0xAB) sprintf(did, "UL28");
  else if (id == 0xB5) sprintf(did, "UL29");
  else if (id == 0xBF) sprintf(did, "UL30");
  else if (id == 0xC9) sprintf(did, "UL31");
  else if (id == 0xD3) sprintf(did, "UL32");
  else if (id == 0xDD) sprintf(did, "UL33");
  return 0;
}

KD_DeviceInfo gdinfo[] =  {
  {0x0B, "UL01", "KCS-093",          { "ULW1", },  {"ULR1", "ULRLT1",  "ULRC1", "ULRD1", "ULRMV1"}},
  {0x0C, "UL02", "KCS-093",          { "ULW2", },  {"ULR2", "ULRLT2",  "ULRC2", "ULRD2", "ULRMV2"}},
  {0x0D, "UL03", "KCS-093",          { "ULW3", },  {"ULR3", "ULRLT3",  "ULRC3", "ULRD3", "ULRMV3"}},
  {0x0E, "UL04", "KCS-093",          { "ULW4", },  {"ULR4", "ULRLT4",  "ULRC4", "ULRD4", "ULRMV4"}},
  {0x15, "UL05", "DL-2015",          { "ULW5", },  {"ULR5", "ULRLT5",  "", "", ""}},
  {0x1F, "UL06", "",                 { "ULW6", },  {"ULR6", "ULRLT6",  "ULRC5", "", ""}},
  {0x29, "UL07", "IS2000C-23M(Set)", { "ULW7", },  {"ULR7", "ULRQ1",  "", "", ""}},
  {0x33, "UL08", "",                 { "ULW8", },  {"ULR8", "ULRMV5", "ULRA1", "", ""}},
  {0x3D, "UL09", "",                 { "ULW9", },  {"ULR9", "ULRD1", "ULRW1", "ULRI1", ""}},
  {0x47, "UL10", "",                 { "ULW10",},  {"ULRBC1", "", "", "", ""}},

  {0x51, "UL11", "    ",             { "ULW11",},  {"ULR10", "ULRLT7",  "ULRA2", "", ""}},
  {0x52, "UL12", "    ",             { "ULW12",},  {"ULR11", "ULRLT8",  "ULRA3", "", ""}},
  {0x53, "UL13", "    ",             { "ULW13",},  {"ULR12", "ULRLT9",  "ULRA4", "", ""}},
  {0x54, "UL14", "    ",             { "ULW14",},  {"ULR13", "ULRLT10", "ULRA5", "", ""}},

  {0x5B, "UL15", "    ",             { "ULW15",},  {"ULR14", "ULRMV6", "ULRA6", "", ""}},
  {0x65, "UL16", "    ",             { "ULW16",},  {"ULR15", "ULRP1","", "", ""}},
  {0x6F, "UL17", "    ",             { "ULW17",},  {"ULR16", "ULRLT11", "", "", ""}},
  {0x70, "UL18", "    ",             { "ULW18",},  {"ULR17", "ULRLT12", "", "", ""}},
  {0x79, "UL19", "    ",             { "ULW19",},  {"ULR18", "ULRLT13", "", "", ""}},
  {0x7A, "UL20", "    ",             { "ULW20",},  {"ULR19", "ULRLT14", "", "", ""}},
  {0x83, "UL21", "    ",             { "ULW21",},  {"ULR20", "ULRLT15", "", "", ""}},
  {0x8D, "UL22", "    ",             { "ULW22",},  {"ULR21", "ULRLT16", "", "", ""}},
  {0x8E, "UL23", "    ",             { "ULW23",},  {"ULR22", "ULRLT17", "", "", ""}},
  {0x97, "UL24", "    ",             { "ULW24",},  {"ULR23", "ULRLT18", "", "", ""}},
  {0x98, "UL25", "    ",             { "ULW25",},  {"ULR24", "ULRLT19", "", "", ""}},
  {0xA1, "UL26", "    ",             { "ULW26",},  {"ULR25", "ULRLT20", "ULRP2", "", ""}},
  {0xA2, "UL27", "    ",             { "ULW27",},  {"ULR26", "ULRLT21", "ULRP3", "", ""}},
  {0xAB, "UL28", "    ",             { "ULW28",},  {"ULR27", "ULRLT22", "", "", ""}},
  {0xB5, "UL29", "    ",             { "ULW29",},  {"ULR28", "ULRLT23", "", "", ""}},
  {0xBF, "UL30", "    ",             { "ULW30",},  {"ULR29", "ULRLT24", "", "", ""}},
  {0xC9, "UL31", "    ",             { "ULW31",},  {"ULR30", "ULRLT25", "ULRMV7", "", ""}},
  {0xD3, "UL32", "    ",             { "ULW32",},  {"ULR31", "ULRQ2", "", "", ""}},
  {0xDD, "UL33", "    ",             { "ULW33",},  {"ULRD1", "ULRC6", "ULRL1", "", ""}},
};


int get_gdinfo_index(unsigned char id)
{
  int e = -1;
  int i = 0;
  for ( i=0 ; gdinfo[i].id != 0; i++ )
  {
    if ( gdinfo[i].id == id )
    {
      e = i;
      break;
    }
  }
  return e;
}

int wsgDBWrite(char* b, int sz)
{
  int  e = 0;
  int  idx = 0;
  int  i = 0;
  int  gindex = 0;
  char temp[32];
  char qval[32][32];
  char query[1024];
  unsigned char tm[32];

  time_t t = time(0);


  *(b + idx); idx++; //STX
  *(b + idx); idx++; //CMD
  *(b + idx); idx++; //LENGTH

  sprintf(qval[0], "%s", *(b + idx) == 0x00 ? STATUS_0 : *(b + idx) == 0x01 ? STATUS_1 : STATUS_2); idx++; //POWER ON/OFF
  sprintf(qval[1], "%d", ((*(b + idx) & 0xFF) * 256) + (*(b + idx + 1) & 0xFF)); idx += 2;
  sprintf(qval[2], "%d", ((*(b + idx) & 0xFF) * 256) + (*(b + idx + 1) & 0xFF)); idx += 2;
  sprintf(qval[3], "%d", ((*(b + idx) & 0xFF) * 256) + (*(b + idx + 1) & 0xFF)); idx += 2;
  *(b + idx); idx++; // 8
  *(b + idx); idx++; // 9
  *(b + idx); idx++; // 10
  *(b + idx); idx++; //Check SUM
  *(b + idx); idx++; //ETX


  gindex = get_gdinfo_index( *(b+1) );
  if ( gindex < 0 ) return 0;


  get_curr_time(tm, "-", "-", " ", ":", 0, 0, 0, 0, 0, 0);

  if (gp->pdbc != 0)
  {
    sprintf(query,
      "insert into Machine_Parameter_Out ( id, machine_code, parameter_code, status_log, date_time ) "
      "values "
      "("
      " (select machine_name from MACHINE where machine_code='%s'), '%s', '%s', '%s', '%s'"
      ")",
      gdinfo[gindex].did, gdinfo[gindex].did, gdinfo[gindex].rfactor[0], qval[0], tm);

    e = mdbcQuery(gp->pdbc, 0, query, strlen(query));
    if (e == 0)
    {
      #if LVLOG
      LVLog(gp->hitem[LIST_WSGW_DB_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "DB", "Query SUCCESS - %s \r\n", query);
      #endif
    }
    else
    {
      #if LVLOG
      LVLog(gp->hitem[LIST_WSGW_DB_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "DB", "Query FAIL - %s \r\n", query);
      #endif
    }

    #if DEBUG_LOCAL
    OutputDebugString(query);
    OutputDebugString("\r\n");
    #endif
  }
  else
  {
    wsgDBOpen();
  }



  return e;
}

#if 0
int wsgDBWrite(char* b, int sz)
{
  int  e = 0;
  int  idx = 0;
  int  i = 0;
  char temp[32];
  char qval[32][32];
  char query[1024];

  *(b+idx); idx++; //STX
  *(b+idx); idx++; //CMD
  *(b+idx); idx++; //LENGTH

  sprintf(qval[0], "%s", *(b+idx)==0x00?STATUS_0:*(b+idx)==0x01?STATUS_1:STATUS_2); idx++; //POWER ON/OFF



  #if 0
  if (  (*(b+1) == 0x01) || (*(b+1) == 0x10) )
  {
    sprintf(qval[1], "%d", ((*(b+idx)&0xFF)* 256) + (*(b+idx+1)&0xFF)); idx+=2;
    sprintf(qval[2], "%d", ((*(b+idx)&0xFF)* 256) + (*(b+idx+1)&0xFF)); idx+=2;
    sprintf(qval[3], "%d", ((*(b+idx)&0xFF)* 256) + (*(b+idx+1)&0xFF)); idx+=2;
    *(b+idx); idx++; // 8
    *(b+idx); idx++; // 9
    *(b+idx); idx++; // 10
  }
  *(b+idx); idx++; //Check SUM
  *(b+idx); idx++; //ETX
  #endif

  if ( gp->pdbc )
  {

    #if 0
    for ( i=0 ; qKey[*(b+1)-1][i][0] != 0 ; i++ )
    {
      memset(temp, 0, 32);
      if ( (*(b+1) == 0x01) && i==1 ) memcpy(temp, qval[3], 32);
      else if ( (*(b+1) == 0x10) && i==1 ) memcpy(temp, qval[1], 32);
      else memcpy(temp, qval[i], 32);

      wsgMakeQuery(b, qKey[*(b+1)-1][i], temp, query);
      OutputDebugString(query);
      OutputDebugString("\r\n");
      e = mdbcQuery(gp->pdbc, 0, query, strlen(query));
      if ( e == 0 )
      {
        #if LVLOG
        LVLog(gp->hitem[LIST_WSGW_DB_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "DB", "Query SUCCESS - %s \r\n", query);
        #endif
      }
      else
      {
        #if LVLOG
        LVLog(gp->hitem[LIST_WSGW_DB_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "DB", "Query FAIL - %s \r\n", query);
        #endif
      }
    }
    #endif


  }
  else
  {
    wsgDBOpen();
  }


  #if 0
  if ( gp->qcount == 100 )
  {
    unsigned char tm[32];
    
    LVLog(gp->hitem[LIST_WSGW_DB_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "DB", "%s Query Count %d\r\n", get_curr_time(tm, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0), gp->qcount);
    gp->qcount = 0;
  }
  gp->qcount++;
  #endif


  return e;
}
#endif

int wsgDBClose()
{
  return mdbcClose(&gp->pdbc);
}

void* wscDBConnectorStatus(int err)
{
  #if LVLOG
  if ( err == -1 )
  {
    LVLog(gp->hitem[LIST_WSGW_DB_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "DB", "Open (%s:%s:%s) Fail \r\n", DB_HOST, DB_PORT, DB_USER);
  }
  else if ( err == 1 )
  {
    LVLog(gp->hitem[LIST_WSGW_DB_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "DB", "Open (%s:%s:%s) Connecting... \r\n", DB_HOST, DB_PORT, DB_USER);
  }
  else
  {
    LVLog(gp->hitem[LIST_WSGW_DB_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "DB", "Open (%s:%s:%s) Success \r\n", DB_HOST, DB_PORT, DB_USER);
  }
  #endif
  return 0;
}

int wsgDBOpen()
{

  mdbcOpen(&gp->pdbc, DB_HOST, DB_PORT, DB_USER, DB_PASS, DB_NAME, wscDBConnectorStatus);


  //if ( mdbcOpen(&gp->pdbc, DB_HOST, DB_PORT, DB_USER, DB_PASS, DB_NAME) < 0 )
  //{
  //  LVLog(gp->hitem[LIST_WSGW_DB_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "DB", "Open (%s:%s:%s) Fail", DB_HOST, DB_PORT, DB_USER);
  //}
  //else
  //{
  //  LVLog(gp->hitem[LIST_WSGW_DB_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "DB", "Open (%s:%s:%s) Success", DB_HOST, DB_PORT, DB_USER);
  //}
  return 0;
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
/*                                                                             */
/*                                                                             */
/* Socket -> DB, WebSocket                                                     */
/*                                                                             */
/*                                                                             */
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/


void wwsgw_transfer(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{

  wsgWebSocketRouting((char*)lparam, (int)wparam);
  wsgDBWrite((char*)lparam, (int)wparam);

  ////GetComboText(gp->hitem[COMBO_DISPLAY_TYPE_WSGW], st);

  //fprint_raw_buffer(0, (char*)lparam, (int)wparam, vbuf);
  //LVLog(gp->hitem[LIST_WSGW_WS_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "WebSocket", "%s", vbuf);
}


void wwsgw_request(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  wsgSocketRequest(equip_ids[gp->equip_id]);
  gp->equip_id++;
  gp->equip_id %= EQUIP_IDS_COUNT;

  if ( equip_ids[gp->equip_id] == 0 ) gp->equip_id = 0;
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


void wwsgw_command(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  char port[2][32];
  char temp[32];

  switch (LOWORD(wparam))
  {
  case IDC_BUTTON_WSGW_START:
    GetText(gp->hitem[EDIT_WSGW_TCP_PORT], port[0], 32);
    GetText(gp->hitem[EDIT_WSGW_WS_PORT], port[1], 32);
    GetText(gp->hitem[BUTTON_WSGW_START], temp, 32);

    if ( strncmp(temp, "START", 5) == 0 )
    {
      if (wsgWebSocketOpen() < 0)
      {
        #if LVLOG
        LVLog(gp->hitem[LIST_WSGW_WS_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "WebSocket", "WebSocket Open Fail (%d) \r\n", gp->pm->mws.fd);
        #endif
        gp->REG.SR &= ~(0x00000001);
      }
      else
      {
        #if LVLOG
        LVLog(gp->hitem[LIST_WSGW_WS_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "WebSocket", "WebSocket Open Success (%d) \r\n", gp->pm->mws.fd);
        #endif
        gp->REG.SR |= 0x00000001;
      }
      if (wsgSocketOpen() < 0)
      {
        #if LVLOG
        LVLog(gp->hitem[LIST_WSGW_TCP_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "Socket", "Socket Open Fail (%d) \r\n", gp->pm->msck.fd);
        #endif
        gp->REG.SR &= ~(0x00000002);
      }
      else
      {
        #if LVLOG
        LVLog(gp->hitem[LIST_WSGW_TCP_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "Socket", "Socket Open Success (%d) \r\n", gp->pm->msck.fd);
        #endif
        gp->REG.SR |= 0x00000002;
      }

      if ( (gp->REG.SR & 0x00000003) == 0x00000003 )
      {
        SetText(gp->hitem[BUTTON_WSGW_START], "STOP", 4);
      }
      else
      {
        SetText(gp->hitem[BUTTON_WSGW_START], "START", 5);
      }
      gp->REG.SR = 0;
    }
    else
    {
      kill_timer(gp->hwnd, 1);
      #if LVLOG
      LVLog(gp->hitem[LIST_WSGW_TCP_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "Socket", "Socket Close (%d) \r\n", gp->pm->msck.fd);
      #endif
      wsgSocketClose();
      #if LVLOG
      LVLog(gp->hitem[LIST_WSGW_WS_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "WebSocket", "WebSocket Open Success (%d) \r\n", gp->pm->mws.fd);
      #endif
      wsgWebSocketClose();
      SetText(gp->hitem[BUTTON_WSGW_START], "START", 5);
    }
    break;


  case IDC_BUTTON_WSGW_CLEAR:
      ClearListView(gp->hitem[LIST_WSGW_TCP_LOG]);
      ClearListView(gp->hitem[LIST_WSGW_WS_LOG]);
      ClearListView(gp->hitem[LIST_WSGW_DB_LOG]);
    break;


  case IDC_CHECK_WSGW_REQ:
    if ( SendMessage(gp->hitem[CHECK_WSGW_REQ], BM_GETCHECK, 0, 0) != BST_CHECKED )
    {
      kill_timer(gp->hwnd, 1);
    }
    else
    {
      char msec[32];
      GetText(gp->hitem[EDIT_WSGW_MSEC], msec, 32);
      set_timer(gp->hwnd, 1, atoi(msec), on_req_timer);
    }

    break;

  }
}

void* wwsgw_dlgproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  switch (msg)
  {
  case WM_INITDIALOG:
    break;

  case WM_COMMAND:
    wwsgw_command(hwnd, msg, wparam, lparam);
    break;

  case XWM_TRANSFER:
    wwsgw_transfer(hwnd, msg, wparam, lparam);
    break;

  case XWM_REQ:
    wwsgw_request(hwnd, msg, wparam, lparam);
    break;

  default:
    break;
  }

  return 0;
}

void* wwsgw_init(HWND hwnd, wWSGW* p)
{
  int e;

  gp = p;

  gp->hwnd = hwnd;

  gp->hitem[EDIT_WSGW_TCP_PORT] = GetDlgItem(hwnd, IDC_EDIT_WSGW_TCP_PORT);
  gp->hitem[EDIT_WSGW_WS_PORT] = GetDlgItem(hwnd, IDC_EDIT_WSGW_WS_PORT);
  gp->hitem[CHECK_WSGW_LOG] = GetDlgItem(hwnd, IDC_CHECK_WSGW_LOG);
  gp->hitem[CHECK_WSGW_REQ] = GetDlgItem(hwnd, IDC_CHECK_WSGW_REQ);
  gp->hitem[BUTTON_WSGW_START] = GetDlgItem(hwnd, IDC_BUTTON_WSGW_START);
  gp->hitem[BUTTON_WSGW_CLEAR] = GetDlgItem(hwnd, IDC_BUTTON_WSGW_CLEAR);
  gp->hitem[LIST_WSGW_TCP_LOG] = GetDlgItem(hwnd, IDC_LIST_WSGW_TCP_LOG);
  gp->hitem[LIST_WSGW_WS_LOG] = GetDlgItem(hwnd, IDC_LIST_WSGW_WS_LOG);
  gp->hitem[LIST_WSGW_DB_LOG] = GetDlgItem(hwnd, IDC_LIST_WSGW_DB_LOG);
  gp->hitem[EDIT_WSGW_MSEC] = GetDlgItem(hwnd, IDC_EDIT_WSGW_MSEC);

  SetText(gp->hitem[EDIT_WSGW_TCP_PORT], "7870", 4);
  SetText(gp->hitem[EDIT_WSGW_WS_PORT], "7810", 4);

  SetText(gp->hitem[BUTTON_WSGW_START], "START", 5);
  SetText(gp->hitem[BUTTON_WSGW_CLEAR], "CLEAR", 5);

  SetText(gp->hitem[EDIT_WSGW_MSEC], "1000", 3);


  InitListView(gp->hitem[LIST_WSGW_TCP_LOG]);
  InitListView(gp->hitem[LIST_WSGW_WS_LOG]);
  InitListView(gp->hitem[LIST_WSGW_DB_LOG]);


  wsgDBOpen();


  return 0;
}
#endif

void* wwsgw_dlgproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  return 0;
}
void* wwsgw_init(HWND hwnd, wWSGW* p)
{
  return 0;
}
