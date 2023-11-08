#include "drbg.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "seedcbc.h"
#include "ariacbc.h"


#include <dbgbuffer.h>
#include "kisa_key.h"

#include <util.h>


#define CHANGE_SEQ(x)  ( ((x&0x000000FF)<<24 ) | ((x&0x0000FF00)<<8  ) | ((x&0x00FF0000)>>8  ) | ((x&0xFF000000)>>24 ) )


# define octet_to_int(os) (((unsigned int)(os)[0] << 24) ^ ((unsigned int)(os)[1] << 16) ^ ((unsigned int)(os)[2] <<  8) ^ ((unsigned int)(os)[3]))
# define int_to_octet(os, i) { (os)[0] = (unsigned char)((i) >> 24); (os)[1] = (unsigned char)((i) >> 16); (os)[2] = (unsigned char)((i) >>  8); (os)[3] = (unsigned char)(i); }



static void ctr_increase(unsigned char *counter) {

	unsigned int c_byte;

	c_byte = octet_to_int(counter + 12);
	c_byte++;
	c_byte &= 0xFFFFFFFF;
	int_to_octet(counter + 12, c_byte);
	if (c_byte)
		return;

	c_byte = octet_to_int(counter +  8);
	c_byte++;	
	c_byte &= 0xFFFFFFFF;
	int_to_octet(counter +  8, c_byte);

	if (c_byte)
		return;

	c_byte = octet_to_int(counter +  4);
	c_byte++;
	c_byte &= 0xFFFFFFFF;
	int_to_octet(counter +  4, c_byte);

	if (c_byte)
		return;


	c_byte = octet_to_int(counter +  0);
	c_byte++;
	c_byte &= 0xFFFFFFFF;
	int_to_octet(counter +  0, c_byte);
}

void KISA_BCC(char algo,
			  unsigned char* K,
			  unsigned char* data, int datalen,
			  unsigned char* output_block, int outlen)
{
	KISA_SEED_KEY seedkey;
	KISA_ARIA_KEY ariakey;
	int n = datalen/outlen;
	int i,j,idx;
	unsigned char inputblock[MAX_V_LEN_IN_BYTES];
	memset(inputblock,0x00,MAX_V_LEN_IN_BYTES);
	memset(output_block,0x00,outlen);
	
	
	switch(algo){
		case ALGO_SEED:
			KISA_SEED_init(K,&seedkey);

			for(j=1; j <= n; j++)
			{				
				for(i=0; i<outlen; i++)
				{
					inputblock[i] = output_block[i] ^ data[i];
				}
				KISA_SEED_encrypt_block(inputblock,output_block,&seedkey);				
				data		 += SEED_BLOCK_SIZE;				
			}
			break;
		case ALGO_ARIA128:
			KISA_ARIA_encrypt_init(K,128,&ariakey);

			for(j=1; j <= n; j++)
			{
				for(i=0; i<outlen; i++)
				{
					inputblock[i] = output_block[i] ^ data[i];
				}
				KISA_ARIA_process_block(inputblock,output_block,&ariakey);				
				data		 += ARIA_BLOCK_SIZE;
			}
			break;
		case ALGO_ARIA192:
			KISA_ARIA_encrypt_init(K,192,&ariakey);

			for(j=1; j <= n; j++)
			{
				for(i=0; i<outlen; i++)
				{
					inputblock[i] = output_block[i] ^ data[i];
				}
				KISA_ARIA_process_block(inputblock,output_block,&ariakey);				
				data		 += ARIA_BLOCK_SIZE;
			}
			break;
		case ALGO_ARIA256:
			KISA_ARIA_encrypt_init(K,256,&ariakey);

			for(j=1; j <= n; j++)
			{
				for(i=0; i<outlen; i++)
				{
					inputblock[i] = output_block[i] ^ data[i];
				}
				KISA_ARIA_process_block(inputblock,output_block,&ariakey);				
				data		 += ARIA_BLOCK_SIZE;
			}
			break;
	}

	memset(&ariakey,0x00,sizeof(KISA_ARIA_KEY));
	memset(&seedkey,0x00,sizeof(KISA_SEED_KEY));
	memset(inputblock,0x00,MAX_V_LEN_IN_BYTES);
}

