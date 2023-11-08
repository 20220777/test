#include "__st.h"
#include <stdarg.h>

#include <lwip/ip_addr.h>

enum __tcp_states
{
  TDS_NONE = 0,
  TDS_ACCEPTED,
  TDS_RECEIVED,
  TDS_CLOSING
};

__attribute__((packed)) typedef struct
{
  #if __LWIP__
  uint8_t state; //ES_NOE, ES_ACCEPTED, ES_RECEIVED, ES_CLOSING
  uint8_t retries; //retry counter
  struct tcp_pcb *pcb; //PCB 포인터
  struct pbuf *p; //송수신 버퍼 포인터
  #endif
  void* prnt;
}__utcp;


void __fprintf(uint8_t* p, int32_t sz)
{
  int32_t i =0;
  for (i=0 ; i<sz ; i++ )
  {
    if ( i&& i%8==0 ) printf("  ");
    if ( i&& i%16==0 ) printf("\r\n");
    printf("%02X ", *(p+i));
  }
  printf("\r\n");
}

void __tcp_close_connection(struct tcp_pcb* pcb, __utcp* t)
{
  /* clear callback functions */
  #if __LWIP__

  printf("%16s:%4d |\r\n", __FUNCTION__,__LINE__);

  tcp_arg(pcb, NULL);
  tcp_sent(pcb, NULL);
  tcp_recv(pcb, NULL);
  tcp_err(pcb, NULL);
  tcp_poll(pcb, NULL, 0);

  if (t != 0)
  {
    mem_free(t);
  }

  tcp_close(pcb);
  #endif
}

int8_t __tcp_callback_writed(void* arg, struct tcp_pcb* pcb, uint16_t sz)
{
  #if __LWIP__
  printf("%16s:%4d sz -> %4d|\r\n", __FUNCTION__,__LINE__, sz);
  #endif
  return 0;
}

int8_t __tcp_callback_poll(void* arg, struct tcp_pcb* pcb)
{
  #if __LWIP__
  //printf("%16s:%4d |\r\n", __FUNCTION__,__LINE__);
  #endif
  return 0;
}


int8_t __tcp_callback_received(void* arg, struct tcp_pcb* pcb, struct pbuf* p, int8_t err)
{
  int8_t e;
  #if 0 //__LWIP__
  __utcp* t = (__utcp*)arg;
  printf("%24s state : %4d (%8s) -> %4d\r\n", __FUNCTION__, t->state, t->p==0?"NULL":"NOT NULL", err);

  if (p == 0) //callback is called but there's no data
  {
    t->state = TDS_CLOSING;
    if (t->p == 0)
    {
      __tcp_close_connection(pcb, t); //close connection
    }
    else //if there's remained data to send
    {
      __tcp_read(pcb, t);
    }
    e = ERR_OK;
  }
  else if (err != ERR_OK) //error when receiving
  {
    if (p != 0) //buffer is not empty
    {
      t->p = 0;
      pbuf_free(p); //clear buffer
    }
    e = err;
  }
  else if (t->state == TDS_ACCEPTED) //first data receiving
  {
    t->state = TDS_RECEIVED; //change state
    t->p = p; //set buffer pointer
    __tcp_read(pcb, t);
    e = ERR_OK;
  }
  else if (t->state == TDS_RECEIVED) //additional data receiving
  {
    if (t->p == 0) //no data to send
    {
      t->p = p; //set buffer pointer
    __tcp_read(pcb, t);
    }
    else //buffer is not empty, there's data to send
    {
      struct pbuf *ptr = t->p; //head buffer
      pbuf_chain(ptr, p);  //append tail buffer to the head, this buffer will be handled by poll callback
  }
    e = ERR_OK;
  }
  else if (t->state == TDS_CLOSING) //receiving data when connection is closing
  {
    tcp_recved(pcb, p->tot_len);  //advertise window size
    t->p = 0;
    pbuf_free(p);
    e = ERR_OK;
  }
  else //undefined condition
  {
    tcp_recved(pcb, p->tot_len);  //advertise window size
    t->p = 0;
    pbuf_free(p);
    e = ERR_OK;
  }
  #endif
  return e;
}



