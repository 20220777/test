#include <uv.h>
#include <assert.h>
#include <stdlib.h>
#include <node_api.h>
#include <__nLite.h>
#include <__util.h>
#include <xcommon.h>


#define N_STATUS       0
#define N_READER       1
#define MAX_N_RS       2
#define MAX_NARG       1024
#define MAX_BUF_SZ     8192

#define __assert(a)     assert(a)


#define NAPI_STATUS(a)    if(napi_ok!=a) printf("%8d [%s]\r\n", errno, strerror(errno));DEBUG_PRINT("\r\n");//(assert(napi_ok==a);
//#define NAPI_STATUS(a)   DEBUG_PRINT("\r\n");assert(napi_ok==a);
  


#if __NHTTP__
#define ARGS "null --m node --d WAAS_NODE --s WAAS_NODE --exec http "
#endif

#if __NHTTPD__
#define ARGS "null --m node --d WAAS_NODE --s WAAS_NODE --exec httpd "
#endif

#if __NHTTPSD__
#define ARGS "null --m node --d WAAS_NODE --s WAAS_NODE --exec httpsd "
#endif

#if __NSERIAL__
#define ARGS "null --m node --d WAAS_NODE --s WAAS_NODE --exec serial "
#endif

#if __NSHM__
#define ARGS "null --m node --d WAAS_NODE --s WAAS_NODE --exec shm "
#endif

#if __NSOCKET__
#define ARGS "null --m node --d WAAS_NODE --s WAAS_NODE --exec socket "
#endif

#if __NWEBSOCKET__
#define ARGS "null --m node --d WAAS_NODE --s WAAS_NODE --exec websocket "
#endif

#if __NTCP__
#define ARGS "null --m node --d WAAS_NODE --s WAAS_NODE --exec tcp "
#endif

#if __NTCPD__
#define ARGS "null --m node --d WAAS_NODE --s WAAS_NODE --exec tcpd "
#endif

#if __NTCPSD__
#define ARGS "null --m node --d WAAS_NODE --s WAAS_NODE --exec tcpsd "
#endif

#if __NWSC__
#define ARGS "null --m node --d WAAS_NODE --s WAAS_NODE --exec wsc "
#endif

#if __NWSD__
#define ARGS "null --m node --d WAAS_NODE --s WAAS_NODE --exec wsd "
#endif



#define USE_WRITE_CALLBACK       0


#define MAX_G_IDX       512
uint32_t g_idx = 0;
uint8_t g_buffer[MAX_G_IDX][1024] = {0};


typedef struct
{
  void* h;
  napi_env* _env;
  napi_value _callback;
  napi_async_work work;
  napi_threadsafe_function tsfx;
  struct nArg nargs[MAX_NARG];
  struct nArg arg;
  uint32_t nidx;
  uint32_t SR;
  napi_callback_info*  _callback_info;
  uv_mutex_t mutex;
}cnLiteIO;

int32_t count_args(int8_t* s)
{
  int32_t c=0;
  for ( ; *s==' ' ; s++ );
  for ( ; ; s++ )
  {
    if ( *s==' ' ) c++;
    if ( *(s+1)==0 )
    {
      if ( *s!=' ' ) c++;
      break;
    }
  }
  return c;
}

int32_t get_args(int8_t* s, int32_t idx, int8_t* o)
{
  int32_t e = -1;
  int32_t i = 0;
  int32_t _idx = 0;

  for ( ; *s==' ' ; s++ );

  for ( i=0; *s!=0 ; s++,i++ )
  {
    *(o+i) = *s;
    if ( *s==' ' )
		{
			if ( idx == _idx )
      {
        *(o+i) = 0;
        e = i;
				break;
      }
			_idx++;
      i = -1;
		}
  }

  if ( i>0 )
  {
    e = i;
    *(o+i) = 0;
  }
  return e;
}


#if USE_WRITE_CALLBACK
static void js_write(napi_env env, napi_value js_cb, void* context, void* arg)
{
  // This parameter is not used.
  (void) context;
  napi_status status;
  napi_value undefined;
  napi_value _nv[4] = {0};
  int32_t idx = 0;
  struct nArg* _arg = (struct nArg*)arg;

  DEBUG_PRINT("\r\n");

  write(_arg->fd, _arg->b, _arg->sz);

  free(_arg->b);
  free(_arg);

  DEBUG_PRINT("\r\n");
}
#endif

