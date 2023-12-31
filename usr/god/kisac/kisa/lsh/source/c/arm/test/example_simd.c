#include <stdio.h>
#include <string.h>
#include "../include/lsh.h"
#include "../include/hmac.h"
#include "../src/lsh_local.h"
#include "../src/check_neon.h"
#include "../src/no_arch/lsh256.h"
#include "../src/no_arch/lsh512.h"
#include "../src/neon/lsh256_neon.h"
#include "../src/neon/lsh512_neon.h"

#define LSH256_TEST_CNT 16
#define LSH512_TEST_CNT 16

static lsh_u8 g_hmac_key_data[384];
static lsh_u8 g_lsh_test_data[1024];

static const lsh_u8 g_lsh256_testvector_iv[64] = {
	0x46, 0xa1, 0x0f, 0x1f, 0xfd, 0xdc, 0xe4, 0x86, 0xb4, 0x14, 0x43, 0xa8, 0x19, 0x8e, 0x6b, 0x9d,
	0x33, 0x04, 0x38, 0x8d, 0xb0, 0xf5, 0xa3, 0xc7, 0xb3, 0x60, 0x61, 0xc4, 0x7a, 0xdb, 0xd5, 0x53,
	0x10, 0x5d, 0x53, 0x78, 0x2f, 0x74, 0xde, 0x54, 0x5c, 0x2f, 0x2d, 0x95, 0xf2, 0x55, 0x3f, 0xbe,
	0x80, 0x51, 0x35, 0x7a, 0x13, 0x86, 0x68, 0xc8, 0x47, 0xaa, 0x44, 0x84, 0xe0, 0x1a, 0xfb, 0x41,
};

static const lsh_u8 g_lsh512_testvector_iv[128] = {
	0xad, 0xd5, 0x0f, 0x3c, 0x7f, 0x07, 0x09, 0x4e, 0xe3, 0xf3, 0xce, 0xe8, 0xf9, 0x41, 0x8a, 0x4f,
	0xb5, 0x27, 0xec, 0xde, 0x5b, 0x3d, 0x0a, 0xe9, 0x2e, 0xf6, 0xde, 0xc6, 0x80, 0x76, 0xf5, 0x01,
	0x8c, 0xb9, 0x94, 0xca, 0xe5, 0xac, 0xa2, 0x16, 0xfb, 0xb9, 0xea, 0xe4, 0xbb, 0xa4, 0x8c, 0xc7,
	0x65, 0x0a, 0x52, 0x61, 0x74, 0x72, 0x5f, 0xea, 0x1f, 0x9a, 0x61, 0xa7, 0x3f, 0x8d, 0x80, 0x85,
	0xb6, 0x60, 0x73, 0x78, 0x17, 0x3b, 0x53, 0x9b, 0x1b, 0xc9, 0x98, 0x53, 0xb0, 0xc0, 0xb9, 0xed,
	0xdf, 0x72, 0x7f, 0xc1, 0x9b, 0x18, 0x2d, 0x47, 0xdb, 0xef, 0x36, 0x0c, 0xf8, 0x93, 0xa4, 0x57,
	0x49, 0x81, 0xf5, 0xe5, 0x70, 0x14, 0x7e, 0x80, 0xd0, 0x0c, 0x44, 0x90, 0xca, 0x7d, 0x3e, 0x30,
	0x5d, 0x73, 0x94, 0x0c, 0x0e, 0x4a, 0xe1, 0xec, 0x89, 0x40, 0x85, 0xe2, 0xed, 0xb2, 0xd8, 0x19,
};

static lsh_u8 g_lsh_testvector_data[1024];

static const int g_lsh256_testvector_step[LSH256_TEST_CNT] = {
	0, 1, 2, 7, 8, 15, 16, 1023, 1024, 1025, 2047, 2048, 2049, 3071, 3072, 3073
};

static const int g_lsh512_testvector_step[LSH512_TEST_CNT] = {
	0, 1, 2, 7, 8, 15, 16, 2047, 2048, 2049, 4095, 4096, 4097, 6143, 6144, 6145
};

