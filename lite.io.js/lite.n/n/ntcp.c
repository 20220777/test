#if __NTCP__
#include <ntcp.h>
#include <nutil.h>
#include <idebug.h>

void* ntcp_request(cntcp* p)
{
  int32_t e = 0;
  uint8_t i = 0;
  uint8_t modbus_protocol[64] = { 0};
  uint8_t hbuf[8192] = {0};
  uint32_t hsz = 0;
  int16_t _addr = 0;
  int16_t _len  = 4;


  modbus_protocol[i++] = 0x00;
  modbus_protocol[i++] = 0;
  modbus_protocol[i++] = 0x00;
  modbus_protocol[i++] = 0x00;
  modbus_protocol[i++] = 0x00;
  modbus_protocol[i++] = 0x06;

  modbus_protocol[i++] = 0x01;

  modbus_protocol[i++] = 0x04;
  modbus_protocol[i++] = (_addr&0xFF00)>>8;
  modbus_protocol[i++] = (_addr&0x00FF);
  modbus_protocol[i++] = (_len &0xFF00)>>8;
  modbus_protocol[i++] = (_len &0x00FF);

  e = __socket_write(p->_imtif.h, 0, modbus_protocol, i, 0, p);
  to_raw(modbus_protocol, i, hbuf, &hsz);
  printf("XSOCKET  ->   %10s -> [%4d] %s\r\n", "request", hsz, hbuf);
  return 0;
}



int32_t ntcp_closer(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cntcp* p = (cntcp*)o;
  int32_t e = 0;

  return e;
}


int32_t ntcp_writer(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  cntcp* p = (cntcp*)o;

  DEBUG_PRINT("%08X:%4d:%4d\r\n%s\r\n",p,fd, sz, b);
  e=__socket_write(p->_imtif.h, fd, b, sz, 0, o);
  DEBUG_PRINT("e -> %d %08X\r\n", e, e);

  return e;
}



int32_t ntcp_connected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cntcp* p = (cntcp*)o;
  DEBUG_PRINT(" ntcp_connected   ->   %08X %d\r\n", sz, p->conn_status);

  return __liteio_call(p->_ind, sz, fd, b, sz);
}

int32_t ntcp_disconnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cntcp* p = (cntcp*)o;
  DEBUG_PRINT(" ntcp_disconnected   ->   %08X \r\n", sz);

  return __liteio_call(p->_ind, sz, fd, b, sz);
}


int32_t ntcp_read(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cntcp* p = (cntcp*)o;
  int32_t e = 0;
  uint8_t hb[1024] = {0};
  int32_t hbsz = 0;

  to_raw(b, sz, hb, &hbsz);

  DEBUG_PRINT(" ntcp_read   ->   %08X \r\n"
          "================================================\r\n"
          "%s\r\n"
          "================================================\r\n", sz,hb);

  return __liteio_call(p->_ind, sz, fd, b, sz);
}

int32_t ntcp_open(cntcp* p)
{
  int32_t e = 0;
  int8_t _json[1024] = {0};
  int8_t _argv[4][256] = {0};

  DEBUG_PRINT("\r\n");

  p->_imtif.callback[IMTIF_CALLBACK_CONNECTED] = ntcp_connected;
  p->_imtif.callback[IMTIF_CALLBACK_DISCONNECTED] = ntcp_disconnected;
  p->_imtif.callback[IMTIF_CALLBACK_READ] = ntcp_read;

  DEBUG_PRINT("\r\n");

  readArgs(p->_ind->argc, p->_ind->argv, "--tcp_ip", _argv[0]);
  readArgs(p->_ind->argc, p->_ind->argv, "--tcp_port", _argv[1]);
  DEBUG_PRINT("\r\n");

  sprintf(_json, 
          "{"
            "\"IP\":\"%s\","
            "\"PORT\":\"%s\","
            "\"CSTYPE\":\"CLIENT\","
            "\"PROTOCOL\":\"TCP\","
            "\"CASTTYPE\":\"UNICAST\","
            "\"SYNC\":\"DISABLE\","
            "\"TIMEOUT\":\"2000\","
          "}",
          _argv[0],
          _argv[1]
  );


  DEBUG_PRINT("%s", _json);
  e = __socket_open(&p->_imtif.h, _json, p->buf, 4096, p->_imtif.callback, p);
  DEBUG_PRINT("\r\n");
  return e;
}


int32_t ntcp_close(cntcp* p)
{
  return __socket_close(&p->_imtif.h);
}


int32_t ntcp(struct cnLiteIO* p)
{
  int32_t e = 0;
  cntcp* pd = (cntcp*)calloc(1, sizeof(cntcp));
  p->hdl[NTCP] = pd;
  pd->_ind = p;

  DEBUG_PRINT("\r\n");

  e = ntcp_open(pd);
  return e;
}


void ntcp_loop(struct cnLiteIO* p)
{
  //delay(1000);
  //ntcp_request(&gtcp);
}
#endif