int KISA_Blockcipher_df(char algo,
						unsigned char *input_string, int input_str_len,
						unsigned char *output, int outlen)
{
#define MAX_NUM_OF_BYTES_TO_RETURN 64
#define BLOCK_SIZE MAX_V_LEN_IN_BYTES
#define SIZE_INT	4

	int retcode = 0;
	int i = 0;
	int L = input_str_len;
	int N = outlen;
	unsigned char X [MAX_NUM_OF_BYTES_TO_RETURN];
	unsigned char K [ALGO_ARIA256_KEYLEN_IN_BYTES];	// Maximum length
	int KLen;
	unsigned char IV[BLOCK_SIZE];
	unsigned char block[BLOCK_SIZE];
	int j;
	unsigned char *S = NULL;
	int SLen = 0;
	unsigned char *temp = NULL;
	unsigned char *iv_s = NULL;
	int iv_s_len = 0;
	int templen = 0;
	unsigned char *ptr;
	KISA_SEED_KEY seedkey;
	KISA_ARIA_KEY ariakey;

	if(outlen > MAX_NUM_OF_BYTES_TO_RETURN)
	{
		goto FREE_AND_EXIT;
	}

	// form S = L||N||input_string||0x80	
	SLen = 8 + input_str_len + 1;
	if((SLen % SEED_BLOCK_SIZE) != 0)
		SLen += (SEED_BLOCK_SIZE - (SLen % SEED_BLOCK_SIZE));
	
	S = (unsigned char*)malloc(SLen);
	memset(S,0x00,SLen);
	int_to_octet(S    , L);
	int_to_octet(S + SIZE_INT, N);
	memcpy(S + SIZE_INT + SIZE_INT, input_string, input_str_len);
	S[SIZE_INT+SIZE_INT+input_str_len] = 0x80;

  PRINT_BUFFER("S", S, SLen);





	for(j=0; j<ALGO_ARIA256_KEYLEN_IN_BYTES; j++)
		K[j] = j;

	KLen = (algo == ALGO_SEED) ? ALGO_SEED_KEYLEN_IN_BYTES : (algo == ALGO_ARIA128) ? ALGO_ARIA128_KEYLEN_IN_BYTES : (algo == ALGO_ARIA192) ? ALGO_ARIA192_KEYLEN_IN_BYTES : ALGO_ARIA256_KEYLEN_IN_BYTES;

	templen = (KLen+outlen) + (BLOCK_SIZE - ((KLen+outlen) % BLOCK_SIZE));	
	temp = (unsigned char*)malloc(templen);	
	ptr = temp;
	iv_s_len = SLen + BLOCK_SIZE;
	iv_s = (unsigned char*)malloc(iv_s_len);	
	i = 0;
	templen = 0;
	while(templen < KLen + outlen){		
		int_to_octet(IV,i);
		memset(IV+SIZE_INT,0x00,BLOCK_SIZE-SIZE_INT);
		memcpy(iv_s,IV,BLOCK_SIZE);
		memcpy(iv_s + BLOCK_SIZE,S,SLen);
	  PRINT_BUFFER("iv_s", iv_s, BLOCK_SIZE+SLen);
		
		KISA_BCC(algo,K,iv_s,iv_s_len,block,BLOCK_SIZE);
		memcpy(ptr,block,BLOCK_SIZE);
		ptr += BLOCK_SIZE;
		templen += BLOCK_SIZE;
		i++;
	}

	memcpy(K,temp,KLen);
	memcpy(X,temp+KLen,outlen);

  PRINT_BUFFER("K", K, KLen);
  PRINT_BUFFER("X", X, outlen);

	memset(temp,0x00,templen);
	free(temp);

	temp = (unsigned char*)malloc((outlen) + (BLOCK_SIZE - ((outlen) % BLOCK_SIZE)));
	ptr = temp;
	templen = 0;	

	switch(algo)
	{
	case ALGO_SEED:

		KISA_SEED_init(K,&seedkey);
		while(templen < outlen){
			KISA_SEED_encrypt_block(X,X,&seedkey);
			memcpy(ptr,X,BLOCK_SIZE);
			ptr += BLOCK_SIZE;
			templen += BLOCK_SIZE;					
		}
		break;	
	case ALGO_ARIA128:
		KISA_ARIA_encrypt_init(K,ARIA128,&ariakey);			
		while(templen < outlen){
			KISA_ARIA_process_block(X,X,&ariakey);
			memcpy(ptr,X,BLOCK_SIZE);
			ptr += BLOCK_SIZE;
			templen += BLOCK_SIZE;
		}
		break;	
	case ALGO_ARIA192:
		KISA_ARIA_encrypt_init(K,ARIA192,&ariakey);			
		while(templen < outlen){
			KISA_ARIA_process_block(X,X,&ariakey);
			memcpy(ptr,X,BLOCK_SIZE);
			ptr += BLOCK_SIZE;
			templen += BLOCK_SIZE;
		}
		break;	
	case ALGO_ARIA256:
		KISA_ARIA_encrypt_init(K,ARIA256,&ariakey);			
		while(templen < outlen){
			KISA_ARIA_process_block(X,X,&ariakey);
			memcpy(ptr,X,BLOCK_SIZE);
			ptr += BLOCK_SIZE;
			templen += BLOCK_SIZE;
		}
		break;	
	}

	memcpy(output,temp,outlen);
  PRINT_BUFFER("output", output, outlen);

	retcode = 1;
FREE_AND_EXIT:
	memset(&ariakey,0x00,sizeof(KISA_ARIA_KEY));
	memset(&seedkey,0x00,sizeof(KISA_SEED_KEY));
	if(S != NULL){
		memset(S,0x00,SLen);
		free(S);
	}
	if(temp != NULL){
		memset(temp,0x00,templen);
		free(temp);
	}
	if(iv_s != NULL){
		memset(iv_s,0x00,iv_s_len);
		free(iv_s);
	}
	memset(X,0x00,MAX_NUM_OF_BYTES_TO_RETURN);
	memset(K,0x00,ALGO_ARIA256_KEYLEN_IN_BYTES);
	memset(IV,0x00,BLOCK_SIZE);
	memset(block,0x00,BLOCK_SIZE);	
	return retcode;	
}
int KISA_CTR_DRBG_Update (unsigned char* provided_data,
													KISA_CTR_DRBG_STATE *state)
{
	unsigned char temp[MAX_SEEDLEN_IN_BYTES];
	int templen = 0;
	unsigned char* ptr;
	int i;
	int ptrindex = 0;
	KISA_SEED_KEY seedkey;
	KISA_ARIA_KEY ariakey;
	
	if(provided_data == NULL || state->seedlen <= 0)
	{
		return 0;
	}
	
	ptr = temp;
	
	switch (state->algo){
		case ALGO_SEED:
			KISA_SEED_init(state->Key,&seedkey);

  		//display("state->Key", state->Key, 32);
      PRINT_BUFFER("state->Key", state->Key, 32);
      PRINT_BUFFER("seed-key", seedkey.key_data, 32);

      //{
      //  int32_t i = 0;
      //  for ( i=0 ; i<32 ; i++ )
      //  {
      //    CHANGE_SEQ(seedkey.key_data[i]);
      //  }
      //}
			while(templen < state->seedlen)
			{
				ctr_increase(state->V);	
        PRINT_BUFFER("state->V", state->V, 16);

				KISA_SEED_encrypt_block(state->V,ptr,&seedkey);


				PRINT_BUFFER("ptr", ptr, 16);


        //{
        //  int32_t i = 0;
        //  for ( i=0 ; i<4 ; i++ )
        //  {
        //    CHANGE_SEQ(((uint32_t*)ptr)[i]);
        //  }
        //}

				ptr += SEED_BLOCK_SIZE;				
				templen += SEED_BLOCK_SIZE;
			}

      PRINT_BUFFER("temp", temp, MAX_SEEDLEN_IN_BYTES);
			memset(&seedkey,0x00,sizeof(KISA_SEED_KEY));
			break;
		case ALGO_ARIA128:
			KISA_ARIA_encrypt_init(state->Key,ARIA128,&ariakey);
			while(templen < state->seedlen)
			{
				ctr_increase(state->V);								
				KISA_ARIA_process_block(state->V,ptr,&ariakey);
				ptr += ARIA_BLOCK_SIZE;				
				templen += ARIA_BLOCK_SIZE;
			}
			memset(&ariakey,0x00,sizeof(KISA_ARIA_KEY));
			break;	
		case ALGO_ARIA192:
			KISA_ARIA_encrypt_init(state->Key,ARIA192,&ariakey);
			while(templen < state->seedlen)
			{
				ctr_increase(state->V);								
				KISA_ARIA_process_block(state->V,ptr,&ariakey);
				ptr += ARIA_BLOCK_SIZE;				
				templen += ARIA_BLOCK_SIZE;
			}
			memset(&ariakey,0x00,sizeof(KISA_ARIA_KEY));
			break;	
		case ALGO_ARIA256:
			KISA_ARIA_encrypt_init(state->Key,ARIA256,&ariakey);
			while(templen < state->seedlen)
			{
				ctr_increase(state->V);								
				KISA_ARIA_process_block(state->V,ptr,&ariakey);
				ptr += ARIA_BLOCK_SIZE;				
				templen += ARIA_BLOCK_SIZE;
			}
			memset(&ariakey,0x00,sizeof(KISA_ARIA_KEY));
			break;	
	}

	for(i = 0; i<state->seedlen; i++)
		temp[i] ^= provided_data[i];
	
	memcpy(state->Key,temp,state->Keylen);
	ptr = temp;
	MARK;PRINT_BUFFER("state->Key", state->Key, state->Keylen);
	memcpy(state->V,ptr + state->seedlen - (state->Vlen), state->Vlen);
	MARK;PRINT_BUFFER("state->V", state->V, state->Vlen);

	memset(temp,0x00,state->seedlen);

	return 1;
}

