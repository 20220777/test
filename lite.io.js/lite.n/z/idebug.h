#ifndef __IDEBUG_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __IDEBUG_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <common.h>

#if defined __cplusplus
extern "C"
#endif
void __debug(int32_t dflg);

#if defined __cplusplus
extern "C"
#endif
void debug_print(const char*, int, const char*, ...);

#if defined __cplusplus
extern "C"
#endif
void debug_buffer(const char*, int, uint8_t*, int32_t);


#define DEBUG_PRINT(...)   debug_print(__FUNCTION__,__LINE__,__VA_ARGS__);
#define DEBUG_BUFFER(b,s)   debug_buffer(__FUNCTION__,__LINE__,b,s);

#endif
