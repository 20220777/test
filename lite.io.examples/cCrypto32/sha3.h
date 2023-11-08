#ifndef _SHA3_H_
#define _SHA3_H_


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>



#ifdef __cplusplus
extern "C" 
{
#endif
	   


int32_t sha3_hash(uint8_t *output, int32_t outLen, uint8_t *input, int32_t inLen, int32_t bitSize, int32_t useSHAKE);

void sha3_main();

#else

#endif
