#include <__lsifr.h>
#if __LINUX__
#include <dlfcn.h>
#endif
#include <__util.h>

#define MODULE   "./liblite.sifr.usr.x64.so"

void print_status(cSIFR* p, int8_t* fx, int32_t e)
{
  int32_t lstatus[4] = {0};

  p->__sifr_last_status(p->h, lstatus);

  printf("| ******** ******** ******** ******** ******** |\r\n"
         "| %.45s |\r\n"
         "| ******** ******** ******** ******** ******** |\r\n"
         "| %16s(%08X) | %s(%08X) \r\n"
         "|                            | %s(%08X) \r\n"
         "|                            | %s(%08X) \r\n"
         "|                            | %s(%08X) \r\n"
         "| ******** ******** ******** ******** ******** |\r\n",
          fx, p->__sifr_last_status_string(e), e,
          p->__sifr_last_status_string(lstatus[0]), lstatus[0],
          p->__sifr_last_status_string(lstatus[1]), lstatus[1],
          p->__sifr_last_status_string(lstatus[2]), lstatus[2],
          p->__sifr_last_status_string(lstatus[3]), lstatus[3]
  );
}



void init_sifr(cSIFR* p)
{
  void* hdl = 0;
  int32_t e = 0;

  printf("%s %s\r\n", BASE_KEY, MODULE);  

  #if __LINUX__
  hdl = dlopen(MODULE, RTLD_NOW);
  if ( hdl == 0 )
  {
    printf("dlopen Fail %s\r\n", dlerror());
    return;
  }
  p->__sifr_initia             = dlsym(hdl,"__sifr_initia");
  p->__sifr_seed_ecb_encode    = dlsym(hdl,"__sifr_seed_ecb_encode");
  p->__sifr_seed_ecb_decode    = dlsym(hdl,"__sifr_seed_ecb_decode");
  p->__sifr_last_status        = dlsym(hdl,"__sifr_last_status");
  p->__sifr_last_status_string = dlsym(hdl,"__sifr_last_status_string");
  #endif
  DEBUG_PRINT(" >> %s\r\n", p->__sifr_initia==0?"NULL":"NOT NULL");
  DEBUG_PRINT(" >> %s\r\n", p->__sifr_seed_ecb_encode==0?"NULL":"NOT NULL");
  DEBUG_PRINT(" >> %s\r\n", p->__sifr_seed_ecb_decode==0?"NULL":"NOT NULL");
  DEBUG_PRINT(" >> %s\r\n", p->__sifr_last_status==0?"NULL":"NOT NULL");
  DEBUG_PRINT(" >> %s\r\n", p->__sifr_last_status_string==0?"NULL":"NOT NULL");

  e = p->__sifr_initia(&p->h, BASE_KEY, MODULE);
  print_status(p, "__sifr_init", e);
}


static const char SEED_ECB[][4][51200] =
{
  {
  "828E9E067BC2E9B306A3FA99426787AC",
  "21C7B0986CF8265708DD9202777B35E7",
  "82E1674DBEF09F6B73552C6329A1A9D9",
  },
};

void decode_pakcet(cSIFR* p, uint8_t* buf, int32_t sz)
{
  int32_t e = 0;
  int8_t  iobuf[2][4096] = {0};
  int8_t  obuf[2][4096] = {0};

  e = ascii_to_hex(SEED_ECB[0][0], iobuf[0]);

  display(iobuf[0], e, "key");

  DEBUG_PRINT(" >> %s\r\n", p->__sifr_initia==0?"NULL":"NOT NULL");
  DEBUG_PRINT(" >> %s\r\n", p->__sifr_seed_ecb_encode==0?"NULL":"NOT NULL");
  DEBUG_PRINT(" >> %s\r\n", p->__sifr_seed_ecb_decode==0?"NULL":"NOT NULL");
  DEBUG_PRINT(" >> %s\r\n", p->__sifr_last_status==0?"NULL":"NOT NULL");
  DEBUG_PRINT(" >> %s\r\n", p->__sifr_last_status_string==0?"NULL":"NOT NULL");

  DEBUG_PRINT("%s\r\n", p->__sifr_seed_ecb_decode==0?"NULL":"NOT NULL");

  display(buf, sz, "READ");

  e = p->__sifr_seed_ecb_decode(p->h, iobuf[0], e, 0, 0, buf, sz, obuf[0], 4096, 0, 0);


  display(obuf[0], e, "SEED ECB DECODE");

}

void decode_pakcet1(cSIFR* p, uint8_t* buf, int32_t sz)
{
  int32_t e = 0;
  uint8_t key[32] = {0};
  uint8_t obuf[1024] = {0};

  sprintf(key, "SEEDKEY_least16B");

  DEBUG_PRINT(" BLOCK KEY : %s \r\n", key);

  e = p->__sifr_seed_ecb_decode(p->h, key, 16, 0, 0, buf, sz, obuf, 1024, 0, 0);

  DEBUG_PRINT(" PLAIN TEXT : %s \r\n", obuf);

}