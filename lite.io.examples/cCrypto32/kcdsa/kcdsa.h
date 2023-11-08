#ifdef __cplusplus
extern "C" {
#endif

#include "KCDSA_SHA224.h"
#include "KCDSA_SHA256.h"
#include "bignum.h"

#define MaxDIGIT		96 //((BN_MAX_BITS-1)/BitsInDIGIT+1)	//	Long #의 최대 자리수

#define GOTO_END		if( ret!=CTR_SUCCESS )	goto LABEL_END

#define CTR_SUCCESS					0

#define KCDSA_SIGN 1
#define KCDSA_VERIFY 0

#define VERIFY_SUCCESS 1
#define VERIFY_FAIL 0

	//extern kcdsa *Parameter;

#define ROTL_WORD(x, n) _lrotl((x), (n))
#define ROTR_WORD(x, n) _lrotr((x), (n))

////////	reverse the byte order of WORD(WORD:4-bytes integer) and WORD.
#define ENDIAN_REVERSE_WORD(dwS)	( (ROTL_WORD((dwS),  8) & 0x00ff00ff)	\
	| (ROTL_WORD((dwS), 24) & 0xff00ff00))

#define BIG_W2B(W, B)		*(uint32_t *)(B) = ENDIAN_REVERSE_WORD(W)

	typedef struct kcdsa_structure {
		BIGNUM 		*KCDSA_P;		//	prime(1024 + 128i bits i=0..8)
		BIGNUM 		*KCDSA_Q;		//	subprime(128 + 32j bits j=0..4)
		BIGNUM 		*KCDSA_G;		//	Base
		BIGNUM 		*KCDSA_x;		//	
		BIGNUM 		*KCDSA_y;		//	
		uint32_t	Count;			//	Prime Type ID
		uint32_t	SeedLen;		//	in BYTEs
	} KISA_KCDSA;

	uint32_t KISA_KCDSA_CreateObject(KISA_KCDSA	**kcdsa);
	uint32_t KCDSA_PRNG_SHA_224(SHA224_ALG_INFO	*SHA224_AlgInfo, uint8_t *pbSrc, uint32_t dSrcByteLen, uint8_t *pbDst, uint32_t dDstBitLen);
	uint32_t KCDSA_PRNG_SHA_256(SHA256_ALG_INFO	*SHA256_AlgInfo, uint8_t *pbSrc, uint32_t dSrcByteLen, uint8_t *pbDst, uint32_t dDstBitLen);
	uint32_t Generate_Random(BIGNUM	*XKEY, uint8_t *pbSrc, uint32_t dSrcByteLen, uint32_t *X, uint32_t XBitLen, KISA_KCDSA *kcdsa, uint32_t HASH);
	uint32_t KISA_KCDSA_GenerateKeyPair(KISA_KCDSA *KCDSA_Key, uint8_t *pbSrc, uint32_t dSrcByteLen, uint32_t qLen, uint32_t HASH);
	uint32_t KISA_KCDSA_sign(KISA_KCDSA *kcdsa, uint8_t *MsgDigest, uint32_t MsgDigestLen, uint8_t *Signature, uint32_t *SignLen, uint32_t HASH, uint8_t *t_omgri, uint32_t omgri_len);
	uint32_t KISA_KCDSA_verify(KISA_KCDSA *kcdsa, uint8_t *MsgDigest, uint32_t MsgDigestLen, uint8_t *Signature, uint32_t SignLen, uint32_t HASH);
	uint32_t KISA_KCDSA_set_params(KISA_KCDSA *kcdsa, uint32_t *p, int32_t plen, uint32_t *q, int32_t qlen, uint32_t *g, int32_t glen, uint32_t *private_key, int32_t private_keylen, uint32_t *public_key, int32_t public_keylen);
	uint32_t KISA_KCDSA_GenerateParameters(uint32_t PrimeBits, uint32_t SubPrimeBits, KISA_KCDSA *kcdsa, uint32_t HASH);
	uint32_t KISA_KCDSA_DestroyObject(KISA_KCDSA	**kcdsa);

#ifdef __cplusplus
}
#endif