static napi_value liteio_write(napi_env env, napi_callback_info info)
{
  napi_valuetype vtype[16] = {0};
  napi_value args[16] = {0};
  napi_value callback = 0;
  napi_value global = 0;
  napi_value result = 0;
  napi_value argv[16] = {0};
  napi_value r = 0;

  uint32_t argc = 16;
  uint32_t idx = 0;
  cnLiteIO* _nliteio = 0;
  void* hdl;
  int32_t _asz = 0;
  int32_t e = 0;
  struct nArg*  parg = 0;


  NAPI_STATUS(napi_get_cb_info(env, info, &argc, args, 0, (void**)(&_nliteio)));
  hdl = _nliteio->h;

  DEBUG_PRINT("argc %d\r\n", argc);
  if ( argc < 3 ) return 0;

  #if 1
  idx = 0;
  if ( args[idx] == 0 )
  {
    DEBUG_PRINT("args[%d] -> %s\r\n", idx, args[idx]==0?"NULL":"NOT NULL");
    return 0;
  }
  NAPI_STATUS(napi_typeof(env, args[idx], &vtype[idx]));
  DEBUG_PRINT("vtype[%d] -> %d\r\n", idx, vtype[idx]);
  if ( vtype[idx] == 0 ) return 0;
  if ( vtype[idx] != napi_number  )
  {
    napi_throw_type_error(env, "TYPE_ERROR", "napi_number 1");
    return 0;
  }

  idx = 1;
  if ( args[idx] == 0 )
  {
    DEBUG_PRINT("args[%d] -> %s\r\n", idx, args[idx]==0?"NULL":"NOT NULL");
    return 0;
  }
  NAPI_STATUS(napi_typeof(env, args[idx], &vtype[idx]));
  DEBUG_PRINT("vtype[%d] -> %d\r\n", idx, vtype[idx]);
  if ( vtype[idx] == 0 ) return 0;
  if ( vtype[idx] != napi_string && vtype[idx] != napi_object )
  {
    napi_throw_type_error(env, "TYPE_ERROR", "napi_string or napi_object");
    return 0;
  }

  idx = 2;
  if ( args[idx] == 0 )
  {
    DEBUG_PRINT("args[%d] -> %s\r\n", idx, args[idx]==0?"NULL":"NOT NULL");
    return 0;
  }
  NAPI_STATUS(napi_typeof(env, args[idx], &vtype[idx]));
  DEBUG_PRINT("vtype[%d] -> %d\r\n", idx, vtype[idx]);
  if ( vtype[idx] == 0 ) return 0;
  if ( vtype[idx] != napi_number )
  {
    napi_throw_type_error(env, "TYPE_ERROR", "napi_number 3");
    return 0;
  }

  if ( argc == 4 )
  {
    idx = 3;
    if ( args[idx] == 0 )
    {
      DEBUG_PRINT("args[%d] -> %s\r\n", idx, args[idx]==0?"NULL":"NOT NULL");
      return 0;
    }
    NAPI_STATUS(napi_typeof(env, args[idx], &vtype[idx]));
    DEBUG_PRINT("vtype[%d] -> %d\r\n", idx, vtype[idx]);
    if ( vtype[idx] == 0 ) return 0;
    if ( vtype[idx] != napi_string )
    {
      napi_throw_type_error(env, "TYPE_ERROR", "napi_string 4");
      return 0;
    }
  }
  #endif

  parg = (struct nArg*)calloc(1, sizeof(struct nArg));
  idx = 0;
  if ( napi_get_value_int32(env, args[idx], &parg->fd) != napi_ok )
  {
    free(parg);
    return 0;
  }
  DEBUG_PRINT("parg->fd : %d\r\n", parg->fd);

  idx = 2;
  if ( napi_get_value_int32(env, args[idx], &parg->sz) != napi_ok )
  {
    free(parg);
    return 0;
  }
  DEBUG_PRINT("parg->sz : %d\r\n", parg->sz);

  idx = 1;
  if ( vtype[idx] == napi_object )
  {
    if ( napi_get_buffer_info(env, args[idx],(void**)&parg->b, &_asz) != napi_ok )
    {
      free(parg);
      return 0;
    }
    parg->asz = parg->sz;
  	DEBUG_PRINT("napi_object %4d:%4d\r\n", _asz, parg->asz);
    DEBUG_BUFFER(parg->b, parg->sz);
  }
  else if ( vtype[idx] == napi_string )
  {
    parg->bs = (int8_t*)calloc(parg->sz*4, sizeof(int8_t));
    if ( napi_get_value_string_utf8(env, args[idx], parg->bs, parg->sz*4, &parg->asz) != napi_ok )
    {
      free(parg->bs);
      free(parg);
      return 0;
    }
  	DEBUG_PRINT("napi_string %d, [%s] -\r\n", parg->asz, parg->bs);
    parg->b = parg->bs;
  }


  DEBUG_PRINT("\r\n");

  parg->ext = (int8_t*)calloc(MAX_BUF_SZ, sizeof(int8_t));
  if ( argc==4 )
  {
    idx = 3;
    if ( napi_get_value_string_utf8(env, args[idx], parg->ext, MAX_BUF_SZ, &_asz) != napi_ok )
    {
      free(parg->ext);
      if ( parg->bs ) free(parg->bs);
      free(parg);
      return 0;
    }
    DEBUG_PRINT("%d, %s\r\n", _asz, parg->ext);
  }


	DEBUG_BUFFER(parg->b, parg->asz);
  DEBUG_PRINT("%d -> %d:%d:%d\r\n", parg->fd, __NHTTPD__,__NSERIAL__,__NSOCKET__);
  #if __NHTTP__
  e = __liteio_http_write(hdl, parg->fd, parg->b, parg->sz, parg->ext, hdl);
  #endif

  #if __NHTTPD__
  e = __liteio_httpd_write(hdl, parg->fd, parg->b, parg->sz, parg->ext, hdl);
  #endif

  #if __NHTTPSD__
  e = __liteio_httpsd_write(hdl, parg->fd, parg->b, parg->sz, parg->ext, hdl);
  #endif

  #if __NSERIAL__
  DEBUG_PRINT("%d %s %d \r\n", parg->fd, parg->b, parg->sz);
  e = __liteio_serial_write(hdl, parg->fd, parg->b, parg->sz, parg->ext, hdl);
  #endif

  #if __NSOCKET__
  DEBUG_PRINT("%d %s %d \r\n", parg->fd, parg->b, parg->sz);
  e = __liteio_socket_write(hdl, parg->fd, parg->b, parg->sz, parg->ext, hdl);
  #endif

  #if __NWEBSOCKET__
  DEBUG_PRINT("%d %s %d \r\n", parg->fd, parg->b, parg->sz);
  e = __liteio_websocket_write(hdl, parg->fd, parg->b, parg->sz, parg->ext, hdl);
  #endif

  #if __NSHM__
  e = __liteio_shm_write(hdl, parg->fd, parg->b, parg->sz, parg->ext, hdl);
  #endif

  #if __NTCP__
  e = __liteio_tcp_write(hdl, parg->fd, parg->b, parg->sz, parg->ext, hdl);
  #endif

  #if __NTCPD__
  e = __liteio_tcpd_write(hdl, parg->fd, parg->b, parg->sz, parg->ext, hdl);
  #endif

  #if __NTCPSD__
  e = __liteio_tcpsd_write(hdl, parg->fd, parg->b, parg->sz, parg->ext, hdl);
  #endif

  #if __NWSC__
  e = __liteio_wsc_write(hdl, parg->fd, parg->b, parg->sz, parg->ext, hdl);
  #endif

  #if __NWSD__
  e = __liteio_wsd_write(hdl, parg->fd, parg->b, parg->sz, parg->ext, hdl);
  #endif

  free(parg->ext);
  if(parg->bs) free(parg->b);
  free(parg);

  NAPI_STATUS(napi_create_int32(env, e, &r));
  return r;
}



