#ifndef ____SOCKET_H_3E768634_8484_4626_B86C_40859CBBA626____
#define ____SOCKET_H_3E768634_8484_4626_B86C_40859CBBA626____

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#if 0
#include <arch/cc.h>
#include <lwipopts.h>

#include <lwip/opt.h>
#include <lwip/sockets.h>
#include <lwip/sys.h>

#include <lwip/mem.h>
#endif


int32_t __socket_open(int32_t port);
int32_t __socket_listen(int32_t s);
int32_t __socket_accept(int32_t s);

#endif
