#ifndef ___SIFR_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define ___SIFR_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <Windows.h>

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


  void* h;

} _sifr;
#if defined WIN32
#pragma pack()
#endif

int32_t load_sifr_kit(HWND h, _sifr* p, uint8_t* path);

#endif
