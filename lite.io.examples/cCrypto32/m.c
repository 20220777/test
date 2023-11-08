#if defined WIN32
#include <Windows.h>
#endif
#include <stdio.h>
#include <stdint.h>
#include <kisa_key.h>
#include <__util.h>

#include <io.x.h>
#include <xcommon.h>

#include <sha3.h>

#if defined WIN32
#define MODULE    "sifr.kit.dll"
#endif

#if defined LINUX
#define MODULE    "sifr.kit.so"
#endif

#if defined WIN32
#pragma pack(1)
#endif
typedef struct
#if defined LINUX
__attribute__((packed))
#endif
{
  uint8_t* p;
  int32_t  sz;
  int32_t (*__sifr_init)(void**,int8_t*,int32_t);
  int32_t (*__sifr_release)(void**);
  int32_t (*__sifr_last_status)(void*,int32_t*,int32_t*);
  int8_t*  (*__sifr_last_status_string)(int32_t*);
  int32_t (*__sifr_version)(void**,int8_t*,int32_t);
  int32_t (*__sifr_author)(void**,int8_t*,int32_t);
  int32_t (*__sifr_module)(void**,int8_t*,int32_t);

  int32_t (*__sifr_integrity_check)(void* h,int8_t*,int32_t);
  int32_t (*__sifr_kat_check)(void* h);
  int32_t (*__sifr_self_check)(void* h,int8_t*,int32_t);

  int32_t (*__sifr_set_callback)(void* h, void* callback, void* o);
  int32_t (*__sifr_base64)(void* h, uint8_t* in, int32_t isz, uint8_t mode, uint8_t* out);


  int32_t (*__sifr_mem_clear)(void* h,int8_t*,int32_t);


  int32_t (*__sifr_noise_source)(uint8_t who, uint8_t* o, int32_t s);

  int32_t (*__sifr_entropy)(void* h, uint32_t who, uint8_t* o, int32_t sz);
  int32_t (*__sifr_drbg)(void* h, uint8_t mode, uint8_t df, uint8_t* b, int32_t sz);
  int32_t (*__sifr_random)(void* h, uint8_t* b, int32_t sz);
  int32_t (*__sifr_key)(void* h, uint8_t* b, int32_t sz);
  //int32_t (*__sifr_drbg)(void* h, uint8_t mode, uint8_t df, uint8_t* str0, int32_t ssz0, uint8_t* str1, int32_t ssz1, uint8_t* out, int32_t osz);

  int32_t (*__sifr_aria_ecb_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_aria_ecb_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_aria_cbc_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_aria_cbc_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_aria_cfb_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_aria_cfb_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_aria_ofb_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_aria_ofb_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_aria_ctr_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_aria_ctr_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_aria_ccm_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_aria_ccm_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);

  int32_t (*__sifr_lea_ecb_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_lea_ecb_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_lea_cbc_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_lea_cbc_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_lea_cfb_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_lea_cfb_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_lea_ofb_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_lea_ofb_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_lea_ctr_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_lea_ctr_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);

  int32_t (*__sifr_seed_ecb_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_seed_ecb_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_seed_cbc_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_seed_cbc_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_seed_cfb_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_seed_cfb_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_seed_ofb_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_seed_ofb_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_seed_ctr_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_seed_ctr_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);

  int32_t (*__sifr_hight_ecb_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_hight_ecb_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_hight_cbc_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_hight_cbc_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_hight_cfb_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_hight_cfb_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_hight_ofb_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_hight_ofb_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_hight_ctr_encode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_hight_ctr_decode)(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);

  int32_t (*__sifr_sha2)(void* h, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_hmac)(void* h, uint8_t* key, int32_t ksz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);

  int32_t (*__sifr_lsh256_224)(void* h, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_lsh256_256)(void* h, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_lsh512_224)(void* h, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_lsh512_256)(void* h, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_lsh512_384)(void* h, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);
  int32_t (*__sifr_lsh512_512)(void* h, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);

  int32_t (*setMessage)(void* h, void* m, void* w, void* l);
  int32_t (*putMessage)(void* h, void* m, void* w, void* l);



} cCrypto32;
#if defined WIN32
#pragma pack()
#endif

cCrypto32   _crpt;

int32_t loadBinary(int8_t* fname, uint8_t** p)
{
  FILE* fp = 0;
  int32_t sz = 0;

  fp = fopen(fname, "rb");
  fseek(fp, 0, SEEK_SET);
  fseek(fp, 0, SEEK_END);
  sz = ftell(fp);

  *p = (uint8_t*)calloc(sz, sizeof(uint8_t));
  fseek(fp, 0, SEEK_SET);
  fread(*p, sizeof(uint8_t), sz, fp);

  if(fp) fclose(fp);

  return sz;
}

void* sifrkit_callback(void* h, void* m, void* w, void* l)
{
  display((int8_t*)w, (int32_t)l, "sifrkit_callback"); 

  //switch( LOWORD((uint32_t)m) )
  //{
  //case ECB_ENCODE:
  //case CBC_ENCODE:
  //case CFB_ENCODE:
  //case OFB_ENCODE:
  //case CTR_ENCODE:
  //case CCM_ENCODE:
  //case GCM_ENCODE:
  //  memcpy(&gbuf[0][gidx[0]], (int8_t*)wparam, (int32_t)lparam*sizeof(int8_t));
  //  gidx[0]+=(int32_t)lparam;
  //  break;

  //case ECB_DECODE:
  //case CBC_DECODE:
  //case CFB_DECODE:
  //case OFB_DECODE:
  //case CTR_DECODE:
  //case CCM_DECODE:
  //case GCM_DECODE:
  //  memcpy(&gbuf[1][gidx[1]], (int8_t*)wparam, (int32_t)lparam*sizeof(int8_t));
  //  gidx[1]+=(int32_t)lparam;
  //  break;


  //case CMAC:
  //  memcpy(&gbuf[0][gidx[0]], (int8_t*)wparam, (int32_t)lparam*sizeof(int8_t));
  //  gidx[0]+=(int32_t)lparam;
  //  break;





  return 0;
}


void* sifr_base64_callback(void* h, void* m, void* w, void* l)
{
  display((int8_t*)w, (int32_t)l, "sifr_base64_callback"); 

  return 0;
}


void* sifr_aria_callback(void* h, void* m, void* w, void* l)
{
  display((int8_t*)w, (int32_t)l, "sifr_aria_callback"); 

  return 0;
}

void* sifr_lea_callback(void* h, void* m, void* w, void* l)
{
  display((int8_t*)w, (int32_t)l, "sifr_lea_callback"); 

  return 0;
}

void* sifr_seed_callback(void* h, void* m, void* w, void* l)
{
  display((int8_t*)w, (int32_t)l, "sifr_seed_callback"); 

  return 0;
}

void* sifr_hight_callback(void* h, void* m, void* w, void* l)
{
  display((int8_t*)w, (int32_t)l, "sifr_hight_callback"); 

  return 0;
}

void* sifr_sha2_callback(void* h, void* m, void* w, void* l)
{
  display((int8_t*)w, (int32_t)l, "sifr_sha2_callback"); 

  return 0;
}

void* sifr_hmac_callback(void* h, void* m, void* w, void* l)
{
  display((int8_t*)w, (int32_t)l, "sifr_hmac_callback"); 

  return 0;
}

void* sifr_lsh256_callback(void* h, void* m, void* w, void* l)
{
  display((int8_t*)w, (int32_t)l, "sifr_lsh256_callback"); 

  return 0;
}

void* sifr_lsh512_callback(void* h, void* m, void* w, void* l)
{
  display((int8_t*)w, (int32_t)l, "sifr_lsh512_callback"); 

  return 0;
}


double get_freq(void* c)
{
  #if LINUX
  clock_gettime(CLOCK_REALTIME, (struct timespec*)c);
  return ((struct timespec*)c)->tv_nsec;
  //return (double)(((struct timespec*)c)->tv_sec + ((((struct timespec*)c)->tv_nsec)/1000000000.0));
  //return 0;
  #endif

  #if WIN32
  QueryPerformanceCounter((LARGE_INTEGER*)c);
  return (long double)((LARGE_INTEGER*)c)->QuadPart;
  #endif
}

long double check_freq(void* begin, void* end)
{
  #if LINUX
  return ((struct timespec*)end)->tv_nsec - ((struct timespec*)begin)->tv_nsec;
  #endif

  #if WIN32
  LARGE_INTEGER freq;
  QueryPerformanceFrequency(&freq);
  return (( (long double)((((LARGE_INTEGER*)end)->QuadPart)-(((LARGE_INTEGER*)begin)->QuadPart)))/(long double)freq.QuadPart)*1000000.0f;
  #endif
}



void sifrkit_VNV(int argc, char** argv)
{
  int32_t e = 0;
  void* h = 0;
  int8_t  iobuf[8][4096] = {0};
  int8_t  obuf[8][4096] = {0};
  int32_t sz[8] = {0};
  int32_t lstatus[2] = {0};
  int8_t  version[1024] = {0};
  int8_t  author[1024] = {0};
  int8_t  module_name[1024] = {0};

  #if LINUX
  struct timespec __start, __end, __chck;
  #endif

  #if WIN32
  LARGE_INTEGER __start, __end, __chck;
  #endif
  float __elapsed;

  e = _crpt.__sifr_init(&h, _crpt.p, _crpt.sz);
  printf(" __sifr_init : %08X \r\n", e);

  //e = _crpt.__sifr_self_check(h, _crpt.p, _crpt.sz );
  //printf(" __sifr_self_check : %08X \r\n", e);

  //e = _crpt.__sifr_kat_check(h);
  //printf(" __sifr_kat_check : %08X \r\n", e);


  e = _crpt.__sifr_last_status(h, &lstatus[0], &lstatus[1]);
  printf(" last status : %s(%08X) -> %s(%08X) \r\n", _crpt.__sifr_last_status_string(lstatus[0]), lstatus[0], _crpt.__sifr_last_status_string(lstatus[1]), lstatus[1]);


  e = _crpt.__sifr_set_callback(h, sifrkit_callback, &_crpt);
  printf(" __sifr_set_callback \r\n");

  e = _crpt.__sifr_last_status(h, &lstatus[0], &lstatus[1]);
  printf(" last status : %s(%08X) -> %s(%08X) \r\n", _crpt.__sifr_last_status_string(lstatus[0]), lstatus[0], _crpt.__sifr_last_status_string(lstatus[1]), lstatus[1]);

  e = _crpt.__sifr_module(h, module_name, 1024);
  printf(" module name : %s \r\n", module_name);

  e = _crpt.__sifr_last_status(h, &lstatus[0], &lstatus[1]);
  printf(" last status : %s(%08X) -> %s(%08X) \r\n", _crpt.__sifr_last_status_string(lstatus[0]), lstatus[0], _crpt.__sifr_last_status_string(lstatus[1]), lstatus[1]);

  e = _crpt.__sifr_version(h, version, 1024);
  printf(" version     : %s \r\n", version);

  e = _crpt.__sifr_last_status(h, &lstatus[0], &lstatus[1]);
  printf(" last status : %s(%08X) -> %s(%08X) \r\n", _crpt.__sifr_last_status_string(lstatus[0]), lstatus[0], _crpt.__sifr_last_status_string(lstatus[1]), lstatus[1]);

  e = _crpt.__sifr_author(h, author, 1024);
  printf(" author      : %s \r\n", author);

  e = _crpt.__sifr_last_status(h, &lstatus[0], &lstatus[1]);
  printf(" last status : %s(%08X) -> %s(%08X) \r\n", _crpt.__sifr_last_status_string(lstatus[0]), lstatus[0], _crpt.__sifr_last_status_string(lstatus[1]), lstatus[1]);

  //e = _crpt.__sifr_kat_check(h, "./testvector");



  #if 1 //__SEED__

  sz[0] = ascii_to_hex( KISA_KEY_SEED_ECB[1][0], iobuf[0]);
  sz[1] = ascii_to_hex( KISA_KEY_SEED_ECB[1][1], iobuf[1]);
  sz[2] = ascii_to_hex( KISA_KEY_SEED_ECB[1][2], iobuf[2]);

  display(iobuf[0], sz[0], "SEED KEY-----");
  display(iobuf[1], sz[1], "PLAIN TEXT---");
  display(iobuf[2], sz[2], "CIPHER TEXT----");

  get_freq(&__start);
  e = _crpt.__sifr_seed_ecb_encode(h, iobuf[0], sz[0], iobuf[1], sz[1], obuf[0], 4096, sifr_seed_callback, &_crpt);
  get_freq(&__end);
  __elapsed = (float)check_freq(&__start, &__end);
  printf("----->encoding elapsed time : %010.4f us\r\n", __elapsed / 1000);

	printf(" givet \r\n");
  display(obuf[0], e, "SEED ECB ENCODE");

  get_freq(&__start);
  e = _crpt.__sifr_seed_ecb_decode(h, iobuf[0], sz[0], obuf[0], e, obuf[1], 4096, sifr_seed_callback, &_crpt);
  get_freq(&__end);
  __elapsed = (float)check_freq(&__start, &__end);
  printf("------>decoding elapsed time : %010.4f us\r\n", __elapsed / 1000);

	printf(" givet \r\n");
  display(obuf[1], e, "SEED ECB DECODE");




  #endif




  e = _crpt.__sifr_release(&h);
  printf(" e : %08X \r\n", e);

}






