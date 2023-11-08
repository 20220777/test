#include "__ua.h"

#define GET_MSGQ_IDX(x) (x=(x>(IOQ_MAX_COUNT-1)?0:x))
#define INC_MSGQ_IDX(x) (x=(x>(IOQ_MAX_COUNT-1)?0:(++x)))

uint32_t IDLE_COUNT   = MAX_IDLE_COUNT;



int32_t setStatus(cLite* p, uint32_t curr)
{
  int32_t e=-1;
  int32_t i=0;

  if ( curr <=0 ) return 0;

  xLOCK(&p->__ioq.crit);
  IDLE_COUNT = MAX_IDLE_COUNT;

  for ( i=0 ; i<IOQ_MAX_COUNT ; i++ )
  {
    if ( p->__ioq.msgq[GET_MSGQ_IDX(p->__ioq.idx[1])] )
    {
      INC_MSGQ_IDX(p->__ioq.idx[1]);
    }
    else
    {
      e = 0;
      break;
    }
  }
  if ( e < 0 )
  {
    xUNLOCK(&p->__ioq.crit);
    return e;
  }
	p->__ioq.msgq[GET_MSGQ_IDX(p->__ioq.idx[1])] = (uint32_t)curr;
  p->__ioq.next = 0;
  INC_MSGQ_IDX(p->__ioq.idx[1]);
  xUNLOCK(&p->__ioq.crit);

	return e;
}

int32_t setNext(cLite* p, uint32_t next)
{
  int32_t e=-1;
  int32_t i=0;

  if ( next <=0 ) return 0;

  xLOCK(&p->__ioq.crit);
  p->__ioq.next = next;

  xUNLOCK(&p->__ioq.crit);

	return e;
}

uint32_t getStatus(cLite* p)
{
  int32_t e=0;

  //printf(" --->>>> %4d, %4d, %4d\r\n", p->__ioq.idx[0], p->__ioq.idx[1], p->__ioq.msgq[GET_MSGQ_IDX(p->__ioq.idx[0])]);

  xLOCK(&p->__ioq.crit);
	if ( p->__ioq.msgq[GET_MSGQ_IDX(p->__ioq.idx[0])] )
	{

		e = p->__ioq.msgq[GET_MSGQ_IDX(p->__ioq.idx[0])];
    p->__ioq.msgq[GET_MSGQ_IDX(p->__ioq.idx[0])] = IDLE;
		INC_MSGQ_IDX(p->__ioq.idx[0]);
	}
  xUNLOCK(&p->__ioq.crit);
	return e;
}

void* __socketOpened(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cLite* p = (cLite*)o;
  int32_t idx = (extra==0)?0:(*(int32_t*)extra);

  DEBUG_PRINT("Opened (%d)\r\n", fd);

  return 0;
}
void* __socketClosed(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnsocket* p = (cnsocket*)o;
  int32_t idx = (extra==0)?0:(*(int32_t*)extra);

  DEBUG_PRINT("Closed (%d)\r\n", fd);

  return 0;
}


void* __socketConnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cLite* p = (cLite*)o;
  int32_t idx = (extra==0)?0:(*(int32_t*)extra);

  DEBUG_PRINT("Connected (%d)\r\n", fd);
  //setNext(SOCKET_WRITE);

  return 0;
}

