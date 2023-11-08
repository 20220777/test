#include <mdbc.h>


#if (defined XWIN32 || defined WINCE)
#pragma pack(1)
#endif
typedef struct
{
  MYSQL*        _conn;
  MYSQL         conn;
  MYSQL_RES     res;
  MYSQL_ROW     row;
  unsigned int  SR;
  char          info[8][32];
  void*         (*cbf)(int);
}MDBC;
#if (defined XWIN32 || defined WINCE)
#pragma pack()
#endif


void* mdbcConnector(void* arg)
{
  int e = 0;
  MDBC* p = (MDBC*)arg;

  set_hex_semaphore(&p->SR, 0x00000001, 0x00000001);
  for ( ; ; )
  {
    if ( get_hex_semaphore(&p->SR, 0x00000002, 0x00000002, 1) == 0 ) break;

    p->cbf(1);
    p->_conn = mysql_real_connect(&p->conn, TEXT(p->info[0]), TEXT(p->info[1]), TEXT(p->info[2]), TEXT(p->info[3]), atoi(TEXT(p->info[4])), 0, 0);

    if ( p->_conn == 0 )
    {
      p->cbf(-1);
      mysql_close(p->_conn);
      free(p);
      p = 0;
    }
    else
    {
      p->cbf(0);
    }
    break;
  }
  set_hex_semaphore(&p->SR, 0x00000002, 0x00000000);
  thread_exit(0, 0);
  return 0;
}




int mdbcOpen(void** hdl, char* host, char* port, char* user, char* pass, char* name, void* (*f)(int) )
{
  int e = 0;
  unsigned int tid;
  MDBC* p;
  p = *hdl = (MDBC*)calloc(1, sizeof(MDBC));
  
  mysql_init(&((MDBC*)(*hdl))->conn);

  sprintf(p->info[0], host);
  sprintf(p->info[1], user);
  sprintf(p->info[2], pass);
  sprintf(p->info[3], name);
  sprintf(p->info[4], port);

  p->cbf = f;

  thread_create(mdbcConnector, (void*)p, (void*)&tid);
  e = get_hex_semaphore(&p->SR, 0x00000001, 0x00000001, 8192);
  if ( e < 0 )
  {
  }

  return 0;
}

int mdbcClose(void** hdl)
{
  if ( *hdl != 0 )
  {
    mysql_close(((MDBC*)(*hdl))->_conn);

    free(*hdl);
    *hdl = 0;
  }
  return 0;
}

int mdbcRead(void* hdl, int fd, char* b, int sz)
{
  int e = 0;

  return e;
}

int mdbcWrite(void* hdl, int fd, char* b, int sz)
{
  int e = 0;
  MDBC*  p = (MDBC*)hdl;
  char query[1024] = {0, };
  
  sprintf(query, TEXT("insert into Machine_Parameter_Out ( id, machine_code, parameter_code, stauts_log, date_time ) values ( '갑피생산공정', '0', '0', '','')"));

  mysql_query(p->_conn, query);

  return e;
}

int mdbcQuery(void* hdl, int fd, char* query, int sz)
{
  int e = 0;
  MDBC*  p = (MDBC*)hdl;

  e = mysql_query(p->_conn, query);

  return e;
}

