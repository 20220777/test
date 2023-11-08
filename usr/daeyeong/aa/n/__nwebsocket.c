#if __NWEBSOCKET__
#include <common.h>
#include <__nwebsocket.h>
#include <__util.h>
#include <imtif.h>


int32_t nwebsocket_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  cnwebsocket* p = (cnwebsocket*)o;

  e=__ws_write(p->io.h, fd, b, sz, extra, o);

  return e;
}

int32_t nwebsocket_connected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnwebsocket* p = (cnwebsocket*)o;

  return p->io.__f[IMTIF_CALLBACK_CONNECTED]?p->io.__f[IMTIF_CALLBACK_CONNECTED](h, fd, b, sz, extra, o):__zero();
}

int32_t nwebsocket_disconnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnwebsocket* p = (cnwebsocket*)o;

  return p->io.__f[IMTIF_CALLBACK_DISCONNECTED]?p->io.__f[IMTIF_CALLBACK_DISCONNECTED](h, fd, b, sz, extra, o):__zero();
}


int32_t nwebsocket_read(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnwebsocket* p = (cnwebsocket*)o;

  return p->io.__f[IMTIF_CALLBACK_READ]?p->io.__f[IMTIF_CALLBACK_READ](h, fd, b, sz, extra, o):__zero();
}

int32_t nwebsocket_open(cnwebsocket* p)
{
  int32_t e = 0;
  int8_t _json[1024] = {0};

  p->io.__f[IMTIF_CALLBACK_OPEN] = nwebsocket_connected;
  p->io.__f[IMTIF_CALLBACK_CLOSE] = nwebsocket_disconnected;
  p->io.__f[IMTIF_CALLBACK_CONNECTED] = nwebsocket_connected;
  p->io.__f[IMTIF_CALLBACK_DISCONNECTED] = nwebsocket_disconnected;
  p->io.__f[IMTIF_CALLBACK_READ] = nwebsocket_read;

  sprintf(_json, 
          "{"
            "\"IP\":\"127.0.0.1\","
            "\"PORT\":\"8090\","
            "\"CSTYPE\":\"SERVER\","
            "\"MAX_FD\":\"32\","
          "}");


  e = __ws_open(&p->io.h, _json, p->io.buf, 4096, p->io.__f, p);
  return e;
}


int32_t nwebsocket_close(cnwebsocket* p)
{
  return __ws_close(&p->io.h);
}


#endif