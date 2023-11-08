#if __NWSC__
#include <nwsc.h>
#include <nutil.h>
#include <idebug.h>


int32_t nwsc_closer(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnwsc* p = (cnwsc*)o;
  int32_t e = 0;

  e = __ws_close_fd(p->_imtif.h, fd);
  DEBUG_PRINT("e -> %d %08X\r\n", e, e);

  return e;
}


int32_t nwsc_writer(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  cnwsc* p = (cnwsc*)o;

  DEBUG_PRINT("%08X:%4d:%4d\r\n%s\r\n",p,fd, sz, b);
  e=__ws_write(p->_imtif.h, fd, b, sz, 0, o);
  DEBUG_PRINT("e -> %d %08X\r\n", e, e);

  return e;
}


int32_t nwsc_write(uint8_t* b, int32_t sz)
{
  int32_t e = 0;

  //e = __ws_write(gwsc._imtif.h, 0, b, sz, 0, &gwsc);

  return e;
}

int32_t nwsc_connected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnwsc* p = (cnwsc*)o;
  printf(" nwsd_connected   ->   %08X %08X %d\r\n", fd, sz, p->conn_status);

  p->conn_status = 1;
  return __liteio_call(p->_ind, 0xE000FDC0, fd, b, sz);
}

int32_t nwsc_disconnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnwsc* p = (cnwsc*)o;
  printf(" nwsd_disconnected   ->   %08X %08X \r\n", fd, sz);

  p->conn_status = -1;
  return __liteio_call(p->_ind, 0xE000FDCF, fd, b, sz);
}


int32_t nwsc_read(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnwsc* p = (cnwsc*)o;
  printf(" nwsd_read   ->   %08X %08X %s\r\n", fd, sz, b);

  return __liteio_call(p->_ind, sz, fd, b, sz);
}

int32_t nwsc_open(cnwsc* p)
{
  int32_t e = 0;
  int8_t _json[1024] = {0};
  int8_t _argv[1024] = {0};

  p->_imtif.callback[IMTIF_CALLBACK_CONNECTED] = nwsc_connected;
  p->_imtif.callback[IMTIF_CALLBACK_DISCONNECTED] = nwsc_disconnected;
  p->_imtif.callback[IMTIF_CALLBACK_READ] = nwsc_read;

  readArgs(p->_ind->argc, p->_ind->argv, "--X", _argv);

  sprintf(_json,
          "{"
            "\"SYSTEM_LIBRARY\":\"%s\","
            "\"IP\":\"127.0.0.1\","
            "\"PORT\":\"7811\","
            "\"CSTYPE\":\"CLIENT\","
            "\"TIMEOUT\":\"4000\","
          "}",
          _argv
          );
  e = __ws_open(&p->_imtif.h, _json, p->_imtif.callback, p);
  printf("__ws_open %08X %s\r\n", e, e>0?"READY":"FAIL");
  return e;
}


int32_t nwsc_close(cnwsc* p)
{
  return __ws_close(&p->_imtif.h);
}


int32_t nwsc(struct cnLiteIO* p)
{
  int32_t e = 0;
  cnwsc* pd = (cnwsc*)calloc(1, sizeof(cnwsc));
  p->hdl[NWSC] = pd;
  pd->_ind = p;
  e = nwsc_open(pd);
  return e;
}


int32_t nwsc_free(struct cnLiteIO* p)
{
  int32_t e = 0;
  nwsc_close((cnwsc*)p->hdl[NWSC]);
  free(p->hdl[NWSC]);
  p->hdl[NWSC] = 0;
  return e;
}


void nwsc_loop(struct cnLiteIO* p)
{
  //int32_t e = 0;
  //delay(2000);
  //e = __ws_write(gwsc._imtif.h, 0, "Hello", 5, 0, &gwsc);
  //printf("__ws_write : %08X \r\n", e);
}
#endif