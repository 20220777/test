#include "wprime.h"
#include "resource.h"

#define MAX_BUF_SZ     1024
//static wprime*  gp;

void findout_prime_numbers()
{
  long long prime[2]={0, };
  long long result[MAX_BUF_SZ]={0, };
  long long count = 0;
  long long i = 0;
  int8_t tmp[32];

  //GetText(gp->item[EDIT_PRIME_BEGIN], tmp, 32);
  //prime[0] = atoll(tmp);

  //GetText(gp->item[EDIT_PRIME_END], tmp, 32);
  //prime[1] = atoll(tmp);

  //count = get_prime_set(prime, result, 0);

  //SendMessage(gp->item[COMBO_PRIME_SET], CB_RESETCONTENT, 0, 0);
  //for ( i=0 ; i<count; i++ )
  //{
  //  sprintf(tmp, "%lld", result[i]);
  //  SendMessage(gp->item[COMBO_PRIME_SET], CB_ADDSTRING, 0, (LPARAM)tmp);
  //}
  //SendMessage(gp->item[COMBO_PRIME_SET], CB_SETCURSEL, 0, 0 );
}

void select_prime()
{
  int8_t tmp[32]={0, };
  int8_t result_primes[MAX_BUF_SZ]={0, };
  int32_t e = 0;

  //GetComboText(gp->item[COMBO_PRIME_SET], tmp);
  //e = GetText(gp->item[EDIT_PRIMES], result_primes, MAX_BUF_SZ);
  //if ( e > 0 )
  //{
  //  sprintf(result_primes, "%s,%s", result_primes, tmp);
  //}
  //else
  //{
  //  sprintf(result_primes, "%s", tmp);
  //}
  //SetText(gp->item[EDIT_PRIMES], result_primes, strlen(result_primes));
}

void set_combo_prime_factors(int8_t* composite, long long* ns)
{
  int8_t items[64][32]={0, };
  long long number_set[64]={0, };
  long long e = 0;
  int32_t i=0;

  //e = GetText(gp->item[EDIT_COMPOSITE], composite, MAX_BUF_SZ);
  //SendMessage(gp->item[COMBO_COMPOSITE_FACTOR], CB_RESETCONTENT, 0, 0);
  //for ( i=0 ;  ; i++ )
  //{
  //  e = get_dlmtr_str(composite, ',', i, items[i]);
  //  if ( e < 0 )
  //  {
  //    *(ns+i) = 0;
  //    break;
  //  }
  //  *(ns+i) = atoll(items[i]);
  //  SendMessage(gp->item[COMBO_COMPOSITE_FACTOR], CB_ADDSTRING, 0, (LPARAM)items[i]);
  //}
  //SendMessage(gp->item[COMBO_COMPOSITE_FACTOR], CB_SETCURSEL, 0, 0 );
}


