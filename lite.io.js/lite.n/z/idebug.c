#include <idebug.h>
#include <liteio.h>

static uint8_t gDEBUG = 1;


void __debug(int32_t dflg)
{
  gDEBUG = dflg;
}


void debug_print(const char* fn, int ln, const char* fmt, ...)
{
	va_list args;

  if ( !gDEBUG ) return;

  printf(" %16s:%6d | ", fn, ln );
  va_start (args, fmt);
  vfprintf(stdout,fmt, args);
  fflush(stdout);
  va_end(args);
}

void debug_buffer(const char* fn, int ln, uint8_t* b, int32_t sz)
{
	va_list args;
  uint8_t title[512] = {0};
  if ( !gDEBUG ) return;

  sprintf(title, " %16s:%6d", fn, ln);
  print_buffer(title, b, sz);
}

