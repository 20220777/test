#include <ntcp.h>


static cntcp gtcp;

int32_t ntcp_connected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cntcp* p = (cntcp*)o;
  printf(" ntcp_connected   ->   %08X %d\r\n", sz, p->conn_status);

  return 0;
}

int32_t ntcp_disconnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cntcp* p = (cntcp*)o;
  printf(" ntcp_disconnected   ->   %08X \r\n", sz);

  return 0;
}


int32_t ntcp_read(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cntcp* p = (cntcp*)o;
  int32_t e = 0;
  uint8_t hb[1024] = {0};
  int32_t hbsz = 0;

  //to_raw(b, sz, hb, &hbsz);

  //printf(" ntcp_read   ->   %08X \r\n"
  //        "================================================\r\n"
  //        "%s\r\n"
  //        "================================================\r\n", sz,hb);

  //e = liteio_write(h, fd, b, sz, extra, &gtcp);

  return 0;
}


int32_t ntcp_open(cntcp* p)
{
  int32_t e = 0;
  int8_t _json[1024] = {0};
  int8_t _argv[1024] = {0};


  p->_imtif.callback[IMTIF_CALLBACK_CONNECTED] = ntcp_connected;
  p->_imtif.callback[IMTIF_CALLBACK_DISCONNECTED] = ntcp_disconnected;
  p->_imtif.callback[IMTIF_CALLBACK_READ] = ntcp_read;

  //readArgs(p->_ind->argc, p->_ind->argv, "--X", _argv);

  sprintf(_json, 
          "{"
            //"\"SYSTEM_LIBRARY\":\"%s\","
            "\"IP\":\"192.168.0.254\","
            "\"PORT\":\"502\","
            "\"CSTYPE\":\"CLIENT\","
            "\"PROTOCOL\":\"TCP\","
            "\"CASTTYPE\":\"UNICAST\","
            "\"SYNC\":\"DISABLE\","
            "\"TIMEOUT\":\"2000\","
          "}",
          _argv
  );
  e = __socket_open(&p->_imtif.h, _json, p->_imtif.callback, p);
  printf("__socket_open %08X %s\r\n", e, e>0?"READY":"FAIL");
  return e;
}
