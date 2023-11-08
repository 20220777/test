#include <CodeX.h>
#include <ICodeX.h>
#include <protocol_shof.h>
#include <protocol_jmt.h>


void* codeXStatusSerial(void* h, void* msg, void* wparam, void* lparam)
{
	CodeX* p = (CodeX*)h;
	static uint32_t bpos = 0;
	int8_t tmp[128];

	switch( LOWORD((uint32_t)msg) )
	{
	case READ:
		on_protocol_proc(jmt_protocol_info, (int8_t*)wparam, (int32_t)lparam, p->buf, &bpos, on_jmt_protocol_check, h);
		break;
	}

	return 0;
}


void* codeXStatusSocket(void* h, void* msg, void* wparam, void* lparam)
{
	CodeX* p = (CodeX*)h;
	static uint32_t bpos = 0;

	switch( LOWORD((uint32_t)msg) )
	{
	case READ:
		on_protocol_proc(shof_protocol_info, (int8_t*)wparam, (int32_t)lparam, p->buf, &bpos, on_shof_protocol_check, h);
		break;

	}

	return 0;
}

void* codeXStatusWebSocket(void* h, void* msg, void* wparam, void* lparam)
{
	CodeX* p = (CodeX*)h;
	switch( LOWORD((uint32_t)msg) )
	{
	case READ:
		break;
	}
	return 0;
}

void* codeXStatus(void* h, void* msg, void* wparam, void* lparam)
{
	CodeX* p = (CodeX*)h;
	switch( HIWORD((uint32_t)msg) )
	{
	case XSERIAL:
		codeXStatusSerial(h,msg,wparam,lparam);
		break;
	case XSOCKET:
		codeXStatusSocket(h,msg,wparam,lparam);
		break;
	case XWEBSOCKET:
		codeXStatusWebSocket(h,msg,wparam,lparam);
		break;
	}

  //p->callback(p->obj, msg, wparam, lparam);

	return 0;
}



void* loadInterface(void* hdl)
{
  if ( hdl == 0 )	hdl = LoadLibrary(MODULE);

  *(FARPROC*)&get_hex_semaphore        = GetProcAddress(hdl,"get_hex_semaphore");
  *(FARPROC*)&set_hex_semaphore        = GetProcAddress(hdl,"set_hex_semaphore");
  *(FARPROC*)&check_hex_semaphore      = GetProcAddress(hdl,"check_hex_semaphore");
  *(FARPROC*)&thread_create            = GetProcAddress(hdl,"thread_create");
  *(FARPROC*)&thread_exit              = GetProcAddress(hdl,"thread_exit");
  *(FARPROC*)&get_curr_time            = GetProcAddress(hdl,"get_curr_time");
	*(FARPROC*)&log_write_ex             = GetProcAddress(hdl,"log_write_ex");

  return hdl;  
}





