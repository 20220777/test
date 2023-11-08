#if __NHTTP__
#include <nhttp.h>
#include <nutil.h>
#include <nm.h>
#include <idebug.h>

#define STOCK_URL              "api.data.go.kr"
#define STOCK_PORT             "80"
#define STOCK_URI              "/openapi/tn_pubr_public_wrpp_qltwtr_inspct_api"



static cnhttp ghttp;


int32_t nhttp_closer(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnhttp* p = (cnhttp*)o;
  int32_t e = 0;

  //e=__http_close_socket(p->_imtif.h, fd);
  //DEBUG_PRINT("close -> %d %08X\r\n", fd, fd);
  return e;
}


int32_t nhttp_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  DEBUG_PRINT(" ---------------------->   %08X\r\n", fd);

  DEBUG_PRINT("%4d:%4d\r\n%s\r\n", fd, sz, b);
  return write(fd, b, sz);
}

int32_t nhttp_writer(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  int8_t ack[1024] = {0};
  cnhttp* p = (cnhttp*)o;

  DEBUG_PRINT(" ---------------------->   %08X\r\n", fd);

  DEBUG_PRINT("%08X:%4d:%4d\r\n%s\r\n",p,fd, sz, b);
  e=__http_write(p->_imtif.h, fd, b, sz, 0, o);
  DEBUG_PRINT("e -> %d %08X\r\n", e, e);

  return e;
}


int32_t nhttp_connected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnhttp* p = (cnhttp*)o;
  printf(" nhttp_connected   ->   %08X %d\r\n", sz, p->conn_status);

  p->conn_status = 1;
  return 0;
}

int32_t nhttp_disconnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnhttp* p = (cnhttp*)o;
  printf(" nhttp_disconnected   ->   %08X \r\n", sz);

  p->conn_status = -1;
  return 0;
}


int32_t nhttp_read(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnhttp* p = (cnhttp*)o;
  printf(" nhttp_read   ->   %08X \r\n%s\r\n", sz, b);

  return 0;
}

int32_t nhttp_open(cnhttp* p)
{
  int32_t e = 0;
  int8_t _json[1024] = {0};
  int32_t fd = 0;
  int8_t _argv[1024] = {0};

  p->_imtif.callback[IMTIF_CALLBACK_CONNECTED] = nhttp_connected;
  p->_imtif.callback[IMTIF_CALLBACK_DISCONNECTED] = nhttp_disconnected;
  p->_imtif.callback[IMTIF_CALLBACK_READ] = nhttp_read;

  readArgs(p->_ind->argc, p->_ind->argv, "--X", _argv);

  sprintf(_json, 
          "{"
            "\"SYSTEM_LIBRARY\":\"%s\","
            "\"SYNC\":\"ENABLE\","
            "\"TIMEOUT\":\"4000\","
            "\"URL\":\"%s\","
            "\"URI\":\"%s\","
            "\"PORT\":\"%s\","
          "}",
          _argv, STOCK_URL, STOCK_URI, STOCK_PORT
  );

  e = __http_open(&p->_imtif.h, _json, p->_imtif.callback, p);


  __http_fd(p->_imtif.h, 0, 0, 0, &fd, 0);


  return e;
}


int32_t nhttp_close(cnhttp* p)
{
  return __http_close(&p->_imtif.h);
}


int32_t nhttp(struct cnLiteIO* p)
{
  int32_t e= 0;
  ghttp._ind = p;
  e = nhttp_open(&ghttp);
  return e;
}


void nhttp_loop(struct cnLiteIO* p)
{
  int32_t e = 0;
  uint8_t b[2048] = {0};
  uint8_t hex = 0;

  return ;
  {
    e = __http_read(ghttp._imtif.h, 0, b, 2048, 0, &ghttp);
    if ( e > 0 ) printf("%s\r\n", b);
    delay(1000);


    //if ( ghttp.conn_status == 1 )
    //{
    //  int32_t i = 0;
    //  delay(500);
    //  for ( i=0 ; i<16 ;i++ )
    //  {
    //    b[i] = hex%26 + 'A';
    //  }
    //  e = __http_write(ghttp._imtif.h, 0, b, 16, 0, &ghttp);

    //  printf(" write (%d)-> %02X \r\n", e, b[0]);
    //  ghttp.conn_status = -1;

    //  hex++;
    //}
  }


}
#endif