static napi_value liteio_read(napi_env env, napi_callback_info info)
{
  napi_valuetype vtype[16] = {0};
  napi_value args[16] = {0};
  napi_value callback = 0;
  napi_value global = 0;
  napi_value result = 0;
  napi_value argv[16] = {0};
  napi_value r = 0;

  uint32_t argc = 16;
  uint32_t idx = 0;
  cnLiteIO* _nliteio = 0;
  void* hdl;
  int32_t _asz = 0;
  int32_t e = 0;
  struct nArg*  parg = 0;

  NAPI_STATUS(napi_get_cb_info(env, info, &argc, args, 0, (void**)(&_nliteio)));
  hdl = _nliteio->h;

  DEBUG_PRINT("argc %d\r\n", argc);
  if ( argc < 3 ) return 0;

  idx = 0;
  if ( args[idx] == 0 )
  {
    DEBUG_PRINT("args[%d] -> %s\r\n", idx, args[idx]==0?"NULL":"NOT NULL");
    return 0;
  }
  NAPI_STATUS(napi_typeof(env, args[idx], &vtype[idx]));
  if ( vtype[idx] != napi_number && vtype[idx] != napi_number_expected )
  {
    napi_throw_type_error(env, "TYPE_ERROR", "napi_number 1");
    return 0;
  }

  idx = 1;
  if ( args[idx] == 0 )
  {
    DEBUG_PRINT("args[%d] -> %s\r\n", idx, args[idx]==0?"NULL":"NOT NULL");
    return 0;
  }
  NAPI_STATUS(napi_typeof(env, args[idx], &vtype[idx]));
  if ( vtype[idx] != napi_number && vtype[idx] != napi_number_expected )
  {
    napi_throw_type_error(env, "TYPE_ERROR", "napi_number 2");
    return 0;
  }


  idx = 2;
  if ( args[idx] == 0 )
  {
    DEBUG_PRINT("args[%d] -> %s\r\n", idx, args[idx]==0?"NULL":"NOT NULL");
    return 0;
  }
  NAPI_STATUS(napi_typeof(env, args[idx], &vtype[idx]));
  if ( vtype[idx] != napi_function && vtype[idx] != napi_function_expected )
  {
    napi_throw_type_error(env, "TYPE_ERROR", "napi_function 3");
    return 0;
  }

  parg = (struct nArg*)calloc(1, sizeof(struct nArg));

  NAPI_STATUS(napi_get_value_int32(env, args[0], &parg->fd));
  NAPI_STATUS(napi_get_value_int32(env, args[1], &parg->sz));
  if ( parg->sz <= 0 )
  {
    free(parg);
    return 0;
  }

  parg->b = (int8_t*)calloc(parg->sz*4, sizeof(int8_t));
  callback = args[2];
  parg->ext = 0;


  #if __NHTTP__
  e = read(parg->fd, parg->b, parg->sz);
  #endif

  #if __NHTTPD__
  e = read(parg->fd, parg->b, parg->sz);
  #endif

  #if __NHTTPSD__
  e = read(parg->fd, parg->b, parg->sz);
  #endif

  #if __NSERIAL__
  e = read(parg->fd, parg->b, parg->sz);
  #endif

  #if __NSOCKET__
  e = read(parg->fd, parg->b, parg->sz);
  #endif

  #if __NWEBSOCKET__
  e = read(parg->fd, parg->b, parg->sz);
  #endif

  #if __NSHM__
  e = __liteio_shm_read(hdl, parg->fd, parg->b, parg->sz, parg->ext, hdl);
  #endif

  #if __NTCP__
  e = read(parg->fd, parg->b, parg->sz);
  #endif

  #if __NTCPD__
  e = read(parg->fd, parg->b, parg->sz);
  #endif

  #if __NTCPSD__
  e = read(parg->fd, parg->b, parg->sz);
  #endif

  #if __NWSC__
  e = read(parg->fd, parg->b, parg->sz);
  #endif

  #if __NWSD__
  e = read(parg->fd, parg->b, parg->sz);
  #endif


  NAPI_STATUS(napi_create_buffer_copy(env, parg->sz, parg->b, 0, &argv[0]));

  NAPI_STATUS(napi_create_int32(env, parg->sz, &argv[1]));

  NAPI_STATUS(napi_get_global(env, &global));

  NAPI_STATUS(napi_call_function(env, global, callback, 2, argv, &result));

  free(parg->b);
  free(parg);

  NAPI_STATUS(napi_create_int32(env, e, &r));
  return r;
}