void findout_gcm_lcd()
{
  int8_t composite[MAX_BUF_SZ]={0, };
  int8_t tmp[32]={0, };
  long long number_set[64]={0, };
  long long result_set[64]={0, };
  long long gl[2]={0, };
  long long e = 0;
  long long i = 0;
  long long l = 0;

  //e = GetText(gp->item[EDIT_COMPOSITE], composite, MAX_BUF_SZ);
  //set_combo_prime_factors(composite, number_set);

  //e = get_common_divisor(number_set, result_set, gl);

  //sprintf(tmp, "%lld", *(gl+0));
  //ResetText(gp->item[EDIT_GCM], tmp);
  //sprintf(tmp, "%lld", *(gl+1));
  //ResetText(gp->item[EDIT_LCD], tmp);
  ////e = xget_lcm(number_set, q);
  ////long long get_gcd_lcm(long long* ns, int32_t c, long long* rs, int32_t* rc, uint8_t mode)
}
//
//long long xget_common_divisor(long long* n, long long* p, long long* gl, long long* q)
//{
//	long long i = 0;
//	long long cn = 0; //// compare number, smaller
//	long long j = 0;
//	long long e = 0;
//	long long pc = 0;
//  long long c = 0;
//
//	cn = *(n + 0);
//	for (c = 0; *(n+c); c++)
//	{
//		cn = (*(n + c) < cn) ? *(n + c) : cn;
//    *(q+c) = *(n+c);
//	}
//  *(q+c) = 0;
//
//  cn  = (cn/2)+1;
//	for ( i=2 ; i <= cn; )
//	{
//		e = c;
//		for (j = 0; *(q+j); j++)
//		{
//			if ((*(q + j) % i) != 0) 
//			{
//				e--;
//			}
//		}
//		if (e == c)
//		{
//			*(p + pc) = i;
//			pc++;
//      *(p + pc) = 0;
//      for ( j=0 ; *(q+j) ; j++ )
//      {
//        if ( (*(q+j)/i) < i )
//        {
//          e = -1;
//          break;
//        }
//        *(q+j) = *(q+j)/i;
//      }
//      *(q+j) = 0;
//		}
//    else
//    {
//      i++;
//    }
//
//    if ( e < 0 ) break;
//	}
//
//  
//  *(gl+0) = *(gl+1) = 1;
//  for ( i=0 ; *(p+i) ; i++ )
//  {
//    *(gl+0) *= *(p+i);
//  }
//
//  for ( i=0; *(q+i) ; i++ )
//  {
//    *(gl+1) *= *(q+i);
//  }
//  *(gl+1) *= *(gl+0);
//
//
//	return pc;
//}
//
//long long wprime_factoring(long long* n, long long* p, long long* q)
//{
//	long long i = 0;
//	long long cn = 0; //// compare number, smaller
//	long long e = 0;
//	long long pc = 0;
//  long long _p = 2;
//
//  cn = *(n + 0);
//	for (i = 0; *(n+i); i++)
//	{
//		cn = (*(n + i) < cn) ? *(n + i) : cn;
//    *(q+i) = *(n+i);
//	}
//  *(q+i) = 0;
//
//	for ( ; _p<=cn ; )
//	{
//		e = 0;
//		for (i = 0; *(q+i); i++)
//		{
//			if ((*(q+i)%_p) != 0)
//			{
//				e = -1;
//        get_next_prime(&_p);
//				break;
//			}
//		}
//		if (e == 0)
//		{
//			*(p + pc) = _p;
//			pc++;
//
//      for ( i=0 ; *(q+i) ; i++ )
//      {
//        *(q+i) = *(q+i)/_p;
//      }
//		}
//	}
//	return pc;
//}


void findout_prime_factors()
{
  int8_t composite[MAX_BUF_SZ]={0, };
  int8_t tmp[32]={0, };
  long long number_set[64]={0, };
  long long result_set[64]={0, };
  long long e = 0;
  long long i = 0;
  long long l = 0;

  //e = GetText(gp->item[EDIT_COMPOSITE], composite, MAX_BUF_SZ);
  //set_combo_prime_factors(composite, number_set);
  //e = prime_factoring(number_set, result_set);

  //for ( i=0 ; i<e ; i++ )
  //{
  //  if ( i > 0 )
  //  {
  //    tmp[l] = ',';
  //    l+=1;
  //  }
  //  sprintf(&tmp[l], "%lld", result_set[i]);
  //  l=strlen(tmp); 
  //}
  //ResetText(gp->item[EDIT_PRIME_FACTORS], tmp);
}

void findout_common_divisors()
{
  int8_t composite[MAX_BUF_SZ]={0, };
  int8_t tmp[32]={0, };
  long long number_set[64]={0, };
  long long result_set[64]={0, };
  long long gl[2]={0, };
  long long e = 0;
  long long i = 0;
  long long l = 0;

  //e = GetText(gp->item[EDIT_COMPOSITE], composite, MAX_BUF_SZ);
  //set_combo_prime_factors(composite, number_set);

  //e = get_common_divisor(number_set, result_set, gl);
  //for ( i=0 ; i<e ; i++ )
  //{
  //  if ( i > 0 )
  //  {
  //    tmp[l] = ',';
  //    l+=1;
  //  }
  //  sprintf(&tmp[l], "%lld", result_set[i]);
  //  l=strlen(tmp); 
  //}
  //ResetText(gp->item[EDIT_COMMON_DIVISORS], tmp);
}

