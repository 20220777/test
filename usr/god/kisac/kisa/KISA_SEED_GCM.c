#include <stdint.h>
#include "KISA_SEED_GCM.h"
#define BLOCK_SIZE_SEED         16


#define SHIFTR( R, n )                              \
    (R)[3] = ((R)[3] >> n) ^ ((R)[2] << (32 - n)),  \
    (R)[2] = ((R)[2] >> n) ^ ((R)[1] << (32 - n)),  \
    (R)[1] = ((R)[1] >> n) ^ ((R)[0] << (32 - n)),  \
    (R)[0] = ((R)[0] >> n)

#define XOR128( R, A, B )       \
    (R)[0] = (A)[0] ^ (B)[0],   \
    (R)[1] = (A)[1] ^ (B)[1],   \
    (R)[2] = (A)[2] ^ (B)[2],   \
    (R)[3] = (A)[3] ^ (B)[3]

#define INCREASE( ctr )	((ctr)[3] == 0xFFFFFFFF) ? ((ctr)[2]++, (ctr)[3] = 0) : ((ctr)[3]++);
#define ZERO128(a)    a[0] = 0x00000000, a[1] = 0x00000000, a[2] = 0x00000000, a[3] = 0x00000000;


#define KC0     0x9e3779b9UL
#define KC1     0x3c6ef373UL
#define KC2     0x78dde6e6UL
#define KC3     0xf1bbcdccUL
#define KC4     0xe3779b99UL
#define KC5     0xc6ef3733UL
#define KC6     0x8dde6e67UL
#define KC7     0x1bbcdccfUL
#define KC8     0x3779b99eUL
#define KC9     0x6ef3733cUL
#define KC10    0xdde6e678UL
#define KC11    0xbbcdccf1UL
#define KC12    0x779b99e3UL
#define KC13    0xef3733c6UL
#define KC14    0xde6e678dUL
#define KC15    0xbcdccf1bUL

#define GetB0(A)    ( (unsigned char)((A)    ) )
#define GetB1(A)    ( (unsigned char)((A)>> 8) )
#define GetB2(A)    ( (unsigned char)((A)>>16) )
#define GetB3(A)    ( (unsigned char)((A)>>24) )

#define ROTL(x, n)  (((x) << (n)) | ((x) >> (32-(n))))
#define ROTR(x, n)  (((x) >> (n)) | ((x) << (32-(n))))

#define Byte2Word(src, src_offset)  \
    ((src[src_offset    ] & 0x0FF) << 24) |     \
    ((src[src_offset + 1] & 0x0FF) << 16) |     \
    ((src[src_offset + 2] & 0x0FF) <<  8) |     \
    ((src[src_offset + 3] & 0x0FF))

#define RoundKeyUpdate0(K, A, B, C, D, KC) {    \
    T0 = A + C - KC;                            \
    T1 = B + KC - D;                            \
    (K)[0] = SS0[GetB0(T0)] ^ SS1[GetB1(T0)] ^  \
             SS2[GetB2(T0)] ^ SS3[GetB3(T0)];   \
    (K)[1] = SS0[GetB0(T1)] ^ SS1[GetB1(T1)] ^  \
             SS2[GetB2(T1)] ^ SS3[GetB3(T1)];   \
    T0 = A;                                     \
    A = (A>>8) ^ (B<<24);                       \
    B = (B>>8) ^ (T0<<24);                      \
}

#define RoundKeyUpdate1(K, A, B, C, D, KC) {    \
    T0 = A + C - KC;                            \
    T1 = B + KC - D;                            \
    (K)[0] = SS0[GetB0(T0)] ^ SS1[GetB1(T0)] ^  \
             SS2[GetB2(T0)] ^ SS3[GetB3(T0)];   \
    (K)[1] = SS0[GetB0(T1)] ^ SS1[GetB1(T1)] ^  \
             SS2[GetB2(T1)] ^ SS3[GetB3(T1)];   \
    T0 = C;                                     \
    C = (C<<8) ^ (D>>24);                       \
    D = (D<<8) ^ (T0>>24);                      \
}

#define SeedRound(L0, L1, R0, R1, K) {          \
    T0 = R0 ^ (K)[0];                           \
    T1 = R1 ^ (K)[1];                           \
    T1 ^= T0;                                   \
    T1 = SS0[GetB0(T1)] ^ SS1[GetB1(T1)] ^      \
         SS2[GetB2(T1)] ^ SS3[GetB3(T1)];       \
    T0 += T1;                                   \
    T0 = SS0[GetB0(T0)] ^ SS1[GetB1(T0)] ^      \
         SS2[GetB2(T0)] ^ SS3[GetB3(T0)];       \
    T1 += T0;                                   \
    T1 = SS0[GetB0(T1)] ^ SS1[GetB1(T1)] ^      \
         SS2[GetB2(T1)] ^ SS3[GetB3(T1)];       \
    T0 += T1;                                   \
    L0 ^= T0; L1 ^= T1;                         \
}


