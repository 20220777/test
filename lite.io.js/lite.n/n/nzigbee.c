#include <nzigbee.h>
#include <nutil.h>
#include <nm.h>

static cnzigbee gzigbee;
#define MAX_SZ        32

#define MAX_PACKET                  7
uint8_t nzprotocol[MAX_PACKET+1][32] = {
  {
    0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  },
  {
    0x3A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  },
  {
    0x3B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  },
  {
    0x36, 0x00, 0x00, 0x11, 0x11, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  },
  {
    0x33, 0x00, 0x22, 0xB6, 0x8A, 0x01, 0xF0, 0x00,
    0x00, 0x00, 0xAC, 0x0B, 0xE6, 0x1A, 0xC4, 0xA3,
    0xBB, 0x3C, 0xCC, 0xB9, 0x75, 0xF6, 0xBA, 0xBB,
    0x5B, 0x0D, 0x03, 0xE6, 0x43, 0x13, 0x92, 0xFF
  },
  {
    0x5B, 0xE8, 0x39, 0xA9, 0x0F, 0xA5, 0x67, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  },
  {
    0x36, 0x00, 0x00, 0xB6, 0x8A, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  },
};

uint8_t ackprotocol[MAX_PACKET+1][32] = {
  {
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x00, 0x00, 0x55, 0x53, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  },
  {
    0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  },
  {
    0x77, 0x00, 0x0F, 0x11, 0x11, 0x00, 0x6E, 0x65,
    0x74, 0x77, 0x6F, 0x72, 0x6B, 0x20, 0x6C, 0x65,
    0x61, 0x76, 0x65, 0x0D, 0x0A, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  },
  {
    0x73, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  },
  {
    0x74, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA3, 0xBB,
    0x3C, 0xCC, 0xB9, 0x75, 0xF6, 0x8A, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  },
  {
    0x76, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  },
};

void printBuffer(uint8_t* title, uint8_t* b, int32_t sz)
{
  int32_t j=0;

  printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\r\n"
         " %s \r\n"
         "--------------------------------------------------------------------------------\r\n", title);
  for ( j=0 ; j<sz ; j++ )
  {
    if ( j && (j%16)==0 ) printf("\r\n");
    else if ( j && (j%8)==0 ) printf("  ");
    printf("%02X ", b[j]);
  }
  printf("\r\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\r\n");
}


#if 0
void arrCheck(cnLiteIO* p)
{
  int32_t i = 0;
  int32_t j = 0;
  int32_t k = 0;
  int32_t e = 0;
  uint8_t a[512] = {0};

  printf("ARRAY CHECK START \r\n");
  while (test_b[31] != 0xFF || test_b[0] != 0xFF)
  {
    printf("i ---> %d\r\n", i);
    for (i = 0; i <= 0xFF; i++)
    {
      #if 0
      printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\r\n");
      for ( j=0 ; j<32 ; j++ )
      {
        if ( j && (j%16)==0 ) printf("\r\n");
        else if ( j && (j%8)==0 ) printf("  ");
        printf("%02X ", test_b[j]);
      }
      printf("\r\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\r\n");
      #endif
      e = __serial_write(gzigbee._imtif.h, 0, test_b, 32, 0, p);
      if ( e < 0 )
      {
        printf("__serial_write fail %08X\r\n", e);
      }
      else
      {
        delay(20);
      }

      if ( i==0xFF ) break;
      test_b[0]++;
    }

    for (k = 0; k < 32; k++)
    {
      if (test_b[k]>=0xFF)
      {
        test_b[k] = 0;
        test_b[k + 1]++;
      }
    }
  }
  printf("End Of ARRAY CHECK \r\n");
}
#endif




void nzigbeeEnablePacket(struct cnLiteIO* p, int32_t id)
{
  int32_t e = 0;
  int32_t i = 0;
  int32_t sz = 32;
  e = __serial_write(gzigbee._imtif.h, 0, nzprotocol[id], sz, 0, p);
  if ( e > 0 )
  {
    BOX("write");
    for( i=0 ; i<sz ; i++ )
    {
      if ( (i%16) == 0 ) printf("\r\n"); 
      else if ( (i%8) == 0 ) printf("  "); 
      printf("%02X ", nzprotocol[id][i]);
    }
    printf("\r\n");
  }
}




void nzigbeeEnable(struct cnLiteIO* p)
{
  int32_t e = 0;
  int32_t i = 0;
  int32_t j = 0;

  printf("Press any key to start...\r\n");
  getchar();
  for ( i=0 ; i<2 ; i++ )
  {
    for ( j=0 ; j<MAX_PACKET ; j++ )
    {
      nzigbeeEnablePacket(p, j);
      printf("Press any key to continue...\r\n");
      getchar();
    }
  }

  printf("End of Enable Packet.....\r\n");

  //arrCheck(p);
  //return;


}

