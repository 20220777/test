#if __NSERIAL__
#include <__nserial.h>
//#include <nutil.h>


int32_t nserial_closer(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnserial* p = (cnserial*)o;
  int32_t e = 0;

  //e=__http_close_socket(p->_imtif.h, fd);
  //DEBUG_PRINT("close -> %d %08X\r\n", fd, fd);
  return e;
}


int32_t nserial_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnserial* p = (cnserial*)o;

  return __serial_write(p->_imtif.h, fd, b, sz, 0, o);
}

//int32_t nserial_writer(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
//{
//  int32_t e = 0;
//  int8_t ack[1024] = {0};
//  cnserial* p = (cnserial*)o;
//
//  e=__serial_write(p->_imtif.h, fd, b, sz, 0, o);
//
//  return e;
//}
int32_t nserial_opened(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnserial* p = (cnserial*)o;

  return p->io.__f[IMTIF_CALLBACK_OPEN]?p->io.__f[IMTIF_CALLBACK_OPEN](h, fd, b, sz, extra, o):__zero();
}

int32_t nserial_closed(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnserial* p = (cnserial*)o;

  return p->io.__f[IMTIF_CALLBACK_CLOSE]?p->io.__f[IMTIF_CALLBACK_CLOSE](h, fd, b, sz, extra, o):__zero();
}


int32_t nserial_connected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnserial* p = (cnserial*)o;
  return p->io.__f[IMTIF_CALLBACK_CONNECTED]?p->io.__f[IMTIF_CALLBACK_CONNECTED](h, fd, b, sz, extra, o):__zero();
}

int32_t nserial_disconnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnserial* p = (cnserial*)o;

  return p->io.__f[IMTIF_CALLBACK_DISCONNECTED]?p->io.__f[IMTIF_CALLBACK_DISCONNECTED](h, fd, b, sz, extra, o):__zero();
}


int32_t nserial_read(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnserial* p = (cnserial*)o;

  return p->io.__f[IMTIF_CALLBACK_READ]?p->io.__f[IMTIF_CALLBACK_READ](h, fd, b, sz, extra, o):__zero();
}

int32_t nserial_open(cnserial* p)
{
  int32_t e = 0;
  int32_t sz = 1;
  int8_t _json[1024] = {0};
  int8_t _argv[16][256] = {0};

  if ( p->_imtif.h ) return 0xE0000001;

  p->_imtif.callback[IMTIF_CALLBACK_OPEN] = nserial_opened;
  p->_imtif.callback[IMTIF_CALLBACK_CLOSE] = nserial_closed;

  //p->_imtif.callback[IMTIF_CALLBACK_CONNECTED] = nserial_connected;
  //p->_imtif.callback[IMTIF_CALLBACK_DISCONNECTED] = nserial_disconnected;
  p->_imtif.callback[IMTIF_CALLBACK_READ] = nserial_read;

  sprintf(_json, 
          "{"
            "\"PORT\":\"%s\","
            "\"BAUDRATE\":\"%s\","
            "\"DATABIT\":\"%s\","
            "\"STOPBIT\":\"%s\","
            "\"PARITYBIT\":\"%s\","
            "\"BUF_SZ\":\"1\","
            "\"SYNC\":\"DISABLE\""
          "}",
          p->io.argv[0],
          p->io.argv[1],
          p->io.argv[2],
          p->io.argv[3],
          p->io.argv[4]
  );

  e = __serial_open(&p->_imtif.h, _json, p->io.buf, sz, p->_imtif.callback, p);

  return e;
}


int32_t nserial_close(cnserial* p)
{
  if ( p->_imtif.h==0 ) return 0xE0000001;
  return __serial_close(&p->_imtif.h);
}


//int32_t nserial(struct cnLiteIO* p)
//{
//  int32_t e = 0;
//  cnserial* pd = (cnserial*)calloc(1, sizeof(cnserial));
//  //p->hdl[NSERIAL] = pd;
//  //pd->_ind = p;
//
//
//  e = nserial_open(pd);
//  return e;
//}

#endif
