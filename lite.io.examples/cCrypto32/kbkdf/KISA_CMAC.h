#ifndef _KISA_CMAC_H_
#define _KISA_CMAC_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif
	void SEED_CMAC_SubkeySched(uint8_t* sKey);
	int32_t SEED_Generate_CMAC(uint8_t* pMAC, int32_t macLen, uint8_t* pIn, int32_t inLen, uint8_t* mKey);
	int32_t SEED_Verify_CMAC(uint8_t* pMAC, int32_t macLen, uint8_t* pIn, int32_t inLen, uint8_t* mKey);
#ifdef __cplusplus
}
#endif

#else
#endif