static napi_value liteio_close(napi_env env, napi_callback_info info)
{
  napi_value r = 0;
  uint32_t argc = 3;
  napi_value args[3];
  napi_valuetype valuetype;
  cnLiteIO* _nliteio = 0;
  void* hdl;
  int32_t _asz = 0;
  int32_t e = 0;
  struct nArg*  parg = 0;

  DEBUG_PRINT("env -> %08X\r\n", env);

  NAPI_STATUS(napi_get_cb_info(env, info, &argc, args, 0, (void**)(&_nliteio)));
  DEBUG_PRINT("\r\n");


  hdl = _nliteio->h;

  DEBUG_PRINT(" _nliteio : %08X, _nliteio->h : %08X \r\n", _nliteio, _nliteio->h);
  if ( env == 0 ) return 0;

  parg = (struct nArg*)calloc(1, sizeof(struct nArg));

  NAPI_STATUS(napi_get_value_int32(env, args[0], &parg->fd));
  DEBUG_PRINT("parg->fd -> %d\r\n", parg->fd);
  if ( parg->fd <= 0 )
  {
    free(parg);
    parg = 0;

    return 0;
  }

  #if __NHTTPD__
  e = __liteio_httpd_close(hdl, parg->fd, 0, 0, 0, hdl);
  #endif

  #if __NTCP__
  e = __liteio_tcp_close(hdl, parg->fd, 0, 0, 0, hdl);
  #endif

  #if __NSERIAL__
  e = __liteio_serial_close(hdl, parg->fd, 0, 0, 0, hdl);
  #endif

  #if __NSOCKET__
  e = __liteio_socket_close(hdl, parg->fd, 0, 0, 0, hdl);
  #endif

  #if __NWEBSOCKET__
  e = __liteio_websocket_close(hdl, parg->fd, 0, 0, 0, hdl);
  #endif


  free(parg);
  parg = 0;
  NAPI_STATUS(napi_create_int32(env, e, &r));

  return r;
}

