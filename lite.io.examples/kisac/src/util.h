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



int asc2hex(unsigned char *dst, const char *src);
void print_title(const char *title);
void print_hex(const char *valName, const unsigned char *data, const int dataLen);
void print_result(const char *func, int ret);


void Byte2Word(unsigned int *dst, const unsigned char *src, const int srcLen);
void Word2Byte(unsigned char *dst, const unsigned int *src, const int srcLen);



#define PRINT_BUFFER(a,b,c)     display(b,c,a)

#endif
