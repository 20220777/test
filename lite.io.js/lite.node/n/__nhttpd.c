#if __NHTTPD__
#include <common.h>
#include <__nhttpd.h>
#include <__util.h>
#include <__httpd.h>

int32_t __nhttpd_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  cnhttpd* p = (cnhttpd*)h;
  e=__httpd_write(p->io.h, fd?fd:p->io.fd, b, sz, extra, o);
  return e;
}

int32_t __nhttpd_status(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  int32_t idx;
  cnhttpd* p = (cnhttpd*)o;

  if ( sz!=0xE000101B && sz!=0xE000101A )
    DEBUG_PRINT("status (%5d) %08X(%5d) %08X\r\n", fd, sz, sz, extra);

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

    case 0xE000FD0F:
      /////// DisConnected
      e = p->io.__f[__CALLBACK_DISCONNECTED](h, fd, b, sz, extra, p->io.__o);
      break;
  }

  return p->io.__f[__CALLBACK_STATUS]?p->io.__f[__CALLBACK_STATUS](h, fd, b, sz, extra, p->io.__o):__zero();
}

int32_t __nhttpd_close_fd(void* h, int32_t fd)
{
  cnhttpd* p = (cnhttpd*)h;
  if ( p->io.h==0 ) return 0xE0000001;

  return __httpd_close_fd(p->io.h, fd);
}

int32_t __nhttpd_read(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnhttpd* p = (cnhttpd*)o;
  if ( sz!=0xE000101B && sz!=0xE000101A )
    DEBUG_PRINT("read   (%5d) %08X(%5d) %08X : %s\r\n", fd, sz, sz, extra, b);

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

  DEBUG_PRINT("_json -> %s\r\n", _json);
  p->io.fd = e = __httpd_open(&p->io.h, _json, p->io.buf, atoi(p->io.argv[SIZE_OF_BUFFER]), f, p);
  return e;
}


int32_t __nhttpd_close(cnhttpd* p)
{
  int32_t e = 0;
  if ( p->io.h==0 ) return 0xE0000001;
  e = __httpd_close(&p->io.h);

  return e;
}


#endif