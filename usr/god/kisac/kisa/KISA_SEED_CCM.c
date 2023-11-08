#include "KISA_SEED_CCM_c.h"
#include "KISA_SEED_CCM.h"
#include <util.h>


#define SHIFTR(x,n)                                     \
    (x)[3] = ((x)[3] >> (n)) ^ ((x)[2] << (32 - (n)));  \
    (x)[2] = ((x)[2] >> (n)) ^ ((x)[1] << (32 - (n)));  \
    (x)[1] = ((x)[1] >> (n)) ^ ((x)[0] << (32 - (n)));  \
    (x)[0] = ((x)[0] >> (n));

#define XOR128( R, A, B )       \
    (R)[0] = (A)[0] ^ (B)[0],   \
    (R)[1] = (A)[1] ^ (B)[1],   \
    (R)[2] = (A)[2] ^ (B)[2],   \
    (R)[3] = (A)[3] ^ (B)[3]

#define INCREASE( ctr )    ((ctr)[3] == 0xFFFFFFFF) ? ((ctr)[2]++, (ctr)[3] = 0) : ((ctr)[3]++);
#define ZERO128(a)    a[0] = 0x00000000, a[1] = 0x00000000, a[2] = 0x00000000, a[3] = 0x00000000

int SEED_CCM_Encryption(
    unsigned char *ct, unsigned int *ctLen,
    unsigned char *pt, unsigned int ptLen,
    unsigned int macLen,
    unsigned char *nonce, unsigned int nonceLen,
    unsigned char *aad, unsigned int aadLen,
    unsigned char *mKey)
{
    unsigned int CTR_in[4] = { 0, }, CTR_out[4] = { 0, };
    unsigned int CBC_in[4] = { 0, }, CBC_out[4] = { 0, };
    unsigned int MAC[4] = { 0, }, tmp[8] = { 0, };
    unsigned int rKey[32] = { 0x00, };
    unsigned int i, flag, tmpLen = 0;

    if (macLen > BLOCK_SIZE_SEED)
    {
        *ctLen = 0;

        return 1;
    }

    SEED_CCM_KeySched(mKey, rKey);
    PRINT_BUFFER("rKey", rKey, 32);
    
    Byte2Word(CTR_in, nonce, nonceLen);
    SHIFTR(CTR_in, 8);

    flag = 14 - nonceLen;

    CTR_in[0] ^= (flag << 24);
    
    SEED_CCM_Encrypt(MAC, CTR_in, rKey);

    for (i = 0; i < ptLen; i += BLOCK_SIZE_SEED)
    {
        INCREASE(CTR_in);

        ZERO128(tmp);

        if ((ptLen - i) < BLOCK_SIZE_SEED)
            Byte2Word(tmp, pt + i, ptLen - i);
        else
            Byte2Word(tmp, pt + i, BLOCK_SIZE_SEED);

        SEED_CCM_Encrypt(CTR_out, CTR_in, rKey);

        XOR128(tmp, CTR_out, tmp);

        if ((ptLen - i) < BLOCK_SIZE_SEED)
            Word2Byte(ct + i, tmp, ptLen - i);
        else
            Word2Byte(ct + i, tmp, BLOCK_SIZE_SEED);
    }

    Byte2Word(CBC_in, nonce, nonceLen);
    SHIFTR(CBC_in, 8);

    flag = aadLen ? (unsigned int)0x00000040 : (unsigned int)0x00000000;
    flag ^= ((macLen - 2) >> 1) << 3;
    flag ^= 14 - nonceLen;

    CBC_in[0] ^= (flag << 24);
    CBC_in[3] ^= ptLen;

    SEED_CCM_Encrypt(CBC_out, CBC_in, rKey);

    if (aadLen > 0)
    {
        if (aadLen > 14)
            tmpLen = 14;
        else
            tmpLen = aadLen;
        
        ZERO128(CBC_in);

        Byte2Word(CBC_in, aad, tmpLen);
        SHIFTR(CBC_in, 16);

        CBC_in[0] ^= (aadLen << 16);

        XOR128(CBC_in, CBC_in, CBC_out);

        SEED_CCM_Encrypt(CBC_out, CBC_in, rKey);

        for (i = tmpLen; i < aadLen; i += BLOCK_SIZE_SEED)
        {
            ZERO128(CBC_in);

            if ((aadLen - i) < BLOCK_SIZE_SEED)
                Byte2Word(CBC_in, aad + i, aadLen - i);
            else
                Byte2Word(CBC_in, aad + i, BLOCK_SIZE_SEED);
            
            XOR128(CBC_in, CBC_in, CBC_out);

            SEED_CCM_Encrypt(CBC_out, CBC_in, rKey);
        }
    }

    for (i = 0; i < ptLen; i += BLOCK_SIZE_SEED)
    {
        ZERO128(tmp);

        if ((ptLen - i) < BLOCK_SIZE_SEED)
            Byte2Word(tmp, pt + i, ptLen - i);
        else
            Byte2Word(tmp, pt + i, BLOCK_SIZE_SEED);
        
        XOR128(CBC_in, tmp, CBC_out);

        SEED_CCM_Encrypt(CBC_out, CBC_in, rKey);
    }

    XOR128(MAC, MAC, CBC_out);

    {
      int i=0;

      for ( i=0 ; i<16 ; i++ )
      {
        if ( i && (i%8)==0 ) printf("  ");
        if ( i && (i%16)==0 ) printf("\r\n");
        printf(" %02X", *((unsigned char*)MAC+i));
      }
      printf("\r\n");
    }
    Word2Byte(ct + ptLen, MAC, macLen);

    *ctLen = ptLen + macLen;


    {
      int i=0;

      for ( i=0 ; i<*ctLen ; i++ )
      {
        if ( i && (i%8)==0 ) printf("  ");
        if ( i && (i%16)==0 ) printf("\r\n");
        printf(" %02X", *(ct+i));
      }
      printf("\r\n");
    }



    return 0;
}

