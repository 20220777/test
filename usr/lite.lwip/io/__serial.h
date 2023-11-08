#ifndef ____SERIAL_H_3E768634_8484_4626_B86C_40859CBBA626____
#define ____SERIAL_H_3E768634_8484_4626_B86C_40859CBBA626____

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"


#if __UART1__
int32_t __serial_open(UART_HandleTypeDef* h);
int32_t __serial_close(UART_HandleTypeDef* h);
int32_t __serial_read(UART_HandleTypeDef* h, uint8_t* b, int32_t sz);
int32_t __serial_write(UART_HandleTypeDef* h, uint8_t* b, int32_t sz, uint32_t ns);
#endif

#endif
