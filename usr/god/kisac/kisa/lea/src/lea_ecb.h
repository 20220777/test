#include "lea.h"
#include "lea_locl.h"

void MAKE_FUNC(ecb_enc)(unsigned char *ct, const unsigned char *pt, unsigned int pt_len, const LEA_KEY *key)
{
	unsigned int remainBlock = pt_len >> 4;
	printf("%20s,%20s,%8d\r\n", __FILE__,__FUNCTION__,__LINE__);
	if (!key){
		return;
	}
	printf("%20s,%20s,%8d\r\n", __FILE__,__FUNCTION__,__LINE__);

	if (pt_len > 0 && (!pt || !ct)){
		return;
	}
	printf("%20s,%20s,%8d\r\n", __FILE__,__FUNCTION__,__LINE__);

	if (pt_len & 0xf){
		return;
	}
	printf("%20s,%20s,%8d\r\n", __FILE__,__FUNCTION__,__LINE__);

#if MAX_BLK >= 8
	printf("%20s,%20s,%8d\r\n", __FILE__,__FUNCTION__,__LINE__);
	for (; remainBlock >= 8; remainBlock -= 8, pt += 0x80, ct += 0x80){
		lea_encrypt_8block(ct, pt, key);
	}
#endif
#if MAX_BLK >= 4
	printf("%20s,%20s,%8d\r\n", __FILE__,__FUNCTION__,__LINE__);
	for (; remainBlock >= 4; remainBlock -= 4, pt += 0x40, ct += 0x40){
		lea_encrypt_4block(ct, pt, key);
	}
#endif
	printf("%20s,%20s,%8d\r\n", __FILE__,__FUNCTION__,__LINE__);

	for (; remainBlock >= 1; remainBlock -= 1, pt += 0x10, ct += 0x10){
		lea_encrypt_1block(ct, pt, key);
	}

}

void MAKE_FUNC(ecb_dec)(unsigned char *pt, const unsigned char *ct, unsigned int ct_len, const LEA_KEY *key)
{
	unsigned int remainBlock = ct_len >> 4;
	printf("%20s,%20s,%8d\r\n", __FILE__,__FUNCTION__,__LINE__);

	if (!key){
		return;
	}
	printf("%20s,%20s,%8d\r\n", __FILE__,__FUNCTION__,__LINE__);

	if (ct_len > 0 && (!pt || !ct)){
		return;
	}
	printf("%20s,%20s,%8d\r\n", __FILE__,__FUNCTION__,__LINE__);

	if (ct_len & 0xf){
		return;
	}

#if MAX_BLK >= 8
	printf("%20s,%20s,%8d\r\n", __FILE__,__FUNCTION__,__LINE__);
	for (; remainBlock >= 8; remainBlock -= 8, pt += 0x80, ct += 0x80){
		lea_decrypt_8block(pt, ct, key);
	}
#endif
#if MAX_BLK >= 4
	printf("%20s,%20s,%8d\r\n", __FILE__,__FUNCTION__,__LINE__);
	for (; remainBlock >= 4; remainBlock -= 4, pt += 0x40, ct += 0x40){
		lea_decrypt_4block(pt, ct, key);
	}
#endif
	printf("%20s,%20s,%8d\r\n", __FILE__,__FUNCTION__,__LINE__);
	for (; remainBlock >= 1; remainBlock -= 1, pt += 0x10, ct += 0x10){
		lea_decrypt_1block(pt, ct, key);
	}
	printf("%20s,%20s,%8d\r\n", __FILE__,__FUNCTION__,__LINE__);

}