static const unsigned int SS0[256] = 
{
    0x2989a1a8, 0x05858184, 0x16c6d2d4, 0x13c3d3d0, 0x14445054, 0x1d0d111c, 0x2c8ca0ac, 0x25052124,
    0x1d4d515c, 0x03434340, 0x18081018, 0x1e0e121c, 0x11415150, 0x3cccf0fc, 0x0acac2c8, 0x23436360,
    0x28082028, 0x04444044, 0x20002020, 0x1d8d919c, 0x20c0e0e0, 0x22c2e2e0, 0x08c8c0c8, 0x17071314,
    0x2585a1a4, 0x0f8f838c, 0x03030300, 0x3b4b7378, 0x3b8bb3b8, 0x13031310, 0x12c2d2d0, 0x2ecee2ec,
    0x30407070, 0x0c8c808c, 0x3f0f333c, 0x2888a0a8, 0x32023230, 0x1dcdd1dc, 0x36c6f2f4, 0x34447074,
    0x2ccce0ec, 0x15859194, 0x0b0b0308, 0x17475354, 0x1c4c505c, 0x1b4b5358, 0x3d8db1bc, 0x01010100,
    0x24042024, 0x1c0c101c, 0x33437370, 0x18889098, 0x10001010, 0x0cccc0cc, 0x32c2f2f0, 0x19c9d1d8,
    0x2c0c202c, 0x27c7e3e4, 0x32427270, 0x03838380, 0x1b8b9398, 0x11c1d1d0, 0x06868284, 0x09c9c1c8,
    0x20406060, 0x10405050, 0x2383a3a0, 0x2bcbe3e8, 0x0d0d010c, 0x3686b2b4, 0x1e8e929c, 0x0f4f434c,
    0x3787b3b4, 0x1a4a5258, 0x06c6c2c4, 0x38487078, 0x2686a2a4, 0x12021210, 0x2f8fa3ac, 0x15c5d1d4,
    0x21416160, 0x03c3c3c0, 0x3484b0b4, 0x01414140, 0x12425250, 0x3d4d717c, 0x0d8d818c, 0x08080008,
    0x1f0f131c, 0x19899198, 0x00000000, 0x19091118, 0x04040004, 0x13435350, 0x37c7f3f4, 0x21c1e1e0,
    0x3dcdf1fc, 0x36467274, 0x2f0f232c, 0x27072324, 0x3080b0b0, 0x0b8b8388, 0x0e0e020c, 0x2b8ba3a8,
    0x2282a2a0, 0x2e4e626c, 0x13839390, 0x0d4d414c, 0x29496168, 0x3c4c707c, 0x09090108, 0x0a0a0208,
    0x3f8fb3bc, 0x2fcfe3ec, 0x33c3f3f0, 0x05c5c1c4, 0x07878384, 0x14041014, 0x3ecef2fc, 0x24446064,
    0x1eced2dc, 0x2e0e222c, 0x0b4b4348, 0x1a0a1218, 0x06060204, 0x21012120, 0x2b4b6368, 0x26466264,
    0x02020200, 0x35c5f1f4, 0x12829290, 0x0a8a8288, 0x0c0c000c, 0x3383b3b0, 0x3e4e727c, 0x10c0d0d0,
    0x3a4a7278, 0x07474344, 0x16869294, 0x25c5e1e4, 0x26062224, 0x00808080, 0x2d8da1ac, 0x1fcfd3dc,
    0x2181a1a0, 0x30003030, 0x37073334, 0x2e8ea2ac, 0x36063234, 0x15051114, 0x22022220, 0x38083038,
    0x34c4f0f4, 0x2787a3a4, 0x05454144, 0x0c4c404c, 0x01818180, 0x29c9e1e8, 0x04848084, 0x17879394,
    0x35053134, 0x0bcbc3c8, 0x0ecec2cc, 0x3c0c303c, 0x31417170, 0x11011110, 0x07c7c3c4, 0x09898188,
    0x35457174, 0x3bcbf3f8, 0x1acad2d8, 0x38c8f0f8, 0x14849094, 0x19495158, 0x02828280, 0x04c4c0c4,
    0x3fcff3fc, 0x09494148, 0x39093138, 0x27476364, 0x00c0c0c0, 0x0fcfc3cc, 0x17c7d3d4, 0x3888b0b8,
    0x0f0f030c, 0x0e8e828c, 0x02424240, 0x23032320, 0x11819190, 0x2c4c606c, 0x1bcbd3d8, 0x2484a0a4,
    0x34043034, 0x31c1f1f0, 0x08484048, 0x02c2c2c0, 0x2f4f636c, 0x3d0d313c, 0x2d0d212c, 0x00404040,
    0x3e8eb2bc, 0x3e0e323c, 0x3c8cb0bc, 0x01c1c1c0, 0x2a8aa2a8, 0x3a8ab2b8, 0x0e4e424c, 0x15455154,
    0x3b0b3338, 0x1cccd0dc, 0x28486068, 0x3f4f737c, 0x1c8c909c, 0x18c8d0d8, 0x0a4a4248, 0x16465254,
    0x37477374, 0x2080a0a0, 0x2dcde1ec, 0x06464244, 0x3585b1b4, 0x2b0b2328, 0x25456164, 0x3acaf2f8,
    0x23c3e3e0, 0x3989b1b8, 0x3181b1b0, 0x1f8f939c, 0x1e4e525c, 0x39c9f1f8, 0x26c6e2e4, 0x3282b2b0,
    0x31013130, 0x2acae2e8, 0x2d4d616c, 0x1f4f535c, 0x24c4e0e4, 0x30c0f0f0, 0x0dcdc1cc, 0x08888088,
    0x16061214, 0x3a0a3238, 0x18485058, 0x14c4d0d4, 0x22426260, 0x29092128, 0x07070304, 0x33033330,
    0x28c8e0e8, 0x1b0b1318, 0x05050104, 0x39497178, 0x10809090, 0x2a4a6268, 0x2a0a2228, 0x1a8a9298
};

static const unsigned int SS1[256] = 
{
    0x38380830, 0xe828c8e0, 0x2c2d0d21, 0xa42686a2, 0xcc0fcfc3, 0xdc1eced2, 0xb03383b3, 0xb83888b0,
    0xac2f8fa3, 0x60204060, 0x54154551, 0xc407c7c3, 0x44044440, 0x6c2f4f63, 0x682b4b63, 0x581b4b53,
    0xc003c3c3, 0x60224262, 0x30330333, 0xb43585b1, 0x28290921, 0xa02080a0, 0xe022c2e2, 0xa42787a3,
    0xd013c3d3, 0x90118191, 0x10110111, 0x04060602, 0x1c1c0c10, 0xbc3c8cb0, 0x34360632, 0x480b4b43,
    0xec2fcfe3, 0x88088880, 0x6c2c4c60, 0xa82888a0, 0x14170713, 0xc404c4c0, 0x14160612, 0xf434c4f0,
    0xc002c2c2, 0x44054541, 0xe021c1e1, 0xd416c6d2, 0x3c3f0f33, 0x3c3d0d31, 0x8c0e8e82, 0x98188890,
    0x28280820, 0x4c0e4e42, 0xf436c6f2, 0x3c3e0e32, 0xa42585a1, 0xf839c9f1, 0x0c0d0d01, 0xdc1fcfd3,
    0xd818c8d0, 0x282b0b23, 0x64264662, 0x783a4a72, 0x24270723, 0x2c2f0f23, 0xf031c1f1, 0x70324272,
    0x40024242, 0xd414c4d0, 0x40014141, 0xc000c0c0, 0x70334373, 0x64274763, 0xac2c8ca0, 0x880b8b83,
    0xf437c7f3, 0xac2d8da1, 0x80008080, 0x1c1f0f13, 0xc80acac2, 0x2c2c0c20, 0xa82a8aa2, 0x34340430,
    0xd012c2d2, 0x080b0b03, 0xec2ecee2, 0xe829c9e1, 0x5c1d4d51, 0x94148490, 0x18180810, 0xf838c8f0,
    0x54174753, 0xac2e8ea2, 0x08080800, 0xc405c5c1, 0x10130313, 0xcc0dcdc1, 0x84068682, 0xb83989b1,
    0xfc3fcff3, 0x7c3d4d71, 0xc001c1c1, 0x30310131, 0xf435c5f1, 0x880a8a82, 0x682a4a62, 0xb03181b1,
    0xd011c1d1, 0x20200020, 0xd417c7d3, 0x00020202, 0x20220222, 0x04040400, 0x68284860, 0x70314171,
    0x04070703, 0xd81bcbd3, 0x9c1d8d91, 0x98198991, 0x60214161, 0xbc3e8eb2, 0xe426c6e2, 0x58194951,
    0xdc1dcdd1, 0x50114151, 0x90108090, 0xdc1cccd0, 0x981a8a92, 0xa02383a3, 0xa82b8ba3, 0xd010c0d0,
    0x80018181, 0x0c0f0f03, 0x44074743, 0x181a0a12, 0xe023c3e3, 0xec2ccce0, 0x8c0d8d81, 0xbc3f8fb3,
    0x94168692, 0x783b4b73, 0x5c1c4c50, 0xa02282a2, 0xa02181a1, 0x60234363, 0x20230323, 0x4c0d4d41,
    0xc808c8c0, 0x9c1e8e92, 0x9c1c8c90, 0x383a0a32, 0x0c0c0c00, 0x2c2e0e22, 0xb83a8ab2, 0x6c2e4e62,
    0x9c1f8f93, 0x581a4a52, 0xf032c2f2, 0x90128292, 0xf033c3f3, 0x48094941, 0x78384870, 0xcc0cccc0,
    0x14150511, 0xf83bcbf3, 0x70304070, 0x74354571, 0x7c3f4f73, 0x34350531, 0x10100010, 0x00030303,
    0x64244460, 0x6c2d4d61, 0xc406c6c2, 0x74344470, 0xd415c5d1, 0xb43484b0, 0xe82acae2, 0x08090901,
    0x74364672, 0x18190911, 0xfc3ecef2, 0x40004040, 0x10120212, 0xe020c0e0, 0xbc3d8db1, 0x04050501,
    0xf83acaf2, 0x00010101, 0xf030c0f0, 0x282a0a22, 0x5c1e4e52, 0xa82989a1, 0x54164652, 0x40034343,
    0x84058581, 0x14140410, 0x88098981, 0x981b8b93, 0xb03080b0, 0xe425c5e1, 0x48084840, 0x78394971,
    0x94178793, 0xfc3cccf0, 0x1c1e0e12, 0x80028282, 0x20210121, 0x8c0c8c80, 0x181b0b13, 0x5c1f4f53,
    0x74374773, 0x54144450, 0xb03282b2, 0x1c1d0d11, 0x24250521, 0x4c0f4f43, 0x00000000, 0x44064642,
    0xec2dcde1, 0x58184850, 0x50124252, 0xe82bcbe3, 0x7c3e4e72, 0xd81acad2, 0xc809c9c1, 0xfc3dcdf1,
    0x30300030, 0x94158591, 0x64254561, 0x3c3c0c30, 0xb43686b2, 0xe424c4e0, 0xb83b8bb3, 0x7c3c4c70,
    0x0c0e0e02, 0x50104050, 0x38390931, 0x24260622, 0x30320232, 0x84048480, 0x68294961, 0x90138393,
    0x34370733, 0xe427c7e3, 0x24240420, 0xa42484a0, 0xc80bcbc3, 0x50134353, 0x080a0a02, 0x84078783,
    0xd819c9d1, 0x4c0c4c40, 0x80038383, 0x8c0f8f83, 0xcc0ecec2, 0x383b0b33, 0x480a4a42, 0xb43787b3
};

