#define _IP              "192.168.0.106"
#define _PORT            "502"
//#define _COMPORT         "/dev/ttyAMA1"
#define _COMPORT         "COM4"
#define _COMBAUDRATE     "115200"


#include <xcommon.h>
#include <__util.h>
#include <__nserial.h>
#include <__nsocket.h>
#include <__nwebsocket.h>
#include <__nhttpd.h>
#include "__bitmap.h"

#include "mathematics.h"
#include "utils.h"

enum
{
  IDLE,
  INIT,
  READY,
  WEBSOCKET_OPEN,
  WEBSOCKET_CLOSE,
  SOCKET_OPEN,
  SOCKET_CLOSE,
  SERIAL_OPEN,
  SERIAL_CLOSE,
  SOCKET_WRITE,
  SERIAL_WRITE,
  WEBSOCKET_WRITE,
  MAX_STATUS
};

#define  IOQ_MAX_COUNT       128

typedef struct
{
  #if __LINUX__
  pthread_mutex_t  crit;
  #endif
  #if __WIN32__
  CRITICAL_SECTION  crit;
  #endif

  uint32_t next;
  uint32_t msgq[IOQ_MAX_COUNT];
  uint32_t idx[2];   //0 : output    1:input
}cIOQ;

#define MAX_IDLE_COUNT      0x04000000
uint32_t IDLE_COUNT   = MAX_IDLE_COUNT;


typedef struct
{
  cnserial           __serial;
  cnsocket           __socket;
  cnwebsocket        __websocket;
  cnhttpd            __httpd;
  cIOQ               __ioq;
}cLite;
cLite*      gp;



#define GET_MSGQ_IDX(x) (x=(x>(IOQ_MAX_COUNT-1)?0:x))
#define INC_MSGQ_IDX(x) (x=(x>(IOQ_MAX_COUNT-1)?0:(++x)))

int32_t setStatus(uint32_t curr)
{
  int32_t e=-1;
  int32_t i=0;

  if ( curr <=0 ) return 0;

  xLOCK(&gp->__ioq.crit);
  IDLE_COUNT = MAX_IDLE_COUNT;


  //printf(" ------> %4d, %4d, %4d\r\n", gp->__ioq.idx[0], gp->__ioq.idx[1], curr);

  for ( i=0 ; i<IOQ_MAX_COUNT ; i++ )
  {
    if ( gp->__ioq.msgq[GET_MSGQ_IDX(gp->__ioq.idx[1])] )
    {
      INC_MSGQ_IDX(gp->__ioq.idx[1]);
    }
    else
    {
      e = 0;
      break;
    }
  }
  if ( e < 0 )
  {
    xUNLOCK(&gp->__ioq.crit);
    return e;
  }
	gp->__ioq.msgq[GET_MSGQ_IDX(gp->__ioq.idx[1])] = (uint32_t)curr;
  gp->__ioq.next = 0;
  INC_MSGQ_IDX(gp->__ioq.idx[1]);
  xUNLOCK(&gp->__ioq.crit);

	return e;
}

int32_t setNext(uint32_t next)
{
  int32_t e=-1;
  int32_t i=0;

  if ( next <=0 ) return 0;

  xLOCK(&gp->__ioq.crit);
  gp->__ioq.next = next;

  xUNLOCK(&gp->__ioq.crit);

	return e;
}

uint32_t getStatus()
{
  int32_t e=0;

  //printf(" --->>>> %4d, %4d, %4d\r\n", gp->__ioq.idx[0], gp->__ioq.idx[1], gp->__ioq.msgq[GET_MSGQ_IDX(gp->__ioq.idx[0])]);

  xLOCK(&gp->__ioq.crit);
	if ( gp->__ioq.msgq[GET_MSGQ_IDX(gp->__ioq.idx[0])] )
	{

		e = gp->__ioq.msgq[GET_MSGQ_IDX(gp->__ioq.idx[0])];
    gp->__ioq.msgq[GET_MSGQ_IDX(gp->__ioq.idx[0])] = IDLE;
		INC_MSGQ_IDX(gp->__ioq.idx[0]);
	}
  xUNLOCK(&gp->__ioq.crit);
	return e;
}

void* __socketOpened(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnsocket* p = (cnsocket*)o;
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
  cnsocket* p = (cnsocket*)o;
  int32_t idx = (extra==0)?0:(*(int32_t*)extra);

  DEBUG_PRINT("Connected (%d)\r\n", fd);
  setNext(SOCKET_WRITE);

  return 0;
}

