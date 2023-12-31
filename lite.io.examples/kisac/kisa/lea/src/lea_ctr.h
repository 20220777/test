#include "lea.h"
#include "lea_locl.h"

/* increment counter (128-bit int) by 1 */
static void ctr128_inc(unsigned char *counter) {
	unsigned int n=16;
	unsigned char c;

	do {
		--n;
		c = counter[n];
		++c;
		counter[n] = c;
		if (c) return;
	} while (n);
}

static void ctr128_inc_aligned(unsigned char *counter) {
	unsigned int *data,c,n;
	const union { long one; char little; } is_endian = {1};

	printf("%s,%s,%d  -> %d\r\n", __FILE__,__FUNCTION__,__LINE__, is_endian.little);


	if (is_endian.little) {
		ctr128_inc(counter);
		return;
	}

	data = (unsigned int *)counter;
	n = 16/sizeof(unsigned int);
	do {
		--n;
		c = data[n];
		++c;
		data[n] = c;
		if (c) return;
	} while (n);
}

void MAKE_FUNC(ctr_enc)(unsigned char *ct, const unsigned char *pt, unsigned int pt_len, unsigned char *ctr, const LEA_KEY *key)
{
	unsigned char block[128] = {0,};
	unsigned int remainBlock = pt_len >> 4;
	printf("%s,%s,%d\r\n", __FILE__,__FUNCTION__,__LINE__);


	if (!ctr || !key){
		return;
	}

	if (pt_len > 0 && (!ct || !pt)){
		return;
	}

#if MAX_BLK >= 8
	printf("%s,%s,%d\r\n", __FILE__,__FUNCTION__,__LINE__);
	for(;remainBlock>=8; remainBlock-=8, pt += 0x80, ct += 0x80, pt_len -= 0x80){
		CPY8x16(block, ctr);
		ctr128_inc_aligned(ctr);

		CPY8x16(block + 0x10, ctr);
		ctr128_inc_aligned(ctr);

		CPY8x16(block + 0x20, ctr);
		ctr128_inc_aligned(ctr);

		CPY8x16(block + 0x30, ctr);
		ctr128_inc_aligned(ctr);

		CPY8x16(block + 0x40, ctr);
		ctr128_inc_aligned(ctr);

		CPY8x16(block + 0x50, ctr);
		ctr128_inc_aligned(ctr);

		CPY8x16(block + 0x60, ctr);
		ctr128_inc_aligned(ctr);

		CPY8x16(block + 0x70, ctr);
		ctr128_inc_aligned(ctr);

		lea_encrypt_8block(block, block, key);

		XOR8x128(ct, block, pt);
	}
#endif
#if  defined(USE_OWN_FUNC)
	printf("%s,%s,%d\r\n", __FILE__,__FUNCTION__,__LINE__);
	_lea_ctr_enc(ct, pt, pt_len, ctr, key);
#else
#if MAX_BLK >= 4
	printf("%s,%s,%d\r\n", __FILE__,__FUNCTION__,__LINE__);
	for (; remainBlock >= 4; remainBlock -= 4, pt += 0x40, ct += 0x40){
		CPY8x16(block, ctr);
		ctr128_inc_aligned(ctr);

		CPY8x16(block + 0x10, ctr);
		ctr128_inc_aligned(ctr);

		CPY8x16(block + 0x20, ctr);
		ctr128_inc_aligned(ctr);

		CPY8x16(block + 0x30, ctr);
		ctr128_inc_aligned(ctr);

		lea_encrypt_4block(block, block, key);

		XOR8x64(ct, block, pt);
	}
#endif


	{
		int j=0;
		printf("--> pt \r\n");
		for ( j=0 ; j<16 ; j++ ) printf("%s%02X", (j&&((j%8)==0))?"  ":" ", *(pt+j));
		printf("\r\n");
	}

	for (; remainBlock >= 1; remainBlock -= 1, pt += 0x10, ct += 0x10){

		{
			int j=0;
			printf("--> ctr \r\n");
			for ( j=0 ; j<16 ; j++ ) printf("%s%02X", (j&&((j%8)==0))?"  ":" ", *(ctr+j));
			printf("\r\n");
		}
		{
			int j=0;
			printf("--> block \r\n");
			for ( j=0 ; j<16 ; j++ ) printf("%s%02X", (j&&((j%8)==0))?"  ":" ", *(block+j));
			printf("\r\n");
		}
		printf(" round : %d \r\n", key->round);
		{
			int j=0;
			printf("--> key->rk \r\n");
			for ( j=0 ; j<16 ; j++ ) printf("%s%02X", (j&&((j%8)==0))?"  ":" ", *(key->rk+j));
			printf("\r\n");
		}

		lea_encrypt_1block(block, ctr, key);
		{
			int j=0;
			printf("block <--------------------------\r\n");
			for ( j=0 ; j<16 ; j++ ) printf("%s%02X", (j&&((j%8)==0))?"  ":" ", *(block+j));
			printf("\r\n");
		}


		{
			int j=0;
			printf("ctr <-- \r\n");
			for ( j=0 ; j<16 ; j++ ) printf("%s%02X", (j&&((j%8)==0))?"  ":" ", *(ctr+j));
			printf("\r\n");
		}
		
		XOR8x16(ct, block, pt);

		{
			int j=0;
			printf("--> out\r\n");
			for ( j=0 ; j<16 ; j++ ) printf("%s%02X", (j&&((j%8)==0))?"  ":" ", *(ct+j));
			printf("\r\n");
		}



		ctr128_inc_aligned(ctr);
	}

	if(pt_len & 0xf)
	{
		unsigned int i;
		lea_encrypt_1block(block, ctr, key);

		for(i = 0; i < (pt_len & 0xf); i++)
			ct[i] = block[i] ^ pt[i];
	}
	{
		int j=0;
		printf(">>>>>>>>>>> out\r\n");
		for ( j=0 ; j<16 ; j++ ) printf("%s%02X", (j&&((j%8)==0))?"  ":" ", *(ct+j));
		printf("\r\n");
	}

#endif
}

void MAKE_FUNC(ctr_dec)(unsigned char *pt, const unsigned char *ct, unsigned int ct_len, unsigned char *ctr, const LEA_KEY *key)
{
	printf("%s,%s,%d\r\n", __FILE__,__FUNCTION__,__LINE__);

	MAKE_FUNC(ctr_enc)(pt, ct, ct_len, ctr, key);
}
