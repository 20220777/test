#if __NHTTPD__
#include <nhttpd.h>
#include <nutil.h>
#include <nm.h>
#include <idebug.h>

// #include <nshm.h>

#include <nutils.h>

int32_t nhttpd_closer(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnhttpd* p = (cnhttpd*)o;
  int32_t e = 0;

  DEBUG_PRINT("close -> %d %08X\r\n", fd, fd);
  e=__httpd_close_fd(p->_imtif.h, fd);
  return e;
}


int32_t nhttpd_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  DEBUG_PRINT(" ---------------------->   %08X\r\n", fd);

  DEBUG_PRINT("%4d:%4d\r\n%s\r\n", fd, sz, b);
  return write(fd, b, sz);
}

int32_t nhttpd_writer(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  int8_t ack[1024] = {0};
  cnhttpd* p = (cnhttpd*)o;

  if ( (int32_t)extra == 'H' )
  {
    sprintf(ack,
          "HTTP/1.1 %d %s\r\n" 
          "Cache-Control: no-cache\r\n"
          "Content-Type: text/html\r\n\r\n", e<0?404:200, e<0?"Not Found":"OK");

    DEBUG_PRINT("%4d:%4d\r\n%s\r\n",fd, strlen(ack), ack);
    e=__httpd_write(p->_imtif.h, fd, ack, strlen(ack), 0, o);
  }
  DEBUG_PRINT("%08X:%4d:%4d\r\n%s\r\n",p,fd, sz, b);
  e=__httpd_write(p->_imtif.h, fd, b, sz, 0, o);

  DEBUG_PRINT("e -> %d %08X\r\n", e, e);

  return e;
}

int32_t nhttpd_proc(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  int32_t i = 0;
  int8_t uri[2][4096] = {0};
  cnhttpd* p = (cnhttpd*)o;
  const int8_t tasks[][256] = { 
    #include "../i/winterface.i"
  };

  e = get_dlmtr(b, '?', 0, uri[0]);
  if ( e>0 ) uri[0][e] = 0;

  e = get_dlmtr(b, '?', 1, uri[1]);
  if ( e>0 ) uri[1][e] = 0;

  //DEBUG_PRINT("uri[0]:%s, uri[1]:%s\r\n", uri[0], uri[1]);

  for ( i=0, e=0 ; tasks[i][0] != 0 ; i++ )
  {
    if ( strcompare(tasks[i], uri[0]) == 0 )
    {
      e = ihttpd(tasks[i], fd, uri[1], nhttpd_writer, o);
      break;
    }
  }

  return e;
}


int32_t nhttpd_connected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnhttpd* p = (cnhttpd*)o;

  //DEBUG_PRINT(" nhttpd_connected   ->   %08X\r\n", fd);

  return __liteio_call(p->_ind, 0xE000FDC0, fd, b, sz);
}

int32_t nhttpd_disconnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnhttpd* p = (cnhttpd*)o;
  
  //DEBUG_PRINT(" nhttpd_disconnected   ->   %08X \r\n", fd);

  return __liteio_call(p->_ind, 0xE000FDCF, fd, b, sz);
}


int32_t nhttpd_read(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t idx = 0;
  cnhttpd* p = (cnhttpd*)o;
  #if 0
  DEBUG_PRINT(" nhttpd_read   ->   %08X \r\n"
              "================================================\r\n"
              "%s\r\n"
              "================================================\r\n", sz,b);
  #endif

  #if 0
  #if __LINUX__
  get_pid("ksbridge.x32", &pid);
  nshm_write(p->_ind->hdl[NSHM], b, sz);
  // nshm_read(p->_ind->hdl[NSHM], rb, 1024);
  kill(pid, SIGUSR1);
  #endif
  #endif

  return __liteio_call(p->_ind, sz, fd, b, sz);
}

int32_t nhttpd_uri(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  cnhttpd* p = (cnhttpd*)o;
  #if 0
  DEBUG_PRINT(" nhttpd_uri   ->   %08X \r\n"
              "================================================\r\n"
              "%s\r\n"
              "================================================\r\n", sz,b);
  #endif
  e = nhttpd_proc(h, fd, b, sz, extra, o);
  if ( e == 0 ) __liteio_call(p->_ind, 0xE0001010, fd, b, sz);
  return e;
}

int32_t nhttpd_get(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnhttpd* p = (cnhttpd*)o;
  #if 0
  DEBUG_PRINT(" nhttpd_get   ->   %08X \r\n"
          "================================================\r\n"
          "%s\r\n"
          "================================================\r\n", sz,b);
  #endif
  return __liteio_call(p->_ind, 0xE0001010, fd, b, sz);
}

