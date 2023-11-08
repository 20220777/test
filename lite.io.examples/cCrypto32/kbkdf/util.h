#pragma once

#include <stdint.h>

#ifdef  __cplusplus
extern "C" {
#endif

	int32_t asc2hex(uint8_t* dst, const int8_t* src);
	void print_title(const int8_t* title);
	void print_hex(const int8_t* valName, const uint8_t* data, const int32_t dataLen);
	void print_result(const int8_t* func, int32_t ret);
	void word2byte(uint8_t* dst, const uint32_t src, const int32_t srcLen);

#ifdef  __cplusplus
}
#endif

// EOF