int32_t nzigbee_CheckProtocol(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnzigbee* p = (cnzigbee*)o;

  if ( p->buf[0] == 0x04 )
  {

  }
  else if ( p->buf[0] == 0x3A )
  {

  }
  else if ( p->buf[0] == 0x3B )
  {
    p->SR <<= 1;
    if ( p->SR & 0x80 )
    {
      p->idx = 0;
      __serial_write(gzigbee._imtif.h, gzigbee.fd, ackprotocol[gzigbee.idx], 32, 0, &gzigbee);
      printBuffer("--------> ACK", ackprotocol[gzigbee.idx], 32);
    }
  }
  else if ( p->buf[0] == 0x01 )
  {
  }
  else if ( p->buf[0] == 0x03 )
  {
    if ( p->SR & 0x80 )
    {
      p->idx = 1;
      __serial_write(gzigbee._imtif.h, gzigbee.fd, ackprotocol[gzigbee.idx], 32, 0, &gzigbee);
      printBuffer("--------> ACK", ackprotocol[gzigbee.idx], 32);
      p->idx = 2;
      __serial_write(gzigbee._imtif.h, gzigbee.fd, ackprotocol[gzigbee.idx], 32, 0, &gzigbee);
      printBuffer("--------> ACK", ackprotocol[gzigbee.idx], 32);
      p->SR |= 0x01;
    }
  }
  else if ( p->buf[0] == 0x36 )
  {
    if ( (p->SR & 0x81) == 0x81 )
    {
      if ( p->buf[3] == 0x00 )
      {
        p->idx = 1;
        __serial_write(gzigbee._imtif.h, gzigbee.fd, ackprotocol[gzigbee.idx], 32, 0, &gzigbee);
        printBuffer("--------> ACK", ackprotocol[gzigbee.idx], 32);
        p->idx = 3;
        __serial_write(gzigbee._imtif.h, gzigbee.fd, ackprotocol[gzigbee.idx], 32, 0, &gzigbee);
        printBuffer("--------> ACK", ackprotocol[gzigbee.idx], 32);
      }
      else if ( p->buf[3] == 0x11 )
      {
        p->idx = 4;
        __serial_write(gzigbee._imtif.h, gzigbee.fd, ackprotocol[gzigbee.idx], 32, 0, &gzigbee);
        printBuffer("--------> ACK", ackprotocol[gzigbee.idx], 32);
        p->idx = 5;
        __serial_write(gzigbee._imtif.h, gzigbee.fd, ackprotocol[gzigbee.idx], 32, 0, &gzigbee);
        printBuffer("--------> ACK", ackprotocol[gzigbee.idx], 32);
      }
    }

  }

  p->sz -= MAX_SZ;

  return 0;
}

int32_t nzigbee_CheckBuffer(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnzigbee* p = (cnzigbee*)o;

  memcpy(&p->buf[p->sz], b, sz);
  p->sz += sz;

  printBuffer("CHECK", p->buf,p->sz);

  return p->sz;
}

int32_t nzigbee_connected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnzigbee* p = (cnzigbee*)o;
  printf(" nzigbee_connected   ->   %08X\r\n", sz);
  return 0;
}

int32_t nzigbee_disconnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cnzigbee* p = (cnzigbee*)o;
  printf(" nzigbee_disconnected   ->   %08X \r\n", sz);

  return 0;
}


int32_t nzigbee_read(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  int32_t s = 0;
  cnzigbee* p = (cnzigbee*)o;


  p->buf[p->sz] = *b;
  p->sz++;
  if ( p->sz == MAX_SZ )
  {
    printBuffer("Read", p->buf, p->sz);
    nzigbee_CheckProtocol(h, fd, b, sz, extra, o);
  }
  p->sz %= MAX_SZ;



  //*(b+sz) = 0;

  //e = nzigbee_CheckBuffer(h, fd, b, sz, extra, o);
  //if ( e >= MAX_SZ )
  //{
  //  nzigbee_CheckProtocol(h, fd, b, sz, extra, o);
  //}



  #if 0
  to_raw(b, sz, rbuf, &s);
  BOX("read");
  printf("%s\r\n", rbuf);
  printf("<<<\r\n<<<%s\r\n<<<\r\n",b);
  #endif

    #if 0
    {
      int32_t j=0;
      printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\r\n");
      for ( j=0 ; j<32 ; j++ )
      {
        if ( j && (j%16)==0 ) printf("\r\n");
        else if ( j && (j%8)==0 ) printf("  ");
        printf("%02X ", test_b[j]);
      }
      printf("\r\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\r\n");
    }
    #endif


  return 0;
}

