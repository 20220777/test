#include <stdio.h>
#include "KISA_HIGHT_CMAC.h"

#define BLOCK_SIZE_HIGHT      8


// include header


// define
#define BLOCK_SIZE_HIGHT        8
#define WHITENING_KEY_SIZE      8

#define HIGHT_CMAC_ENC(k, i0,i1,i2,i3,i4,i5,i6,i7) {                   \
    XX[i0] = (XX[i0] ^ (F0[XX[i1]] + rKey[4 * k + 3])) & 0xFF;    \
    XX[i2] = (XX[i2] + (F1[XX[i3]] ^ rKey[4 * k + 2])) & 0xFF;    \
    XX[i4] = (XX[i4] ^ (F0[XX[i5]] + rKey[4 * k + 1])) & 0xFF;    \
    XX[i6] = (XX[i6] + (F1[XX[i7]] ^ rKey[4 * k    ])) & 0xFF;    \
}

#define HIGHT_CMAC_DEC(k, i0,i1,i2,i3,i4,i5,i6,i7) {                   \
    XX[i1] = (XX[i1] - (F1[XX[i2]] ^ rKey[4 * k + 2])) & 0xFF;    \
    XX[i3] = (XX[i3] ^ (F0[XX[i4]] + rKey[4 * k + 1])) & 0xFF;    \
    XX[i5] = (XX[i5] - (F1[XX[i6]] ^ rKey[4 * k    ])) & 0xFF;    \
    XX[i7] = (XX[i7] ^ (F0[XX[i0]] + rKey[4 * k + 3])) & 0xFF;    \
}



static const unsigned char Delta[128] = 
{
    0x5A,0x6D,0x36,0x1B,0x0D,0x06,0x03,0x41,
    0x60,0x30,0x18,0x4C,0x66,0x33,0x59,0x2C,
    0x56,0x2B,0x15,0x4A,0x65,0x72,0x39,0x1C,
    0x4E,0x67,0x73,0x79,0x3C,0x5E,0x6F,0x37,
    0x5B,0x2D,0x16,0x0B,0x05,0x42,0x21,0x50,
    0x28,0x54,0x2A,0x55,0x6A,0x75,0x7A,0x7D,
    0x3E,0x5F,0x2F,0x17,0x4B,0x25,0x52,0x29,
    0x14,0x0A,0x45,0x62,0x31,0x58,0x6C,0x76,
    0x3B,0x1D,0x0E,0x47,0x63,0x71,0x78,0x7C,
    0x7E,0x7F,0x3F,0x1F,0x0F,0x07,0x43,0x61,
    0x70,0x38,0x5C,0x6E,0x77,0x7B,0x3D,0x1E,
    0x4F,0x27,0x53,0x69,0x34,0x1A,0x4D,0x26,
    0x13,0x49,0x24,0x12,0x09,0x04,0x02,0x01,
    0x40,0x20,0x10,0x08,0x44,0x22,0x11,0x48,
    0x64,0x32,0x19,0x0C,0x46,0x23,0x51,0x68,
    0x74,0x3A,0x5D,0x2E,0x57,0x6B,0x35,0x5A
};

