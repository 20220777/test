#ifndef __CODEX_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __CODEX_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <stdio.h>
#include <stdint.h>
#include <Windows.h>

#include <code.x.h>

#include <util.h>
#include <mprotocol.h>



#define USE_XSOCKET         0
#define USE_XWEBSOCKET      0
#define USE_XHTTPD          0
#define USE_XSERIAL         1



#define MODULE     "code.X.x86.dll"
#define delay(msec)    Sleep(msec)

#if defined XWIN32
#pragma pack(1)
#endif
typedef struct
#if defined LINUX
__attribute__((packed))
#endif
{
  int   a[4];  // fd sz  bp  fdp
} CodeXfdset;
#if defined XWIN32
#pragma pack()
#endif


#if defined XWIN32
#pragma pack(1)
#endif
typedef struct
#if defined LINUX
__attribute__((packed))
#endif
{
  CodeXfdset*  fdset;
} CodeXModule;
#if defined XWIN32
#pragma pack()
#endif


#if (defined XWIN32 || defined WINCE)
#pragma pack(1)
#endif
typedef struct
{
  uint32_t   SR;

	void* hdl;
	void* h;

  int8_t  buf[4096];
  int32_t idx;

  int32_t (*codeXRun)(void** h, void* (*f)(void*,void*,void*,void*), void*);
  int32_t (*codeXStop)(void** h);
  int32_t (*putMessage)(void* h, void* m, void* w, void* l);
  int32_t (*setMessage)(void* h, void* m, void* w, void* l);
  int32_t (*getMessage)(void* h, void* m, void* w, void* l);

  void* (*callback)(void*,void*,void*,void*);
  void*  obj;

  CodeXModule modul[MAX_MODULES-XMODULES];
}CodeX;
#if (defined XWIN32 || defined WINCE)
#pragma pack()
#endif


void* loadInterface(void* hdl);
void* codeXmain(void* hdl, CodeX* p);
void* codeXend(CodeX* p);


#endif

