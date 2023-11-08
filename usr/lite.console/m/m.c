#include <__ua.h>
#include <__lsifr.h>

void main(int argc, char** argv)
{
  void* hdl = 0;

  uint32_t slp = 4000000;

  cLite* p = (cLite*)calloc(1, sizeof(cLite));


  #if __TITLE__
  BOX("SolWith lite.console");
  #endif

  
  xLOCK_INIT(&p->__ioq.crit);

  setStatus(p, INIT);
  setStatus(p, READY);
  setStatus(p, SOCKET_OPEN);
  //setStatus(SERIAL_OPEN);

  init_sifr(&p->__sfr);
  DEBUG_PRINT(" >> %s\r\n", p->__sfr.__sifr_initia==0?"NULL":"NOT NULL");
  DEBUG_PRINT(" >> %s\r\n", p->__sfr.__sifr_seed_ecb_encode==0?"NULL":"NOT NULL");
  DEBUG_PRINT(" >> %s\r\n", p->__sfr.__sifr_seed_ecb_decode==0?"NULL":"NOT NULL");
  DEBUG_PRINT(" >> %s\r\n", p->__sfr.__sifr_last_status==0?"NULL":"NOT NULL");
  DEBUG_PRINT(" >> %s\r\n", p->__sfr.__sifr_last_status_string==0?"NULL":"NOT NULL");

  while ( 1 )
  {
    state(p);
    __mcsleep(1);
  }

}

