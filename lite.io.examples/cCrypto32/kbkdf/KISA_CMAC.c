
#include <memory.h>
#include <stdlib.h>
#include <assert.h>
#include "KISA_SEED.h"

void SEED_CMAC_SubkeySched(uint8_t* sKey)
{
	int32_t i = 0, carry = sKey[0] >> 7;

	for (i = 0; i < 15; i++)
		sKey[i] = (sKey[i] << 1) | (sKey[i + 1] >> 7);

	sKey[i] = sKey[i] << 1;

	if (carry)
		sKey[i] ^= 0x87;
}

int32_t SEED_Generate_CMAC(uint8_t* pMAC, int32_t macLen, uint8_t* pIn, int32_t inLen, uint8_t* mKey)
{
	uint8_t K1[BLOCK_SIZE_SEED] = { 0x00, };
	uint8_t K2[BLOCK_SIZE_SEED] = { 0x00, };

	uint8_t blockTemp[BLOCK_SIZE_SEED] = { 0x00, };
	uint8_t Mm[BLOCK_SIZE_SEED] = { 0x00, };
	uint32_t subKey[BLOCK_SIZE_SEED / 4] = { 0x00, };

	uint32_t encBlock[BLOCK_SIZE_SEED / 4] = { 0x00, };

	uint32_t rKey[32] = { 0x00, };
	int32_t blockLen = 0, remainder = 0, i = 0, j = 0;
	int32_t times = 0;

	if (macLen > BLOCK_SIZE_SEED)
		return 1;

	if (inLen == 0) {
		blockLen = 1;
	}
	else {
		// 아래 코드는 좀 더 깔끔하게 가다듬어야 함
		times = inLen / BLOCK_SIZE_SEED;
		blockLen = times;
		times *= BLOCK_SIZE_SEED;

		if (times < inLen)
		{
			blockLen += 1;
		}
	}

	SEED_KeySched(mKey, rKey);
	SEED_Encrypt(subKey, subKey, rKey);

	Word2Byte(K1, subKey, BLOCK_SIZE_SEED);

	// make K1
	SEED_CMAC_SubkeySched(K1);

	// make K2
	memcpy(K2, K1, sizeof(uint8_t) * BLOCK_SIZE_SEED);
	SEED_CMAC_SubkeySched(K2);

	// Make m-th block
	remainder = inLen % 16;
	if (inLen != 0 && remainder == 0) {
		memcpy(Mm, pIn + (blockLen - 1) * BLOCK_SIZE_SEED, sizeof(uint8_t) * BLOCK_SIZE_SEED);
		for (i = 0; i < BLOCK_SIZE_SEED; i++) {
			Mm[i] ^= K1[i];
		}
	}
	else {
		// 표준에 의거하면 비트단위로 계산되어야 하나
		// CMAC KISA 코드에서 이미 바이트 단위 입력으로 되어있어 아래와 같이 구현함
		memcpy(Mm, pIn + (blockLen - 1) * BLOCK_SIZE_SEED, sizeof(uint8_t) * remainder);
		Mm[remainder] = 0x80;
		for (i = 0; i < BLOCK_SIZE_SEED; i++) {
			Mm[i] ^= K2[i];
		}
	}

	memset(blockTemp, 0, BLOCK_SIZE_SEED);

	// processing 1~(m-1) blocks
	for (i = 0; i < blockLen - 1; i++) {
		for (j = 0; j < BLOCK_SIZE_SEED; j++)
		{
			blockTemp[j] ^= pIn[BLOCK_SIZE_SEED * i + j];
		}

		Word2Byte(encBlock, blockTemp, BLOCK_SIZE_SEED);
		SEED_Encrypt(encBlock, encBlock, rKey);
		Word2Byte(blockTemp, encBlock, BLOCK_SIZE_SEED);
	}

	// processing final block Mm
	for (j = 0; j < BLOCK_SIZE_SEED; j++)
	{
		blockTemp[j] ^= Mm[j];
	}
	Word2Byte(encBlock, blockTemp, BLOCK_SIZE_SEED);
	SEED_Encrypt(encBlock, encBlock, rKey);
	Word2Byte(blockTemp, encBlock, BLOCK_SIZE_SEED);
	memcpy(pMAC, blockTemp, BLOCK_SIZE_SEED);

	return 0;
}

