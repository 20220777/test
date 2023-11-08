#include "wCodeX.h"
#include "util.h"
#include "resource.h"


#define WCODEX_TIMER                      WM_USER+1
#define WCODEX_NET_SIMUL_TIMER            1
#define WCODEX_WS_SIMUL_TIMER             WCODEX_NET_SIMUL_TIMER+1
#define WCODEX_SERIAL_SIMUL_TIMER         WCODEX_NET_SIMUL_TIMER+2

static wCodeX* gp;

void change_list_count()
{
  int8_t lcnt[32];
  int32_t e = 0;
  e = GetText(gp->item[EDIT_LIST_COUNT].hwnd, lcnt, 32);
  lcnt[e] = 0;
  gp->max_line = atoi(lcnt);
}


void* fxCallbackSerial(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int32_t fd=0;
  int8_t raw[1024];
  LVLog(gp->item[LIST_READ].hwnd, gp->item[CHECK_SERIAL_LOG].hwnd, gp->max_line, &gp->log, "log", "Serial", "Serial -> EVENT (%08X %08X) (%08X)", LOWORD((uint32_t)msg), HIWORD((uint32_t)msg), (uint32_t)wparam);


	switch( LOWORD((uint32_t)msg) )
	{
	case READ:
    raw_buffer((int8_t*)wparam, (int32_t)lparam, raw);
    LVLog(gp->item[LIST_READ].hwnd, gp->item[CHECK_SERIAL_LOG].hwnd, gp->max_line, &gp->log, "log", "Serial", "Serial -> READ (%d) %s\r\n", (uint32_t)lparam, raw);
		break;
  }
  return 0;
}
void* fxCallbackSocket(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int32_t fd=0;
  int8_t raw[1024];
  int32_t e = 0;
  int32_t i = 0;
  uint8_t txt[512];

	switch( LOWORD((uint32_t)msg) )
	{
	case READ:

    GetText(gp->item[COMBO_NET_DISPLAY_TYPE_W].hwnd, gp->item[COMBO_NET_DISPLAY_TYPE_W].txt, MAX_TITLE);
    if ( gp->item[COMBO_NET_DISPLAY_TYPE_W].txt[0] == 'A' )
    {
      LVLog(gp->item[LIST_READ].hwnd, gp->item[CHECK_NET_LOG].hwnd, gp->max_line, &gp->log, "log", "Socket", "Socket -> READ (%d) %s\r\n", (uint32_t)lparam, (uint8_t*)wparam);
    }
    else
    {
      raw_buffer((int8_t*)wparam, (int32_t)lparam, raw);
      LVLog(gp->item[LIST_READ].hwnd, gp->item[CHECK_NET_LOG].hwnd, gp->max_line, &gp->log, "log", "Socket", "Socket -> READ (%d) %s\r\n", (uint32_t)lparam, raw);
    }

    if ( SendMessage(gp->item[CHECK_NET_ECHO].hwnd, BM_GETCHECK, 0, 0) == BST_CHECKED )
    {
  	  gp->pcx->getMessage(gp->pcx->_sck, (void*)MAKELONG(FDSCRPTRS, XSOCKET), &gp->pcx->modul[XSOCKET].fdset, sizeof(gp->pcx->modul[XSOCKET].fdset));
      for ( i=0; i<FD_SETSIZE ; i++ )
      {
        if ( (gp->pcx->modul[XSOCKET].fdset+i)->a[0] > 0 )
        {
          gp->pcx->setMessage(gp->pcx->_sck, (void*)MAKELONG(FDSCRPTR, XSOCKET), (void*)(gp->pcx->modul[XSOCKET].fdset+i)->a[0],0);
          gp->pcx->setMessage(gp->pcx->_sck, (void*)MAKELONG(WRITE, XSOCKET), (void*)wparam, (void*)lparam);
        }
      }
    }
		break;
  default:
    LVLog(gp->item[LIST_READ].hwnd, gp->item[CHECK_NET_LOG].hwnd, gp->max_line, &gp->log, "log", "Socket", "Socket -> EVENT (%08X %08X) (%08X)", LOWORD((uint32_t)msg), HIWORD((uint32_t)msg), (uint32_t)wparam);
    break;
  }
  return 0;
}

void* fxCallbackWebSocket(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int32_t fd=0;
  int8_t raw[1024];
  LVLog(gp->item[LIST_READ].hwnd, gp->item[CHECK_WS_LOG].hwnd, gp->max_line, &gp->log, "log", "WebSocket", "WebSocket -> EVENT (%08X %08X) (%08X)", LOWORD((uint32_t)msg), HIWORD((uint32_t)msg), (uint32_t)wparam);


	switch( LOWORD((uint32_t)msg) )
	{
	case READ:
    raw_buffer((int8_t*)wparam, (int32_t)lparam, raw);
    LVLog(gp->item[LIST_READ].hwnd, gp->item[CHECK_WS_LOG].hwnd, gp->max_line, &gp->log, "log", "WebSocket", "WebSocket -> READ (%d) %s\r\n", (uint32_t)lparam, raw);
		break;
  }
  return 0;
}


/*******************************************************************************
 *******************************************************************************
 *******************************************************************************
 *
 *
 * WebSocket
 *
 *
 *******************************************************************************
 *******************************************************************************
 *******************************************************************************/


void wCodeX_net_simul_write(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int8_t temp[32];
  int32_t e = 0;
  GetText(gp->item[BUTTON_NET_OPEN_CLOSE].hwnd, temp, 32);
  if ( strcmp(temp, STR_CLOSE) == 0 )
  {
    ChangeComboIndex(gp->item[COMBO_NET_DISPLAY_TYPE_W].hwnd, 1);
    ChangeComboIndex(gp->item[COMBO_NET_DISPLAY_TYPE_R].hwnd, 1);
    //SocketWrite((int8_t*)wparam, (int32_t)lparam);

  	e = gp->pcx->setMessage( gp->pcx->_sck, (void*)MAKELONG(WRITE   , XSOCKET), (void*)wparam, (void*)lparam);
  }
}
void wCodeX_ws_simul_write(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  //int8_t temp[32];
  //GetText(gp->item[BUTTON_WS_OPEN_CLOSE], temp, 32);
  //if ( strcmp(temp, STR_CLOSE) == 0 )
  //{
  //  ChangeComboIndex(gp->item[COMBO_WS_DISPLAY_TYPE_W], 1);
  //  ChangeComboIndex(gp->item[COMBO_WS_DISPLAY_TYPE_R], 1);
  //  WebSocketWrite((int8_t*)wparam, (int32_t)lparam);
  //}
}

void wCodeX_serial_simul_write(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  //int8_t temp[32];
  //GetText(gp->item[BUTTON_SERIAL_OPEN_CLOSE], temp, 32);
  //if ( strcmp(temp, STR_CLOSE) == 0 )
  //{
  //  ChangeComboIndex(gp->item[COMBO_SERIAL_DISPLAY_TYPE_W], 1);
  //  ChangeComboIndex(gp->item[COMBO_SERIAL_DISPLAY_TYPE_R], 1);
  //  SerialWrite((int8_t*)wparam, (int32_t)lparam);
  //}
}



