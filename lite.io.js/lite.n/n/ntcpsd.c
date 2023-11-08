#if __NTCPSD__
#include <ntcpsd.h>
#include <nutil.h>
#include <idebug.h>

static cntcpsd gtcpsd;



int32_t ntcpsd_closer(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cntcpsd* p = (cntcpsd*)o;
  int32_t e = 0;

  e = __socket_close_fd(p->_imtif.h, fd);
  DEBUG_PRINT("e -> %d %08X\r\n", e, e);

  return e;
}


int32_t ntcpsd_writer(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  cntcpsd* p = (cntcpsd*)o;

  DEBUG_PRINT("%08X:%4d:%4d\r\n%s\r\n",p,fd, sz, b);
  e=__socket_write(p->_imtif.h, fd, b, sz, 0, o);
  DEBUG_PRINT("e -> %d %08X\r\n", e, e);

  return e;
}


int32_t ntcpsd_connected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cntcpsd* p = (cntcpsd*)o;
  printf(" ntcpsd_connected   ->   %08X %d\r\n", sz, p->conn_status);

  return 0;
}

int32_t ntcpsd_disconnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cntcpsd* p = (cntcpsd*)o;
  printf(" ntcpsd_disconnected   ->   %08X \r\n", sz);

  return 0;
}


int32_t ntcpsd_read(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cntcpsd* p = (cntcpsd*)o;
  printf(" ntcpsd_read   ->   %08X \r\n"
          "================================================\r\n"
          "%s\r\n"
          "================================================\r\n", sz,b);

  return 0;
}

int32_t ntcpsd_get(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cntcpsd* p = (cntcpsd*)o;
  printf(" ntcpsd_get   ->   %08X \r\n"
          "================================================\r\n"
          "%s\r\n"
          "================================================\r\n", sz,b);

  return 0;
}
int32_t ntcpsd_post(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cntcpsd* p = (cntcpsd*)o;
  printf(" ntcpsd_post   ->   %08X \r\n"
          "================================================\r\n"
          "%s\r\n"
          "================================================\r\n", sz,b);

  return 0;
}

int32_t ntcpsd_open(cntcpsd* p)
{
  int32_t e = 0;
  int8_t _json[1024] = {0};

  p->_imtif.callback[IMTIF_CALLBACK_CONNECTED] = ntcpsd_connected;
  p->_imtif.callback[IMTIF_CALLBACK_DISCONNECTED] = ntcpsd_disconnected;
  p->_imtif.callback[IMTIF_CALLBACK_READ] = ntcpsd_read;


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
            "\"SYSTEM_LIBRARY\":\"/usr/local/node/ha32/mtif.ha32.so\","
            "\"IP\":\"192.168.0.11\","
            "\"PORT\":\"20014\","
            "\"CSTYPE\":\"SERVER\","
            "\"PROTOCOL\":\"TCP\","
            "\"CASTTYPE\":\"UNICAST\","
            "\"SYNC\":\"DISABLE\","
            "\"TIMEOUT\":\"2000\","
            "\"BLOCK\":\"DISABLE\","
            "\"CERTFILE\":\"/usr/local/node/cert/local.crt\","
            "\"KEYFILE\":\"/usr/local/node/cert/local.key\""
          "}"
  );
  #endif


  e = __socket_open(&p->_imtif.h, _json, p->_imtif.callback, p);
  return e;
}


int32_t ntcpsd_close(cntcpsd* p)
{
  return __socket_close(&p->_imtif.h);
}


int32_t ntcpsd(struct cnLiteIO* p)
{
  int32_t e = 0;
  e = ntcpsd_open(&gtcpsd);
  return e;
}


void ntcpsd_loop(struct cnLiteIO* p)
{

}
#endif