void* __socketDisconnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnsocket* p = (cnsocket*)o;
  //p->io.__f[IMTIF_CALLBACK_CONNECTED] = 0;

  DEBUG_PRINT("Disconnected (%d)\r\n", fd);
  setStatus(SOCKET_CLOSE);

  return 0;
}
void* __socketStatus(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnsocket* p = (cnsocket*)o;

  return 0;
}
void* __socketRead(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnsocket* p = (cnsocket*)o;

  DEBUG_PRINT("read   (%5d) %08X(%5d)\r\n", fd, sz, sz);

  __fprintf_buffer(b, sz, 0, 16, "read (%5d) %08X(%5d)\r\n", fd, sz, sz);

  setNext(SOCKET_WRITE);

  return 0;
}

void* __socketWrite(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnsocket* p = (cnsocket*)o;
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

  e = __nsocket_write(h, fd, _b, s, extra, o);

  return 0;
}



void* __httpdConnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnhttpd* p = (cnhttpd*)o;
  int32_t idx = (extra==0)?0:(*(int32_t*)extra);

  DEBUG_PRINT("Connected (%d)\r\n", fd);

  return 0;
}

void* __httpdDisconnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnhttpd* p = (cnhttpd*)o;
  //p->io.__f[IMTIF_CALLBACK_CONNECTED] = 0;

  DEBUG_PRINT("Disconnected (%d)\r\n", fd);
  setStatus(SOCKET_CLOSE);

  return 0;
}
void* __httpdStatus(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnhttpd* p = (cnhttpd*)o;

  return 0;
}
void* __httpdRead(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnhttpd* p = (cnhttpd*)o;

  DEBUG_PRINT("read   (%5d) %08X(%5d)\r\n", fd, sz, sz);

  __fprintf_buffer(b, sz, 0, 16, "read");


  __httpd_close_fd(p, fd);
  return 0;
}





void* __websocketConnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnwebsocket* p = (cnwebsocket*)o;
  int32_t idx = (extra==0)?0:(*(int32_t*)extra);

  DEBUG_PRINT("Connected (%d)\r\n", fd);
  return 0;
}

void* __websocketDisconnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnwebsocket* p = (cnwebsocket*)o;
  //p->io.__f[IMTIF_CALLBACK_CONNECTED] = 0;

  DEBUG_PRINT("Disconnected (%d)\r\n", fd);
  setStatus(SOCKET_CLOSE);

  return 0;
}
void* __websocketStatus(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnwebsocket* p = (cnwebsocket*)o;

  return 0;
}
static void* __websocketRead(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnwebsocket* p = (cnwebsocket*)o;

  DEBUG_PRINT("read   (%5d) %08X(%5d) %s\r\n", fd, sz, sz, b);
  
  display(b, sz, "__websocketRead");

  __nwebsocket_write(h, fd, b, sz, 0, 0);  

  return 0;
}






void* __serialOpened(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnserial* p = (cnserial*)o;
  int32_t idx = (extra==0)?0:(*(int32_t*)extra);

  DEBUG_PRINT("Opened (%d)\r\n", fd);

  return 0;
}
void* __serialClosed(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnserial* p = (cnserial*)o;
  int32_t idx = (extra==0)?0:(*(int32_t*)extra);

  DEBUG_PRINT("Closed (%d)\r\n", fd);

  return 0;
}



void* __serialRead(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnserial* p = (cnserial*)o;
  DEBUG_PRINT("read (%d)\r\n", fd);

  return 0;
}