void findout_divisors()
{
  int8_t tmp[4028]={0, };
  long long q[MAX_BUF_SZ]={0, };
  long long e = 0;
  long long i=0;
  long long l=0;
  long long composite;

  //GetComboText(gp->item[COMBO_COMPOSITE_FACTOR], tmp);
  //composite = atoll(tmp);
  //e = get_divisor(composite, q);
  //for ( i=0 ; i<e ; i++ )
  //{
  //  if ( i > 0 )
  //  {
  //    tmp[l] = ',';
  //    l+=1;
  //  }
  //  sprintf(&tmp[l], "%lld", q[i]);
  //  l=strlen(tmp); 
  //}
  //ResetText(gp->item[EDIT_DIVISORS], tmp);

}


//long long xget_coprimes_gt(long long* ps, long long* rs, long long count, long long* q)
//{
//  long long i = 0;
//  long long _i = 0;
//  for ( ; ; )
//  {
//    *(ps+1) = *(ps+0) + (_i++);
//    if ( is_coprime(ps, rs) == 1 )
//    {
//      *(q+i) = *(ps+1);
//      i++;
//      count --;
//    }
//    if ( count == 0 ) break;
//  }
//  return i;
//}
//long long xstr_to_long(int8_t* str, int32_t sz)
//{
//  long long i = 0;
//  long long r = 0;
//  long long _i = sz-1;
//  long long s = 1;
//
//  if ( *(str+0)<=0x30 || *(str+0)>=0x39 )
//  {
//    if ( *(str+0) == '-') 
//    {
//      s = -1;
//      i = 1;
//      _i = sz-2;
//    }
//    else if ( *(str+0) == '+') 
//    {
//      i = 1;
//      _i = sz-2;
//    }
//    else
//    {
//      return 0;
//    }
//  }
//  for (  ; i<sz ; i++, _i-- )
//  {
//    r += ctod(*(str+i))*get_exp(10, _i, 0);
//  }
//  return r*s;
//}
//long long xstr_to_long(int8_t* str, int32_t sz)
//{
//  long long i = 0;
//  long long r = 0;
//  long long _i = sz-1;
//  long long s = 1;
//
//  if ( *(str+0)<0x30 || *(str+0)>0x39 )
//  {
//    if ( *(str+0) == '-') 
//    {
//      s = -1;
//      i = 1;
//      _i = sz-2;
//    }
//    else if ( *(str+0) == '+') 
//    {
//      i = 1;
//      _i = sz-2;
//    }
//    else
//    {
//      return 0;
//    }
//  }
//  for (  ; i<sz ; i++, _i-- )
//  {
//    r += ctod(*(str+i))*get_exp(10, _i, 0);
//  }
//  return r*s;
//}
//long long xget_prime_factoring(long long p, long long* rs)
//{
//  long long e = 0;
//  long long i, ii;
//  long long idx = 0;
//  long long r = p;
//  long long q = 1;
//
//  *(rs+idx) = 1;
//  idx++;
//
//  for ( i=2; i<=p ; i++ )
//  {
//    if ( is_prime(i) )
//    {
//      if ( r%i == 0 )
//      {
//        r/=i;
//        *(rs+idx) = i;
//        idx++;
//        if ( is_prime(r) )
//        {
//          for ( ii=0 ; ii<idx ; ii++ )
//          {
//            q *= *(rs+ii);
//          }
//          if ( (q*r)==p )
//          {
//            *(rs+idx) = r;
//            idx++;
//            break;
//          }
//        }
//      }
//    }
//  }
//
//  return idx;
//}
long long wprime_factoring(long long* n, long long* p)
{
  long long i = 0;
  long long cn = 0; //// compare number, smaller
  long long e = 0;
  long long pc = 0;
  long long _p = 2;
  long long c = 0;
  long long* q = 0;

  cn = *(n + 0);
  for (c = 0; *(n+c); c++)
  {
    cn = (*(n + c) < cn) ? *(n + c) : cn;
  }

  q = n+(c+1);
  for ( i=0 ;i<c ; i++ )
  {
    *(q+i) = *(n+i);
  }

  *(p + pc) = 1;
  pc++;
  *(p+pc) = 0;

  for ( ; _p<=cn ; )
  {
    e = 0;
    for (i = 0; i<c; i++)
    {
      if ( (*(q+i)%_p)!=0 )
      {
        e = -1;
        get_next_prime(&_p);
        break;
      }
    }
    if (e == 0)
    {
      *(p + pc) = _p;
      pc++;
      *(p+pc) = 0;
      for ( i=0 ; i<c ; i++ )
      {
        *(q+i) = *(q+i)/_p;
      }
    }

    for ( i=0 ; i<c ; i++ )
    {
      if ( *(q+i) > 1 ) break;
      e++;
    }
    if ( e==c ) break;
  }
  return pc;
}
long long wprime_factoring_ex(long long* n, long long* ps, long long* p)
{
  long long i = 0;
  long long ii = 0;
  long long preq = 0;
  long long c = 0;

  c = wprime_factoring(n, p);
  //c=xget_prime_factoring(*(n+0), p);
  for ( i=0, ii=0 ; i<c ; i++ )
  {
    if ( preq != *(p+i) )
    {    
      preq = *(ps+(ii*2)+0) = *(p+i);
    }
    else
    {
      ii--;
    }
    (*(ps+(ii*2)+1))++;
    ii++;
  }

  return ii;
}
long long xeuler(long long* n, long long* pv, long long* pf)
{
  long long es = 1;
  long long i=0;
  long long e=0;

  //if ( is_prime(*(n+0)) ) es = *(n+0)-1;
  //else
  //{
  //  e = wprime_factoring_ex(n, pv, pf);
  //  for ( i=0 ; i<e ; i++ )
  //  {
  //    if ( *(pv+(i*2)+0) > 1 )
  //    {
  //      es *= (get_exp( *(pv+(i*2)+0), *(pv+(i*2)+1), 0 ) - get_exp( *(pv+(i*2)+0), *(pv+(i*2)+1)-1, 0 ));
  //    }
  //  }
  //}
  return es;
}