void __tcp_callback_error(void* arg, int8_t err)
{
  #if __LWIP__
  __stf*   pstf = (__stf*)arg;
  printf("%16s:%4d | %4d\r\n", __FUNCTION__,__LINE__, err);
  if ( err == ERR_RST )
  {
	  pstf->SR &= ~(TCP_CONNECTED);
	  tcp_close(pstf->_tcp._p);
	  tcp_free(pstf->_tcp._p);
	  tcp_setprio(pstf->_tcp._p, TCP_PRIO_NORMAL);
	  tcp_arg(pstf->_tcp._p, 0);
	  tcp_sent(pstf->_tcp._p, 0);
	  tcp_recv(pstf->_tcp._p, 0);
	  tcp_err(pstf->_tcp._p, 0);
	  tcp_poll(pstf->_tcp._p, 0, 0);
	  pstf->SR &= ~(INITIALIZED_TCP);
  }
  #endif
}
int8_t __tcp_callback_connected(void* arg, struct tcp_pcb* p, uint8_t err)
{
  __stf*   pstf = (__stf*)arg;
  printf("%16s:%4d | err-> %d\r\n", __FUNCTION__,__LINE__, err);
  if ( err != ERR_OK ) return err;
  pstf->SR |= TCP_CONNECTED;
  return 0;
}


void __tcp_write(struct tcp_pcb *pcb, uint8_t* b, int32_t sz, int8_t (*f)(void*, struct tcp_bcp*, uint16_t))
{
  #if 0 //__LWIP__
  tcp_sent(pcb, f);
  tcp_write(pcb, b, sz, TCP_WRITE_FLAG_COPY);
  tcp_recved(pcb, sz);
  #endif

  #if __LWIP__
  int8_t e;
  //tcp_sent(pcb, f);
  e = tcp_write(pcb, b, sz, 1);
  printf("%16s:%4d | e -> %d, tcp_sndbuf -> %d \r\n", __FUNCTION__,__LINE__, e, tcp_sndbuf(pcb));
  //tcp_recved(pcb, sz);
  tcp_output(pcb);
  #endif
}


void __tcp_read(struct tcp_pcb *pcb, __utcp* t)
{
  #if __LWIP__
  struct pbuf* ptr;
  int8_t e = 0;
  uint8_t freed = 0;
  for( ; t->p ; )
  {
    ptr = t->p;
    __fprintf(t->p->payload, t->p->len);
    t->p = ptr->next;
    if ( t->p != 0 ) pbuf_ref(t->p);
    for ( freed=0 ; freed == 0 ; ) freed = pbuf_free(ptr);
    tcp_recved(pcb, ptr->len);
  }

  //__tcp_write(pcb, "ACCK", 4, __tcp_callback_writed);
  #endif
}



int32_t tcpc(__stf* p)
{
  int32_t e = 0;
  uint16_t port = 80;
  ip_addr_t dst;

  #if __LWIP__
  if ( (p->SR & INITIALIZED_TCP) == 0 )
  {
	printf("%24s\r\n", __FUNCTION__);

    p->_tcp._p = tcp_new();
    if ( p->_tcp._p != 0 )
    {
      p->SR |= INITIALIZED_TCP;
      IP4_ADDR( &dst, 192, 168, 0, 9);

      printf("%24s -> %08X\r\n", __FUNCTION__, p->_tcp._p);

      tcp_arg(p->_tcp._p, p);
      tcp_setprio(p->_tcp._p, TCP_PRIO_NORMAL);
      tcp_sent(p->_tcp._p, __tcp_callback_writed);
      tcp_recv(p->_tcp._p, __tcp_callback_received);
      tcp_err(p->_tcp._p, __tcp_callback_error);
      tcp_poll(p->_tcp._p, __tcp_callback_poll, 0);

      e = tcp_connect(p->_tcp._p, &dst, port, __tcp_callback_connected);
      printf("%24s -> %d\r\n", __FUNCTION__, e);
    }
  }
  #endif

  return 0;
}



