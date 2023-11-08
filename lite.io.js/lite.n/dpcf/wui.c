#include <stdio.h>
#include <stdint.h>
#include <network.h>
#include <common.h>
#include <nm.h>

#if __LINUX__
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <linux/wireless.h>
#endif