void euler_n()
{
  int8_t tmp[32]={0, };
  int8_t val[32]={0, };
  long long t[MAX_BUF_SZ]= {0, };
  long long rs[MAX_BUF_SZ]= {0, };
  long long fs[MAX_BUF_SZ][2] = {0, };
  long long e = 0;
  long long i=0;
  long long l=0;
  //gp->rsa.composite = 1;

  //GetText(gp->item[EDIT_RSA_PRIMES], tmp, 32);

  //for ( i=0 ; ; i++)
  //{
  //  e = get_dlmtr_str(tmp, ',', i, val);
  //  if ( e == -1 ) break;
  //  gp->rsa.primes[i] = xstr_to_long(val, e);
  //  gp->rsa.composite *= (gp->rsa.primes[i]);
  //  gp->rsa.primes[i+1] = 0;
  //}

  //gp->rsa.primes[0] = gp->rsa.N = gp->rsa.composite;
  //gp->rsa.primes[1] = 0;
  //gp->rsa.euler_N = euler((long long*)gp->rsa.primes, (long long*)fs, t);
  //sprintf(tmp, "%lld", gp->rsa.euler_N);
  //SetText(gp->item[EDIT_RSA_EULER_N], tmp, 32);
  //sprintf(tmp, "0x%08X", gp->rsa.euler_N);
  //SetText(gp->item[EDIT_RSA_EULER_N_HEX], tmp, 32);
  //sprintf(tmp, "%lld", gp->rsa.composite);
  //SetText(gp->item[EDIT_RSA_N], tmp, 32);
  //sprintf(tmp, "0x%08X", gp->rsa.composite);
  //SetText(gp->item[EDIT_RSA_N_HEX], tmp, 32);


  //e = get_coprimes_gt(p, t, 10, rs);
  //if ( e > 0 )
  //{
  //  sprintf(tmp, "%lld", rs[e-1]);
  //  SetText(gp->item[EDIT_RSA_E], tmp, 32);
  //}


  //p[0] = _euler_n;
  //p[1] = rs[e-1];
  //p[2] = 0;
  //e = euclid(p, t);
  //e = euclidex(t, rs);
  //sprintf(tmp, "%lld", rs[1]);
  //SetText(gp->item[EDIT_RSA_D], tmp, 32);
}


