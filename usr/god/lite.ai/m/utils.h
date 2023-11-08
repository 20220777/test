#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void printArray(int32_t* p, int32_t count);
void assignArray(int32_t* p, int32_t count);
void printBuffer(int8_t* b, int32_t sz);


#define  __TR__   printf("\r\n---------------------------------------\r\n")


#endif