int KISA_CTR_DRBG_Instantiate(KISA_CTR_DRBG_STATE *state,
							  unsigned char  algo,
							  unsigned char* entropy_input, int entropylen,
							  unsigned char* nonce, int noncelen,
							  unsigned char* personalization_string, int stringlen,
							  unsigned char derivation_function_flag)
{

	unsigned char	seed_material[MAX_SEEDLEN_IN_BYTES];
	unsigned char*	seed_material_in = NULL;
	unsigned char*	ptr				 = NULL;
	int				seed_material_len = 0;
	int				retcode = 0;
	
	if(entropy_input == NULL)
	{
		return 0;
	}

	if(derivation_function_flag == USE_DERIVATION_FUNCTION)
	{
		state->derivation_function_flag = USE_DERIVATION_FUNCTION;
	}
	else
	{
		state->derivation_function_flag = NON_DERIVATION_FUNCTION;
	}

	switch(algo)
	{

		case ALGO_SEED:
			if(derivation_function_flag == USE_DERIVATION_FUNCTION)
			{
				if(entropylen < ALGO_SEED_SECURITY_STRENGTH_IN_BYTES )
					return 0;
			}
			else
			{
				if(entropylen < ALGO_SEED_SEEDLEN_IN_BYTES )
					return 0;
			}

			if(nonce != NULL && noncelen < ALGO_SEED_SECURITY_STRENGTH_IN_BYTES/2)
				return 0;

			state->seedlen = ALGO_SEED_SEEDLEN_IN_BYTES;
			state->Keylen = ALGO_SEED_KEYLEN_IN_BYTES;
			state->Vlen = ALGO_SEED_OUTLEN_IN_BYTES;			
			break;

		//--------------------------------------------------------------
		case ALGO_ARIA128:
			if(derivation_function_flag == USE_DERIVATION_FUNCTION)
			{
				if(entropylen < ALGO_ARIA128_SECURITY_STRENGTH_IN_BYTES )
					return 0;
			}
			else
			{
				if(entropylen < ALGO_ARIA128_SEEDLEN_IN_BYTES )
					return 0;
			}

			if(nonce != NULL && noncelen < ALGO_ARIA128_SECURITY_STRENGTH_IN_BYTES/2)
				return 0;

			state->seedlen = ALGO_ARIA128_SEEDLEN_IN_BYTES;
			state->Keylen = ALGO_ARIA128_KEYLEN_IN_BYTES;
			state->Vlen = ALGO_ARIA128_OUTLEN_IN_BYTES;
			break;
		
		//--------------------------------------------------------------
		case ALGO_ARIA192:	
			if(derivation_function_flag == USE_DERIVATION_FUNCTION)
			{
				if(entropylen < ALGO_ARIA192_SECURITY_STRENGTH_IN_BYTES )
					return 0;
			}
			else
			{
				if(entropylen < ALGO_ARIA192_SEEDLEN_IN_BYTES )
					return 0;
			}

			if(nonce != NULL && noncelen < ALGO_ARIA192_SECURITY_STRENGTH_IN_BYTES/2)
				return 0;

			state->seedlen = ALGO_ARIA192_SEEDLEN_IN_BYTES;
			state->Keylen = ALGO_ARIA192_KEYLEN_IN_BYTES;
			state->Vlen = ALGO_ARIA192_OUTLEN_IN_BYTES;
			break;

		//--------------------------------------------------------------
		case ALGO_ARIA256:	
			if(derivation_function_flag == USE_DERIVATION_FUNCTION)
			{
				if(entropylen < ALGO_ARIA256_SECURITY_STRENGTH_IN_BYTES )
					return 0;
			}
			else
			{
				if(entropylen < ALGO_ARIA256_SEEDLEN_IN_BYTES )
					return 0;
			}

			if(nonce != NULL && noncelen < ALGO_ARIA256_SECURITY_STRENGTH_IN_BYTES/2)
				return 0;

			state->seedlen = ALGO_ARIA256_SEEDLEN_IN_BYTES;
			state->Keylen = ALGO_ARIA256_KEYLEN_IN_BYTES;
			state->Vlen = ALGO_ARIA256_OUTLEN_IN_BYTES;
			break;

		default:
			return 0; // No Such Algorithm
	}

	state->algo = algo;

	if(state->derivation_function_flag == USE_DERIVATION_FUNCTION)
	{
		memset(seed_material,0x00,MAX_SEEDLEN_IN_BYTES);
		seed_material_len = entropylen;
		if(nonce != NULL && noncelen > 0) 	seed_material_len += (noncelen);
		if(personalization_string != NULL && stringlen > 0) 	seed_material_len += (stringlen);

		ptr = seed_material_in = (unsigned char*) malloc(seed_material_len);
	
		memcpy(ptr, entropy_input, entropylen);
		MARK;PRINT_BUFFER("entropy_input", seed_material_in, entropylen);

		if(nonce != NULL && noncelen > 0)
		{
			ptr += entropylen;
			memcpy(ptr, nonce, noncelen);			
		MARK;PRINT_BUFFER("entropy_input || nonce", seed_material_in, noncelen + entropylen);
		}
		
		if(personalization_string != NULL && stringlen > 0)
		{
			ptr += noncelen;
			memcpy(ptr, personalization_string, stringlen);		
		}

		MARK;PRINT_BUFFER("entropy_input || nonce || personal_string", seed_material_in, seed_material_len);


		if(!KISA_Blockcipher_df(algo,seed_material_in,seed_material_len,seed_material,state->seedlen))
		{
			goto FREE_AND_EXIT;
		}
	}
	else
	{
		int loop = stringlen <= entropylen ? stringlen : entropylen;
		int i;

		if(loop > MAX_SEEDLEN_IN_BYTES) loop = MAX_SEEDLEN_IN_BYTES;
		// seed_material = entropy_input xor personalization_string
		memset(seed_material,0x00,MAX_SEEDLEN_IN_BYTES);
		if(personalization_string == NULL || stringlen == 0)
			for(i = 0; i < entropylen; i++)
				seed_material[i] = entropy_input[i];
		else
			for(i = 0; i < loop; i++)
				seed_material[i] = entropy_input[i] ^ personalization_string[i];


	MARK;PRINT_BUFFER("seed_material", seed_material, loop?loop:entropylen);


	}


	memset(state->Key, 0x00, MAX_Key_LEN_IN_BYTES);
	memset(state->V, 0x00, MAX_V_LEN_IN_BYTES);



	if(!KISA_CTR_DRBG_Update(seed_material,state))
	{
		goto FREE_AND_EXIT;
	}

	state->reseed_counter = 1;

	retcode = 1;
	state->initialized_flag = STATE_INITIALIZED_FLAG;

FREE_AND_EXIT:	
	if(seed_material_in){
		memset(seed_material_in,0x00,seed_material_len);
		free(seed_material_in);
	}
	memset(seed_material,0x00,MAX_SEEDLEN_IN_BYTES);
	return retcode;
}