static const unsigned int SS2[256] = 
{
    0xa1a82989, 0x81840585, 0xd2d416c6, 0xd3d013c3, 0x50541444, 0x111c1d0d, 0xa0ac2c8c, 0x21242505,
    0x515c1d4d, 0x43400343, 0x10181808, 0x121c1e0e, 0x51501141, 0xf0fc3ccc, 0xc2c80aca, 0x63602343,
    0x20282808, 0x40440444, 0x20202000, 0x919c1d8d, 0xe0e020c0, 0xe2e022c2, 0xc0c808c8, 0x13141707,
    0xa1a42585, 0x838c0f8f, 0x03000303, 0x73783b4b, 0xb3b83b8b, 0x13101303, 0xd2d012c2, 0xe2ec2ece,
    0x70703040, 0x808c0c8c, 0x333c3f0f, 0xa0a82888, 0x32303202, 0xd1dc1dcd, 0xf2f436c6, 0x70743444,
    0xe0ec2ccc, 0x91941585, 0x03080b0b, 0x53541747, 0x505c1c4c, 0x53581b4b, 0xb1bc3d8d, 0x01000101,
    0x20242404, 0x101c1c0c, 0x73703343, 0x90981888, 0x10101000, 0xc0cc0ccc, 0xf2f032c2, 0xd1d819c9,
    0x202c2c0c, 0xe3e427c7, 0x72703242, 0x83800383, 0x93981b8b, 0xd1d011c1, 0x82840686, 0xc1c809c9,
    0x60602040, 0x50501040, 0xa3a02383, 0xe3e82bcb, 0x010c0d0d, 0xb2b43686, 0x929c1e8e, 0x434c0f4f,
    0xb3b43787, 0x52581a4a, 0xc2c406c6, 0x70783848, 0xa2a42686, 0x12101202, 0xa3ac2f8f, 0xd1d415c5,
    0x61602141, 0xc3c003c3, 0xb0b43484, 0x41400141, 0x52501242, 0x717c3d4d, 0x818c0d8d, 0x00080808,
    0x131c1f0f, 0x91981989, 0x00000000, 0x11181909, 0x00040404, 0x53501343, 0xf3f437c7, 0xe1e021c1,
    0xf1fc3dcd, 0x72743646, 0x232c2f0f, 0x23242707, 0xb0b03080, 0x83880b8b, 0x020c0e0e, 0xa3a82b8b,
    0xa2a02282, 0x626c2e4e, 0x93901383, 0x414c0d4d, 0x61682949, 0x707c3c4c, 0x01080909, 0x02080a0a,
    0xb3bc3f8f, 0xe3ec2fcf, 0xf3f033c3, 0xc1c405c5, 0x83840787, 0x10141404, 0xf2fc3ece, 0x60642444,
    0xd2dc1ece, 0x222c2e0e, 0x43480b4b, 0x12181a0a, 0x02040606, 0x21202101, 0x63682b4b, 0x62642646,
    0x02000202, 0xf1f435c5, 0x92901282, 0x82880a8a, 0x000c0c0c, 0xb3b03383, 0x727c3e4e, 0xd0d010c0,
    0x72783a4a, 0x43440747, 0x92941686, 0xe1e425c5, 0x22242606, 0x80800080, 0xa1ac2d8d, 0xd3dc1fcf,
    0xa1a02181, 0x30303000, 0x33343707, 0xa2ac2e8e, 0x32343606, 0x11141505, 0x22202202, 0x30383808,
    0xf0f434c4, 0xa3a42787, 0x41440545, 0x404c0c4c, 0x81800181, 0xe1e829c9, 0x80840484, 0x93941787,
    0x31343505, 0xc3c80bcb, 0xc2cc0ece, 0x303c3c0c, 0x71703141, 0x11101101, 0xc3c407c7, 0x81880989,
    0x71743545, 0xf3f83bcb, 0xd2d81aca, 0xf0f838c8, 0x90941484, 0x51581949, 0x82800282, 0xc0c404c4,
    0xf3fc3fcf, 0x41480949, 0x31383909, 0x63642747, 0xc0c000c0, 0xc3cc0fcf, 0xd3d417c7, 0xb0b83888,
    0x030c0f0f, 0x828c0e8e, 0x42400242, 0x23202303, 0x91901181, 0x606c2c4c, 0xd3d81bcb, 0xa0a42484,
    0x30343404, 0xf1f031c1, 0x40480848, 0xc2c002c2, 0x636c2f4f, 0x313c3d0d, 0x212c2d0d, 0x40400040,
    0xb2bc3e8e, 0x323c3e0e, 0xb0bc3c8c, 0xc1c001c1, 0xa2a82a8a, 0xb2b83a8a, 0x424c0e4e, 0x51541545,
    0x33383b0b, 0xd0dc1ccc, 0x60682848, 0x737c3f4f, 0x909c1c8c, 0xd0d818c8, 0x42480a4a, 0x52541646,
    0x73743747, 0xa0a02080, 0xe1ec2dcd, 0x42440646, 0xb1b43585, 0x23282b0b, 0x61642545, 0xf2f83aca,
    0xe3e023c3, 0xb1b83989, 0xb1b03181, 0x939c1f8f, 0x525c1e4e, 0xf1f839c9, 0xe2e426c6, 0xb2b03282,
    0x31303101, 0xe2e82aca, 0x616c2d4d, 0x535c1f4f, 0xe0e424c4, 0xf0f030c0, 0xc1cc0dcd, 0x80880888,
    0x12141606, 0x32383a0a, 0x50581848, 0xd0d414c4, 0x62602242, 0x21282909, 0x03040707, 0x33303303,
    0xe0e828c8, 0x13181b0b, 0x01040505, 0x71783949, 0x90901080, 0x62682a4a, 0x22282a0a, 0x92981a8a
};

