#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <liteio.h>
#include <njson.h>
#include <nutil.h>
#include <imtif.h>

#include <idebug.h>
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
//#include <nm.h>
// #include <nwsc.h>
// #include <ntcp.h>
// #include <nhttp.h>
// #include <nhttpd.h>
// #include <nserial.h>
//#include <nzigbee.h>
#include <nhttpd.h>
#include <nhttp.h>
#include <nhttpsd.h>
#include <nserial.h>
#include <ntcp.h>
#include <ntcpd.h>
#include <ntcpsd.h>
#include <nwsc.h>
#include <nwsd.h>
#include <nshm.h>


#define __PID_STR_0__         "ksbridge.x32"


#if __NHTTP__
int32_t __liteio_http_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct cnLiteIO* liteio = (struct cnLiteIO*)h;
  if ( liteio == 0 ) return 0xEFFFFFFF;
  e = liteio->__writer[NHTTP](liteio->hdl[NHTTP], fd, b, sz, extra, liteio->hdl[NHTTP]);
  return e;
}
#endif

#if __NHTTP__
int32_t __liteio_http_close(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct cnLiteIO* liteio = (struct cnLiteIO*)h;
  if ( liteio == 0 ) return 0xEFFFFFFF;
  e = liteio->__closer[NHTTP](liteio->hdl[NHTTP], fd, b, sz, extra, liteio->hdl[NHTTP]);
  return e;
}
#endif


#if __NHTTPD__
int32_t __liteio_httpd_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct cnLiteIO* liteio = (struct cnLiteIO*)h;
  if ( liteio == 0 ) return 0xEFFFFFFF;
  e = liteio->__writer[NHTTPD](liteio->hdl[NHTTPD], fd, b, sz, extra, liteio->hdl[NHTTPD]);
  return e;
}
#endif

#if __NHTTPD__
int32_t __liteio_httpd_close(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct cnLiteIO* liteio = (struct cnLiteIO*)h;
  if ( liteio == 0 ) return 0xEFFFFFFF;
  e = liteio->__closer[NHTTPD](liteio->hdl[NHTTPD], fd, b, sz, extra, liteio->hdl[NHTTPD]);
  return e;
}
#endif



#if __NHTTPSD__
int32_t __liteio_httpsd_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct cnLiteIO* liteio = (struct cnLiteIO*)h;
  if ( liteio == 0 ) return 0xEFFFFFFF;
  e = liteio->__writer[NHTTPSD](liteio->hdl[NHTTPSD], fd, b, sz, extra, liteio->hdl[NHTTPSD]);
  return e;
}
#endif

#if __NHTTPSD__
int32_t __liteio_httpsd_close(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct cnLiteIO* liteio = (struct cnLiteIO*)h;
  if ( liteio == 0 ) return 0xEFFFFFFF;
  e = liteio->__closer[NHTTPSD](liteio->hdl[NHTTPSD], fd, b, sz, extra, liteio->hdl[NHTTPSD]);
  return e;
}
#endif

#if __NSERIAL__
int32_t __liteio_serial_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct cnLiteIO* liteio = (struct cnLiteIO*)h;
  if ( liteio == 0 ) return 0xEFFFFFFF;
  e = liteio->__writer[NSERIAL](liteio->hdl[NSERIAL], fd, b, sz, extra, liteio->hdl[NSERIAL]);
  return e;
}
#endif

#if __NSERIAL__
int32_t __liteio_serial_close(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct cnLiteIO* liteio = (struct cnLiteIO*)h;
  if ( liteio == 0 ) return 0xEFFFFFFF;
  e = liteio->__closer[NSERIAL](liteio->hdl[NSERIAL], fd, b, sz, extra, liteio->hdl[NSERIAL]);
  return e;
}
#endif

#if __NSHM__
int32_t __liteio_shm_read(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct cnLiteIO* liteio = (struct cnLiteIO*)h;
  if ( liteio == 0 ) return 0xEFFFFFFF;
  e = liteio->__reader[NSHM](liteio->hdl[NSHM], fd, b, sz, extra, liteio->hdl[NSHM]);
  return e;
}
#endif


#if __NSHM__
int32_t __liteio_shm_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct cnLiteIO* liteio = (struct cnLiteIO*)h;
  if ( liteio == 0 ) return 0xEFFFFFFF;
  e = liteio->__writer[NSHM](liteio->hdl[NSHM], fd, b, sz, extra, liteio->hdl[NSHM]);
  return e;
}
#endif

#if __NSHM__
int32_t __liteio_shm_close(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct cnLiteIO* liteio = (struct cnLiteIO*)h;
  if ( liteio == 0 ) return 0xEFFFFFFF;
  e = liteio->__closer[NSHM](liteio->hdl[NSHM], fd, b, sz, extra, liteio->hdl[NSHM]);
  return e;
}
#endif