int KISA_CTR_DRBG_Reseed(KISA_CTR_DRBG_STATE *state,
					     unsigned char* entropy_input, int entropylen,
						 unsigned char* additional_input, int addlen
						 )
{

	unsigned char	seed_material[MAX_SEEDLEN_IN_BYTES];
	unsigned char*	seed_material_in = NULL;
	unsigned char*	ptr			 = NULL;
	int				seed_material_len = 0;
	int				retcode = 0;
		
	if(entropy_input == NULL)
	{
		return 0;
	}

	if(addlen > state->seedlen)
	{
		addlen = state->seedlen;
	}

	if(state->initialized_flag != STATE_INITIALIZED_FLAG)
	{
		return 0; // KISA_CTR_DRBG_Instantiate(...) required
	}

	switch(state->algo)
	{
		
		//--------------------------------------------------------------
		case ALGO_SEED:
			if(entropylen < ALGO_SEED_SECURITY_STRENGTH_IN_BYTES)
				return 0;			
			break;

		//--------------------------------------------------------------
		case ALGO_ARIA128:
			if(entropylen < ALGO_ARIA128_SECURITY_STRENGTH_IN_BYTES)
				return 0;
			break;
		
		//--------------------------------------------------------------
		case ALGO_ARIA192:	
			if(entropylen < ALGO_ARIA192_SECURITY_STRENGTH_IN_BYTES)
				return 0;
			break;

		//--------------------------------------------------------------
		case ALGO_ARIA256:	
			if(entropylen < ALGO_ARIA256_SECURITY_STRENGTH_IN_BYTES)
				return 0;
			break;

		default:
			return 0; // No Such Algorithm
	}

	if(state->derivation_function_flag == USE_DERIVATION_FUNCTION)
	{
		memset(seed_material,0x00,MAX_SEEDLEN_IN_BYTES);
		seed_material_len = entropylen;
		if(addlen > 0)
			seed_material_len += (addlen);
		ptr = seed_material_in = (unsigned char*) malloc(seed_material_len);

		memcpy(ptr, entropy_input, entropylen);
		if(addlen > 0)
		{
			ptr += entropylen;
			memcpy(ptr, additional_input, addlen);		
		}

		MARK;PRINT_BUFFER("entropy_input || nonce || personal_string", seed_material_in, seed_material_len);


		if(!KISA_Blockcipher_df(state->algo,seed_material_in,seed_material_len,seed_material,state->seedlen))
		{
			goto FREE_AND_EXIT;
		}
	}
	else
	{
		int loop = addlen <= entropylen ? addlen : entropylen;
		int i;

		// seed_material = entropy_input xor additional input
		memset(seed_material, 0x00, MAX_SEEDLEN_IN_BYTES);

		if(additional_input == NULL || addlen == 0) {
			for(i = 0; i < entropylen; i++) {
				seed_material[i] = entropy_input[i];
			}
		}else{
			for(i = 0; i < loop; i++) {
				seed_material[i] = entropy_input[i] ^ additional_input[i];
			}
		}


		MARK;PRINT_BUFFER("seed_material", seed_material, loop?loop:entropylen);

	}
	
	if(!KISA_CTR_DRBG_Update(seed_material,state))
	{
		goto FREE_AND_EXIT;
	}

	state->reseed_counter = 1;
	
	retcode = 1;

FREE_AND_EXIT:
	memset(seed_material_in,0x00,seed_material_len);
	if(seed_material_in) free(seed_material_in);
	memset(seed_material,0x00,MAX_SEEDLEN_IN_BYTES);
	return retcode;
}

