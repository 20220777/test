#if __NHTTPSD__
#include <nhttpsd.h>
#include <nutil.h>
#include <idebug.h>

static cnhttpsd ghttpsd;


int32_t nhttpsd_closer(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnhttpsd* p = (cnhttpsd*)o;
  int32_t e = 0;

  e=__httpsd_close_fd(p->_imtif.h, fd);
  DEBUG_PRINT("close -> %d %08X\r\n", fd, fd);
  return e;
}


int32_t nhttpsd_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  DEBUG_PRINT(" ---------------------->   %08X\r\n", fd);

  DEBUG_PRINT("%4d:%4d\r\n%s\r\n", fd, sz, b);
  return write(fd, b, sz);
}

int32_t nhttpsd_writer(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  int8_t ack[1024] = {0};
  cnhttpsd* p = (cnhttpsd*)o;

  DEBUG_PRINT(" ---------------------->   %08X\r\n", fd);

  if ( (int32_t)extra == 'H' )
  {
    sprintf(ack,
          "HTTP/1.1 %d %s\r\n" 
          "Cache-Control: no-cache\r\n"
          "Content-Type: text/html\r\n\r\n", e<0?404:200, e<0?"Not Found":"OK");

    DEBUG_PRINT("%4d:%4d\r\n%s\r\n",fd, strlen(ack), ack);
    e=__httpsd_write(p->_imtif.h, fd, ack, strlen(ack), 0, o);
  }
  DEBUG_PRINT("%08X:%4d:%4d\r\n%s\r\n",p,fd, sz, b);
  e=__httpsd_write(p->_imtif.h, fd, b, sz, 0, o);

  DEBUG_PRINT("e -> %d %08X\r\n", e, e);

  return e;
}


int32_t nhttpsd_connected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnhttpsd* p = (cnhttpsd*)o;
  printf(" nhttpsd_connected   ->   %08X %d\r\n", sz, p->conn_status);

  return 0;
}

int32_t nhttpsd_disconnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnhttpsd* p = (cnhttpsd*)o;
  printf(" nhttpsd_disconnected   ->   %08X \r\n", sz);

  return 0;
}


int32_t nhttpsd_read(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnhttpsd* p = (cnhttpsd*)o;
  printf(" nhttpsd_read   ->   %08X \r\n"
          "================================================\r\n"
          "%s\r\n"
          "================================================\r\n", sz,b);

  return 0;
}

int32_t nhttpsd_get(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnhttpsd* p = (cnhttpsd*)o;
  printf(" nhttpsd_get   ->   %08X \r\n"
          "================================================\r\n"
          "%s\r\n"
          "================================================\r\n", sz,b);

  return 0;
}
int32_t nhttpsd_post(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnhttpsd* p = (cnhttpsd*)o;
  printf(" nhttpsd_post   ->   %08X \r\n"
          "================================================\r\n"
          "%s\r\n"
          "================================================\r\n", sz,b);

  return 0;
}

int32_t nhttpsd_open(cnhttpsd* p)
{
  int32_t e = 0;
  int8_t _json[1024] = {0};

  p->_imtif.callback[IMTIF_CALLBACK_CONNECTED] = nhttpsd_connected;
  p->_imtif.callback[IMTIF_CALLBACK_DISCONNECTED] = nhttpsd_disconnected;
  p->_imtif.callback[IMTIF_CALLBACK_READ] = nhttpsd_read;
  p->_imtif.callback[IMTIF_CALLBACK_GET] = nhttpsd_get;
  p->_imtif.callback[IMTIF_CALLBACK_POST] = nhttpsd_post;


  #if defined WIN32
  sprintf(_json, 
          "{"
            "\"SYSTEM_LIBRARY\":\"mtif.x86.dll\","
            "\"SYNC\":\"DISABLE\","
            "\"BLOCK\":\"DISABLE\","
            "\"HOME\":\"c:\\waas\\htdocs\","
            "\"INDEX\":\"index.html\","
            "\"TIMEOUT\":\"4000\","
            "\"CERTFILE\":\"c:\\waas\\cert\\kme.crt\","
            "\"KEYFILE\":\"c:\\waas\\cert\\kme.key\""
          "}"
  );
  #endif

  #if defined x32
  sprintf(_json, 
          "{"
            "\"SYSTEM_LIBRARY\":\"/usr/local/node/x32/mtif.x32.so\","
            "\"SYNC\":\"DISABLE\","
            "\"BLOCK\":\"DISABLE\","
            "\"HOME\":\"/usr/local/node/www\","
            "\"INDEX\":\"index.html\","
            "\"TIMEOUT\":\"4000\","
            "\"CERTFILE\":\"/usr/local/node/cert/local.crt\","
            "\"KEYFILE\":\"/usr/local/node/cert/local.key\""
          "}"
  );
  #endif
  #if defined a32
  sprintf(_json, 
          "{"
            "\"SYSTEM_LIBRARY\":\"/usr/local/node/a32/mtif.a32.so\","
            "\"SYNC\":\"DISABLE\","
            "\"BLOCK\":\"DISABLE\","
            "\"HOME\":\"/usr/local/node/www\","
            "\"INDEX\":\"index.html\","
            "\"TIMEOUT\":\"4000\","
            "\"CERTFILE\":\"/usr/local/node/cert/local.crt\","
            "\"KEYFILE\":\"/usr/local/node/cert/local.key\""
          "}"
  );
  #endif


  e = __httpsd_open(&p->_imtif.h, _json, p->_imtif.callback, p);
  if ( e < 0 ) printf("HTTPS open Fail %08X\r\n", e);
  else printf("HTTPS open Success \r\n");
  return e;
}


int32_t nhttpsd_close(cnhttpsd* p)
{
  return __httpsd_close(&p->_imtif.h);
}


int32_t nhttpsd(struct cnLiteIO* p)
{
  int32_t e = 0;
  e = nhttpsd_open(&ghttpsd);
  return e;
}


void nhttpsd_loop(struct cnLiteIO* p)
{

}
#endif