static const unsigned int SS3[256] = 
{
    0x08303838, 0xc8e0e828, 0x0d212c2d, 0x86a2a426, 0xcfc3cc0f, 0xced2dc1e, 0x83b3b033, 0x88b0b838,
    0x8fa3ac2f, 0x40606020, 0x45515415, 0xc7c3c407, 0x44404404, 0x4f636c2f, 0x4b63682b, 0x4b53581b,
    0xc3c3c003, 0x42626022, 0x03333033, 0x85b1b435, 0x09212829, 0x80a0a020, 0xc2e2e022, 0x87a3a427,
    0xc3d3d013, 0x81919011, 0x01111011, 0x06020406, 0x0c101c1c, 0x8cb0bc3c, 0x06323436, 0x4b43480b,
    0xcfe3ec2f, 0x88808808, 0x4c606c2c, 0x88a0a828, 0x07131417, 0xc4c0c404, 0x06121416, 0xc4f0f434,
    0xc2c2c002, 0x45414405, 0xc1e1e021, 0xc6d2d416, 0x0f333c3f, 0x0d313c3d, 0x8e828c0e, 0x88909818,
    0x08202828, 0x4e424c0e, 0xc6f2f436, 0x0e323c3e, 0x85a1a425, 0xc9f1f839, 0x0d010c0d, 0xcfd3dc1f,
    0xc8d0d818, 0x0b23282b, 0x46626426, 0x4a72783a, 0x07232427, 0x0f232c2f, 0xc1f1f031, 0x42727032,
    0x42424002, 0xc4d0d414, 0x41414001, 0xc0c0c000, 0x43737033, 0x47636427, 0x8ca0ac2c, 0x8b83880b,
    0xc7f3f437, 0x8da1ac2d, 0x80808000, 0x0f131c1f, 0xcac2c80a, 0x0c202c2c, 0x8aa2a82a, 0x04303434,
    0xc2d2d012, 0x0b03080b, 0xcee2ec2e, 0xc9e1e829, 0x4d515c1d, 0x84909414, 0x08101818, 0xc8f0f838,
    0x47535417, 0x8ea2ac2e, 0x08000808, 0xc5c1c405, 0x03131013, 0xcdc1cc0d, 0x86828406, 0x89b1b839,
    0xcff3fc3f, 0x4d717c3d, 0xc1c1c001, 0x01313031, 0xc5f1f435, 0x8a82880a, 0x4a62682a, 0x81b1b031,
    0xc1d1d011, 0x00202020, 0xc7d3d417, 0x02020002, 0x02222022, 0x04000404, 0x48606828, 0x41717031,
    0x07030407, 0xcbd3d81b, 0x8d919c1d, 0x89919819, 0x41616021, 0x8eb2bc3e, 0xc6e2e426, 0x49515819,
    0xcdd1dc1d, 0x41515011, 0x80909010, 0xccd0dc1c, 0x8a92981a, 0x83a3a023, 0x8ba3a82b, 0xc0d0d010,
    0x81818001, 0x0f030c0f, 0x47434407, 0x0a12181a, 0xc3e3e023, 0xcce0ec2c, 0x8d818c0d, 0x8fb3bc3f,
    0x86929416, 0x4b73783b, 0x4c505c1c, 0x82a2a022, 0x81a1a021, 0x43636023, 0x03232023, 0x4d414c0d,
    0xc8c0c808, 0x8e929c1e, 0x8c909c1c, 0x0a32383a, 0x0c000c0c, 0x0e222c2e, 0x8ab2b83a, 0x4e626c2e,
    0x8f939c1f, 0x4a52581a, 0xc2f2f032, 0x82929012, 0xc3f3f033, 0x49414809, 0x48707838, 0xccc0cc0c,
    0x05111415, 0xcbf3f83b, 0x40707030, 0x45717435, 0x4f737c3f, 0x05313435, 0x00101010, 0x03030003,
    0x44606424, 0x4d616c2d, 0xc6c2c406, 0x44707434, 0xc5d1d415, 0x84b0b434, 0xcae2e82a, 0x09010809,
    0x46727436, 0x09111819, 0xcef2fc3e, 0x40404000, 0x02121012, 0xc0e0e020, 0x8db1bc3d, 0x05010405,
    0xcaf2f83a, 0x01010001, 0xc0f0f030, 0x0a22282a, 0x4e525c1e, 0x89a1a829, 0x46525416, 0x43434003,
    0x85818405, 0x04101414, 0x89818809, 0x8b93981b, 0x80b0b030, 0xc5e1e425, 0x48404808, 0x49717839,
    0x87939417, 0xccf0fc3c, 0x0e121c1e, 0x82828002, 0x01212021, 0x8c808c0c, 0x0b13181b, 0x4f535c1f,
    0x47737437, 0x44505414, 0x82b2b032, 0x0d111c1d, 0x05212425, 0x4f434c0f, 0x00000000, 0x46424406,
    0xcde1ec2d, 0x48505818, 0x42525012, 0xcbe3e82b, 0x4e727c3e, 0xcad2d81a, 0xc9c1c809, 0xcdf1fc3d,
    0x00303030, 0x85919415, 0x45616425, 0x0c303c3c, 0x86b2b436, 0xc4e0e424, 0x8bb3b83b, 0x4c707c3c,
    0x0e020c0e, 0x40505010, 0x09313839, 0x06222426, 0x02323032, 0x84808404, 0x49616829, 0x83939013,
    0x07333437, 0xc7e3e427, 0x04202424, 0x84a0a424, 0xcbc3c80b, 0x43535013, 0x0a02080a, 0x87838407,
    0xc9d1d819, 0x4c404c0c, 0x83838003, 0x8f838c0f, 0xcec2cc0e, 0x0b33383b, 0x4a42480a, 0x87b3b437
};


int gcm_asc2hex(unsigned char *dst, const char *src)
{
    unsigned char temp = 0x00;
    int i = 0;

    while (src[i] != 0x00)
    {
        temp = 0x00;

        if ((src[i] >= 0x30) && (src[i] <= 0x39))
            temp = src[i] - '0';
        else if ((src[i] >= 0x41) && (src[i] <= 0x5A))
            temp = src[i] - 'A' + 10;
        else if ((src[i] >= 0x61) && (src[i] <= 0x7A))
            temp = src[i] - 'a' + 10;
        else
            temp = 0x00;

        (i & 1) ? (dst[i >> 1] ^= temp & 0x0F) : (dst[i >> 1] = 0, dst[i >> 1] = temp << 4);

        i++;
    }

    return ((i + 1) / 2);
}


void gcm_print_title(const char *title)
{
    printf("================================================\n");
    printf("  %s\n", title);
    printf("================================================\n");
}


void gcm_print_hex(const char *valName, const unsigned char *data, const int dataLen)
{
    int i = 0;

    printf("%s [%dbyte] :", valName, dataLen);
    for (i = 0; i < dataLen; i++)
    {
        if (!(i & 0x0F))
            printf("\n");
        printf(" %02X", data[i]);
    }
    printf("\n");
}

void gcm_print_result(const char *func, int ret)
{
    if (ret)
    {
        printf("================================================\n");
        printf("  %s Failure!\n", func);
		printf("================================================\n");

        exit(0);
    }
    else
    {
        printf("================================================\n");
        printf("  %s Success!\n", func);
        printf("================================================\n");
    }
}