#if 0
static void call_js(napi_env env, napi_value js_cb, void* context, void* arg)
{
  // This parameter is not used.
  (void) context;
  napi_value undefined;
  napi_value result;
  napi_value _nv[16] = {0};
  int32_t idx = 0;
  struct nArg* _arg = (struct nArg*)arg;

  if (env != 0)
  {
    NAPI_STATUS(napi_create_int32(env, _arg->fd, &_nv[idx]));
    idx++;

    NAPI_STATUS(napi_create_buffer_copy(env, _arg->sz, _arg->b, 0, &_nv[idx]));
    idx++;

    NAPI_STATUS(napi_create_int32(env, _arg->sz, &_nv[idx]));
    idx++;

    NAPI_STATUS(napi_create_uint32(env, _arg->ecode, &_nv[idx]));
    idx++;

    NAPI_STATUS(napi_get_undefined(env, &undefined));

    printf(" env  : %08X \r\n", env);
    printf(" napi_call_function -> %d, %d, %d(%08X)\r\n"
                "////////////////////////////////////////////////////////////////////////////////\r\n"
                "%s\r\n"
                "################################################################################\r\n",
                idx, _arg->sz, _arg->ecode, _arg->ecode, _arg->b);

    NAPI_STATUS(napi_call_function(env, undefined, js_cb, idx, _nv, &result));

    //__set_hex_semaphore(&p->SR, 0x00000004, 0x00000004);

  }
}
#endif


#if 1
static void call_js(napi_env env, napi_value js_cb, void* context, void* arg)
{
  // This parameter is not used.
  //(void) context;
  napi_value undefined;
  napi_value result;
  napi_value _nv[16] = {0};
  int32_t idx = 0;
  cnLiteIO* _nliteio = (cnLiteIO*)arg;

  if (env != 0)
  {
    DEBUG_PRINT("env -> %08X\r\n", env);

    DEBUG_PRINT("[%08d] -> %08X(%d) \r\n", _nliteio->arg.fd, _nliteio->arg.sz, _nliteio->arg.sz);
    DEBUG_PRINT(">>>>>>>>>>\r\n");
    NAPI_STATUS(napi_create_int32(env, _nliteio->arg.fd, &_nv[idx]));
    idx++;

    if ( _nliteio->arg.sz > 0 )
    {
      NAPI_STATUS(napi_create_buffer_copy(env, _nliteio->arg.sz, _nliteio->arg.b, 0, &_nv[idx]));
    }
    else
    {
      NAPI_STATUS(napi_create_int32(env, _nliteio->arg.sz, &_nv[idx]));
    }
    idx++;

    NAPI_STATUS(napi_create_int32(env, _nliteio->arg.sz, &_nv[idx]));
    idx++;

    NAPI_STATUS(napi_get_undefined(env, &undefined));

    #if 0
    DEBUG_PRINT(" napi_call_function -> %d, %d(%08X)\r\n"
                "////////////////////////////////////////////////////////////////////////////////\r\n"
                "%s\r\n"
                "################################################################################\r\n",
                idx, _nliteio->arg.sz, _nliteio->arg.sz, _nliteio->arg.b);
    #endif
    NAPI_STATUS(napi_call_function(env, undefined, js_cb, idx, _nv, &result));

    DEBUG_PRINT("<<<<<<<<<<\r\n");
    __set_hex_semaphore(&_nliteio->SR, 0x00000001, 0x00000001);
    DEBUG_PRINT("<<<<<<<<<< result -> %d(%08X)\r\n", result, result);
  }

}
#endif