#if __NWSC__
int32_t __liteio_wsc_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct cnLiteIO* liteio = (struct cnLiteIO*)h;
  if ( liteio == 0 ) return 0xEFFFFFFF;
  e = liteio->__writer[NWSC](liteio->hdl[NWSC], fd, b, sz, extra, liteio->hdl[NWSC]);
  return e;
}
#endif

#if __NWSC__
int32_t __liteio_wsc_close(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct cnLiteIO* liteio = (struct cnLiteIO*)h;
  if ( liteio == 0 ) return 0xEFFFFFFF;
  e = liteio->__closer[NWSC](liteio->hdl[NWSC], fd, b, sz, extra, liteio->hdl[NWSC]);
  return e;
}
#endif


#if __NWSD__
int32_t __liteio_wsd_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct cnLiteIO* liteio = (struct cnLiteIO*)h;
  if ( liteio == 0 ) return 0xEFFFFFFF;
  e = liteio->__writer[NWSD](liteio->hdl[NWSD], fd, b, sz, extra, liteio->hdl[NWSD]);
  return e;
}
#endif

#if __NWSD__
int32_t __liteio_wsd_close(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct cnLiteIO* liteio = (struct cnLiteIO*)h;
  if ( liteio == 0 ) return 0xEFFFFFFF;
  e = liteio->__closer[NWSD](liteio->hdl[NWSD], fd, b, sz, extra, liteio->hdl[NWSD]);
  return e;
}
#endif






#if __NTCP__
int32_t __liteio_tcp_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct cnLiteIO* liteio = (struct cnLiteIO*)h;
  if ( liteio == 0 ) return 0xEFFFFFFF;
  e = liteio->__writer[NTCP](liteio->hdl[NTCP], fd, b, sz, extra, liteio->hdl[NTCP]);
  return e;
}
#endif

#if __NTCP__
int32_t __liteio_tcp_close(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct cnLiteIO* liteio = (struct cnLiteIO*)h;
  if ( liteio == 0 ) return 0xEFFFFFFF;
  e = liteio->__closer[NTCP](liteio->hdl[NTCP], fd, b, sz, extra, liteio->hdl[NTCP]);
  return e;
}
#endif


#if __NTCPD__
int32_t __liteio_tcpd_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct cnLiteIO* liteio = (struct cnLiteIO*)h;
  if ( liteio == 0 ) return 0xEFFFFFFF;
  e = liteio->__writer[NTCPD](liteio->hdl[NTCPD], fd, b, sz, extra, liteio->hdl[NTCPD]);
  return e;
}
#endif

#if __NTCPD__
int32_t __liteio_tcpd_close(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct cnLiteIO* liteio = (struct cnLiteIO*)h;
  if ( liteio == 0 ) return 0xEFFFFFFF;
  e = liteio->__closer[NTCPD](liteio->hdl[NTCPD], fd, b, sz, extra, liteio->hdl[NTCPD]);
  return e;
}
#endif




#if __NTCPSD__
int32_t __liteio_tcpsd_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct cnLiteIO* liteio = (struct cnLiteIO*)h;
  if ( liteio == 0 ) return 0xEFFFFFFF;
  e = liteio->__writer[NTCPSD](liteio->hdl[NTCPSD], fd, b, sz, extra, liteio->hdl[NTCPSD]);
  return e;
}
#endif

