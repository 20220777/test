#ifndef _SEED_CCM_C_H_
#define _SEED_CCM_C_H_


// include header
#include <dbgbuffer.h>


// define
#define BLOCK_SIZE_SEED         16


// function declare
#ifdef __cplusplus
extern "C" 
{
#endif
void SEED_CCM_KeySched(unsigned char *mKey, unsigned int *rKey );
void SEED_CCM_Encrypt(unsigned int *pOut, unsigned int *pIn, unsigned int *rKey);
void SEED_CCM_Decrypt(unsigned int *pOut, unsigned int *pIn, unsigned int *rKey);
#ifdef __cplusplus
}
#endif



#else
#endif
