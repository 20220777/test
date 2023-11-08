#if __NSOCKET__
#include <common.h>
#include <__nsocket.h>
#include <__util.h>

void* nsocket_request(cnsocket* p)
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



int32_t nsocket_closer(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnsocket* p = (cnsocket*)o;
  int32_t e = 0;

  return e;
}


int32_t nsocket_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  cnsocket* p = (cnsocket*)o;

  e=__socket_write(p->_imtif.h, fd, b, sz, 0, o);

  return e;
}

int32_t nsocket_connected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnsocket* p = (cnsocket*)o;

  return p->io.__f[IMTIF_CALLBACK_CONNECTED]?p->io.__f[IMTIF_CALLBACK_CONNECTED](h, fd, b, sz, extra, o):__zero();
}

int32_t nsocket_disconnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnsocket* p = (cnsocket*)o;

  return p->io.__f[IMTIF_CALLBACK_DISCONNECTED]?p->io.__f[IMTIF_CALLBACK_DISCONNECTED](h, fd, b, sz, extra, o):__zero();
}


int32_t nsocket_read(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnsocket* p = (cnsocket*)o;

  return p->io.__f[IMTIF_CALLBACK_READ]?p->io.__f[IMTIF_CALLBACK_READ](h, fd, b, sz, extra, o):__zero();
}

int32_t nsocket_open(cnsocket* p)
{
  int32_t e = 0;
  int8_t _json[1024] = {0};

  p->_imtif.callback[IMTIF_CALLBACK_OPEN] = nsocket_connected;
  p->_imtif.callback[IMTIF_CALLBACK_CLOSE] = nsocket_disconnected;
  p->_imtif.callback[IMTIF_CALLBACK_CONNECTED] = nsocket_connected;
  p->_imtif.callback[IMTIF_CALLBACK_DISCONNECTED] = nsocket_disconnected;
  p->_imtif.callback[IMTIF_CALLBACK_READ] = nsocket_read;

  sprintf(_json, 
          "{"
            "\"IP\":\"%s\","
            "\"PORT\":\"%s\","
            "\"CSTYPE\":\"%s\","
            "\"PROTOCOL\":\"%s\","
            "\"CASTTYPE\":\"%s\","
            "\"SYNC\":\"DISABLE\","
            "\"TIMEOUT\":\"%s\","
          "}",
            p->io.argv[0],
            p->io.argv[1],
            p->io.argv[3],
            p->io.argv[2],
            p->io.argv[4], p->io.argv[3][0]=='C'?"4000000":"0");


  e = __socket_open(&p->_imtif.h, _json, p->io.buf, 4096, p->_imtif.callback, p);
  return e;
}


int32_t nsocket_close(cnsocket* p)
{
  return __socket_close(&p->_imtif.h);
}


#endif