#if 0
static int32_t __ncallback_reader(void* obj, void* arg)
{
  napi_status status;
  napi_value undefined;
  napi_value result;
  DEBUG_PRINT("\r\n");
  cnLiteIO* _nliteio = (cnLiteIO*)obj;
  struct nArg*  _arg = (struct nArg*)arg;
  DEBUG_PRINT("\r\n");


  #if 1
  uv_mutex_lock(&_nliteio->mutex);
  memcpy(&_nliteio->nargs[_nliteio->nidx], _arg, sizeof(struct nArg));
  status = napi_acquire_threadsafe_function(_nliteio->tsfx);
  status = napi_call_threadsafe_function(_nliteio->tsfx,(void*)&_nliteio->nargs[_nliteio->nidx],napi_tsfn_blocking);
  _nliteio->nidx++;
  _nliteio->nidx %= MAX_NARG;
  uv_mutex_unlock(&_nliteio->mutex);
  #endif

  return 0;
}
#else
static int32_t __ncallback_reader(void* obj, void* arg)
{
  napi_value global = 0;
  napi_value result = 0;
  napi_value argv[16] = {0};
  napi_value undefined;
  napi_value _nv[16] = {0};

  int32_t idx = 0;
  int32_t e = -1;
  cnLiteIO* _nliteio = (cnLiteIO*)obj;
  struct nArg*  _arg = (struct nArg*)arg;

  //NAPI_STATUS(napi_acquire_threadsafe_function(_nliteio->tsfx));

  #if 0
  DEBUG_PRINT("%08X %d -> %08X(%d) \r\n", *_nliteio->_env, _nliteio->arg.fd, _nliteio->arg.sz, _nliteio->arg.sz);
  DEBUG_PRINT(">>>>>>>>>>\r\n");
  NAPI_STATUS(napi_create_int32(*_nliteio->_env, _nliteio->arg.fd, &_nv[idx]));
  idx++;

  if ( _nliteio->arg.sz > 0 )
  {
    NAPI_STATUS(napi_create_buffer_copy(*_nliteio->_env, _nliteio->arg.sz, _nliteio->arg.b, 0, &_nv[idx]));
  }
  else
  {
    NAPI_STATUS(napi_create_int32(*_nliteio->_env, _nliteio->arg.sz, &_nv[idx]));
  }
  idx++;

  NAPI_STATUS(napi_create_int32(*_nliteio->_env, _nliteio->arg.sz, &_nv[idx]));
  idx++;

  //NAPI_STATUS(napi_get_undefined(*_nliteio->_env, &undefined));

  NAPI_STATUS(napi_call_function(*_nliteio->_env, global, _nliteio->_callback, idx, _nv, &result));


  //NAPI_STATUS(napi_get_global(*_nliteio->_env, &global));
  DEBUG_PRINT("\r\n");

  NAPI_STATUS(napi_call_function(*_nliteio->_env, global, _nliteio->_callback, 0, 0, &result));
  DEBUG_PRINT("\r\n");
  #endif


  #if 0
  status = napi_create_int32(_nliteio->_env, _arg->fd, &argv[idx]);
  assert(status == napi_ok);
  idx++;
  DEBUG_PRINT("\r\n");

  status = napi_create_buffer_copy(_nliteio->_env, _arg->sz, _arg->b, 0, &argv[idx]);
  assert(status == napi_ok);
  idx++;
  DEBUG_PRINT("\r\n");

  status = napi_create_int32(_nliteio->_env, _arg->sz, &argv[idx]);
  assert(status == napi_ok);
  idx++;
  DEBUG_PRINT("\r\n");

  status = napi_create_uint32(_nliteio->_env, _arg->ecode, &argv[idx]);
  assert(status == napi_ok);
  idx++;
  DEBUG_PRINT("\r\n");


  printf(" %08X(%d) , %d\r\n%s\r\n", _arg->ecode, _arg->ecode, _arg->sz, _arg->b);

  // status = napi_call_function(_nliteio->_env, global, _nliteio->_callback, idx, argv, &result);
  // assert(status == napi_ok);
  #endif

  #if 0
  //DEBUG_PRINT("uv_mutex_lock\r\n");
  uv_mutex_lock(&_nliteio->mutex);
  memcpy(&_nliteio->nargs[_nliteio->nidx], _arg, sizeof(struct nArg));


  //DEBUG_PRINT("napi_call_threadsafe_function\r\n");
  NAPI_STATUS(napi_call_threadsafe_function(_nliteio->tsfx,(void*)&_nliteio->nargs[_nliteio->nidx],napi_tsfn_blocking));

  _nliteio->nidx++;
  _nliteio->nidx %= MAX_NARG;

  uv_mutex_unlock(&_nliteio->mutex);
  //DEBUG_PRINT("uv_mutex_unlock\r\n");
  #endif

  #if 1
  DEBUG_PRINT("uv_mutex_lock\r\n");
  uv_mutex_lock(&_nliteio->mutex);
  memcpy(&_nliteio->arg, _arg, sizeof(struct nArg));

  DEBUG_PRINT(" (%d)%08X(%d)\r\n%s\r\n", _arg->fd, _arg->sz, _arg->sz,_arg->b);

  NAPI_STATUS(napi_call_threadsafe_function(_nliteio->tsfx,_nliteio,napi_tsfn_blocking));

  //NAPI_STATUS(napi_call_function(_nliteio->_env, undefined, _nliteio->_callback, 0, 0, &result));

  #if 0
  if (*_nliteio->_env != 0)
  {
    DEBUG_PRINT("%08X %d -> %08X(%d) \r\n", *_nliteio->_env, _nliteio->arg.fd, _nliteio->arg.sz, _nliteio->arg.sz);
    DEBUG_PRINT(">>>>>>>>>>\r\n");
    NAPI_STATUS(napi_create_int32(*_nliteio->_env, _nliteio->arg.fd, &_nv[idx]));
    idx++;

    if ( _nliteio->arg.sz > 0 )
    {
      NAPI_STATUS(napi_create_buffer_copy(*_nliteio->_env, _nliteio->arg.sz, _nliteio->arg.b, 0, &_nv[idx]));
    }
    else
    {
      NAPI_STATUS(napi_create_int32(*_nliteio->_env, _nliteio->arg.sz, &_nv[idx]));
    }
    idx++;

    NAPI_STATUS(napi_create_int32(*_nliteio->_env, _nliteio->arg.sz, &_nv[idx]));
    idx++;

    NAPI_STATUS(napi_get_undefined(*_nliteio->_env, &undefined));

    NAPI_STATUS(napi_call_function(*_nliteio->_env, undefined, _nliteio->_callback, idx, _nv, &result));

    DEBUG_PRINT("<<<<<<<<<<\r\n");
    __set_hex_semaphore(&_nliteio->SR, 0x00000001, 0x00000001);
  }
  #endif
  //NAPI_STATUS(napi_threadsafe_function_call_js(env, _nliteio->_callback,0,_nliteio));

  // _nliteio->nidx++;
  // _nliteio->nidx %= MAX_NARG;
  DEBUG_PRINT(" e---> %d %08X\r\n",e, _nliteio->SR );
  e = __get_hex_semaphore(&_nliteio->SR, 0x00000001, 0x00000001, 0x04000000);
  DEBUG_PRINT(" e---> %d %08X\r\n",e, _nliteio->SR );
  __set_hex_semaphore(&_nliteio->SR, 0x00000001, 0x00000000);

  uv_mutex_unlock(&_nliteio->mutex);
  DEBUG_PRINT("uv_mutex_unlock\r\n");
  #endif


  //Sleep(4000);
  //NAPI_STATUS(napi_release_threadsafe_function(_nliteio->tsfx, napi_tsfn_release));

  return 0;
}
#endif