static const lsh_u8 g_lsh256_tv_answer[LSH256_TEST_CNT][LSH256_HASH_VAL_MAX_BYTE_LEN] =
{
	{
		0xf3, 0xcd, 0x41, 0x6a, 0x03, 0x81, 0x82, 0x17, 0x72, 0x6c, 0xb4, 0x7f, 0x4e, 0x4d, 0x28, 0x81,
		0xc9, 0xc2, 0x9f, 0xd4, 0x45, 0xc1, 0x8b, 0x66, 0xfb, 0x19, 0xde, 0xa1, 0xa8, 0x10, 0x07, 0xc1,
	}, {
		0xfd, 0x5b, 0xe8, 0x99, 0xff, 0x15, 0x74, 0x3e, 0x75, 0xc1, 0xde, 0xfb, 0xdc, 0xd8, 0xbd, 0x8f,
		0x10, 0x39, 0x75, 0xd8, 0x1d, 0x64, 0xd7, 0xe3, 0x5f, 0xe9, 0xe2, 0x3d, 0x98, 0x6e, 0x66, 0x62,
	}, {
		0x10, 0xae, 0x63, 0xfd, 0x3d, 0xc6, 0x3f, 0xa8, 0xe2, 0x1b, 0x51, 0xae, 0xa0, 0xd4, 0x6d, 0x40,
		0x95, 0x7c, 0xc0, 0x8e, 0x0d, 0x8f, 0x6a, 0x74, 0xcb, 0xfd, 0xaf, 0xf1, 0x61, 0xe0, 0xc0, 0xc2,
	}, {
		0x34, 0x14, 0x0d, 0x1e, 0x77, 0x87, 0x2c, 0x87, 0x99, 0xc1, 0xeb, 0xb3, 0x55, 0xcb, 0xb3, 0xe6,
		0x19, 0x31, 0xf4, 0x59, 0x4c, 0x34, 0x7a, 0x29, 0xa1, 0x2f, 0x29, 0x3a, 0x46, 0xdf, 0x0f, 0xe1,
	}, {
		0xcf, 0x25, 0xc4, 0x7e, 0xb1, 0xef, 0xa7, 0x7d, 0x2f, 0x7a, 0x1d, 0xfc, 0xc0, 0x9f, 0x4d, 0x3a,
		0xcf, 0xe9, 0x7d, 0xc7, 0x7c, 0x31, 0x7b, 0x43, 0x97, 0x6e, 0x7b, 0x23, 0x8d, 0xa3, 0xdc, 0x71,
	}, {
		0x0a, 0xfe, 0xa6, 0xcd, 0xc8, 0xba, 0x4c, 0x2b, 0x2f, 0x5f, 0xb1, 0xf3, 0x2e, 0xd2, 0x7c, 0x22,
		0xac, 0xc8, 0x81, 0x4e, 0x70, 0xd5, 0x4f, 0x64, 0xb6, 0x23, 0xb4, 0x10, 0x9b, 0x32, 0x21, 0x77,
	}, {
		0x70, 0x59, 0x9e, 0x67, 0x39, 0x9e, 0xa1, 0x45, 0x8c, 0x9d, 0xdc, 0xb8, 0x31, 0x4b, 0x7a, 0xbb,
		0x4c, 0x6e, 0x97, 0xa5, 0x97, 0x98, 0x4d, 0x67, 0x76, 0xa3, 0x0f, 0xf5, 0xbc, 0x87, 0xfe, 0xd6,
	}, {
		0x69, 0xbd, 0x57, 0x58, 0x0e, 0xaf, 0x01, 0xf8, 0xce, 0x84, 0x5d, 0x02, 0x3f, 0x07, 0x0a, 0x36,
		0x16, 0x34, 0x75, 0x09, 0x84, 0x7f, 0x99, 0x48, 0xbb, 0x1a, 0x04, 0xed, 0x6c, 0x70, 0x63, 0xc7,
	}, {
		0x2d, 0x44, 0xa9, 0x0b, 0x60, 0xf6, 0x96, 0xe8, 0xfa, 0x4b, 0xb2, 0x54, 0x32, 0xe2, 0x2d, 0xeb,
		0xa1, 0xd9, 0x77, 0x5c, 0xff, 0x56, 0x06, 0xdb, 0xa2, 0x54, 0x5d, 0x17, 0xe2, 0xd4, 0xbf, 0x9a,
	}, {
		0xe4, 0x73, 0x27, 0x8f, 0x03, 0x77, 0x60, 0xdf, 0x87, 0x20, 0xf9, 0xab, 0xca, 0x62, 0xbf, 0x38,
		0x1c, 0xc3, 0x23, 0x2a, 0xc6, 0x8e, 0xce, 0x3e, 0xb3, 0xa8, 0x01, 0xa0, 0x7c, 0xe5, 0xaf, 0x64,
	}, {
		0x7c, 0xe1, 0x25, 0xd1, 0x98, 0x4a, 0x19, 0xd6, 0x52, 0x2d, 0x4a, 0xfc, 0xa5, 0xeb, 0x6a, 0x48,
		0xa8, 0x98, 0xfa, 0xd5, 0xb4, 0xfd, 0x94, 0x36, 0xa3, 0x2f, 0xbc, 0x9e, 0x16, 0x07, 0xe0, 0x8c,
	}, {
		0x71, 0xbb, 0x40, 0x71, 0xbc, 0x78, 0x9e, 0x2c, 0x48, 0xb7, 0x26, 0xb5, 0x46, 0xa5, 0x29, 0xcb,
		0x6a, 0x18, 0x51, 0xa7, 0x68, 0x6c, 0x36, 0x12, 0xad, 0xe3, 0xf7, 0xc0, 0x16, 0x0d, 0x68, 0x84,
	}, {
		0xca, 0x9e, 0x93, 0x28, 0xdb, 0x05, 0xbd, 0x14, 0xa7, 0x64, 0xdb, 0x5a, 0x78, 0x09, 0x09, 0xc2,
		0x13, 0x0a, 0x1c, 0xae, 0x86, 0xc5, 0xdb, 0xfb, 0x36, 0xa9, 0xe4, 0x4a, 0x88, 0x93, 0x54, 0x3c,
	}, {
		0x28, 0xf3, 0xe6, 0x95, 0x26, 0x76, 0x56, 0xad, 0x99, 0xe0, 0x90, 0x6c, 0x46, 0xd1, 0x7e, 0x98,
		0xee, 0x3f, 0xb0, 0x02, 0xe1, 0x7a, 0xcd, 0x39, 0x43, 0xc7, 0x0d, 0x1d, 0xf9, 0x70, 0x52, 0xab,
	}, {
		0x10, 0xc8, 0xe2, 0x52, 0x25, 0xfb, 0xea, 0xc3, 0x94, 0xd2, 0x86, 0xaf, 0xc7, 0x9e, 0xc1, 0x7f,
		0x40, 0x06, 0x5f, 0x74, 0x85, 0xaa, 0x61, 0xf0, 0x7c, 0xed, 0x06, 0x3c, 0x7f, 0xe9, 0x17, 0x7d,
	}, {
		0xa7, 0x6a, 0x9d, 0x0f, 0xd7, 0xc9, 0xd3, 0x55, 0xdb, 0x14, 0x72, 0xa3, 0xdb, 0xde, 0xc7, 0xb6,
		0x67, 0x90, 0xef, 0x8c, 0x0b, 0x0e, 0x7b, 0x17, 0x2d, 0xf8, 0xf6, 0x08, 0x43, 0xc1, 0x3b, 0xf4,
	}
};