//
//
//
//#define __LINUX__ 1
//
//
//int32_t __get_noiz2(uint32_t who)
//{
//  uint32_t o = 0;
//  if (who == 1 )
//  {
//    #if __LINUX__
//    int32_t fd = 0;
//    int32_t i = 0;
//    if ( (fd = open("/dev/urandom", O_RDONLY)) < 0 ) return 0xEFFFFFFF;
//    if ( read(fd, &o, sizeof(uint32_t)) < 0 ) return 0xEFFFFFFF;
//    close(fd);
//    #endif
//
//    #if __WIN32__
//    GUID guid = {0};
//    CoCreateGuid(&guid);
//    o = guid.Data1;
//    #endif
//  }
//  else
//  if ( who == 2 )
//  {
//    #if __LINUX__
//    struct timeval tv;
//    gettimeofday(&tv, 0);
//    o = (int32_t)(tv.tv_usec);
//    #endif
//
//    #if __WIN32__
//    SYSTEMTIME tv;
//    GetSystemTime( &tv );   
//    o = (int32_t)(tv.wMilliseconds);
//    #endif
//
//  }
//  else
//  {
//    #if __LINUX__
//    int32_t fd = 0;
//    int32_t i = 0;
//    if ( (fd = open("/dev/random", O_RDONLY)) < 0 ) return 0xEFFFFFFF;
//    if ( read(fd, &o, sizeof(uint32_t)) < 0 ) return 0xEFFFFFFF;
//    close(fd);
//    #endif
//
//    #if __WIN32__
//    void* hdl = 0;
//    if ( !CryptAcquireContext(&hdl, 0, 0, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT) ) return 0xEFFFFFFF;
//    if ( !CryptGenRandom(hdl, sizeof(uint32_t), &o) ) return 0xEFFFFFFF;
//    CryptReleaseContext(hdl, 0);
//    #endif
//  }
//  return o;
//}
//
//int32_t __get_noise2(uint8_t* o, int32_t sz_bit)
//{
//  int32_t i=0;
//  int32_t r = 0;
//
//  #if __WIN32__
//  for ( ;  ; )
//  {
//    r = __get_noiz2(0);
//    memcpy(o+i, &r, sizeof(int32_t));
//    i += sizeof(int32_t);
//    if ( i>= (sz_bit/8 + sz_bit%8) ) break;
//
//    r = __get_noiz2(1);
//    memcpy(o+i, &r, sizeof(int32_t));
//    i += sizeof(int32_t);
//    if ( i>= (sz_bit/8 + sz_bit%8) ) break;
//  }
//  #endif
//
//
//  #if __LINUX__
//
//  for ( ; ; )
//  {
//    r = __get_noiz2(0);
//    memcpy(o+i, &r, sizeof(int32_t));
//    i += sizeof(int32_t);
//    if ( i>= (sz_bit/8 + sz_bit%8) ) break;
//
//    r = __get_noiz2(3);
//    memcpy(o+i, &r, sizeof(int32_t));
//    i += sizeof(int32_t);
//    if ( i>= (sz_bit/8 + sz_bit%8) ) break;
//
//    //r = __get_noiz2(2);
//    //memcpy(o+i, &r, sizeof(int32_t));
//    //i += sizeof(int32_t);
//    //if ( i>= (sz_bit/8 + sz_bit%8) ) break;
//
//  }
//  #endif
//
//
//  return i*8;
//}
//
//
//

#if defined WIN32
#define __WIN32__ 1
#define __LINUX__ 0
#else
#define __WIN32__ 0
#define __LINUX__ 1
#endif

int32_t __chk_seed()
{
  return 0;

}


int32_t __chk_noiz(uint32_t who, uint8_t* o, int32_t s)
{
  if (who == 1 )
  {
    #if __LINUX__
    int32_t fd = 0;
    int32_t i = 0;
    if ( (fd = open("/dev/urandom", O_RDONLY)) < 0 ) return 0xEFFFFFFF;
    if ( read(fd, o, s/8) < 0 ) return 0xEFFFFFFF;
    close(fd);
    #endif

    #if __WIN32__
    CoCreateGuid((GUID*)o);
    #endif
  }
  else
  {
    #if __LINUX__
    int32_t fd = 0;
    int32_t i = 0;
    if ( (fd = open("/dev/random", O_RDONLY)) < 0 ) return 0xEFFFFFFF;
    if ( read(fd, o, s/8) < 0 ) return 0xEFFFFFFF;
    close(fd);
    #endif

    #if __WIN32__
    void* hdl = 0;
    if ( !CryptAcquireContext(&hdl, 0, 0, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT) ) return 0xEFFFFFFF;
    if ( !CryptGenRandom(hdl, s/8, o) ) return 0xEFFFFFFF;
    //if ( !CryptGenRandom(hdl, sizeof(int32_t), &o) ) return 0xEFFFFFFF;
    CryptReleaseContext(hdl, 0);
    #endif
  }
  return s;
}

void sifrkit_check_noise(int argc, char** argv)
{
  int32_t rsz = 128;

  int8_t fname[1024] = {0};
  int8_t rbit[1024] = {0};
  int32_t r = 0;
  int32_t i = 0;
  int32_t j = 0;
  FILE* fp = 0;

  #if __WIN32__
  sprintf(fname, "%s.%d.txt", "noise-CryptGenRandom", rsz);
  #endif

  #if __LINUX__
  sprintf(fname, "%s.%d.txt", "noise-random", rsz);
  #endif

  fp = fopen(fname, "w");

  for ( j=0 ; j<256 ; j++ )
  {
    __chk_noiz(0, rbit, rsz);
    for ( i=0 ; i<rsz/8 ; i++ )
    {
      fprintf(fp, "%02X", (uint8_t)rbit[i]);
    }
    fprintf(fp, "\n");
  }
  fclose(fp);



  #if __WIN32__
  sprintf(fname, "%s.%d.txt", "noise-CoCreateGuid", rsz);
  #endif

  #if __LINUX__
  sprintf(fname, "%s.%d.txt", "noise-urandom", rsz);
  #endif

  fp = fopen(fname, "w");

  for ( j=0 ; j<256 ; j++ )
  {
    __chk_noiz(1, rbit, rsz);
    for ( i=0 ; i<rsz/8 ; i++ )
    {
      fprintf(fp, "%02X", (uint8_t)rbit[i]);
    }
    fprintf(fp, "\n");
  }
  fclose(fp);

}


FILE* gfp;
FILE* gfp2;




void* sifr_drbg_caallback(void* h, void* m, void* w, void* l)
{
  int32_t i = 0;

  if ( (int32_t)l > 0 )
  {

    for ( i=0 ; i<(int32_t)l ; i++ )
    {
      fprintf(gfp, "%02X", (uint8_t)(*((uint8_t*)w+i)));
    }
    fflush(gfp);

    fwrite(w, l, sizeof(uint8_t), gfp2);
    fflush(gfp2);
  }

  return 0;
}






int32_t __check_seed(void* h)
{



  return 0;
}


//
//
//void check_RCT(void* h)
//{
//  int32_t e = 0;
//  uint8_t noiz[128] = {0};
//  int32_t i = 0;
//  int32_t j = 0;
//
//
//  e = _crpt.__sifr_noise_source(0, noiz, 32);
//
//  __RCT(3, noiz, 32);
//}
//
//void check_APT(void* h)
//{
//  int32_t e = 0;
//  uint8_t noiz[128] = {0};
//  int32_t i = 0;
//  int32_t j = 0;
//
//
//  e = _crpt.__sifr_noise_source(0, noiz, 32);
//
//  __APT(5, noiz, 32);
//}



void system_noise0(void* h)
{
  FILE* fp;
  FILE* fp2;
  uint8_t fn[512] = {0};
  uint8_t fn2[512] = {0};
  uint8_t noiz[128] = {0};
  int i = 0;
  int j = 0;

  #if WIN32
  #if defined x64
  sprintf(fn, "w64_noise_cryptgenrand.txt");
  #else
  sprintf(fn, "w32_noise_cryptgenrand.txt");
  #endif
  #endif

  #if LINUX  
  #if defined x32
  sprintf(fn, "ubuntu_32_noise_dev_random.txt");
  #elif defined x64
  sprintf(fn, "ubuntu_64_noise_dev_random.txt");
  #elif defined ha32
  sprintf(fn, "ubuntu_iot_32_noise_dev_random.txt");
  #else
  sprintf(fn, "ubuntu_iot_64_noise_dev_random.txt");
  #endif
  #endif


  sprintf(fn2, "%s.dat", fn);
  
  fp = fopen(fn, "wb");
  fp2 = fopen(fn2, "wb");


  fprintf(fp, "Len = 8, Num = 250000\n");

  i = 250000;
  for (; i>0 ;)
  {
    _crpt.__sifr_noise_source(0, noiz, 1);

    fwrite(noiz, 1, sizeof(uint8_t), fp2);
    fflush(fp2);

    fprintf(fp, "%02X", (uint8_t)noiz[0]);

    if ( i%1000 == 0 )  printf("  %08X  \r\n", i);
    fflush(fp);
    i--;

  }
  fclose(fp);
  fclose(fp2);

  printf("End of Programs \r\n");

}

void system_noise1(void* h)
{
  FILE* fp;
  FILE* fp2;
  uint8_t fn[512] = {0};
  uint8_t fn2[512] = {0};
  uint8_t noiz[128] = {0};
  int i = 0;
  int j = 0;

  #if WIN32
  #if defined x64
  sprintf(fn, "w64_noise_guid.txt");
  #else
  sprintf(fn, "w32_noise_guid.txt");
  #endif
  #endif

  #if LINUX  
  #if defined x32
  sprintf(fn, "ubuntu_32_noise_dev_urandom.txt");
  #elif defined x64
  sprintf(fn, "ubuntu_64_noise_dev_urandom.txt");
  #elif defined ha32
  sprintf(fn, "ubuntu_iot_32_noise_dev_urandom.txt");
  #else
  sprintf(fn, "ubuntu_iot_64_noise_dev_urandom.txt");
  #endif
  #endif


  sprintf(fn2, "%s.dat", fn);
  
  fp = fopen(fn, "wb");
  fp2 = fopen(fn2, "wb");

  fprintf(fp, "Len = 8, Num = 250000\n");

  i = 250000;
  for (; i>0 ;)
  {
    _crpt.__sifr_noise_source(0, noiz, 1);

    fwrite(noiz, 1, sizeof(uint8_t), fp2);
    fflush(fp2);

    fprintf(fp, "%02X", (uint8_t)noiz[0]);
    if ( i%1000 == 0 )  printf("  %08X  \r\n", i);
    fflush(fp);
    i--;

  }
  fclose(fp);
  fclose(fp2);

  printf("End of Programs \r\n");

}


#if 0
void system_noise0(void* h)
{
  FILE* fp;
  int8_t tmp[32] = {0};
  uint8_t fn[512] = {0};
  uint8_t noiz[128] = {0};
  int i = 0;

  #if WIN32
  #if defined x64
  sprintf(fn, "w64_noise_0.dat");
  #else
  sprintf(fn, "w32_noise_0.dat");
  #endif
  #endif

  #if LINUX  
  #if defined x32
  sprintf(fn, "l32_noise_0.dat");
  #elif defined x64
  sprintf(fn, "l64_noise_0.dat");
  #elif defined ha32
  sprintf(fn, "el32_noise_0.dat");
  #else
  sprintf(fn, "el64_noise_0.dat");
  #endif
  #endif

  fp = fopen(fn, "wb");

  i = 100000;
  for (; i>0 ;)
  {
    _crpt.__sifr_noise_source(0, noiz, 16);

    fwrite(noiz, 16, sizeof(uint8_t), fp);
    if ( i%1000 == 0 )  printf("  %08X  \r\n", i);
    fflush(fp);
    i--;
  }
  fclose(fp);

  printf("End of Programs \r\n");

}

void system_noise1(void* h)
{
  FILE* fp;
  int8_t tmp[32] = {0};
  uint8_t fn[512] = {0};
  uint8_t noiz[128] = {0};
  int i = 0;
  
  #if WIN32
  #if defined x64
  sprintf(fn, "w64_noise_1.dat");
  #else
  sprintf(fn, "w32_noise_1.dat");
  #endif
  #endif

  #if LINUX  
  #if defined x32
  sprintf(fn, "l32_noise_1.dat");
  #elif defined x64
  sprintf(fn, "l64_noise_1.dat");
  #elif defined ha32
  sprintf(fn, "el32_noise_1.dat");
  #else
  sprintf(fn, "el64_noise_1.dat");
  #endif
  #endif

  fp = fopen(fn, "wb");

  i = 100000;
  for (; i>0 ;)
  {
    _crpt.__sifr_noise_source(1, noiz, 16);

    fwrite(noiz, 16, sizeof(uint8_t), fp);
    if ( i%1000 == 0 )  printf("  %08X  \r\n", i);
    fflush(fp);
    i--;
  }
  fclose(fp);

  printf("End of Programs \r\n");

}
#endif



