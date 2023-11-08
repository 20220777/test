#ifndef _KISA_SEED_H_
#define _KISA_SEED_H_

#include <stdint.h>

// include header


// define
#define BLOCK_SIZE_SEED         16


// function declare
#ifdef __cplusplus
extern "C"
{
#endif
	void SEED_KeySched(uint8_t* mKey, uint32_t* rKey);
	void SEED_Encrypt(uint32_t* pOut, uint32_t* pIn, uint32_t* rKey);
	void SEED_Decrypt(uint32_t* pOut, uint32_t* pIn, uint32_t* rKey);
	void Byte2Word(uint32_t* dst, const uint8_t* src, const int32_t srcLen);
	void Word2Byte(uint8_t* dst, const uint32_t* src, const int32_t srcLen);
#ifdef __cplusplus
}
#endif



#else
#endif