void gcm_SEED_KeySched(unsigned char *mKey, unsigned int *rKey )
{
    unsigned int A, B, C, D;
    unsigned int T0, T1;

    A = Byte2Word(mKey, 0);
    B = Byte2Word(mKey, 4);
    C = Byte2Word(mKey, 8);
    D = Byte2Word(mKey,12);

    RoundKeyUpdate0(rKey   , A, B, C, D, KC0 );
    RoundKeyUpdate1(rKey+ 2, A, B, C, D, KC1 );
    RoundKeyUpdate0(rKey+ 4, A, B, C, D, KC2 );
    RoundKeyUpdate1(rKey+ 6, A, B, C, D, KC3 );
    RoundKeyUpdate0(rKey+ 8, A, B, C, D, KC4 );
    RoundKeyUpdate1(rKey+10, A, B, C, D, KC5 );
    RoundKeyUpdate0(rKey+12, A, B, C, D, KC6 );
    RoundKeyUpdate1(rKey+14, A, B, C, D, KC7 );
    RoundKeyUpdate0(rKey+16, A, B, C, D, KC8 );
    RoundKeyUpdate1(rKey+18, A, B, C, D, KC9 );
    RoundKeyUpdate0(rKey+20, A, B, C, D, KC10);
    RoundKeyUpdate1(rKey+22, A, B, C, D, KC11);
    RoundKeyUpdate0(rKey+24, A, B, C, D, KC12);
    RoundKeyUpdate1(rKey+26, A, B, C, D, KC13);
    RoundKeyUpdate0(rKey+28, A, B, C, D, KC14);

    T0 = A + C - KC15;
    T1 = B - D + KC15;
    rKey[30] = SS0[GetB0(T0)] ^ SS1[GetB1(T0)] ^
                SS2[GetB2(T0)] ^ SS3[GetB3(T0)];
    rKey[31] = SS0[GetB0(T1)] ^ SS1[GetB1(T1)] ^
                SS2[GetB2(T1)] ^ SS3[GetB3(T1)];
}


void gcm_SEED_Encrypt(unsigned int *pOut, unsigned int *pIn, unsigned int *rKey)
{
    unsigned int L0, L1, R0, R1;
    unsigned int T0, T1;

    L0 = pIn[0];
    L1 = pIn[1];
    R0 = pIn[2];
    R1 = pIn[3];

    SeedRound(L0, L1, R0, R1, rKey   );
    SeedRound(R0, R1, L0, L1, rKey+ 2);
    SeedRound(L0, L1, R0, R1, rKey+ 4);
    SeedRound(R0, R1, L0, L1, rKey+ 6);
    SeedRound(L0, L1, R0, R1, rKey+ 8);
    SeedRound(R0, R1, L0, L1, rKey+10);
    SeedRound(L0, L1, R0, R1, rKey+12);
    SeedRound(R0, R1, L0, L1, rKey+14);
    SeedRound(L0, L1, R0, R1, rKey+16);
    SeedRound(R0, R1, L0, L1, rKey+18);
    SeedRound(L0, L1, R0, R1, rKey+20);
    SeedRound(R0, R1, L0, L1, rKey+22);
    SeedRound(L0, L1, R0, R1, rKey+24);
    SeedRound(R0, R1, L0, L1, rKey+26);
    SeedRound(L0, L1, R0, R1, rKey+28);
    SeedRound(R0, R1, L0, L1, rKey+30);

    pOut[0] = R0;
    pOut[1] = R1;
    pOut[2] = L0;
    pOut[3] = L1;
}

void gcm_SEED_Decrypt(unsigned int *pOut, unsigned int *pIn, unsigned int *rKey)
{
    unsigned int L0, L1, R0, R1;
    unsigned int T0, T1;

    L0 = pIn[0];
    L1 = pIn[1];
    R0 = pIn[2];
    R1 = pIn[3];

    SeedRound(L0, L1, R0, R1, rKey+30);
    SeedRound(R0, R1, L0, L1, rKey+28);
    SeedRound(L0, L1, R0, R1, rKey+26);
    SeedRound(R0, R1, L0, L1, rKey+24);
    SeedRound(L0, L1, R0, R1, rKey+22);
    SeedRound(R0, R1, L0, L1, rKey+20);
    SeedRound(L0, L1, R0, R1, rKey+18);
    SeedRound(R0, R1, L0, L1, rKey+16);
    SeedRound(L0, L1, R0, R1, rKey+14);
    SeedRound(R0, R1, L0, L1, rKey+12);
    SeedRound(L0, L1, R0, R1, rKey+10);
    SeedRound(R0, R1, L0, L1, rKey+ 8);
    SeedRound(L0, L1, R0, R1, rKey+ 6);
    SeedRound(R0, R1, L0, L1, rKey+ 4);
    SeedRound(L0, L1, R0, R1, rKey+ 2);
    SeedRound(R0, R1, L0, L1, rKey+ 0);

    pOut[0] = R0;
    pOut[1] = R1;
    pOut[2] = L0;
    pOut[3] = L1;
}

void gcm_eByte2Word(unsigned int *dst, const unsigned char *src, const int srcLen)
{
    int i = 0;
    int remain = 0;

    for (i = 0; i < srcLen; i++)
    {
        remain = i & 3;

        if (remain == 0)
            dst[i >> 2]  = ((unsigned int)src[i] << 24);
        else if (remain == 1)
            dst[i >> 2] ^= ((unsigned int)src[i] << 16);
        else if (remain == 2)
            dst[i >> 2] ^= ((unsigned int)src[i] << 8);
        else
            dst[i >> 2] ^= ((unsigned int)src[i] & 0x000000FF);
    }
}

void gcm_eWord2Byte(unsigned char *dst, const unsigned int *src, const int srcLen)
{
    int i = 0;
    int remain = 0;

    for (i = 0; i < srcLen; i++)
    {
        remain = i & 3;

        if (remain == 0)
            dst[i] = (unsigned char)(src[i >> 2] >> 24);
        else if (remain == 1)
            dst[i] = (unsigned char)(src[i >> 2] >> 16);
        else if (remain == 2)
            dst[i] = (unsigned char)(src[i >> 2] >> 8);
        else
            dst[i] = (unsigned char) src[i >> 2];
    }
}