void euler_e()
{
  int8_t tmp[32]={0, };
  int8_t val[32]={0, };
  long long p[COPRIME_RANGE]={0, };
  long long t[COPRIME_RANGE]= {0, };
  long long rs[COPRIME_RANGE]= {0, };
  long long fs[COPRIME_RANGE][2] = {0, };
  long long e = 0;
  long long i=0;
  long long l=0;
  long long composite = 1;

  //p[0] = gp->rsa.euler_N;//( (_euler_n-(COPRIME_RANGE/2)) < 1 ) ? 1 : (_euler_n-(COPRIME_RANGE/2));
  //p[1] = 1;//( (_euler_n-(COPRIME_RANGE/2)) < 1 ) ? 1 : (_euler_n-(COPRIME_RANGE/2));
  //p[2] = gp->rsa.euler_N+(COPRIME_RANGE);

  //e = get_coprimes(p, t, COPRIME_RANGE, rs);
  //if ( e > 0 )
  //{
  //  SendMessage(gp->item[COMBO_RSA_E], CB_RESETCONTENT, 0, 0);
  //  for ( i=0 ; i<e ; i++ )
  //  {
  //    sprintf(tmp, "%lld", rs[i]);
  //    SendMessage(gp->item[COMBO_RSA_E], CB_ADDSTRING, 0, (LPARAM)tmp);
  //  }
  //}
  //SendMessage(gp->item[COMBO_RSA_E], CB_SETCURSEL, 0, 0 );
}


void euler_e_change()
{
  int8_t tmp[32];
  long long e = 0;
  long long p[MAX_BUF_SZ]={0, };
  long long t[MAX_BUF_SZ]= {0, };
  long long euc[MAX_BUF_SZ][2]= {0, };
  long long fs[MAX_BUF_SZ][2] = {0, };

  //e = GetComboText(gp->item[COMBO_RSA_E], tmp);
  //SetText(gp->item[EDIT_RSA_E], tmp, e);
  //gp->rsa.E = str_to_long(tmp, e);


  //p[0] = gp->rsa.euler_N;
  //p[1] = gp->rsa.E;
  //p[2] = 0;
  //e = euclid(p, t);
  //e = euclidex(t, (long long*)euc);
  //gp->rsa.D = euc[e-1][1]<0?(gp->rsa.euler_N+euc[e-1][1]):euc[e-1][1];
  //sprintf(tmp, "%lld", gp->rsa.D);
  //SetText(gp->item[EDIT_RSA_D], tmp, 32);
  //sprintf(tmp, "%lld",euc[e-1][1]);
  //SetText(gp->item[EDIT_RSA_D_ORG], tmp, 32);
}

void euler_e_combo_command(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  switch(HIWORD(wparam))
  {
    case CBN_DROPDOWN:
      break;

    case CBN_SELCHANGE:
      euler_e_change();
      break;

    case CBN_SETFOCUS:
      break;

    case CBN_SELENDOK:
      break;
  }

}

