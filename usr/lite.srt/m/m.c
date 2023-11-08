#define _IP              "192.168.0.2"
#define _PORT            "7810"
#define _COMPORT         "/dev/ttyAMA1"
#define _COMBAUDRATE     "115200"

#include <common.h>
#include <xcommon.h>

#include <__nserial.h>
#include <__nsocket.h>

enum
{
  IDLE,
  INIT,
  READY,
  SOCKET_OPEN,
  SOCKET_CLOSE,
  SERIAL_OPEN,
  SERIAL_CLOSE,
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

#define MAX_IDLE_COUNT      1
uint32_t IDLE_COUNT   = MAX_IDLE_COUNT;


typedef struct
{
  cnserial           __serial;
  cnsocket           __socket;
  cIOQ               __ioq;
}cMTIF;
cMTIF*      gp;

void debug_print(const char* fn, int ln, const char* fmt, ...)
{
	va_list args;
  printf(" %16s:%4d | ", fn, ln );
  va_start (args, fmt);
  vfprintf(stdout,fmt, args);
  fflush(stdout);
  va_end(args);
}

#define DEBUG_PRINT(...)   debug_print(__FUNCTION__,__LINE__,__VA_ARGS__)



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

  return 0;
}

void* __socketDisconnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnsocket* p = (cnsocket*)o;
  p->io.__f[IMTIF_CALLBACK_CONNECTED] = 0;

  DEBUG_PRINT("Disconnected (%d)\r\n", fd);
  setStatus(SOCKET_CLOSE);

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


void* __socketRead(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnsocket* p = (cnsocket*)o;

  DEBUG_PRINT("read (%d)\r\n", fd);

  return 0;
}

void* __serialRead(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnserial* p = (cnserial*)o;
  DEBUG_PRINT("read (%d)\r\n", fd);

  return 0;
}

void setup(cMTIF* p)
{

}



void state(cMTIF* p)
{
  switch(getStatus())
  {
    case INIT:
      DEBUG_PRINT("INIT\r\n");
      //setup(p);
      break;

    case READY:
      DEBUG_PRINT("READY\r\n");
      break;

    case SOCKET_OPEN:
      DEBUG_PRINT("SOCKET_OPEN\r\n");
      p->__socket.io.__f[IMTIF_CALLBACK_OPEN] = __socketOpened;
      p->__socket.io.__f[IMTIF_CALLBACK_CLOSE] = __socketClosed;
      p->__socket.io.__f[IMTIF_CALLBACK_CONNECTED] = __socketConnected;
      p->__socket.io.__f[IMTIF_CALLBACK_DISCONNECTED] = __socketDisconnected;
      p->__socket.io.__f[IMTIF_CALLBACK_READ] = __socketRead;
      sprintf(p->__socket.io.argv[0], "%s", _IP);
      sprintf(p->__socket.io.argv[1], "%s", _PORT);
      sprintf(p->__socket.io.argv[2], "%s", "TCP");
      sprintf(p->__socket.io.argv[3], "%s", "CLIENT");
      sprintf(p->__socket.io.argv[4], "%s", "UNICAST");
      p->__socket.io.fd = nsocket_open(&p->__socket);
      DEBUG_PRINT("socket -> %d \r\n", p->__socket.io.fd);
      break;

    case SOCKET_CLOSE:
      DEBUG_PRINT("SOCKET_CLOSE\r\n");
      nsocket_close(&p->__socket);
      p->__socket.io.__f[IMTIF_CALLBACK_CONNECTED] = 0;
      p->__socket.io.__f[IMTIF_CALLBACK_DISCONNECTED] = 0;
      p->__socket.io.__f[IMTIF_CALLBACK_READ] = 0;
      p->__ioq.next = SOCKET_OPEN;
      DEBUG_PRINT("SOCKET_CLOSED\r\n");
      break;

    case SERIAL_OPEN:
      DEBUG_PRINT("SERIAL_OPEN\r\n");
      p->__serial.io.__f[IMTIF_CALLBACK_READ] = __serialRead;
      sprintf(p->__serial.io.argv[0], "%s", _COMPORT);
      sprintf(p->__serial.io.argv[1], "%s", _COMBAUDRATE);
      sprintf(p->__serial.io.argv[2], "%s", "8");
      sprintf(p->__serial.io.argv[3], "%s", "1");
      sprintf(p->__serial.io.argv[4], "%s", "0");
      p->__serial.io.fd = nserial_open(&p->__serial);
      //DEBUG_PRINT("socket -> %d \r\n", p->__socket.io.fd);
      break;

    case SERIAL_CLOSE:
      DEBUG_PRINT("SERIAL_CLOSE\r\n");
      nserial_close(&p->__serial);
      p->__serial.io.__f[IMTIF_CALLBACK_READ] = 0;
      //setStatus(INIT, MAX_IDLE_COUNT);
      DEBUG_PRINT("SERIAL_CLOSED\r\n");

      break;

    case IDLE:

      IDLE_COUNT--;
      if ( IDLE_COUNT == 0 )
      {
        DEBUG_PRINT("IDLE\r\n");
        IDLE_COUNT = MAX_IDLE_COUNT;

        setStatus(p->__ioq.next);
      }
      break;

    default:
      break;

  }
}


void main(int argc, char** argv)
{
  void* hdl = 0;

  uint32_t slp = 4000000;


  static cMTIF      m;
  gp = &m;
  
  xLOCK_INIT(&m.__ioq.crit);


  setStatus(INIT);
  setStatus(READY);
  setStatus(SOCKET_OPEN);
  //setStatus(SERIAL_OPEN);

  while ( 1 )
  {
    state(&m);
    __mcsleep(1);
  }

  xLOCK_FINAL(&m.__ioq.crit);

  //nserial_close(&m.__serial);


}