int32_t nzigbee_open(cnzigbee* p)
{
  int32_t e = 0;
  int8_t _json[1024] = {0};
  int8_t _argv[4][256] = {0};

  p->_imtif.callback[IMTIF_CALLBACK_CONNECTED] = nzigbee_connected;
  p->_imtif.callback[IMTIF_CALLBACK_DISCONNECTED] = nzigbee_disconnected;
  p->_imtif.callback[IMTIF_CALLBACK_READ] = nzigbee_read;

  readArgs(p->_ind->argc, p->_ind->argv, "--X", _argv[0]);
  readArgs(p->_ind->argc, p->_ind->argv, "--zigbee_port", _argv[1]);

  sprintf(_json, 
          "{"
            "\"SYSTEM_LIBRARY\":\"%s\","
            "\"PORT\":\"%s\","
            "\"BAUDRATE\":\"115200\","
            "\"DATABIT\":\"8\","
            "\"STOPBIT\":\"1\","
            "\"PARITYBIT\":\"0\","
            "\"BUF_SZ\":\"1\","
            "\"SYNC\":\"DISABLE\""
          "}",
          _argv[0],
          _argv[1]
  );

  p->fd = e = __serial_open(&p->_imtif.h, _json, p->_imtif.callback, p);
  return p->fd;
}


int32_t nzigbee_close(cnzigbee* p)
{
  return __serial_close(&p->_imtif.h);
}


int32_t nzigbee(struct cnLiteIO* p)
{
  int32_t e = 0;
  uint8_t b[128] = {0};

  gzigbee._ind = p;
  gzigbee.SR = 0x20;
  e = nzigbee_open(&gzigbee);
  printf("nzigbee_open ---> %d %08X\r\n", e, e);
  //nzigbeeEnable(p);
  return e;
}

void nzigbee_loop(struct cnLiteIO* p)
{
  int32_t e = 0;

  if ( gzigbee.idx >=0 )
  {
  }
  //{
  //  //__serial_write(gzigbee._imtif.h, gzigbee.fd, ackprotocol[gzigbee.idx], 32, 0, &gzigbee);
  //  //printBuffer("ACK", ackprotocol[gzigbee.idx], 32);
  //  gzigbee.idx = -1;
  //}

  //if( gzigbee.SR&0x80 )
  //{
  //  gzigbee.SR &= 0x7F;
  //  __serial_write(gzigbee._imtif.h, gzigbee.fd, ackprotocol[0], 32, 0, &gzigbee);
  //  printBuffer("ACK", ackprotocol[0], 32);
  //}
  //else if( gzigbee.SR&0x40 )
  //{
  //  gzigbee.SR &= 0xBF;
  //  e = __serial_write(gzigbee._imtif.h, gzigbee.fd, ackprotocol[1], 32, 0, &gzigbee);
  //  printBuffer("ACK", ackprotocol[1], 32);
  //  e = __serial_write(gzigbee._imtif.h, gzigbee.fd, ackprotocol[2], 32, 0, &gzigbee);
  //  printBuffer("ACK", ackprotocol[2], 32);
  //}
  //else if( gzigbee.SR&0x20 )
  //{
  //  gzigbee.SR &= 0xDF;
  //  e = __serial_write(gzigbee._imtif.h, gzigbee.fd, ackprotocol[3], 32, 0, &gzigbee);
  //  printBuffer("ACK", ackprotocol[3], 32);
  //  e = __serial_write(gzigbee._imtif.h, gzigbee.fd, ackprotocol[4], 32, 0, &gzigbee);
  //  printBuffer("ACK", ackprotocol[4], 32);
  //}
  //else if( gzigbee.SR&0x10 )
  //{
  //  gzigbee.SR &= 0xEF;
  //  e = __serial_write(gzigbee._imtif.h, gzigbee.fd, ackprotocol[5], 32, 0, &gzigbee);
  //  printBuffer("ACK", ackprotocol[5], 32);
  //}
  //if( gzigbee.SR&0x80 )
  //{
  //  gzigbee.SR &= 0x7F;
  //  {
  //    int32_t i=0;
  //    for ( ; i<7 ; i++ )
  //    {
  //      __serial_write(gzigbee._imtif.h, gzigbee.fd, ackprotocol[i], 32, 0, &gzigbee);
  //      printBuffer("ACK", ackprotocol[i], 32);
  //      delay(10);
  //    }
  //  }
  //}

}