static const lsh_u8 g_lsh512_tv_answer[LSH256_TEST_CNT][LSH512_HASH_VAL_MAX_BYTE_LEN] = {
	{
		0x11, 0x8a, 0x2f, 0xf2, 0xa9, 0x9e, 0x3b, 0x21, 0x34, 0x12, 0x5e, 0x2b, 0xaf, 0x20, 0xeb, 0xe3,
		0xbd, 0xd0, 0x34, 0xd5, 0xa6, 0x9b, 0x29, 0xc2, 0x2f, 0xc4, 0x99, 0x50, 0x63, 0x34, 0x0b, 0x46,
		0x69, 0x78, 0x01, 0xd7, 0xf7, 0xfb, 0x00, 0x70, 0x56, 0x8f, 0x78, 0xe8, 0xed, 0x51, 0x42, 0x15,
		0xfc, 0x70, 0xaf, 0x27, 0xd6, 0xf2, 0x7b, 0x01, 0xaa, 0x8a, 0x1d, 0xa7, 0x2b, 0x14, 0xce, 0x7c,
	}, {
		0x1e, 0xd1, 0x93, 0x0d, 0x5e, 0xbb, 0xd5, 0x81, 0xe2, 0xe5, 0xe8, 0x13, 0x77, 0x62, 0x04, 0xab,
		0xcd, 0xf3, 0x1a, 0x32, 0xec, 0x2b, 0xd8, 0x3d, 0x63, 0x5a, 0x2d, 0x9b, 0x86, 0xa6, 0x81, 0xbf,
		0x23, 0xec, 0x76, 0x69, 0x62, 0x05, 0xab, 0x89, 0xeb, 0xa5, 0xab, 0x27, 0x36, 0x81, 0x52, 0x2d,
		0xb3, 0xaf, 0xea, 0x71, 0x77, 0x6c, 0xa0, 0xd8, 0x8e, 0x26, 0x9c, 0xcb, 0x03, 0x57, 0x67, 0x90,
	}, {
		0x65, 0xd7, 0x4e, 0x79, 0x05, 0xcb, 0xed, 0x1b, 0x1f, 0xcd, 0xaf, 0xae, 0xcb, 0x16, 0x44, 0xc6,
		0x43, 0x34, 0x45, 0xea, 0x9a, 0x75, 0x75, 0xa4, 0x4e, 0x42, 0xa9, 0x52, 0x0d, 0x94, 0x15, 0xed,
		0xa3, 0x05, 0x87, 0x1a, 0xad, 0x64, 0x51, 0x0a, 0x67, 0x34, 0x90, 0x47, 0x06, 0x95, 0x13, 0xc9,
		0x96, 0x95, 0x42, 0x47, 0x53, 0xdd, 0xd8, 0x8a, 0xff, 0xdb, 0x10, 0x8a, 0x79, 0x5f, 0x72, 0x82,
	}, {
		0x43, 0xeb, 0xf6, 0xcf, 0xb5, 0xaf, 0xe5, 0xe6, 0xd4, 0xbb, 0x19, 0x00, 0xa4, 0xae, 0xb9, 0x91,
		0x80, 0xe4, 0x8c, 0x94, 0x43, 0x88, 0xd9, 0xb8, 0xb8, 0x2e, 0xd1, 0x1e, 0x3f, 0xf2, 0x8b, 0x7a,
		0x89, 0x0a, 0xe5, 0x14, 0x8c, 0x88, 0xcc, 0x60, 0x94, 0x82, 0xa5, 0x62, 0x83, 0x4f, 0x0e, 0xd4,
		0xde, 0x91, 0x68, 0xf2, 0x1c, 0x86, 0x79, 0x3d, 0xa9, 0x37, 0x37, 0xea, 0x73, 0x04, 0xba, 0x8f,
	}, {
		0x48, 0xd2, 0xda, 0xa6, 0x96, 0x72, 0x86, 0x8d, 0x4a, 0x0d, 0x68, 0x2a, 0xb7, 0x4d, 0x3e, 0x78,
		0xdb, 0x79, 0x31, 0x39, 0x28, 0x3a, 0xca, 0x40, 0x84, 0x60, 0xfa, 0xc3, 0xaa, 0xe5, 0xd9, 0x58,
		0x02, 0x6d, 0x24, 0xae, 0xa8, 0x41, 0xf8, 0x30, 0x2a, 0x89, 0xff, 0xca, 0xd0, 0x4a, 0x03, 0x12,
		0xfe, 0xb3, 0x7e, 0x0c, 0x73, 0x4e, 0x7c, 0xbc, 0xe6, 0xb3, 0x61, 0x22, 0x02, 0x85, 0x16, 0x98,
	}, {
		0x65, 0xa5, 0x32, 0x6f, 0x88, 0x9a, 0x1d, 0x3f, 0xd0, 0x8c, 0x22, 0x3f, 0x48, 0xdb, 0x1a, 0x0f,
		0x3d, 0x66, 0x68, 0x99, 0xe0, 0xb5, 0x01, 0x43, 0xdc, 0xb7, 0x78, 0x71, 0x93, 0x70, 0x24, 0x53,
		0x72, 0x3b, 0x3c, 0xa8, 0xd2, 0x67, 0xcb, 0xfb, 0xe3, 0xa3, 0x29, 0x11, 0xef, 0x6a, 0x29, 0xed,
		0x20, 0xe5, 0x3c, 0x3e, 0x18, 0xfa, 0x9c, 0x32, 0x32, 0xe5, 0x71, 0xb4, 0xc9, 0x41, 0x53, 0xaa,
	}, {
		0x1e, 0x17, 0x58, 0x74, 0x16, 0x43, 0xa7, 0xb0, 0x96, 0x98, 0x6f, 0xa7, 0xec, 0x1b, 0x7a, 0x04,
		0xe1, 0x39, 0x7f, 0x86, 0xd9, 0x1d, 0x3b, 0xd9, 0x2f, 0x25, 0x3c, 0x87, 0x5e, 0xda, 0xc7, 0x59,
		0xc5, 0xe7, 0xbb, 0x63, 0x28, 0x8f, 0x7f, 0x5e, 0xb2, 0xa0, 0x99, 0x37, 0x60, 0x05, 0x66, 0x72,
		0x63, 0x39, 0x31, 0xfa, 0x0e, 0x04, 0x2d, 0xc1, 0xbf, 0x1e, 0x14, 0x45, 0xf9, 0xfb, 0x37, 0xcd,
	}, {
		0x89, 0x66, 0x48, 0x50, 0xdb, 0x35, 0x80, 0xf1, 0xe7, 0xf1, 0x13, 0x9f, 0xc8, 0xf1, 0x49, 0x49,
		0xf9, 0x60, 0xa9, 0xb6, 0x6a, 0x6e, 0xba, 0x58, 0x85, 0xee, 0xf5, 0x59, 0xe7, 0x0d, 0x6d, 0x89,
		0x7c, 0x91, 0x9f, 0x5a, 0x41, 0xef, 0x5c, 0x6a, 0xec, 0x50, 0x23, 0x4f, 0xff, 0x56, 0xb4, 0xb4,
		0xf3, 0x38, 0x8e, 0x85, 0x75, 0x62, 0xdb, 0xef, 0x3a, 0x0b, 0x10, 0xbd, 0x7e, 0x22, 0x8f, 0xec,
	}, {
		0x9c, 0x2b, 0xb4, 0xe6, 0xb4, 0x5b, 0xa3, 0x35, 0x0e, 0x3a, 0x22, 0x91, 0x05, 0x14, 0xcd, 0xfe,
		0xff, 0xa8, 0x21, 0xe1, 0x6f, 0xb3, 0x9d, 0x29, 0xd9, 0x23, 0xc9, 0xe5, 0xfd, 0x98, 0x04, 0x5f,
		0x4a, 0x9d, 0xfe, 0x83, 0xec, 0x18, 0x04, 0x8b, 0xde, 0xc1, 0xcd, 0x7f, 0x79, 0x31, 0x93, 0x99,
		0xe1, 0x95, 0xb8, 0x5e, 0xd2, 0x17, 0xf2, 0x5e, 0x21, 0xa2, 0x5c, 0x73, 0x77, 0xf3, 0x4c, 0xa0,
	}, {
		0xc2, 0x8f, 0x31, 0xe7, 0xdc, 0x19, 0x47, 0xaa, 0xea, 0x0d, 0xb7, 0x26, 0xea, 0xa0, 0x8f, 0x4a,
		0xb2, 0x77, 0xa0, 0x03, 0x35, 0xc3, 0xe5, 0x33, 0xd8, 0xf0, 0x33, 0xf6, 0x2e, 0x30, 0x20, 0x9d,
		0x7d, 0x17, 0x39, 0x3a, 0xda, 0xed, 0xb2, 0x82, 0x22, 0xc8, 0x6a, 0x1d, 0xe8, 0xb3, 0xfa, 0xab,
		0x48, 0x16, 0x70, 0x79, 0xf8, 0x51, 0xb9, 0x30, 0xc1, 0x5d, 0xc6, 0xff, 0x30, 0xbb, 0x65, 0x58,
	}, {
		0xf4, 0x42, 0x6a, 0xe3, 0xe2, 0xff, 0xe4, 0x8d, 0x8d, 0xae, 0x3a, 0xaa, 0x17, 0x45, 0xc4, 0x24,
		0x83, 0x2a, 0xec, 0x0c, 0x1e, 0x9c, 0x7b, 0xd6, 0xf8, 0x75, 0xa7, 0xcd, 0x78, 0x6d, 0x4b, 0xcf,
		0xa3, 0x74, 0xbd, 0xeb, 0x28, 0x85, 0x05, 0x3e, 0xde, 0x76, 0x19, 0x13, 0xe5, 0x70, 0xa1, 0x30,
		0x6c, 0xe9, 0x9b, 0xe4, 0xbe, 0x29, 0xf5, 0xe4, 0x4c, 0xdc, 0x49, 0xdb, 0x29, 0x08, 0xcc, 0x8d,
	}, {
		0xe2, 0xa4, 0xc9, 0x26, 0xf2, 0x59, 0x27, 0x2c, 0x8c, 0x94, 0x82, 0xcb, 0x57, 0x8b, 0xac, 0xbd,
		0x59, 0xcc, 0xee, 0x78, 0x82, 0x27, 0x9e, 0xe7, 0x4d, 0x83, 0x8c, 0x2f, 0x68, 0xa7, 0xfd, 0xd5,
		0x47, 0x89, 0x6f, 0x99, 0x3a, 0x52, 0x28, 0x3d, 0xa9, 0x37, 0x59, 0x97, 0xc6, 0x3e, 0xa9, 0xe4,
		0x55, 0x8f, 0x9e, 0xfc, 0x0e, 0x86, 0xd0, 0xd6, 0x5f, 0xd4, 0xe3, 0x46, 0xfe, 0x3d, 0x02, 0xbf,
	}, {
		0x31, 0x57, 0x6f, 0x84, 0x86, 0x0f, 0x85, 0x60, 0x03, 0x5b, 0xce, 0xe6, 0xf8, 0xd5, 0x87, 0xe3,
		0xab, 0xe8, 0x1f, 0x67, 0xdf, 0x11, 0x84, 0xb7, 0x58, 0x0d, 0xaa, 0xb2, 0xf2, 0xee, 0x54, 0xf2,
		0x52, 0x1f, 0x0d, 0x5a, 0x7d, 0xef, 0xde, 0x1c, 0x08, 0x25, 0x4d, 0xc7, 0x4e, 0x6d, 0x99, 0x99,
		0x8a, 0xd2, 0x33, 0x74, 0xbc, 0x91, 0x1d, 0xa6, 0xa9, 0x7b, 0x56, 0x18, 0x56, 0x94, 0x8c, 0x21,
	}, {
		0x67, 0xfd, 0x33, 0xa2, 0x7a, 0x7f, 0x9d, 0x19, 0xe5, 0xc1, 0x0b, 0x62, 0x70, 0x8e, 0xbf, 0x11,
		0xb7, 0x09, 0xaa, 0x85, 0xa8, 0x4c, 0xdc, 0xea, 0x2a, 0xdb, 0xd6, 0x4d, 0xa6, 0xb1, 0x15, 0xcb,
		0xc1, 0x84, 0x21, 0xd7, 0x94, 0x3f, 0x60, 0x2d, 0xb1, 0xdf, 0x23, 0xea, 0xba, 0xf9, 0x6a, 0xe8,
		0x8f, 0xa5, 0x73, 0xdd, 0xa0, 0x42, 0x1a, 0x61, 0xd5, 0xa2, 0x73, 0x84, 0x2a, 0x3f, 0xd9, 0x16,
	}, {
		0x42, 0x5d, 0xcd, 0xc2, 0xb7, 0xdd, 0x92, 0xbe, 0x41, 0x05, 0xd7, 0x5f, 0xce, 0x7c, 0x22, 0xae,
		0x42, 0x68, 0xd6, 0x0b, 0xb7, 0xcc, 0xcd, 0x28, 0x1b, 0x2c, 0x2e, 0x34, 0x98, 0x48, 0x73, 0x98,
		0xb5, 0x3c, 0xae, 0x23, 0xc8, 0xf8, 0xaa, 0xf7, 0x2e, 0x69, 0xf4, 0x90, 0xea, 0x02, 0x23, 0xd3,
		0xd2, 0x9d, 0xba, 0x01, 0x1f, 0x8a, 0x32, 0xe3, 0x85, 0x39, 0xa7, 0x61, 0xc8, 0x12, 0x8f, 0x11,
	}, {
		0x8d, 0x8a, 0x71, 0x6d, 0x87, 0xbf, 0xd9, 0xaf, 0x51, 0xeb, 0xeb, 0x57, 0xfd, 0xdb, 0x9e, 0xa6,
		0xeb, 0x22, 0x78, 0xae, 0x3d, 0x66, 0xf8, 0x61, 0x74, 0xdf, 0x77, 0x88, 0x63, 0xf0, 0xef, 0x1c,
		0xb3, 0x27, 0xe2, 0xfa, 0x1e, 0x6e, 0x95, 0x9b, 0x40, 0xda, 0x22, 0xfa, 0xa7, 0x6c, 0xfe, 0x76,
		0xdf, 0x18, 0xf3, 0x99, 0x71, 0xf3, 0x8c, 0xf6, 0x75, 0xb1, 0x3c, 0x4c, 0xdb, 0x96, 0x71, 0xbb,
	}
};