void* __socketDisconnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cLite* p = (cLite*)o;
  //p->io.__f[IMTIF_CALLBACK_CONNECTED] = 0;

  DEBUG_PRINT("Disconnected (%d)\r\n", fd);
  setStatus(p, SOCKET_CLOSE);

  return 0;
}
void* __socketStatus(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cLite* p = (cLite*)o;

  return 0;
}
void* __socketRead(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cLite* p = (cLite*)o;
  uint8_t hex[1024] = {0};
  uint32_t s = 0;
  DEBUG_PRINT("__socketRead : %08X\r\n", p);
  DEBUG_PRINT("read   (%5d) %08X(%5d)\r\n", fd, sz, sz);

  __fprintf_buffer(b, sz, 0, 16, "read (%5d) %08X(%5d)\r\n", fd, sz, sz);

  DEBUG_PRINT(" >> %s\r\n", p->__sfr.__sifr_initia==0?"NULL":"NOT NULL");
  DEBUG_PRINT(" >> %s\r\n", p->__sfr.__sifr_seed_ecb_encode==0?"NULL":"NOT NULL");
  DEBUG_PRINT(" >> %s\r\n", p->__sfr.__sifr_seed_ecb_decode==0?"NULL":"NOT NULL");
  DEBUG_PRINT(" >> %s\r\n", p->__sfr.__sifr_last_status==0?"NULL":"NOT NULL");
  DEBUG_PRINT(" >> %s\r\n", p->__sfr.__sifr_last_status_string==0?"NULL":"NOT NULL");

  {
    int32_t i=0;

    for ( i=0 ; i<sz ; i++ )
    {
      if ( *(b+i) == '\r'  && *(b+i+1) == '\n' && *(b+i+2) == '\r' && *(b+i+3) == '\n' )
      {
        break;
      }
    }



    for ( ; i<sz ; i++ )
    {
      if ( *(b+i) == '=' )
      {
        i++;
        DEBUG_PRINT("%s\r\n", b+i);
        s = __base64_decode(b+i, sz-(i+2), hex);
        decode_pakcet1(&p->__sfr, hex, s);
        break;
      }
    }



  }

  //setNext(SOCKET_WRITE);

  return 0;
}

void* __socketWrite(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cLite* p = (cLite*)o;
  int32_t e = 0;
  int32_t s = 0;
  uint8_t temp[1024] = {0};
  int8_t  _b[128] = {0};

  // 0001 0000 0006 0003 00000004

  _b[s++] = 0x00;
  _b[s++] = 0x01;

  _b[s++] = 0x00;
  _b[s++] = 0x00;

  _b[s++] = 0x00;
  _b[s++] = 0x06;

  _b[s++] = 0x00;
  _b[s++] = 0x03;

  _b[s++] = 0x00;
  _b[s++] = 0x00;

  _b[s++] = 0x00;
  _b[s++] = 0x04;

  __fprintf_buffer(_b, s, 0, 16, "write (%5d) %08X(%5d)\r\n", fd, s, s);

  #if __NSOCKET__
  e = __nsocket_write(h, fd, _b, s, extra, o);
  #endif
  return 0;
}



void* __httpdConnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cLite* p = (cLite*)o;
  int32_t idx = (extra==0)?0:(*(int32_t*)extra);

  DEBUG_PRINT("Connected (%d)\r\n", fd);

  return 0;
}

void* __httpdDisconnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cLite* p = (cLite*)o;
  //p->io.__f[IMTIF_CALLBACK_CONNECTED] = 0;

  DEBUG_PRINT("Disconnected (%d)\r\n", fd);
  setStatus(p, SOCKET_CLOSE);

  return 0;
}
void* __httpdStatus(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cLite* p = (cLite*)o;

  return 0;
}
void* __httpdRead(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cLite* p = (cLite*)o;

  DEBUG_PRINT("read   (%5d) %08X(%5d)\r\n", fd, sz, sz);

  __fprintf_buffer(b, sz, 0, 16, "read");

  #if __NHTTPD__
  __httpd_close_fd(p, fd);
  #endif
  return 0;
}





void* __websocketConnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cLite* p = (cLite*)o;
  int32_t idx = (extra==0)?0:(*(int32_t*)extra);

  DEBUG_PRINT("Connected (%d)\r\n", fd);
  return 0;
}

void* __websocketDisconnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cLite* p = (cLite*)o;
  //p->io.__f[IMTIF_CALLBACK_CONNECTED] = 0;

  DEBUG_PRINT("Disconnected (%d)\r\n", fd);
  setStatus(p, SOCKET_CLOSE);

  return 0;
}
void* __websocketStatus(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cLite* p = (cLite*)o;

  return 0;
}
static void* __websocketRead(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cLite* p = (cLite*)o;

  DEBUG_PRINT("read   (%5d) %08X(%5d) %s\r\n", fd, sz, sz, b);
  
  display(b, sz, "__websocketRead");

  #if __NWEBSOCKET__
  __nwebsocket_write(h, fd, b, sz, 0, 0);  
  #endif
  return 0;
}






