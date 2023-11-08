
#include "KISA_KBKDF.h" 

// L을 넣는 것 확인 필요

int32_t addLparam(uint8_t* in, uint32_t L)
{
	int32_t ret = 0;

	if (L < 0x100)
	{
		ret = 1;
		in[0] = (L) & 0xff;
	}
	else if (L > 0xff && L < 0x10000)
	{
		ret = 2;
		in[0] = (L >> 8) & 0xff;
		in[1] = (L) & 0xff;
	}
	else if (L > 0xffff && L < 0X1000000)
	{
		ret = 3;
		in[0] = (L >> 16) & 0xff;
		in[1] = (L >> 8) & 0xff;
		in[2] = (L) & 0xff;
	}
	else
	{
		ret = 4;
		in[0] = (L >> 24) & 0xff;
		in[1] = (L >> 16) & 0xff;
		in[2] = (L >> 8) & 0xff;
		in[3] = (L) & 0xff;
	}
	return ret;
}

void kbkdf_hmac_ctr_mode(
	uint8_t* KI, uint32_t KILen,
	uint32_t r, uint32_t L,
	uint8_t* Label, uint32_t LabelLen, uint8_t* Context, uint32_t ContextLen,
	uint8_t* KO)
{
	int32_t n = 0, h = 0, i = 0;
	int32_t inputLen = 0, macLen = 0, Llen = 0, r_pos = 0;
	uint8_t* input, *K;
	uint8_t byte_ctr[4] = { 0, };
	uint32_t ctr = 0;

	macLen = KISA_SHA256_DIGEST_VALUELEN;

	h = macLen * 8;
	n = ceiling(L, h);

	r_pos = r / 8;

	input = (uint8_t*)calloc(r_pos + LabelLen + 1 + ContextLen + 4, sizeof(uint8_t));
	
	memcpy(input + r_pos, Label, sizeof(uint8_t) * LabelLen);
	memcpy(input + r_pos + LabelLen + 1, Context, sizeof(uint8_t) * ContextLen);
	Llen = addLparam(input + r_pos + LabelLen + 1 + ContextLen, L);

	K = (uint8_t*)calloc(macLen * n, sizeof(uint8_t));

	inputLen = r_pos + LabelLen + 1 + ContextLen + Llen;

	for (i = 0; i < n; i++)
	{
		ctr++;
		word2byte(byte_ctr, ctr, r_pos);
		memcpy(input, byte_ctr, sizeof(uint8_t)*r_pos);

		HMAC_SHA256(input, inputLen, KI, KILen, K + (i * macLen));
	}

	memcpy(KO, K, sizeof(uint8_t) * (L / 8));

	free(input);
	free(K);

}