static const unsigned char F0[256] =
{
    0x00,0x86,0x0D,0x8B,0x1A,0x9C,0x17,0x91,
    0x34,0xB2,0x39,0xBF,0x2E,0xA8,0x23,0xA5,
    0x68,0xEE,0x65,0xE3,0x72,0xF4,0x7F,0xF9,
    0x5C,0xDA,0x51,0xD7,0x46,0xC0,0x4B,0xCD,
    0xD0,0x56,0xDD,0x5B,0xCA,0x4C,0xC7,0x41,
    0xE4,0x62,0xE9,0x6F,0xFE,0x78,0xF3,0x75,
    0xB8,0x3E,0xB5,0x33,0xA2,0x24,0xAF,0x29,
    0x8C,0x0A,0x81,0x07,0x96,0x10,0x9B,0x1D,
    0xA1,0x27,0xAC,0x2A,0xBB,0x3D,0xB6,0x30,
    0x95,0x13,0x98,0x1E,0x8F,0x09,0x82,0x04,
    0xC9,0x4F,0xC4,0x42,0xD3,0x55,0xDE,0x58,
    0xFD,0x7B,0xF0,0x76,0xE7,0x61,0xEA,0x6C,
    0x71,0xF7,0x7C,0xFA,0x6B,0xED,0x66,0xE0,
    0x45,0xC3,0x48,0xCE,0x5F,0xD9,0x52,0xD4,
    0x19,0x9F,0x14,0x92,0x03,0x85,0x0E,0x88,
    0x2D,0xAB,0x20,0xA6,0x37,0xB1,0x3A,0xBC,
    0x43,0xC5,0x4E,0xC8,0x59,0xDF,0x54,0xD2,
    0x77,0xF1,0x7A,0xFC,0x6D,0xEB,0x60,0xE6,
    0x2B,0xAD,0x26,0xA0,0x31,0xB7,0x3C,0xBA,
    0x1F,0x99,0x12,0x94,0x05,0x83,0x08,0x8E,
    0x93,0x15,0x9E,0x18,0x89,0x0F,0x84,0x02,
    0xA7,0x21,0xAA,0x2C,0xBD,0x3B,0xB0,0x36,
    0xFB,0x7D,0xF6,0x70,0xE1,0x67,0xEC,0x6A,
    0xCF,0x49,0xC2,0x44,0xD5,0x53,0xD8,0x5E,
    0xE2,0x64,0xEF,0x69,0xF8,0x7E,0xF5,0x73,
    0xD6,0x50,0xDB,0x5D,0xCC,0x4A,0xC1,0x47,
    0x8A,0x0C,0x87,0x01,0x90,0x16,0x9D,0x1B,
    0xBE,0x38,0xB3,0x35,0xA4,0x22,0xA9,0x2F,
    0x32,0xB4,0x3F,0xB9,0x28,0xAE,0x25,0xA3,
    0x06,0x80,0x0B,0x8D,0x1C,0x9A,0x11,0x97,
    0x5A,0xDC,0x57,0xD1,0x40,0xC6,0x4D,0xCB,
    0x6E,0xE8,0x63,0xE5,0x74,0xF2,0x79,0xFF
};

static const unsigned char F1[256] =
{
    0x00,0x58,0xB0,0xE8,0x61,0x39,0xD1,0x89,
    0xC2,0x9A,0x72,0x2A,0xA3,0xFB,0x13,0x4B,
    0x85,0xDD,0x35,0x6D,0xE4,0xBC,0x54,0x0C,
    0x47,0x1F,0xF7,0xAF,0x26,0x7E,0x96,0xCE,
    0x0B,0x53,0xBB,0xE3,0x6A,0x32,0xDA,0x82,
    0xC9,0x91,0x79,0x21,0xA8,0xF0,0x18,0x40,
    0x8E,0xD6,0x3E,0x66,0xEF,0xB7,0x5F,0x07,
    0x4C,0x14,0xFC,0xA4,0x2D,0x75,0x9D,0xC5,
    0x16,0x4E,0xA6,0xFE,0x77,0x2F,0xC7,0x9F,
    0xD4,0x8C,0x64,0x3C,0xB5,0xED,0x05,0x5D,
    0x93,0xCB,0x23,0x7B,0xF2,0xAA,0x42,0x1A,
    0x51,0x09,0xE1,0xB9,0x30,0x68,0x80,0xD8,
    0x1D,0x45,0xAD,0xF5,0x7C,0x24,0xCC,0x94,
    0xDF,0x87,0x6F,0x37,0xBE,0xE6,0x0E,0x56,
    0x98,0xC0,0x28,0x70,0xF9,0xA1,0x49,0x11,
    0x5A,0x02,0xEA,0xB2,0x3B,0x63,0x8B,0xD3,
    0x2C,0x74,0x9C,0xC4,0x4D,0x15,0xFD,0xA5,
    0xEE,0xB6,0x5E,0x06,0x8F,0xD7,0x3F,0x67,
    0xA9,0xF1,0x19,0x41,0xC8,0x90,0x78,0x20,
    0x6B,0x33,0xDB,0x83,0x0A,0x52,0xBA,0xE2,
    0x27,0x7F,0x97,0xCF,0x46,0x1E,0xF6,0xAE,
    0xE5,0xBD,0x55,0x0D,0x84,0xDC,0x34,0x6C,
    0xA2,0xFA,0x12,0x4A,0xC3,0x9B,0x73,0x2B,
    0x60,0x38,0xD0,0x88,0x01,0x59,0xB1,0xE9,
    0x3A,0x62,0x8A,0xD2,0x5B,0x03,0xEB,0xB3,
    0xF8,0xA0,0x48,0x10,0x99,0xC1,0x29,0x71,
    0xBF,0xE7,0x0F,0x57,0xDE,0x86,0x6E,0x36,
    0x7D,0x25,0xCD,0x95,0x1C,0x44,0xAC,0xF4,
    0x31,0x69,0x81,0xD9,0x50,0x08,0xE0,0xB8,
    0xF3,0xAB,0x43,0x1B,0x92,0xCA,0x22,0x7A,
    0xB4,0xEC,0x04,0x5C,0xD5,0x8D,0x65,0x3D,
    0x76,0x2E,0xC6,0x9E,0x17,0x4F,0xA7,0xFF
};

