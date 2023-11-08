#if __NTCPD__
#include <ntcpd.h>
#include <nutil.h>
#include <idebug.h>

static cntcpd gtcpd;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////                                                                   //////
//////                                                                   //////
//////                         USER FUNCTIONS                            //////
//////                                                                   //////
//////                                                                   //////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************/
/*****************************************************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*****************************                ********************************/
/*******************************            **********************************/
/*********************************        ************************************/
/************************************   **************************************/
/************************************* ***************************************/
/*****************************************************************************/
//void* TCPClientRequest(cntcpd* p)
//{
//  int32_t e = 0;
//  uint8_t i = 0;
//  uint8_t modbus_protocol[64] = { 0};
//  uint8_t hbuf[8192] = {0};
//  uint32_t hsz = 0;
//  int16_t _addr = 0;
//  int16_t _len  = 4;
//
//
//
//  //if ( p->readplc.SR&0x80 )
//  //{
//  //  _addr = (int16_t)atoi(p->readplc.cmd[2]);
//  //  _len  = (int16_t)atoi(p->readplc.cmd[3]);
//  //}
//
//  modbus_protocol[i++] = 0x00;
//  modbus_protocol[i++] = 0;
//  modbus_protocol[i++] = 0x00;
//  modbus_protocol[i++] = 0x00;
//  modbus_protocol[i++] = 0x00;
//  modbus_protocol[i++] = 0x06;
//
//  modbus_protocol[i++] = 0x01;
//
//  modbus_protocol[i++] = 0x04;
//  modbus_protocol[i++] = (_addr&0xFF00)>>8;
//  modbus_protocol[i++] = (_addr&0x00FF);
//  modbus_protocol[i++] = (_len &0xFF00)>>8;
//  modbus_protocol[i++] = (_len &0x00FF);
//
//  e = __socket_write(p->_imtif.h, 0, modbus_protocol, i, 0, p);
//  to_raw(modbus_protocol, i, hbuf, &hsz);
//  printf("XSOCKET  ->   %10s -> [%4d] %s\r\n", "request", hsz, hbuf);
//  return 0;
//}
//


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//////                                                                   //////
//////                                                                   //////
//////                       SYSTEM FUNCTIONS                            //////
//////                                                                   //////
//////                                                                   //////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/*****************************************************************************/
/*****************************************************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*********************************        ************************************/
/*****************************                ********************************/
/*******************************            **********************************/
/*********************************        ************************************/
/************************************   **************************************/
/************************************* ***************************************/
/*****************************************************************************/




int32_t ntcpd_closer(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cntcpd* p = (cntcpd*)o;
  int32_t e = 0;

  e = __socket_close_fd(p->_imtif.h, fd);
  DEBUG_PRINT("e -> %d %08X\r\n", e, e);

  return e;
}


int32_t ntcpd_writer(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  cntcpd* p = (cntcpd*)o;

  DEBUG_PRINT("%08X:%4d:%4d\r\n%s\r\n",p,fd, sz, b);
  e=__socket_write(p->_imtif.h, fd, b, sz, 0, o);
  DEBUG_PRINT("e -> %d %08X\r\n", e, e);

  return e;
}


int32_t ntcpd_connected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cntcpd* p = (cntcpd*)o;
  int32_t idx = (extra==0)?0:(*(int32_t*)extra);

  printf(" ntcpd_connected   ->   %08X %d %d\r\n", sz, idx, p->conn_status);

  p->conn_status = 1;
  return 0;
}

int32_t ntcpd_disconnected(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cntcpd* p = (cntcpd*)o;
  printf(" ntcpd_disconnected   ->   %08X \r\n", sz);

  p->conn_status = -1;
  return 0;
}


int32_t ntcpd_read(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  cntcpd* p = (cntcpd*)o;
  uint8_t hbuf[8192] = {0};
  uint32_t hsz = 0;
  to_raw(b, sz, hbuf, &hsz);

  printf(" ntcpd_read   ->   %s \r\n", hbuf);
  return 0;
}