void kbkdf_hmac_feedback_mode(
	uint8_t* KI, uint32_t KILen,
	uint32_t r, uint32_t L,
	uint8_t* Label, uint32_t LabelLen,
	uint8_t* Context, uint32_t ContextLen,
	uint8_t* IV, uint32_t IVLen,
	uint8_t* KO)
{
	int32_t n = 0, h = 0, i = 0;
	int32_t inputLen = 0, macLen = 0, Llen = 0, fixed_inputLen = 0, r_pos = 0;
	uint8_t* fixed_input, *input, *K;
	uint8_t byte_ctr[4] = { 0, };
	uint32_t ctr = 0;

	macLen = KISA_SHA256_DIGEST_VALUELEN;

	// Note that when L<=h, IV=0, and the counter is used, the feedback mode will generate an ouput that is identical to the ouput of the counter mode)

	// 고정 입력값 설정
	// 고정 입력값 = Label || 0x00 || Context || L
	fixed_input = (uint8_t*)calloc(LabelLen + 1 + ContextLen + 4, sizeof(uint8_t));
	memcpy(fixed_input, Label, sizeof(uint8_t) * LabelLen);
	memcpy(fixed_input + LabelLen + 1, Context, sizeof(uint8_t) * ContextLen);
	Llen = addLparam(fixed_input + LabelLen + 1 + ContextLen, L);
	fixed_inputLen = LabelLen + 1 + ContextLen + Llen;

	r_pos = r / 8;

	if(macLen > IVLen)
		input = (uint8_t*)calloc(macLen + r_pos + LabelLen + 1 + ContextLen + 4, sizeof(uint8_t));
	else
		input = (uint8_t*)calloc(IVLen + r_pos + LabelLen + 1 + ContextLen + 4, sizeof(uint8_t));
	
	h = macLen * 8;
	n = ceiling(L, h);

	K = (uint8_t*)calloc(IVLen + macLen * n, sizeof(uint8_t));

	// K(0) = IV
	if (IVLen != 0)
	{
		memcpy(K, IV, sizeof(uint8_t) * IVLen);
	}

	for (i = 0; i < n; i++)
	{
		// 입력값 설정
		if (i == 0)
		{
			// input = K(0) || count || 고정 입력값 (i == 0)
			if (IVLen != 0)
			{
				memcpy(input, K, sizeof(uint8_t) * IVLen);
			}

			if (r_pos != 0)
			{
				ctr++;
				word2byte(byte_ctr, ctr, r_pos);
				memcpy(input + IVLen, byte_ctr, sizeof(uint8_t) * r_pos);
			}

			memcpy(input + IVLen + r_pos, fixed_input, sizeof(uint8_t) * fixed_inputLen);
			inputLen = IVLen + r_pos + fixed_inputLen;
		}
		else
		{
			// input = K(i) || count || 고정 입력값 (i >= 1)
			memcpy(input, K + IVLen + ((i-1)*macLen), sizeof(uint8_t) * macLen);

			if (r_pos != 0)
			{
				ctr++;
				word2byte(byte_ctr, ctr, r_pos);
				memcpy(input + macLen, byte_ctr, sizeof(uint8_t) * r_pos);
			}

			memcpy(input + macLen + r_pos, fixed_input, sizeof(uint8_t) * fixed_inputLen);
			inputLen = macLen + r_pos + fixed_inputLen;
		}

		HMAC_SHA256(input, inputLen, KI, KILen, K + IVLen + ((i)*macLen));
	}

	memcpy(KO, K + IVLen, sizeof(uint8_t) * (L / 8));

	free(fixed_input);
	free(input);
	free(K);
}

void kbkdf_hmac_doublepipeline_mode(
	uint8_t* KI, uint32_t KILen,
	uint32_t r, uint32_t L,
	uint8_t* Label, uint32_t LabelLen,
	uint8_t* Context, uint32_t ContextLen,
	uint8_t* KO)
{
	int32_t n = 0, h = 0, i = 0;
	int32_t inputLen = 0, macLen = 0, Llen = 0, r_pos = 0;
	uint8_t* input, *K;
	uint8_t byte_ctr[4] = { 0, };
	uint32_t ctr = 0;
	uint8_t A[KISA_SHA256_DIGEST_VALUELEN] = { 0, };
	
	macLen = KISA_SHA256_DIGEST_VALUELEN;

	r_pos = r / 8;

	input = (uint8_t*)calloc(macLen + r_pos + LabelLen + 1 + ContextLen + 4, sizeof(uint8_t));

	memcpy(input + macLen + r_pos, Label, sizeof(uint8_t) * LabelLen);
	memcpy(input + macLen + r_pos+ LabelLen + 1, Context, sizeof(uint8_t) * ContextLen);
	Llen = addLparam(input + macLen + r_pos + LabelLen + 1 + ContextLen, L);
	
	inputLen = macLen + r_pos + LabelLen + 1 + ContextLen + Llen;

	h = macLen * 8;
	n = ceiling(L, h);

	K = (uint8_t*)calloc(macLen * n, sizeof(uint8_t));

	for (i = 0; i < n; i++)
	{
		if(i == 0)
			HMAC_SHA256(input+(macLen + r_pos), LabelLen + 1 + ContextLen + Llen, KI, KILen, A);
		else
			HMAC_SHA256(A, macLen, KI, KILen, A);

		memcpy(input, A, sizeof(uint8_t) * macLen);

		if (r_pos != 0)
		{
			ctr++;
			word2byte(byte_ctr, ctr, r_pos);
			memcpy(input + macLen, byte_ctr, sizeof(uint8_t) * r_pos);
		}

		HMAC_SHA256(input, inputLen, KI, KILen, K + (i * macLen));
		
	}
	memcpy(KO, K, sizeof(uint8_t) * (L / 8));

	free(input);
	free(K);
}

