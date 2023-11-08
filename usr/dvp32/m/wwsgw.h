#ifndef __WWEBSOCKETGATEWAY_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __WWEBSOCKETGATEWAY_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include "wcommon.h"
#include "mcommon.h"
#include <mdbc.h>

enum
{
  EDIT_WSGW_TCP_PORT,
  EDIT_WSGW_WS_PORT,
  CHECK_WSGW_LOG,
  CHECK_WSGW_REQ,
  BUTTON_WSGW_START,
  BUTTON_WSGW_CLEAR,
  LIST_WSGW_TCP_LOG,
  LIST_WSGW_WS_LOG,
  LIST_WSGW_DB_LOG,
  EDIT_WSGW_MSEC,
  MAX_WSGW_ITEM
};


static unsigned char shof_protocol[32] = {0x02, 0x03, 0x0A,};

#define EQUIP_IDS_COUNT        17
static unsigned char equip_ids[EQUIP_IDS_COUNT] = {1, 16, 0,};


#define MAX_KD_DeviceInfo              33
typedef struct
{
  unsigned char id;
  char did[8];
  char model[16];
  char wfactor[6][32];
  char rfactor[6][8];
}KD_DeviceInfo;


#if (defined XWIN32 || defined WINCE)
#pragma pack(1)
#endif
typedef struct
{
  xREG               REG;
  wLog               log;
  MTIF*              pm;
  unsigned char      wshdr[1024];
  unsigned char      read_lock;
  HWND               hitem[MAX_WSGW_ITEM];
  HWND               hwnd;
  long double        range[2];

  void*              pdbc;
  unsigned char      ecount;
  unsigned char      equip_id;
  unsigned char      qcount;
}wWSGW;
#if (defined XWIN32 || defined WINCE)
#pragma pack()
#endif

void* wwsgw_dlgproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
void* wwsgw_init(HWND hwnd, wWSGW* p);

#endif