int32_t tcpd(__stf* p)
{
  int32_t e = 0;
  uint16_t port = 7810;

  #if __LWIP__
  if ( (p->SR & INITIALIZED_TCP) == 0 )
  {
    p->_tcp._p = tcp_new();
    if ( p->_tcp._p != 0 )
    {
      p->SR |= INITIALIZED_TCP;
      e = tcp_bind(p->_tcp._p, IP_ADDR_ANY, port);//((port&0xFF00)>>8)|((port&0x00FF)<<8));
      if ( e == ERR_OK )
      {
        printf("%16s %d.%d.%d.%d:%d\r\n","tcp server started",
          (p->_pnetif->ip_addr.addr&0x000000FF),
          (p->_pnetif->ip_addr.addr&0x0000FF00)>>8,
          (p->_pnetif->ip_addr.addr&0x00FF0000)>>16,
          (p->_pnetif->ip_addr.addr&0xFF000000)>>24, port);
        p->_tcp._p = tcp_listen(p->_tcp._p);

      }
    }
  }


  if ( p->SR & INITIALIZED_TCP )
  {
    tcp_accept(p->_tcp._p, __tcp_accept);
  }
  #endif
  return 0;
}





int32_t httpd(__stf* p)
{
  int32_t e = 0;
  uint16_t port = 7810;

  if ( (p->SR & INITIALIZED_HTTPD) == 0 )
  {
    //httpd_init();
    printf("%16s \r\n", "tcp server started");
    p->SR |= INITIALIZED_HTTPD;
  }
  return 0;
}







#if 0

int32_t __st_netif_check(__stf* p, uint32_t msec)
{
  if ( dhcp_supplied_address(p->_pnetif) )
  {
    p->SR |= IP_ASSIGNED;
    return IP_ASSIGNED;;
  }
  else
  {
    p->SR &= ~(IP_ASSIGNED);
  }

  ethernetif_input(p->_pnetif);
  sys_check_timeouts();

  printf("%d.%d.%d.%d\r\n",
    (p->_pnetif->ip_addr.addr&0x000000FF),
    (p->_pnetif->ip_addr.addr&0x0000FF00)>>8,
    (p->_pnetif->ip_addr.addr&0x00FF0000)>>16,
    (p->_pnetif->ip_addr.addr&0xFF000000)>>24);

  if (netif_is_link_up(p->_pnetif) && !netif_is_up(p->_pnetif))
  {
    // printf("link is down\r\n");
    netif_set_up(p->_pnetif);
    dhcp_start(p->_pnetif);
  }
  #if 0
  else if (netif_is_link_up(p->_pnetif) && netif_is_up(p->_pnetif))
  {
    // printf("link is up\r\n");
  }
  #endif

  return p->SR;
}

#endif


int32_t __st_netif_check(__stf* p, uint32_t msec)
{
  #if __LWIP__
  if ( dhcp_supplied_address(p->_pnetif) )
  {
    if ( (p->SR&ASSIGNED_IP) == 0 )
    {
      printf("%d.%d.%d.%d\r\n",
        (p->_pnetif->ip_addr.addr&0x000000FF),
        (p->_pnetif->ip_addr.addr&0x0000FF00)>>8,
        (p->_pnetif->ip_addr.addr&0x00FF0000)>>16,
        (p->_pnetif->ip_addr.addr&0xFF000000)>>24);
    }
    p->SR |= ASSIGNED_IP;
    return ASSIGNED_IP;;
  }
  else
  {
    p->SR &= ~(ASSIGNED_IP);
  }
  #endif
  return p->SR;
}


void* sifr_seed_ecb_encode_callback(void* h, void* o, void* w, void* l)
{
  display((uint8_t*)w, (int32_t)l, __FUNCTION__);
  return 0;
}

void* sifr_seed_ecb_decode_callback(void* h, void* o, void* w, void* l)
{
  display((uint8_t*)w, (int32_t)l, __FUNCTION__);
  return 0;
}


static const char SEED_ECB[][4][51200] =
{
  {
  "828E9E067BC2E9B306A3FA99426787AC",
  "21C7B0986CF8265708DD9202777B35E7",
  "82E1674DBEF09F6B73552C6329A1A9D9",
  },
};