static int32_t __ninit(cnLiteIO* _nliteio, int8_t* argv)
{
  int32_t e = 0;
  int32_t i = 0;
  int32_t count = 0;
  int32_t sz = 0;
  int8_t*  tmp = 0;
  int8_t** pp = 0;
  int8_t** _p = pp;
  int32_t (*cbf[2])(void* obj, void* arg) = { __ncallback_reader, 0};

  count = count_args(argv);
  _p = pp = (int8_t**)calloc(count, sizeof(int8_t*));

  DEBUG_PRINT(" count -> %d, %s \r\n", count, argv);
  tmp = (int8_t*)calloc(1024, sizeof(int8_t));
  for ( i=0 ; i<count ; i++ )
  {
    DEBUG_PRINT(" i -> %d\r\n", i);
    sz = get_args(argv, i, tmp);
    DEBUG_PRINT(" sz -> %d, %s \r\n", sz, tmp);
    if ( sz > 0 )
    {
      *pp = (int8_t*)calloc(sz+1, sizeof(int8_t));
      memcpy(*pp, tmp, sz);
      *pp ++;
    }
  }
  free(tmp);
  DEBUG_PRINT("\r\n");


  e = __initia(&_nliteio->h, cbf, _nliteio, &(_nliteio->arg), count, _p);
  DEBUG_PRINT(" _nliteio : %08X, _nliteio->h : %08X \r\n", _nliteio, _nliteio->h);

  pp = _p;
  for ( i=0 ; i<count ; i++ )
  {
    free(*pp);
    *pp++;
  }
  free(_p);
  DEBUG_PRINT("\r\n");

  return e;
}





#if 1
static napi_value liteio_open(napi_env env, napi_callback_info info)
{
  napi_value r = 0;
  uint32_t argc = 2;
  int32_t idx = 0;
  napi_value args[2]= {0};
  napi_valuetype vtype[16] = {0};
  napi_value work_name;

  cnLiteIO* _nliteio = 0;
  int8_t* _args = 0;
  int32_t _asz = 0;
  int32_t e = 0;

  DEBUG_PRINT("env -> %08X\r\n", env);

  NAPI_STATUS(napi_get_cb_info(env, info, &argc, args, 0, (void**)(&_nliteio)));
  _nliteio->nidx = 0;
  _nliteio->SR = 0;
  idx = 0;
  if ( args[idx] == 0 )
  {
    DEBUG_PRINT("args[%d] -> %s\r\n", idx, args[idx]==0?"NULL":"NOT NULL");
    return 0;
  }
  NAPI_STATUS(napi_typeof(env, args[idx], &vtype[idx]));
  if ( vtype[idx] != napi_string && vtype[idx] != napi_string_expected )
  {
    napi_throw_type_error(env, "TYPE_ERROR", "napi_string");
    return 0;
  }

  idx = 1;
  if ( args[idx] == 0 )
  {
    DEBUG_PRINT("args[%d] -> %s\r\n", idx, args[idx]==0?"NULL":"NOT NULL");
    return 0;
  }
  NAPI_STATUS(napi_typeof(env, args[idx], &vtype[idx]));
  if ( vtype[idx] != napi_function && vtype[idx] != napi_function_expected )
  {
    napi_throw_type_error(env, "TYPE_ERROR", "napi_function");
    return 0;
  }
  _nliteio->_callback = args[idx];

  DEBUG_PRINT("napi_env : %08X \r\n", env);
  _nliteio->_env = &env;
  _nliteio->_callback_info = &info;

  _args = (int8_t*)calloc(1024, sizeof(int8_t));
  sprintf(_args, ARGS);
  _asz = strlen(_args);

  NAPI_STATUS(napi_get_value_string_utf8(env, args[0], &_args[_asz], 512, &_asz));

  #if 1
  NAPI_STATUS(napi_create_string_utf8(env, "tsfx_0", NAPI_AUTO_LENGTH, &work_name));
  NAPI_STATUS(napi_create_threadsafe_function(env, args[1], 0, work_name,0,1,0,0,0,call_js, &_nliteio->tsfx)); // from callback
  //NAPI_STATUS(napi_create_async_work(env,0,work_name,exec_work,work_complete,_nliteio,&(_nliteio->work));
  //NAPI_STATUS(napi_queue_async_work(env,_nliteio->work));
  NAPI_STATUS(napi_acquire_threadsafe_function(_nliteio->tsfx));
  uv_mutex_init(&_nliteio->mutex);
  #endif

  e = __ninit(_nliteio, _args);
  free(_args);

  NAPI_STATUS(napi_create_int32(env, e, &r));
  return r;
}