int KISA_CTR_DRBG_Generate(KISA_CTR_DRBG_STATE *state,
						   unsigned char* output, int requested_num_of_bits,
						   unsigned char* addtional_input, int addlen	
						   )
{
	KISA_SEED_KEY seed_key;
	KISA_ARIA_KEY aria_key;
	unsigned char addtional_input_for_seed[MAX_SEEDLEN_IN_BYTES];
	int request_num_of_bytes;
	
	int retcode = 0;
	unsigned char* temp = NULL;
	unsigned char* ptr = NULL;
	int templen = 0;
	
	if(addlen > state->seedlen)
	{
		addlen = state->seedlen;
	}

	if(requested_num_of_bits <= 0)
	{
		return 0; // No length to generate
	}
	else
	{
		request_num_of_bytes = requested_num_of_bits / 8 + ((requested_num_of_bits % 8) != 0 ? 1 : 0);
	}

	if(state->reseed_counter > NUM_OF_REQUESTS_BETWEEN_RESEEDS)
	{
		return 0; // Reseed Required.
	}
	

	if(addtional_input != NULL && addlen > 0)
	{	
		if(state->derivation_function_flag == USE_DERIVATION_FUNCTION)
		{
			if(!KISA_Blockcipher_df(state->algo,addtional_input,addlen,addtional_input_for_seed,state->seedlen))
			{
				memset(addtional_input_for_seed,0x00,MAX_SEEDLEN_IN_BYTES);
				return 0;
			}

			if(!KISA_CTR_DRBG_Update(addtional_input_for_seed,state))
			{
				memset(addtional_input_for_seed,0x00,MAX_SEEDLEN_IN_BYTES);
				return 0;
			}
		}
		else
		{
			memset(addtional_input_for_seed,0x00,MAX_SEEDLEN_IN_BYTES);
			memcpy(addtional_input_for_seed, addtional_input, addlen);

			if(!KISA_CTR_DRBG_Update(addtional_input_for_seed,state))
			{
				memset(addtional_input_for_seed,0x00,MAX_SEEDLEN_IN_BYTES);
				return 0;
			}
		}
	}else
	{
		memset(addtional_input_for_seed,0x00,MAX_SEEDLEN_IN_BYTES);
	}

	templen = request_num_of_bytes + (MAX_V_LEN_IN_BYTES - (request_num_of_bytes % MAX_V_LEN_IN_BYTES));
	temp = (unsigned char*)malloc(templen);
	ptr = temp;
	templen = 0;


	switch(state->algo)
	{
	case ALGO_SEED:
		KISA_SEED_init(state->Key, &seed_key);

    MARK;PRINT_BUFFER("state->Key", state->Key, 32);


    MARK;PRINT_BUFFER("seed_key", seed_key.key_data, 32);
      //{
      //  int32_t i = 0;
      //  for ( i=0 ; i<32 ; i++ )
      //  {
      //    CHANGE_SEQ(seed_key.key_data[i]);
      //  }
      //}

		while(templen < request_num_of_bytes)
		{
			ctr_increase(state->V);
    	MARK;PRINT_BUFFER("state->V", state->V, 16);

			KISA_SEED_encrypt_block(state->V,ptr,&seed_key);
      //{
      //  int32_t i = 0;
      //  for ( i=0 ; i<4 ; i++ )
      //  {
      //    CHANGE_SEQ(((uint32_t*)ptr)[i]);
      //  }
      //}

    	MARK;PRINT_BUFFER("ptr", ptr, 16);

			ptr += ALGO_SEED_OUTLEN_IN_BYTES;
			templen += ALGO_SEED_OUTLEN_IN_BYTES;
		}
		MARK;
		PRINT_BUFFER("temp", temp, templen);

		memset(&seed_key,0x00,sizeof(KISA_SEED_KEY));
		break;
	case ALGO_ARIA128:
		KISA_ARIA_encrypt_init(state->Key, 128 ,&aria_key);
		while(templen < request_num_of_bytes)
		{
			ctr_increase(state->V);
			KISA_ARIA_process_block(state->V,ptr,&aria_key);
			ptr += ALGO_ARIA128_OUTLEN_IN_BYTES;
			templen += ALGO_ARIA128_OUTLEN_IN_BYTES;
		}
		memset(&aria_key,0x00,sizeof(KISA_ARIA_KEY));
		break;
	case ALGO_ARIA192:
		KISA_ARIA_encrypt_init(state->Key, 192 ,&aria_key);
		while(templen < request_num_of_bytes)
		{
			ctr_increase(state->V);
			KISA_ARIA_process_block(state->V,ptr,&aria_key);
			ptr += ALGO_ARIA192_OUTLEN_IN_BYTES;
			templen += ALGO_ARIA192_OUTLEN_IN_BYTES;
		}
		memset(&aria_key,0x00,sizeof(KISA_ARIA_KEY));
		break;
	case ALGO_ARIA256:
		KISA_ARIA_encrypt_init(state->Key, 256 ,&aria_key);
		while(templen < request_num_of_bytes)
		{
			ctr_increase(state->V);
			KISA_ARIA_process_block(state->V,ptr,&aria_key);
			ptr += ALGO_ARIA256_OUTLEN_IN_BYTES;
			templen += ALGO_ARIA256_OUTLEN_IN_BYTES;
		}
		memset(&aria_key,0x00,sizeof(KISA_ARIA_KEY));
		break;
	}
	
	memcpy(output,temp,request_num_of_bytes);

	printf("---> request_num_of_bytes %d \r\n", request_num_of_bytes);
	if(requested_num_of_bits % 8 != 0)
		output[request_num_of_bytes-1] = (temp[request_num_of_bytes-1] & (0x000000FF&(0xFF << (8-(requested_num_of_bits%8)))));

	if(!KISA_CTR_DRBG_Update(addtional_input_for_seed,state))
	{
		goto FREE_AND_EXIT;
	}

	(state->reseed_counter)++;

	retcode = 1;
FREE_AND_EXIT:
	memset(temp,0x00,templen);
	if(temp) free(temp);
	memset(addtional_input_for_seed,0x00,MAX_SEEDLEN_IN_BYTES);	
	return retcode;
}



#define TEST_VECTOR_SZ    2048

int32_t __read_token(int8_t* token, int32_t idx, uint8_t* in, uint8_t* out)
{
	int32_t i = 0;
	int32_t _idx = 0;

	for (  ; *in ; in++ )
	{
		if ( memcmp(token, in, strlen(token))==0 )
		{
			in+=strlen(token);
			for ( i=0 ; *in ; in++ )
			{
				*(out+i) = *in;
				i++;
				if ( *in==':' )
				{
					i--;
					break;
				}
			}

      if ( idx == _idx ) break;
      _idx ++;
		}
	}
	*(out+i) = 0;
	return i;
}