int SEED_CCM_Decryption(
    unsigned char *pt, unsigned int *ptLen,
    unsigned char *ct, unsigned int ctLen,
    unsigned int macLen,
    unsigned char *nonce, unsigned int nonceLen,
    unsigned char *aad, unsigned int aadLen,
    unsigned char *mKey)
{
    unsigned int CTR_in[4] = { 0, }, CTR_out[4] = { 0, };
    unsigned int CBC_in[4] = { 0, }, CBC_out[4] = { 0, };
    unsigned int MAC[4] = { 0, }, tmp[8] = { 0, };
    unsigned char tMAC[16] = { 0x00, };
    unsigned int rKey[32] = { 0x00, };
    unsigned int i, j, flag, tmpLen = 0;

    if (macLen > BLOCK_SIZE_SEED)
    {
        *ptLen = 0;

        return 1;
    }

    SEED_CCM_KeySched(mKey, rKey);

    Byte2Word(CTR_in, nonce, nonceLen);
    SHIFTR(CTR_in, 8);

    flag = 14 - nonceLen;

    CTR_in[0] ^= (flag << 24);
    
    SEED_CCM_Encrypt(MAC, CTR_in, rKey);

    for (i = 0; i < ctLen - macLen; i += BLOCK_SIZE_SEED)
    {
        INCREASE(CTR_in);

        ZERO128(tmp);

        if ((ctLen - macLen - i) < BLOCK_SIZE_SEED)
            Byte2Word(tmp, ct + i, ctLen - macLen - i);
        else
            Byte2Word(tmp, ct + i, BLOCK_SIZE_SEED);

        SEED_CCM_Encrypt(CTR_out, CTR_in, rKey);

        XOR128(tmp, CTR_out, tmp);

        if ((ctLen - macLen - i) < BLOCK_SIZE_SEED)
            Word2Byte(pt + i, tmp, ctLen - macLen - i);
        else
            Word2Byte(pt + i, tmp, BLOCK_SIZE_SEED);
    }

    Byte2Word(CBC_in, nonce, nonceLen);
    SHIFTR(CBC_in, 8);

    flag = aadLen ? (unsigned int)0x00000040 : (unsigned int)0x00000000;
    flag ^= ((macLen - 2) >> 1) << 3;
    flag ^= 14 - nonceLen;

    CBC_in[0] ^= (flag << 24);
    CBC_in[3] ^= ctLen - macLen;

    SEED_CCM_Encrypt(CBC_out, CBC_in, rKey);

    if (aadLen > 0)
    {
        if (aadLen > 14)
            tmpLen = 14;
        else
            tmpLen = aadLen;
        
        ZERO128(CBC_in);

        Byte2Word(CBC_in, aad, tmpLen);
        SHIFTR(CBC_in, 16);

        CBC_in[0] ^= (aadLen << 16);

        XOR128(CBC_in, CBC_in, CBC_out);

        SEED_CCM_Encrypt(CBC_out, CBC_in, rKey);

        for (i = tmpLen; i < aadLen; i += BLOCK_SIZE_SEED)
        {
            ZERO128(CBC_in);

            if ((aadLen - i) < BLOCK_SIZE_SEED)
                Byte2Word(CBC_in, aad + i, aadLen - i);
            else
                Byte2Word(CBC_in, aad + i, BLOCK_SIZE_SEED);
            
            XOR128(CBC_in, CBC_in, CBC_out);

            SEED_CCM_Encrypt(CBC_out, CBC_in, rKey);
        }
    }

    for (i = 0; i < ctLen - macLen; i += BLOCK_SIZE_SEED)
    {
        ZERO128(tmp);

        if ((ctLen - macLen - i) < BLOCK_SIZE_SEED)
            Byte2Word(tmp, pt + i, ctLen - macLen - i);
        else
            Byte2Word(tmp, pt + i, BLOCK_SIZE_SEED);
        
        XOR128(CBC_in, tmp, CBC_out);

        SEED_CCM_Encrypt(CBC_out, CBC_in, rKey);
    }

    XOR128(MAC, MAC, CBC_out);

    Word2Byte(tMAC, MAC, macLen);

    for (i = 0; i < macLen; i++)
    {
        if (tMAC[i] != ct[ctLen - macLen + i])
        {
            for (j = 0; j < ctLen - macLen; j++)
                pt[j] = 0;
                
            return 1;
        }
    }

    *ptLen = ctLen - macLen;

    return 0;
}