void generate_key()
{
  int8_t tmp[MAX_BUF_SZ];
  long long rsakey[MAX_BUF_SZ] = {0, };
  long long e = 0;
  long long i = 0;
  long long sz = 0;
  long long p[MAX_BUF_SZ] = {0, };
  long long r[MAX_BUF_SZ] = {0, };

  //sprintf(tmp, "%lld,%lld", gp->rsa.N, gp->rsa.E);
  //SetText(gp->item[EDIT_RSA_PUBKEY], tmp, MAX_BUF_SZ);

  //sprintf(tmp, "%lld", gp->rsa.D);
  //SetText(gp->item[EDIT_RSA_PRIKEY], tmp, strlen(tmp));

}
//long long get_digit_count(long long n)
//{
//  long long i = 0;
//  long long d = 1;
//  for ( i=1 ;  ; i++ )
//  {
//    if ( n/d == 0 )
//    {
//      break;
//    }
//    d *= 10;
//  }
//  return i;
//}
//
//long long rsa_encode(int8_t m, long long key, long long mod)
//{
//  return get_exp((long long)m, key, mod);
//}
//long long rsa_decode(long long cipher, long long key, long long mod)
//{
//  return get_exp(cipher, key, mod);
//}
//long long rsa_encode_stream(int8_t* m, long long sz, long long key, long long mod, int8_t* o)
//{
//  long long i, s=0;
//  unsigned long long E;
//
//  for ( i=0 ; i<sz ; i++ )
//  {
//    E = rsa_encode(*(m+i), key, mod);
//    sprintf(o+s, "%08X", E&0xFFFFFFFF);
//    s+=8;
//  }
//  return s;
//}
//long long rsa_decode_stream(int8_t* m, long long sz, long long key, long long mod, int8_t* o)
//{
//  long long i, s=0;
//  unsigned long long M, E;
//
//  for ( i=0 ; i<sz ; i+=8)
//  {
//    E = (hex_to_digit(m+i)<<24)+(hex_to_digit(m+i+2)<<16)+(hex_to_digit(m+i+4)<<8)+(hex_to_digit(m+i+6));
//    M = get_exp(E, key, mod);
//    sprintf(o+s, "%c", (int8_t)(M&0x000000FF));
//    s++;
//  }
//  return s;
//}



void encode_rsa(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int8_t tmp[MAX_BUF_SZ];
  int8_t cleartext[1024];
  int8_t cipher[1024];
  long long  e = 0;
  long long  i = 0;
  long long  ci = 0;
  long long  c = 0;
  int8_t pubkey[128][MAX_BUF_SZ];
  unsigned long long M = 0;
  unsigned long long E = 0;
  //e = GetText(gp->item[EDIT_RSA_PUBKEY], tmp, MAX_BUF_SZ);

  //for ( i=0 ; ; i++ )
  //{
  //  e = get_dlmtr_str(tmp, ',', i, pubkey[i]);
  //  if ( e < 0 ) break;
  //  gp->rsa.key[0][i] = str_to_long(pubkey[i], e);
  //}
  //e = GetText(gp->item[EDIT_RSA_CLEAR_TEXT], cleartext, 8192);
  //c = get_digit_count(gp->rsa.key[0][0]);


  //ci = rsa_encode_stream(cleartext, e, gp->rsa.key[0][1], gp->rsa.key[0][0], 0,cipher);

  ///****
  //if ( e%2 )
  //{
  //  cleartext[e] = cleartext[e+1] = 0;
  //}
  //for ( i=0,ci=0 ; i<e ; i+=2 )
  //{
  //  M = (unsigned long long)(cleartext[i]*256 + cleartext[i+1]);
  //  E = get_exp(M, gp->rsa.key[0][1], gp->rsa.key[0][0]);
  //  sprintf(&cipher[ci], "%04X", E&0x0000FFFF);
  //  ci+=4;
  //}
  //****/
  //SetText(gp->item[EDIT_RSA_ENCODE], cipher, ci);

  return;

}

