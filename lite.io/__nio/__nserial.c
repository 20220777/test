#if __NSERIAL__
#include <__nserial.h>
//#include <nutil.h>


int32_t __nserial_closer(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnserial* p = (cnserial*)o;
  int32_t e = 0;

  //e=__http_close_socket(p->_imtif.h, fd);
  //DEBUG_PRINT("close -> %d %08X\r\n", fd, fd);
  return e;
}


int32_t __nserial_write(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnserial* p = (cnserial*)h;

  return __serial_write(p->io.h, fd, b, sz, 0, o);
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


int32_t __nserial_read(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnserial* p = (cnserial*)o;

  return p->io.__f[__CALLBACK_READ]?p->io.__f[__CALLBACK_READ](h, fd, b, sz, extra, p->io.__o):__zero();
}

int32_t __nserial_open(cnserial* p)
{
  int32_t e = 0;
  int8_t _json[1024] = {0};
  int8_t _argv[16][256] = {0};
  int32_t (*f[__FUNCTIONS])(void*,int32_t,int8_t*,int32_t,void*,void*) = {0};

  if ( p->io.h ) return 0xE0000001;

  f[__CALLBACK_READ] = __nserial_read;

  sprintf(_json, 
          "{"
            "\"PORT\":\"%s\","
            "\"BAUDRATE\":\"%s\","
            "\"DATABIT\":\"%s\","
            "\"STOPBIT\":\"%s\","
            "\"PARITYBIT\":\"%s\","
            "\"BUF_SZ\":\"%s\","
            "\"SYNC\":\"DISABLE\""
          "}",
          p->io.argv[SERIAL_PORT],
          p->io.argv[SERIAL_BAUDRATE],
          p->io.argv[SERIAL_DATABIT],
          p->io.argv[SERIAL_STOPBIT],
          p->io.argv[SERIAL_PARITYBIT],
          p->io.argv[SIZE_OF_BUFFER]
  );

  e = __serial_open(&p->io.h, _json, p->io.buf, atoi(p->io.argv[SIZE_OF_BUFFER]), f, p);

  return e;
}


int32_t __nserial_close(cnserial* p)
{
  if ( p->io.h==0 ) return 0xE0000001;
  return __serial_close(&p->io.h);
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