void* __serialOpened(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cLite* p = (cLite*)o;
  int32_t idx = (extra==0)?0:(*(int32_t*)extra);

  DEBUG_PRINT("Opened (%d)\r\n", fd);

  return 0;
}
void* __serialClosed(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cLite* p = (cLite*)o;
  int32_t idx = (extra==0)?0:(*(int32_t*)extra);

  DEBUG_PRINT("Closed (%d)\r\n", fd);

  return 0;
}



void* __serialRead(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cLite* p = (cLite*)o;
  DEBUG_PRINT("read (%d)\r\n", fd);

  return 0;
}

void state(cLite* p)
{
  switch(getStatus(p))
  {
    case INIT:
      DEBUG_PRINT("INIT\r\n");
      break;

    case READY:
      DEBUG_PRINT("READY\r\n");
      break;

    case SOCKET_WRITE:
      #if __NSOCKET__
      DEBUG_PRINT("SOCKET_OPEN\r\n");
      __socketWrite(&p->__socket, p->__socket.io.fd, 0, 0, 0, 0);
      #endif
      break;

    case SOCKET_OPEN:
      #if __NSOCKET__
      DEBUG_PRINT("SOCKET_OPEN : %08X\r\n", p);
  DEBUG_PRINT(" >> %s\r\n", p->__sfr.__sifr_initia==0?"NULL":"NOT NULL");
  DEBUG_PRINT(" >> %s\r\n", p->__sfr.__sifr_seed_ecb_encode==0?"NULL":"NOT NULL");
  DEBUG_PRINT(" >> %s\r\n", p->__sfr.__sifr_seed_ecb_decode==0?"NULL":"NOT NULL");
  DEBUG_PRINT(" >> %s\r\n", p->__sfr.__sifr_last_status==0?"NULL":"NOT NULL");
  DEBUG_PRINT(" >> %s\r\n", p->__sfr.__sifr_last_status_string==0?"NULL":"NOT NULL");

      sprintf(p->__socket.io.argv[SOCKET_IP], "%s", _IP);
      sprintf(p->__socket.io.argv[SOCKET_PORT], "%s", _PORT);
      sprintf(p->__socket.io.argv[SOCKET_PROTOCOL], "%s", "TCP");
      sprintf(p->__socket.io.argv[SOCKET_CSTYPE], "%s", _CSTYPE);
      sprintf(p->__socket.io.argv[SOCKET_CASTTYPE], "%s", "UNICAST");
      p->__socket.io.__f[__CALLBACK_CONNECTED] = __socketConnected;
      p->__socket.io.__f[__CALLBACK_DISCONNECTED] = __socketDisconnected;
      p->__socket.io.__f[__CALLBACK_READ] = __socketRead;
      p->__socket.io.__o = p;

      DEBUG_PRINT("%s\r\n", p->__socket.io.argv[SOCKET_IP]);
      DEBUG_PRINT("%s\r\n", p->__socket.io.argv[SOCKET_PORT]);
      DEBUG_PRINT("%s\r\n", p->__socket.io.argv[SOCKET_PROTOCOL]);
      DEBUG_PRINT("%s\r\n", p->__socket.io.argv[SOCKET_CSTYPE]);
      DEBUG_PRINT("%s\r\n", p->__socket.io.argv[SOCKET_CASTTYPE]);
      p->__socket.io.fd = __nsocket_open(&p->__socket);
      DEBUG_PRINT("socket -> %d \r\n", p->__socket.io.fd);
      #endif
      break;

    case SOCKET_CLOSE:
      #if __NSOCKET__
      DEBUG_PRINT("SOCKET_CLOSE\r\n");
      __nsocket_close(&p->__socket);
      p->__socket.io.__f[__CALLBACK_STATUS] = 0;
      p->__socket.io.__f[__CALLBACK_READ] = 0;
      setNext(p, SOCKET_OPEN);
      DEBUG_PRINT("SOCKET_CLOSED\r\n");
      #endif
      break;

    case SERIAL_OPEN:
      #if __NSERIAL__
      DEBUG_PRINT("SERIAL_OPEN\r\n");
      p->__serial.io.__f[__CALLBACK_READ] = __serialRead;
      p->__serial.io.__o = p;
      sprintf(p->__serial.io.argv[SERIAL_PORT], "%s", _COMPORT);
      sprintf(p->__serial.io.argv[SERIAL_BAUDRATE], "%s", _COMBAUDRATE);
      sprintf(p->__serial.io.argv[SERIAL_DATABIT], "%s", "8");
      sprintf(p->__serial.io.argv[SERIAL_STOPBIT], "%s", "1");
      sprintf(p->__serial.io.argv[SERIAL_PARITYBIT], "%s", "0");
      p->__serial.io.fd = __nserial_open(&p->__serial);
      DEBUG_PRINT("SERIAL_OPEN %d\r\n", p->__serial.io.fd);
      #endif
      break;

    case SERIAL_CLOSE:
      #if __NSERIAL__
      DEBUG_PRINT("SERIAL_CLOSE\r\n");
      __nserial_close(&p->__serial);
      p->__serial.io.__f[__CALLBACK_READ] = 0;
      //setStatus(INIT, MAX_IDLE_COUNT);
      DEBUG_PRINT("SERIAL_CLOSED\r\n");
      #endif
      break;

    case IDLE:

      IDLE_COUNT--;
      if ( IDLE_COUNT == 0 )
      {
        //DEBUG_PRINT("IDLE\r\n");
        IDLE_COUNT = MAX_IDLE_COUNT;

        setStatus(p, p->__ioq.next);
      }
      break;

    default:
      break;

  }
}