#endif

// Free the per-addon-instance data.
static void _unloaded(napi_env env, void* data, void* hint) {
  cnLiteIO* _nliteio = (cnLiteIO*)data;
  free(_nliteio);
}



static napi_value liteio_debug(napi_env env, napi_callback_info info)
{
  uint32_t argc = 1;
  napi_value args[1];
  napi_valuetype valuetype;
  cnLiteIO* _nliteio = 0;
  int32_t dflg = 0;

  NAPI_STATUS(napi_get_cb_info(env, info, &argc, args, 0, (void**)(&_nliteio)));
  if ( env == 0 ) return 0;

  NAPI_STATUS(napi_get_value_int32(env, args[0], &dflg));
  __debug(dflg);

  return 0;
}

napi_value liteio_init(napi_env env, napi_value exports)
{
  napi_status status;
  napi_value _fx[16] = {0};
  cnLiteIO* _nliteio = (cnLiteIO*)malloc(sizeof(cnLiteIO));
  DEBUG_PRINT("env -> %08X\r\n", env);

  #if __LINUX__
  signal(SIGPIPE, SIG_IGN);
  #endif
  #if 1
  NAPI_STATUS(napi_create_function(env, "open",  NAPI_AUTO_LENGTH, liteio_open, _nliteio, &_fx[0]));
  NAPI_STATUS(napi_set_named_property(env, exports, "open", _fx[0]));

  NAPI_STATUS(napi_create_function(env, "close", NAPI_AUTO_LENGTH, liteio_close, _nliteio, &_fx[1]));
  NAPI_STATUS(napi_set_named_property(env, exports, "close", _fx[1]));

  NAPI_STATUS(napi_create_function(env, "write", NAPI_AUTO_LENGTH, liteio_write, _nliteio, &_fx[2]));
  NAPI_STATUS(napi_set_named_property(env, exports, "write", _fx[2]));

  NAPI_STATUS(napi_create_function(env, "read",  NAPI_AUTO_LENGTH, liteio_read, _nliteio, &_fx[3]));
  NAPI_STATUS(napi_set_named_property(env, exports, "read", _fx[3]));

  NAPI_STATUS(napi_create_function(env, "debug", NAPI_AUTO_LENGTH, liteio_debug, _nliteio, &_fx[4]));
  NAPI_STATUS(napi_set_named_property(env, exports, "debug", _fx[4]));
  #endif
  #if 0
  napi_property_descriptor _workers[] =
  {
    { "open", 0, liteio_open, 0, 0, 0, napi_default, _nliteio},
    { "close", 0, liteio_close, 0, 0, 0, napi_default, _nliteio},
    { "write", 0, liteio_write, 0, 0, 0, napi_default, _nliteio},
    { "read", 0, liteio_read, 0, 0, 0, napi_default, _nliteio},
    { "debug", 0, liteio_debug, 0, 0, 0, napi_default, _nliteio},
  };

  NAPI_STATUS(napi_define_properties(env, exports, sizeof(_workers)/sizeof(_workers[0]), _workers));
  #endif
  return exports;
}
NAPI_MODULE(NODE_GYP_MODULE_NAME, liteio_init)






#if 0
ubuntu on Raspberry Pi 4 B+ 설치 과정
1.ubuntu download
	A. ubuntu – Ubuntu Server 20.04 LTS 버전
		https://ubuntu.com/download/raspberry-pi
2.ubuntu sd card 설치 후
	A.UART 115200
	B.login :   ubuntu / ubuntu
	C.upgrade
		i.apt-get update -y
		ii.apt-get upgrade -y
3.node 개발 환경 설치
	A.apt-get install -y nodejs
	B.apt-get install -y npm
#endif

