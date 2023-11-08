#ifndef __ICODEX_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __ICODEX_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <stdint.h>

//extern int32_t (*get_hex_semaphore)(uint32_t* id, uint32_t h, uint32_t v, int32_t msec);
//extern int32_t (*set_hex_semaphore)(uint32_t* id, uint32_t h, uint32_t v);
//extern int32_t (*check_hex_semaphore)(uint32_t* id, uint32_t h, uint32_t v);
//extern void*   (*thread_create)(void* (*f)(void*),void* arg, void* id);
//extern void    (*thread_exit)(int32_t sid, void* id);
//extern int8_t* (*get_curr_time)(int8_t*p, int8_t* arg0, int8_t* arg1, int8_t* arg2, int8_t* arg3, int32_t* YY, int32_t* MM, int32_t* DD, int32_t* hh, int32_t* mm, int32_t* ss);
//extern void*   (*log_write_ex)(int8_t* ppath, int8_t* fname, int8_t* pfname, void** pfp, int8_t* pfx, uint32_t mode, const int8_t* fmt, ...);


int32_t (*get_hex_semaphore)(uint32_t* id, uint32_t h, uint32_t v, int32_t msec);
int32_t (*set_hex_semaphore)(uint32_t* id, uint32_t h, uint32_t v);
int32_t (*check_hex_semaphore)(uint32_t* id, uint32_t h, uint32_t v);
void*   (*thread_create)(void* (*f)(void*),void* arg, void* id);
void    (*thread_exit)(int32_t sid, void* id);
int8_t* (*get_curr_time)(int8_t*p, int8_t* arg0, int8_t* arg1, int8_t* arg2, int8_t* arg3, int32_t* YY, int32_t* MM, int32_t* DD, int32_t* hh, int32_t* mm, int32_t* ss, int32_t* us);
void*   (*log_write_ex)(int8_t* ppath, int8_t* fname, int8_t* pfname, void** pfp, int8_t* pfx, uint32_t mode, const int8_t* fmt, ...);

#endif
