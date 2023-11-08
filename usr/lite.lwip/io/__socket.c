#include "__socket.h"


int32_t __socket_open(int32_t port)
{
	int32_t s = 0;
	#if 0
	struct sockaddr_storage addr;
	struct sockaddr_in *addr_in;
	memset(&addr, 0, sizeof(addr));
	addr.ss_family = AF_INET;
	addr_in = (struct sockaddr_in *)&addr;
	addr_in->sin_addr.s_addr = inet_addr("127.0.0.1");
    addr_in->sin_port = htons(port);

	s = lwip_socket(AF_INET, SOCK_STREAM, 0);

    if ( lwip_bind(s, (struct sockaddr*)&addr, sizeof(struct sockaddr)) < 0 ) return -1;
	#endif
	return s;
}


int32_t __socket_listen(int32_t s)
{
   return 0;//lwip_listen(s, 0);
}

int32_t __socket_accept(int32_t s)
{
    int32_t sz = 0;
    int32_t sock = 0;

    #if 0
	struct sockaddr_in addr;

	memset(&addr, 0, sizeof(addr));

	sz = sizeof(addr);

    sock = lwip_accept(s, (struct sockaddr*)&addr, (socklen_t*)&sz);
    #endif
    return sock;
}