int32_t __read_line(uint8_t* in, uint8_t* out)
{
	int32_t i = 0;

  if ( in == 0 ) return -1;

	for ( i=0 ; *in ; in++ )
	{
		*(out+i) = *in;
		i++;
		if ( *in==';' )
		{
      break;
		}
	}
	if ( i>0 )*(out+i-1) = 0;
	return i-1;
}


void kisa_ctr_drbg_testvector()
{
	const uint8_t* TestVector[] = 
//#include "testvector/CTR_DRBG(SEED-128(no DF)(no PR))_KAT.txt"
//#include "testvector/CTR_DRBG(SEED-128(no DF)(use PR))_KAT.txt"
//#include "testvector/CTR_DRBG(SEED-128(use DF)(use PR))_KAT.txt"
#include "testvector/CTR_DRBG(SEED-128(use DF)(no PR))_KAT.txt"

;

	FILE* fp = 0;
  int32_t e = 0;
	int32_t i = 0;
	int32_t sz = 32;
	volatile uint8_t line[TEST_VECTOR_SZ] = {0};
	volatile uint8_t hval[8][TEST_VECTOR_SZ] = {0};
	volatile uint8_t hbuf[8][TEST_VECTOR_SZ] = {0};
	volatile uint8_t rbuf[TEST_VECTOR_SZ] = {0};
	int32_t vsz[8] = {0};
	int32_t hsz[8] = {0};
	int8_t vctrname[1024] = {0};
  KISA_CTR_DRBG_STATE state;
  memset(&state, 0, sizeof(KISA_CTR_DRBG_STATE));
  unsigned char randC[1024] = {0};
	int drnsz = 32;



	//const uint8_t* ENTROPY_1 =
	//	"0001020304050607 08090A0B0C0D0E0F"
	//	"1011121314151617 18191A1B1C1D1E1F";

	//const uint8_t* ENTROPY_2 =
	//	"8081828384858687 88898A8B8C8D8E8F"
	//	"9091929394959697 98999A9B9C9D9E9F"
	//	"C0C1C2C3C4C5C6C7 C8C9CACBCCCDCECF"
	//	"D0D1D2D3D4D5D6D7 D8D9DADBDCDDDEDF";

	//const uint8_t* NONCE =
	//	"2021222324252627";

	//const uint8_t* PER_STR =
	//	"4041424344454647 48494A4B4C4D4E4F"
	//	"5051525354555657 58595A5B5C5D5E5F";

	//const uint8_t* ADD_STR =
	//	"6061626364656667 68696A6B6C6D6E6F"
	//	"7071727374757677 78797A7B7C7D7E7F";
	//	"A0A1A2A3A4A5A6A7 A8A9AAABACADAEAF"
	//	"B0B1B2B3B4B5B6B7 B8B9BABBBCBDBEBF";



	////const uint8_t* ENTROPY_1 = "A5 BA CF E4 F9 0F 24 39 4E 63 78 8D A2 B7 CC E1";
	////const uint8_t* ENTROPY_2 = 0;

	////const uint8_t* NONCE = "D1 E6 FB 11 26 3B 50 65";

	////const uint8_t* PER_STR = "50 65 72 73 6F 6E 61 6C 69 7A 61 74 69 6F 6E 20 53 74 72 69 6E 67";

	////const uint8_t* ADD_STR = 0;



	//hsz[7] = ascii_to_hex("3002F890728569CF A9184DBC36A52050 D0F9E76AF64CA232 A7293E40D5F96A7A", hbuf[7]);

	//hsz[0] = ascii_to_hex(ENTROPY_1, hbuf[0]);
	//hsz[3] = ascii_to_hex(ENTROPY_2, hbuf[3]);
	//hsz[1] = ascii_to_hex(NONCE, hbuf[1]);
	//hsz[2] = ascii_to_hex(PER_STR, hbuf[2]);
	//hsz[4] = ascii_to_hex(ADD_STR, hbuf[4]);


 // hsz[3] = 32;
 // hsz[4] = 32;


	for ( i=0 ; ; i++ )
	{

		if (__read_line(TestVector[i], line)<0) break;
		hsz[0] = __read_token("EntropyInput=", 0, line, hval[0]);
		hsz[1] = __read_token("Nonce=", 0, line, hval[1]);
		hsz[2] = __read_token("PersonalizationString=", 0, line, hval[2]);
		hsz[3] = __read_token("EntropyInputReseed=", 0, line, hval[3]);
		hsz[4] = __read_token("AdditionalInputReseed=", 0, line, hval[4]);
		hsz[5] = __read_token("AdditionalInput1=", 0, line, hval[5]);
		hsz[6] = __read_token("AdditionalInput2=", 0, line, hval[6]);
		hsz[7] = __read_token("ReturnedBits=", 0, line, hval[7]);

		hsz[0] = ascii_to_hex(hval[0], hbuf[0]);
		hsz[1] = ascii_to_hex(hval[1], hbuf[1]);
		hsz[2] = ascii_to_hex(hval[2], hbuf[2]);
		hsz[3] = ascii_to_hex(hval[3], hbuf[3]);
		hsz[4] = ascii_to_hex(hval[4], hbuf[4]);
		hsz[5] = ascii_to_hex(hval[5], hbuf[5]);
		hsz[6] = ascii_to_hex(hval[6], hbuf[6]);
		hsz[7] = ascii_to_hex(hval[7], hbuf[7]);

    BOX("KISA_CTR_DRBG_Instantiate");
    e = KISA_CTR_DRBG_Instantiate(&state, ALGO_SEED, hbuf[0], hsz[0], hbuf[1], hsz[1], hbuf[2], hsz[2], USE_DERIVATION_FUNCTION);

    BOX("KISA_CTR_DRBG_Reseed");
	  e = KISA_CTR_DRBG_Reseed(&state, hbuf[3], hsz[3], hbuf[4], hbuf[4]);


    BOX("KISA_CTR_DRBG_Generate");
    e = KISA_CTR_DRBG_Generate(&state, &randC[0], drnsz*8, 0, 0);   /// 32 byte == 256 bit

    PRINT_BUFFER("drn", hbuf[7], hsz[7]);

    PRINT_BUFFER("rand", randC, drnsz);


	}


	return (void*)e;

}
















