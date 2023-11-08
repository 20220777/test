#ifndef __UTIL_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __UTIL_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#include <stdio.h>
#include <stdint.h>

#define PREFIX     printf("|        |");
#define CRLF       printf("\r\n");


#define BOX(a)       printf("+------------------------------------------------------------------------------+\r\n" \
                            "|                                                                              |\r\n"\
                            "| %-76s |\r\n" \
                            "|                                                                              |\r\n"\
                            "+------------------------------------------------------------------------------+\r\n", a)

int32_t strcompare(int8_t* a, int8_t* b);

void display(int8_t* b, int32_t sz, const int8_t* fmt,...);
int32_t ascii_to_hex(uint8_t* src, uint8_t* dst);
int32_t hexasc(uint8_t* dst, uint8_t* src, int32_t sz);

extern int32_t (*putMessage)(void* h, void* m, void* w, void* l);
extern int32_t (*setMessage)(void* h, void* m, void* w, void* l);

void __debug(int32_t dflg);
void __debug_print(const char*, int, const char*, ...);
void __debug_buffer(const char*, int, uint8_t*, int32_t);


#define DEBUG_PRINT(...)    __debug_print(__FUNCTION__,__LINE__,__VA_ARGS__)
#define DEBUG_BUFFER(b,s)   __debug_buffer(__FUNCTION__,__LINE__,b,s)


#endif
