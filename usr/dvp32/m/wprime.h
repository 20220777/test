#ifndef __WPRIME_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __WPRIME_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include "mcommon.h"
#include "wcommon.h"
#include <xmath.h>
#define COPRIME_RANGE   2048

enum
{
  EDIT_PRIME_BEGIN,
  EDIT_PRIME_END,
  BUTTON_FIND,
  COMBO_PRIME_SET,
  BUTTON_SELECT,
  EDIT_PRIMES,
  BUTTON_RESET,
  EDIT_GCM,
  EDIT_LCD,
  EDIT_COMPOSITE,
  BUTTON_PRIME_FACTORS,
  EDIT_PRIME_FACTORS,
  BUTTON_GCM_LCD,
  EDIT_COMMON_DIVISORS,
  BUTTON_COMMON_DIVISOR,
  COMBO_COMPOSITE_FACTOR,
  BUTTON_DIVISOR,
  EDIT_DIVISORS,
  EDIT_RSA_PRIMES,
  EDIT_RSA_EULER_N,
  EDIT_RSA_EULER_N_HEX,
  BUTTON_RSA_EULER_N,
  BUTTON_RSA_E,
  COMBO_RSA_E,
  EDIT_RSA_N,
  EDIT_RSA_N_HEX,
  EDIT_RSA_E,
  EDIT_RSA_D,
  EDIT_RSA_D_ORG,
  EDIT_RSA_PUBKEY,
  EDIT_RSA_PRIKEY,
  BUTTON_RSA_KEY,
  EDIT_RSA_CLEAR_TEXT,
  EDIT_RSA_ENCODE,
  EDIT_RSA_DECODE,
  BUTTON_RSA_ENCODE,
  BUTTON_RSA_DECODE,
  MAX_CRYPTO_ITEM
};


#if (defined XWIN32 || defined WINCE)
#pragma pack(1)
#endif
typedef struct xRSA
{
  long long key[2][128];
  unsigned long long primes[128];
  unsigned long long composite;
  unsigned long long euler_N;
  unsigned long long N;
  unsigned long long E;
  unsigned long long D;
}xRSA;
#if (defined XWIN32 || defined WINCE)
#pragma pack()
#endif


#if (defined XWIN32 || defined WINCE)
#pragma pack(1)
#endif
typedef struct
{
  MTIF*              pm;
  wLog        log;
  HWND        hitem[MAX_CRYPTO_ITEM];
  xRSA        rsa;
}wPrime;
#if (defined XWIN32 || defined WINCE)
#pragma pack()
#endif

void* wprime_dlgproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
void* wprime_init(HWND hwnd, wPrime* p);


#endif