void* codeXmain(void* hdl, CodeX* p)
{
  int32_t e = 0;
  uint32_t tid;

  if ( hdl == 0 )	hdl = LoadLibrary(MODULE);

  //*(FARPROC*)&p->codeXRun          = GetProcAddress(hdl,"codeXRun");
  //*(FARPROC*)&p->codeXStop         = GetProcAddress(hdl,"codeXStop");
  *(FARPROC*)&p->getMessage        = GetProcAddress(hdl,"codeXGetMessage");
  *(FARPROC*)&p->setMessage        = GetProcAddress(hdl,"codeXSetMessage");
  *(FARPROC*)&p->putMessage        = GetProcAddress(hdl,"codeXPutMessage");

	//p->codeXRun(&p->h, codeXStatus, p);
	p->setMessage(&p->h, (void*)MAKELONG(INIT, CODEX), codeXStatus, p);


  #if 1
	#if USE_XSOCKET
	p->setMessage(p->h, (void*)MAKELONG(XM_DELAY_0 , XSOCKET),   (void*)"3000",                 (void*)strlen("3000"));
	p->setMessage(p->h, (void*)MAKELONG(XM_IP      , XSOCKET),   (void*)"127.0.0.1",            (void*)strlen("127.0.0.1"));
	p->setMessage(p->h, (void*)MAKELONG(XM_PORT    , XSOCKET),   (void*)"7870",                 (void*)strlen("7870"));
	p->setMessage(p->h, (void*)MAKELONG(XM_PROTO   , XSOCKET),   (void*)"TCP",                  (void*)strlen("TCP"));
	p->setMessage(p->h, (void*)MAKELONG(XM_CSTYPE  , XSOCKET),   (void*)"SERVER",               (void*)strlen("SERVER"));
	p->setMessage(p->h, (void*)MAKELONG(XM_CASTTYPE, XSOCKET),   (void*)"UNICAST",              (void*)strlen("UNICAST"));
	p->setMessage(p->h, (void*)MAKELONG(XM_ECHOMODE, XSOCKET),   (void*)"0",                    (void*)strlen("0"));
	p->setMessage(p->h, (void*)MAKELONG(XM_SECRET     , XSOCKET),   (void*)"shinbaad@gmail.com",   (void*)strlen("shinbaad@gmail.com"));
	p->setMessage(p->h, (void*)MAKELONG(ENABLE     , XSOCKET),  0, 0);
	#endif


	#if USE_XWEBSOCKET
	p->setMessage(p->h, (void*)MAKELONG(XM_DELAY_0 , XWEBSOCKET),   (void*)"3000",                 (void*)strlen("3000"));
	p->setMessage(p->h, (void*)MAKELONG(XM_IP      , XWEBSOCKET),   (void*)"127.0.0.1",            (void*)strlen("127.0.0.1"));
	p->setMessage(p->h, (void*)MAKELONG(XM_PORT    , XWEBSOCKET),   (void*)"7810",                 (void*)strlen("7810"));
	p->setMessage(p->h, (void*)MAKELONG(XM_CSTYPE  , XWEBSOCKET),   (void*)"SERVER",               (void*)strlen("SERVER"));
	p->setMessage(p->h, (void*)MAKELONG(XM_ECHOMODE, XWEBSOCKET),   (void*)"0",                    (void*)strlen("0"));
	p->setMessage(p->h, (void*)MAKELONG(XM_SECRET     , XWEBSOCKET),   (void*)"shinbaad@gmail.com",   (void*)strlen("shinbaad@gmail.com"));
	p->setMessage(p->h, (void*)MAKELONG(ENABLE     , XWEBSOCKET), 0, 0);
	#endif


	#if USE_XHTTPD
	p->setMessage(p->h, (void*)MAKELONG(XM_DELAY_0, XHTTPD),   (void*)"3000",                 (void*)strlen("3000"));
	p->setMessage(p->h, (void*)MAKELONG(XM_IP     , XHTTPD),   (void*)"127.0.0.1",            (void*)strlen("127.0.0.1"));
	p->setMessage(p->h, (void*)MAKELONG(XM_PORT   , XHTTPD),   (void*)"80",                   (void*)strlen("80"));
	p->setMessage(p->h, (void*)MAKELONG(XM_HOME   , XHTTPD),   (void*)"/usr/local/www",       (void*)strlen("/usr/local/www"));
	p->setMessage(p->h, (void*)MAKELONG(XM_INDEX  , XHTTPD),   (void*)"index.html",           (void*)strlen("index.html"));
	p->setMessage(p->h, (void*)MAKELONG(XM_SECRET    , XHTTPD),   (void*)"shinbaad@gmail.com",   (void*)strlen("shinbaad@gmail.com"));
	p->setMessage(p->h, (void*)MAKELONG(XHTTPD    , ENABLE), 0, 0);
	#endif

//<CONFIG system="SERIAL" enable="0" port="/dev/ttyS0" baudrate="115200" databit="8" stopbit="1" paritybit="0" blockmode="0" echomode="1" delay="3000" />

	#if USE_XSERIAL
	p->setMessage(p->h, (void*)MAKELONG(XM_DELAY_0  , XSERIAL),   (void*)"3000",                 (void*)strlen("3000"));
	//p->setMessage(p->h, (void*)MAKELONG(XM_PORT     , XSERIAL),   (void*)"COM11",                (void*)strlen("COM11"));
	p->setMessage(p->h, (void*)MAKELONG(XM_BAUDRATE , XSERIAL),   (void*)"9600",                 (void*)strlen("9600"));
	p->setMessage(p->h, (void*)MAKELONG(XM_DATABIT  , XSERIAL),   (void*)"8",                    (void*)strlen("8"));
	p->setMessage(p->h, (void*)MAKELONG(XM_STOPBIT  , XSERIAL),   (void*)"1",                    (void*)strlen("1"));
	p->setMessage(p->h, (void*)MAKELONG(XM_PARITYBIT, XSERIAL),   (void*)"0",                    (void*)strlen("0"));
	//p->setMessage(p->h, (void*)MAKELONG(XM_SECRET      , XSERIAL),   (void*)"shinbaad@gmail.com",   (void*)strlen("shinbaad@gmail.com"));
	//p->setMessage(p->h, (void*)MAKELONG(ENABLE      , XSERIAL), 0, 0);
	#endif

  #endif

  return hdl;
}



void* codeXend(CodeX* p)
{
	#if USE_XSOCKET
	p->putMessage(p->h, (void*)MAKELONG(DISABLE     , XSOCKET),  0,0);
	#endif

	#if USE_XWEBSOCKET
	p->putMessage(p->h, (void*)MAKELONG(DISABLE     , XWEBSOCKET), 0, 0);
	#endif

	#if USE_XHTTPD
	p->putMessage(p->h, (void*)MAKELONG(DISABLE     , XHTTPD), 0, 0);
	#endif

	#if USE_XSERIAL
	p->putMessage(p->h, (void*)MAKELONG(DISABLE     , XSERIAL), 0, 0);
	#endif

	return p->setMessage(&p->h, (void*)MAKELONG(RELEASE, CODEX), 0, 0 );
}
