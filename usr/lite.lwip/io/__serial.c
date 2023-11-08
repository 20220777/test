#include "__serial.h"

#if __UART1__
int32_t __serial_open(UART_HandleTypeDef* h)
{
  int32_t e = 0;


  return e;
}
#endif

#if __UART1__
int32_t __serial_close(UART_HandleTypeDef* h)
{

	return 0;
}
#endif

#if __UART1__
int32_t __serial_read(UART_HandleTypeDef* h, uint8_t* b, int32_t sz)
{
	return 0;
}
#endif

#if __UART1__
int32_t __serial_write(UART_HandleTypeDef* h, uint8_t* b, int32_t sz, uint32_t ns)
{
  return HAL_UART_Transmit(h, b, sz, ns);
}
#endif
