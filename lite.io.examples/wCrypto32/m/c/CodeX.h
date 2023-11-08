#ifndef __CODEX_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __CODEX_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <stdio.h>
#include <stdint.h>
#include <Windows.h>

#include <ICodeX.h>
#include <code.x.h>

#include <util.h>
#include <mprotocol.h>
#include <protocol_shof.h>


#define USE_XSOCKET         0
#define USE_XWEBSOCKET      0
#define USE_XHTTPD          0
#define USE_XSERIAL         0

#define CODEX_MODULE     "code.X.sifr.x86.dll"
#define delay(msec)    Sleep(msec)

#if defined XWIN32
#pragma pack(1)
#endif
typedef struct
#if defined LINUX
__attribute__((packed))
#endif
{
  int32_t   a[4];  // fd sz  bp  fdp
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

	void* h;

  int8_t  buf[4096];
  int32_t idx;

  int32_t (*putMessage)(void* h, void* m, void* w, void* l);
  int32_t (*setMessage)(void* h, void* m, void* w, void* l);
  int32_t (*getMessage)(void* h, void* m, void* w, void* l);

  void* (*callback)(void*,void*,void*,void*);
  void*  obj;

  CodeXModule modul[MAX_MODULES];

  int32_t  _sckfd;
  int32_t  _wsckfd;
  int32_t  _srlfd[2];

  void*    _sck;
  void*    _wsck;
  void*    _srl[2];

  uint32_t  sck_buf[1024];
  uint32_t  wsck_buf[1024];
  uint32_t  srl_buf[2][1024];
}CodeX;
#if (defined XWIN32 || defined WINCE)
#pragma pack()
#endif


void* loadInterface(void* hdl);
void* codeXmain(void* hdl, CodeX* p);
void* codeXend(CodeX* p);


#endif