int32_t ntcpd_open(cntcpd* p)
{
  int32_t e = 0;
  int8_t _json[1024] = {0};

  p->_imtif.callback[IMTIF_CALLBACK_CONNECTED] = ntcpd_connected;
  p->_imtif.callback[IMTIF_CALLBACK_DISCONNECTED] = ntcpd_disconnected;
  p->_imtif.callback[IMTIF_CALLBACK_READ] = ntcpd_read;

  #if defined XWIN32
  sprintf(_json,
          "{"
            "\"SYSTEM_LIBRARY\":\"mtif.x86.dll\","
            "\"IP\":\"192.168.0.2\","
            "\"PORT\":\"9999\","
            "\"CSTYPE\":\"SERVER\","
            "\"PROTOCOL\":\"TCP\","
            "\"CASTTYPE\":\"UNICAST\","
            "\"SYNC\":\"DISABLE\","
            "\"TIMEOUT\":\"2000\""
          "}"
          );
  #endif

  #if defined x32
  sprintf(_json,
          "{"
            "\"SYSTEM_LIBRARY\":\"/usr/xlocal/projectX/tools/ngine/pkg/mtif.x32.so\","
            "\"IP\":\"192.168.0.10\","
            "\"PORT\":\"9999\","
            "\"CSTYPE\":\"SERVER\","
            "\"PROTOCOL\":\"TCP\","
            "\"CASTTYPE\":\"UNICAST\","
            "\"SYNC\":\"DISABLE\","
            "\"TIMEOUT\":\"2000\""
          "}"
          );
  #endif


  #if defined a32
  sprintf(_json,
          "{"
            "\"SYSTEM_LIBRARY\":\"/usr/local/node/a32/mtif.a32.so\","
            "\"IP\":\"192.168.0.10\","
            "\"PORT\":\"9999\","
            "\"CSTYPE\":\"SERVER\","
            "\"PROTOCOL\":\"TCP\","
            "\"CASTTYPE\":\"UNICAST\","
            "\"SYNC\":\"DISABLE\","
            "\"TIMEOUT\":\"2000\",,,"
          "}"
          );
  #endif

  e = __socket_open(&p->_imtif.h, _json, p->b, 4096, p->_imtif.callback, p);
  return e;
}


int32_t ntcpd_close(cntcpd* p)
{
  return __socket_close(&p->_imtif.h);
}


int32_t ntcpd(struct cnLiteIO* p)
{
  int32_t e = 0;
  e = ntcpd_open(&gtcpd);
  return e;
}


void ntcpd_loop(struct cnLiteIO* p)
{
  int32_t e = 0;
  uint8_t b[16] = {0};
  uint8_t hex = 0;

  //{

  //  printf(" gtcpd.conn_status %d \r\n", gtcpd.conn_status );

  //  if ( gtcpd.conn_status == 0 )
  //  {
  //    e = ntcpd_open(&gtcpd);
  //    printf("ntcpd_open : %08X \r\n", e);
  //    //gtcpd.conn_status = -2;
  //  }



  //  if ( gtcpd.conn_status == -1 )
  //  {
  //    e = ntcpd_close(&gtcpd);
  //    printf("ntcpd_close : %08X \r\n", e);
  //    gtcpd.conn_status = 0;
  //  }


  //  if ( gtcpd.conn_status == 1 )
  //  {
  //    //TCPClientRequest(&gtcpd);

  //    //int32_t i = 0;
  //    //delay(500);
  //    //for ( i=0 ; i<16 ;i++ )
  //    //{
  //    //  b[i] = hex%26 + 'A';
  //    //}
  //    //e = __socket_write(gtcpd._imtif.h, 0, b, 16, 0, &gtcpd);

  //    //printf(" write (%d)-> %02X \r\n", e, b[0]);
  //    //gtcpd.conn_status = -1;

  //    //hex++;
  //  }
  //}


}
#endif