void decode_rsa(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int8_t tmp[MAX_BUF_SZ];
  int8_t cleartext[8192];
  int8_t cipher[8192];
  long long  e = 0;
  long long  i = 0;
  long long  ci = 0;
  int8_t prikey[128][MAX_BUF_SZ];
  unsigned long long E = 0;
  unsigned long long M = 0;
  unsigned long long D = 0;

  //e = GetText(gp->item[EDIT_RSA_PRIKEY], tmp, MAX_BUF_SZ);
  //for ( i=0 ;  ; i++ )
  //{
  //  e = get_dlmtr_str(tmp, ',', i, prikey[i]);
  //  if ( e < 0 ) break;
  //  gp->rsa.key[1][i] = str_to_long(prikey[i], e);
  //}
  //e = GetText(gp->item[EDIT_RSA_ENCODE], cipher, 8192);


  //ci = rsa_decode_stream(cipher, e, gp->rsa.key[1][0], gp->rsa.key[0][0], 0,cleartext);

  ////for ( i=0,ci=0 ; i<e ; i+=8)
  ////{
  ////  E = (hex_to_digit(&cipher[i])<<24)+(hex_to_digit(&cipher[i+2])<<16)+(hex_to_digit(&cipher[i+4])<<8)+(hex_to_digit(&cipher[i+6]));
  ////  M = get_exp(E,  gp->rsa.key[1][0], gp->rsa.key[0][0]);
  ////  sprintf(&cleartext[ci], "%c", (int8_t)(M&0x000000FF));
  ////  ci++;
  ////}

  ///***
  //for ( i=0,ci=0 ; i<e ; i+=4)
  //{
  //  E = (hex_to_digit(&cipher[i])*256)+hex_to_digit(&cipher[i+2]);
  //  M = get_exp(E,  gp->rsa.key[1][0], gp->rsa.key[0][0]);
  //  sprintf(&cleartext[ci], "%c%c", (int8_t)((M>>8)&0x000000FF), (int8_t)(M&0x000000FF));
  //  ci+=2;
  //}
  //***/
  //SetText(gp->item[EDIT_RSA_DECODE], cleartext, ci);

  return;
}



void wprime_command(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int8_t temp[32];

  switch(LOWORD(wparam))
  {
    case IDC_BUTTON_FIND:
      findout_prime_numbers();
      break;

    case IDC_BUTTON_SELECT:
      select_prime();
      break;

    case IDC_BUTTON_RESET:
      //ResetText(gp->item[EDIT_PRIMES], 0);
      break;

    case IDC_BUTTON_GCM_LCD:
      findout_gcm_lcd();
      break;

    case IDC_BUTTON_PRIME_FACTORS:
      findout_prime_factors();
      break;

    case IDC_BUTTON_COMMON_DIVISOR:
      findout_common_divisors();
      break;

    case IDC_BUTTON_DIVISOR:
      findout_divisors();  
      break;

    case IDC_BUTTON_RSA_EULER_N:
      euler_n();
      break;

    case IDC_BUTTON_RSA_E:
      euler_e();
      break;

    case IDC_COMBO_RSA_E:
      euler_e_combo_command(hwnd, msg, wparam, lparam);
      break;

    case IDC_BUTTON_RSA_KEY:
      generate_key();
      break;

    case IDC_BUTTON_RSA_ENCODE:
      encode_rsa(hwnd, msg, wparam, lparam);
      break;

    case IDC_BUTTON_RSA_DECODE:
      decode_rsa(hwnd, msg, wparam, lparam);
      break;
  }    
}

void* wPrimeDlgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  switch(msg)
  {
    case WM_COMMAND:
      wprime_command(hwnd, msg, wparam, lparam);
      break;
    default:
      break;    
  }

  return 0;
}