// Key Generation
void HIGHT_CMAC_KeySched(unsigned char *mKey, unsigned char *rKey)
{
    int i = 0, j = 0;

    // Whitening Key
    for (i = 0; i < 4; i++)
    {
        rKey[i    ] = mKey[i + 12];
        rKey[i + 4] = mKey[i     ];
    }

    // SubKey
    for (i = 0; i < BLOCK_SIZE_HIGHT; i++)
    {
        for (j = 0; j < BLOCK_SIZE_HIGHT; j++)
            rKey[WHITENING_KEY_SIZE + 16 * i + j    ] = (unsigned char)(mKey[ (j - i) & 7     ] + Delta[16 * i + j    ]);

        for (j = 0; j < BLOCK_SIZE_HIGHT; j++)
            rKey[WHITENING_KEY_SIZE + 16 * i + j + 8] = (unsigned char)(mKey[((j - i) & 7) + 8] + Delta[16 * i + j + 8]);
    }
}

// Encryption
void HIGHT_CMAC_Encrypt(unsigned char *pOut, unsigned char *pIn, unsigned char *rKey)
{
    unsigned int XX[8];

    XX[1] = pIn[1];
    XX[3] = pIn[3];
    XX[5] = pIn[5];
    XX[7] = pIn[7];

    XX[0] = (pIn[0] + rKey[0]) & 0xFF;
    XX[2] = (pIn[2] ^ rKey[1]);
    XX[4] = (pIn[4] + rKey[2]) & 0xFF;
    XX[6] = (pIn[6] ^ rKey[3]);

    HIGHT_CMAC_ENC( 2, 7,6,5,4,3,2,1,0);
    HIGHT_CMAC_ENC( 3, 6,5,4,3,2,1,0,7);
    HIGHT_CMAC_ENC( 4, 5,4,3,2,1,0,7,6);
    HIGHT_CMAC_ENC( 5, 4,3,2,1,0,7,6,5);
    HIGHT_CMAC_ENC( 6, 3,2,1,0,7,6,5,4);
    HIGHT_CMAC_ENC( 7, 2,1,0,7,6,5,4,3);
    HIGHT_CMAC_ENC( 8, 1,0,7,6,5,4,3,2);
    HIGHT_CMAC_ENC( 9, 0,7,6,5,4,3,2,1);
    HIGHT_CMAC_ENC(10, 7,6,5,4,3,2,1,0);
    HIGHT_CMAC_ENC(11, 6,5,4,3,2,1,0,7);
    HIGHT_CMAC_ENC(12, 5,4,3,2,1,0,7,6);
    HIGHT_CMAC_ENC(13, 4,3,2,1,0,7,6,5);
    HIGHT_CMAC_ENC(14, 3,2,1,0,7,6,5,4);
    HIGHT_CMAC_ENC(15, 2,1,0,7,6,5,4,3);
    HIGHT_CMAC_ENC(16, 1,0,7,6,5,4,3,2);
    HIGHT_CMAC_ENC(17, 0,7,6,5,4,3,2,1);
    HIGHT_CMAC_ENC(18, 7,6,5,4,3,2,1,0);
    HIGHT_CMAC_ENC(19, 6,5,4,3,2,1,0,7);
    HIGHT_CMAC_ENC(20, 5,4,3,2,1,0,7,6);
    HIGHT_CMAC_ENC(21, 4,3,2,1,0,7,6,5);
    HIGHT_CMAC_ENC(22, 3,2,1,0,7,6,5,4);
    HIGHT_CMAC_ENC(23, 2,1,0,7,6,5,4,3);
    HIGHT_CMAC_ENC(24, 1,0,7,6,5,4,3,2);
    HIGHT_CMAC_ENC(25, 0,7,6,5,4,3,2,1);
    HIGHT_CMAC_ENC(26, 7,6,5,4,3,2,1,0);
    HIGHT_CMAC_ENC(27, 6,5,4,3,2,1,0,7);
    HIGHT_CMAC_ENC(28, 5,4,3,2,1,0,7,6);
    HIGHT_CMAC_ENC(29, 4,3,2,1,0,7,6,5);
    HIGHT_CMAC_ENC(30, 3,2,1,0,7,6,5,4);
    HIGHT_CMAC_ENC(31, 2,1,0,7,6,5,4,3);
    HIGHT_CMAC_ENC(32, 1,0,7,6,5,4,3,2);
    HIGHT_CMAC_ENC(33, 0,7,6,5,4,3,2,1);

    pOut[1] = (unsigned char)XX[2];
    pOut[3] = (unsigned char)XX[4];
    pOut[5] = (unsigned char)XX[6];
    pOut[7] = (unsigned char)XX[0];

    pOut[0] = (unsigned char)(XX[1] + rKey[4]);
    pOut[2] = (unsigned char)(XX[3] ^ rKey[5]);
    pOut[4] = (unsigned char)(XX[5] + rKey[6]);
    pOut[6] = (unsigned char)(XX[7] ^ rKey[7]);
}