void wCodeX_net_simul_request(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int8_t tmp[512];
  int8_t sim[512];
  int32_t e = 0;
  e = GetText(gp->item[EDIT_NET_WRITE].hwnd, tmp, 512);
  if ( e > 0 )
  {
    tmp[e] = 0;
    e = hexsim(tmp, sim);
    sim[e] = 0;
    change_list_count();
    LVLog(gp->item[LIST_READ].hwnd, gp->item[CHECK_NET_LOG].hwnd, gp->max_line, &gp->log, "log", "%s", sim);
    wCodeX_net_simul_write(hwnd, msg, sim, e);
  }
  else
  {
    SetText(gp->item[EDIT_NET_WRITE].hwnd, "02 AA XX XX XX XX XX XX XX XX 03", 32);
  }
}

void wCodeX_ws_simul_request(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  //int8_t tmp[512];
  //int8_t sim[512];
  //int32_t e = 0;
  //e = GetText(gp->item[EDIT_WS_WRITE], tmp, 512);
  //if ( e > 0 )
  //{
  //  tmp[e] = 0;
  //  e = hexsim(tmp, sim);
  //  sim[e] = 0;
  //  change_list_count();
  //  LVLog(gp->item[LIST_READ], gp->item[CHECK_WS_LOG], gp->max_line, &gp->log, "log", "%s", sim);
  //  wCodeX_ws_simul_write(hwnd, msg, sim, e);
  //}
  //else
  //{
  //  SetText(gp->item[EDIT_WS_WRITE], "02 BB XX XX XX XX XX XX XX XX 03", 32);
  //}
}

void wCodeX_serial_simul_request(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  //int8_t tmp[512];
  //int8_t sim[512];
  //int32_t e = 0;
  //e = GetText(gp->item[EDIT_SERIAL_WRITE], tmp, 512);
  //if ( e > 0 )
  //{
  //  tmp[e] = 0;
  //  e = hexsim(tmp, sim);
  //  sim[e] = 0;
  //  change_list_count();
  //  LVLog(gp->item[LIST_READ], gp->item[CHECK_SERIAL_LOG], gp->max_line, &gp->log, "log", "%s", sim);
  //  wCodeX_serial_simul_write(hwnd, msg, sim, e);
  //}
  //else
  //{
  //  SetText(gp->item[EDIT_SERIAL_WRITE], "02 CC XX XX XX XX XX XX XX XX 03", 32);
  //}
}


void* on_simul_timer(void* hwnd, int32_t msg, int32_t id, int32_t tm)
{
  PostMessage(hwnd, WCODEX_TIMER, MAKEWORD(id, 0), 0);
  return 0;
}
int32_t socketWrite(uint8_t* b, int32_t sz)
{
  int32_t e = 0;
  uint8_t txt[512];
  uint8_t hex[512];

  GetText(gp->item[COMBO_NET_DISPLAY_TYPE_W].hwnd, gp->item[COMBO_NET_DISPLAY_TYPE_W].txt, MAX_TITLE);
  GetText(gp->item[EDIT_NET_WRITE].hwnd,        txt, MAX_TITLE);
  if ( gp->item[COMBO_NET_DISPLAY_TYPE_W].txt[0] == 'A' )
  {
	  gp->pcx->setMessage(gp->pcx->_sck, (void*)MAKELONG(WRITE, XSOCKET), (void*)txt, (void*)strlen(txt));
  }
  else
  {
    e = string_to_hex(txt, hex);
    hex[e] = 0;
	  gp->pcx->setMessage(gp->pcx->_sck, (void*)MAKELONG(WRITE, XSOCKET), (void*)hex, (void*)e);
  }
  return e;
}

int32_t socketWriteTo(uint8_t* b, int32_t sz)
{
  int32_t e = 0;
  uint8_t txt[512];
  uint8_t hex[512];

  GetText(gp->item[COMBO_NET_DISPLAY_TYPE_W].hwnd, gp->item[COMBO_NET_DISPLAY_TYPE_W].txt, MAX_TITLE);
  GetText(gp->item[EDIT_NET_WRITE].hwnd,        txt, MAX_TITLE);
	gp->pcx->setMessage(gp->pcx->_sck, (void*)MAKELONG(XM_DST_IP        , XSOCKET),   (void*)gp->item[EDIT_NET_IP].txt,         (void*)strlen(gp->item[EDIT_NET_IP].txt));
	gp->pcx->setMessage(gp->pcx->_sck, (void*)MAKELONG(XM_DST_PORT      , XSOCKET),   (void*)gp->item[EDIT_NET_PORT].txt,       (void*)strlen(gp->item[EDIT_NET_PORT].txt));
  if ( gp->item[COMBO_NET_DISPLAY_TYPE_W].txt[0] == 'A' )
  {
	  gp->pcx->setMessage(gp->pcx->_sck, (void*)MAKELONG(WRITETO      , XSOCKET), (void*)txt, (void*)strlen(txt));
  }
  else
  {
    e = string_to_hex(txt, hex);
    hex[e] = 0;
	  gp->pcx->setMessage(gp->pcx->_sck, (void*)MAKELONG(WRITETO, XSOCKET), (void*)hex, (void*)e);

  }

  return e;
}


