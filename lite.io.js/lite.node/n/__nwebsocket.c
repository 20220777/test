#if __NWEBSOCKET__
#include <common.h>
#include <__nwebsocket.h>
#include <__util.h>
#include <__websocket.h>
//
//void* __nwebsocket_request(cnwebsocket* p)
//{
//  int32_t e = 0;
//  uint8_t i = 0;
//  uint8_t modbus_protocol[64] = { 0};
//  uint8_t hbuf[8192] = {0};
//  uint32_t hsz = 0;
//  int16_t _addr = 0;
//  int16_t _len  = 4;
//
//
//  modbus_protocol[i++] = 0x00;
//  modbus_protocol[i++] = 0;
//  modbus_protocol[i++] = 0x00;
//  modbus_protocol[i++] = 0x00;
//  modbus_protocol[i++] = 0x00;
//  modbus_protocol[i++] = 0x06;
//
//  modbus_protocol[i++] = 0x01;
//
//  modbus_protocol[i++] = 0x04;
//  modbus_protocol[i++] = (_addr&0xFF00)>>8;
//  modbus_protocol[i++] = (_addr&0x00FF);
//  modbus_protocol[i++] = (_len &0xFF00)>>8;
//  modbus_protocol[i++] = (_len &0x00FF);
//
//  e = __websocket_write(p->io.h, 0, modbus_protocol, i, 0, p);
//  //to_raw(modbus_protocol, i, hbuf, &hsz);
//  //printf("XSOCKET  ->   %10s -> [%4d] %s\r\n", "request", hsz, hbuf);
//  return 0;
//}
//


int32_t __nwebsocket_closer(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnwebsocket* p = (cnwebsocket*)o;
  int32_t e = 0;

  return e;
}


int32_t __nwebsocket_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  cnwebsocket* p = (cnwebsocket*)h;

  e=__websocket_write(p->io.h, fd?fd:p->io.fd, b, sz, 0x02, o);

  return e;
}

int32_t __nwebsocket_status(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  int32_t idx;
  cnwebsocket* p = (cnwebsocket*)o;

  //DEBUG_PRINT("status (%5d) %08X(%5d)\r\n", fd, sz, sz);

  switch(sz)
  {
    case 0xE000BF0B:
      //idx = (extra == 0) ? 0 : (*(int32_t*)extra);
      //*((int8_t**)b) = p->field[idx];
      break;
    case 0xE000FD0B:
      break;

    case 0xE000FD0A:
      /////// Connected
      e = p->io.__f[__CALLBACK_CONNECTED](h, fd, b, sz, extra, p->io.__o);
      break;

    case 0xE000FDFA:
    case 0xE000FD0F:
      /////// DisConnected
      e = p->io.__f[__CALLBACK_DISCONNECTED](h, fd, b, sz, extra, p->io.__o);
      break;
  }

  return e;
  //return p->io.__f[__CALLBACK_STATUS]?p->io.__f[__CALLBACK_STATUS](h, fd, b, sz, extra, o):__zero();
}

int32_t __nwebsocket_read(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnwebsocket* p = (cnwebsocket*)o;

  return p->io.__f[__CALLBACK_READ]?p->io.__f[__CALLBACK_READ](h, fd, b, sz, extra, p->io.__o):__zero();
}

int32_t __nwebsocket_open(cnwebsocket* p)
{
  int32_t e = 0;
  int8_t _json[1024] = {0};
  int32_t (*f[__FUNCTIONS])(void*,int32_t,int8_t*,int32_t,void*,void*) = {0};

  if ( p->io.h ) return 0xE0000001;

  f[__CALLBACK_READ] = __nwebsocket_read;
  f[__CALLBACK_STATUS] = __nwebsocket_status;

  sprintf(_json, 
          "{"
            "\"URL\":\"%s\","
            "\"CSTYPE\":\"%s\","
            "\"TIMEOUT\":\"0\","
          "}",
            p->io.argv[HTTP_URL],
            p->io.argv[SOCKET_CSTYPE]);
  p->io.fd = e = __websocket_open(&p->io.h, _json, p->io.buf, 4096, f, p);
  return e;
}


int32_t __nwebsocket_close(cnwebsocket* p)
{
  int32_t e = 0;
  if ( p->io.h==0 ) return 0xE0000001;
  e = __websocket_close(&p->io.h);

  return e;
}


#endif