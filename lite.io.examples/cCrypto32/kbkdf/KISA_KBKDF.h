#ifndef _KISA_KBKDF_H_
#define _KISA_KBKDF_H_

#include "KISA_CMAC.h"
#include "KISA_HMAC.h"
#include "common.h"

#define ceiling(x,y) x%y == 0 ? x/y : x/y+1;


void kbkdf_hmac_ctr_mode(
	uint8_t* KI, uint32_t KILen,
	uint32_t r, uint32_t L,
	uint8_t* Label, uint32_t LabelLen, uint8_t* Context, uint32_t ContextLen,
	uint8_t* KO);

void kbkdf_hmac_feedback_mode(
	uint8_t* KI, uint32_t KILen,
	uint32_t r, uint32_t L,
	uint8_t* Label, uint32_t LabelLen,
	uint8_t* Context, uint32_t ContextLen,
	uint8_t* IV, uint32_t IVLen,
	uint8_t* KO);

void kbkdf_hmac_doublepipeline_mode(
	uint8_t* KI, uint32_t KILen,
	uint32_t r, uint32_t L,
	uint8_t* Label, uint32_t LabelLen,
	uint8_t* Context, uint32_t ContextLen,
	uint8_t* KO);


void kbkdf_cmac_ctr_mode(
	uint8_t* KI, uint32_t KILen,
	uint32_t r, uint32_t L,
	uint8_t* Label, uint32_t LabelLen, uint8_t* Context, uint32_t ContextLen,
	uint8_t* KO);

void kbkdf_cmac_feedback_mode(
	uint8_t* KI, uint32_t KILen,
	uint32_t r, uint32_t L,
	uint8_t* Label, uint32_t LabelLen,
	uint8_t* Context, uint32_t ContextLen,
	uint8_t* IV, uint32_t IVLen,
	uint8_t* KO);

void kbkdf_cmac_doublepipeline_mode(
	uint8_t* KI, uint32_t KILen,
	uint32_t r, uint32_t L,
	uint8_t* Label, uint32_t LabelLen,
	uint8_t* Context, uint32_t ContextLen,
	uint8_t* KO);
#else
#endif