int32_t socketOpen()
{
  int32_t e = 0;

  GetText(gp->item[EDIT_NET_IP].hwnd,        gp->item[EDIT_NET_IP].txt, MAX_TITLE);
  GetText(gp->item[EDIT_NET_PORT].hwnd,      gp->item[EDIT_NET_PORT].txt, MAX_TITLE);
  GetText(gp->item[EDIT_NET_LPORT].hwnd,     gp->item[EDIT_NET_LPORT].txt, MAX_TITLE);
  GetText(gp->item[COMBO_NET_PROTOCOL].hwnd, gp->item[COMBO_NET_PROTOCOL].txt, MAX_TITLE);
  GetText(gp->item[COMBO_NET_CS].hwnd,       gp->item[COMBO_NET_CS].txt, MAX_TITLE);
  GetText(gp->item[COMBO_NET_CASTTYPE].hwnd, gp->item[COMBO_NET_CASTTYPE].txt, MAX_TITLE);

  //gp->pcx->setMessage(gp->pcx->h, (void*)MAKELONG(XM_DELAY_0 , XSOCKET),   (void*)"3000",                 (void*)strlen("3000"));
	gp->pcx->setMessage(&gp->pcx->_sck, (void*)MAKELONG(INIT         , XSOCKET),   (void*)gp->pcx->h,                        (void*)0);
	gp->pcx->setMessage( gp->pcx->_sck, (void*)MAKELONG(XM_KEY       , XSOCKET),   (void*)"shinbaad@gmail.com",              (void*)strlen("shinbaad@gmail.com"));
	gp->pcx->setMessage( gp->pcx->_sck, (void*)MAKELONG(XM_BUFFER_PTR, XSOCKET),   (void*)gp->pcx->sck_buf,                  (void*)1024);
	gp->pcx->setMessage( gp->pcx->_sck, (void*)MAKELONG(XM_ECHOMODE  , XSOCKET),   (void*)"0",                               (void*)strlen("0"));
	gp->pcx->setMessage( gp->pcx->_sck, (void*)MAKELONG(XM_IP        , XSOCKET),   (void*)gp->item[EDIT_NET_IP].txt,         (void*)strlen(gp->item[EDIT_NET_IP].txt));

	//if ( (gp->item[COMBO_NET_PROTOCOL].txt[0]=='U') && (gp->item[COMBO_NET_CS].txt[0]=='C') )//&& (gp->item[COMBO_NET_CASTTYPE].txt[0]!='B') )
 // {
 // 	gp->pcx->setMessage( gp->pcx->_sck, (void*)MAKELONG(XM_PORT      , XSOCKET),   (void*)gp->item[EDIT_NET_LPORT].txt,       (void*)strlen(gp->item[EDIT_NET_LPORT].txt));
 // }
 // else
 // {
 // 	gp->pcx->setMessage( gp->pcx->_sck, (void*)MAKELONG(XM_PORT      , XSOCKET),   (void*)gp->item[EDIT_NET_PORT].txt,       (void*)strlen(gp->item[EDIT_NET_PORT].txt));
 // }
  gp->pcx->setMessage( gp->pcx->_sck, (void*)MAKELONG(XM_PORT      , XSOCKET),   (void*)gp->item[EDIT_NET_PORT].txt,       (void*)strlen(gp->item[EDIT_NET_PORT].txt));
	gp->pcx->setMessage( gp->pcx->_sck, (void*)MAKELONG(XM_PROTO     , XSOCKET),   (void*)gp->item[COMBO_NET_PROTOCOL].txt,  (void*)strlen(gp->item[COMBO_NET_PROTOCOL].txt));
	gp->pcx->setMessage( gp->pcx->_sck, (void*)MAKELONG(XM_CSTYPE    , XSOCKET),   (void*)gp->item[COMBO_NET_CS].txt,        (void*)strlen(gp->item[COMBO_NET_CS].txt));
	gp->pcx->setMessage( gp->pcx->_sck, (void*)MAKELONG(XM_CASTTYPE  , XSOCKET),   (void*)gp->item[COMBO_NET_CASTTYPE].txt,  (void*)strlen(gp->item[COMBO_NET_CASTTYPE].txt));
	gp->pcx->setMessage( gp->pcx->_sck, (void*)MAKELONG(XM_TIMEOUT   , XSOCKET),   (void*)"1000",                            (void*)strlen("4000"));

	gp->pcx->_sckfd = gp->pcx->setMessage(gp->pcx->_sck, (void*)MAKELONG(ENABLE       , XSOCKET),  0, 0);

  return gp->pcx->getMessage(gp->pcx->_sck, (void*)MAKELONG(XM_STATUS , XSOCKET),  0, 0);
}

int32_t websocketOpen()
{
  int32_t e = 0;
  int8_t  ip[128];
  int8_t  uri[128];
  int8_t  port[16];

  GetText(gp->item[EDIT_WS_URL].hwnd,        gp->item[EDIT_WS_URL].txt, MAX_TITLE);
  GetText(gp->item[COMBO_WS_CS].hwnd,        gp->item[COMBO_WS_CS].txt, MAX_TITLE);

  e = get_url(gp->item[EDIT_WS_URL].txt, ip, uri);
  sprintf(port, "%d", e);

	gp->pcx->setMessage(gp->pcx->h, (void*)MAKELONG(XM_KEY       , XWEBSOCKET),   (void*)"shinbaad@gmail.com",        (void*)strlen("shinbaad@gmail.com"));
	gp->pcx->setMessage(gp->pcx->h, (void*)MAKELONG(XM_BUFFER_PTR, XWEBSOCKET),   (void*)gp->pcx->wsck_buf,           (void*)1024);
	gp->pcx->setMessage(gp->pcx->h, (void*)MAKELONG(XM_ECHOMODE  , XWEBSOCKET),   (void*)"0",                         (void*)strlen("0"));
	gp->pcx->setMessage(gp->pcx->h, (void*)MAKELONG(XM_IP        , XWEBSOCKET),   (void*)ip,                          (void*)strlen(ip));
	gp->pcx->setMessage(gp->pcx->h, (void*)MAKELONG(XM_PORT      , XWEBSOCKET),   (void*)port,                        (void*)strlen(port));
	gp->pcx->setMessage(gp->pcx->h, (void*)MAKELONG(XM_CSTYPE    , XWEBSOCKET),   (void*)gp->item[COMBO_WS_CS].txt,   (void*)strlen(gp->item[COMBO_WS_CS].txt));
	gp->pcx->setMessage(gp->pcx->h, (void*)MAKELONG(ENABLE       , XWEBSOCKET),  0, 0);

  return gp->pcx->getMessage(gp->pcx->h, (void*)MAKELONG(XM_STATUS , XWEBSOCKET),  0, 0);
}

int32_t serialOpen(int32_t id)
{
  int32_t e = 0;

  GetText(gp->item[EDIT_NET_IP].hwnd,        gp->item[EDIT_NET_IP].txt, MAX_TITLE);
  GetText(gp->item[EDIT_NET_PORT].hwnd,      gp->item[EDIT_NET_PORT].txt, MAX_TITLE);
  GetText(gp->item[COMBO_NET_PROTOCOL].hwnd, gp->item[COMBO_NET_PROTOCOL].txt, MAX_TITLE);
  GetText(gp->item[COMBO_NET_CS].hwnd,       gp->item[COMBO_NET_CS].txt, MAX_TITLE);
  GetText(gp->item[COMBO_NET_CASTTYPE].hwnd, gp->item[COMBO_NET_CASTTYPE].txt, MAX_TITLE);

  //gp->pcx->setMessage(gp->pcx->h, (void*)MAKELONG(XM_DELAY_0 , XSERIAL),   (void*)"3000",                 (void*)strlen("3000"));
	gp->pcx->setMessage(gp->pcx->h, (void*)MAKELONG(XM_KEY       , XSERIAL),   (void*)"shinbaad@gmail.com",              (void*)strlen("shinbaad@gmail.com"));
	gp->pcx->setMessage(gp->pcx->h, (void*)MAKELONG(XM_BUFFER_PTR, XSERIAL),   (void*)gp->pcx->srl_buf,                  (void*)1);
	gp->pcx->setMessage(gp->pcx->h, (void*)MAKELONG(XM_ECHOMODE  , XSERIAL),   (void*)"0",                               (void*)strlen("0"));
	gp->pcx->setMessage(gp->pcx->h, (void*)MAKELONG(XM_IP        , XSERIAL),   (void*)gp->item[EDIT_NET_IP].txt,         (void*)strlen(gp->item[EDIT_NET_IP].txt));
	gp->pcx->setMessage(gp->pcx->h, (void*)MAKELONG(XM_PORT      , XSERIAL),   (void*)gp->item[EDIT_NET_PORT].txt,       (void*)strlen(gp->item[EDIT_NET_PORT].txt));
	gp->pcx->setMessage(gp->pcx->h, (void*)MAKELONG(XM_PROTO     , XSERIAL),   (void*)gp->item[COMBO_NET_PROTOCOL].txt,  (void*)strlen(gp->item[COMBO_NET_PROTOCOL].txt));
	gp->pcx->setMessage(gp->pcx->h, (void*)MAKELONG(XM_CSTYPE    , XSERIAL),   (void*)gp->item[COMBO_NET_CS].txt,        (void*)strlen(gp->item[COMBO_NET_CS].txt));
	gp->pcx->setMessage(gp->pcx->h, (void*)MAKELONG(XM_CASTTYPE  , XSERIAL),   (void*)gp->item[COMBO_NET_CASTTYPE].txt,  (void*)strlen(gp->item[COMBO_NET_CASTTYPE].txt));
	gp->pcx->setMessage(gp->pcx->h, (void*)MAKELONG(ENABLE       , XSERIAL),  0, 0);

  return gp->pcx->getMessage(gp->pcx->h, (void*)MAKELONG(XM_STATUS , XSERIAL),  0, 0);
}