void kbkdf_cmac_ctr_mode(
	uint8_t* KI, uint32_t KILen,
	uint32_t r, uint32_t L,
	uint8_t* Label, uint32_t LabelLen, uint8_t* Context, uint32_t ContextLen,
	uint8_t* KO)
{
	int32_t n = 0, h = 0, i = 0;
	int32_t inputLen = 0, macLen = 0, Llen = 0, r_pos = 0;
	uint8_t *input, *K;
	uint8_t byte_ctr[4] = { 0, };
	uint32_t ctr = 0;
	
	macLen = 16;

	h = macLen * 8;
	n = ceiling(L, h);

	r_pos = r / 8;

	input = (uint8_t*)calloc(r_pos + LabelLen + 1 + ContextLen + 4, sizeof(uint8_t));

	memcpy(input + r_pos, Label, sizeof(uint8_t) * LabelLen);
	memcpy(input + r_pos + LabelLen + 1, Context, sizeof(uint8_t) * ContextLen);
	Llen = addLparam(input + r_pos + LabelLen + 1 + ContextLen, L);
	
	K = (uint8_t*)calloc(macLen * n, sizeof(uint8_t));

	inputLen = r_pos + LabelLen + 1 + ContextLen + Llen;
	
	for (i = 0; i < n; i++)
	{
		ctr++;
		word2byte(byte_ctr, ctr, r_pos);
		memcpy(input, byte_ctr, sizeof(uint8_t) * r_pos);

		SEED_Generate_CMAC(K + (i * macLen), macLen, input, inputLen, KI);
	}

	memcpy(KO, K, sizeof(uint8_t) * (L / 8));

	free(input);
	free(K);
}

