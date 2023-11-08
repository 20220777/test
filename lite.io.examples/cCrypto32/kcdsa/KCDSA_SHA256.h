#ifndef _KCDSA_SHA256_H
#define _KCDSA_SHA256_H
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
#include "kcdsa_type.h"

	// SHA-256 상수 정의
#define SHA256_DIGEST_BLOCKLEN	64
#define SHA256_DIGEST_VALUELEN	32

// SHA-256 구조체 정의
	typedef struct {
		uint32_t ChainVar[SHA256_DIGEST_VALUELEN / 4];	// 연쇄변수
		uint32_t Count[4];								// 길이변수
		uint8_t Buffer[SHA256_DIGEST_BLOCKLEN];		// 메시지 버퍼
	} SHA256_ALG_INFO;

	/*************** Functions ************************************************/

	// SHA-256 함수 선언
	void KCDSA_SHA256_Init(SHA256_ALG_INFO *AlgInfo);
	void KCDSA_SHA256_Update(SHA256_ALG_INFO *AlgInfo, uint8_t* Message, uint32_t MessageLen);
	void KCDSA_SHA256_Final(SHA256_ALG_INFO *AlgInfo, uint8_t* Digest);

	/*************** END OF FILE **********************************************/

#ifdef __cplusplus
}
#endif
#endif	//	_SHA256_H