void print_hex_string(const char* title, const lsh_u8* data, const size_t len) {
	int j;
	printf("%s: ", title);
	for (j = 0; j < len; j++){
		printf("%02x", data[j]);

		if (j % 4 == 3) {
			printf(" ");
		}
	}
	printf("\n");
}

int lsh256_testvector_simd(PtrLSHInit256 p_lsh256_init, PtrLSHUpdate256 p_lsh256_update, PtrLSHFinal256 p_lsh256_final){
	struct LSH256_Context ctx;
	lsh_u8 hashval[LSH256_HASH_VAL_MAX_BYTE_LEN];
	int i;
	
	/* LSH256-256 */

	for (i = 0; i < LSH256_TEST_CNT; i++){
		p_lsh256_init(&ctx, LSH_TYPE_256);
		p_lsh256_update(&ctx, g_lsh_testvector_data, g_lsh256_testvector_step[i]);
		p_lsh256_final(&ctx, hashval);

		if (memcmp(hashval, g_lsh256_tv_answer[i], LSH256_HASH_VAL_MAX_BYTE_LEN) != 0){
			printf("Failed : LSH256, Test %d\n", i);
			print_hex_string("VS ", g_lsh256_tv_answer[i], LSH256_HASH_VAL_MAX_BYTE_LEN);
			print_hex_string("ANS", hashval, LSH256_HASH_VAL_MAX_BYTE_LEN);
			printf("\n");
			return 0x100 | i;
		}
	}

	return 0;
}