static const unsigned int R8[256] =
{
    0x00000000, 0x01c20000, 0x03840000, 0x02460000, 0x07080000, 0x06ca0000, 0x048c0000, 0x054e0000,
    0x0e100000, 0x0fd20000, 0x0d940000, 0x0c560000, 0x09180000, 0x08da0000, 0x0a9c0000, 0x0b5e0000,
    0x1c200000, 0x1de20000, 0x1fa40000, 0x1e660000, 0x1b280000, 0x1aea0000, 0x18ac0000, 0x196e0000,
    0x12300000, 0x13f20000, 0x11b40000, 0x10760000, 0x15380000, 0x14fa0000, 0x16bc0000, 0x177e0000,
    0x38400000, 0x39820000, 0x3bc40000, 0x3a060000, 0x3f480000, 0x3e8a0000, 0x3ccc0000, 0x3d0e0000,
    0x36500000, 0x37920000, 0x35d40000, 0x34160000, 0x31580000, 0x309a0000, 0x32dc0000, 0x331e0000,
    0x24600000, 0x25a20000, 0x27e40000, 0x26260000, 0x23680000, 0x22aa0000, 0x20ec0000, 0x212e0000,
    0x2a700000, 0x2bb20000, 0x29f40000, 0x28360000, 0x2d780000, 0x2cba0000, 0x2efc0000, 0x2f3e0000,
    0x70800000, 0x71420000, 0x73040000, 0x72c60000, 0x77880000, 0x764a0000, 0x740c0000, 0x75ce0000,
    0x7e900000, 0x7f520000, 0x7d140000, 0x7cd60000, 0x79980000, 0x785a0000, 0x7a1c0000, 0x7bde0000,
    0x6ca00000, 0x6d620000, 0x6f240000, 0x6ee60000, 0x6ba80000, 0x6a6a0000, 0x682c0000, 0x69ee0000,
    0x62b00000, 0x63720000, 0x61340000, 0x60f60000, 0x65b80000, 0x647a0000, 0x663c0000, 0x67fe0000,
    0x48c00000, 0x49020000, 0x4b440000, 0x4a860000, 0x4fc80000, 0x4e0a0000, 0x4c4c0000, 0x4d8e0000,
    0x46d00000, 0x47120000, 0x45540000, 0x44960000, 0x41d80000, 0x401a0000, 0x425c0000, 0x439e0000,
    0x54e00000, 0x55220000, 0x57640000, 0x56a60000, 0x53e80000, 0x522a0000, 0x506c0000, 0x51ae0000,
    0x5af00000, 0x5b320000, 0x59740000, 0x58b60000, 0x5df80000, 0x5c3a0000, 0x5e7c0000, 0x5fbe0000,
    0xe1000000, 0xe0c20000, 0xe2840000, 0xe3460000, 0xe6080000, 0xe7ca0000, 0xe58c0000, 0xe44e0000,
    0xef100000, 0xeed20000, 0xec940000, 0xed560000, 0xe8180000, 0xe9da0000, 0xeb9c0000, 0xea5e0000,
    0xfd200000, 0xfce20000, 0xfea40000, 0xff660000, 0xfa280000, 0xfbea0000, 0xf9ac0000, 0xf86e0000,
    0xf3300000, 0xf2f20000, 0xf0b40000, 0xf1760000, 0xf4380000, 0xf5fa0000, 0xf7bc0000, 0xf67e0000,
    0xd9400000, 0xd8820000, 0xdac40000, 0xdb060000, 0xde480000, 0xdf8a0000, 0xddcc0000, 0xdc0e0000,
    0xd7500000, 0xd6920000, 0xd4d40000, 0xd5160000, 0xd0580000, 0xd19a0000, 0xd3dc0000, 0xd21e0000,
    0xc5600000, 0xc4a20000, 0xc6e40000, 0xc7260000, 0xc2680000, 0xc3aa0000, 0xc1ec0000, 0xc02e0000,
    0xcb700000, 0xcab20000, 0xc8f40000, 0xc9360000, 0xcc780000, 0xcdba0000, 0xcffc0000, 0xce3e0000,
    0x91800000, 0x90420000, 0x92040000, 0x93c60000, 0x96880000, 0x974a0000, 0x950c0000, 0x94ce0000,
    0x9f900000, 0x9e520000, 0x9c140000, 0x9dd60000, 0x98980000, 0x995a0000, 0x9b1c0000, 0x9ade0000,
    0x8da00000, 0x8c620000, 0x8e240000, 0x8fe60000, 0x8aa80000, 0x8b6a0000, 0x892c0000, 0x88ee0000,
    0x83b00000, 0x82720000, 0x80340000, 0x81f60000, 0x84b80000, 0x857a0000, 0x873c0000, 0x86fe0000,
    0xa9c00000, 0xa8020000, 0xaa440000, 0xab860000, 0xaec80000, 0xaf0a0000, 0xad4c0000, 0xac8e0000,
    0xa7d00000, 0xa6120000, 0xa4540000, 0xa5960000, 0xa0d80000, 0xa11a0000, 0xa35c0000, 0xa29e0000,
    0xb5e00000, 0xb4220000, 0xb6640000, 0xb7a60000, 0xb2e80000, 0xb32a0000, 0xb16c0000, 0xb0ae0000,
    0xbbf00000, 0xba320000, 0xb8740000, 0xb9b60000, 0xbcf80000, 0xbd3a0000, 0xbf7c0000, 0xbebe0000
};


void makeM8(unsigned int M[][4], const unsigned int *H)
{
    unsigned int i = 64, j = 0, temp[4] = { 0,  };

    M[128][0] = H[0];
    M[128][1] = H[1];
    M[128][2] = H[2];
    M[128][3] = H[3];
  //{
  //  int32_t i = 0, j=0;

  //  printf("----------------------------------------\r\n");
  //  for ( i=0 ; i<256 ; i++ )
  //  {
  //    printf(" %08d | %08X %08X   %08X %08X \r\n", i,  M[i][0],M[i][1],M[i][2],M[i][3]);
  //  }
  //  printf("****************************************\r\n");
  //}


    while( i > 0 )
    {
    printf(" [%d] ", i);

        temp[0] = M[i << 1][0];
        temp[1] = M[i << 1][1];
        temp[2] = M[i << 1][2];
        temp[3] = M[i << 1][3];

        if( temp[3] & 0x01 )
        {
            SHIFTR( temp, 1 );
            temp[0] ^= 0xE1000000;
        }
        else
        {
            SHIFTR( temp, 1 );
        }

        M[i][0] = temp[0];
        M[i][1] = temp[1];
        M[i][2] = temp[2];
        M[i][3] = temp[3];

        i >>= 1;
    }

  //{
  //  int32_t i = 0, j=0;

  //  printf("----------------------------------------\r\n");
  //  for ( i=0 ; i<256 ; i++ )
  //  {
  //    printf(" %08d | %08X %08X   %08X %08X \r\n", i,  M[i][0],M[i][1],M[i][2],M[i][3]);
  //  }
  //  printf("****************************************\r\n");
  //}


    i = 2;

    while( i < 256 )
    {
        for( j = 1; j < i; j++ )
        {
            M[i + j][0] = M[i][0] ^ M[j][0];
            M[i + j][1] = M[i][1] ^ M[j][1];
            M[i + j][2] = M[i][2] ^ M[j][2];
            M[i + j][3] = M[i][3] ^ M[j][3];
        }

        i <<= 1;
    }

    M[0][0] = 0;
    M[0][1] = 0;
    M[0][2] = 0;
    M[0][3] = 0;
}

void GHASH_8BIT(unsigned int *out, unsigned int *in, unsigned int M[][4], const unsigned int *R)
{
    unsigned int W[4] = { 0, }, Z[4] = {0, };
    unsigned int temp = 0, i = 0;

    XOR128( Z, out, in );

  //{
  //  int32_t i = 0, j=0;
  //  uint8_t* p = Z;
  //  printf( "\r\n-----------------------------------------------------"
  //          "\r\n- %50s -"
  //          "\r\n-----------------------------------------------------\r\n", "Z");
  //  for ( i=0 ; i<16 ; i++ )
  //  {
  //    if (i!=0) 
  //      if ( (i%8)==0 )
  //        if ( (i%16)==0 ) printf("\r\n");
  //        else printf("   ");
  //    printf(" %02X", *(p+i));
  //  }
  //  printf( "\r\n*****************************************************\r\n");
  //  printf("pause.......\r\n");
  //  getchar();
  //}



    for( i = 0; i < 15; i++ )
    {
        temp = ((Z[3 - (i >> 2)] >> ((i & 3) << 3)) & 0xFF);

        W[0] ^= M[temp][0];
        W[1] ^= M[temp][1];
        W[2] ^= M[temp][2];
        W[3] ^= M[temp][3];



        temp = W[3] & 0xFF;
    printf(" %08d : %08X %08X %08X %08X  ->", i, W[0], W[1], W[2], W[3]);
        
        SHIFTR( W, 8 );

    printf(" %08X %08X %08X %08X  ->", W[0], W[1], W[2], W[3]);

        W[0] ^= R[temp];

    printf(" %08X %08X \r\n", R[temp], W[0]);

    }

    temp = (Z[0] >> 24) & 0xFF;

    out[0] = W[0] ^ M[temp][0];
    out[1] = W[1] ^ M[temp][1];
    out[2] = W[2] ^ M[temp][2];
    out[3] = W[3] ^ M[temp][3];
}