int32_t nhttpd_post(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnhttpd* p = (cnhttpd*)o;
  #if 0
  DEBUG_PRINT(" nhttpd_post   ->   %08X \r\n"
              "================================================\r\n"
              "%s\r\n"
              "================================================\r\n", sz,b);
  #endif
  return __liteio_call(p->_ind, 0xE0001010, fd, b, sz);
}

int32_t nhttpd_uri_not_found(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  cnhttpd* p = (cnhttpd*)o;

  #if 0
  DEBUG_PRINT(" nhttpd_uri_not_found   ->   %08X \r\n"
              "================================================\r\n"
              "%s\r\n"
              "================================================\r\n", sz,b);
  #endif
  //return __liteio_call(p->_ind, 0xE0000404, fd, b, sz);
  return e;
}


int32_t nhttpd_open(cnhttpd* p)
{
  int32_t e = 0;
  int8_t _json[1024] = {0};
  int8_t _argv[4][256] = {0};

  DEBUG_PRINT("%s \r\n", _argv);

  p->_imtif.callback[IMTIF_CALLBACK_CONNECTED] = nhttpd_connected;
  p->_imtif.callback[IMTIF_CALLBACK_DISCONNECTED] = nhttpd_disconnected;
  p->_imtif.callback[IMTIF_CALLBACK_READ] = nhttpd_read;
  p->_imtif.callback[IMTIF_CALLBACK_URI] = nhttpd_uri;
  p->_imtif.callback[IMTIF_CALLBACK_URI_NOT_FOUND] = nhttpd_uri_not_found;
  p->_imtif.callback[IMTIF_CALLBACK_GET] = nhttpd_get;
  p->_imtif.callback[IMTIF_CALLBACK_POST] = nhttpd_post;

  DEBUG_PRINT("%s \r\n", _argv);

  readArgs(p->_ind->argc, p->_ind->argv, "--httpd_home", _argv[0]);
  readArgs(p->_ind->argc, p->_ind->argv, "--httpd_index", _argv[1]);
  readArgs(p->_ind->argc, p->_ind->argv, "--httpd_port", _argv[2]);

  DEBUG_PRINT("%s, %s, %s, %s\r\n", _argv[0], _argv[1], _argv[2],_argv[3]);
  //BUF_SZ,IP,PORT,CSTYPE,MAX_FD,SYNC,BLOCK,TIMEOUT,PROTOCOL,CASTTYPE,HOME,INDEX
  sprintf(_json, 
          "{"
            "\"HOME\":\"%s\","
            "\"INDEX\":\"%s\","
            "\"PORT\":\"%s\","
            "\"MAX_FD\":\"32\","
            "\"TIMEOUT\":\"4000\","
          "}",
          _argv[0],
          _argv[1],
          _argv[2]
  );
  DEBUG_PRINT("%s \r\n", _json);
  e = __httpd_open(&p->_imtif.h, _json, p->buf, 4096, p->_imtif.callback, p);
  DEBUG_PRINT("%08X \r\n", e);

  return e;
}


int32_t nhttpd_close(cnhttpd* p)
{
  return __httpd_close(&p->_imtif.h);
}


int32_t nhttpd(struct cnLiteIO* p)
{
  int32_t e = 0;
  cnhttpd* pd = (cnhttpd*)calloc(1, sizeof(cnhttpd));
  p->hdl[NHTTPD] = pd;
  pd->_ind = p;

  e = nhttpd_open(pd);
  return e;
}

int32_t nhttpd_free(struct cnLiteIO* p)
{
  nhttpd_close((cnhttpd*)p->hdl[NHTTPD]);
  free(p->hdl[NHTTPD]);
  p->hdl[NHTTPD] = 0;
  return 0;
}

void nhttpd_loop(struct cnLiteIO* p)
{
  // int32_t idx = 0;
  // cnhttpd* pd = (cnhttpd*)p->hdl;
  // idx = get_item(&pd->_itms);
  // if ( idx>=0 )
  // {
  //   // printf(" idx ---> %d \r\n", idx);
  //   // {
  //   //   int8_t hb[1024] = {0};
  //   //   int32_t s = 0;
  //   //   to_raw(pd->_itms.arg[idx].b, pd->_itms.arg[idx].sz, hb, &s);

  //   //   printf("-->%d<--\r\n--\r\n--> %s \r\n--\r\n",s, hb);
  //   // }

  //   if (p->fx) p->fx(p->obj, pd->_itms.arg[idx].fd, pd->_itms.arg[idx].b);
  // }



}
#endif