int lsh512_testvector_simd(PtrLSHInit512 p_lsh512_init, PtrLSHUpdate512 p_lsh512_update, PtrLSHFinal512 p_lsh512_final){
	struct LSH512_Context ctx;
	LSH_ALIGNED_(32) lsh_u8 hashval[LSH512_HASH_VAL_MAX_BYTE_LEN];
	int i, j;

	/* LSH512-512 */

	for (i = 0; i < LSH512_TEST_CNT; i++){
		p_lsh512_init(&ctx, LSH_TYPE_512);
		p_lsh512_update(&ctx, g_lsh_testvector_data, g_lsh512_testvector_step[i]);
		p_lsh512_final(&ctx, hashval);

		if (memcmp(hashval, g_lsh512_tv_answer[i], LSH512_HASH_VAL_MAX_BYTE_LEN) != 0){
			printf("TEST FAILED : LSH512, Test %d\n", i);
			print_hex_string("VS ", g_lsh512_tv_answer[i], LSH512_HASH_VAL_MAX_BYTE_LEN);
			print_hex_string("ANS", hashval, LSH512_HASH_VAL_MAX_BYTE_LEN);
			printf("\n");
			return 0x200 | i;
		}
	}

	return 0;
}

int lsh256_crosscheck_simd(PtrLSHInit256 p_lsh256_init, PtrLSHUpdate256 p_lsh256_update, PtrLSHFinal256 p_lsh256_final){
	struct LSH256_Context ctx;
	lsh_u8 hashval[LSH256_HASH_VAL_MAX_BYTE_LEN];
	lsh_u8 hashval_cross[LSH256_HASH_VAL_MAX_BYTE_LEN];
	lsh_uint i, j, k;
	lsh_type t_type;


	for (i = 1; i <= 256; i++){
		t_type = LSH_MAKE_TYPE(0, i);
		for (j = 0; j <= 3073; j++){
			p_lsh256_init(&ctx, t_type);
			p_lsh256_update(&ctx, g_lsh_testvector_data, j);
			p_lsh256_final(&ctx, hashval);

			lsh256_digest(t_type, g_lsh_testvector_data, j, hashval_cross);

			if (memcmp(hashval, hashval_cross, LSH_GET_HASHBYTE(t_type)) != 0){
				printf("Failed : LSH256-CrossCheck, Test %d-%d\n", i, j);
				print_hex_string("NEON", hashval, LSH_GET_HASHBYTE(t_type));
				print_hex_string("REF ", hashval_cross, LSH_GET_HASHBYTE(t_type));
				return 0x10000000 | (i << 16) | j;
			}
		}
	}

	return 0;
}