int SEED_GCM_Encryption(
    unsigned char *ct, unsigned int *ctLen,
    unsigned char *pt, unsigned int ptLen,
    unsigned int macLen,
    unsigned char *nonce, unsigned int nonceLen,
    unsigned char *aad, unsigned int aadLen,
    unsigned char *mKey)
{
    unsigned int rKey[32] = { 0x00, };
    unsigned int H[4] = { 0x00, }, Z[4] = { 0x00, }, tmp[8] = { 0x00, };
    unsigned int GCTR_in[4] = { 0x00, }, GCTR_out[4] = { 0x00, };
    unsigned int GHASH_in[4] = { 0x00, }, GHASH_out[4] = { 0x00, };
    unsigned int M8[256][4] = { 0x00, }, i = 0;

    if (macLen > 16)
    {
        *ctLen = 0;

        return 1;
    }

    gcm_SEED_KeySched(mKey, rKey);

    gcm_SEED_Encrypt(H, H, rKey);

    makeM8(M8, H);

    if (nonceLen == 12)
    {
        gcm_eByte2Word(GCTR_in, nonce, nonceLen);

        GCTR_in[3] = 1;
        
        gcm_SEED_Encrypt(Z, GCTR_in, rKey);
    }
    else
    {
        for (i = 0; i < nonceLen; i += BLOCK_SIZE_SEED)
        {
            ZERO128(tmp);

            if ((nonceLen - i) < 16)
                gcm_eByte2Word(tmp, nonce + i, nonceLen - i);
            else
                gcm_eByte2Word(tmp, nonce + i, BLOCK_SIZE_SEED);
            
            GHASH_8BIT(GCTR_in, tmp, M8, R8);
        }

        ZERO128(tmp);
        tmp[3] = (nonceLen << 3);

        GHASH_8BIT(GCTR_in, tmp, M8, R8);

        gcm_SEED_Encrypt(Z, GCTR_in, rKey);
    }

  {
    int32_t i = 0, j=0;
    uint8_t* p = GCTR_in;
    printf( "\r\n-----------------------------------------------------"
            "\r\n- %50s -"
            "\r\n-----------------------------------------------------\r\n", "GCTR_in");
    for ( i=0 ; i<16 ; i++ )
    {
      if (i!=0) 
        if ( (i%8)==0 )
          if ( (i%16)==0 ) printf("\r\n");
          else printf("   ");
      printf(" %02X", *(p+i));
    }
    printf( "\r\n*****************************************************\r\n");
  }





    for (i = 0; i < ptLen; i += BLOCK_SIZE_SEED)
    {
        ZERO128(tmp);

        INCREASE(GCTR_in);

        gcm_SEED_Encrypt(GCTR_out, GCTR_in, rKey);

        if ((ptLen - i) < 16)
        {
            gcm_eByte2Word(tmp, pt + i, ptLen - i);
            XOR128(GCTR_out, GCTR_out, tmp);
            gcm_eWord2Byte(ct + i, GCTR_out, ptLen - i);
        }
        else
        {
            gcm_eByte2Word(tmp, pt + i, BLOCK_SIZE_SEED);
            XOR128(GCTR_out, GCTR_out, tmp);
            gcm_eWord2Byte(ct + i, GCTR_out, BLOCK_SIZE_SEED);
        }
    }

  {
    int32_t i = 0, j=0;
    uint8_t* p = GCTR_out;
    printf( "\r\n-----------------------------------------------------"
            "\r\n- %50s -"
            "\r\n-----------------------------------------------------\r\n", "GCTR_out");
    for ( i=0 ; i<16 ; i++ )
    {
      if (i!=0) 
        if ( (i%8)==0 )
          if ( (i%16)==0 ) printf("\r\n");
          else printf("   ");
      printf(" %02X", *(p+i));
    }
    printf( "\r\n*****************************************************\r\n");
  }



    for (i = 0; i < aadLen; i += BLOCK_SIZE_SEED)
    {
        ZERO128(GHASH_in);

        if ((aadLen - i) < 16)
            gcm_eByte2Word(GHASH_in, aad + i, aadLen - i);
        else
            gcm_eByte2Word(GHASH_in, aad + i, BLOCK_SIZE_SEED);

        GHASH_8BIT(GHASH_out, GHASH_in, M8, R8);


        {
          int32_t i = 0, j=0;
          uint8_t* p = GHASH_out;
          printf( "\r\n-----------------------------------------------------"
                  "\r\n- %50s -"
                  "\r\n-----------------------------------------------------\r\n", "GHASH_out");
          for ( i=0 ; i<16 ; i++ )
          {
            if (i!=0) 
              if ( (i%8)==0 )
                if ( (i%16)==0 ) printf("\r\n");
                else printf("   ");
            printf(" %02X", *(p+i));
          }
          printf( "\r\n*****************************************************\r\n");
        }

    }

    for (i = 0; i < ptLen; i += BLOCK_SIZE_SEED)
    {
        ZERO128(GHASH_in);

        if ((ptLen - i) < 16)
            gcm_eByte2Word(GHASH_in, ct + i, ptLen - i);
        else
            gcm_eByte2Word(GHASH_in, ct + i, BLOCK_SIZE_SEED);

        GHASH_8BIT(GHASH_out, GHASH_in, M8, R8);
    }
  {
    int32_t i = 0, j=0;
    uint8_t* p = GHASH_out;
    printf( "\r\n-----------------------------------------------------"
            "\r\n- %50s -"
            "\r\n-----------------------------------------------------\r\n", "GHASH_out");
    for ( i=0 ; i<16 ; i++ )
    {
      if (i!=0) 
        if ( (i%8)==0 )
          if ( (i%16)==0 ) printf("\r\n");
          else printf("   ");
      printf(" %02X", *(p+i));
    }
    printf( "\r\n*****************************************************\r\n");
  }

    ZERO128(GHASH_in);

    GHASH_in[1] ^= aadLen << 3;
    GHASH_in[3] ^= ptLen << 3;

      {
        int32_t i = 0, j=0;
        uint8_t* p = GHASH_in;
        printf( "\r\n-----------------------------------------------------"
                "\r\n- %50s -"
                "\r\n-----------------------------------------------------\r\n", "GHASH_in");
        for ( i=0 ; i<16 ; i++ )
        {
          if (i!=0) 
            if ( (i%8)==0 )
              if ( (i%16)==0 ) printf("\r\n");
              else printf("   ");
          printf(" %02X", *(p+i));
        }
        printf( "\r\n*****************************************************\r\n");
      }


    GHASH_8BIT(GHASH_out, GHASH_in, M8, R8);

    XOR128(GHASH_out, GHASH_out, Z);

    gcm_eWord2Byte(ct + ptLen, GHASH_out, macLen);


  {
    int32_t i = 0, j=0;
    uint8_t* p = GHASH_out;
    printf( "\r\n-----------------------------------------------------"
            "\r\n- %50s -"
            "\r\n-----------------------------------------------------\r\n", "GHASH_out");
    for ( i=0 ; i<16 ; i++ )
    {
      if (i!=0) 
        if ( (i%8)==0 )
          if ( (i%16)==0 ) printf("\r\n");
          else printf("   ");
      printf(" %02X", *(p+i));
    }
    printf( "\r\n*****************************************************\r\n");
  }




    *ctLen = ptLen + macLen;

    return 0;
}


