#ifndef ____UA_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define ____UA_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__



//#define _IP              "192.168.0.106"
//#define _PORT            "502"
//#define _COMPORT         "/dev/ttyAMA1"
#define _COMPORT         "COM4"
#define _COMBAUDRATE     "115200"


#define _IP              "127.0.0.1"
#define _PORT            "80"
#define _CSTYPE          "SERVER"

#include <xcommon.h>
#include <__util.h>
#include <__nserial.h>
#include <__nsocket.h>
#include <__nwebsocket.h>
#include <__nhttpd.h>

#include <__lsifr.h>

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
typedef struct
{
  cSIFR              __sfr;

  #if __NSERIAL__
  cnserial           __serial;
  #endif

  #if __NSOCKET__
  cnsocket           __socket;
  #endif

  #if __NWEBSOCKET__
  cnwebsocket        __websocket;
  #endif

  #if __NHTTPD__
  cnhttpd            __httpd;
  #endif
  cIOQ               __ioq;

}cLite;

int32_t setStatus(cLite*, uint32_t);
int32_t setNext(cLite*, uint32_t);
void state(cLite*);

#endif