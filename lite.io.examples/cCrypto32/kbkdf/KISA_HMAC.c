#include "KISA_HMAC.h"


// HMAC_H(message, K) == H(K ^ opad, H(K ^ ipad, message))
// H : HASH Fuction (SHA256)
// int SEED_Generate_CMAC(unsigned char* pMAC, int macLen, unsigned char* pIn, int inLen, unsigned char* mKey)
// void HMAC_SHA256(u8 *hmac, int macLen, unsiged char* message int mlen, const u8 *key)
void HMAC_SHA256(const u8 *message, u32 mlen, const u8 *key, u32 klen, u8 hmac[KISA_SHA256_DIGEST_VALUELEN])
{
	KISA_SHA256_INFO hash_ctx;
	u8 ipad = 0x36, opad = 0x5c;
	int32_t i = 0;
	u8 tk[KISA_SHA256_DIGEST_VALUELEN], tb[KISA_SHA256_DIGEST_BLOCKLEN];
	
	if (klen > KISA_SHA256_DIGEST_BLOCKLEN)
	{
		KISA_SHA256_Encrpyt(key, klen, tk);
		klen = KISA_SHA256_DIGEST_VALUELEN;
		key = tk;
	}

	for (i = 0; i < klen; i++)	tb[i] = ipad ^ key[i];
	for (i = klen; i < KISA_SHA256_DIGEST_BLOCKLEN; i++)	tb[i] = ipad ^ 0;

	KISA_SHA256_Init(&hash_ctx);
	KISA_SHA256_Process(&hash_ctx, tb, KISA_SHA256_DIGEST_BLOCKLEN);
	KISA_SHA256_Process(&hash_ctx, message, mlen);
	KISA_SHA256_Close(&hash_ctx, hmac);

	for (i = 0; i < klen; i++)	tb[i] = opad ^ key[i];
	for (i = klen; i < KISA_SHA256_DIGEST_BLOCKLEN; i++)	tb[i] = opad ^ 0;

	KISA_SHA256_Init(&hash_ctx);
	KISA_SHA256_Process(&hash_ctx, tb, KISA_SHA256_DIGEST_BLOCKLEN);
	KISA_SHA256_Process(&hash_ctx, hmac, KISA_SHA256_DIGEST_VALUELEN);
	KISA_SHA256_Close(&hash_ctx, hmac);
}
