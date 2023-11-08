#ifndef ____ST_H_3E768634_8484_4626_B86C_40859CBBA626____
#define ____ST_H_3E768634_8484_4626_B86C_40859CBBA626____

#define __LWIP__           1
#define __UART1__          1

#define BASE_KEY     "XFFtAKk6l4ktya1ct5XZajlM4M8BgXFJbedcoqoPfdI="


#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"
#if __LWIP__
#include "stm32f4xx_hal_eth.h"
#include "lwip.h"
#include "tcp.h"
#include "lwip/stats.h"
#endif

#include "__utils.h"

#define	__MAX_UART             2


#if 0
+----+----+ +----+----+  +----+----+ +----+----+
+----+----+ +----+----+  +----+----+ +----+----+
 ^^^                                          ^
 |||                                          |
 |||                                          +---------------- initialized sifr
 ||+----------------------------------------------------------- initialized httpd
 |+------------------------------------------------------------ initialized tcp
 +------------------------------------------------------------- assigned ip
#endif

#define ASSIGNED_IP                  0x80000000
#define INITIALIZED_TCP              0x40000000
#define INITIALIZED_HTTPD            0x20000000
#define INITIALIZED_SIFR             0x00000001

#define TCP_CONNECTED                0x08000000
#define TCP_CLOSED                   0x04000000

#define MAX_UBUF                     1024


 __attribute__((packed)) typedef struct
 {
 	uint8_t buf[MAX_UBUF];
 	uint32_t idx;
 } __ubuf;

__attribute__((packed)) typedef struct
{
	#if __LWIP__
	struct tcp_pcb*      _p;
	#endif
	__ubuf  ubuf;
} __tcp;

__attribute__((packed)) typedef struct
{
	uint32_t             SR;
	#if __UART1__
	UART_HandleTypeDef*  _puart[__MAX_UART];
	#endif
	struct netif*        _pnetif;
	__tcp                _tcp;
	__tcp                _httpd;

	void*                _sifr;
} __stf;

int32_t __st_proc(__stf*);
void user_input(__stf* p, uint8_t in);


#endif
