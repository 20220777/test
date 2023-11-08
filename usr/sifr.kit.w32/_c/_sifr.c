#include <_sifr.h>

int32_t loadBinary(int8_t* fname, uint8_t** p)
{
  FILE* fp = 0;
  int32_t sz = 0;

  fp = fopen(fname, "rb");
  fseek(fp, 0, SEEK_SET);
  fseek(fp, 0, SEEK_END);
  sz = ftell(fp);

  *p = (uint8_t*)calloc(sz, sizeof(uint8_t));
  fseek(fp, 0, SEEK_SET);
  fread(*p, sizeof(uint8_t), sz, fp);

  if(fp) fclose(fp);

  return sz;
}





int32_t load_sifr_kit(HWND h, _sifr* p, uint8_t* path)
{
  void* hdl = 0;
  int32_t e = 0;
  wchar_t _path[2048] = {0};

  p->sz = loadBinary(path, &p->p);
  if ( p->sz <= 0 ) return -1;

  mbstowcs(_path, path, strlen(path));

  hdl = LoadLibrary(_path);
  if ( hdl == 0 )
  {
    return -1;
  }
  *(FARPROC*)&p->__sifr_init             = GetProcAddress(hdl,"__sifr_init");
  *(FARPROC*)&p->__sifr_release          = GetProcAddress(hdl,"__sifr_release");
  *(FARPROC*)&p->__sifr_version          = GetProcAddress(hdl,"__sifr_version");
  *(FARPROC*)&p->__sifr_author           = GetProcAddress(hdl,"__sifr_author");
  *(FARPROC*)&p->__sifr_module           = GetProcAddress(hdl,"__sifr_module");
  *(FARPROC*)&p->__sifr_set_callback     = GetProcAddress(hdl,"__sifr_set_callback");

  *(FARPROC*)&p->__sifr_base64           = GetProcAddress(hdl,"__sifr_base64");

  *(FARPROC*)&p->__sifr_noise_source     = GetProcAddress(hdl,"__sifr_noise_source");
  *(FARPROC*)&p->__sifr_entropy          = GetProcAddress(hdl,"__sifr_entropy");
  *(FARPROC*)&p->__sifr_drbg             = GetProcAddress(hdl,"__sifr_drbg");
  *(FARPROC*)&p->__sifr_random           = GetProcAddress(hdl,"__sifr_random");
  *(FARPROC*)&p->__sifr_key              = GetProcAddress(hdl,"__sifr_key");
  *(FARPROC*)&p->__sifr_self_check       = GetProcAddress(hdl,"__sifr_self_check");
  *(FARPROC*)&p->__sifr_kat_check        = GetProcAddress(hdl,"__sifr_kat_check");
  *(FARPROC*)&p->__sifr_integrity_check  = GetProcAddress(hdl,"__sifr_integrity_check");

  *(FARPROC*)&p->__sifr_mem_clear        = GetProcAddress(hdl,"__sifr_mem_clear");

  *(FARPROC*)&p->__sifr_last_status         = GetProcAddress(hdl,"__sifr_last_status");
  *(FARPROC*)&p->__sifr_last_status_string  = GetProcAddress(hdl,"__sifr_last_status_string");

  *(FARPROC*)&p->__sifr_aria_ecb_encode  = GetProcAddress(hdl,"__sifr_aria_ecb_encode");
  *(FARPROC*)&p->__sifr_aria_ecb_decode  = GetProcAddress(hdl,"__sifr_aria_ecb_decode");
  *(FARPROC*)&p->__sifr_aria_cbc_encode  = GetProcAddress(hdl,"__sifr_aria_cbc_encode");
  *(FARPROC*)&p->__sifr_aria_cbc_decode  = GetProcAddress(hdl,"__sifr_aria_cbc_decode");
  *(FARPROC*)&p->__sifr_aria_cfb_encode  = GetProcAddress(hdl,"__sifr_aria_cfb_encode");
  *(FARPROC*)&p->__sifr_aria_cfb_decode  = GetProcAddress(hdl,"__sifr_aria_cfb_decode");
  *(FARPROC*)&p->__sifr_aria_ofb_encode  = GetProcAddress(hdl,"__sifr_aria_ofb_encode");
  *(FARPROC*)&p->__sifr_aria_ofb_decode  = GetProcAddress(hdl,"__sifr_aria_ofb_decode");
  *(FARPROC*)&p->__sifr_aria_ctr_encode  = GetProcAddress(hdl,"__sifr_aria_ctr_encode");
  *(FARPROC*)&p->__sifr_aria_ctr_decode  = GetProcAddress(hdl,"__sifr_aria_ctr_decode");
  *(FARPROC*)&p->__sifr_aria_ccm_encode  = GetProcAddress(hdl,"__sifr_aria_ccm_encode");
  *(FARPROC*)&p->__sifr_aria_ccm_decode  = GetProcAddress(hdl,"__sifr_aria_ccm_decode");

  *(FARPROC*)&p->__sifr_lea_ecb_encode  = GetProcAddress(hdl,"__sifr_lea_ecb_encode");
  *(FARPROC*)&p->__sifr_lea_ecb_decode  = GetProcAddress(hdl,"__sifr_lea_ecb_decode");
  *(FARPROC*)&p->__sifr_lea_cbc_encode  = GetProcAddress(hdl,"__sifr_lea_cbc_encode");
  *(FARPROC*)&p->__sifr_lea_cbc_decode  = GetProcAddress(hdl,"__sifr_lea_cbc_decode");
  *(FARPROC*)&p->__sifr_lea_cfb_encode  = GetProcAddress(hdl,"__sifr_lea_cfb_encode");
  *(FARPROC*)&p->__sifr_lea_cfb_decode  = GetProcAddress(hdl,"__sifr_lea_cfb_decode");
  *(FARPROC*)&p->__sifr_lea_ofb_encode  = GetProcAddress(hdl,"__sifr_lea_ofb_encode");
  *(FARPROC*)&p->__sifr_lea_ofb_decode  = GetProcAddress(hdl,"__sifr_lea_ofb_decode");
  *(FARPROC*)&p->__sifr_lea_ctr_encode  = GetProcAddress(hdl,"__sifr_lea_ctr_encode");
  *(FARPROC*)&p->__sifr_lea_ctr_decode  = GetProcAddress(hdl,"__sifr_lea_ctr_decode");

  *(FARPROC*)&p->__sifr_seed_ecb_encode  = GetProcAddress(hdl,"__sifr_seed_ecb_encode");
  *(FARPROC*)&p->__sifr_seed_ecb_decode  = GetProcAddress(hdl,"__sifr_seed_ecb_decode");
  *(FARPROC*)&p->__sifr_seed_cbc_encode  = GetProcAddress(hdl,"__sifr_seed_cbc_encode");
  *(FARPROC*)&p->__sifr_seed_cbc_decode  = GetProcAddress(hdl,"__sifr_seed_cbc_decode");
  *(FARPROC*)&p->__sifr_seed_cfb_encode  = GetProcAddress(hdl,"__sifr_seed_cfb_encode");
  *(FARPROC*)&p->__sifr_seed_cfb_decode  = GetProcAddress(hdl,"__sifr_seed_cfb_decode");
  *(FARPROC*)&p->__sifr_seed_ofb_encode  = GetProcAddress(hdl,"__sifr_seed_ofb_encode");
  *(FARPROC*)&p->__sifr_seed_ofb_decode  = GetProcAddress(hdl,"__sifr_seed_ofb_decode");
  *(FARPROC*)&p->__sifr_seed_ctr_encode  = GetProcAddress(hdl,"__sifr_seed_ctr_encode");
  *(FARPROC*)&p->__sifr_seed_ctr_decode  = GetProcAddress(hdl,"__sifr_seed_ctr_decode");

  *(FARPROC*)&p->__sifr_hight_ecb_encode  = GetProcAddress(hdl,"__sifr_hight_ecb_encode");
  *(FARPROC*)&p->__sifr_hight_ecb_decode  = GetProcAddress(hdl,"__sifr_hight_ecb_decode");
  *(FARPROC*)&p->__sifr_hight_cbc_encode  = GetProcAddress(hdl,"__sifr_hight_cbc_encode");
  *(FARPROC*)&p->__sifr_hight_cbc_decode  = GetProcAddress(hdl,"__sifr_hight_cbc_decode");
  *(FARPROC*)&p->__sifr_hight_cfb_encode  = GetProcAddress(hdl,"__sifr_hight_cfb_encode");
  *(FARPROC*)&p->__sifr_hight_cfb_decode  = GetProcAddress(hdl,"__sifr_hight_cfb_decode");
  *(FARPROC*)&p->__sifr_hight_ofb_encode  = GetProcAddress(hdl,"__sifr_hight_ofb_encode");
  *(FARPROC*)&p->__sifr_hight_ofb_decode  = GetProcAddress(hdl,"__sifr_hight_ofb_decode");
  *(FARPROC*)&p->__sifr_hight_ctr_encode  = GetProcAddress(hdl,"__sifr_hight_ctr_encode");
  *(FARPROC*)&p->__sifr_hight_ctr_decode  = GetProcAddress(hdl,"__sifr_hight_ctr_decode");

  *(FARPROC*)&p->__sifr_sha2    = GetProcAddress(hdl,"__sifr_sha2");
  *(FARPROC*)&p->__sifr_hmac    = GetProcAddress(hdl,"__sifr_hmac");
  *(FARPROC*)&p->__sifr_lsh256_224  = GetProcAddress(hdl,"__sifr_lsh256_224");
  *(FARPROC*)&p->__sifr_lsh256_256  = GetProcAddress(hdl,"__sifr_lsh256_256");
  *(FARPROC*)&p->__sifr_lsh512_224  = GetProcAddress(hdl,"__sifr_lsh512_224");
  *(FARPROC*)&p->__sifr_lsh512_256  = GetProcAddress(hdl,"__sifr_lsh512_256");
  *(FARPROC*)&p->__sifr_lsh512_384  = GetProcAddress(hdl,"__sifr_lsh512_384");
  *(FARPROC*)&p->__sifr_lsh512_512  = GetProcAddress(hdl,"__sifr_lsh512_512");


  *(FARPROC*)&p->setMessage  = GetProcAddress(hdl,"__setMessage");
  *(FARPROC*)&p->putMessage  = GetProcAddress(hdl,"__putMessage");



  return p->sz;
}