int lsh512_crosscheck_simd(PtrLSHInit512 p_lsh512_init, PtrLSHUpdate512 p_lsh512_update, PtrLSHFinal512 p_lsh512_final){
	struct LSH512_Context ctx;
	LSH_ALIGNED_(32) lsh_u8 hashval[LSH512_HASH_VAL_MAX_BYTE_LEN];
	LSH_ALIGNED_(32) lsh_u8 hashval_cross[LSH512_HASH_VAL_MAX_BYTE_LEN];
	lsh_uint i, j, k;
	lsh_type t_type;


	for (i = 1; i <= 512; i++){
		t_type = LSH_MAKE_TYPE(1, i);
		for (j = 0; j <= 6145; j++){
			p_lsh512_init(&ctx, t_type);
			p_lsh512_update(&ctx, g_lsh_testvector_data, j);
			p_lsh512_final(&ctx, hashval);

			lsh512_digest(t_type, g_lsh_testvector_data, j, hashval_cross);

			if (memcmp(hashval, hashval_cross, LSH_GET_HASHBYTE(t_type)) != 0){
				printf("Failed : LSH512-CrossCheck, Test %d-%d\n", i, j);
				print_hex_string("NEON", hashval, LSH_GET_HASHBYTE(t_type));
				print_hex_string("REF ", hashval_cross, LSH_GET_HASHBYTE(t_type));
				return 0x20000000 | (i << 16) | j;
			}
		}
	}

	return 0;
}

