#include <stdio.h>

#include "kisa_key.h"


#include <drbg.h>

#include "KISA_HIGHT_CBC.h"
#include "KISA_HIGHT_CMAC.h"
#include "KISA_SEED_CCM.h"
#include "KISA_SEED_GCM.h"

#include "KISA_SHA256.h"
#include "KISA_HIGHT_ECB.h"

#include "pbkdf.h"

#include "./util.h"




#define BIT_256               32
#define SEED_256              BIT_256
#define UNDER_LINE   printf("\r\n________________________________________________________________________________\r\n")
#define END_LINE  {printf("press any key to continue.....\r\n");getchar();}


int InputCount[2] = {0, 0};


int ascii_2_hex(unsigned char* src, unsigned char* dst)
{
  int i=0;
  for (i=0; *src ; src++, i++ )
  {
    if ( (*(src)>='A') && (*(src)<='Z') )
    {
      ( i&1 ) ? ((*dst |= (*(src) - 0x37)&0x0F ), dst++ ): (*dst=0, ( *dst |= ( (*(src) - 0x37)&0x0F) << 4 ));
    }
    else if ( (*(src)>='a') && (*(src)<='z') )
    {
      ( i&1 ) ? ((*dst |= (*(src) - 0x57)&0x0F ), dst++ ): (*dst=0, ( *dst |= ( (*(src) - 0x57)&0x0F) << 4 ));
    }
    else if ( (*(src)>='0') && (*(src)<='9') )
    {
      ( i&1 ) ? ((*dst |= (*(src) - 0x30)&0x0F ), dst++ ): (*dst=0, ( *dst |= ( (*(src) - 0x30)&0x0F) << 4 ));
    }
    else
    {
      i--;
    }
  }

  if ( i&1 )
  {
    *dst>>=4;
    dst++;
    *dst = 0;
  }
  return (i/2) + (i%2);
}


void kisa_sha256_test()
{
  uint8_t md5[32];
  int8_t hbuf[4][51200];
  int32_t sz[4];

#if 0
  sz[0] = ascii_to_hex(KISA_KEY_SHA2_256_S[1][0], hbuf[0]);
  sz[1] = ascii_to_hex(KISA_KEY_SHA2_256_S[1][1], hbuf[1]);

  PRINT_BUFFER("MSG",  hbuf[0], sz[0]);
  PRINT_BUFFER("HASH", hbuf[1], sz[1]);

  SHA256_Encrpyt( hbuf[0], sz[0], md5 );

  PRINT_BUFFER("MD5", md5, 32);
#endif

}


void hmac_check()
{
	char hbuf[4][51200] = {0};
	int sz[4] = {0};

	char rbuf[4][51200] = {0};
	int rsz[4] = {0};

	const char* sample = "Kumoh National Institute of Technology, Department of Applied Mathematics";
	int ssz = strlen(sample);
	char result[1024] = {0, };
	int e = 0;
  int i = 0;

	sz[0] = ascii_to_hex(KISA_KEY_HMAC_SHA256[0][3], hbuf[0]);
	sz[1] = ascii_to_hex(KISA_KEY_HMAC_SHA256[0][4], hbuf[1]);
	sz[2] = ascii_to_hex(KISA_KEY_HMAC_SHA256[0][5], hbuf[2]);


	HMAC_SHA256(hbuf[0], sz[0], hbuf[1], sz[1], result);

  PRINT_BUFFER("key",      hbuf[0], sz[0]);
  PRINT_BUFFER("msg",      hbuf[1], sz[1]);
  PRINT_BUFFER("expected", hbuf[2], sz[2]);

  PRINT_BUFFER("HMAC_SHA256", result, 32);

}



void main()
{

	//main_kisa_seed_ecb();
 // UNDER_LINE;
 // END_LINE;
 // return 0;

  //kisa_aria_test();
  //UNDER_LINE;
  //END_LINE;
  //return 0;





  //kisa_ctr_drbg_testvector();
  //UNDER_LINE;
  //END_LINE;

  //return 0;



  kisa_ctr_drbg_test();
  UNDER_LINE;
  END_LINE;

  return 0;



  main_kisa_seed_ccm();
  UNDER_LINE;
  return;

  main_kisa_hight_cmac();
  UNDER_LINE;
  return;


  main_kisa_seed_gcm();
  UNDER_LINE;
  return;



    main_kisa_seed_cmac();
    UNDER_LINE;
    END_LINE;

    return 0;





  hmac_check();
  UNDER_LINE;
  END_LINE;
  return 0;





  main_kisa_hight_ctr();
  UNDER_LINE;
  END_LINE;
  return 0;


  main_kisa_hight_ecb();
  UNDER_LINE;
  END_LINE;
  return 0;






  kisa_sha256_test();
  UNDER_LINE;
  END_LINE;
  return 0;


  main_kisa_seed_cbc();
  UNDER_LINE;
  return 0;








  main_kisa_seed_ctr();
  UNDER_LINE;
  return 0;




  main_kisa_hight_cbc();
  UNDER_LINE;
  return 0;






  #if 0


  main_kisa_seed_ctr();
  UNDER_LINE;

  main_kisa_hight_cbc();
  UNDER_LINE;


  kisa_aria_test();
  UNDER_LINE;
  #endif


  main_kisa_seed_ccm();
  UNDER_LINE;




  #if 0
  UNDER_LINE;
  main_kisa_lsh();
  UNDER_LINE;

  #endif




  /****

  ****/

  //ARIA_test();



  //hight_cbc_encrypt();
  //main_kisa_seed_cbc2();
  //main_kisa_hight_cbc();





}


