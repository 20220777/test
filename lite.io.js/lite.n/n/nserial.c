#if __NSERIAL__
#include <nserial.h>
#include <nutil.h>
#include <idebug.h>


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

  DEBUG_PRINT("%4d,%d,%s\r\n", fd, sz, b);
  return write(fd, b, sz);
}

int32_t nserial_writer(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  int8_t ack[1024] = {0};
  cnserial* p = (cnserial*)o;

  DEBUG_PRINT(" ---------------------->   %08X\r\n", fd);

  DEBUG_PRINT("%08X:%4d:%4d,%s\r\n",p,fd, sz, b);
  e=__serial_write(p->_imtif.h, fd, b, sz, 0, o);
  DEBUG_PRINT("e -> %d %08X\r\n", e, e);

  return e;
}

int32_t nserial_connected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnserial* p = (cnserial*)o;
  DEBUG_PRINT(" nserial_connected   ->   %08X\r\n", sz);
  return 0;
}

int32_t nserial_disconnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnserial* p = (cnserial*)o;
  DEBUG_PRINT(" nserial_disconnected   ->   %08X \r\n", sz);

  return 0;
}


int32_t nserial_read(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnserial* p = (cnserial*)o;
  DEBUG_BUFFER(b, sz);

  return __liteio_call(p->_ind, sz, fd, b, sz);
}

int32_t nserial_open(cnserial* p)
{
  int32_t e = 0;
  int32_t sz = 1;
  int8_t _json[1024] = {0};
  int8_t _argv[16][256] = {0};

  p->_imtif.callback[IMTIF_CALLBACK_CONNECTED] = nserial_connected;
  p->_imtif.callback[IMTIF_CALLBACK_DISCONNECTED] = nserial_disconnected;
  p->_imtif.callback[IMTIF_CALLBACK_READ] = nserial_read;

  readArgs(p->_ind->argc, p->_ind->argv, "--serial_port", _argv[0]);
  readArgs(p->_ind->argc, p->_ind->argv, "--serial_baudrate", _argv[1]);
  readArgs(p->_ind->argc, p->_ind->argv, "--serial_size_of_buffer", _argv[2]);

  DEBUG_PRINT("%s, %s, %s\r\n", _argv[0], _argv[1], _argv[2]);

  sprintf(_json, 
          "{"
            "\"PORT\":\"%s\","
            "\"BAUDRATE\":\"%s\","
            "\"DATABIT\":\"8\","
            "\"STOPBIT\":\"1\","
            "\"PARITYBIT\":\"0\","
            "\"BUF_SZ\":\"%d\","
            "\"SYNC\":\"DISABLE\""
          "}",
          _argv[0],
          _argv[1],
          _argv[2]
  );

  sz = atoi(_argv[2]);

  p->buf = (uint8_t*)calloc(sz, sizeof(uint8_t));
  DEBUG_PRINT("%s \r\n", _json);
  e = __serial_open(&p->_imtif.h, _json, p->buf, sz, p->_imtif.callback, p);
  DEBUG_PRINT("%08X \r\n", e);

  return e;
}


int32_t nserial_close(cnserial* p)
{
  int32_t e = 0;
  __serial_close(&p->_imtif.h);
  free(p->buf);
  p->buf = 0;
}


int32_t nserial(struct cnLiteIO* p)
{
  int32_t e = 0;
  cnserial* pd = (cnserial*)calloc(1, sizeof(cnserial));
  p->hdl[NSERIAL] = pd;
  pd->_ind = p;

  DEBUG_PRINT("\r\n");

  e = nserial_open(pd);
  return e;
}

void nserial_loop(struct cnLiteIO* p)
{
  #if 0
  int32_t e = 0;
  uint8_t b[16] = {0};
  uint8_t hex = 0;
  cnserial* pd = (cnserial*)p->hdl[NSERIAL];
  {

    //printf("nserial_open\r\n");
    //e = nserial_open(&gserial);
    //delay(500);


   {
     b[0] = 0x77;
     b[1] = 1;
     b[2] = 4;
     b[3] = 0;
     b[4] = 0;
     b[5] = 1;
     b[6] = 0;
   }

   e = __serial_write(pd->_imtif.h, 0, b, 7, 0, p);
   printf("write : %d\r\n", e);
   //delay(1000);

   // nserial_close(&gserial);
   // delay(500);

  }
  #endif

}
#endif