int lsh_testvector_simd(){
	int i;
	int result;
	
	for (i = 0; i < 1024; i++){
		g_lsh_testvector_data[i] = (lsh_u8)i;
	}
	
	printf("TEST LSH_REF\n");

	result = lsh256_testvector_simd(lsh256_init, lsh256_update, lsh256_final);
	if (result)return result;

	result = lsh512_testvector_simd(lsh512_init, lsh512_update, lsh512_final);
	if (result)return result;

	if (has_neon_feature()){
		printf("TEST LSH256_NEON\n");
		result = lsh256_testvector_simd(lsh256_neon_init, lsh256_neon_update, lsh256_neon_final);
		if (result)return result;

		printf("TEST LSH512_NEON\n");
		result = lsh512_testvector_simd(lsh512_neon_init, lsh512_neon_update, lsh512_neon_final);
		if (result) return result;
		
		printf("CrossCheck LSH256_NEON\n");
		result = lsh256_crosscheck_simd(lsh256_neon_init, lsh256_neon_update, lsh256_neon_final);
		if (result)return result;

		printf("CrossCheck LSH512_NEON\n");
		result = lsh512_crosscheck_simd(lsh512_neon_init, lsh512_neon_update, lsh512_neon_final);
		if (result)return result;
	}

	printf("TEST PASSED\n");
	return 0;
}