void kisa_ctr_drbg_test()
{
  int e = 0;
  unsigned char entropy1[2048]={0};
  unsigned char entropy2[2048]={0};
  unsigned char drn[2048]={0};
	int drnsz = 0;
  unsigned char add1[1024]={0};
  int add1_sz = 0;
  unsigned char nonce1[1024]={0};
  int nonce1_sz = 16;
  char pstr[1024] = {0 };
  int pstr_sz = 0;

  unsigned char randC[8][1024] = {0};
  int i=0;
	int32_t sz[4] = {0};


  KISA_CTR_DRBG_STATE state;
  memset(&state, 0, sizeof(KISA_CTR_DRBG_STATE));



#if 1 //// SEED useDF usePR
	const uint8_t* ENTROPY_1 =
		"0001020304050607 08090A0B0C0D0E0F"
		"1011121314151617 18191A1B1C1D1E1F";

	const uint8_t* ENTROPY_2 =
		"8081828384858687 88898A8B8C8D8E8F"
		"9091929394959697 98999A9B9C9D9E9F"
		"C0C1C2C3C4C5C6C7 C8C9CACBCCCDCECF"
		"D0D1D2D3D4D5D6D7 D8D9DADBDCDDDEDF";

	const uint8_t* NONCE =
		"2021222324252627";

	const uint8_t* PER_STR =
		"4041424344454647 48494A4B4C4D4E4F"
		"5051525354555657 58595A5B5C5D5E5F";

	const uint8_t* ADD_STR =
		"6061626364656667 68696A6B6C6D6E6F"
		"7071727374757677 78797A7B7C7D7E7F";
		"A0A1A2A3A4A5A6A7 A8A9AAABACADAEAF"
		"B0B1B2B3B4B5B6B7 B8B9BABBBCBDBEBF";

	sz[0]     = ascii_to_hex(ENTROPY_1, entropy1);
	sz[1]     = ascii_to_hex(ENTROPY_2, entropy2);
	nonce1_sz = ascii_to_hex(NONCE, nonce1);
	pstr_sz   = ascii_to_hex(PER_STR, pstr);
	add1_sz   = ascii_to_hex(ADD_STR, add1);
	//sz[2] = ascii_to_hex(KISA_KEY_SEED_CTR_DRBG[0][6], drn);

	drnsz = ascii_to_hex("3002F890728569CF A9184DBC36A52050 D0F9E76AF64CA232 A7293E40D5F96A7A", drn);



  BOX("KISA_CTR_DRBG_Instantiate 0");
  e = KISA_CTR_DRBG_Instantiate(&state, ALGO_SEED, entropy1, sz[0], nonce1, nonce1_sz, pstr,  pstr_sz, 0xFF);

  BOX("KISA_CTR_DRBG_Reseed 0");
	e = KISA_CTR_DRBG_Reseed(&state, entropy2, 32, add1, 32);

  BOX("KISA_CTR_DRBG_Generate 0");
  e = KISA_CTR_DRBG_Generate(&state, &randC[0], drnsz*8,add1,32);   /// 32 byte == 256 bit
  PRINT_BUFFER("rand", randC[0], drnsz);


  BOX("");









  BOX("KISA_CTR_DRBG_Instantiate 2");
  e = KISA_CTR_DRBG_Instantiate(&state, ALGO_SEED, entropy1, sz[0], nonce1, nonce1_sz, pstr,  pstr_sz, 0xFF);

  BOX("KISA_CTR_DRBG_Reseed 0");
	e = KISA_CTR_DRBG_Reseed(&state, entropy2, 32, add1, 32);
  BOX("KISA_CTR_DRBG_Reseed 0");
	e = KISA_CTR_DRBG_Reseed(&state, entropy2, 32, add1, 32);
  BOX("KISA_CTR_DRBG_Reseed 0");
	e = KISA_CTR_DRBG_Reseed(&state, entropy2, 32, add1, 32);

  BOX("KISA_CTR_DRBG_Generate 0");
  e = KISA_CTR_DRBG_Generate(&state, &randC[0], drnsz*8,0,0);   /// 32 byte == 256 bit
  PRINT_BUFFER("rand", randC[0], drnsz);

  BOX("KISA_CTR_DRBG_Reseed 0");
	e = KISA_CTR_DRBG_Reseed(&state, entropy2, 32, add1, 32);
  BOX("KISA_CTR_DRBG_Reseed 0");
	e = KISA_CTR_DRBG_Reseed(&state, entropy2, 32, add1, 32);
  BOX("KISA_CTR_DRBG_Reseed 0");
	e = KISA_CTR_DRBG_Reseed(&state, entropy2, 32, add1, 32);


  BOX("KISA_CTR_DRBG_Generate 0");
  e = KISA_CTR_DRBG_Generate(&state, &randC[0], drnsz*8,0,0);   /// 32 byte == 256 bit
  PRINT_BUFFER("rand", randC[0], drnsz);

  BOX("KISA_CTR_DRBG_Reseed 0");
	e = KISA_CTR_DRBG_Reseed(&state, entropy2, 32, add1, 32);
  BOX("KISA_CTR_DRBG_Reseed 0");
	e = KISA_CTR_DRBG_Reseed(&state, entropy2, 32, add1, 32);
  BOX("KISA_CTR_DRBG_Reseed 0");
	e = KISA_CTR_DRBG_Reseed(&state, entropy2, 32, add1, 32);

  BOX("KISA_CTR_DRBG_Generate 0");
  e = KISA_CTR_DRBG_Generate(&state, &randC[0], drnsz*8,0,0);   /// 32 byte == 256 bit
  PRINT_BUFFER("rand", randC[0], drnsz);



#endif




#if 0 //// SEED noDF noPR

	const uint8_t* ENTROPY_1 =
		"0001020304050607 08090A0B0C0D0E0F"
		"1011121314151617 18191A1B1C1D1E1F"
		"8081828384858687 88898A8B8C8D8E8F"
		"9091929394959697 98999A9B9C9D9E9F"
		"C0C1C2C3C4C5C6C7 C8C9CACBCCCDCECF"
		"D0D1D2D3D4D5D6D7 D8D9DADBDCDDDEDF";

	const uint8_t* PER_STR =
		"4041424344454647 48494A4B4C4D4E4F"
		"5051525354555657 58595A5B5C5D5E5F";

	const uint8_t* ADD_STR =
		"6061626364656667 68696A6B6C6D6E6F"
		"7071727374757677 78797A7B7C7D7E7F"
		"A0A1A2A3A4A5A6A7 A8A9AAABACADAEAF"
		"B0B1B2B3B4B5B6B7 B8B9BABBBCBDBEBF";



	sz[0]   = ascii_to_hex(ENTROPY_1, entropy1);
	pstr_sz = ascii_to_hex(PER_STR, pstr);
	add1_sz = ascii_to_hex(ADD_STR, add1);
	//sz[2] = ascii_to_hex(KISA_KEY_SEED_CTR_DRBG[0][6], drn);



  BOX("KISA_CTR_DRBG_Instantiate");
  e = KISA_CTR_DRBG_Instantiate(&state, ALGO_SEED, entropy1, 32, 0, 0, pstr,  32, 0);

  BOX("KISA_CTR_DRBG_Reseed");
	e = KISA_CTR_DRBG_Reseed(&state, &entropy1[32], 32, add1, 32);



  BOX("KISA_CTR_DRBG_Generate");
  e = KISA_CTR_DRBG_Generate(&state, &randC[0], 256,0,0);   /// 32 byte == 256 bit




  //BOX("KISA_CTR_DRBG_Generate");
  //e = KISA_CTR_DRBG_Generate(&state, &randC[0], 128*8, 0, 0);   /// 32 byte == 256 bit

  PRINT_BUFFER("rand", randC, 128);

#endif


#if 0 /// SEED DF noPR

	sz[0] = ascii_to_hex(KISA_KEY_SEED_CTR_DRBG_DF[0][1], entropy1);
	sz[1] = ascii_to_hex(KISA_KEY_SEED_CTR_DRBG_DF[0][2], nonce1);
	sz[2] = ascii_to_hex(KISA_KEY_SEED_CTR_DRBG_DF[0][8], drn);



  BOX("KISA_CTR_DRBG_Instantiate");
  e = KISA_CTR_DRBG_Instantiate(&state, ALGO_SEED, entropy1, sz[0], nonce1, sz[1], 0,  0, 0xFF);
  printf(" KISA_CTR_DRBG_Instantiate  ----> %d \r\n", e);

  for ( ; ; )
  {
    PRINT_BUFFER("entropy1", entropy1, sz[0]);
    PRINT_BUFFER("nonce1", nonce1, sz[1]);

    e = KISA_CTR_DRBG_Generate(&state, &randC[0], 128*8, 0, 0);   /// 32 byte == 256 bit
    printf(" KISA_CTR_DRBG_Generate     ----> %d \r\n", e);

    PRINT_BUFFER("rand", randC, 128);
    PRINT_BUFFER("drn", drn, sz[2]);

    break;


    e = KISA_CTR_DRBG_Generate(&state, &randC[16], 128, 0, 0);   /// 32 byte == 256 bit
    printf(" KISA_CTR_DRBG_Generate     ----> %d \r\n", e);

    e = KISA_CTR_DRBG_Reseed(&state, entropy2, 32, 0, 0);
    printf(" KISA_CTR_DRBG_Reseed       ----> %d \r\n", e);

    e = KISA_CTR_DRBG_Generate(&state, &randC[64], 256, 0, 0);   /// 32 byte == 256 bit
    printf(" KISA_CTR_DRBG_Generate     ----> %d \r\n", e);

    e = KISA_CTR_DRBG_Generate(&state, &randC[86], 256, 0, 0);   /// 32 byte == 256 bit
    printf(" KISA_CTR_DRBG_Generate     ----> %d \r\n", e);

    break;
  }
#endif




#if 0 //// SEED noDF noPR

	sz[0] = ascii_to_hex(KISA_KEY_SEED_CTR_DRBG[0][0], entropy1);
	sz[1] = ascii_to_hex(KISA_KEY_SEED_CTR_DRBG[0][2], entropy2);
	sz[2] = ascii_to_hex(KISA_KEY_SEED_CTR_DRBG[0][6], drn);



  BOX("KISA_CTR_DRBG_Instantiate");
  e = KISA_CTR_DRBG_Instantiate(&state, ALGO_SEED, entropy1, sz[0], 0, 0, 0,  0, 0);
  printf(" KISA_CTR_DRBG_Instantiate  ----> %d \r\n", e);

  for ( ; ; )
  {
    PRINT_BUFFER("entropy1", entropy1, sz[0]);
    PRINT_BUFFER("entropy2", entropy2, sz[1]);
    BOX("KISA_CTR_DRBG_Reseed");

    e = KISA_CTR_DRBG_Reseed(&state, entropy2, sz[1], 0, 0);
    BOX("KISA_CTR_DRBG_Generate");

    e = KISA_CTR_DRBG_Generate(&state, &randC[0], 128*8, 0, 0);   /// 32 byte == 256 bit
    printf(" KISA_CTR_DRBG_Generate     ----> %d \r\n", e);

    PRINT_BUFFER("rand", randC, 128);
    PRINT_BUFFER("drn", drn, sz[2]);

    break;


    e = KISA_CTR_DRBG_Generate(&state, &randC[16], 128, 0, 0);   /// 32 byte == 256 bit
    printf(" KISA_CTR_DRBG_Generate     ----> %d \r\n", e);

    e = KISA_CTR_DRBG_Reseed(&state, entropy2, 32, 0, 0);
    printf(" KISA_CTR_DRBG_Reseed       ----> %d \r\n", e);
    //fprint_buffer("entropy2", entropy2, 32, 0, 16);

    e = KISA_CTR_DRBG_Generate(&state, &randC[64], 256, 0, 0);   /// 32 byte == 256 bit
    printf(" KISA_CTR_DRBG_Generate     ----> %d \r\n", e);

    e = KISA_CTR_DRBG_Generate(&state, &randC[86], 256, 0, 0);   /// 32 byte == 256 bit
    printf(" KISA_CTR_DRBG_Generate     ----> %d \r\n", e);
    //fprint_buffer("rand", randC, 128, 0, 16);

    //mcsleep(500000);
    break;
  }
#endif



}

