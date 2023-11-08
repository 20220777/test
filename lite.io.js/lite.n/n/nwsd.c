#if __NWSD__
#include <nwsd.h>
#include <nutil.h>
#include <idebug.h>

int32_t nwsd_closer(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnwsd* p = (cnwsd*)o;
  int32_t e = 0;

  e = __ws_close_fd(p->_imtif.h, fd);
  DEBUG_PRINT("e -> %d %08X\r\n", e, e);

  return e;
}

int32_t nwsd_writer(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  cnwsd* p = (cnwsd*)o;

  DEBUG_PRINT("%08X:%4d:%4d\r\n%s\r\n",p,fd, sz, b);
  e=__ws_write(p->_imtif.h, fd, b, sz, 0, o);
  DEBUG_PRINT("e -> %d %08X\r\n", e, e);

  return e;
}

int32_t nwsd_connected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnwsd* p = (cnwsd*)o;
  printf(" nwsd_connected   ->   %08X %08X %d\r\n", fd, sz, p->conn_status);

  p->conn_status = 1;
  return __liteio_call(p->_ind, 0xE000FDC0, fd, b, sz);
}

int32_t nwsd_disconnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnwsd* p = (cnwsd*)o;
  printf(" nwsd_disconnected   ->   %08X %08X \r\n", fd, sz);

  p->conn_status = -1;
  return __liteio_call(p->_ind, 0xE000FDCF, fd, b, sz);
}


int32_t nwsd_read(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnwsd* p = (cnwsd*)o;
  printf(" nwsd_read   ->   %08X %08X %s\r\n", fd, sz, b);

  return __liteio_call(p->_ind, sz, fd, b, sz);
}

int32_t nwsd_open(cnwsd* p)
{
  int32_t e = 0;
  int8_t _json[1024] = {0};
  int8_t _argv[4][1024] = {0};

  p->_imtif.callback[IMTIF_CALLBACK_CONNECTED] = nwsd_connected;
  p->_imtif.callback[IMTIF_CALLBACK_DISCONNECTED] = nwsd_disconnected;
  p->_imtif.callback[IMTIF_CALLBACK_READ] = nwsd_read;

  readArgs(p->_ind->argc, p->_ind->argv, "--wsd_port", _argv[0]);

  sprintf(_json,
          "{"
            "\"IP\":\"127.0.0.1\","
            "\"PORT\":\"%s\","
            "\"CSTYPE\":\"SERVER\","
            "\"MAX_FD\":\"32\","
          "}",
          _argv[0]
          );

  DEBUG_PRINT("%s\r\n", _json);

  e = __ws_open(&p->_imtif.h, _json, p->buf, 4096, p->_imtif.callback, p);

  return e;
}

int32_t nwsd_close(cnwsd* p)
{
  return __ws_close(&p->_imtif.h);
}

int32_t nwsd(struct cnLiteIO* p)
{
  int32_t e = 0;
  cnwsd* pd = (cnwsd*)calloc(1, sizeof(cnwsd));
  p->hdl[NWSD] = pd;
  pd->_ind = p;

  DEBUG_PRINT("\r\n");
  e =nwsd_open(pd);
  return e;
}

int32_t nwsd_free(struct cnLiteIO* p)
{
  nwsd_close((cnwsd*)p->hdl[NWSD]);
  free(p->hdl[NWSD]);
  p->hdl[NWSD] = 0;
  return 0;
}

void nwsd_loop(struct cnLiteIO* p)
{

}
#endif