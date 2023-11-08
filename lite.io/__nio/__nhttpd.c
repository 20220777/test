#if __NHTTPD__
#include <common.h>
#include <__nhttpd.h>
#include <__util.h>
#include <__httpd.h>




//
//void* __nhttpd_request(cnhttpd* p)
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
//  e = __httpd_write(p->io.h, 0, modbus_protocol, i, 0, p);
//  //to_raw(modbus_protocol, i, hbuf, &hsz);
//  //printf("XSOCKET  ->   %10s -> [%4d] %s\r\n", "request", hsz, hbuf);
//  return 0;
//}
//


int32_t __nhttpd_closer(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnhttpd* p = (cnhttpd*)o;
  int32_t e = 0;

  return e;
}


int32_t __nhttpd_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  cnhttpd* p = (cnhttpd*)h;

  e=__httpd_write(p->io.h, fd?fd:p->io.fd, b, sz, extra, o);

  DEBUG_PRINT("%d, %d, [%s] -> %d\r\n", fd, sz, b, e);

  //if ( fd != p->io.fd ) __httpd_close_fd(p->io.h, fd);

  //DEBUG_PRINT("\r\n");

  return e;
}

int32_t __nhttpd_status(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  int32_t idx = 0;
  int32_t _sz = 0;
  cnhttpd* p = (cnhttpd*)o;

  if ( sz != 0xE000101B && sz != 0xE000101A )
    DEBUG_PRINT("status (%5d) %08X(%5d)\r\n", fd, sz, sz);

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
      e = p->io.__f[__CALLBACK_CONNECTED]?p->io.__f[__CALLBACK_CONNECTED](h, fd, b, sz, extra, p->io.__o):__zero();
      break;

    case 0xE000FDFA:
    case 0xE000FD0F:
      /////// DisConnected
      e = p->io.__f[__CALLBACK_DISCONNECTED]?p->io.__f[__CALLBACK_DISCONNECTED](h, fd, b, sz, extra, p->io.__o):__zero();
      break;


    case 0xE000FDAB:
      idx = (extra == 0) ? 0 : (*(int32_t*)extra);
      DEBUG_PRINT("_buffer (%d)\r\n", idx);
      _sz = atoi(p->io.argv[SIZE_OF_BUFFER]);
      (p->buf+idx)->_p[0][0] = (_sz >= 0x80 )?0x80|__shift(_sz): _sz;
      *(uint8_t**)b = (p->buf+idx)->_p[0];//(p->buf+idx);
      DEBUG_PRINT("\r\n");
      break;


    case 0xE00010BB:
      idx = (extra == 0) ? 0 : (*(int32_t*)extra);
      DEBUG_PRINT("_buffer (%d)\r\n", idx);
      *(uint8_t**)b = (p->buf+idx)->_p[1];//(p->buf+idx);
      break;

    case 0xE000101F:
      idx = (extra == 0) ? 0 : (*(int32_t*)extra);
      DEBUG_PRINT("_buffer (%d) -> (%d)\r\n", idx, fd);
      break;

    case 0xE000FD1F:
      /////// DisConnected
      break;
  }

  return p->io.__f[__CALLBACK_STATUS]?p->io.__f[__CALLBACK_STATUS](h, fd, b, sz, extra, p->io.__o):__zero();
}

int32_t __nhttpd_read(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnhttpd* p = (cnhttpd*)o;

  return p->io.__f[__CALLBACK_READ]?p->io.__f[__CALLBACK_READ](h, fd, b, sz, extra, p->io.__o):__zero();
}

int32_t __nhttpd_open(cnhttpd* p)
{
  int32_t e = 0;
  int8_t _json[1024] = {0};
  int32_t (*f[__FUNCTIONS])(void*,int32_t,int8_t*,int32_t,void*,void*) = {0};

  if ( p->io.h ) return 0xE0000001;

  f[__CALLBACK_READ] = __nhttpd_read;
  f[__CALLBACK_STATUS] = __nhttpd_status;

  sprintf(_json, 
          "{"
            "\"HOME\":\"%s\","
            "\"PORT\":\"%s\","
          "}",
            p->io.argv[HTTP_HOME],
            p->io.argv[HTTP_PORT]);

  p->buf = (__buffer*)calloc(MAX_CLIENT, sizeof(__buffer));
  for ( e=0 ; e<MAX_CLIENT ; e++ )
  {
    (p->buf+e)->_p[0] = p->b[e][0];
    (p->buf+e)->_p[1] = p->b[e][1];
    (p->buf+e)->_sz = 0;//atoi(p->io.argv[SIZE_OF_BUFFER]);
  }
  p->io.fd = e = __httpd_open(&p->io.h, _json, p->io.buf, atoi(p->io.argv[SIZE_OF_BUFFER]), f, p);
  return e;
}


int32_t __nhttpd_close(cnhttpd* p)
{
  int32_t e = 0;
  if ( p->io.h==0 ) return 0xE0000001;
  e = __httpd_close(&p->io.h);

  free(p->buf);
  p->buf = 0;
  return e;
}

int32_t __nhttpd_close_fd(cnhttpd* p, int32_t fd)
{
  DEBUG_PRINT("%d\r\n", fd);

  if ( p->io.h==0 ) return 0xE0000001;

  DEBUG_PRINT("%d\r\n", fd);

  return __httpd_close_fd(p->io.h, fd);
}

#endif