#if __NTCPSD__
int32_t __liteio_tcpsd_close(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  struct cnLiteIO* liteio = (struct cnLiteIO*)h;
  if ( liteio == 0 ) return 0xEFFFFFFF;
  e = liteio->__closer[NTCPSD](liteio->hdl[NTCPSD], fd, b, sz, extra, liteio->hdl[NTCPSD]);
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

int32_t __liteio_call(struct cnLiteIO* p, uint32_t ecode, int32_t fd, int8_t* b, int32_t sz)
{
  int32_t e = 0;

  if ( p->arg==0 ) return -1;

  ((struct nArg*)p->arg)->ecode = ecode;
  ((struct nArg*)p->arg)->fd = fd;
  ((struct nArg*)p->arg)->b = b;
  ((struct nArg*)p->arg)->sz = sz;


  DEBUG_PRINT(" sz : %d, ecode : %d(%08X) \r\n"
              "--------------------------------------------------------------------------------\r\n"
              "%s\r\n"
              "================================================================================\r\n", sz, ecode, ecode, b);

  #if 0
  printf(" %16s:%6d | sz : %d, ecode : %d\r\n"
         "================================================\r\n"
         "%s\r\n"
         "================================================\r\n",
         __FUNCTION__,__LINE__, sz,ecode,b);
  #endif

  if ( p->fx[0] ) e = p->fx[0](p->obj, p->arg);
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
  struct cnLiteIO* liteio = (struct cnLiteIO*)arg;
  int8_t _argv[1024] = {0};
  int8_t _cmd[1024] = {0}; /// 16 length array
  int8_t* pcmd = _cmd;
  int32_t c = 0;

  readArgs(liteio->argc, liteio->argv, "--exec", _argv);

  c = dlmt_string(_argv, _cmd);

  DEBUG_PRINT("%s \r\n", _argv);

  for ( ; c>0 ; c-- )
  {
    pcmd = _cmd+(ARRAY_DIM*(c-1));
    #if __NHTTPD__
    if ( strcompare(pcmd, "httpd") == 0 )
    {
      e=nhttpd(liteio);
      liteio->__loop[NHTTPD] = nhttpd_loop;
      liteio->__writer[NHTTPD] = nhttpd_writer;
      liteio->__closer[NHTTPD] = nhttpd_closer;
    }
    #endif

    #if __NHTTPSD__
    if ( strcompare(pcmd, "httpsd") == 0 )
    {
      e=nhttpsd(liteio);
      liteio->__loop[NHTTPSD] = nhttpsd_loop;
      liteio->__writer[NHTTPSD] = nhttpsd_writer;
      liteio->__closer[NHTTPSD] = nhttpsd_closer;
    }
    #endif

    #if __NHTTP__
    if ( strcompare(pcmd, "http") == 0 )
    {
      e=nhttp(liteio);
      liteio->__loop[NHTTP] = nhttp_loop;
      liteio->__writer[NHTTP] = nhttp_writer;
      liteio->__closer[NHTTP] = nhttp_closer;
    }
    #endif

    #if __NSERIAL__
    if ( strcompare(pcmd, "serial") == 0 )
    {
      e=nserial(liteio);
      liteio->__loop[NSERIAL] = nserial_loop;
      liteio->__writer[NSERIAL] = nserial_writer;
      liteio->__closer[NSERIAL] = nserial_closer;
    }
    #endif

    #if __NTCPD__
    if ( strcompare(pcmd, "tcpd") == 0 )
    {
      e=ntcpd(liteio);
      liteio->__loop[NTCPD] = ntcpd_loop;
      liteio->__writer[NTCPD] = ntcpd_writer;
      liteio->__closer[NTCPD] = ntcpd_closer;
    }
    #endif

    #if __NTCPSD__
    if ( strcompare(pcmd, "tcpsd") == 0 )
    {
      e=ntcpsd(liteio);
      liteio->__loop[NTCPSD] = ntcpsd_loop;
      liteio->__writer[NTCPSD] = ntcpsd_writer;
      liteio->__closer[NTCPSD] = ntcpsd_closer;
    }
    #endif

    #if __NTCP__
    if ( strcompare(pcmd, "tcp") == 0 )
    {
      e=ntcp(liteio);
      liteio->__loop[NTCP] = ntcp_loop;
      liteio->__writer[NTCP] = ntcp_writer;
      liteio->__closer[NTCP] = ntcp_closer;
    }
    #endif

    #if __NWSD__
    if ( strcompare(pcmd, "wsd") == 0 )
    {
      e=nwsd(liteio);
      liteio->__loop[NWSD] = nwsd_loop;
      liteio->__writer[NWSD] = nwsd_writer;
      liteio->__closer[NWSD] = nwsd_closer;
    }
    #endif

    #if __NWSC__
    if ( strcompare(pcmd, "wsc") == 0 )
    {
      e=nwsc(liteio);
      liteio->__loop[NWSC] = nwsc_loop;
      liteio->__writer[NWSC] = nwsc_writer;
      liteio->__closer[NWSC] = nwsc_closer;
    }
    #endif


    #if __NSHM__
    if ( strcompare(pcmd, "shm") == 0 )
    {
      e=nshm(liteio);
      liteio->__loop[NSHM] = nshm_loop;
      liteio->__reader[NSHM] = nshm_reader;
      liteio->__writer[NSHM] = nshm_writer;
      liteio->__closer[NSHM] = nshm_closer;
    }
    #endif


  }
  return e;
}


void* loop(void* arg)
{
  struct cnLiteIO* liteio = (struct cnLiteIO*)arg;
  uint32_t i = 0;
  for ( ; i<NMAX ; i++)
  {
    if ( liteio->__loop[i] ) liteio->__loop[i](liteio);
  }
  return 0;
}


int32_t __initia(void** hdl, int32_t (*fx[])(void*,void*), void* obj, void* arg, int32_t argc, int8_t** argv)
{
  int32_t e = 0;
  struct cnLiteIO* liteio;
  *hdl = liteio = (struct cnLiteIO*)calloc(1, sizeof(struct cnLiteIO));

  liteio->argc = argc;
  liteio->argv = argv;

  liteio->obj = obj;
  liteio->arg = arg;

  if ( fx )
  {
    liteio->fx[0] = fx[0];
  }
  DEBUG_PRINT("%08X \r\n", liteio);
  e = __nmain(argc, argv, setup, loop, liteio);

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
