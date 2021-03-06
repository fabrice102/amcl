/* Test and benchmark elliptic curve and RSA functions
	First build amcl.a from build_ec batch file
	gcc -O3 benchtest_ec.c amcl.a -o benchtest_ec.exe
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "rsa_RSA2048.h"
#include "ecp_NIST256.h"
#include "ecp_GOLDILOCKS.h"
#include "ecp_ED25519.h"
#include "pair_BN254.h"
#include "pair_BLS383.h"
#include "pair192_BLS24.h"

#define MIN_TIME 10.0
#define MIN_ITERS 10 

using namespace amcl;

int ED_25519(csprng *RNG)
{
	using namespace ED25519;
	using namespace ED25519_BIG;

    int i,iterations;
    clock_t start;
    double elapsed;
	ECP EP,EG;
	BIG s,r,x,y;
	printf("\nTesting/Timing ED25519 ECC\n");

#if CURVETYPE_ED25519==WEIERSTRASS
	printf("Weierstrass parameterization\n");
#endif
#if CURVETYPE_ED25519==EDWARDS
	printf("Edwards parameterization\n");
#endif
#if CURVETYPE_ED25519==MONTGOMERY
	printf("Montgomery parameterization\n");
#endif

#if CHUNK==16
	printf("16-bit Build\n");
#endif
#if CHUNK==32
	printf("32-bit Build\n");
#endif
#if CHUNK==64
	printf("64-bit Build\n");
#endif

	ECP_generator(&EG);

	BIG_rcopy(r,CURVE_Order);
	BIG_randomnum(s,r,RNG);
	ECP_copy(&EP,&EG);
    ECP_mul(&EP,r);

	if (!ECP_isinf(&EP))
	{
		printf("FAILURE - rG!=O\n");
		return 0;
	}

	iterations=0;
    start=clock();
    do {
		ECP_copy(&EP,&EG);
		ECP_mul(&EP,s);

		iterations++;
		elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);
    elapsed=1000.0*elapsed/iterations;
    printf("EC  mul - %8d iterations  ",iterations);
    printf(" %8.2lf ms per iteration\n",elapsed);

	return 0;
}


int NIST_256(csprng *RNG)
{
	using namespace NIST256;
	using namespace NIST256_BIG;

    int i,iterations;
    clock_t start;
    double elapsed;
	ECP EP,EG;
	BIG s,r,x,y;
	printf("\nTesting/Timing NIST256 ECC\n");

#if CURVETYPE_NIST256==WEIERSTRASS
	printf("Weierstrass parameterization\n");
#endif
#if CURVETYPE_NIST256==EDWARDS
	printf("Edwards parameterization\n");
#endif
#if CURVETYPE_NIST256==MONTGOMERY
	printf("Montgomery parameterization\n");
#endif

#if CHUNK==16
	printf("16-bit Build\n");
#endif
#if CHUNK==32
	printf("32-bit Build\n");
#endif
#if CHUNK==64
	printf("64-bit Build\n");
#endif

	ECP_generator(&EG);

	BIG_rcopy(r,CURVE_Order);
	BIG_randomnum(s,r,RNG);
	ECP_copy(&EP,&EG);
    ECP_mul(&EP,r);

	if (!ECP_isinf(&EP))
	{
		printf("FAILURE - rG!=O\n");
		return 0;
	}

	iterations=0;
    start=clock();
    do {
		ECP_copy(&EP,&EG);
		ECP_mul(&EP,s);

		iterations++;
		elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);
    elapsed=1000.0*elapsed/iterations;
    printf("EC  mul - %8d iterations  ",iterations);
    printf(" %8.2lf ms per iteration\n",elapsed);

	return 0;
}

int GOLDI_LOCKS(csprng *RNG)
{
	using namespace GOLDILOCKS;
	using namespace GOLDILOCKS_BIG;

    int i,iterations;
    clock_t start;
    double elapsed;
	ECP EP,EG;
	BIG s,r,x,y;
	printf("\nTesting/Timing GOLDILOCKS ECC\n");

#if CURVETYPE_GOLDILOCKS==WEIERSTRASS
	printf("Weierstrass parameterization\n");
#endif
#if CURVETYPE_GOLDILOCKS==EDWARDS
	printf("Edwards parameterization\n");
#endif
#if CURVETYPE_GOLDILOCKS==MONTGOMERY
	printf("Montgomery parameterization\n");
#endif

#if CHUNK==16
	printf("16-bit Build\n");
#endif
#if CHUNK==32
	printf("32-bit Build\n");
#endif
#if CHUNK==64
	printf("64-bit Build\n");
#endif

	ECP_generator(&EG);

	BIG_rcopy(r,CURVE_Order);
	BIG_randomnum(s,r,RNG);
	ECP_copy(&EP,&EG);
    ECP_mul(&EP,r);

	if (!ECP_isinf(&EP))
	{
		printf("FAILURE - rG!=O\n");
		return 0;
	}

	iterations=0;
    start=clock();
    do {
		ECP_copy(&EP,&EG);
		ECP_mul(&EP,s);

		iterations++;
		elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);
    elapsed=1000.0*elapsed/iterations;
    printf("EC  mul - %8d iterations  ",iterations);
    printf(" %8.2lf ms per iteration\n",elapsed);

	return 0;
}



int BN_254(csprng *RNG)
{
	using namespace BN254;
	using namespace BN254_FP;
	using namespace BN254_BIG;

    int i,iterations;
    clock_t start;
    double elapsed;

	ECP P,G;
	ECP2 Q,W;
	FP12 g,w;
	FP4 cm;
	FP2 wx,wy;

	BIG s,r,x,y;
	printf("\nTesting/Timing BN254 Pairings\n");

	ECP_generator(&G);
	
	BIG_rcopy(r,CURVE_Order);
	BIG_randomnum(s,r,RNG);
	ECP_copy(&P,&G);
    PAIR_G1mul(&P,r);

	if (!ECP_isinf(&P))
	{
		printf("FAILURE - rG!=O\n");
		return 0;
	}
	
	iterations=0;
    start=clock();
    do {
		ECP_copy(&P,&G);
		PAIR_G1mul(&P,s);

		iterations++;
		elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);
    elapsed=1000.0*elapsed/iterations;
    printf("G1 mul              - %8d iterations  ",iterations);
    printf(" %8.2lf ms per iteration\n",elapsed);

    ECP2_generator(&W);

	ECP2_copy(&Q,&W);
    ECP2_mul(&Q,r);

	if (!ECP2_isinf(&Q))
	{
		printf("FAILURE - rQ!=O\n");
		return 0;
	}

	iterations=0;
    start=clock();
    do {
		ECP2_copy(&Q,&W);
		PAIR_G2mul(&Q,s);

		iterations++;
		elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);
    elapsed=1000.0*elapsed/iterations;
    printf("G2 mul              - %8d iterations  ",iterations);
    printf(" %8.2lf ms per iteration\n",elapsed);

	PAIR_ate(&w,&Q,&P);
	PAIR_fexp(&w);

	FP12_copy(&g,&w);

	PAIR_GTpow(&g,r);

	if (!FP12_isunity(&g))
	{
		printf("FAILURE - g^r!=1\n");
		return 0;
	}

	iterations=0;
    start=clock();
    do {
		FP12_copy(&g,&w);
		PAIR_GTpow(&g,s);

		iterations++;
		elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);
    elapsed=1000.0*elapsed/iterations;
    printf("GT pow              - %8d iterations  ",iterations);
    printf(" %8.2lf ms per iteration\n",elapsed);

	FP12_copy(&g,&w);

	iterations=0;
    start=clock();
    do {
		FP12_compow(&cm,&g,s,r);
		iterations++;
		elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);
    elapsed=1000.0*elapsed/iterations;
    printf("GT pow (compressed) - %8d iterations  ",iterations);
    printf(" %8.2lf ms per iteration\n",elapsed);

	iterations=0;
    start=clock();
    do {
		PAIR_ate(&w,&Q,&P);
		iterations++;
		elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);
    elapsed=1000.0*elapsed/iterations;
    printf("PAIRing ATE         - %8d iterations  ",iterations);
    printf(" %8.2lf ms per iteration\n",elapsed);

	iterations=0;
    start=clock();
    do {
		FP12_copy(&g,&w);
		PAIR_fexp(&g);
		iterations++;
		elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);
    elapsed=1000.0*elapsed/iterations;
    printf("PAIRing FEXP        - %8d iterations  ",iterations);
    printf(" %8.2lf ms per iteration\n",elapsed);

	ECP_copy(&P,&G);	
	ECP2_copy(&Q,&W);

	PAIR_G1mul(&P,s);
	PAIR_ate(&g,&Q,&P);
	PAIR_fexp(&g);

	ECP_copy(&P,&G);

	PAIR_G2mul(&Q,s);
	PAIR_ate(&w,&Q,&P);
	PAIR_fexp(&w);

	if (!FP12_equals(&g,&w))
	{
		printf("FAILURE - e(sQ,p)!=e(Q,sP) \n");
		return 0;
	}

	ECP2_copy(&Q,&W);
	PAIR_ate(&g,&Q,&P);
	PAIR_fexp(&g);

	PAIR_GTpow(&g,s);

	if (!FP12_equals(&g,&w))
	{
		printf("FAILURE - e(sQ,p)!=e(Q,P)^s \n");
		return 0;
	}
	return 0;
}


int BLS_383(csprng *RNG)
{
	using namespace BLS383;
	using namespace BLS383_FP;
	using namespace BLS383_BIG;

    int i,iterations;
    clock_t start;
    double elapsed;

	ECP P,G;
	ECP2 Q,W;
	FP12 g,w;
	FP4 cm;
	FP2 wx,wy;

	BIG s,r,x,y;
	printf("\nTesting/Timing BLS383 Pairings\n");

	ECP_generator(&G);
	
	BIG_rcopy(r,CURVE_Order);
	BIG_randomnum(s,r,RNG);
	ECP_copy(&P,&G);
    PAIR_G1mul(&P,r);

	if (!ECP_isinf(&P))
	{
		printf("FAILURE - rG!=O\n");
		return 0;
	}
	
	iterations=0;
    start=clock();
    do {
		ECP_copy(&P,&G);
		PAIR_G1mul(&P,s);

		iterations++;
		elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);
    elapsed=1000.0*elapsed/iterations;
    printf("G1 mul              - %8d iterations  ",iterations);
    printf(" %8.2lf ms per iteration\n",elapsed);

    ECP2_generator(&W);

	ECP2_copy(&Q,&W);
    ECP2_mul(&Q,r);

	if (!ECP2_isinf(&Q))
	{
		printf("FAILURE - rQ!=O\n");
		return 0;
	}

	iterations=0;
    start=clock();
    do {
		ECP2_copy(&Q,&W);
		PAIR_G2mul(&Q,s);

		iterations++;
		elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);
    elapsed=1000.0*elapsed/iterations;
    printf("G2 mul              - %8d iterations  ",iterations);
    printf(" %8.2lf ms per iteration\n",elapsed);

	PAIR_ate(&w,&Q,&P);
	PAIR_fexp(&w);

	FP12_copy(&g,&w);

	PAIR_GTpow(&g,r);

	if (!FP12_isunity(&g))
	{
		printf("FAILURE - g^r!=1\n");
		return 0;
	}

	iterations=0;
    start=clock();
    do {
		FP12_copy(&g,&w);
		PAIR_GTpow(&g,s);

		iterations++;
		elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);
    elapsed=1000.0*elapsed/iterations;
    printf("GT pow              - %8d iterations  ",iterations);
    printf(" %8.2lf ms per iteration\n",elapsed);

	FP12_copy(&g,&w);

	iterations=0;
    start=clock();
    do {
		FP12_compow(&cm,&g,s,r);
		iterations++;
		elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);
    elapsed=1000.0*elapsed/iterations;
    printf("GT pow (compressed) - %8d iterations  ",iterations);
    printf(" %8.2lf ms per iteration\n",elapsed);

	iterations=0;
    start=clock();
    do {
		PAIR_ate(&w,&Q,&P);
		iterations++;
		elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);
    elapsed=1000.0*elapsed/iterations;
    printf("PAIRing ATE         - %8d iterations  ",iterations);
    printf(" %8.2lf ms per iteration\n",elapsed);

	iterations=0;
    start=clock();
    do {
		FP12_copy(&g,&w);
		PAIR_fexp(&g);
		iterations++;
		elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);
    elapsed=1000.0*elapsed/iterations;
    printf("PAIRing FEXP        - %8d iterations  ",iterations);
    printf(" %8.2lf ms per iteration\n",elapsed);

	ECP_copy(&P,&G);	
	ECP2_copy(&Q,&W);

	PAIR_G1mul(&P,s);
	PAIR_ate(&g,&Q,&P);
	PAIR_fexp(&g);

	ECP_copy(&P,&G);

	PAIR_G2mul(&Q,s);
	PAIR_ate(&w,&Q,&P);
	PAIR_fexp(&w);

	if (!FP12_equals(&g,&w))
	{
		printf("FAILURE - e(sQ,p)!=e(Q,sP) \n");
		return 0;
	}

	ECP2_copy(&Q,&W);
	PAIR_ate(&g,&Q,&P);
	PAIR_fexp(&g);

	PAIR_GTpow(&g,s);

	if (!FP12_equals(&g,&w))
	{
		printf("FAILURE - e(sQ,p)!=e(Q,P)^s \n");
		return 0;
	}
	return 0;
}

int BLS_24(csprng *RNG)
{
	using namespace BLS24;
	using namespace BLS24_FP;
	using namespace BLS24_BIG;

    int i,iterations;
    clock_t start;
    double elapsed;

	ECP P,G;
	ECP4 Q,W;
	FP24 g,w;

	FP8 cm;
	BIG a,b,s,r;

	printf("\nTesting/Timing BLS24 Pairings\n");

	ECP_generator(&G);
	
	BIG_rcopy(r,CURVE_Order);
	BIG_randomnum(s,r,RNG);
	ECP_copy(&P,&G);
    PAIR_G1mul(&P,r);

	if (!ECP_isinf(&P))
	{
		printf("FAILURE - rG!=O\n");
		return 0;
	}
	
	iterations=0;
    start=clock();
    do {
		ECP_copy(&P,&G);
		PAIR_G1mul(&P,s);

		iterations++;
		elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);
    elapsed=1000.0*elapsed/iterations;
    printf("G1 mul              - %8d iterations  ",iterations);
    printf(" %8.2lf ms per iteration\n",elapsed);

	ECP4_generator(&W);

	ECP4_copy(&Q,&W);
    ECP4_mul(&Q,r);

	if (!ECP4_isinf(&Q))
	{
		printf("FAILURE - rQ!=O\n");
		return 0;
	}

	iterations=0;
    start=clock();
    do {
		ECP4_copy(&Q,&W);
		PAIR_G2mul(&Q,s);

		iterations++;
		elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);
    elapsed=1000.0*elapsed/iterations;
    printf("G2 mul              - %8d iterations  ",iterations);
    printf(" %8.2lf ms per iteration\n",elapsed);

	PAIR_ate(&w,&Q,&P);
	PAIR_fexp(&w);

	FP24_copy(&g,&w);

	PAIR_GTpow(&g,r);

	if (!FP24_isunity(&g))
	{
		printf("FAILURE - g^r!=1\n");
		return 0;
	}

	iterations=0;
    start=clock();
    do {
		FP24_copy(&g,&w);
		PAIR_GTpow(&g,s);

		iterations++;
		elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);
    elapsed=1000.0*elapsed/iterations;
    printf("GT pow              - %8d iterations  ",iterations);
    printf(" %8.2lf ms per iteration\n",elapsed);

	FP24_copy(&g,&w);

	iterations=0;
    start=clock();
    do {
		FP24_compow(&cm,&g,s,r);
		iterations++;
		elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);
    elapsed=1000.0*elapsed/iterations;
    printf("GT pow (compressed) - %8d iterations  ",iterations);
    printf(" %8.2lf ms per iteration\n",elapsed);

	iterations=0;
    start=clock();
    do {
		PAIR_ate(&w,&Q,&P);
		iterations++;
		elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);
    elapsed=1000.0*elapsed/iterations;
    printf("PAIRing ATE         - %8d iterations  ",iterations);
    printf(" %8.2lf ms per iteration\n",elapsed);

	iterations=0;
    start=clock();
    do {
		FP24_copy(&g,&w);
		PAIR_fexp(&g);
		iterations++;
		elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);
    elapsed=1000.0*elapsed/iterations;
    printf("PAIRing FEXP        - %8d iterations  ",iterations);
    printf(" %8.2lf ms per iteration\n",elapsed);

	ECP_copy(&P,&G);	
	ECP4_copy(&Q,&W);

	PAIR_G1mul(&P,s);
	PAIR_ate(&g,&Q,&P);
	PAIR_fexp(&g);

	ECP_copy(&P,&G);

	PAIR_G2mul(&Q,s);
	PAIR_ate(&w,&Q,&P);
	PAIR_fexp(&w);

	if (!FP24_equals(&g,&w))
	{
		printf("FAILURE - e(sQ,p)!=e(Q,sP) \n");
		return 0;
	}

	ECP4_copy(&Q,&W);
	PAIR_ate(&g,&Q,&P);
	PAIR_fexp(&g);

	PAIR_GTpow(&g,s);

	if (!FP24_equals(&g,&w))
	{
		printf("FAILURE - e(sQ,p)!=e(Q,P)^s \n");
		return 0;
	}
	return 0;
}


int RSA_2048(csprng *RNG)
{
	using namespace RSA2048;

    rsa_public_key pub;
    rsa_private_key priv;

    int i,iterations;
    clock_t start;
    double elapsed;

    char m[RFS_RSA2048],d[RFS_RSA2048],c[RFS_RSA2048];
    octet M= {0,sizeof(m),m};
    octet D= {0,sizeof(d),d};
    octet C= {0,sizeof(c),c};

	printf("\nTesting/Timing 2048-bit RSA\n");

	printf("Generating 2048-bit RSA public/private key pair\n");

	iterations=0;
    start=clock();
    do {
		RSA_KEY_PAIR(RNG,65537,&priv,&pub,NULL,NULL);
		iterations++;
		elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);
    elapsed=1000.0*elapsed/iterations;
    printf("RSA gen - %8d iterations  ",iterations);
    printf(" %8.2lf ms per iteration\n",elapsed);

	M.len=RFS_RSA2048;
	for (i=0;i<RFS_RSA2048;i++) M.val[i]=i%128;

	iterations=0;
    start=clock();
    do {
		RSA_ENCRYPT(&pub,&M,&C);
		iterations++;
		elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);
    elapsed=1000.0*elapsed/iterations;
    printf("RSA enc - %8d iterations  ",iterations);
    printf(" %8.2lf ms per iteration\n",elapsed);

	iterations=0;
    start=clock();
    do {
		RSA_DECRYPT(&priv,&C,&D);
		iterations++;
		elapsed=(clock()-start)/(double)CLOCKS_PER_SEC;
    } while (elapsed<MIN_TIME || iterations<MIN_ITERS);
    elapsed=1000.0*elapsed/iterations;
    printf("RSA dec - %8d iterations  ",iterations);
    printf(" %8.2lf ms per iteration\n",elapsed);

	for (i=0;i<RFS_RSA2048;i++)
	{
		if (M.val[i]!=D.val[i])
		{
			printf("FAILURE - RSA decryption\n");
			return 0;
		}
	}

	printf("All tests pass\n");

	return 0;
}

int main()
{
    csprng RNG;
	int i;
	char pr[10];
	unsigned long ran;


	time((time_t *)&ran);
	pr[0]=ran;
	pr[1]=ran>>8;
	pr[2]=ran>>16;
	pr[3]=ran>>24;
	for (i=4;i<10;i++) pr[i]=i;
    RAND_seed(&RNG,10,pr);

	ED_25519(&RNG);
	NIST_256(&RNG);
	GOLDI_LOCKS(&RNG);
	BN_254(&RNG);
	BLS_383(&RNG);
	BLS_24(&RNG);
	RSA_2048(&RNG);
	
}