// Decryption
void HIGHT_CMAC_Decrypt(unsigned char *pOut, unsigned char *pIn, unsigned char *rKey)
{
    unsigned int XX[8];

    XX[2] = (unsigned char)pIn[1];
    XX[4] = (unsigned char)pIn[3];
    XX[6] = (unsigned char)pIn[5];
    XX[0] = (unsigned char)pIn[7];

    XX[1] = (unsigned char)(pIn[0] - rKey[4]);
    XX[3] = (unsigned char)(pIn[2] ^ rKey[5]);
    XX[5] = (unsigned char)(pIn[4] - rKey[6]);
    XX[7] = (unsigned char)(pIn[6] ^ rKey[7]);

    HIGHT_CMAC_DEC(33, 7,6,5,4,3,2,1,0);
    HIGHT_CMAC_DEC(32, 0,7,6,5,4,3,2,1);
    HIGHT_CMAC_DEC(31, 1,0,7,6,5,4,3,2);
    HIGHT_CMAC_DEC(30, 2,1,0,7,6,5,4,3);
    HIGHT_CMAC_DEC(29, 3,2,1,0,7,6,5,4);
    HIGHT_CMAC_DEC(28, 4,3,2,1,0,7,6,5);
    HIGHT_CMAC_DEC(27, 5,4,3,2,1,0,7,6);
    HIGHT_CMAC_DEC(26, 6,5,4,3,2,1,0,7);
    HIGHT_CMAC_DEC(25, 7,6,5,4,3,2,1,0);
    HIGHT_CMAC_DEC(24, 0,7,6,5,4,3,2,1);
    HIGHT_CMAC_DEC(23, 1,0,7,6,5,4,3,2);
    HIGHT_CMAC_DEC(22, 2,1,0,7,6,5,4,3);
    HIGHT_CMAC_DEC(21, 3,2,1,0,7,6,5,4);
    HIGHT_CMAC_DEC(20, 4,3,2,1,0,7,6,5);
    HIGHT_CMAC_DEC(19, 5,4,3,2,1,0,7,6);
    HIGHT_CMAC_DEC(18, 6,5,4,3,2,1,0,7);
    HIGHT_CMAC_DEC(17, 7,6,5,4,3,2,1,0);
    HIGHT_CMAC_DEC(16, 0,7,6,5,4,3,2,1);
    HIGHT_CMAC_DEC(15, 1,0,7,6,5,4,3,2);
    HIGHT_CMAC_DEC(14, 2,1,0,7,6,5,4,3);
    HIGHT_CMAC_DEC(13, 3,2,1,0,7,6,5,4);
    HIGHT_CMAC_DEC(12, 4,3,2,1,0,7,6,5);
    HIGHT_CMAC_DEC(11, 5,4,3,2,1,0,7,6);
    HIGHT_CMAC_DEC(10, 6,5,4,3,2,1,0,7);
    HIGHT_CMAC_DEC( 9, 7,6,5,4,3,2,1,0);
    HIGHT_CMAC_DEC( 8, 0,7,6,5,4,3,2,1);
    HIGHT_CMAC_DEC( 7, 1,0,7,6,5,4,3,2);
    HIGHT_CMAC_DEC( 6, 2,1,0,7,6,5,4,3);
    HIGHT_CMAC_DEC( 5, 3,2,1,0,7,6,5,4);
    HIGHT_CMAC_DEC( 4, 4,3,2,1,0,7,6,5);
    HIGHT_CMAC_DEC( 3, 5,4,3,2,1,0,7,6);
    HIGHT_CMAC_DEC( 2, 6,5,4,3,2,1,0,7);

    pOut[1] = (unsigned char)(XX[1]);
    pOut[3] = (unsigned char)(XX[3]);
    pOut[5] = (unsigned char)(XX[5]);
    pOut[7] = (unsigned char)(XX[7]);

    pOut[0] = (unsigned char)(XX[0] - rKey[0]);
    pOut[2] = (unsigned char)(XX[2] ^ rKey[1]);
    pOut[4] = (unsigned char)(XX[4] - rKey[2]);
    pOut[6] = (unsigned char)(XX[6] ^ rKey[3]);
}


