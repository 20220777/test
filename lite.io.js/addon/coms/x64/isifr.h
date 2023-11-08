/*****************************************************************************/
/*                                                                           */
/*            NCLab (Networked Control Lab) CORE version 1.0                 */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
/*  File Name         : isifr.h                                              */
/*                                                                           */
/*  Description       : This file contains all the necessary constants ,     */
/*                      type definitions according to CAST specifications,	 */
/*                      common system headers.                               */
/*                                                                           */
/*                                                                           */
/*  Issues / Problems : None                                                 */
/*                                                                           */
/*  Revision History  :                                                      */
/*                                                                           */
/*        DD MM YYYY   Author(s)        Changes (Describe the changes made)  */
/*        18 03 2021   Shin Seunghyeok  Draft                                */
/*                                                                           */
/*****************************************************************************/
#ifndef __ISIFR_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __ISIFR_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#include <stdint.h>
#include <icommon.h>





///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////                                                                   //////
//////                                                                   //////
//////                          User Variable                            //////
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


enum
{
  ISIFR_CALLBACK_CONNECTED = 0,
  ISIFR_CALLBACK_DISCONNECTED,
  ISIFR_CALLBACK_OPEN,
  ISIFR_CALLBACK_CLOSE,
  ISIFR_CALLBACK_READ,
  ISIFR_CALLBACK_READFROM,
  ISIFR_CALLBACK_URI,
  ISIFR_CALLBACK_URI_NOT_FOUND,
  ISIFR_CALLBACK_POST,
  ISIFR_CALLBACK_GET,
  ISIFR_CALLBACK_SSL_TLS,
  ISIFR_CALLBACK_SSL_TLS_READ,
  ISIFR_CALLBACK_SSL_TLS_WRITE,
  ISIFR_CALLBACK_PRE_OPEN,
  ISIFR_CALLBACK,
  ISIFR_WRITE,
  ISIFR_FD,
  ISIFR_FDSET,
  ISIFR_FUNCTIONS,
};





///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////                                                                   //////
//////                                                                   //////
//////                              SIFR                                 //////
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
#if __SIFR__
#if __STATIC__


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_init   (void**, int8_t*, int32_t);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_release(void**);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_set_callback(void*, void*, void*);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_last_status(void*, int32_t*, int32_t*);

#if defined __cplusplus
extern "C"
#endif
int8_t* __sifr_last_status_string(int32_t ecode);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_version(void*, int8_t*, int32_t);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_author(void*, int8_t*, int32_t);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_module(void*, int8_t*, int32_t);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_integrity_check(void* h, int8_t* p, int32_t sz);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_kat_check(void* h);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_self_check(void* h, int8_t*, int32_t);



#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_base64(void*, uint8_t*, int32_t, uint8_t, uint8_t*);



#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_mem_clear(void*, uint8_t*, int32_t);




#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_drbg(void*, uint8_t, uint8_t, uint8_t*, int32_t);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_random(void* h, uint8_t* b, int32_t sz);



#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_aria_ecb_encode(void* h, uint8_t* key, int32_t ksz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_aria_ecb_decode(void* h, uint8_t* key, int32_t ksz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_aria_cbc_encode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_aria_cbc_decode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_aria_cfb_encode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_aria_cfb_decode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_aria_ofb_encode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_aria_ofb_decode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_aria_ctr_encode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_aria_ctr_decode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_aria_ccm_encode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);



#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_lea_ecb_encode(void* h, uint8_t* key, int32_t ksz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_lea_ecb_decode(void* h, uint8_t* key, int32_t ksz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_lea_cbc_encode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_lea_cbc_decode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_lea_cfb_encode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_lea_cfb_decode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_lea_ofb_encode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_lea_ofb_decode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_lea_ctr_encode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_lea_ctr_decode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);



#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_seed_ecb_encode(void* h, uint8_t* key, int32_t ksz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_seed_ecb_decode(void* h, uint8_t* key, int32_t ksz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_seed_cbc_encode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_seed_cbc_decode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_seed_cfb_encode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_seed_cfb_decode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_seed_ofb_encode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_seed_ofb_decode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_seed_ctr_encode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_seed_ctr_decode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);



#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_hight_ecb_encode(void* h, uint8_t* key, int32_t ksz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_hight_ecb_decode(void* h, uint8_t* key, int32_t ksz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_hight_cbc_encode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_hight_cbc_decode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_hight_cfb_encode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_hight_cfb_decode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_hight_ofb_encode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_hight_ofb_decode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_hight_ctr_encode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_hight_ctr_decode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_sha2(void* h, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_hmac(void* h, uint8_t* key, int32_t ksz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);



#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_lsh256_224(void* h, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_lsh256_256(void* h, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_lsh512_224(void* h, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_lsh512_256(void* h, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_lsh512_384(void* h, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);


#if defined __cplusplus
extern "C"
#endif
int32_t __sifr_lsh512_512(void* h, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz, void* callback, void* obj);




/////// UTILS
//
//
//#if defined __cplusplus
//extern "C"
//#endif
//int32_t __sifr_noise_source(uint8_t who, uint8_t* o, int32_t s);
//


#endif
#endif





#endif