void state(cLite* p)
{
  switch(getStatus())
  {
    case INIT:
      DEBUG_PRINT("INIT\r\n");
      break;

    case READY:
      DEBUG_PRINT("READY\r\n");
      break;

    case SOCKET_WRITE:
      DEBUG_PRINT("SOCKET_OPEN\r\n");
      __socketWrite(&p->__socket, p->__socket.io.fd, 0, 0, 0, 0);
      break;

    case SOCKET_OPEN:
      DEBUG_PRINT("SOCKET_OPEN\r\n");
      sprintf(p->__socket.io.argv[SOCKET_IP], "%s", _IP);
      sprintf(p->__socket.io.argv[SOCKET_PORT], "%s", _PORT);
      sprintf(p->__socket.io.argv[SOCKET_PROTOCOL], "%s", "TCP");
      sprintf(p->__socket.io.argv[SOCKET_CSTYPE], "%s", "CLIENT");
      sprintf(p->__socket.io.argv[SOCKET_CASTTYPE], "%s", "UNICAST");
      p->__socket.io.__f[__CALLBACK_CONNECTED] = __socketConnected;
      p->__socket.io.__f[__CALLBACK_DISCONNECTED] = __socketDisconnected;
      p->__socket.io.__f[__CALLBACK_READ] = __socketRead;
      p->__socket.io.__o = p;
      p->__socket.io.fd = __nsocket_open(&p->__socket);
      DEBUG_PRINT("socket -> %d \r\n", p->__socket.io.fd);
      break;

    case SOCKET_CLOSE:
      DEBUG_PRINT("SOCKET_CLOSE\r\n");
      __nsocket_close(&p->__socket);
      p->__socket.io.__f[__CALLBACK_STATUS] = 0;
      p->__socket.io.__f[__CALLBACK_READ] = 0;
      setNext(SOCKET_OPEN);
      DEBUG_PRINT("SOCKET_CLOSED\r\n");
      break;

    case SERIAL_OPEN:
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

      break;

    case SERIAL_CLOSE:
      DEBUG_PRINT("SERIAL_CLOSE\r\n");
      __nserial_close(&p->__serial);
      p->__serial.io.__f[__CALLBACK_READ] = 0;
      //setStatus(INIT, MAX_IDLE_COUNT);
      DEBUG_PRINT("SERIAL_CLOSED\r\n");

      break;

    case IDLE:

      IDLE_COUNT--;
      if ( IDLE_COUNT == 0 )
      {
        //DEBUG_PRINT("IDLE\r\n");
        IDLE_COUNT = MAX_IDLE_COUNT;

        setStatus(p->__ioq.next);
      }
      break;

    default:
      break;

  }
}

void xxxxcnn_main()
{
  uint8_t* p = 0;
  uint8_t* q = 0;
  uint8_t* b = 0;
  int32_t sz = 0;
  int32_t r = 0;
  int32_t xy[2] = {0};
  int32_t wh[2] = {0};

  FILE* fp = fopen("joker3.bmp", "rb");
  FILE* ft = fopen("joker3-rt3-6.bmp", "wb");
  //FILE* fp = fopen("..\\imgs\\sample.bmp", "rb");

  sz = (564*3+BMP_PADDING(564))*1002;

  p = calloc(sz, sizeof(int8_t));
  q = calloc(sz, sizeof(int8_t));
  b = calloc(sz, sizeof(int8_t));

  r = fread(p, sizeof(int8_t), sz, fp);

  xy[0] = 100;
  xy[1] = 120;
  wh[0] = 257;
  wh[1] = 300;

  r = rread_raw(p, xy, wh, &q);
  r = write_raw_bitmap(q, wh, 24, b);

  //r = __rread_raw(p, xy, wh, &q);
  //r = __rwrite_raw_bitmap(q, wh, 24, b);

  r = fwrite(b, r, sizeof(int8_t), ft);



  //__fprintf_buffer(q, r, 0, 16, "raw_bitmap");


  //r = __rread_raw(p, xy, wh, &q);

  //__fprintf_buffer(q, r, 0, 16, "rraw_bitmap");



  //r = __pick_pixel(p, xy, &q);

  //__fprintf_buffer(q, r, 0, 16, "__pick_pixel");

  ////r = pick_mosaic_bitmap(p, 0, 0, 4, 4, &q);


  ////__fprint_buffer("raw image", q, r, 0, 16);


  //write_bitmap("joker3-4.bmp", "4X4", 24, q+54);


  free(p);
  free(q);
  fclose(fp);
  fclose(ft);
}






void xxxmain(int argc, char** argv)
{
  void* hdl = 0;

  uint32_t slp = 4000000;


  cLite* p = (cLite*)calloc(1, sizeof(cLite));
  gp = p;
  
  xLOCK_INIT(&p->__ioq.crit);

  //setStatus(INIT);
  //setStatus(READY);
  //setStatus(SOCKET_OPEN);
  //setStatus(SERIAL_OPEN);


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
    //state(&m);
    __mcsleep(1);
  }

  xLOCK_FINAL(&p->__ioq.crit);


}

