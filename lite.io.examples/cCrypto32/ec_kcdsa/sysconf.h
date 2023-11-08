#ifndef _SYSCONF_H_
#define _SYSCONF_H_

#ifdef  __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define _BIT32_PROCESSOR_ 

#define _MATHEMATICA_EXPRESS_
#define ULONG_PTR uint32_t*
	/* system independent types */
	typedef uint32_t ULONG;

	typedef int32_t SLONG;
	typedef SLONG* SLONG_PTR;

	typedef uint16_t USHORT;
	typedef USHORT* USHORT_PTR;

	typedef int16_t SSHORT;
	typedef SSHORT* SSHORT_PTR;

	typedef uint32_t UINT;
	typedef uint32_t* UINT_PTR;

	typedef int32_t SINT;
	typedef SINT* SINT_PTR;

	typedef uint8_t Uint8_t;
	typedef Uint8_t* Uint8_t_PTR;

	typedef int8_t Sint8_t;
	typedef Sint8_t* Sint8_t_PTR;

	//typedef uint8_t BOOL;
#define TRUE	1
#define FALSE	0

/* system dependent types */

	typedef uint8_t  UINT8;
	typedef uint16_t UINT16;
	typedef uint32_t   UINT32;


	typedef struct _OSTR {
		Uint8_t	*val;
		UINT	len;
	}OSTR;


#if defined(_BIT32_PROCESSOR_)

#define BITMASK_LONG        0xffffffff
#define BITMASK_HIGHER_LONG 0xffff0000 
#define BITMASK_LOWER_LONG  0x0000ffff
#define HIGHER_MSB_ONE		0x80000000
#define LOWER_MSB_ONE		0x00008000
#define HIGHER_LSB_ONE		0x00010000
#define LOWER_LSB_ONE		0x00000001
#define LOW_DEG_FIND        0x0000001f
#define LONG_BITS			32
#define HALF_LONG_BITS		16

#elif defined(_BIT64_PROCESSOR_)

#define BITMASK_LONG        0xffffffffffffffff
#define BITMASK_HIGHER_LONG 0xffffffff00000000 
#define BITMASK_LOWER_LONG  0x00000000ffffffff
#define HIGHER_MSB_ONE		0x8000000000000000
#define LOWER_MSB_ONE		0x0000000080000000
#define HIGHER_LSB_ONE		0x0000000100000000
#define LOWER_LSB_ONE		0x0000000000000001
#define LONG_BITS			64
#define HALF_LONG_BITS		32

#endif

#define MAX_MPZ_BUF_LEN (300 + 1)
#define MAX_GFP_BUF_LEN (500 + 1)
#define MAX_GF2N_BUF_LEN (500 + 1)
#define MAX_HASH_BUF_BYTES (20 + 1)

#ifdef  __cplusplus
}
#endif

#endif _SYSCONF_H_