void fout_hex(FILE* fp, const lsh_u8* data, const size_t datalen){
	size_t i;

	if (fp == NULL || data == NULL){
		return;
	}

	for (i = 0; i < datalen; i++){
		fprintf(fp, "%02x", (lsh_u8)data[i]);
	}
}

int hmac_lsh_test_type2(const char* path_prefix){
	FILE* fp;
	lsh_uint i;
	lsh_uint hashbit, keylen_idx, msglen;
	lsh_uint tmp;
	lsh_type t_type;

	int hmac256_keylen[] = { 0, 1, 8, 32, 64, 128, 256 };
	int hmac512_keylen[] = { 0, 1, 8, 32, 64, 128, 256, 384 };
	LSH_ALIGNED_(32) lsh_u8 hmac_result[LSH512_HASH_VAL_MAX_BYTE_LEN];
	char outpath[256];

	if (path_prefix == NULL || strlen(path_prefix) > 200){
		return 1;
	}

	/* hmac key = {2k} + {2*(k-128)+1} + {2(k-256)} */
	g_hmac_key_data[0] = 0;
	for (i = 1; i < 384; i++){
		tmp = g_hmac_key_data[i - 1] + 2;
		if (tmp >= 0x100){
			tmp ^= 0x101;
		}
		g_hmac_key_data[i] = tmp;
	}

	for (i = 0; i < 1024; i++){
		g_lsh_test_data[i] = (lsh_u8)i;
	}

	/* LSH256 */
	for (hashbit = 1; hashbit <= 256; hashbit++){
		t_type = LSH_MAKE_TYPE(0, hashbit);
		for (keylen_idx = 0; keylen_idx < sizeof(hmac256_keylen) / sizeof(int); keylen_idx++){
			sprintf(outpath, "%s%03d_%03d_%03d.txt", path_prefix, 256, hashbit, hmac256_keylen[keylen_idx]);
			fp = fopen(outpath, "wt");
			if (fp == NULL){
				continue;
			}

			for (msglen = 0; msglen < sizeof(g_lsh_test_data); msglen++){
				hmac_lsh_digest(t_type, g_hmac_key_data, hmac256_keylen[keylen_idx], g_lsh_test_data, msglen, hmac_result);
				fprintf(fp, "%d\n", msglen);
				fout_hex(fp, hmac_result, LSH_GET_HASHBYTE(t_type));
				fprintf(fp, "\n");
			}
			fclose(fp);
		}
	}

	/* LSH512 */
	for (hashbit = 1; hashbit <= 512; hashbit++){
		t_type = LSH_MAKE_TYPE(1, hashbit);
		for (keylen_idx = 0; keylen_idx < sizeof(hmac512_keylen) / sizeof(int); keylen_idx++){
			sprintf(outpath, "%s%03d_%03d_%03d.txt", path_prefix, 512, hashbit, hmac512_keylen[keylen_idx]);
			fp = fopen(outpath, "wt");
			if (fp == NULL){
				continue;
			}

			for (msglen = 0; msglen < sizeof(g_lsh_test_data); msglen++){
				hmac_lsh_digest(t_type, g_hmac_key_data, hmac512_keylen[keylen_idx], g_lsh_test_data, msglen, hmac_result);
				fprintf(fp, "%d\n", msglen);
				fout_hex(fp, hmac_result, LSH_GET_HASHBYTE(t_type));
				fprintf(fp, "\n");
			}
			fclose(fp);
		}
	}

	return 0;
}

int main() {
	lsh_testvector_simd();
	//hmac_lsh_test_type2("hmac_lsh_test_");
	return 0;
}