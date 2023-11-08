#if __NSHM__
#include <__nshm.h>
#include <__shm.h>

void* __nshm_get(void* h, int32_t offset)
{
  return __shm_get(((cnshm*)h)->io.h,  offset);
}


int32_t __nshm_read(void* h, uint8_t* b, int32_t sz)
{
  return __shm_read(((cnshm*)h)->io.h,  b, sz, 0, 0);
}


int32_t __nshm_write(void* h, int8_t* b, int32_t sz)
{
  return __shm_write(((cnshm*)h)->io.h,  b, sz, 0, 0);
}



int32_t __nshm_open(cnshm* p)
{
  int8_t _json[1024] = {0};

  if ( p->io.h ) return 0xE0000001;

  sprintf(_json, 
          "{"
            "\"KEY\":\"%s\","
            "\"SIZE\":\"%s\","
          "}",
            p->io.argv[SHM_KEY],
            p->io.argv[SHM_SIZE]);
  return __shm_open(&p->io.h, _json);
}

int32_t __nshm_close(cnshm* p)
{
  return __shm_close(&p->io.h);
}


#endif