void kbkdf_cmac_feedback_mode(
	uint8_t* KI, uint32_t KILen,
	uint32_t r, uint32_t L,
	uint8_t* Label, uint32_t LabelLen,
	uint8_t* Context, uint32_t ContextLen,
	uint8_t* IV, uint32_t IVLen,
	uint8_t* KO)
{
	int32_t n = 0, h = 0, i = 0;
	int32_t inputLen = 0, macLen = 0, Llen = 0, fixed_inputLen = 0, r_pos = 0;
	uint8_t* fixed_input, * input, * K;
	uint8_t byte_ctr[4] = { 0, };
	uint32_t ctr = 0;
	
	macLen = 16;

	// 고정 입력값 설정
	// 고정 입력값 = Label || 0x00 || Context || L
	fixed_input = (uint8_t*)calloc(LabelLen + 1 + ContextLen + 4, sizeof(uint8_t));
	memcpy(fixed_input, Label, sizeof(uint8_t) * LabelLen);
	memcpy(fixed_input + LabelLen + 1, Context, sizeof(uint8_t) * ContextLen);
	Llen = addLparam(fixed_input + LabelLen + 1 + ContextLen, L);
	fixed_inputLen = LabelLen + 1 + ContextLen + Llen;

	r_pos = r / 8;

	if (macLen > IVLen)
		input = (uint8_t*)calloc(macLen + r_pos + LabelLen + 1 + ContextLen + 4, sizeof(uint8_t));
	else
		input = (uint8_t*)calloc(IVLen + r_pos + LabelLen + 1 + ContextLen + 4, sizeof(uint8_t));

	h = macLen * 8;
	n = ceiling(L, h);

	K = (uint8_t*)calloc(IVLen + macLen * n, sizeof(uint8_t));

	if (IVLen != 0)
	{
		// K(0) = IV
		memcpy(K, IV, sizeof(uint8_t) * IVLen);
	}

	for (i = 0; i < n; i++)
	{
		// 입력값 설정
		if (i == 0)
		{
			if (IVLen != 0)
			{
				// input = K(0) || count || 고정 입력값 (i == 0)
				memcpy(input, K, sizeof(uint8_t) * IVLen);
			}

			if (r_pos != 0)
			{
				ctr++;
				word2byte(byte_ctr, ctr, r_pos);
				memcpy(input + IVLen, byte_ctr, sizeof(uint8_t) * r_pos);
			}

			memcpy(input + IVLen + r_pos, fixed_input, sizeof(uint8_t) * fixed_inputLen);
			inputLen = IVLen + r_pos + fixed_inputLen;
		}
		else
		{
			// input = K(i) || count || 고정 입력값 (i >= 1)
			memcpy(input, K + IVLen + ((i - 1) * macLen), sizeof(uint8_t) * macLen);

			if (r_pos != 0)
			{
				ctr++;
				word2byte(byte_ctr, ctr, r_pos);
				memcpy(input + macLen, byte_ctr, sizeof(uint8_t) * r_pos);
			}

			memcpy(input + macLen + r_pos, fixed_input, sizeof(uint8_t) * fixed_inputLen);
			inputLen = macLen + r_pos + fixed_inputLen;
		}
		SEED_Generate_CMAC(K + IVLen + ((i)*macLen), macLen, input, inputLen, KI);
	}
	
	memcpy(KO, K + IVLen, sizeof(uint8_t) * (L / 8));

	free(fixed_input);
	free(input);
	free(K);
}

void kbkdf_cmac_doublepipeline_mode(
	uint8_t* KI, uint32_t KILen,
	uint32_t r, uint32_t L,
	uint8_t* Label, uint32_t LabelLen,
	uint8_t* Context, uint32_t ContextLen,
	uint8_t* KO)
{
	int32_t n = 0, h = 0, i = 0;
	int32_t inputLen = 0, macLen = 0, Llen = 0, r_pos = 0;
	uint8_t* input, *K;
	uint8_t byte_ctr[4] = { 0, };
	uint32_t ctr = 0;
	uint8_t A[16] = { 0, };
	
	macLen = 16;

	r_pos = r / 8;

	input = (uint8_t*)calloc(macLen + r_pos + LabelLen + 1 + ContextLen + 4, sizeof(uint8_t));

	memcpy(input + macLen + r_pos, Label, sizeof(uint8_t) * LabelLen);
	memcpy(input + macLen + r_pos + LabelLen + 1, Context, sizeof(uint8_t) * ContextLen);
	Llen = addLparam(input + macLen + r_pos + LabelLen + 1 + ContextLen, L);

	inputLen = macLen + r_pos + LabelLen + 1 + ContextLen + Llen;

	h = macLen * 8;
	n = ceiling(L, h);

	K = (uint8_t*)calloc(macLen * n, sizeof(uint8_t));

	for (i = 0; i < n; i++)
	{
		if (i == 0)
			SEED_Generate_CMAC(A, macLen, input + (macLen + r_pos), LabelLen + 1 + ContextLen + Llen, KI);
		else
			SEED_Generate_CMAC(A, macLen, A, 16, KI);

		memcpy(input, A, sizeof(uint8_t) * macLen);
		
		if (r_pos != 0)
		{
			ctr++;
			word2byte(byte_ctr, ctr, r_pos);
			memcpy(input + macLen, byte_ctr, sizeof(uint8_t) * r_pos);
		}

		SEED_Generate_CMAC(K + (i * macLen), macLen, input, inputLen, KI);

	}
	memcpy(KO, K, sizeof(uint8_t) * (L / 8));

	free(input);
	free(K);
}