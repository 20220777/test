#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <__npoint.h>
#include <njson.h>
#include <xcommon.h>
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////                                                                   //////
//////                                                                   //////
//////                          User Function                            //////
//////                                                                   //////
//////                                                                   //////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************/
/*****************************************************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*****************************                ********************************/
/*******************************            **********************************/
/*********************************        ************************************/
/************************************   **************************************/
/************************************* ***************************************/
/*****************************************************************************/
#include <__util.h>
#include <__nserial.h>
#include <__nhttpd.h>
#include <__nsocket.h>
#include <__nwebsocket.h>

#define __PID_STR_0__         "ksbridge.x32"


#if __NHTTP__
int32_t __liteio_http_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct _litePoint* liteP = (struct _litePoint*)h;
  if ( liteP == 0 ) return 0xEFFFFFFF;
  e = liteP->__writer[NHTTP](liteP->hdl[NHTTP], fd, b, sz, extra, liteP->hdl[NHTTP]);
  return e;
}
#endif

#if __NHTTP__
int32_t __liteio_http_close(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct _litePoint* liteP = (struct _litePoint*)h;
  if ( liteP == 0 ) return 0xEFFFFFFF;
  e = liteP->__closer[NHTTP](liteP->hdl[NHTTP], fd, b, sz, extra, liteP->hdl[NHTTP]);
  return e;
}
#endif


#if __NHTTPD__
int32_t __liteio_httpd_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct _litePoint* liteP = (struct _litePoint*)h;
  if ( liteP == 0 ) return 0xEFFFFFFF;
  e = liteP->__writer[NHTTPD](&liteP->__httpd, fd, b, sz, extra, &liteP->__httpd);
  return e;
}
#endif

#if __NHTTPD__
int32_t __liteio_httpd_close(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct _litePoint* liteP = (struct _litePoint*)h;
  if ( liteP == 0 ) return 0xEFFFFFFF;

  //DEBUG_PRINT(" %d : %d\r\n", liteP->__httpd.io.fd, fd);

  if ( liteP->__httpd.io.fd == fd )
  {
    e = liteP->__closer[NHTTPD](&liteP->__httpd, fd, b, sz, extra, &liteP->__httpd);
  }
  else
  {
    e = liteP->__closefd[NHTTPD](&liteP->__httpd, fd, b, sz, extra, &liteP->__httpd);
  }
  return e;
}
#endif



#if __NHTTPSD__
int32_t __liteio_httpsd_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct _litePoint* liteP = (struct _litePoint*)h;
  if ( liteP == 0 ) return 0xEFFFFFFF;
  e = liteP->__writer[NHTTPSD](liteP->hdl[NHTTPSD], fd, b, sz, extra, liteP->hdl[NHTTPSD]);
  return e;
}
#endif

#if __NHTTPSD__
int32_t __liteio_httpsd_close(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct _litePoint* liteP = (struct _litePoint*)h;
  if ( liteP == 0 ) return 0xEFFFFFFF;
  e = liteP->__closer[NHTTPSD](liteP->hdl[NHTTPSD], fd, b, sz, extra, liteP->hdl[NHTTPSD]);
  return e;
}
#endif

#if __NSERIAL__
int32_t __liteio_serial_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct _litePoint* liteP = (struct _litePoint*)h;
  if ( liteP == 0 ) return 0xEFFFFFFF;
  e = liteP->__writer[NSERIAL](&liteP->__serial, fd, b, sz, extra, &liteP->__serial);
  return e;
}
#endif

#if __NSERIAL__
int32_t __liteio_serial_close(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct _litePoint* liteP = (struct _litePoint*)h;
  if ( liteP == 0 ) return 0xEFFFFFFF;
  e = liteP->__closer[NSERIAL](&liteP->__serial, fd, b, sz, extra, &liteP->__serial);
  return e;
}
#endif

#if __NSOCKET__
int32_t __liteio_socket_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct _litePoint* liteP = (struct _litePoint*)h;
  if ( liteP == 0 ) return 0xEFFFFFFF;
  e = liteP->__writer[NSOCKET](&liteP->__socket, fd, b, sz, extra, &liteP->__socket);
  return e;
}
#endif

#if __NSOCKET__
int32_t __liteio_socket_close(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct _litePoint* liteP = (struct _litePoint*)h;
  if ( liteP == 0 ) return 0xEFFFFFFF;
  e = liteP->__closer[NSOCKET](&liteP->__socket, fd, b, sz, extra, &liteP->__socket);
  return e;
}
#endif