void* wPrimeInit(HWND hwnd, wPrime* p)
{
  int32_t e;
  void* hmod;

  //gp->item[EDIT_PRIME_BEGIN] = GetDlgItem(hwnd, IDC_EDIT_PRIME_BEGIN);
  //gp->item[EDIT_PRIME_END] = GetDlgItem(hwnd, IDC_EDIT_PRIME_END);
  //gp->item[BUTTON_FIND] = GetDlgItem(hwnd, IDC_BUTTON_FIND);
  //gp->item[COMBO_PRIME_SET] = GetDlgItem(hwnd, IDC_COMBO_PRIME_SET);
  //gp->item[BUTTON_SELECT] = GetDlgItem(hwnd, IDC_BUTTON_SELECT);
  //gp->item[EDIT_PRIMES] = GetDlgItem(hwnd, IDC_EDIT_PRIMES);
  //gp->item[BUTTON_RESET] = GetDlgItem(hwnd, IDC_BUTTON_RESET);
  //gp->item[EDIT_GCM] = GetDlgItem(hwnd, IDC_EDIT_GCM);
  //gp->item[EDIT_LCD] = GetDlgItem(hwnd, IDC_EDIT_LCD);
  //gp->item[EDIT_COMPOSITE] = GetDlgItem(hwnd, IDC_EDIT_COMPOSITE);
  //gp->item[BUTTON_PRIME_FACTORS] = GetDlgItem(hwnd, IDC_BUTTON_PRIME_FACTORS);
  //gp->item[EDIT_PRIME_FACTORS] = GetDlgItem(hwnd, IDC_EDIT_PRIME_FACTORS);
  //gp->item[BUTTON_GCM_LCD] = GetDlgItem(hwnd, IDC_BUTTON_GCM_LCD);
  //gp->item[EDIT_COMMON_DIVISORS] = GetDlgItem(hwnd, IDC_EDIT_COMMON_DIVISORS);
  //gp->item[BUTTON_COMMON_DIVISOR] = GetDlgItem(hwnd, IDC_BUTTON_COMMON_DIVISOR);
  //gp->item[COMBO_COMPOSITE_FACTOR] = GetDlgItem(hwnd, IDC_COMBO_COMPOSITE_FACTOR);
  //gp->item[BUTTON_DIVISOR] = GetDlgItem(hwnd, IDC_BUTTON_DIVISOR);
  //gp->item[EDIT_DIVISORS] = GetDlgItem(hwnd, IDC_EDIT_DIVISORS);
  //gp->item[EDIT_RSA_PRIMES] = GetDlgItem(hwnd, IDC_EDIT_RSA_PRIMES);
  //gp->item[EDIT_RSA_EULER_N] = GetDlgItem(hwnd, IDC_EDIT_RSA_EULER_N);
  //gp->item[EDIT_RSA_EULER_N_HEX] = GetDlgItem(hwnd, IDC_EDIT_RSA_EULER_N_HEX);
  //gp->item[BUTTON_RSA_EULER_N] = GetDlgItem(hwnd, IDC_BUTTON_RSA_EULER_N);
  //gp->item[BUTTON_RSA_E] = GetDlgItem(hwnd, IDC_BUTTON_RSA_E);
  //gp->item[COMBO_RSA_E] = GetDlgItem(hwnd, IDC_COMBO_RSA_E);
  //gp->item[EDIT_RSA_N] = GetDlgItem(hwnd, IDC_EDIT_RSA_N);
  //gp->item[EDIT_RSA_N_HEX] = GetDlgItem(hwnd, IDC_EDIT_RSA_N_HEX);
  //gp->item[EDIT_RSA_E] = GetDlgItem(hwnd, IDC_EDIT_RSA_E);
  //gp->item[EDIT_RSA_D] = GetDlgItem(hwnd, IDC_EDIT_RSA_D);
  //gp->item[EDIT_RSA_D_ORG] = GetDlgItem(hwnd, IDC_EDIT_RSA_D_ORG);
  //gp->item[EDIT_RSA_PUBKEY] = GetDlgItem(hwnd, IDC_EDIT_RSA_PUBKEY);
  //gp->item[EDIT_RSA_PRIKEY] = GetDlgItem(hwnd, IDC_EDIT_RSA_PRIKEY);
  //gp->item[BUTTON_RSA_KEY] = GetDlgItem(hwnd, IDC_BUTTON_RSA_KEY);
  //gp->item[EDIT_RSA_CLEAR_TEXT] = GetDlgItem(hwnd, IDC_EDIT_RSA_CLEAR_TEXT);
  //gp->item[EDIT_RSA_ENCODE] = GetDlgItem(hwnd, IDC_EDIT_RSA_ENCODE);
  //gp->item[EDIT_RSA_DECODE] = GetDlgItem(hwnd, IDC_EDIT_RSA_DECODE);
  //gp->item[BUTTON_RSA_ENCODE] = GetDlgItem(hwnd, IDC_BUTTON_RSA_ENCODE);
  //gp->item[BUTTON_RSA_DECODE] = GetDlgItem(hwnd, IDC_BUTTON_RSA_DECODE);



  //SetText(gp->item[EDIT_PRIME_BEGIN], "200", 3);
  //SetText(gp->item[EDIT_PRIME_END], "100", 3);


  return 0;
}
