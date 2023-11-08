#include <mdbc.h>
#include <ICodeX.h>


#if (defined XWIN32 || defined WINCE)
#pragma pack(1)
#endif
typedef struct
{
  MYSQL*        _conn;
  MYSQL         conn;
  MYSQL_RES     res;
  MYSQL_ROW     row;
  uint32_t  SR;
  int8_t          info[8][32];
  void*         (*cbf)(int32_t);

}MDBC;
#if (defined XWIN32 || defined WINCE)
#pragma pack()
#endif


void* mdbcConnector(void* arg)
{
  int32_t e = 0;
  MDBC* p = (MDBC*)arg;

  set_hex_semaphore(&p->SR, 0x00000001, 0x00000001);
  for ( ; ; )
  {
    //if ( get_hex_semaphore(&p->SR, 0x00000002, 0x00000002, 1) == 0 ) break;

    p->cbf(1);
    p->_conn = mysql_real_connect(&p->conn, TEXT(p->info[0]), TEXT(p->info[1]), TEXT(p->info[2]), TEXT(p->info[3]), atoi(TEXT(p->info[4])), 0, 0);

    if ( p->_conn == 0 )
    {
      p->cbf(-1);
      mysql_close(p->_conn);
    }
    else
    {
      p->cbf(0);
    }
    break;
  }
  set_hex_semaphore(&p->SR, 0x00000002, 0x00000000);
  //thread_exit(0, 0);
  return 0;
}




int32_t mdbcOpen(void** hdl, int8_t* host, int8_t* port, int8_t* user, int8_t* pass, int8_t* name, void* (*f)(int32_t) )
{
  int32_t e = 0;
  uint32_t tid;
  MDBC* p;

  if (*hdl !=0 )
  {
    free(*hdl);
    *hdl=0;
  }
  p = *hdl = (MDBC*)calloc(1, sizeof(MDBC));
  
  mysql_init(&((MDBC*)(*hdl))->conn);

  sprintf(p->info[0], host);
  sprintf(p->info[1], user);
  sprintf(p->info[2], pass);
  sprintf(p->info[3], name);
  sprintf(p->info[4], port);

  p->cbf = f;

  thread_create(mdbcConnector, (void*)*hdl, (void*)&tid);
  e = get_hex_semaphore(&p->SR, 0x00000001, 0x00000001, 8192);

  return 0;
}

int32_t mdbcClose(void** hdl)
{
  if ( *hdl != 0 )
  {
    mysql_close(((MDBC*)(*hdl))->_conn);

    free(*hdl);
    *hdl = 0;
  }
  return 0;
}

int32_t mdbcRead(void* hdl, int32_t fd, int8_t* b, int32_t sz)
{
  int32_t e = 0;

  return e;
}

int32_t mdbcWrite(void* hdl, int32_t fd, int8_t* b, int32_t sz)
{
  int32_t e = 0;
  MDBC*  p = (MDBC*)hdl;
  int8_t query[1024] = {0, };
  
  sprintf(query, TEXT("insert into Machine_Parameter_Out ( id, machine_code, parameter_code, stauts_log, date_time ) values ( '갑피생산공정', '0', '0', '','')"));

  mysql_query(p->_conn, query);

  return e;
}

int32_t mdbcQuery(void* hdl, int32_t fd, int8_t* query, int32_t sz)
{
  int32_t e = 0;
  MDBC*  p = (MDBC*)hdl;

  if ( p->_conn == 0) return -1;


  e = mysql_query(p->_conn, query);

  return e;
}