#if __NSHM__
int32_t __liteio_shm_read(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct _litePoint* liteP = (struct _litePoint*)h;
  if ( liteP == 0 ) return 0xEFFFFFFF;
  e = liteP->__reader[NSHM](liteP->hdl[NSHM], fd, b, sz, extra, liteP->hdl[NSHM]);
  return e;
}
#endif


#if __NSHM__
int32_t __liteio_shm_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct _litePoint* liteP = (struct _litePoint*)h;
  if ( liteP == 0 ) return 0xEFFFFFFF;
  e = liteP->__writer[NSHM](liteP->hdl[NSHM], fd, b, sz, extra, liteP->hdl[NSHM]);
  return e;
}
#endif

#if __NSHM__
int32_t __liteio_shm_close(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct _litePoint* liteP = (struct _litePoint*)h;
  if ( liteP == 0 ) return 0xEFFFFFFF;
  e = liteP->__closer[NSHM](liteP->hdl[NSHM], fd, b, sz, extra, liteP->hdl[NSHM]);
  return e;
}
#endif


#if __NWSC__
int32_t __liteio_wsc_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct _litePoint* liteP = (struct _litePoint*)h;
  if ( liteP == 0 ) return 0xEFFFFFFF;
  e = liteP->__writer[NWSC](liteP->hdl[NWSC], fd, b, sz, extra, liteP->hdl[NWSC]);
  return e;
}
#endif

#if __NWSC__
int32_t __liteio_wsc_close(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct _litePoint* liteP = (struct _litePoint*)h;
  if ( liteP == 0 ) return 0xEFFFFFFF;
  e = liteP->__closer[NWSC](liteP->hdl[NWSC], fd, b, sz, extra, liteP->hdl[NWSC]);
  return e;
}
#endif


#if __NWSD__
int32_t __liteio_wsd_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct _litePoint* liteP = (struct _litePoint*)h;
  if ( liteP == 0 ) return 0xEFFFFFFF;
  e = liteP->__writer[NWSD](liteP->hdl[NWSD], fd, b, sz, extra, liteP->hdl[NWSD]);
  return e;
}
#endif

#if __NWSD__
int32_t __liteio_wsd_close(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct _litePoint* liteP = (struct _litePoint*)h;
  if ( liteP == 0 ) return 0xEFFFFFFF;
  e = liteP->__closer[NWSD](liteP->hdl[NWSD], fd, b, sz, extra, liteP->hdl[NWSD]);
  return e;
}
#endif






#if __NTCP__
int32_t __liteio_tcp_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct _litePoint* liteP = (struct _litePoint*)h;
  if ( liteP == 0 ) return 0xEFFFFFFF;
  e = liteP->__writer[NTCP](liteP->hdl[NTCP], fd, b, sz, extra, liteP->hdl[NTCP]);
  return e;
}
#endif

#if __NTCP__
int32_t __liteio_tcp_close(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct _litePoint* liteP = (struct _litePoint*)h;
  if ( liteP == 0 ) return 0xEFFFFFFF;
  e = liteP->__closer[NTCP](liteP->hdl[NTCP], fd, b, sz, extra, liteP->hdl[NTCP]);
  return e;
}
#endif


#if __NTCPD__
int32_t __liteio_tcpd_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct _litePoint* liteP = (struct _litePoint*)h;
  if ( liteP == 0 ) return 0xEFFFFFFF;
  e = liteP->__writer[NTCPD](liteP->hdl[NTCPD], fd, b, sz, extra, liteP->hdl[NTCPD]);
  return e;
}
#endif

#if __NTCPD__
int32_t __liteio_tcpd_close(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct _litePoint* liteP = (struct _litePoint*)h;
  if ( liteP == 0 ) return 0xEFFFFFFF;
  e = liteP->__closer[NTCPD](liteP->hdl[NTCPD], fd, b, sz, extra, liteP->hdl[NTCPD]);
  return e;
}
#endif




#if __NTCPSD__
int32_t __liteio_tcpsd_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct _litePoint* liteP = (struct _litePoint*)h;
  if ( liteP == 0 ) return 0xEFFFFFFF;
  e = liteP->__writer[NTCPSD](liteP->hdl[NTCPSD], fd, b, sz, extra, liteP->hdl[NTCPSD]);
  return e;
}
#endif

