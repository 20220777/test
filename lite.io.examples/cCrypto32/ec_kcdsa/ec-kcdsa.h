#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdint.h>
#include "ecc.h"
#include "mpz.h"
#include "sysconf.h"
#include "ec_gf2n.h"
#include "ec_gfp.h"

#define Binary 1
#define Prime 0
#define SHA224 1
#define SHA256 2

#ifdef  __cplusplus
extern "C" {}
#endif
	void Private_Key_generator(MPZ *Private_key, ECC_PARAMS SELECTED_CURVE, const ECC_ID ecc_id, const int32_t HASH_FUNCTION, uint8_t *URAND_VAL, const int32_t URAND_len);

	void Public_Key_generator_gfp(ECC_POINT *Public_point, uint32_t *Private_key, ECC_PARAMS SELECTED_CURVE);

	void Public_Key_generator_gf2n(ECC_POINT *Public_point, uint32_t *Private_key, ECC_PARAMS SELECTED_CURVE);

	void eckcdsa_gfp(const ECC_POINT Private, const ECC_PARAMS SELECTED_CURVE, uint32_t *secret, const uint32_t ECC_ID,
		const uint32_t HASH_FUNCTION, uint8_t Message[], const int32_t MSG_len, uint8_t signature[]);

	void eckcdsa_gf2n(const ECC_POINT Private, const ECC_PARAMS SELECTED_CURVE, uint32_t *secret, const uint32_t ECC_ID,
		const uint32_t HASH_FUNCTION, uint8_t Message[], const int32_t MSG_len, uint8_t signature[]);

	int32_t	eckcdsa_gfp_verify(const ECC_POINT Private, uint8_t signature[], const ECC_PARAMS SELECTED_CURVE,
		const uint32_t ECC_ID, const uint32_t HASH_FUNCTION, uint8_t Message[], const int32_t MSG_len);

	int32_t	eckcdsa_gf2n_verify(const ECC_POINT Private, uint8_t signature[], const ECC_PARAMS SELECTED_CURVE,
		const uint32_t ECC_ID, const uint32_t HASH_FUNCTION, uint8_t Message[], const int32_t MSG_len);

	void Public_Key_generator(ECC_POINT *Public_point, uint32_t *Private_key, ECC_PARAMS SELECTED_CURVE);

	void EC_KCDSA_sign(const ECC_POINT Public_point, const ECC_PARAMS SELECTED_CURVE, uint32_t *secret, const uint32_t ECC_ID,
		const uint32_t HASH_FUNCTION, uint8_t Message[], const int32_t MSG_len, uint8_t signature[]);

	int32_t EC_KCDSA_verify(const ECC_POINT Public_point, uint8_t signature[], const ECC_PARAMS SELECTED_CURVE,
		const uint32_t ECC_ID, const uint32_t HASH_FUNCTION, uint8_t Message[], const int32_t MSG_len);

	void Public_Key_set_params(ECC_POINT *Public_point, const ECC_PARAMS SELECTED_CURVE, const uint32_t *x_Q, int32_t x_Q_len, const uint32_t *y_Q, int32_t y_Q_len);

	void Word_to_Byte(uint32_t *W, uint8_t *C, int32_t W_length, int32_t int8_t_length);
	void Point_to_Byte(uint32_t *W, uint8_t *C, int32_t W_length, const int32_t Temp_int8_t_length);
	void Byte_to_Prime_Field(uint8_t *C, uint32_t *Field, int32_t Byte_length, int32_t Field_length);

#ifdef  __cplusplus
}
#endif