void print_status(void* h, int8_t* fx, int32_t e)
{
  int32_t lstatus[2] = {0};

  _crpt.__sifr_last_status(h, &lstatus[0], &lstatus[1]);
  if ( e < 0 ) printf(" %26s : %s(%08X) \r\n", fx, _crpt.__sifr_last_status_string(e), e);
  else         printf(" %26s : %s(%08X) -> %s(%08X) \r\n", fx, _crpt.__sifr_last_status_string(e), e, _crpt.__sifr_last_status_string(lstatus[0]), lstatus[0]);
}



void sifrkit(int argc, char** argv)
{
  int32_t e = 0;
  void* h = 0;
  int8_t  iobuf[8][4096] = {0};
  int8_t  ubuf[4096] = {0};
  int8_t  obuf[8][4096] = {0};
  int32_t sz[8] = {32, 32, 32, 32, 8, 32, 32, 64};
  int32_t lstatus[2] = {0};
  int8_t  version[1024] = {0};
  int8_t  author[1024] = {0};
  int8_t  module_name[1024] = {0};


  // 초기화 테스트
  e = _crpt.__sifr_init(&h, _crpt.p, _crpt.sz);
  print_status(h, "__sifr_init", e);

  // 조건부 시험
  e = _crpt.__sifr_kat_check(h);
  print_status(h, "__sifr_kat_check", e);

  e = _crpt.__sifr_integrity_check(h, _crpt.p, _crpt.sz );
  print_status(h, "__sifr_integrity_check", e);

  e = _crpt.__sifr_set_callback(h, sifrkit_callback, &_crpt);
  print_status(h, "__sifr_set_callback", e);

  e = _crpt.__sifr_module(h, module_name, 1024);
  print_status(h, "__sifr_module", e);
  printf(" module name : %s \r\n", module_name);

  e = _crpt.__sifr_version(h, version, 1024);
  print_status(h, "__sifr_version", e);
  printf(" version : %s \r\n", version);


  e = _crpt.__sifr_author(h, author, 1024);
  print_status(h, "__sifr_author", e);
  printf(" author : %s \r\n", author);


  ////e = _crpt.__sifr_kat_check(h, "./testvector");




  #if 0
  //e = _crpt.__sifr_kat_check(h);
  e = _crpt.__sifr_base64(h, "0001020304050607", 16, 'E', iobuf[0]);
  display(iobuf[0], e, "__sifr_base64 ENCODE");
  e = _crpt.__sifr_base64(h, iobuf[0], e, 'D', iobuf[1]);
  display(iobuf[1], e, "__sifr_base64 DECODE");
  #endif



  #if 1 /// DRBG

  //const uint8_t* PER_STR = "4041424344454647 48494A4B4C4D4E4F 5051525354555657 58595A5B5C5D5E5F";

  //const uint8_t* ADD_STR = "6061626364656667 68696A6B6C6D6E6F 7071727374757677 78797A7B7C7D7E7F";

	const uint8_t* ENTROPY_1 =
		"0001020304050607 08090A0B0C0D0E0F"
		"1011121314151617 18191A1B1C1D1E1F";

	const uint8_t* ENTROPY_2 = 
		"8081828384858687 88898A8B8C8D8E8F"
		"9091929394959697 98999A9B9C9D9E9F";
		//"C0C1C2C3C4C5C6C7 C8C9CACBCCCDCECF"
		//"D0D1D2D3D4D5D6D7 D8D9DADBDCDDDEDF";

	const uint8_t* NONCE =
		"2021222324252627";

	const uint8_t* PER_STR =
		"4041424344454647 48494A4B4C4D4E4F"
		"5051525354555657 58595A5B5C5D5E5F";

	const uint8_t* ADD_STR =
		"6061626364656667 68696A6B6C6D6E6F"
		"7071727374757677 78797A7B7C7D7E7F";
		//"A0A1A2A3A4A5A6A7 A8A9AAABACADAEAF"
		//"B0B1B2B3B4B5B6B7 B8B9BABBBCBDBEBF";

	//hsz[0] = ascii_to_hex("0001020304050607 08090A0B0C0D0E0F 1011121314151617 18191A1B1C1D1E1F", hbuf[0]);
	//hsz[1] = ascii_to_hex("4041424344454647 48494A4B4C4D4E4F 5051525354555657 58595A5B5C5D5E5F", hbuf[1]);
	//hsz[2] = ascii_to_hex("8081828384858687 88898A8B8C8D8E8F 9091929394959697 98999A9B9C9D9E9F", hbuf[2]);
	//hsz[4] = ascii_to_hex("6061626364656667 68696A6B6C6D6E6F 7071727374757677 78797A7B7C7D7E7F", hbuf[4]);
	//hsz[6] = ascii_to_hex("93942F7B917F352B 523348E09972ED5C 78A10E1135278103 80EE10FC5DFE4A85", hbuf[6]);

  sz[0] = ascii_to_hex(PER_STR, iobuf[0]);
  sz[1] = ascii_to_hex(ADD_STR, iobuf[1]);

  sz[2] = ascii_to_hex(ENTROPY_1, iobuf[2]);
  sz[3] = ascii_to_hex(ENTROPY_2, iobuf[3]);
  sz[4] = ascii_to_hex(NONCE, iobuf[4]);

  //sz[1] = 32;

  //e = _crpt.__sifr_entropy(h, 0, iobuf[5], 256);
  //e = _crpt.__sifr_entropy(h, 1, iobuf[6], 256);
  //e = _crpt.__sifr_entropy(h, 2, iobuf[7], 256);




  //check_RCT(h);
  //check_APT(h);


  #if 0
  {
    int32_t i = 0;
    int8_t fn[128] = {0};
    int8_t fn2[128] = {0};

    #if WIN32
    #if defined x64
    sprintf(fn, "w64_noise_conditioning.txt");
    #else
    sprintf(fn, "w32_noise_conditioning.txt");
    #endif
    #endif

    #if LINUX  
    #if defined x32
    sprintf(fn, "ubuntu_32_noise_conditioning.txt");
    #elif defined x64
    sprintf(fn, "ubuntu_64_noise_conditioning.txt");
    #elif defined ha32
    sprintf(fn, "ubuntu_iot_32_noise_conditioning.txt");
    #else
    sprintf(fn, "ubuntu_iot_64_noise_conditioning.txt");
    #endif
    #endif

    sprintf(fn2, "%s.dat", fn);

    gfp = fopen(fn, "wb");
    gfp2 = fopen(fn2, "wb");

    _crpt.__sifr_noise_source(0, iobuf[2], 32);  
    _crpt.__sifr_noise_source(0, iobuf[3], 32);
    _crpt.__sifr_noise_source(1, iobuf[4], 8);

    _crpt.__sifr_noise_source(1, iobuf[0], 8);
    _crpt.__sifr_noise_source(1, iobuf[1], 8);
  
    e = _crpt.__sifr_drbg(h, 'e', 0x80, iobuf[2], 32);
    e = _crpt.__sifr_drbg(h, 'e', 0x81, iobuf[3], 32);
    e = _crpt.__sifr_drbg(h, 'e', 0x82, iobuf[4], 8);

    e = _crpt.setMessage(h, MAKELONG(SYSTEM_CALLBACK,  SIFR_DRBG), sifr_drbg_caallback, h);

    fprintf(gfp, "Len = 576, Num = 250000\n");

    for ( i=0 ; i<250000 ; i++ )
    {
      e = _crpt.__sifr_drbg(h, 'i', 0xFF, iobuf[0], sz[0]);
    }

    fclose(gfp2);
    fclose(gfp);
  }
  system_noise0(h);
  system_noise1(h);
  #endif



  ////"93942F7B917F352B 523348E09972ED5C 78A10E1135278103 80EE10FC5DFE4A85"
  ////"3002F890728569CF A9184DBC36A52050 D0F9E76AF64CA232 A7293E40D5F96A7A"
  #endif



  e = _crpt.__sifr_random(h, iobuf[0], 128);
  print_status(h, "__sifr_random", e);
  display(iobuf[0], e, "KEY");







  e = _crpt.__sifr_random(h, iobuf[0], 128);
  print_status(h, "__sifr_random", e);
  display(iobuf[0], e, "KEY");

  e = _crpt.__sifr_random(h, iobuf[0], 128);
  print_status(h, "__sifr_random", e);
  display(iobuf[0], e, "KEY");


  e = _crpt.__sifr_drbg(h, 'e', 0, iobuf[2], sz[2]);
  print_status(h, "__sifr_drbg", e);
  display(iobuf[2], e, "entropy");

  e = _crpt.__sifr_drbg(h, 'e', 1, iobuf[3], sz[3]);
  print_status(h, "__sifr_drbg", e);
  display(iobuf[3], e, "entropy reseed");

  e = _crpt.__sifr_drbg(h, 'e', 2, iobuf[4], sz[4]);
  print_status(h, "__sifr_drbg", e);
  display(iobuf[4], e, "nonce");

  //e = _crpt.__sifr_drbg(h, 'p', 0, iobuf[0], sz[0]);
  //print_status(h, "__sifr_drbg", e);
  //display(iobuf[0], e, "personal string");

  //e = _crpt.__sifr_drbg(h, 'a', 0, iobuf[1], sz[1]);
  //print_status(h, "__sifr_drbg", e);
  //display(iobuf[1], e, "additional input");


  e = _crpt.__sifr_drbg(h, 'n', 0, iobuf[6], sz[6]);
  print_status(h, "__sifr_drbg", e);
  display(iobuf[6], e, "Noise Souce");


  e = _crpt.__sifr_drbg(h, 'i', 0xFF, iobuf[0], sz[0]);
  print_status(h, "__sifr_drbg", e);
  e = _crpt.__sifr_drbg(h, 'r', 0xFF, iobuf[1], sz[1]);
  print_status(h, "__sifr_drbg", e);
  e = _crpt.__sifr_drbg(h,   0, 0xFF, iobuf[7], sz[7]);
  print_status(h, "__sifr_drbg", e);
  display(iobuf[7], e, "__sifr_drbg");



  _crpt.__sifr_mem_clear(h, iobuf[0], sz[0]);
  display(iobuf[0], sz[0], "personal string");
  _crpt.__sifr_mem_clear(h, iobuf[1], sz[1]);
  display(iobuf[1], sz[1], "additional input");
  _crpt.__sifr_mem_clear(h, iobuf[2], sz[2]);
  display(iobuf[2], sz[2], "entropy");
  _crpt.__sifr_mem_clear(h, iobuf[3], sz[3]);
  display(iobuf[3], sz[3], "entropy reseed");
  _crpt.__sifr_mem_clear(h, iobuf[4], sz[4]);
  display(iobuf[4], sz[4], "nonce");
  _crpt.__sifr_mem_clear(h, iobuf[7], sz[7]);
  display(iobuf[7], sz[7], "random");












  e = _crpt.__sifr_drbg(h, 'r', 0xFF, iobuf[1], sz[1]);
  print_status(h, "__sifr_drbg", e);
  e = _crpt.__sifr_drbg(h, 'r', 0xFF, iobuf[1], sz[1]);
  print_status(h, "__sifr_drbg", e);
  e = _crpt.__sifr_drbg(h,   0, 0xFF, iobuf[7], 32);
  print_status(h, "__sifr_drbg", e);
  display(iobuf[7], e, "__sifr_drbg");


  e = _crpt.__sifr_drbg(h, 'r', 0xFF, iobuf[1], sz[1]);
  print_status(h, "__sifr_drbg", e);
  e = _crpt.__sifr_drbg(h, 'r', 0xFF, iobuf[1], sz[1]);
  print_status(h, "__sifr_drbg", e);
  e = _crpt.__sifr_drbg(h,   0, 0xFF, iobuf[7], 32);
  print_status(h, "__sifr_drbg", e);
  display(iobuf[7], e, "__sifr_drbg");


  e = _crpt.__sifr_drbg(h, 'e', 0x80, iobuf[2], sz[2]);
  print_status(h, "__sifr_drbg", e);
  e = _crpt.__sifr_drbg(h, 'e', 0x81, iobuf[3], sz[3]);
  print_status(h, "__sifr_drbg", e);
  e = _crpt.__sifr_drbg(h, 'e', 0x82, iobuf[4], sz[4]);
  print_status(h, "__sifr_drbg", e);

  e = _crpt.__sifr_drbg(h, 'i', 0xFF, iobuf[0], sz[0]);
  print_status(h, "__sifr_drbg", e);
  e = _crpt.__sifr_drbg(h, 'r', 0xFF, iobuf[1], sz[1]);
  print_status(h, "__sifr_drbg", e);
  e = _crpt.__sifr_drbg(h,   0, 0xFF, iobuf[7], 32);
  print_status(h, "__sifr_drbg", e);

  display(iobuf[7], e, "__sifr_drbg");

  e = _crpt.__sifr_drbg(h, 'e', 0, iobuf[2], 32);
  print_status(h, "__sifr_drbg", e);
  e = _crpt.__sifr_drbg(h, 'e', 1, iobuf[3], 32);
  print_status(h, "__sifr_drbg", e);
  e = _crpt.__sifr_drbg(h, 'e', 2, iobuf[4], 8);
  print_status(h, "__sifr_drbg", e);

  e = _crpt.__sifr_drbg(h, 'i', 0xFF, iobuf[0], sz[0]);
  print_status(h, "__sifr_drbg", e);
  e = _crpt.__sifr_drbg(h, 'r', 0xFF, iobuf[1], sz[1]);
  print_status(h, "__sifr_drbg", e);











  #if 1



  #if 1 // ARIA


///////////////////////////////////////////////////////////////////////////////
//////                                                                   //////
//////                                                                   //////
//////                             ARIA                                  //////
//////                                                                   //////
//////                                                                   //////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************/
/*****************************************************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*****************************                ********************************/
/*******************************            **********************************/
/*********************************        ************************************/
/************************************   **************************************/
/************************************* ***************************************/
/*****************************************************************************/
  BOX("ARIA ECB 128 CHECK");
  sz[0] = ascii_to_hex( KISA_KEY_ARIA128_ECB[0][0], iobuf[0]);
  sz[1] = ascii_to_hex( KISA_KEY_ARIA128_ECB[0][1], iobuf[1]);
  display(iobuf[0], sz[0], "Input Key");
  display(iobuf[1], sz[1], "Input Text");
  e = _crpt.__sifr_aria_ecb_encode(h, iobuf[0], sz[0], iobuf[1], sz[1], obuf[0], 4096, sifr_aria_callback, &_crpt);
  print_status(h, "__sifr_aria_ecb_encode", e);
  display(obuf[0], e, "ARIA ECB 128 ENCODE");
  e = _crpt.__sifr_aria_ecb_decode(h, iobuf[0], sz[0], obuf[0], e, obuf[1], 4096, sifr_aria_callback, &_crpt);
  print_status(h, "__sifr_aria_ecb_decode", e);
  display(obuf[1], e, "ARIA ECB 128 DECODE");


  BOX("ARIA ECB 192 CHECK");
  sz[0] = ascii_to_hex( KISA_KEY_ARIA192_ECB[0][0], iobuf[0]);
  sz[1] = ascii_to_hex( KISA_KEY_ARIA192_ECB[0][1], iobuf[1]);
  display(iobuf[0], sz[0], "Input Key");
  display(iobuf[1], sz[1], "Input Text");
  e = _crpt.__sifr_aria_ecb_encode(h, iobuf[0], sz[0], iobuf[1], sz[1], obuf[0], 4096, sifr_aria_callback, &_crpt);
  print_status(h, "__sifr_aria_ecb_encode", e);
  display(obuf[0], e, "ARIA ECB 192 ENCODE");
  e = _crpt.__sifr_aria_ecb_decode(h, iobuf[0], sz[0], obuf[0], e, obuf[1], 4096, sifr_aria_callback, &_crpt);
  print_status(h, "__sifr_aria_ecb_decode", e);
  display(obuf[1], e, "ARIA ECB 192 DECODE");


  BOX("ARIA ECB 256 CHECK");
  sz[0] = ascii_to_hex( KISA_KEY_ARIA256_ECB[0][0], iobuf[0]);
  sz[1] = ascii_to_hex( KISA_KEY_ARIA256_ECB[0][1], iobuf[1]);
  display(iobuf[0], sz[0], "Input Key");
  display(iobuf[1], sz[1], "Input Text");
  e = _crpt.__sifr_aria_ecb_encode(h, iobuf[0], sz[0], iobuf[1], sz[1], obuf[0], 4096, sifr_aria_callback, &_crpt);
  print_status(h, "__sifr_aria_ecb_encode", e);
  display(obuf[0], e, "ARIA ECB 256 ENCODE");
  e = _crpt.__sifr_aria_ecb_decode(h, iobuf[0], sz[0], obuf[0], e, obuf[1], 4096, sifr_aria_callback, &_crpt);
  print_status(h, "__sifr_aria_ecb_decode", e);
  display(obuf[1], e, "ARIA ECB 256 DECODE");



  BOX("ARIA CBC 128 CHECK");
  sz[0] = ascii_to_hex( KISA_KEY_ARIA128_CBC[0][0], iobuf[0]);
  sz[1] = ascii_to_hex( KISA_KEY_ARIA128_CBC[0][1], iobuf[1]);
  sz[2] = ascii_to_hex( KISA_KEY_ARIA128_CBC[0][2], iobuf[2]);
  display(iobuf[0], sz[0], "Input Key");
  display(iobuf[1], sz[1], "Input Vector");
  display(iobuf[2], sz[2], "Input Text");
  e = _crpt.__sifr_aria_cbc_encode(h, iobuf[0], sz[0], iobuf[1], sz[1], iobuf[2], sz[2], obuf[0], 4096, sifr_aria_callback, &_crpt);
  print_status(h, "__sifr_aria_cbc_encode", e);
  display(obuf[0], e, "ARIA CBC 128 ENCODE");
  e = _crpt.__sifr_aria_cbc_decode(h, iobuf[0], sz[0], iobuf[1], sz[1], obuf[0], e, obuf[1], 4096, sifr_aria_callback, &_crpt);
  print_status(h, "__sifr_aria_cbc_decode", e);
  display(obuf[1], e, "ARIA CBC 128 DECODE");


  BOX("ARIA CBC 192 CHECK");
  sz[0] = ascii_to_hex( KISA_KEY_ARIA192_CBC[0][0], iobuf[0]);
  sz[1] = ascii_to_hex( KISA_KEY_ARIA192_CBC[0][1], iobuf[1]);
  sz[2] = ascii_to_hex( KISA_KEY_ARIA192_CBC[0][2], iobuf[2]);
  display(iobuf[0], sz[0], "Input Key");
  display(iobuf[1], sz[1], "Input Vector");
  display(iobuf[2], sz[2], "Input Text");
  e = _crpt.__sifr_aria_cbc_encode(h, iobuf[0], sz[0], iobuf[1], sz[1], iobuf[2], sz[2], obuf[0], 4096, sifr_aria_callback, &_crpt);
  print_status(h, "__sifr_aria_cbc_encode", e);
  display(obuf[0], e, "ARIA CBC 192 ENCODE");
  e = _crpt.__sifr_aria_cbc_decode(h, iobuf[0], sz[0], iobuf[1], sz[1], obuf[0], e, obuf[1], 4096, sifr_aria_callback, &_crpt);
  print_status(h, "__sifr_aria_cbc_decode", e);
  display(obuf[1], e, "ARIA CBC 192 DECODE");



  BOX("ARIA CBC 256 CHECK");
  sz[0] = ascii_to_hex( KISA_KEY_ARIA256_CBC[0][0], iobuf[0]);
  sz[1] = ascii_to_hex( KISA_KEY_ARIA256_CBC[0][1], iobuf[1]);
  sz[2] = ascii_to_hex( KISA_KEY_ARIA256_CBC[0][2], iobuf[2]);
  display(iobuf[0], sz[0], "Input Key");
  display(iobuf[1], sz[1], "Input Vector");
  display(iobuf[2], sz[2], "Input Text");
  e = _crpt.__sifr_aria_cbc_encode(h, iobuf[0], sz[0], iobuf[1], sz[1], iobuf[2], sz[2], obuf[0], 4096, sifr_aria_callback, &_crpt);
  print_status(h, "__sifr_aria_cbc_encode", e);
  display(obuf[0], e, "ARIA CBC 256 ENCODE");
  e = _crpt.__sifr_aria_cbc_decode(h, iobuf[0], sz[0], iobuf[1], sz[1], obuf[0], e, obuf[1], 4096, sifr_aria_callback, &_crpt);
  print_status(h, "__sifr_aria_cbc_decode", e);
  display(obuf[1], e, "ARIA CBC 256 DECODE");


  BOX("ARIA CFB 128 CHECK");
  sz[0] = ascii_to_hex( KISA_KEY_ARIA128_CFB[0][0], iobuf[0]);
  sz[1] = ascii_to_hex( KISA_KEY_ARIA128_CFB[0][1], iobuf[1]);
  sz[2] = ascii_to_hex( KISA_KEY_ARIA128_CFB[0][2], iobuf[2]);
  display(iobuf[0], sz[0], "Input Key");
  display(iobuf[1], sz[1], "Input Vector");
  display(iobuf[2], sz[2], "Input Text");
  e = _crpt.__sifr_aria_cfb_encode(h, iobuf[0], sz[0], iobuf[1], sz[1], iobuf[2], sz[2], obuf[0], 4096, sifr_aria_callback, &_crpt);
  print_status(h, "__sifr_aria_cfb_encode", e);
  display(obuf[0], e, "ARIA CFB 128 ENCODE");
  e = _crpt.__sifr_aria_cbc_decode(h, iobuf[0], sz[0], iobuf[1], sz[1], obuf[0], e, obuf[1], 4096, sifr_aria_callback, &_crpt);
  print_status(h, "__sifr_aria_cbc_decode", e);
  display(obuf[1], e, "ARIA CFB 128 DECODE");


  BOX("ARIA CFB 192 CHECK");
  sz[0] = ascii_to_hex( KISA_KEY_ARIA192_CFB[0][0], iobuf[0]);
  sz[1] = ascii_to_hex( KISA_KEY_ARIA192_CFB[0][1], iobuf[1]);
  sz[2] = ascii_to_hex( KISA_KEY_ARIA192_CFB[0][2], iobuf[2]);
  display(iobuf[0], sz[0], "Input Key");
  display(iobuf[1], sz[1], "Input Vector");
  display(iobuf[2], sz[2], "Input Text");
  e = _crpt.__sifr_aria_cfb_encode(h, iobuf[0], sz[0], iobuf[1], sz[1], iobuf[2], sz[2], obuf[0], 4096, sifr_aria_callback, &_crpt);
  print_status(h, "__sifr_aria_cfb_encode", e);
  display(obuf[0], e, "ARIA CFB 192 ENCODE");
  e = _crpt.__sifr_aria_cfb_decode(h, iobuf[0], sz[0], iobuf[1], sz[1], obuf[0], e, obuf[1], 4096, sifr_aria_callback, &_crpt);
  print_status(h, "__sifr_aria_cfb_decode", e);
  display(obuf[1], e, "ARIA CFB 192 DECODE");


  BOX("ARIA CFB 256 CHECK");
  sz[0] = ascii_to_hex( KISA_KEY_ARIA256_CFB[0][0], iobuf[0]);
  sz[1] = ascii_to_hex( KISA_KEY_ARIA256_CFB[0][1], iobuf[1]);
  sz[2] = ascii_to_hex( KISA_KEY_ARIA256_CFB[0][2], iobuf[2]);
  display(iobuf[0], sz[0], "Input Key");
  display(iobuf[1], sz[1], "Input Vector");
  display(iobuf[2], sz[2], "Input Text");
  e = _crpt.__sifr_aria_cfb_encode(h, iobuf[0], sz[0], iobuf[1], sz[1], iobuf[2], sz[2], obuf[0], 4096, sifr_aria_callback, &_crpt);
  print_status(h, "__sifr_aria_cfb_encode", e);
  display(obuf[0], e, "ARIA CFB 256 ENCODE");
  e = _crpt.__sifr_aria_cfb_decode(h, iobuf[0], sz[0], iobuf[1], sz[1], obuf[0], e, obuf[1], 4096, sifr_aria_callback, &_crpt);
  print_status(h, "__sifr_aria_cfb_decode", e);
  display(obuf[1], e, "ARIA CFB 256 DECODE");


  BOX("ARIA OFB 128 CHECK");
  sz[0] = ascii_to_hex( KISA_KEY_ARIA128_OFB[0][0], iobuf[0]);
  sz[1] = ascii_to_hex( KISA_KEY_ARIA128_OFB[0][1], iobuf[1]);
  sz[2] = ascii_to_hex( KISA_KEY_ARIA128_OFB[0][2], iobuf[2]);
  display(iobuf[0], sz[0], "Input Key");
  display(iobuf[1], sz[1], "Input Vector");
  display(iobuf[2], sz[2], "Input Text");
  e = _crpt.__sifr_aria_ofb_encode(h, iobuf[0], sz[0], iobuf[1], sz[1], iobuf[2], sz[2], obuf[0], 4096, sifr_aria_callback, &_crpt);
  print_status(h, "__sifr_aria_ofb_encode", e);
  display(obuf[0], e, "ARIA OFB 128 ENCODE");
  e = _crpt.__sifr_aria_ofb_decode(h, iobuf[0], sz[0], iobuf[1], sz[1], obuf[0], e, obuf[1], 4096, sifr_aria_callback, &_crpt);
  print_status(h, "__sifr_aria_ofb_decode", e);
  display(obuf[1], e, "ARIA OFB 128 DECODE");


  BOX("ARIA OFB 192 CHECK");
  sz[0] = ascii_to_hex( KISA_KEY_ARIA192_OFB[0][0], iobuf[0]);
  sz[1] = ascii_to_hex( KISA_KEY_ARIA192_OFB[0][1], iobuf[1]);
  sz[2] = ascii_to_hex( KISA_KEY_ARIA192_OFB[0][2], iobuf[2]);
  display(iobuf[0], sz[0], "Input Key");
  display(iobuf[1], sz[1], "Input Vector");
  display(iobuf[2], sz[2], "Input Text");
  e = _crpt.__sifr_aria_ofb_encode(h, iobuf[0], sz[0], iobuf[1], sz[1], iobuf[2], sz[2], obuf[0], 4096, sifr_aria_callback, &_crpt);
  print_status(h, "__sifr_aria_ofb_encode", e);
  display(obuf[0], e, "ARIA OFB 192 ENCODE");
  e = _crpt.__sifr_aria_ofb_decode(h, iobuf[0], sz[0], iobuf[1], sz[1], obuf[0], e, obuf[1], 4096, sifr_aria_callback, &_crpt);
  print_status(h, "__sifr_aria_ofb_decode", e);
  display(obuf[1], e, "ARIA OFB 192 DECODE");



  BOX("ARIA OFB 256 CHECK");
  sz[0] = ascii_to_hex( KISA_KEY_ARIA256_OFB[0][0], iobuf[0]);
  sz[1] = ascii_to_hex( KISA_KEY_ARIA256_OFB[0][1], iobuf[1]);
  sz[2] = ascii_to_hex( KISA_KEY_ARIA256_OFB[0][2], iobuf[2]);
  display(iobuf[0], sz[0], "Input Key");
  display(iobuf[1], sz[1], "Input Vector");
  display(iobuf[2], sz[2], "Input Text");
  e = _crpt.__sifr_aria_ofb_encode(h, iobuf[0], sz[0], iobuf[1], sz[1], iobuf[2], sz[2], obuf[0], 4096, sifr_aria_callback, &_crpt);
  print_status(h, "__sifr_aria_ofb_encode", e);
  display(obuf[0], e, "ARIA OFB 256 ENCODE");
  e = _crpt.__sifr_aria_ofb_decode(h, iobuf[0], sz[0], iobuf[1], sz[1], obuf[0], e, obuf[1], 4096, sifr_aria_callback, &_crpt);
  print_status(h, "__sifr_aria_ofb_decode", e);
  display(obuf[1], e, "ARIA OFB 256 DECODE");

  BOX("ARIA CTR 128 CHECK");
  sz[0] = ascii_to_hex( KISA_KEY_ARIA128_CTR[0][0], iobuf[0]);
  sz[1] = ascii_to_hex( KISA_KEY_ARIA128_CTR[0][1], iobuf[1]);
  sz[2] = ascii_to_hex( KISA_KEY_ARIA128_CTR[0][2], iobuf[2]);
  display(iobuf[0], sz[0], "Input Key");
  display(iobuf[1], sz[1], "Input Vector");
  display(iobuf[2], sz[2], "Input Text");
  e = _crpt.__sifr_aria_ctr_encode(h, iobuf[0], sz[0], iobuf[1], sz[1], iobuf[2], sz[2], obuf[0], 4096, sifr_aria_callback, &_crpt);
  print_status(h, "__sifr_aria_ctr_encode", e);
  display(obuf[0], e, "ARIA CTR 128 ENCODE");
  e = _crpt.__sifr_aria_ctr_decode(h, iobuf[0], sz[0], iobuf[1], sz[1], obuf[0], e, obuf[1], 4096, sifr_aria_callback, &_crpt);
  print_status(h, "__sifr_aria_ctr_decode", e);
  display(obuf[1], e, "ARIA CTR 128 DECODE");


  BOX("ARIA CTR 192 CHECK");
  sz[0] = ascii_to_hex( KISA_KEY_ARIA192_CTR[0][0], iobuf[0]);
  sz[1] = ascii_to_hex( KISA_KEY_ARIA192_CTR[0][1], iobuf[1]);
  sz[2] = ascii_to_hex( KISA_KEY_ARIA192_CTR[0][2], iobuf[2]);
  display(iobuf[0], sz[0], "Input Key");
  display(iobuf[1], sz[1], "Input Vector");
  display(iobuf[2], sz[2], "Input Text");
  e = _crpt.__sifr_aria_ctr_encode(h, iobuf[0], sz[0], iobuf[1], sz[1], iobuf[2], sz[2], obuf[0], 4096, sifr_aria_callback, &_crpt);
  print_status(h, "__sifr_aria_ctr_encode", e);
  display(obuf[0], e, "ARIA CTR 192 ENCODE");
  e = _crpt.__sifr_aria_ctr_decode(h, iobuf[0], sz[0], iobuf[1], sz[1], obuf[0], e, obuf[1], 4096, sifr_aria_callback, &_crpt);
  print_status(h, "__sifr_aria_ctr_decode", e);
  display(obuf[1], e, "ARIA CTR 192 DECODE");


  BOX("ARIA CTR 256 CHECK");
  sz[0] = ascii_to_hex( KISA_KEY_ARIA256_CTR[0][0], iobuf[0]);
  sz[1] = ascii_to_hex( KISA_KEY_ARIA256_CTR[0][1], iobuf[1]);
  sz[2] = ascii_to_hex( KISA_KEY_ARIA256_CTR[0][2], iobuf[2]);
  display(iobuf[0], sz[0], "Input Key");
  display(iobuf[1], sz[1], "Input Vector");
  display(iobuf[2], sz[2], "Input Text");
  e = _crpt.__sifr_aria_ctr_encode(h, iobuf[0], sz[0], iobuf[1], sz[1], iobuf[2], sz[2], obuf[0], 4096, sifr_aria_callback, &_crpt);
  print_status(h, "__sifr_aria_ctr_encode", e);
  display(obuf[0], e, "ARIA CTR 256 ENCODE");
  e = _crpt.__sifr_aria_ctr_decode(h, iobuf[0], sz[0], iobuf[1], sz[1], obuf[0], e, obuf[1], 4096, sifr_aria_callback, &_crpt);
  print_status(h, "__sifr_aria_ctr_decode", e);
  display(obuf[1], e, "ARIA CTR 256 DECODE");

  //const uint8_t* ARIA_CCM_KEY = "2A82F2A33E5588FB32CD6AB328CC0659";
  //const uint8_t* ARIA_CCM_ADD = "3B6B320972196FBC56B40601AE7B8A29";
  //const uint8_t* ARIA_CCM_PT  = "56666311865C2CF656A6598B82A41D49";

  //sz[0] = ascii_to_hex( ARIA_CCM_KEY, iobuf[0]);
  //sz[1] = ascii_to_hex( ARIA_CCM_ADD, iobuf[1]);
  //sz[2] = ascii_to_hex( ARIA_CCM_PT, iobuf[2]);
  //e = _crpt.__sifr_aria_ccm_encode(h, iobuf[0], sz[0], iobuf[1], sz[1], iobuf[2], sz[2], obuf[0], 4096, sifr_aria_callback, &_crpt);
  //display(obuf[0], e, "ARIA CCM ENCODE");

  //e = _crpt.__sifr_aria_ccm_decode(h, iobuf[0], sz[0], iobuf[1], sz[1], obuf[0], e, obuf[1], 4096, sifr_aria_callback, &_crpt);
  //display(obuf[1], e, "ARIA CCM DECODE");
  #endif


  #if 1 //__LEA__

  BOX("LEA ECB 128 CHECK");
  sz[0] = ascii_to_hex( KISA_KEY_LEA128_ECB[0][0], iobuf[0]);
  sz[1] = ascii_to_hex( KISA_KEY_LEA128_ECB[0][1], iobuf[1]);
  sz[2] = ascii_to_hex( KISA_KEY_LEA128_ECB[0][2], iobuf[2]);
  display(iobuf[0], sz[0], "Input Key");
  display(iobuf[1], sz[1], "Input Text");
  display(iobuf[2], sz[2], "Expected Cipher");
  e = _crpt.__sifr_lea_ecb_encode(h, iobuf[0], sz[0], iobuf[1], sz[1], obuf[0], 4096, sifr_lea_callback, &_crpt);
  print_status(h, "__sifr_lea_ecb_encode", e);
  display(obuf[0], e, "LEA ECB 128 ENCODE");
  e = _crpt.__sifr_lea_ecb_decode(h, iobuf[0], sz[0], obuf[0], e, obuf[1], 4096, sifr_lea_callback, &_crpt);
  print_status(h, "__sifr_lea_ecb_decode", e);
  display(obuf[1], e, "LEA ECB 128 DECODE");



  BOX("LEA CBC 128 CHECK");
  sz[0] = ascii_to_hex( KISA_KEY_LEA128_CBC[0][0], iobuf[0]);
  sz[1] = ascii_to_hex( KISA_KEY_LEA128_CBC[0][1], iobuf[1]);
  sz[2] = ascii_to_hex( KISA_KEY_LEA128_CBC[0][2], iobuf[2]);
  sz[3] = ascii_to_hex( KISA_KEY_LEA128_CBC[0][3], iobuf[3]);
  display(iobuf[0], sz[0], "Input Key");
  display(iobuf[1], sz[1], "Input Vector");
  display(iobuf[2], sz[2], "Input Text");
  display(iobuf[3], sz[3], "Expected Cipher");
  e = _crpt.__sifr_lea_cbc_encode(h, iobuf[0], sz[0], iobuf[1], sz[1], iobuf[2], sz[2], obuf[0], 4096, sifr_lea_callback, &_crpt);
  print_status(h, "__sifr_lea_cbc_encode", e);
  display(obuf[0], e, "LEA CBC 128 ENCODE");
  e = _crpt.__sifr_lea_cbc_decode(h, iobuf[0], sz[0], iobuf[1], sz[1], obuf[0], e, obuf[1], 4096, sifr_lea_callback, &_crpt);
  print_status(h, "__sifr_lea_cbc_decode", e);
  display(obuf[1], e, "LEA CBC 128 DECODE");



  BOX("LEA CFB 128 CHECK");
  sz[0] = ascii_to_hex( KISA_KEY_LEA128_CFB[0][0], iobuf[0]);
  sz[1] = ascii_to_hex( KISA_KEY_LEA128_CFB[0][1], iobuf[1]);
  sz[2] = ascii_to_hex( KISA_KEY_LEA128_CFB[0][2], iobuf[2]);
  sz[3] = ascii_to_hex( KISA_KEY_LEA128_CFB[0][3], iobuf[3]);
  display(iobuf[0], sz[0], "Input Key");
  display(iobuf[1], sz[1], "Input Vector");
  display(iobuf[2], sz[2], "Input Text");
  display(iobuf[3], sz[3], "Expected Cipher");
  e = _crpt.__sifr_lea_cfb_encode(h, iobuf[0], sz[0], iobuf[1], sz[1], iobuf[2], sz[2], obuf[0], 4096, sifr_lea_callback, &_crpt);
  print_status(h, "__sifr_lea_cfb_encode", e);
  display(obuf[0], e, "LEA CFB 128 ENCODE");
  e = _crpt.__sifr_lea_cfb_decode(h, iobuf[0], sz[0], iobuf[1], sz[1], obuf[0], e, obuf[1], 4096, sifr_lea_callback, &_crpt);
  print_status(h, "__sifr_lea_cfb_decode", e);
  display(obuf[1], e, "LEA CFB 128 DECODE");


  BOX("LEA OFB 128 CHECK");
  sz[0] = ascii_to_hex( KISA_KEY_LEA128_OFB[0][0], iobuf[0]);
  sz[1] = ascii_to_hex( KISA_KEY_LEA128_OFB[0][1], iobuf[1]);
  sz[2] = ascii_to_hex( KISA_KEY_LEA128_OFB[0][2], iobuf[2]);
  sz[3] = ascii_to_hex( KISA_KEY_LEA128_OFB[0][3], iobuf[3]);
  display(iobuf[0], sz[0], "Input Key");
  display(iobuf[1], sz[1], "Input Vector");
  display(iobuf[2], sz[2], "Input Text");
  display(iobuf[3], sz[3], "Expected Cipher");
  e = _crpt.__sifr_lea_ofb_encode(h, iobuf[0], sz[0], iobuf[1], sz[1], iobuf[2], sz[2], obuf[0], 4096, sifr_lea_callback, &_crpt);
  print_status(h, "__sifr_lea_ofb_encode", e);
  display(obuf[0], e, "LEA OFB 128 ENCODE");
  e = _crpt.__sifr_lea_ofb_decode(h, iobuf[0], sz[0], iobuf[1], sz[1], obuf[0], e, obuf[1], 4096, sifr_lea_callback, &_crpt);
  print_status(h, "__sifr_lea_ofb_decode", e);
  display(obuf[1], e, "LEA OFB 128 DECODE");


  BOX("LEA CTR 128 CHECK");
  sz[0] = ascii_to_hex( KISA_KEY_LEA128_CTR[0][0], iobuf[0]);
  sz[1] = ascii_to_hex( KISA_KEY_LEA128_CTR[0][1], iobuf[1]);
  sz[2] = ascii_to_hex( KISA_KEY_LEA128_CTR[0][2], iobuf[2]);
  sz[3] = ascii_to_hex( KISA_KEY_LEA128_CTR[0][3], iobuf[3]);
  display(iobuf[0], sz[0], "Input Key");
  display(iobuf[1], sz[1], "Input Vector");
  display(iobuf[2], sz[2], "Input Text");
  display(iobuf[3], sz[3], "Expected Cipher");
  e = _crpt.__sifr_lea_ctr_encode(h, iobuf[0], sz[0], iobuf[1], sz[1], iobuf[2], sz[2], obuf[0], 4096, sifr_lea_callback, &_crpt);
  print_status(h, "__sifr_lea_ctr_encode", e);
  display(obuf[0], e, "LEA CTR 128 ENCODE");
  e = _crpt.__sifr_lea_ctr_decode(h, iobuf[0], sz[0], iobuf[1], sz[1], obuf[0], e, obuf[1], 4096, sifr_lea_callback, &_crpt);
  print_status(h, "__sifr_lea_ctr_decode", e);
  display(obuf[1], e, "LEA CTR 128 DECODE");

  #endif



  #if 1 //__SEED__

  BOX("SEED ECB CHECK");
  sz[0] = ascii_to_hex( KISA_KEY_SEED_ECB[0][0], iobuf[0]);
  sz[1] = ascii_to_hex( KISA_KEY_SEED_ECB[0][1], iobuf[1]);
  sz[2] = ascii_to_hex( KISA_KEY_SEED_ECB[0][2], iobuf[2]);
  display(iobuf[0], sz[0], "Input Key");
  display(iobuf[1], sz[1], "Input Text");
  display(iobuf[2], sz[2], "Expected Cipher");
  e = _crpt.__sifr_seed_ecb_encode(h, iobuf[0], sz[0], iobuf[1], sz[1], obuf[0], 4096, sifr_seed_callback, &_crpt);
  print_status(h, "__sifr_seed_ecb_encode", e);
  display(obuf[0], e, "SEED ECB ENCODE");
  e = _crpt.__sifr_seed_ecb_decode(h, iobuf[0], sz[0], obuf[0], e, obuf[1], 4096, sifr_seed_callback, &_crpt);
  print_status(h, "__sifr_seed_ecb_decode", e);
  display(obuf[1], e, "SEED ECB DECODE");

  BOX("SEED CBC CHECK");
  sz[0] = ascii_to_hex( KISA_KEY_SEED_CBC[0][0], iobuf[0]);
  sz[1] = ascii_to_hex( KISA_KEY_SEED_CBC[0][1], iobuf[1]);
  sz[2] = ascii_to_hex( KISA_KEY_SEED_CBC[0][2], iobuf[2]);
  sz[3] = ascii_to_hex( KISA_KEY_SEED_CBC[0][3], iobuf[3]);
  display(iobuf[0], sz[0], "Input Key");
  display(iobuf[1], sz[1], "Input Vector");
  display(iobuf[2], sz[2], "Input Text");
  display(iobuf[3], sz[3], "Expected Cipher");
  e = _crpt.__sifr_seed_cbc_encode(h, iobuf[0], sz[0], iobuf[1], sz[1], iobuf[2], sz[2], obuf[0], 4096, sifr_seed_callback, &_crpt);
  print_status(h, "__sifr_seed_cbc_encode", e);
  display(obuf[0], e, "SEED CBC ENCODE");
  e = _crpt.__sifr_seed_cbc_decode(h, iobuf[0], sz[0], iobuf[1], sz[1], obuf[0], e, obuf[1], 4096, sifr_seed_callback, &_crpt);
  print_status(h, "__sifr_seed_cbc_decode", e);
  display(obuf[1], e, "SEED CBC DECODE");


  BOX("SEED CFB CHECK");
  sz[0] = ascii_to_hex( KISA_KEY_SEED_CFB[0][0], iobuf[0]);
  sz[1] = ascii_to_hex( KISA_KEY_SEED_CFB[0][1], iobuf[1]);
  sz[2] = ascii_to_hex( KISA_KEY_SEED_CFB[0][2], iobuf[2]);
  sz[3] = ascii_to_hex( KISA_KEY_SEED_CFB[0][3], iobuf[3]);
  display(iobuf[0], sz[0], "Input Key");
  display(iobuf[1], sz[1], "Input Vector");
  display(iobuf[2], sz[2], "Input Text");
  display(iobuf[3], sz[3], "Expected Cipher");
  e = _crpt.__sifr_seed_cfb_encode(h, iobuf[0], sz[0], iobuf[1], sz[1], iobuf[2], sz[2], obuf[0], 4096, sifr_seed_callback, &_crpt);
  print_status(h, "__sifr_seed_cfb_encode", e);
  display(obuf[0], e, "SEED CFB ENCODE");
  e = _crpt.__sifr_seed_cfb_decode(h, iobuf[0], sz[0], iobuf[1], sz[1], obuf[0], e, obuf[1], 4096, sifr_seed_callback, &_crpt);
  print_status(h, "__sifr_seed_cfb_decode", e);
  display(obuf[1], e, "SEED CFB DECODE");


  BOX("SEED OFB CHECK");
  sz[0] = ascii_to_hex( KISA_KEY_SEED_OFB[0][0], iobuf[0]);
  sz[1] = ascii_to_hex( KISA_KEY_SEED_OFB[0][1], iobuf[1]);
  sz[2] = ascii_to_hex( KISA_KEY_SEED_OFB[0][2], iobuf[2]);
  sz[3] = ascii_to_hex( KISA_KEY_SEED_OFB[0][3], iobuf[3]);
  display(iobuf[0], sz[0], "Input Key");
  display(iobuf[1], sz[1], "Input Vector");
  display(iobuf[2], sz[2], "Input Text");
  display(iobuf[3], sz[3], "Expected Cipher");
  e = _crpt.__sifr_seed_ofb_encode(h, iobuf[0], sz[0], iobuf[1], sz[1], iobuf[2], sz[2], obuf[0], 4096, sifr_seed_callback, &_crpt);
  print_status(h, "__sifr_seed_ofb_encode", e);
  display(obuf[0], e, "SEED OFB ENCODE");
  e = _crpt.__sifr_seed_ofb_decode(h, iobuf[0], sz[0], iobuf[1], sz[1], obuf[0], e, obuf[1], 4096, sifr_seed_callback, &_crpt);
  print_status(h, "__sifr_seed_ofb_decode", e);
  display(obuf[1], e, "SEED OFB DECODE");


  BOX("SEED CTR CHECK");
  sz[0] = ascii_to_hex( KISA_KEY_SEED_CTR[0][0], iobuf[0]);
  sz[1] = ascii_to_hex( KISA_KEY_SEED_CTR[0][1], iobuf[1]);
  sz[2] = ascii_to_hex( KISA_KEY_SEED_CTR[0][2], iobuf[2]);
  sz[3] = ascii_to_hex( KISA_KEY_SEED_CTR[0][3], iobuf[3]);
  display(iobuf[0], sz[0], "Input Key");
  display(iobuf[1], sz[1], "Input Vector");
  display(iobuf[2], sz[2], "Input Text");
  display(iobuf[3], sz[3], "Expected Cipher");
  e = _crpt.__sifr_seed_ctr_encode(h, iobuf[0], sz[0], iobuf[1], sz[1], iobuf[2], sz[2], obuf[0], 4096, sifr_seed_callback, &_crpt);
  print_status(h, "__sifr_seed_ctr_encode", e);
  display(obuf[0], e, "SEED CTR ENCODE");
  e = _crpt.__sifr_seed_ctr_decode(h, iobuf[0], sz[0], iobuf[1], sz[1], obuf[0], e, obuf[1], 4096, sifr_seed_callback, &_crpt);
  print_status(h, "__sifr_seed_ctr_decode", e);
  display(obuf[1], e, "SEED CTR DECODE");

  #endif




  #if 1 //__HIGHT__
  BOX("HIGHT ECB CHECK");
  sz[0] = ascii_to_hex( KISA_KEY_HIGHT_ECB[0][0], iobuf[0]);
  sz[1] = ascii_to_hex( KISA_KEY_HIGHT_ECB[0][1], iobuf[1]);
  sz[2] = ascii_to_hex( KISA_KEY_HIGHT_ECB[0][2], iobuf[2]);
  display(iobuf[0], sz[0], "Input Key");
  display(iobuf[1], sz[1], "Input Text");
  display(iobuf[2], sz[2], "Expected Cipher");
  e = _crpt.__sifr_hight_ecb_encode(h, iobuf[0], sz[0], iobuf[1], sz[1], obuf[0], 4096, sifr_hight_callback, &_crpt);
  print_status(h, "__sifr_hight_ecb_encode", e);
  display(obuf[0], e, "HIGHT ECB ENCODE");
  e = _crpt.__sifr_hight_ecb_decode(h, iobuf[0], sz[0], obuf[0], e, obuf[1], 4096, sifr_hight_callback, &_crpt);
  print_status(h, "__sifr_hight_ecb_decode", e);
  display(obuf[1], e, "HIGHT ECB DECODE");


  BOX("HIGHT CBC CHECK");
  sz[0] = ascii_to_hex( KISA_KEY_HIGHT_CBC[0][0], iobuf[0]);
  sz[1] = ascii_to_hex( KISA_KEY_HIGHT_CBC[0][1], iobuf[1]);
  sz[2] = ascii_to_hex( KISA_KEY_HIGHT_CBC[0][2], iobuf[2]);
  sz[3] = ascii_to_hex( KISA_KEY_HIGHT_CBC[0][3], iobuf[3]);
  display(iobuf[0], sz[0], "Input Key");
  display(iobuf[1], sz[1], "Input Vector");
  display(iobuf[2], sz[2], "Input Text");
  display(iobuf[3], sz[3], "Expected Cipher");
  e = _crpt.__sifr_hight_cbc_encode(h, iobuf[0], sz[0], iobuf[1], sz[1], iobuf[2], sz[2], obuf[0], 4096, sifr_hight_callback, &_crpt);
  print_status(h, "__sifr_hight_cbc_encode", e);
  display(obuf[0], e, "HIGHT CBC ENCODE");
  e = _crpt.__sifr_hight_cbc_decode(h, iobuf[0], sz[0], iobuf[1], sz[1], obuf[0], e, obuf[1], 4096, sifr_hight_callback, &_crpt);
  print_status(h, "__sifr_hight_cbc_decode", e);
  display(obuf[1], e, "HIGHT CBC DECODE");



  BOX("HIGHT CFB CHECK");
  sz[0] = ascii_to_hex( KISA_KEY_HIGHT_CFB[0][0], iobuf[0]);
  sz[1] = ascii_to_hex( KISA_KEY_HIGHT_CFB[0][1], iobuf[1]);
  sz[2] = ascii_to_hex( KISA_KEY_HIGHT_CFB[0][2], iobuf[2]);
  sz[3] = ascii_to_hex( KISA_KEY_HIGHT_CFB[0][3], iobuf[3]);
  display(iobuf[0], sz[0], "Input Key");
  display(iobuf[1], sz[1], "Input Vector");
  display(iobuf[2], sz[2], "Input Text");
  display(iobuf[3], sz[3], "Expected Cipher");
  e = _crpt.__sifr_hight_cfb_encode(h, iobuf[0], sz[0], iobuf[1], sz[1], iobuf[2], sz[2], obuf[0], 4096, sifr_hight_callback, &_crpt);
  print_status(h, "__sifr_hight_cfb_encode", e);
  display(obuf[0], e, "HIGHT CFB ENCODE");
  e = _crpt.__sifr_hight_cfb_decode(h, iobuf[0], sz[0], iobuf[1], sz[1], obuf[0], e, obuf[1], 4096, sifr_hight_callback, &_crpt);
  print_status(h, "__sifr_hight_cfb_decode", e);
  display(obuf[1], e, "HIGHT CFB DECODE");



  BOX("HIGHT OFB CHECK");
  sz[0] = ascii_to_hex( KISA_KEY_HIGHT_OFB[0][0], iobuf[0]);
  sz[1] = ascii_to_hex( KISA_KEY_HIGHT_OFB[0][1], iobuf[1]);
  sz[2] = ascii_to_hex( KISA_KEY_HIGHT_OFB[0][2], iobuf[2]);
  sz[3] = ascii_to_hex( KISA_KEY_HIGHT_OFB[0][3], iobuf[3]);
  display(iobuf[0], sz[0], "Input Key");
  display(iobuf[1], sz[1], "Input Vector");
  display(iobuf[2], sz[2], "Input Text");
  display(iobuf[3], sz[3], "Expected Cipher");
  e = _crpt.__sifr_hight_ofb_encode(h, iobuf[0], sz[0], iobuf[1], sz[1], iobuf[2], sz[2], obuf[0], 4096, sifr_hight_callback, &_crpt);
  print_status(h, "__sifr_hight_ofb_encode", e);
  display(obuf[0], e, "HIGHT OFB ENCODE");
  e = _crpt.__sifr_hight_ofb_decode(h, iobuf[0], sz[0], iobuf[1], sz[1], obuf[0], e, obuf[1], 4096, sifr_hight_callback, &_crpt);
  print_status(h, "__sifr_hight_ofb_decode", e);
  display(obuf[1], e, "HIGHT OFB DECODE");




  BOX("HIGHT CTR CHECK");
  sz[0] = ascii_to_hex( KISA_KEY_HIGHT_CTR[0][0], iobuf[0]);
  sz[1] = ascii_to_hex( KISA_KEY_HIGHT_CTR[0][1], iobuf[1]);
  sz[2] = ascii_to_hex( KISA_KEY_HIGHT_CTR[0][2], iobuf[2]);
  sz[3] = ascii_to_hex( KISA_KEY_HIGHT_CTR[0][3], iobuf[3]);
  display(iobuf[0], sz[0], "Input Key");
  display(iobuf[1], sz[1], "Input Vector");
  display(iobuf[2], sz[2], "Input Text");
  display(iobuf[3], sz[3], "Expected Cipher");
  e = _crpt.__sifr_hight_ctr_encode(h, iobuf[0], sz[0], iobuf[1], sz[1], iobuf[2], sz[2], obuf[0], 4096, sifr_hight_callback, &_crpt);
  print_status(h, "__sifr_hight_ctr_encode", e);
  display(obuf[0], e, "HIGHT CTR ENCODE");
  e = _crpt.__sifr_hight_ctr_decode(h, iobuf[0], sz[0], iobuf[1], sz[1], obuf[0], e, obuf[1], 4096, sifr_hight_callback, &_crpt);
  print_status(h, "__sifr_hight_ctr_decode", e);
  display(obuf[1], e, "HIGHT CTR DECODE");


  #endif



  #if 1 //__SHA2__
  BOX("SHA2 CHECK");
  sz[0] = ascii_to_hex(KISA_KEY_SHA2_256_S[0][0], iobuf[0]);
  sz[1] = ascii_to_hex(KISA_KEY_SHA2_256_S[0][1], iobuf[1]);
  display(iobuf[0], sz[0], "Input Text");
  display(iobuf[1], sz[1], "Expected HASH");
  e = _crpt.__sifr_sha2(h, iobuf[0], sz[0], obuf[0], 4096, sifr_sha2_callback, &_crpt);
  print_status(h, "__sifr_sha2", e);
  display(obuf[0], e, "SHA2 256 HASH");


  #endif



  #if 1 //__HMAC__
  BOX("HMAC CHECK");
  sz[0] = ascii_to_hex(KISA_KEY_HMAC_SHA256[0][3], iobuf[0]);
  sz[1] = ascii_to_hex(KISA_KEY_HMAC_SHA256[0][4], iobuf[1]);
  sz[2] = ascii_to_hex(KISA_KEY_HMAC_SHA256[0][5], iobuf[2]);
  display(iobuf[0], sz[0], "Input Key");
  display(iobuf[1], sz[1], "Input Text");
  display(iobuf[2], sz[2], "Expected HASH");
  e = _crpt.__sifr_hmac(h, iobuf[0], sz[0], iobuf[1], sz[1],  obuf[0], 4096, sifr_hmac_callback, &_crpt);
  print_status(h, "__sifr_hmac", e);
  display(obuf[0], e, "HMAC SHA2 256 HASH");


  #endif

  #if 1 //__LSH256__
  BOX("LSH 256 224 CHECK");
  sz[0] = ascii_to_hex(KISA_KEY_LSH256_224_S[1][0], iobuf[0]); /// convert to size of bit from sz[0] is byte
  sz[1] = ascii_to_hex(KISA_KEY_LSH256_224_S[1][1], iobuf[1]);
  display(iobuf[0], sz[0], "Input Text");
  display(iobuf[1], sz[1], "Expected HASH");
  e = _crpt.__sifr_lsh256_224(h, iobuf[0], sz[0]*8, obuf[0], 4096, sifr_lsh256_callback, &_crpt);
  print_status(h, "__sifr_lsh256_224", e);
  display(obuf[0], e, "LSH256 224 MD");


  BOX("LSH 256 256 CHECK");
  sz[0] = ascii_to_hex(KISA_KEY_LSH256_256_S[1][0], iobuf[0]); /// convert to size of bit from sz[0] is byte
  sz[1] = ascii_to_hex(KISA_KEY_LSH256_256_S[1][1], iobuf[1]);
  display(iobuf[0], sz[0], "Input Text");
  display(iobuf[1], sz[1], "Expected HASH");
  e = _crpt.__sifr_lsh256_256(h, iobuf[0], sz[0]*8, obuf[0], 4096, sifr_lsh256_callback, &_crpt);
  print_status(h, "__sifr_lsh256_256", e);
  display(obuf[0], e, "LSH256 256 MD");


  #endif

  #if 1 //__LSH512__
  BOX("LSH 512 224 CHECK");
  sz[0] = ascii_to_hex(KISA_KEY_LSH512_224_S[1][0], iobuf[0]); /// convert to size of bit from sz[0] is byte
  sz[1] = ascii_to_hex(KISA_KEY_LSH512_224_S[1][1], iobuf[1]);
  display(iobuf[0], sz[0], "Input Text");
  display(iobuf[1], sz[1], "Expected HASH");
  e = _crpt.__sifr_lsh512_224(h, iobuf[0], sz[0]*8, obuf[0], 4096, sifr_lsh512_callback, &_crpt);
  print_status(h, "__sifr_lsh512_224", e);
  display(obuf[0], e, "LSH512 224 MD");


  BOX("LSH 512 256 CHECK");
  sz[0] = ascii_to_hex(KISA_KEY_LSH512_256_S[1][0], iobuf[0]); /// convert to size of bit from sz[0] is byte
  sz[1] = ascii_to_hex(KISA_KEY_LSH512_256_S[1][1], iobuf[1]);
  display(iobuf[0], sz[0], "Input Text");
  display(iobuf[1], sz[1], "Expected HASH");
  e = _crpt.__sifr_lsh512_256(h, iobuf[0], sz[0]*8, obuf[0], 4096, sifr_lsh512_callback, &_crpt);
  print_status(h, "__sifr_lsh512_256", e);
  display(obuf[0], e, "LSH512 256 MD");


  BOX("LSH 512 384 CHECK");
  sz[0] = ascii_to_hex(KISA_KEY_LSH512_384_S[1][0], iobuf[0]); /// convert to size of bit from sz[0] is byte
  sz[1] = ascii_to_hex(KISA_KEY_LSH512_384_S[1][1], iobuf[1]);
  display(iobuf[0], sz[0], "Input Text");
  display(iobuf[1], sz[1], "Expected HASH");
  e = _crpt.__sifr_lsh512_384(h, iobuf[0], sz[0]*8, obuf[0], 4096, sifr_lsh512_callback, &_crpt);
  print_status(h, "__sifr_lsh512_384", e);
  display(obuf[0], e, "LSH512 384 MD");



  BOX("LSH 512 512 CHECK");
  sz[0] = ascii_to_hex(KISA_KEY_LSH512_512_S[1][0], iobuf[0]); /// convert to size of bit from sz[0] is byte
  sz[1] = ascii_to_hex(KISA_KEY_LSH512_512_S[1][1], iobuf[1]);
  display(iobuf[0], sz[0], "Input Text");
  display(iobuf[1], sz[1], "Expected HASH");
  e = _crpt.__sifr_lsh512_512(h, iobuf[0], sz[0]*8, obuf[0], 4096, sifr_lsh512_callback, &_crpt);
  print_status(h, "__sifr_lsh512_512", e);
  display(obuf[0], e, "LSH512 512 MD");



  #endif



  #endif



  e = _crpt.__sifr_release(&h);
  printf(" e : %08X \r\n", e);

}