int32_t SEED_Verify_CMAC(uint8_t* pMAC, int32_t macLen, uint8_t* pIn, int32_t inLen, uint8_t* mKey)
{
	uint8_t K1[BLOCK_SIZE_SEED] = { 0x00, };
	uint8_t K2[BLOCK_SIZE_SEED] = { 0x00, };

	uint8_t blockTemp[BLOCK_SIZE_SEED] = { 0x00, };
	uint8_t Mm[BLOCK_SIZE_SEED] = { 0x00, };
	uint32_t subKey[BLOCK_SIZE_SEED / 4] = { 0x00, };

	uint32_t encBlock[BLOCK_SIZE_SEED / 4] = { 0x00, };

	uint32_t rKey[32] = { 0x00, };
	int32_t blockLen = 0, remainder = 0, i = 0, j = 0;
	int32_t times = 0;

	if (macLen > BLOCK_SIZE_SEED)
		return 1;

	if (inLen == 0) {
		blockLen = 1;
	}
	else {
		// 아래 코드는 좀 더 깔끔하게 가다듬어야 함
		times = inLen / BLOCK_SIZE_SEED;
		blockLen = times;
		times *= BLOCK_SIZE_SEED;

		if (times < inLen)
		{
			blockLen += 1;
		}
	}

	SEED_KeySched(mKey, rKey);
	SEED_Encrypt(subKey, subKey, rKey);

	Word2Byte(K1, subKey, BLOCK_SIZE_SEED);

	// make K1
	SEED_CMAC_SubkeySched(K1);

	// make K2
	memcpy(K2, K1, sizeof(uint8_t) * BLOCK_SIZE_SEED);
	SEED_CMAC_SubkeySched(K2);

	// Make m-th block
	remainder = inLen % 16;
	if (inLen != 0 && remainder == 0) {
		memcpy(Mm, pIn + (blockLen - 1) * BLOCK_SIZE_SEED, sizeof(uint8_t) * BLOCK_SIZE_SEED);
		for (i = 0; i < BLOCK_SIZE_SEED; i++) {
			Mm[i] ^= K1[i];
		}
	}
	else {
		// 표준에 의거하면 비트단위로 계산되어야 하나
		// CMAC KISA 코드에서 이미 바이트 단위 입력으로 되어있어 아래와 같이 구현함
		memcpy(Mm, pIn + (blockLen - 1) * BLOCK_SIZE_SEED, sizeof(uint8_t) * remainder);
		Mm[remainder] = 0x80;
		for (i = 0; i < BLOCK_SIZE_SEED; i++) {
			Mm[i] ^= K2[i];
		}
	}

	memset(blockTemp, 0, BLOCK_SIZE_SEED);

	// processing 1~(m-1) blocks
	for (i = 0; i < blockLen - 1; i++) {
		for (j = 0; j < BLOCK_SIZE_SEED; j++)
		{
			blockTemp[j] ^= pIn[BLOCK_SIZE_SEED * i + j];
		}

		Word2Byte(encBlock, blockTemp, BLOCK_SIZE_SEED);
		SEED_Encrypt(encBlock, encBlock, rKey);
		Word2Byte(blockTemp, encBlock, BLOCK_SIZE_SEED);
	}

	// processing final block Mm
	for (j = 0; j < BLOCK_SIZE_SEED; j++)
	{
		blockTemp[j] ^= Mm[j];
	}
	Word2Byte(encBlock, blockTemp, BLOCK_SIZE_SEED);
	SEED_Encrypt(encBlock, encBlock, rKey);
	Word2Byte(blockTemp, encBlock, BLOCK_SIZE_SEED);

	for (i = 0; i < macLen; i++)
		if (pMAC[i] != blockTemp[i])
			return 1;

	return 0;
}

// EOF