int main_kisa_seed_ccm()
{
  unsigned char key[160] = { 0x00, };
  unsigned char in[160] = { 0x00, };
  unsigned char out1[160] = { 0x00, };
  unsigned char out2[160] = { 0x00, };
  unsigned char nonce[160] = { 0x00, };
  unsigned char aad[160] = { 0x00, };

  int keyLen = 0, inLen = 0, out1Len = 0, out2Len = 0, nonceLen = 0, aadLen = 0, macLen = 16;

  print_title("Test SEED CCM - 1");

  keyLen = asc2hex(key, "FAB5E5DE4350E5A4E0F1DF63E46A2AA0");
  nonceLen = asc2hex(nonce, "0C911408A595DF62A99209C2");
  aadLen = asc2hex(aad, "2C62D1FFF6B7F6687266C2B3C706473644BAE95A014B1C4CC37A6FF52194CA2D");
  inLen = asc2hex(in, "E546F32BB5B35740F3C408C6E1BF0253091CB232DC94B913997AED01704EA095E89026697E");

  macLen = 16;

  print_result("SEED CCM_Encryption", SEED_CCM_Encryption(out1, (unsigned int *)&out1Len, in, inLen, macLen, nonce, nonceLen, aad, aadLen, key));

  print_hex("key", key, keyLen);
  print_hex("in", in, inLen);
  print_hex("nonce", nonce, nonceLen);
  print_hex("aad", aad, aadLen);
  print_hex("out1", out1, out1Len);
  printf("\n");

  print_result("SEED CCM_Decryption", SEED_CCM_Decryption(out2, (unsigned int *)&out2Len, out1, out1Len, macLen, nonce, nonceLen, aad, aadLen, key));

  print_hex("in", out1, out1Len);
  print_hex("out2", out2, out2Len);

  print_title("Test SEED CCM - 2");

  keyLen = asc2hex(key, "002B30E20CCC65E95DAE1FDF2411C0D5");
  nonceLen = asc2hex(nonce, "188CC310D2A428");
  aadLen = asc2hex(aad, "5CE917AF1AF4732CC220FC022979650E");
  inLen = asc2hex(in, "559869FF1ADDCC7261CDC9CB40D67626");

  macLen = 4;

  print_result("SEED CCM_Encryption", SEED_CCM_Encryption(out1, (unsigned int *)&out1Len, in, inLen, macLen, nonce, nonceLen, aad, aadLen, key));

  print_hex("key", key, keyLen);
  print_hex("in", in, inLen);
  print_hex("nonce", nonce, nonceLen);
  print_hex("aad", aad, aadLen);
  print_hex("out1", out1, out1Len);
  printf("\n");

  print_result("SEED CCM_Decryption", SEED_CCM_Decryption(out2, (unsigned int *)&out2Len, out1, out1Len, macLen, nonce, nonceLen, aad, aadLen, key));

  print_hex("in", out1, out1Len);
  print_hex("out2", out2, out2Len);

  return 0;
}