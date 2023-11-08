#include "ihttpd.h"
//#include <network.h>
#include <nutil.h>


int32_t ihttpd(uint8_t* task, int32_t fd, int8_t* uri, int32_t (*f)(void*,int32_t,int8_t*,int32_t,void*,void*),void* o)
{
  int32_t e = 0xEFFFFFFF;

  if ( strcompare("/__network", task) == 0 )
  {
    e = nNetworkInfo(fd, task, uri, f, o);
  }

  return e;
}