#if __NTCPSD__
int32_t __liteio_tcpsd_close(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct _litePoint* liteP = (struct _litePoint*)h;
  if ( liteP == 0 ) return 0xEFFFFFFF;
  e = liteP->__closer[NTCPSD](liteP->hdl[NTCPSD], fd, b, sz, extra, liteP->hdl[NTCPSD]);
  return e;
}
#endif
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////                                                                   //////
//////                                                                   //////
//////                           Entry Point                             //////
//////                                                                   //////
//////                                                                   //////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************/
/*****************************************************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*****************************                ********************************/
/*******************************            **********************************/
/*********************************        ************************************/
/************************************   **************************************/
/************************************* ***************************************/
/*****************************************************************************/
#if 0
int32_t set_item(nItems* p, void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t idx = -1;

  for ( ; ;)
  {
    xLOCK(&p->crit); 
    if ( p->itm[p->p[1]].h == 0 )
    {
      p->itm[p->p[1]].h = h;
      p->itm[p->p[1]].fd = fd;
      p->itm[p->p[1]].b = b;
      p->itm[p->p[1]].sz = sz;
      p->itm[p->p[1]].extra = extra;
      p->itm[p->p[1]].o = o;
      idx = p->p[1];
      xUNLOCK(&p->crit); 
      break;
    }
    p->p[1]++;
    p->p[1] %= NITEM_MAX;
    xUNLOCK(&p->crit); 
  }
  return idx;
}

int32_t get_item(nItems* p)
{
  int32_t idx = -1;

  xLOCK(&p->crit); 
  if ( p->itm[p->p[0]].h )
  {
    idx = p->p[0];
    p->itm[p->p[0]].h = 0;
    p->p[0]++;
    p->p[0] %= NITEM_MAX;
  }
  xUNLOCK(&p->crit); 
  return idx;
}
#endif

