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


void display(int8_t* b, int32_t sz, const int8_t* fmt,...);
int32_t ascii_to_hex(uint8_t* src, uint8_t* dst);
int32_t hexasc(uint8_t* dst, uint8_t* src, int32_t sz);

int32_t hexTo(int8_t* a);
int32_t toHex(int8_t* a, uint8_t* result, int32_t* count);
void bigNumToArray(uint8_t* a, int32_t count, uint32_t* p);

extern int32_t (*putMessage)(void* h, void* m, void* w, void* l);
extern int32_t (*setMessage)(void* h, void* m, void* w, void* l);


#endif