void fIDC_BUTTON_NET_OPEN_CLOSE(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{

  int8_t temp[32];
  int32_t e = 0;
  int32_t fd = 0;

  GetText(gp->item[BUTTON_NET_OPEN_CLOSE].hwnd, temp, 32);
  change_list_count();
  if ( strcmp(temp, STR_OPEN) == 0 )
  {
	  if ( socketOpen() == 'E' )
    {
      SetText(gp->item[BUTTON_NET_OPEN_CLOSE].hwnd, STR_CLOSE, strlen(STR_CLOSE));

      gp->pcx->getMessage(gp->pcx->_sck,  (void*)MAKELONG(FDSCRPTR     , XSOCKET),  &fd, 0);
      LVLog(gp->item[LIST_READ].hwnd, gp->item[CHECK_NET_LOG].hwnd, gp->max_line, &gp->log, "log", "Socket", "Socket (%d) Open Success %s %s %s %s %s",
                              fd,
                              gp->item[EDIT_NET_IP].txt,
                              gp->item[EDIT_NET_PORT].txt,
                              gp->item[COMBO_NET_PROTOCOL].txt,
                              gp->item[COMBO_NET_CS].txt,
                              gp->item[COMBO_NET_CASTTYPE].txt);
    }
    else
    {
      LVLog(gp->item[LIST_READ].hwnd, gp->item[CHECK_NET_LOG].hwnd, gp->max_line, &gp->log, "log", "Socket", "Socket Open Fail %s %s %s %s %s",
                              gp->item[EDIT_NET_IP].txt,
                              gp->item[EDIT_NET_PORT].txt,
                              gp->item[COMBO_NET_PROTOCOL].txt,
                              gp->item[COMBO_NET_CS].txt,
                              gp->item[COMBO_NET_CASTTYPE].txt);
    }
  }
  else if ( strcmp(temp, STR_CLOSE) == 0 )
  {
    gp->pcx->getMessage( gp->pcx->_sck,  (void*)MAKELONG(FDSCRPTR     , XSOCKET),  &fd, 0);
    gp->pcx->setMessage( gp->pcx->_sck, (void*)MAKELONG(DISABLE, XSOCKET), 0, 0);
    gp->pcx->setMessage(&gp->pcx->_sck, (void*)MAKELONG(RELEASE, XSOCKET), 0, 0);
    SetText(gp->item[BUTTON_NET_OPEN_CLOSE].hwnd, STR_OPEN, strlen(STR_OPEN));
    LVLog(gp->item[LIST_READ].hwnd, gp->item[CHECK_NET_LOG].hwnd, gp->max_line, &gp->log, "log", "Socket", "Socket (%d) Closed %s %s %s %s %s",
                            fd,
                            gp->item[EDIT_NET_IP].txt,
                            gp->item[EDIT_NET_PORT].txt,
                            gp->item[COMBO_NET_PROTOCOL].txt,
                            gp->item[COMBO_NET_CS].txt,
                            gp->item[COMBO_NET_CASTTYPE].txt);
  }



}


void fIDC_BUTTON_WS_OPEN_CLOSE(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int8_t temp[32];
  int32_t e = 0;
  int32_t fd = 0;

  GetText(gp->item[BUTTON_WS_OPEN_CLOSE].hwnd, temp, 32);
  change_list_count();
  if ( strcmp(temp, STR_OPEN) == 0 )
  {
	  if ( websocketOpen() == 'E' )
    {
      SetText(gp->item[BUTTON_WS_OPEN_CLOSE].hwnd, STR_CLOSE, strlen(STR_CLOSE));

      gp->pcx->getMessage(gp->pcx->h,  (void*)MAKELONG(FDSCRPTR     , XWEBSOCKET),  &fd, 0);
      LVLog(gp->item[LIST_READ].hwnd, gp->item[CHECK_WS_LOG].hwnd, gp->max_line, &gp->log, "log", "WebSocket", "WebSocket (%d) Open Success %s %s",
                              fd,
                              gp->item[EDIT_WS_URL].txt,
                              gp->item[COMBO_WS_CS].txt);
    }
    else
    {
      LVLog(gp->item[LIST_READ].hwnd, gp->item[CHECK_WS_LOG].hwnd, gp->max_line, &gp->log, "log", "WebSocket", "WebSocket Open Fail %s %s",
                              gp->item[EDIT_WS_URL].txt,
                              gp->item[COMBO_WS_CS].txt);
    }
  }
  else if ( strcmp(temp, STR_CLOSE) == 0 )
  {
    gp->pcx->getMessage(gp->pcx->h,  (void*)MAKELONG(FDSCRPTR     , XWEBSOCKET),  &fd, 0);
    gp->pcx->setMessage(gp->pcx->h, (void*)MAKELONG(DISABLE, XWEBSOCKET), 0, 0);
    SetText(gp->item[BUTTON_WS_OPEN_CLOSE].hwnd, STR_OPEN, strlen(STR_OPEN));
    LVLog(gp->item[LIST_READ].hwnd, gp->item[CHECK_WS_LOG].hwnd, gp->max_line, &gp->log, "log", "WebSocket", "WebSocket (%d) Closed %s %s",
                            fd,
                              gp->item[EDIT_WS_URL].txt,
                              gp->item[COMBO_WS_CS].txt);
  }

  //int8_t temp[32];
  //GetText(gp->item[BUTTON_WS_OPEN_CLOSE], temp, 32);
  //if ( strcmp(temp, STR_OPEN) == 0 )
  //{
  //  if ( WebSocketOpen()> 0 )
  //  {
  //    SetText(gp->item[BUTTON_WS_OPEN_CLOSE], STR_CLOSE, strlen(STR_CLOSE));
  //    change_list_count();
  //    LVLog(gp->item[LIST_READ], gp->item[CHECK_WS_LOG], gp->max_line, &gp->log, "log", "WebSocket", "WebSocket Open SUCCESS");
  //  }
  //  else
  //  {
  //    change_list_count();
  //    LVLog(gp->item[LIST_READ], gp->item[CHECK_WS_LOG], gp->max_line, &gp->log, "log", "WebSocket", "WebSocket Open FAIL");
  //  }
  //}
  //else
  //{
  //  SetText(gp->item[BUTTON_WS_OPEN_CLOSE], STR_OPEN, strlen(STR_OPEN));
  //  WebSocketClose();
  //  change_list_count();
  //  LVLog(gp->item[LIST_READ], gp->item[CHECK_WS_LOG], gp->max_line, &gp->log, "log", "WebSocket", "WebSocket Open SUCCESS");
  //}
}


void fIDC_BUTTON_SERIAL_OPEN_CLOSE(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  //int8_t temp[32];

  //GetText(gp->item[BUTTON_SERIAL_OPEN_CLOSE], temp, 32);
  //if ( strcmp(temp, STR_OPEN) == 0 )
  //{
  //  if ( SerialOpen()> 0 )
  //  {
  //    SetText(gp->item[BUTTON_SERIAL_OPEN_CLOSE], STR_CLOSE, strlen(STR_CLOSE));
  //    change_list_count();
  //    LVLog(gp->item[LIST_READ], gp->item[CHECK_SERIAL_LOG], gp->max_line, &gp->log, "log", "Serial #1", "Serial #1 (%d) Open Success %s %s %s %s %s",
  //                            gp->pm->msrl[0].fd,
  //                            ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_PORT],
  //                            ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_BAUDRATE],
  //                            ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_DATABIT],
  //                            ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_STOPBIT],
  //                            ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_PARITYBIT]);
  //  }
  //  else
  //  {
  //    change_list_count();
  //    LVLog(gp->item[LIST_READ], gp->item[CHECK_SERIAL_LOG], gp->max_line, &gp->log, "log", "Serial #1", "Serial #1 (%d) Open Fail %s %s %s %s %s",
  //                            gp->pm->msrl[0].fd,
  //                            ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_PORT],
  //                            ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_BAUDRATE],
  //                            ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_DATABIT],
  //                            ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_STOPBIT],
  //                            ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_PARITYBIT]);
  //  }
  //}
  //else
  //{
  //  SetText(gp->item[BUTTON_SERIAL_OPEN_CLOSE], STR_OPEN, strlen(STR_OPEN));
  //  SerialClose();
  //  change_list_count();
  //  LVLog(gp->item[LIST_READ], gp->item[CHECK_SERIAL_LOG], gp->max_line, &gp->log, "log", "Serial #1", "Serial #1 (%d) Closed %s %s %s %s %s",
  //                          gp->pm->msrl[0].fd,
  //                          ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_PORT],
  //                          ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_BAUDRATE],
  //                          ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_DATABIT],
  //                          ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_STOPBIT],
  //                          ((mtifInfo*)gp->pm->msrl[0].info)->arg[XSERIAL][XM_PARITYBIT]);
  //}
}

void fIDC_BUTTON_SERIAL_OPEN_CLOSE2(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  //int8_t temp[32];

  //GetText(gp->item[BUTTON_SERIAL_OPEN_CLOSE2], temp, 32);
  //if ( strcmp(temp, STR_OPEN) == 0 )
  //{
  //  if ( SerialOpen2()> 0 )
  //  {
  //    SetText(gp->item[BUTTON_SERIAL_OPEN_CLOSE2], STR_CLOSE, strlen(STR_CLOSE));
  //    change_list_count();
  //    LVLog(gp->item[LIST_READ], gp->item[CHECK_SERIAL_LOG2], gp->max_line, &gp->log, "log", "Serial #2", "Serial #2 (%d) Open Success %s %s %s %s %s",
  //                            gp->pm->msrl[1].fd,
  //                            ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_PORT],
  //                            ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_BAUDRATE],
  //                            ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_DATABIT],
  //                            ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_STOPBIT],
  //                            ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_PARITYBIT]);
  //  }
  //  else
  //  {
  //    change_list_count();
  //    LVLog(gp->item[LIST_READ], gp->item[CHECK_SERIAL_LOG2], gp->max_line, &gp->log, "log", "Serial #2", "Serial #2 (%d) Open Fail %s %s %s %s %s",
  //                            gp->pm->msrl[1].fd,
  //                            ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_PORT],
  //                            ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_BAUDRATE],
  //                            ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_DATABIT],
  //                            ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_STOPBIT],
  //                            ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_PARITYBIT]);
  //  }
  //}
  //else
  //{
  //  SetText(gp->item[BUTTON_SERIAL_OPEN_CLOSE2], STR_OPEN, strlen(STR_OPEN));
  //  SerialClose2();
  //  change_list_count();
  //  LVLog(gp->item[LIST_READ], gp->item[CHECK_SERIAL_LOG2], gp->max_line, &gp->log, "log", "Serial #2", "Serial #2 (%d) Closed %s %s %s %s %s",
  //                          gp->pm->msrl[1].fd,
  //                          ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_PORT],
  //                          ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_BAUDRATE],
  //                          ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_DATABIT],
  //                          ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_STOPBIT],
  //                          ((mtifInfo*)gp->pm->msrl[1].info)->arg[XSERIAL][XM_PARITYBIT]);
  //}
}


void wCodeX_command(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int8_t tmp[32];
  switch(LOWORD(wparam))
  {
    case IDC_BUTTON_NET_OPEN_CLOSE:
      fIDC_BUTTON_NET_OPEN_CLOSE(hwnd, msg, wparam, lparam);
      break;

    case IDC_BUTTON_WS_OPEN_CLOSE:
      fIDC_BUTTON_WS_OPEN_CLOSE(hwnd, msg, wparam, lparam);
      break;

    case IDC_BUTTON_SERIAL_OPEN_CLOSE:
      fIDC_BUTTON_SERIAL_OPEN_CLOSE(hwnd, msg, wparam, lparam);
      break;

    case IDC_BUTTON_SERIAL_OPEN_CLOSE2:
      fIDC_BUTTON_SERIAL_OPEN_CLOSE2(hwnd, msg, wparam, lparam);
      break;

    case IDC_BUTTON_NET_WRITE:
    	if ( gp->item[COMBO_NET_PROTOCOL].txt[0] == 'T' ) socketWrite(0,0);
    	else if ( gp->item[COMBO_NET_PROTOCOL].txt[0] == 'U' ) socketWriteTo(0,0);
      break;

    //case IDC_BUTTON_WS_WRITE:
    //  WebSocketWrite(0,0);
    //  break;

    //case IDC_BUTTON_SERIAL_WRITE:
    //  SerialWrite(0, 0);
    //  break;

    //case IDC_BUTTON_SERIAL_WRITE2:
    //  SerialWrite2(0, 0);
    //  break;

    case IDC_BUTTON_CLEAR:
      //ClearListView(gp->item[LIST_READ]);
      break;

    //case IDC_CHECK_READ_YN:
    //  if ( SendMessage(gp->item[CHECK_READ_YN], BM_GETCHECK, 0, 0) == BST_CHECKED )
    //  {
    //    gp->read_lock = 0x01;
    //  }
    //  else
    //  {
    //    gp->read_lock = 0x00;
    //  }
    //  break;

    case IDC_CHECK_NET_SIMULA:
      GetText(gp->item[EDIT_NET_MSEC].hwnd, tmp, 32);
      if ( SendMessage(gp->item[CHECK_NET_SIMUL].hwnd, BM_GETCHECK, 0, 0) == BST_CHECKED )
      {
        set_timer(hwnd, WCODEX_NET_SIMUL_TIMER, atoi(tmp), on_simul_timer);
      }
      else
      {
        kill_timer(hwnd, WCODEX_NET_SIMUL_TIMER);
      }
      break;

    //case IDC_CHECK_WS_SIMULA:
    //  GetText(gp->item[EDIT_WS_MSEC], tmp, 32);
    //  if ( SendMessage(gp->item[CHECK_WS_SIMUL], BM_GETCHECK, 0, 0) == BST_CHECKED )
    //  {
    //    set_timer(hwnd, WCODEX_WS_SIMUL_TIMER, atoi(tmp), on_simul_timer);
    //  }
    //  else
    //  {
    //    kill_timer(hwnd, WCODEX_WS_SIMUL_TIMER);
    //  }
    //  break;
    //case IDC_CHECK_SERIAL_SIMULA:
    //  GetText(gp->item[EDIT_SERIAL_MSEC], tmp, 32);
    //  if ( SendMessage(gp->item[CHECK_SERIAL_SIMUL], BM_GETCHECK, 0, 0) == BST_CHECKED )
    //  {
    //    set_timer(hwnd, WCODEX_SERIAL_SIMUL_TIMER, atoi(tmp), on_simul_timer);
    //  }
    //  else
    //  {
    //    kill_timer(hwnd, WCODEX_SERIAL_SIMUL_TIMER);
    //  }
    //  break;



  }    
}

void wCodeX_timer(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  switch(LOWORD(wparam))
  {
    case WCODEX_NET_SIMUL_TIMER:
      wCodeX_net_simul_request(hwnd, msg, wparam, lparam);
      break;
    case WCODEX_WS_SIMUL_TIMER:
      wCodeX_ws_simul_request(hwnd, msg, wparam, lparam);
      break;
    case WCODEX_SERIAL_SIMUL_TIMER:
      wCodeX_serial_simul_request(hwnd, msg, wparam, lparam);
      break;
  }

}


void* wCodeXDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  switch(msg)
  {
    case WM_COMMAND:
      wCodeX_command(hwnd, msg, wparam, lparam);
      break;
    case WCODEX_TIMER:
      wCodeX_timer(hwnd, msg, wparam, lparam);
      break;
    default:
      break;    
  }

  return 0;
}


