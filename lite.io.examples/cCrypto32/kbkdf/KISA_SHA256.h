/**
@file KISA_SHA_256.h
@brief SHA256 암호 알고리즘
@author Copyright (c) 2013 by KISA
@remarks http://seed.kisa.or.kr/
*/

#ifndef _KISA_KISA_SHA256_H
#define _KISA_KISA_SHA256_H

#include <stdint.h>

#ifdef  __cplusplus
extern "C" {
#endif

#ifndef OUT
#define OUT
#endif

#ifndef IN
	#define IN
#endif

#ifndef INOUT
	#define INOUT
#endif

#define USER_LITTLE_ENDIAN

#if defined(USER_BIG_ENDIAN)
	#define USING_BIG_ENDIAN
#elif defined(USER_LITTLE_ENDIAN)
	#define USING_LITTLE_ENDIAN
#else
	#if 0
		#define USING_BIG_ENDIAN
	#elif defined(_MSC_VER)
		#define USING_LITTLE_ENDIAN
	#else
		#error
	#endif
#endif

	//typedef unsigned long ULONG;
	//typedef ULONG* ULONG_PTR;
	
	typedef uint32_t ULONG;
	typedef ULONG* ULONG_PTR;

	typedef uint32_t UINT;
	typedef UINT* UINT_PTR;

	typedef int32_t SINT;
	typedef SINT* SINT_PTR;

	typedef uint8_t UCHAR;
	typedef UCHAR* UCHAR_PTR;

	typedef uint8_t BYTE;

#define KISA_SHA256_DIGEST_BLOCKLEN	64
#define KISA_SHA256_DIGEST_VALUELEN	32

	typedef struct {
		UINT uChainVar[KISA_SHA256_DIGEST_VALUELEN / 4];
		UINT uHighLength;
		UINT uLowLength;
		BYTE szBuffer[KISA_SHA256_DIGEST_BLOCKLEN];
	} KISA_SHA256_INFO;

	/**
	@brief 연쇄변수와 길이변수를 초기화하는 함수
	@param Info : KISA_SHA256_Process 호출 시 사용되는 구조체
	*/
	void KISA_SHA256_Init(OUT KISA_SHA256_INFO* Info);

	/**
	@brief 연쇄변수와 길이변수를 초기화하는 함수
	@param Info : KISA_SHA256_Init 호출하여 초기화된 구조체(내부적으로 사용된다.)
	@param pszMessage : 사용자 입력 평문
	@param inLen : 사용자 입력 평문 길이
	*/
	void KISA_SHA256_Process(OUT KISA_SHA256_INFO* Info, IN const BYTE* pszMessage, IN UINT uDataLen);

	/**
	@brief 메시지 덧붙이기와 길이 덧붙이기를 수행한 후 마지막 메시지 블록을 가지고 압축함수를 호출하는 함수
	@param Info : KISA_SHA256_Init 호출하여 초기화된 구조체(내부적으로 사용된다.)
	@param pszDigest : 암호문
	*/
	void KISA_SHA256_Close(OUT KISA_SHA256_INFO* Info, IN BYTE* pszDigest);

	/**
	@brief 사용자 입력 평문을 한번에 처리
	@param pszMessage : 사용자 입력 평문
	@param pszDigest : 암호문
	@remarks 내부적으로 KISA_SHA256_Init, KISA_SHA256_Process, KISA_SHA256_Close를 호출한다.
	*/
	void KISA_SHA256_Encrpyt(IN const BYTE* pszMessage, IN UINT uPlainTextLen, OUT BYTE* pszDigest);

#ifdef  __cplusplus
}
#endif

#endif