void main(int argc, char** argv)
{
  void* hdl = 0;
  int32_t e = 0;

  printf(" MODULE -> %s \r\n", MODULE);

  #if defined LINUX
  _crpt.sz = loadBinary("./sifr.kit.so", &_crpt.p);
  #endif

  #if defined WIN32
  _crpt.sz = loadBinary("./sifr.kit.dll", &_crpt.p);
  #endif
  printf(" loaded size : %d \r\n", _crpt.sz);

  #if defined LINUX
  hdl = dlopen("./sifr.kit.so", RTLD_LAZY);
  if ( hdl == 0 )
  {
    printf("dlopen Fail %s\r\n", dlerror());
    return;
  }
  _crpt.__sifr_init               = dlsym(hdl,"__sifr_init");
  _crpt.__sifr_release            = dlsym(hdl,"__sifr_release");
  _crpt.__sifr_version            = dlsym(hdl,"__sifr_version");
  _crpt.__sifr_author             = dlsym(hdl,"__sifr_author");
  _crpt.__sifr_module             = dlsym(hdl,"__sifr_module");
  _crpt.__sifr_set_callback       = dlsym(hdl,"__sifr_set_callback");

  _crpt.__sifr_base64             = dlsym(hdl,"__sifr_base64");

  _crpt.__sifr_noise_source       = dlsym(hdl,"__sifr_noise_source");
  _crpt.__sifr_entropy            = dlsym(hdl,"__sifr_entropy");
  _crpt.__sifr_drbg               = dlsym(hdl,"__sifr_drbg");
  _crpt.__sifr_random             = dlsym(hdl,"__sifr_random");
  _crpt.__sifr_key                = dlsym(hdl,"__sifr_key");
  _crpt.__sifr_self_check         = dlsym(hdl,"__sifr_self_check");
  _crpt.__sifr_kat_check          = dlsym(hdl,"__sifr_kat_check");
  _crpt.__sifr_integrity_check    = dlsym(hdl,"__sifr_integrity_check");

  _crpt.__sifr_mem_clear          = dlsym(hdl,"__sifr_mem_clear");


  _crpt.__sifr_last_status        = dlsym(hdl,"__sifr_last_status");
  _crpt.__sifr_last_status_string = dlsym(hdl,"__sifr_last_status_string");


  _crpt.__sifr_aria_ecb_encode  = dlsym(hdl,"__sifr_aria_ecb_encode");
  _crpt.__sifr_aria_ecb_decode  = dlsym(hdl,"__sifr_aria_ecb_decode");
  _crpt.__sifr_aria_cbc_encode  = dlsym(hdl,"__sifr_aria_cbc_encode");
  _crpt.__sifr_aria_cbc_decode  = dlsym(hdl,"__sifr_aria_cbc_decode");
  _crpt.__sifr_aria_cfb_encode  = dlsym(hdl,"__sifr_aria_cfb_encode");
  _crpt.__sifr_aria_cfb_decode  = dlsym(hdl,"__sifr_aria_cfb_decode");
  _crpt.__sifr_aria_ofb_encode  = dlsym(hdl,"__sifr_aria_ofb_encode");
  _crpt.__sifr_aria_ofb_decode  = dlsym(hdl,"__sifr_aria_ofb_decode");
  _crpt.__sifr_aria_ctr_encode  = dlsym(hdl,"__sifr_aria_ctr_encode");
  _crpt.__sifr_aria_ctr_decode  = dlsym(hdl,"__sifr_aria_ctr_decode");
  _crpt.__sifr_aria_ccm_encode  = dlsym(hdl,"__sifr_aria_ccm_encode");
  _crpt.__sifr_aria_ccm_decode  = dlsym(hdl,"__sifr_aria_ccm_decode");

  _crpt.__sifr_lea_ecb_encode  = dlsym(hdl,"__sifr_lea_ecb_encode");
  _crpt.__sifr_lea_ecb_decode  = dlsym(hdl,"__sifr_lea_ecb_decode");
  _crpt.__sifr_lea_cbc_encode  = dlsym(hdl,"__sifr_lea_cbc_encode");
  _crpt.__sifr_lea_cbc_decode  = dlsym(hdl,"__sifr_lea_cbc_decode");
  _crpt.__sifr_lea_cfb_encode  = dlsym(hdl,"__sifr_lea_cfb_encode");
  _crpt.__sifr_lea_cfb_decode  = dlsym(hdl,"__sifr_lea_cfb_decode");
  _crpt.__sifr_lea_ofb_encode  = dlsym(hdl,"__sifr_lea_ofb_encode");
  _crpt.__sifr_lea_ofb_decode  = dlsym(hdl,"__sifr_lea_ofb_decode");
  _crpt.__sifr_lea_ctr_encode  = dlsym(hdl,"__sifr_lea_ctr_encode");
  _crpt.__sifr_lea_ctr_decode  = dlsym(hdl,"__sifr_lea_ctr_decode");

  _crpt.__sifr_seed_ecb_encode  = dlsym(hdl,"__sifr_seed_ecb_encode");
  _crpt.__sifr_seed_ecb_decode  = dlsym(hdl,"__sifr_seed_ecb_decode");
  _crpt.__sifr_seed_cbc_encode  = dlsym(hdl,"__sifr_seed_cbc_encode");
  _crpt.__sifr_seed_cbc_decode  = dlsym(hdl,"__sifr_seed_cbc_decode");
  _crpt.__sifr_seed_cfb_encode  = dlsym(hdl,"__sifr_seed_cfb_encode");
  _crpt.__sifr_seed_cfb_decode  = dlsym(hdl,"__sifr_seed_cfb_decode");
  _crpt.__sifr_seed_ofb_encode  = dlsym(hdl,"__sifr_seed_ofb_encode");
  _crpt.__sifr_seed_ofb_decode  = dlsym(hdl,"__sifr_seed_ofb_decode");
  _crpt.__sifr_seed_ctr_encode  = dlsym(hdl,"__sifr_seed_ctr_encode");
  _crpt.__sifr_seed_ctr_decode  = dlsym(hdl,"__sifr_seed_ctr_decode");

  _crpt.__sifr_hight_ecb_encode  = dlsym(hdl,"__sifr_hight_ecb_encode");
  _crpt.__sifr_hight_ecb_decode  = dlsym(hdl,"__sifr_hight_ecb_decode");
  _crpt.__sifr_hight_cbc_encode  = dlsym(hdl,"__sifr_hight_cbc_encode");
  _crpt.__sifr_hight_cbc_decode  = dlsym(hdl,"__sifr_hight_cbc_decode");
  _crpt.__sifr_hight_cfb_encode  = dlsym(hdl,"__sifr_hight_cfb_encode");
  _crpt.__sifr_hight_cfb_decode  = dlsym(hdl,"__sifr_hight_cfb_decode");
  _crpt.__sifr_hight_ofb_encode  = dlsym(hdl,"__sifr_hight_ofb_encode");
  _crpt.__sifr_hight_ofb_decode  = dlsym(hdl,"__sifr_hight_ofb_decode");
  _crpt.__sifr_hight_ctr_encode  = dlsym(hdl,"__sifr_hight_ctr_encode");
  _crpt.__sifr_hight_ctr_decode  = dlsym(hdl,"__sifr_hight_ctr_decode");

  _crpt.__sifr_sha2    = dlsym(hdl,"__sifr_sha2");
  _crpt.__sifr_hmac    = dlsym(hdl,"__sifr_hmac");
  _crpt.__sifr_lsh256_224  = dlsym(hdl,"__sifr_lsh256_224");
  _crpt.__sifr_lsh256_256  = dlsym(hdl,"__sifr_lsh256_256");
  _crpt.__sifr_lsh512_224  = dlsym(hdl,"__sifr_lsh512_224");
  _crpt.__sifr_lsh512_256  = dlsym(hdl,"__sifr_lsh512_256");
  _crpt.__sifr_lsh512_384  = dlsym(hdl,"__sifr_lsh512_384");
  _crpt.__sifr_lsh512_512  = dlsym(hdl,"__sifr_lsh512_512");

  _crpt.setMessage  = dlsym(hdl,"__setMessage");
  _crpt.putMessage  = dlsym(hdl,"__putMessage");
  #endif

  #if defined WIN32
  hdl = LoadLibrary(MODULE);
  if ( hdl == 0 )
  {
    printf("LoadLibrary Fail\r\n");
    return;
  }
  *(FARPROC*)&_crpt.__sifr_init             = GetProcAddress(hdl,"__sifr_init");
  *(FARPROC*)&_crpt.__sifr_release          = GetProcAddress(hdl,"__sifr_release");
  *(FARPROC*)&_crpt.__sifr_version          = GetProcAddress(hdl,"__sifr_version");
  *(FARPROC*)&_crpt.__sifr_author           = GetProcAddress(hdl,"__sifr_author");
  *(FARPROC*)&_crpt.__sifr_module           = GetProcAddress(hdl,"__sifr_module");
  *(FARPROC*)&_crpt.__sifr_set_callback     = GetProcAddress(hdl,"__sifr_set_callback");

  *(FARPROC*)&_crpt.__sifr_base64           = GetProcAddress(hdl,"__sifr_base64");

  *(FARPROC*)&_crpt.__sifr_noise_source     = GetProcAddress(hdl,"__sifr_noise_source");
  *(FARPROC*)&_crpt.__sifr_entropy          = GetProcAddress(hdl,"__sifr_entropy");
  *(FARPROC*)&_crpt.__sifr_drbg             = GetProcAddress(hdl,"__sifr_drbg");
  *(FARPROC*)&_crpt.__sifr_random           = GetProcAddress(hdl,"__sifr_random");
  *(FARPROC*)&_crpt.__sifr_key              = GetProcAddress(hdl,"__sifr_key");
  *(FARPROC*)&_crpt.__sifr_self_check       = GetProcAddress(hdl,"__sifr_self_check");
  *(FARPROC*)&_crpt.__sifr_kat_check        = GetProcAddress(hdl,"__sifr_kat_check");
  *(FARPROC*)&_crpt.__sifr_integrity_check  = GetProcAddress(hdl,"__sifr_integrity_check");

  *(FARPROC*)&_crpt.__sifr_mem_clear        = GetProcAddress(hdl,"__sifr_mem_clear");

  *(FARPROC*)&_crpt.__sifr_last_status         = GetProcAddress(hdl,"__sifr_last_status");
  *(FARPROC*)&_crpt.__sifr_last_status_string  = GetProcAddress(hdl,"__sifr_last_status_string");

  *(FARPROC*)&_crpt.__sifr_aria_ecb_encode  = GetProcAddress(hdl,"__sifr_aria_ecb_encode");
  *(FARPROC*)&_crpt.__sifr_aria_ecb_decode  = GetProcAddress(hdl,"__sifr_aria_ecb_decode");
  *(FARPROC*)&_crpt.__sifr_aria_cbc_encode  = GetProcAddress(hdl,"__sifr_aria_cbc_encode");
  *(FARPROC*)&_crpt.__sifr_aria_cbc_decode  = GetProcAddress(hdl,"__sifr_aria_cbc_decode");
  *(FARPROC*)&_crpt.__sifr_aria_cfb_encode  = GetProcAddress(hdl,"__sifr_aria_cfb_encode");
  *(FARPROC*)&_crpt.__sifr_aria_cfb_decode  = GetProcAddress(hdl,"__sifr_aria_cfb_decode");
  *(FARPROC*)&_crpt.__sifr_aria_ofb_encode  = GetProcAddress(hdl,"__sifr_aria_ofb_encode");
  *(FARPROC*)&_crpt.__sifr_aria_ofb_decode  = GetProcAddress(hdl,"__sifr_aria_ofb_decode");
  *(FARPROC*)&_crpt.__sifr_aria_ctr_encode  = GetProcAddress(hdl,"__sifr_aria_ctr_encode");
  *(FARPROC*)&_crpt.__sifr_aria_ctr_decode  = GetProcAddress(hdl,"__sifr_aria_ctr_decode");
  *(FARPROC*)&_crpt.__sifr_aria_ccm_encode  = GetProcAddress(hdl,"__sifr_aria_ccm_encode");
  *(FARPROC*)&_crpt.__sifr_aria_ccm_decode  = GetProcAddress(hdl,"__sifr_aria_ccm_decode");

  *(FARPROC*)&_crpt.__sifr_lea_ecb_encode  = GetProcAddress(hdl,"__sifr_lea_ecb_encode");
  *(FARPROC*)&_crpt.__sifr_lea_ecb_decode  = GetProcAddress(hdl,"__sifr_lea_ecb_decode");
  *(FARPROC*)&_crpt.__sifr_lea_cbc_encode  = GetProcAddress(hdl,"__sifr_lea_cbc_encode");
  *(FARPROC*)&_crpt.__sifr_lea_cbc_decode  = GetProcAddress(hdl,"__sifr_lea_cbc_decode");
  *(FARPROC*)&_crpt.__sifr_lea_cfb_encode  = GetProcAddress(hdl,"__sifr_lea_cfb_encode");
  *(FARPROC*)&_crpt.__sifr_lea_cfb_decode  = GetProcAddress(hdl,"__sifr_lea_cfb_decode");
  *(FARPROC*)&_crpt.__sifr_lea_ofb_encode  = GetProcAddress(hdl,"__sifr_lea_ofb_encode");
  *(FARPROC*)&_crpt.__sifr_lea_ofb_decode  = GetProcAddress(hdl,"__sifr_lea_ofb_decode");
  *(FARPROC*)&_crpt.__sifr_lea_ctr_encode  = GetProcAddress(hdl,"__sifr_lea_ctr_encode");
  *(FARPROC*)&_crpt.__sifr_lea_ctr_decode  = GetProcAddress(hdl,"__sifr_lea_ctr_decode");

  *(FARPROC*)&_crpt.__sifr_seed_ecb_encode  = GetProcAddress(hdl,"__sifr_seed_ecb_encode");
  *(FARPROC*)&_crpt.__sifr_seed_ecb_decode  = GetProcAddress(hdl,"__sifr_seed_ecb_decode");
  *(FARPROC*)&_crpt.__sifr_seed_cbc_encode  = GetProcAddress(hdl,"__sifr_seed_cbc_encode");
  *(FARPROC*)&_crpt.__sifr_seed_cbc_decode  = GetProcAddress(hdl,"__sifr_seed_cbc_decode");
  *(FARPROC*)&_crpt.__sifr_seed_cfb_encode  = GetProcAddress(hdl,"__sifr_seed_cfb_encode");
  *(FARPROC*)&_crpt.__sifr_seed_cfb_decode  = GetProcAddress(hdl,"__sifr_seed_cfb_decode");
  *(FARPROC*)&_crpt.__sifr_seed_ofb_encode  = GetProcAddress(hdl,"__sifr_seed_ofb_encode");
  *(FARPROC*)&_crpt.__sifr_seed_ofb_decode  = GetProcAddress(hdl,"__sifr_seed_ofb_decode");
  *(FARPROC*)&_crpt.__sifr_seed_ctr_encode  = GetProcAddress(hdl,"__sifr_seed_ctr_encode");
  *(FARPROC*)&_crpt.__sifr_seed_ctr_decode  = GetProcAddress(hdl,"__sifr_seed_ctr_decode");

  *(FARPROC*)&_crpt.__sifr_hight_ecb_encode  = GetProcAddress(hdl,"__sifr_hight_ecb_encode");
  *(FARPROC*)&_crpt.__sifr_hight_ecb_decode  = GetProcAddress(hdl,"__sifr_hight_ecb_decode");
  *(FARPROC*)&_crpt.__sifr_hight_cbc_encode  = GetProcAddress(hdl,"__sifr_hight_cbc_encode");
  *(FARPROC*)&_crpt.__sifr_hight_cbc_decode  = GetProcAddress(hdl,"__sifr_hight_cbc_decode");
  *(FARPROC*)&_crpt.__sifr_hight_cfb_encode  = GetProcAddress(hdl,"__sifr_hight_cfb_encode");
  *(FARPROC*)&_crpt.__sifr_hight_cfb_decode  = GetProcAddress(hdl,"__sifr_hight_cfb_decode");
  *(FARPROC*)&_crpt.__sifr_hight_ofb_encode  = GetProcAddress(hdl,"__sifr_hight_ofb_encode");
  *(FARPROC*)&_crpt.__sifr_hight_ofb_decode  = GetProcAddress(hdl,"__sifr_hight_ofb_decode");
  *(FARPROC*)&_crpt.__sifr_hight_ctr_encode  = GetProcAddress(hdl,"__sifr_hight_ctr_encode");
  *(FARPROC*)&_crpt.__sifr_hight_ctr_decode  = GetProcAddress(hdl,"__sifr_hight_ctr_decode");

  *(FARPROC*)&_crpt.__sifr_sha2    = GetProcAddress(hdl,"__sifr_sha2");
  *(FARPROC*)&_crpt.__sifr_hmac    = GetProcAddress(hdl,"__sifr_hmac");
  *(FARPROC*)&_crpt.__sifr_lsh256_224  = GetProcAddress(hdl,"__sifr_lsh256_224");
  *(FARPROC*)&_crpt.__sifr_lsh256_256  = GetProcAddress(hdl,"__sifr_lsh256_256");
  *(FARPROC*)&_crpt.__sifr_lsh512_224  = GetProcAddress(hdl,"__sifr_lsh512_224");
  *(FARPROC*)&_crpt.__sifr_lsh512_256  = GetProcAddress(hdl,"__sifr_lsh512_256");
  *(FARPROC*)&_crpt.__sifr_lsh512_384  = GetProcAddress(hdl,"__sifr_lsh512_384");
  *(FARPROC*)&_crpt.__sifr_lsh512_512  = GetProcAddress(hdl,"__sifr_lsh512_512");


  *(FARPROC*)&_crpt.setMessage  = GetProcAddress(hdl,"__setMessage");
  *(FARPROC*)&_crpt.putMessage  = GetProcAddress(hdl,"__putMessage");
  #endif
  printf(" %s %s\r\n", MODULE, hdl?"SUCCESS":"FAIL");



  sifrkit(argc, argv);
  //sifrkit_check_noise(argc, argv);
  //sifrkit_VNV(argc, argv);
  //sha3_main();
  //kbkdf_main(); 
  //kcdsa_main();
  //ec_kcdsa_main();
  

  {
    int32_t i = 3;
    for ( ; i>0; i-- )
    {
      printf(" %d \r\n", i);
      #if defined WIN32
      Sleep(1);
      #endif

      #if defined LINUX
      usleep(100);
      #endif
    }
  }

  #if defined LINUX
  dlclose(hdl);
  #endif

  #if defined WIN32
  FreeLibrary(hdl);
  #endif

}