void* wCodeXInit(HWND hwnd, wCodeX* p)
{
  int32_t e;
  gp = p;

  gp->item[EDIT_NET_IP].hwnd = GetDlgItem(hwnd, IDC_EDIT_NET_IP);
  gp->item[EDIT_NET_PORT].hwnd = GetDlgItem(hwnd, IDC_EDIT_NET_PORT);
  gp->item[EDIT_NET_LPORT].hwnd = GetDlgItem(hwnd, IDC_EDIT_NET_LPORT);
  gp->item[COMBO_NET_PROTOCOL].hwnd = GetDlgItem(hwnd, IDC_COMBO_NET_PROTOCOL);
  gp->item[COMBO_NET_CS].hwnd = GetDlgItem(hwnd, IDC_COMBO_NET_CS);
  gp->item[COMBO_NET_CASTTYPE].hwnd = GetDlgItem(hwnd, IDC_COMBO_NET_CASTTYPE);
  gp->item[BUTTON_NET_OPEN_CLOSE].hwnd = GetDlgItem(hwnd, IDC_BUTTON_NET_OPEN_CLOSE);
  gp->item[EDIT_NET_WRITE].hwnd = GetDlgItem(hwnd, IDC_EDIT_NET_WRITE);
  gp->item[BUTTON_NET_WRITE].hwnd = GetDlgItem(hwnd, IDC_BUTTON_NET_WRITE);
  gp->item[CHECK_NET_CR].hwnd = GetDlgItem(hwnd, IDC_CHECK_NET_CR);
  gp->item[CHECK_NET_LF].hwnd = GetDlgItem(hwnd, IDC_CHECK_NET_LF);
  gp->item[COMBO_NET_DISPLAY_TYPE_W].hwnd = GetDlgItem(hwnd, IDC_COMBO_NET_DISPLAY_TYPE_W);
  gp->item[COMBO_NET_DISPLAY_TYPE_R].hwnd = GetDlgItem(hwnd, IDC_COMBO_NET_DISPLAY_TYPE_R);
  gp->item[EDIT_SERIAL_PORT].hwnd = GetDlgItem(hwnd, IDC_EDIT_SERIAL_PORT);
  gp->item[EDIT_SERIAL_BAUDRATE].hwnd = GetDlgItem(hwnd, IDC_EDIT_SERIAL_BAUD);
  gp->item[EDIT_SERIAL_DBIT].hwnd = GetDlgItem(hwnd, IDC_EDIT_SERIAL_DBIT);
  gp->item[EDIT_SERIAL_SBIT].hwnd = GetDlgItem(hwnd, IDC_EDIT_SERIAL_SBIT);
  gp->item[EDIT_SERIAL_PBIT].hwnd = GetDlgItem(hwnd, IDC_EDIT_SERIAL_PBIT);
  gp->item[BUTTON_SERIAL_OPEN_CLOSE].hwnd = GetDlgItem(hwnd, IDC_BUTTON_SERIAL_OPEN_CLOSE);
  gp->item[COMBO_SERIAL_DISPLAY_TYPE_R].hwnd = GetDlgItem(hwnd, IDC_COMBO_SERIAL_DISPLAY_TYPE_R);
  gp->item[COMBO_SERIAL_DISPLAY_TYPE_W].hwnd = GetDlgItem(hwnd, IDC_COMBO_SERIAL_DISPLAY_TYPE_W);
  gp->item[EDIT_SERIAL_WRITE].hwnd = GetDlgItem(hwnd, IDC_EDIT_SERIAL_WRITE);
  gp->item[BUTTON_SERIAL_WRITE].hwnd = GetDlgItem(hwnd, IDC_BUTTON_SERIAL_WRITE);
  gp->item[CHECK_SERIAL_CR].hwnd = GetDlgItem(hwnd, IDC_CHECK_SERIAL_CR);
  gp->item[CHECK_SERIAL_LF].hwnd = GetDlgItem(hwnd, IDC_CHECK_SERIAL_LF);
  gp->item[CHECK_SERIAL_ROUTER].hwnd = GetDlgItem(hwnd, IDC_CHECK_SERIAL_ROUTER);
  gp->item[EDIT_SERIAL_PORT2].hwnd = GetDlgItem(hwnd, IDC_EDIT_SERIAL_PORT2);
  gp->item[EDIT_SERIAL_BAUDRATE2].hwnd = GetDlgItem(hwnd, IDC_EDIT_SERIAL_BAUD2);
  gp->item[EDIT_SERIAL_DBIT2].hwnd = GetDlgItem(hwnd, IDC_EDIT_SERIAL_DBIT2);
  gp->item[EDIT_SERIAL_SBIT2].hwnd = GetDlgItem(hwnd, IDC_EDIT_SERIAL_SBIT2);
  gp->item[EDIT_SERIAL_PBIT2].hwnd = GetDlgItem(hwnd, IDC_EDIT_SERIAL_PBIT2);
  gp->item[BUTTON_SERIAL_OPEN_CLOSE2].hwnd = GetDlgItem(hwnd, IDC_BUTTON_SERIAL_OPEN_CLOSE2);
  gp->item[COMBO_SERIAL_DISPLAY_TYPE_R2].hwnd = GetDlgItem(hwnd, IDC_COMBO_SERIAL_DISPLAY_TYPE_R2);
  gp->item[COMBO_SERIAL_DISPLAY_TYPE_W2].hwnd = GetDlgItem(hwnd, IDC_COMBO_SERIAL_DISPLAY_TYPE_W2);
  gp->item[EDIT_SERIAL_WRITE2].hwnd = GetDlgItem(hwnd, IDC_EDIT_SERIAL_WRITE2);
  gp->item[BUTTON_SERIAL_WRITE2].hwnd = GetDlgItem(hwnd, IDC_BUTTON_SERIAL_WRITE2);
  gp->item[CHECK_SERIAL_CR2].hwnd = GetDlgItem(hwnd, IDC_CHECK_SERIAL_CR2);
  gp->item[CHECK_SERIAL_LF2].hwnd = GetDlgItem(hwnd, IDC_CHECK_SERIAL_LF2);
  gp->item[LIST_READ].hwnd = GetDlgItem(hwnd, IDC_LIST_READ);
  gp->item[CHECK_READ_YN].hwnd = GetDlgItem(hwnd, IDC_CHECK_READ_YN);
  gp->item[BUTTON_CLEAR].hwnd = GetDlgItem(hwnd, IDC_BUTTON_CLEAR);
  gp->item[COMBO_WS_CS].hwnd = GetDlgItem(hwnd, IDC_COMBO_WS_CS);
  gp->item[EDIT_WS_URL].hwnd = GetDlgItem(hwnd, IDC_EDIT_WS_URL);
  gp->item[COMBO_WS_DISPLAY_TYPE_W].hwnd = GetDlgItem(hwnd, IDC_COMBO_WS_DISPLAY_TYPE_W);
  gp->item[COMBO_WS_DISPLAY_TYPE_R].hwnd = GetDlgItem(hwnd, IDC_COMBO_WS_DISPLAY_TYPE_R);
  gp->item[BUTTON_WS_OPEN_CLOSE].hwnd = GetDlgItem(hwnd, IDC_BUTTON_WS_OPEN_CLOSE);
	gp->item[EDIT_WS_WRITE].hwnd = GetDlgItem(hwnd, IDC_EDIT_WS_WRITE);
	gp->item[CHECK_WS_CR].hwnd = GetDlgItem(hwnd, IDC_CHECK_WS_CR);
	gp->item[CHECK_WS_LF].hwnd = GetDlgItem(hwnd, IDC_CHECK_WS_LF);
	gp->item[BUTTON_WS_WRITE].hwnd = GetDlgItem(hwnd, IDC_BUTTON_WS_WRITE);
  gp->item[CHECK_NET_LOG].hwnd = GetDlgItem(hwnd, IDC_CHECK_NET_LOG);
  gp->item[CHECK_WS_LOG].hwnd = GetDlgItem(hwnd, IDC_CHECK_WS_LOG);
  gp->item[CHECK_SERIAL_LOG].hwnd = GetDlgItem(hwnd, IDC_CHECK_SERIAL_LOG);
  gp->item[CHECK_SERIAL_LOG2].hwnd = GetDlgItem(hwnd, IDC_CHECK_SERIAL_LOG2);
  gp->item[CHECK_NET_ECHO].hwnd = GetDlgItem(hwnd, IDC_CHECK_NET_ECHO);
  gp->item[CHECK_WS_ECHO].hwnd = GetDlgItem(hwnd, IDC_CHECK_WS_ECHO);
  gp->item[CHECK_SERIAL_ECHO].hwnd = GetDlgItem(hwnd, IDC_CHECK_SERIAL_ECHO);
  gp->item[CHECK_SERIAL_ECHO2].hwnd = GetDlgItem(hwnd, IDC_CHECK_SERIAL_ECHO2);
  gp->item[EDIT_SERIAL_MSEC].hwnd = GetDlgItem(hwnd, IDC_EDIT_SERIAL_MSEC);
  gp->item[CHECK_SERIAL_SIMUL].hwnd = GetDlgItem(hwnd, IDC_CHECK_SERIAL_SIMULA);
  gp->item[CHECK_NET_SIMUL].hwnd = GetDlgItem(hwnd, IDC_CHECK_NET_SIMULA);
  gp->item[CHECK_WS_SIMUL].hwnd = GetDlgItem(hwnd, IDC_CHECK_WS_SIMULA);
  gp->item[CHECK_NET_STX].hwnd = GetDlgItem(hwnd, IDC_CHECK_NET_STX);
  gp->item[CHECK_NET_ETX].hwnd = GetDlgItem(hwnd, IDC_CHECK_NET_ETX);
  gp->item[CHECK_WS_STX].hwnd = GetDlgItem(hwnd, IDC_CHECK_WS_STX);
  gp->item[CHECK_WS_ETX].hwnd = GetDlgItem(hwnd, IDC_CHECK_WS_ETX);
  gp->item[CHECK_SERIAL_STX].hwnd = GetDlgItem(hwnd, IDC_CHECK_SERIAL_STX);
  gp->item[CHECK_SERIAL_ETX].hwnd = GetDlgItem(hwnd, IDC_CHECK_SERIAL_ETX);
  gp->item[CHECK_SERIAL_STX2].hwnd = GetDlgItem(hwnd, IDC_CHECK_SERIAL_STX2);
  gp->item[CHECK_SERIAL_ETX2].hwnd = GetDlgItem(hwnd, IDC_CHECK_SERIAL_ETX2);
  gp->item[EDIT_NET_MSEC].hwnd = GetDlgItem(hwnd, IDC_EDIT_NET_MSEC);
  gp->item[EDIT_WS_MSEC].hwnd = GetDlgItem(hwnd, IDC_EDIT_WS_MSEC);
  gp->item[EDIT_LIST_COUNT].hwnd = GetDlgItem(hwnd, IDC_EDIT_LIST_COUNT);


  SetText(gp->item[EDIT_NET_IP].hwnd, "127.0.0.1", strlen("127.0.0.1"));
  SetText(gp->item[EDIT_NET_PORT].hwnd, "7870", strlen("7870"));
  SetText(gp->item[EDIT_NET_LPORT].hwnd, "7880", strlen("7880"));
  SetText(gp->item[BUTTON_NET_WRITE].hwnd, "SEND", strlen("SEND"));
  SetText(gp->item[BUTTON_NET_OPEN_CLOSE].hwnd, STR_OPEN, strlen(STR_OPEN));
  SetText(gp->item[BUTTON_SERIAL_WRITE].hwnd, "WRITE", strlen("WRITE"));
  SetText(gp->item[BUTTON_WS_OPEN_CLOSE].hwnd, STR_OPEN, strlen(STR_OPEN));
  SetText(gp->item[BUTTON_CLEAR].hwnd, "CLEAR", strlen("CLEAR"));
  SetText(gp->item[EDIT_WS_URL].hwnd, "http://127.0.0.1:7810/", strlen("http://127.0.0.1:7810/"));
  SetText(gp->item[BUTTON_WS_OPEN_CLOSE].hwnd, STR_OPEN, strlen(STR_OPEN));
  SetText(gp->item[BUTTON_WS_WRITE].hwnd, "SEND", strlen("SEND"));

  ResetText(gp->item[EDIT_SERIAL_PORT].hwnd, "COM1");
  ResetText(gp->item[EDIT_SERIAL_BAUDRATE].hwnd, "115200");
  ResetText(gp->item[EDIT_SERIAL_DBIT].hwnd, "8");
  ResetText(gp->item[EDIT_SERIAL_SBIT].hwnd, "1");
  ResetText(gp->item[EDIT_SERIAL_PBIT].hwnd, "0");

  ResetText(gp->item[EDIT_SERIAL_PORT2].hwnd, "COM2");
  ResetText(gp->item[EDIT_SERIAL_BAUDRATE2].hwnd, "115200");
  ResetText(gp->item[EDIT_SERIAL_DBIT2].hwnd, "8");
  ResetText(gp->item[EDIT_SERIAL_SBIT2].hwnd, "1");
  ResetText(gp->item[EDIT_SERIAL_PBIT2].hwnd, "0");


  ResetText(gp->item[EDIT_NET_MSEC].hwnd, "1000");
  ResetText(gp->item[EDIT_WS_MSEC].hwnd, "1000");
  ResetText(gp->item[EDIT_SERIAL_MSEC].hwnd, "1000");

  ResetText(gp->item[EDIT_LIST_COUNT].hwnd, "2000");

  SendMessage(gp->item[COMBO_NET_PROTOCOL].hwnd, CB_ADDSTRING, 0, (LPARAM)"TCP");
  SendMessage(gp->item[COMBO_NET_PROTOCOL].hwnd, CB_ADDSTRING, 0, (LPARAM)"UDP");
  SendMessage(gp->item[COMBO_NET_PROTOCOL].hwnd, CB_SETCURSEL, 0, 0 );

  SendMessage(gp->item[COMBO_NET_CS].hwnd, CB_ADDSTRING, 0, (LPARAM)"SERVER");
  SendMessage(gp->item[COMBO_NET_CS].hwnd, CB_ADDSTRING, 0, (LPARAM)"CLIENT");
  SendMessage(gp->item[COMBO_NET_CS].hwnd, CB_SETCURSEL, 0, 0 );

  SendMessage(gp->item[COMBO_WS_CS].hwnd, CB_ADDSTRING, 0, (LPARAM)"SERVER");
  SendMessage(gp->item[COMBO_WS_CS].hwnd, CB_ADDSTRING, 0, (LPARAM)"CLIENT");
  SendMessage(gp->item[COMBO_WS_CS].hwnd, CB_SETCURSEL, 0, 0 );

  SendMessage(gp->item[COMBO_NET_CASTTYPE].hwnd, CB_ADDSTRING, 0, (LPARAM)"UNICAST");
  SendMessage(gp->item[COMBO_NET_CASTTYPE].hwnd, CB_ADDSTRING, 0, (LPARAM)"BROADCAST");
  SendMessage(gp->item[COMBO_NET_CASTTYPE].hwnd, CB_ADDSTRING, 0, (LPARAM)"MULTICAST");
  SendMessage(gp->item[COMBO_NET_CASTTYPE].hwnd, CB_SETCURSEL, 0, 0 );

	SendMessage(gp->item[COMBO_NET_DISPLAY_TYPE_W].hwnd, CB_ADDSTRING, 0, (LPARAM)"ASCII");
	SendMessage(gp->item[COMBO_NET_DISPLAY_TYPE_W].hwnd, CB_ADDSTRING, 0, (LPARAM)"HEX");
  SendMessage(gp->item[COMBO_NET_DISPLAY_TYPE_W].hwnd, CB_SETCURSEL, 0, 0 );

	SendMessage(gp->item[COMBO_NET_DISPLAY_TYPE_R].hwnd, CB_ADDSTRING, 0, (LPARAM)"ASCII");
	SendMessage(gp->item[COMBO_NET_DISPLAY_TYPE_R].hwnd, CB_ADDSTRING, 0, (LPARAM)"HEX");
  SendMessage(gp->item[COMBO_NET_DISPLAY_TYPE_R].hwnd, CB_SETCURSEL, 0, 0 );

	SendMessage(gp->item[COMBO_WS_DISPLAY_TYPE_W].hwnd, CB_ADDSTRING, 0, (LPARAM)"ASCII");
	SendMessage(gp->item[COMBO_WS_DISPLAY_TYPE_W].hwnd, CB_ADDSTRING, 0, (LPARAM)"HEX");
  SendMessage(gp->item[COMBO_WS_DISPLAY_TYPE_W].hwnd, CB_SETCURSEL, 0, 0 );

	SendMessage(gp->item[COMBO_WS_DISPLAY_TYPE_R].hwnd, CB_ADDSTRING, 0, (LPARAM)"ASCII");
	SendMessage(gp->item[COMBO_WS_DISPLAY_TYPE_R].hwnd, CB_ADDSTRING, 0, (LPARAM)"HEX");
  SendMessage(gp->item[COMBO_WS_DISPLAY_TYPE_R].hwnd, CB_SETCURSEL, 0, 0 );

	SendMessage(gp->item[COMBO_SERIAL_DISPLAY_TYPE_W].hwnd, CB_ADDSTRING, 0, (LPARAM)"ASCII");
	SendMessage(gp->item[COMBO_SERIAL_DISPLAY_TYPE_W].hwnd, CB_ADDSTRING, 0, (LPARAM)"HEX");
  SendMessage(gp->item[COMBO_SERIAL_DISPLAY_TYPE_W].hwnd, CB_SETCURSEL, 0, 0 );

	SendMessage(gp->item[COMBO_SERIAL_DISPLAY_TYPE_R].hwnd, CB_ADDSTRING, 0, (LPARAM)"ASCII");
	SendMessage(gp->item[COMBO_SERIAL_DISPLAY_TYPE_R].hwnd, CB_ADDSTRING, 0, (LPARAM)"HEX");
  SendMessage(gp->item[COMBO_SERIAL_DISPLAY_TYPE_R].hwnd, CB_SETCURSEL, 0, 0 );

	SendMessage(gp->item[COMBO_SERIAL_DISPLAY_TYPE_W2].hwnd, CB_ADDSTRING, 0, (LPARAM)"ASCII");
	SendMessage(gp->item[COMBO_SERIAL_DISPLAY_TYPE_W2].hwnd, CB_ADDSTRING, 0, (LPARAM)"HEX");
  SendMessage(gp->item[COMBO_SERIAL_DISPLAY_TYPE_W2].hwnd, CB_SETCURSEL, 0, 0 );

	SendMessage(gp->item[COMBO_SERIAL_DISPLAY_TYPE_R2].hwnd, CB_ADDSTRING, 0, (LPARAM)"ASCII");
	SendMessage(gp->item[COMBO_SERIAL_DISPLAY_TYPE_R2].hwnd, CB_ADDSTRING, 0, (LPARAM)"HEX");
  SendMessage(gp->item[COMBO_SERIAL_DISPLAY_TYPE_R2].hwnd, CB_SETCURSEL, 0, 0 );


  InitListView(gp->item[LIST_READ].hwnd);

  return 0;
}

