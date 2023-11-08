#ifndef _SEED_CCM_H_
#define _SEED_CCM_H_


// include header


// define
#include <dbgbuffer.h>


// function declare
#ifdef __cplusplus
extern "C" 
{
#endif
int SEED_CCM_Encryption(
    unsigned char *ct, unsigned int *ctLen,
    unsigned char *pt, unsigned int ptLen,
    unsigned int macLen,
    unsigned char *nonce, unsigned int nonceLen,
    unsigned char *aad, unsigned int aadLen,
    unsigned char *mKey);
int SEED_CCM_Decryption(
    unsigned char *pt, unsigned int *ptLen,
    unsigned char *ct, unsigned int ctLen,
    unsigned int macLen,
    unsigned char *nonce, unsigned int nonceLen,
    unsigned char *aad, unsigned int aadLen,
    unsigned char *mKey);


int main_kisa_seed_ccm();    
#ifdef __cplusplus
}
#endif



#else
#endif