// CMAC Subkey Generate
void HIGHT_CMAC_CMAC_SubkeySched(unsigned char *sKey)
{
    int i = 0, carry = sKey[0] >> 7;

    for (i = 0; i < 7; i++)
        sKey[i] = (sKey[i] << 1) | (sKey[i + 1] >> 7);

    sKey[i] = sKey[i] << 1;

    if (carry)
        sKey[i] ^= 0x1b;
}

// HIGHT Generate CMAC
int HIGHT_CMAC_Generate_CMAC(unsigned char *pMAC, int macLen, unsigned char *pIn, int inLen, unsigned char *mKey)
{
    unsigned char temp[BLOCK_SIZE_HIGHT] = { 0x00, };
    unsigned char subKey[BLOCK_SIZE_HIGHT] = { 0x00, };
    unsigned char rKey[136] = { 0x00, };
    int blockLen = 0, i = 0, j = 0;

    if (macLen > BLOCK_SIZE_HIGHT)
        return 1;

    HIGHT_CMAC_KeySched(mKey, rKey);
    HIGHT_CMAC_Encrypt(subKey, subKey, rKey);

    // make K1
    HIGHT_CMAC_CMAC_SubkeySched(subKey);

    if (inLen == 0)
    {
        // make K2
        HIGHT_CMAC_CMAC_SubkeySched(subKey);

        subKey[0] ^= 0x80;

        HIGHT_CMAC_Encrypt(temp, subKey, rKey);
    }
    else if (inLen & 7)
    {
        // make K2
        HIGHT_CMAC_CMAC_SubkeySched(subKey);

        blockLen = (inLen + BLOCK_SIZE_HIGHT) / BLOCK_SIZE_HIGHT;

        for (i = 0; i < blockLen - 1; i++)
        {
            for (j = 0; j < BLOCK_SIZE_HIGHT; j++)
                temp[j] ^= pIn[BLOCK_SIZE_HIGHT * i + j];

            HIGHT_CMAC_Encrypt(temp, temp, rKey);
        }

        for (j = 0; (BLOCK_SIZE_HIGHT * i + j) < inLen; j++)
            temp[j] ^= pIn[BLOCK_SIZE_HIGHT * i + j] ^ subKey[j];
        temp[j] ^= 0x80 ^ subKey[j];
        for (j += 1; j < BLOCK_SIZE_HIGHT; j++)
            temp[j] ^= subKey[j];

        HIGHT_CMAC_Encrypt(temp, temp, rKey);
    }
    else
    {
        blockLen = inLen / BLOCK_SIZE_HIGHT;

        for (i = 0; i < blockLen - 1; i++)
        {
            for (j = 0; j < BLOCK_SIZE_HIGHT; j++)
                temp[j] ^= pIn[BLOCK_SIZE_HIGHT * i + j];

            HIGHT_CMAC_Encrypt(temp, temp, rKey);
        }

        for (j = 0; j < BLOCK_SIZE_HIGHT; j++)
            temp[j] ^= pIn[BLOCK_SIZE_HIGHT * i + j] ^ subKey[j];

        HIGHT_CMAC_Encrypt(temp, temp, rKey);

    }

    for (i = 0; i < macLen; i++)
        pMAC[i] = temp[i];
    
    return 0;
}

