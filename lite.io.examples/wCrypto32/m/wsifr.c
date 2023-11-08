#include "resource.h"
#include "wsifr.h"

#include <ntcp.h>


void* fx_IDC_BUTTON_SIFR_INIT(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  return 0;
}


void* wsifrDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  switch(LOWORD(wparam))
  {
    case IDC_BUTTON_SIFR_INIT:
      fx_IDC_BUTTON_SIFR_INIT(hwnd, msg, wparam, lparam);
      break;
  }
  return 0;
}


void* wsifrInit(HWND hwnd, wsifr* p)
{
  int32_t e;
  void* hmod;

  p->item[BUTTON_SIFR_INIT].hwnd = GetDlgItem(hwnd, IDC_BUTTON_SIFR_INIT);

  return 0;
}