int32_t __liteio_call(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  struct _litePoint* p = (struct _litePoint*)o;
  int32_t e = 0;

  DEBUG_PRINT(" p->arg : %s\r\n", p->arg?"NOT NULL":"NULL");

  if ( p->arg==0 ) return -1;

  ((struct nArg*)p->arg)->fd = fd;
  ((struct nArg*)p->arg)->b = b;
  ((struct nArg*)p->arg)->sz = sz;

  #if 0
  DEBUG_PRINT(" sz : %d(%08X) \r\n"
              "--------------------------------------------------------------------------------\r\n"
              "%s\r\n"
              "================================================================================\r\n", sz, sz, b);
  #endif

  DEBUG_PRINT("%d -> %08X(%d) \r\n", fd, sz, sz);

  #if 1
  DEBUG_PRINT("--->>>--->>>--->>>--->>>--->>>--->>>--->>>--->>>\r\n");
  if ( p->fx[0] ) e = p->fx[0](p->obj, p->arg);
  DEBUG_PRINT("<<<---<<<---<<<---<<<---<<<---<<<---<<<---<<<---\r\n");
  #endif

  return e;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////                                                                   //////
//////                                                                   //////
//////                           Entry Point                             //////
//////                                                                   //////
//////                                                                   //////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************/
/*****************************************************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*****************************                ********************************/
/*******************************            **********************************/
/*********************************        ************************************/
/************************************   **************************************/
/************************************* ***************************************/
/*****************************************************************************/

#define ARRAY_DIM              16

int32_t dlmt_string(int8_t* str, int8_t* out)
{
  int32_t i = 0;
  int32_t e = 0;

  for ( i=0 ;  ; i++ )
  {
    e = __get_dlmtr_str(str, ',', i, out+(ARRAY_DIM*i));
    if ( e <= 0 ) break;
  }

  return i;
}


void* setup(void* arg)
{
  int32_t e = 0;
  struct _litePoint* liteP = (struct _litePoint*)arg;
  int8_t _argv[1024] = {0};
  int8_t _cmd[1024] = {0}; /// 16 length array
  int8_t* pcmd = _cmd;
  int32_t c = 0;

  readArgs(liteP->argc, liteP->argv, "--exec", _argv);

  c = dlmt_string(_argv, _cmd);

  DEBUG_PRINT("%s \r\n", _argv);

  for ( ; c>0 ; c-- )
  {
    pcmd = _cmd+(ARRAY_DIM*(c-1));
    #if __NHTTPD__
    if ( strcompare(pcmd, "httpd") == 0 )
    {
      liteP->__writer[NHTTPD] = __nhttpd_write;
      liteP->__closer[NHTTPD] = __nhttpd_close;
      liteP->__closefd[NHTTPD] = __nhttpd_close_fd;

      readArgs(liteP->argc, liteP->argv, "--httpd_port",             liteP->__httpd.io.argv[HTTP_PORT]);
      readArgs(liteP->argc, liteP->argv, "--httpd_home",             liteP->__httpd.io.argv[HTTP_HOME]);
      readArgs(liteP->argc, liteP->argv, "--httpd_size_of_buffer",   liteP->__httpd.io.argv[SIZE_OF_BUFFER]);

      DEBUG_PRINT("%s, %s\r\n",
					  liteP->__httpd.io.argv[HTTP_PORT],
            liteP->__httpd.io.argv[HTTP_HOME]);

      liteP->__httpd.io.__f[__CALLBACK_CONNECTED] = __liteio_call;
      liteP->__httpd.io.__f[__CALLBACK_DISCONNECTED] = __liteio_call;
      liteP->__httpd.io.__f[__CALLBACK_READ] = __liteio_call;
      liteP->__httpd.io.__o = liteP;

      e = __nhttpd_open(&liteP->__httpd);
      DEBUG_PRINT(" __nhttpd_open : %08X(%d) \r\n", e,e);
    }
    #endif

    #if __NHTTPSD__
    if ( strcompare(pcmd, "httpsd") == 0 )
    {
      e=nhttpsd(liteP);
      liteP->__loop[NHTTPSD] = nhttpsd_loop;
      liteP->__writer[NHTTPSD] = nhttpsd_writer;
      liteP->__closer[NHTTPSD] = nhttpsd_closer;
    }
    #endif

    #if __NHTTP__
    if ( strcompare(pcmd, "http") == 0 )
    {
      e=nhttp(liteP);
      liteP->__loop[NHTTP] = nhttp_loop;
      liteP->__writer[NHTTP] = nhttp_writer;
      liteP->__closer[NHTTP] = nhttp_closer;
    }
    #endif

    #if __NSERIAL__
    if ( strcompare(pcmd, "serial") == 0 )
    {
      //e=nserial(liteP);
      //liteP->__loop[NSERIAL] = nserial_loop;
      liteP->__writer[NSERIAL] = __nserial_write;
      liteP->__closer[NSERIAL] = __nserial_close;


      readArgs(liteP->argc, liteP->argv, "--serial_port", liteP->__serial.io.argv[SERIAL_PORT]);
      readArgs(liteP->argc, liteP->argv, "--serial_baudrate", liteP->__serial.io.argv[SERIAL_BAUDRATE]);
      readArgs(liteP->argc, liteP->argv, "--serial_size_of_buffer", liteP->__serial.io.argv[SIZE_OF_BUFFER]);

      sprintf(liteP->__serial.io.argv[SERIAL_DATABIT], "8");
      sprintf(liteP->__serial.io.argv[SERIAL_STOPBIT], "1");
      sprintf(liteP->__serial.io.argv[SERIAL_PARITYBIT], "0");

      DEBUG_PRINT("%s, %s, %s, %s, %s, %s\r\n",
            liteP->__serial.io.argv[SERIAL_PORT],
					  liteP->__serial.io.argv[SERIAL_BAUDRATE],
					  liteP->__serial.io.argv[SIZE_OF_BUFFER],
            liteP->__serial.io.argv[SERIAL_DATABIT],
            liteP->__serial.io.argv[SERIAL_STOPBIT],
            liteP->__serial.io.argv[SERIAL_PARITYBIT]);


      liteP->__serial.io.__f[__CALLBACK_READ] = __liteio_call;
      liteP->__serial.io.__o = liteP;

      e = __nserial_open(&liteP->__serial);
      DEBUG_PRINT(" __nserial_open : %08X(%d) \r\n", e,e);
    }
    #endif


    #if __NSOCKET__
    if ( strcompare(pcmd, "socket") == 0 )
    {
      liteP->__writer[NSOCKET] = __nsocket_write;
      liteP->__closer[NSOCKET] = __nsocket_close;
      liteP->__closefd[NSOCKET] = __nsocket_close_fd;


      readArgs(liteP->argc, liteP->argv, "--socket_ip",             liteP->__socket.io.argv[SOCKET_IP]);
      readArgs(liteP->argc, liteP->argv, "--socket_port",           liteP->__socket.io.argv[SOCKET_PORT]);
      readArgs(liteP->argc, liteP->argv, "--socket_cstype",         liteP->__socket.io.argv[SOCKET_CSTYPE]);
      readArgs(liteP->argc, liteP->argv, "--socket_protocol",       liteP->__socket.io.argv[SOCKET_PROTOCOL]);
      readArgs(liteP->argc, liteP->argv, "--socket_casttype",       liteP->__socket.io.argv[SOCKET_CASTTYPE]);
      readArgs(liteP->argc, liteP->argv, "--socket_size_of_buffer", liteP->__socket.io.argv[SIZE_OF_BUFFER]);

      DEBUG_PRINT("%s, %s, %s, %s, %s, %s\r\n",
            liteP->__socket.io.argv[SOCKET_IP],
					  liteP->__socket.io.argv[SOCKET_PORT],
					  liteP->__socket.io.argv[SOCKET_CSTYPE],
            liteP->__socket.io.argv[SOCKET_PROTOCOL],
            liteP->__socket.io.argv[SOCKET_CASTTYPE],
            liteP->__socket.io.argv[SIZE_OF_BUFFER]);


      liteP->__socket.io.__f[__CALLBACK_CONNECTED] = __liteio_call;
      liteP->__socket.io.__f[__CALLBACK_DISCONNECTED] = __liteio_call;
      liteP->__socket.io.__f[__CALLBACK_READ] = __liteio_call;
      liteP->__socket.io.__o = liteP;

      e = __nsocket_open(&liteP->__socket);
      DEBUG_PRINT(" __nsocket_open : %08X(%d) \r\n", e,e);
    }
    #endif

    #if __NTCP__
    if ( strcompare(pcmd, "tcp") == 0 )
    {
      liteP->__writer[NTCP] = __ntcp_write;
      liteP->__closer[NTCP] = __ntcp_close;


      readArgs(liteP->argc, liteP->argv, "--tcp_ip",             liteP->__tcp.io.argv[SOCKET_IP]);
      readArgs(liteP->argc, liteP->argv, "--tcp_port",           liteP->__tcp.io.argv[SOCKET_PORT]);
      readArgs(liteP->argc, liteP->argv, "--tcp_size_of_buffer", liteP->__tcp.io.argv[SIZE_OF_BUFFER]);

      sprintf(liteP->__tcp.io.argv[SOCKET_CSTYPE],   "CLIENT");
      sprintf(liteP->__tcp.io.argv[SOCKET_PROTOCOL], "TCP");
      sprintf(liteP->__tcp.io.argv[SOCKET_CASTTYPE], "UNICAST");

      DEBUG_PRINT("%s, %s, %s, %s, %s, %s\r\n",
            liteP->__tcp.io.argv[SOCKET_IP],
					  liteP->__tcp.io.argv[SOCKET_PORT],
					  liteP->__tcp.io.argv[SOCKET_CSTYPE],
            liteP->__tcp.io.argv[SOCKET_PROTOCOL],
            liteP->__tcp.io.argv[SOCKET_CASTTYPE],
            liteP->__tcp.io.argv[SIZE_OF_BUFFER]);


      liteP->__tcp.io.__f[__CALLBACK_CONNECTED] = __liteio_call;
      liteP->__tcp.io.__f[__CALLBACK_DISCONNECTED] = __liteio_call;
      liteP->__tcp.io.__f[__CALLBACK_READ] = __liteio_call;
      liteP->__tcp.io.__o = liteP;

      e = __ntcp_open(&liteP->__tcp);
      DEBUG_PRINT(" __ntcp_open : %08X(%d) \r\n", e,e);
    }
    #endif

    #if __NTCPD__
    if ( strcompare(pcmd, "tcpd") == 0 )
    {
      liteP->__writer[NTCPD] = __nsocket_write;
      liteP->__closer[NTCPD] = __nsocket_close;


      readArgs(liteP->argc, liteP->argv, "--tcpd_ip",             liteP->__tcpd.io.argv[SOCKET_IP]);
      readArgs(liteP->argc, liteP->argv, "--tcpd_port",           liteP->__tcpd.io.argv[SOCKET_PORT]);
      readArgs(liteP->argc, liteP->argv, "--tcpd_size_of_buffer", liteP->__tcpd.io.argv[SIZE_OF_BUFFER]);

      sprintf(liteP->__tcpd.io.argv[SOCKET_CSTYPE],   "SERVER");
      sprintf(liteP->__tcpd.io.argv[SOCKET_PROTOCOL], "TCP");
      sprintf(liteP->__tcpd.io.argv[SOCKET_CASTTYPE], "UNICAST");

      DEBUG_PRINT("%s, %s, %s, %s, %s, %s\r\n",
            liteP->__tcpd.io.argv[SOCKET_IP],
					  liteP->__tcpd.io.argv[SOCKET_PORT],
					  liteP->__tcpd.io.argv[SOCKET_CSTYPE],
            liteP->__tcpd.io.argv[SOCKET_PROTOCOL],
            liteP->__tcpd.io.argv[SOCKET_CASTTYPE],
            liteP->__tcpd.io.argv[SIZE_OF_BUFFER]);


      liteP->__tcpd.io.__f[__CALLBACK_CONNECTED] = __liteio_call;
      liteP->__tcpd.io.__f[__CALLBACK_DISCONNECTED] = __liteio_call;
      liteP->__tcpd.io.__f[__CALLBACK_READ] = __liteio_call;
      liteP->__tcpd.io.__o = liteP;

      e = __nsocket_open(&liteP->__tcpd);
      DEBUG_PRINT(" __nsocket_open : %08X(%d) \r\n", e,e);
    }
    #endif

    #if __NTCPSD__
    if ( strcompare(pcmd, "tcpsd") == 0 )
    {
      e=ntcpsd(liteP);
      liteP->__loop[NTCPSD] = ntcpsd_loop;
      liteP->__writer[NTCPSD] = ntcpsd_writer;
      liteP->__closer[NTCPSD] = ntcpsd_closer;
    }
    #endif


    #if __NWSD__
    if ( strcompare(pcmd, "wsd") == 0 )
    {
      e=nwsd(liteP);
      liteP->__loop[NWSD] = nwsd_loop;
      liteP->__writer[NWSD] = nwsd_writer;
      liteP->__closer[NWSD] = nwsd_closer;
    }
    #endif

    #if __NWSC__
    if ( strcompare(pcmd, "wsc") == 0 )
    {
      e=nwsc(liteP);
      liteP->__loop[NWSC] = nwsc_loop;
      liteP->__writer[NWSC] = nwsc_writer;
      liteP->__closer[NWSC] = nwsc_closer;
    }
    #endif


    #if __NSHM__
    if ( strcompare(pcmd, "shm") == 0 )
    {
      e=nshm(liteP);
      liteP->__loop[NSHM] = nshm_loop;
      liteP->__reader[NSHM] = nshm_reader;
      liteP->__writer[NSHM] = nshm_writer;
      liteP->__closer[NSHM] = nshm_closer;
    }
    #endif


  }
  return e;
}


void* loop(void* arg)
{

  #if 0
  struct _litePoint* liteP = (struct _litePoint*)arg;
  uint32_t i = 0;
  for ( ; i<NMAX ; i++)
  {
    if ( liteP->__loop[i] ) liteP->__loop[i](liteP);
  }
  #endif
  return 0;
}


int32_t __initia(void** hdl, int32_t (*fx[])(void*,void*), void* obj, void* arg, int32_t argc, int8_t** argv)
{
  int32_t e = 0;
  struct _litePoint* liteP;
  *hdl = liteP = (struct _litePoint*)calloc(1, sizeof(struct _litePoint));

  liteP->argc = argc;
  liteP->argv = argv;

  liteP->obj = obj;
  liteP->arg = arg;

  if ( fx )
  {
    liteP->fx[0] = fx[0];
  }
  DEBUG_PRINT("%08X \r\n", liteP);
  e = __nmain(argc, argv, setup, loop, liteP);

  return e;
}

#if __NODE__

#else
int32_t main(int32_t argc, int8_t** argv)
{
  void* h;
  return __initia(&h, 0, 0, 0, argc, argv);
}
#endif






#if 0

24 x 7

audit deamon

csh

awk

ps -aef | grep node | grep -v grep | awk '{print $2}'

kill -9 `ps -aef | grep node | grep -v grep | awk '{print $2}'`


#endif