// HIGHT Verify CMAC
int HIGHT_CMAC_Verify_CMAC(unsigned char *pMAC, int macLen, unsigned char *pIn, int inLen, unsigned char *mKey)
{
    unsigned char temp[BLOCK_SIZE_HIGHT] = { 0x00, };
    unsigned char subKey[BLOCK_SIZE_HIGHT] = { 0x00, };
    unsigned char rKey[136] = { 0x00, };
    int blockLen = 0, i = 0, j = 0;

    if (macLen > BLOCK_SIZE_HIGHT)
        return 1;

    HIGHT_CMAC_KeySched(mKey, rKey);
    HIGHT_CMAC_Encrypt(subKey, subKey, rKey);

    // make K1
    HIGHT_CMAC_CMAC_SubkeySched(subKey);

    if (inLen == 0)
    {
        // make K2
        HIGHT_CMAC_CMAC_SubkeySched(subKey);

        subKey[0] ^= 0x80;

        HIGHT_CMAC_Encrypt(temp, subKey, rKey);
    }
    else if (inLen & 7)
    {
        // make K2
        HIGHT_CMAC_CMAC_SubkeySched(subKey);

        blockLen = (inLen + BLOCK_SIZE_HIGHT) / BLOCK_SIZE_HIGHT;

        for (i = 0; i < blockLen - 1; i++)
        {
            for (j = 0; j < BLOCK_SIZE_HIGHT; j++)
                temp[j] ^= pIn[BLOCK_SIZE_HIGHT * i + j];

            HIGHT_CMAC_Encrypt(temp, temp, rKey);
        }

        for (j = 0; (BLOCK_SIZE_HIGHT * i + j) < inLen; j++)
            temp[j] ^= pIn[BLOCK_SIZE_HIGHT * i + j] ^ subKey[j];
        temp[j] ^= 0x80 ^ subKey[j];
        for (j += 1; j < BLOCK_SIZE_HIGHT; j++)
            temp[j] ^= subKey[j];

        HIGHT_CMAC_Encrypt(temp, temp, rKey);
    }
    else
    {
        blockLen = inLen / BLOCK_SIZE_HIGHT;

        for (i = 0; i < blockLen - 1; i++)
        {
            for (j = 0; j < BLOCK_SIZE_HIGHT; j++)
                temp[j] ^= pIn[BLOCK_SIZE_HIGHT * i + j];

            HIGHT_CMAC_Encrypt(temp, temp, rKey);
        }

        for (j = 0; j < BLOCK_SIZE_HIGHT; j++)
            temp[j] ^= pIn[BLOCK_SIZE_HIGHT * i + j] ^ subKey[j];

        HIGHT_CMAC_Encrypt(temp, temp, rKey);

    }

    for (i = 0; i < macLen; i++)
        if (pMAC[i] != temp[i])
            return 1;
    
    return 0;
}




int main_kisa_hight_cmac()
{
    unsigned char key[16] = { 0x00, };
    unsigned char rKey[136] = { 0x00, };
    unsigned char msg[1000] = { 0x00, };
    unsigned char mac[8] = { 0x00, };
    unsigned char tag[8] = { 0x00, };
    int keyLen = 16, msgLen = 0, macLen = 8;

    print_title("Test HIGHT CMAC - 1!");
    
    keyLen = asc2hex(key, "F9C59DD0B28BB29B741BC650BE4186BB");
    msgLen = asc2hex(msg, "BDC99BB27AE87C9D53D78635A8C14E8BD6DF364C69E23E448D911D22C6B3917BE12FF3112B720E54E0113129E6AF");
    macLen = asc2hex(tag, "1726866576B73601");

    print_result("HIGHT Generate CMAC", HIGHT_CMAC_Generate_CMAC(mac, macLen, msg, msgLen, key));

    print_hex("key", key, keyLen);
    print_hex("msg", msg, msgLen);
    print_hex("mac", mac, macLen);
    print_hex("tag", tag, macLen);
    
    print_result("HIGHT Verify CMAC",HIGHT_CMAC_Verify_CMAC(tag, macLen, msg, msgLen, key));

    print_title("Test HIGHT CMAC - 2!");
    
    keyLen = asc2hex(key, "5059620A3ADF4159C41B3F89F48A361E");
    msgLen = asc2hex(msg, "");
    macLen = asc2hex(tag, "5B796790481524D4");

    print_result("HIGHT Generate CMAC", HIGHT_CMAC_Generate_CMAC(mac, macLen, msg, msgLen, key));

    print_hex("key", key, keyLen);
    print_hex("msg", msg, msgLen);
    print_hex("mac", mac, macLen);
    print_hex("tag", tag, macLen);

    print_result("HIGHT Verify CMAC",HIGHT_CMAC_Verify_CMAC(tag, macLen, msg, msgLen, key));
    
    return 0;
}