#if 0
int32_t __sifr_seed_ecb_encode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz,  void* (*callback)(void*,void*,void*,void*), void* obj);
int32_t __sifr_seed_ecb_decode(void* h, uint8_t* key, int32_t ksz, uint8_t* vctr, int32_t vsz, uint8_t* in, int32_t isz, uint8_t* out, int32_t osz,  void* (*callback)(void*,void*,void*,void*), void* obj);
int32_t __sifr_initia(void**,int8_t*,int8_t*);
int32_t __sifr_finelia(void**);
#endif
void sifr(__stf* p)
{
  int32_t e = 0;
  int8_t  iobuf[8][4096] = {0};
  int8_t  ubuf[4096] = {0};
  int8_t  obuf[8][4096] = {0};
  int32_t sz[8] = {32, 32, 32, 32, 8, 32, 32, 64};
  int32_t lstatus[2] = {0};
  int8_t  version[1024] = {0};
  int8_t  author[1024] = {0};
  int8_t  module_name[1024] = {0};


  if ( p->SR & INITIALIZED_SIFR ) return;


  __sifr_initia(&p->_sifr, BASE_KEY, 0);

  sz[0] = ascii_to_hex(SEED_ECB[0][0], iobuf[0]);
  sz[1] = ascii_to_hex(SEED_ECB[0][1], iobuf[1]);
  sz[2] = ascii_to_hex(SEED_ECB[0][2], iobuf[2]);

  display(iobuf[0], sz[0], "Input Key");
  display(iobuf[1], sz[1], "Input Text");
  display(iobuf[2], sz[2], "expected Output Text");
  e = __sifr_seed_ecb_encode(p->_sifr, iobuf[0], sz[0], 0, 0, iobuf[1], sz[1], obuf[0], 4096, sifr_seed_ecb_encode_callback, (void*)p);
  display(obuf[0], e, "SEED ECB ENCODE");
  e = __sifr_seed_ecb_decode(p->_sifr, iobuf[0], sz[0], 0, 0, obuf[0], e, obuf[1], 4096, sifr_seed_ecb_decode_callback, (void*)p);
  display(obuf[1], e, "SEED ECB DECODE");

  p->SR |= INITIALIZED_SIFR;
}



void write_cipher(__stf* p)
{
  int32_t e = 0;
  int8_t  iobuf[8][4096] = {0};
  int8_t  ubuf[4096] = {0};
  int8_t  obuf[8][4096] = {0};
  int32_t sz[8] = {32, 32, 32, 32, 8, 32, 32, 64};
  int8_t  req[1024] = {0};


  if ( p->SR & INITIALIZED_SIFR == 0 ) return;

  if ( p->SR & INITIALIZED_TCP == 0 ) return;

  sz[0] = ascii_to_hex(SEED_ECB[0][0], iobuf[0]);
  sz[1] = ascii_to_hex(SEED_ECB[0][1], iobuf[1]);
  sz[2] = ascii_to_hex(SEED_ECB[0][2], iobuf[2]);

  display(iobuf[0], sz[0], "Input Key");
  display(iobuf[1], sz[1], "Input Text");
  display(iobuf[2], sz[2], "expected Output Text");
  e = __sifr_seed_ecb_encode(p->_sifr, iobuf[0], sz[0], 0, 0, iobuf[1], sz[1], obuf[0], 4096, sifr_seed_ecb_encode_callback, (void*)p);


  HAL_Delay(2000);

  printf("----------          ----------          ----------          ----------\r\n");

    sprintf(req,
          "POST / HTTP/1.1\r\n"
          "\r\n"
          "key1=%s\r\n",
          obuf[0]);


  __tcp_write(p->_tcp._p, req, strlen(req), __tcp_callback_writed);
  printf("          ----------          ----------          ----------          ----------\r\n");

}





int32_t __st_proc(__stf* p)
{

  printf(".");

  #if __LWIP__
  MX_LWIP_Process();
  #endif

  if ( (__st_netif_check(p, 0) & ASSIGNED_IP) == 0  )
  {
    return 0;
  }

  tcpc(p);

  sifr(p);

  write_cipher(p);

  //printf("HCLK=%d, %d, %d, %08X \r\n", HAL_RCC_GetHCLKFreq(), HAL_RCC_GetPCLK1Freq(), HAL_RCC_GetPCLK2Freq(), uwTick);//HAL_RNG_GetRandomNumber(&hrng));

  //display(RNG, sizeof(RNG_TypeDef), "RNG_TypeDef");

  //HAL_Delay(4000);

  //tcpd(p);
  //httpd(p);
  return 0;
}