int SEED_GCM_Decryption(
    unsigned char *pt, unsigned int *ptLen,
    unsigned char *ct, unsigned int ctLen,
    unsigned int macLen,
    unsigned char *nonce, unsigned int nonceLen,
    unsigned char *aad, unsigned int aadLen,
    unsigned char *mKey)
{
    unsigned int rKey[32] = { 0x00, };
    unsigned int H[4] = { 0x00, }, Z[4] = { 0x00, }, tmp[8] = { 0x00, };
    unsigned char MAC[16] = { 0x00, };
    unsigned int GCTR_in[4] = { 0x00, }, GCTR_out[4] = { 0x00, };
    unsigned int GHASH_in[4] = { 0x00, }, GHASH_out[4] = { 0x00, };
    unsigned int M8[256][4] = { 0x00, }, i, j;

    if (macLen > 16)
    {
        *ptLen = 0;

        return 1;
    }

    gcm_SEED_KeySched(mKey, rKey);

    gcm_SEED_Encrypt(H, H, rKey);

    makeM8(M8, H);

    if (nonceLen == 12)
    {
        gcm_eByte2Word(GCTR_in, nonce, nonceLen);

        GCTR_in[3] = 1;
        
        gcm_SEED_Encrypt(Z, GCTR_in, rKey);
    }
    else
    {
        for (i = 0; i < nonceLen; i += BLOCK_SIZE_SEED)
        {
            ZERO128(tmp);

            if ((nonceLen - i) < 16)
                gcm_eByte2Word(tmp, nonce + i, nonceLen - i);
            else
                gcm_eByte2Word(tmp, nonce + i, BLOCK_SIZE_SEED);
            
            GHASH_8BIT(GCTR_in, tmp, M8, R8);
        }

        ZERO128(tmp);
        tmp[3] = (nonceLen << 3);

        GHASH_8BIT(GCTR_in, tmp, M8, R8);
        
        gcm_SEED_Encrypt(Z, GCTR_in, rKey);
    }

    for (i = 0; i < ctLen - macLen; i += BLOCK_SIZE_SEED)
    {
        ZERO128(tmp);

        INCREASE(GCTR_in);

        gcm_SEED_Encrypt(GCTR_out, GCTR_in, rKey);

        if ((ctLen - macLen - i) < 16)
        {
            gcm_eByte2Word(tmp, ct + i, ctLen - macLen - i);
            XOR128(GCTR_out, GCTR_out, tmp);
            gcm_eWord2Byte(pt + i, GCTR_out, ctLen - macLen - i);
        }
        else
        {
            gcm_eByte2Word(tmp, ct + i, BLOCK_SIZE_SEED);
            XOR128(GCTR_out, GCTR_out, tmp);
            gcm_eWord2Byte(pt + i, GCTR_out, BLOCK_SIZE_SEED);
        }
    }

    for (i = 0; i < aadLen; i += BLOCK_SIZE_SEED)
    {
        ZERO128(GHASH_in);

        if ((aadLen - i) < 16)
            gcm_eByte2Word(GHASH_in, aad + i, aadLen - i);
        else
            gcm_eByte2Word(GHASH_in, aad + i, BLOCK_SIZE_SEED);

        GHASH_8BIT(GHASH_out, GHASH_in, M8, R8);
    }

    for (i = 0; i < ctLen - macLen; i += BLOCK_SIZE_SEED)
    {
        ZERO128(GHASH_in);

        if ((ctLen - macLen - i) < 16)
            gcm_eByte2Word(GHASH_in, ct + i, ctLen - macLen - i);
        else
            gcm_eByte2Word(GHASH_in, ct + i, BLOCK_SIZE_SEED);

        GHASH_8BIT(GHASH_out, GHASH_in, M8, R8);
    }

    ZERO128(GHASH_in);

    GHASH_in[1] = aadLen <<3;
    GHASH_in[3] = (ctLen - macLen) << 3;

    GHASH_8BIT(GHASH_out, GHASH_in, M8, R8);

    XOR128(GHASH_out, GHASH_out, Z);

    gcm_eWord2Byte(MAC, GHASH_out, macLen);

    for (i = 0; i < macLen; i++)
    {
        if (MAC[i] != ct[ctLen - macLen + i])
        {
            for (j = 0; j < ctLen - macLen; j++)
                pt[j] = 0;
                
            return 1;
        }
    }

    *ptLen = ctLen - macLen;

    return 0;
}




int main_kisa_seed_gcm()
{
    unsigned char key[160] = { 0x00, };
    unsigned char in[160] = { 0x00, };
    unsigned char out1[160] = { 0x00, };
    unsigned char out2[160] = { 0x00, };
    unsigned char nonce[160] = { 0x00, };
    unsigned char aad[160] = { 0x00, };

    int keyLen = 0, inLen = 0, out1Len = 0, out2Len = 0, nonceLen = 0, aadLen = 0, macLen = 16;

    gcm_print_title("Test SEED GCM - 1");

    keyLen = gcm_asc2hex(key, "1032F990B76B0686C0CF9BBB80AEE08C");
    nonceLen = gcm_asc2hex(nonce, "75E2534A34F65F85A28E318A");
    aadLen = gcm_asc2hex(aad, "9DEA72038744675F026877F23C1F6056F77700BA38ADB2E33F50DB71BCA4C06440459BDEF20CED2A833615FE64C322FD361DE68082FA4B96AA83EB4A1FB6DA24D509C6F2F45043C7D1E060451CF57E185B5162C39626889F5436BA20C739E25B447F1DC5F6D6103ED2AE7F4ECD7B1BAE4D5B9C0ADEF9100527B1737E1CF57F11");
    inLen = gcm_asc2hex(in, "6702C72AA04D49BDD4269D672A6C369AD9C72CDCDF8D92CBF6E2045EC4247F6D52867574BFFA2194365519DA1DAD22C48F0647010D2E2D7970E6A18D224273A08E5387D6D503291BC33FA168015C07418CB35983658FCB5C8B4A5E9B26B2B42A05B123D84A2E085C642E5E973E3F8F1AB61689E85177157D2D55640F373BEB13");

	macLen = 12;

    gcm_print_result("SEED GCM Encryption", SEED_GCM_Encryption(out1, (unsigned int *)&out1Len, in, inLen, macLen, nonce, nonceLen, aad, aadLen, key));

    gcm_print_hex("key", key, keyLen);
    gcm_print_hex("in", in, inLen);
    gcm_print_hex("nonce", nonce, nonceLen);
    gcm_print_hex("aad", aad, aadLen);
    gcm_print_hex("out1", out1, out1Len);

    gcm_print_result("SEED GCM Decryption", SEED_GCM_Decryption(out2, (unsigned int *)&out2Len, out1, out1Len, macLen, nonce, nonceLen, aad, aadLen, key));

    gcm_print_hex("in", out1, out1Len);
    gcm_print_hex("out2", out2, out2Len);

	gcm_print_title("Test SEED GCM - 2");

	keyLen = gcm_asc2hex(key, "11B13AD70556009DA9D0A8A8C11E4199");
	nonceLen = gcm_asc2hex(nonce, "FC80175A2ADF87A8A96911CF207CAFB5");
	aadLen = gcm_asc2hex(aad, "");
	inLen = gcm_asc2hex(in, "");

	macLen = 16;

	gcm_print_result("SEED GCM Encryption", SEED_GCM_Encryption(out1, (unsigned int *)&out1Len, in, inLen, macLen, nonce, nonceLen, aad, aadLen, key));

	gcm_print_hex("key", key, keyLen);
	gcm_print_hex("in", in, inLen);
	gcm_print_hex("nonce", nonce, nonceLen);
	gcm_print_hex("aad", aad, aadLen);
	gcm_print_hex("out1", out1, out1Len);

	gcm_print_result("SEED GCM Decryption", SEED_GCM_Decryption(out2, (unsigned int *)&out2Len, out1, out1Len, macLen, nonce, nonceLen, aad, aadLen, key));

	gcm_print_hex("in", out1, out1Len);
	gcm_print_hex("out2", out2, out2Len);

    return 0;
}