#if 0
void main(int argc, char** argv)
{
  void* hdl = 0;

  uint32_t slp = 4000000;


  cLite* p = (cLite*)calloc(1, sizeof(cLite));
  p = p;
  
  xLOCK_INIT(&p->__ioq.crit);

  setStatus(INIT);
  setStatus(READY);
  setStatus(SOCKET_OPEN);
  //setStatus(SERIAL_OPEN);

  init_sifr(&p->__sfr);


  #if 0  
  p->__httpd.io.__f[__CALLBACK_READ] = __httpdRead;
  p->__httpd.io.__f[__CALLBACK_CONNECTED] = __httpdConnected;
  p->__httpd.io.__f[__CALLBACK_DISCONNECTED] = __httpdDisconnected;
  p->__httpd.io.__o = p;
  sprintf(p->__httpd.io.argv[HTTP_PORT], "%s", "8090");
  sprintf(p->__httpd.io.argv[HTTP_HOME], "%s", "D:\\waas\\htdocs\\");
  sprintf(p->__httpd.io.argv[SIZE_OF_BUFFER], "%s", "2048");
  p->__httpd.io.fd = __nhttpd_open(&p->__httpd);
  #endif


  #if 0
  sprintf(p->__websocket.io.argv[WEBSOCKET_URL], "%s", "http://127.0.0.1:8091/");
  sprintf(p->__websocket.io.argv[WEBSOCKET_CSTYPE], "%s", "SERVER");
  sprintf(p->__websocket.io.argv[SIZE_OF_BUFFER], "%s", "2048");
  p->__websocket.io.__f[__CALLBACK_READ] = __websocketRead;
  p->__websocket.io.__f[__CALLBACK_CONNECTED] = __websocketConnected;
  p->__websocket.io.__f[__CALLBACK_DISCONNECTED] = __websocketDisconnected;
  p->__websocket.io.__o = p;
  p->__websocket.io.fd = __nwebsocket_open(&p->__websocket);
  #endif

  while ( 1 )
  {
    state(p);
    __mcsleep(1);
  }

  xLOCK_FINAL(&p->__ioq.crit);


}
#endif
