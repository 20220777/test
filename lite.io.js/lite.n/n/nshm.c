#if __NSHM__
#include <nshm.h>
#include <nutil.h>
#include <nm.h>
#include <idebug.h>
#if __LINUX__
#include <signal.h>
#include <sys/types.h>
#include <sys/shm.h>
#endif


cnshm* gshm;

#if __LINUX__
void nshm_signal_hanlder(int sid)
{
  uint8_t   mem[1024];
  int32_t i = 0;

  //DEBUG_PRINT(" %d \r\n", sid);


  __liteio_call(gshm->_ind, 0, 0, gshm->p, 8192);

  // for ( i=0 ; i<1024 ; i++ )
  // {
  //   printf("%02X ", *(gshm->p+i));
  // }
}
#endif

#if __LINUX__
void set_signal(void* h, uint32_t key, int32_t size)
{
  // int32_t id = 0;

  // id = shmget(key, size, 0666|IPC_CREAT);

  // ((cnshm*)h)->p = shmat(id, 0, 0);
  signal(SIGUSR1, nshm_signal_hanlder);
}
#endif


int32_t nshm_closer(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;

  //e=__http_close_socket(p->_imtif.h, fd);
  //DEBUG_PRINT("close -> %d %08X\r\n", fd, fd);
  return e;
}


int32_t nshm_writer(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;
  int32_t e2= 0;
  int32_t pid = 0;

  #if __LINUX__
  if ( extra!= 0 )
  {
    e2 = __getpid((uint8_t*)extra, &pid);
  }
  #endif

  e = __shm_write(((cnshm*)h)->_imtif.h, b, sz);
  #if __LINUX__
  if ( e2 > 0 )
  {
    kill(pid, SIGUSR1);
  }
  #endif

  return e;
}

int32_t nshm_reader(void* h, int32_t fd, int8_t* b, int32_t sz, void* extra, void* o)
{
  int32_t e = 0;

  e = __shm_read(((cnshm*)h)->_imtif.h, b, sz);

  return e;
}


int32_t nshm_write(void* h, int8_t* b, int32_t sz)
{
  return __shm_write(((cnshm*)h)->_imtif.h, b, sz);
}

int32_t nshm_read(void* h, int8_t* b, int32_t sz)
{
  return __shm_read(((cnshm*)h)->_imtif.h, b, sz);
}


int32_t nshm_open(cnshm* p)
{
  int32_t e = 0;
  int8_t _json[1024] = {0};
  int8_t _argv[4][256] = {0};

  gshm = p;

  DEBUG_PRINT("%s \r\n", _argv);
  DEBUG_PRINT("%s \r\n", _argv);

  readArgs(p->_ind->argc, p->_ind->argv, "--shm_key", _argv[0]);
  readArgs(p->_ind->argc, p->_ind->argv, "--shm_size", _argv[1]);

  sprintf(_json, 
          "{"
            "\"KEY\":\"%s\","
            "\"SIZE\":\"%s\","
          "}",
          _argv[0],
          _argv[1]
  );


  DEBUG_PRINT("%s \r\n", _json);
  e = __shm_open(&p->_imtif.h, _json);
  DEBUG_PRINT("%08X \r\n", e);


  __shm_get(p->_imtif.h, &p->p);


  #if __LINUX__
  DEBUG_PRINT("pid : %d\r\n", getpid());
  set_signal(p, atoi(_argv[0]), atoi(_argv[1]));
  #endif


  return e;
}


int32_t nshm_close(cnshm* p)
{
  return __shm_close(&p->_imtif.h);
}


int32_t nshm(struct cnLiteIO* p)
{
  int32_t e = 0;
  cnshm* pd = (cnshm*)calloc(1, sizeof(cnshm));
  p->hdl[NSHM] = pd;
  pd->_ind = p;

  DEBUG_PRINT("\r\n");

  e = nshm_open(pd);
  return e;
}

int32_t nshm_free(struct cnLiteIO* p)
{
  nshm_close((cnshm*)p->hdl[NSHM]);
  free(p->hdl[NSHM]);
  p->hdl[NSHM] = 0;
  return 0;
}

void nshm_loop(struct cnLiteIO* p)
{
  // int32_t idx = 0;
  // cnhttpd* pd = (cnhttpd*)p->hdl;
  // idx = get_item(&pd->_itms);
  // if ( idx>=0 )
  // {
  //   // printf(" idx ---> %d \r\n", idx);
  //   // {
  //   //   int8_t hb[1024] = {0};
  //   //   int32_t s = 0;
  //   //   to_raw(pd->_itms.arg[idx].b, pd->_itms.arg[idx].sz, hb, &s);

  //   //   printf("-->%d<--\r\n--\r\n--> %s \r\n--\r\n",s, hb);
  //   // }

  //   if (p->fx) p->fx(p->obj, pd->_itms.arg[idx].fd, pd->_itms.arg[idx].b);
  // }



}
#endif
