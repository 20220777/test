#include "kbkdf_test.h"
#include "util.h"

void kbkdf_main()
{	
	test_kbkdf_hmac_ctr();
	test_kbkdf_hmac_fb();
	test_kbkdf_hmac_dp();

	test_kbkdf_cmac_ctr();
	test_kbkdf_cmac_fb();
	test_kbkdf_cmac_dp();
}

// EOF
