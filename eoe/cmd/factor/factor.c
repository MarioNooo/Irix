/*	Copyright (c) 1984 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/* #ident	"@(#)factor:factor.c	1.2" */
#ident	"$Header: /proj/irix6.5.7m/isms/eoe/cmd/factor/RCS/factor.c,v 1.6 1996/08/23 21:03:29 livesey Exp $"

/*	factor	COMPILE:	cc -O factor.c -s -i -lm -o factor	*/
/*
 * works up to 14 digit numbers, this limit is due to strod (used in scanf) in
 * can only handle 14 digits.  Otherwise it returns inaccurate values.
 * running time is proportional to sqrt(n)
 * accepts arguments either as input or on command line
 * 0 input terminates processing
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void try(double arg);

double nn, vv;
double huge = 1.0e14;
double sq[] = {
	10, 2, 4, 2, 4, 6, 2, 6,
	 4, 2, 4, 6, 6, 2, 6, 4,
	 2, 6, 4, 6, 8, 4, 2, 4,
	 2, 4, 8, 6, 4, 6, 2, 4,
	 6, 2, 6, 6, 4, 2, 4, 6,
	 2, 6, 4, 2, 4, 2,10, 2,
};

main(int argc, char **argv)
{
	int test = 1;
	int ret;
	register j;
	double junk, temp;
	double fr;
	double ii;

	if(argc > 2){
		printf("Usage: factor number\n");
		exit(1);
	}
	if(argc == 2){
		ret = sscanf(argv[1], "%lf", &nn);
		test = 0;
		printf("%.0f\n", nn);
		goto start;
	}
	while(test == 1){
		ret = scanf("%lf", &nn);
start:
		if((ret<1) || (nn == 0.0)){
			exit(0);
		}
		if((nn<0.0) || (nn>huge)){
			printf("Ouch!  Value not between 1 and %.lf\n",huge);
			continue;
		}
		fr = modf(nn, &junk);
		if(fr != 0.0){
			printf("Not an integer!\n");
			continue;
		}
		vv = 1. + sqrt(nn);
		try(2.0);
		try(3.0);
		try(5.0);
		try(7.0);
		ii = 1.0;
		while(ii <= vv){
			for(j=0; j<48; j++){
				ii += sq[j];
retry:
				modf(nn/ii, &temp);
				if(nn == temp*ii){
					printf("     %.0f\n", ii);
					nn = nn/ii;
					vv = 1 + sqrt(nn);
					goto retry;
				}
			}
		}
		if(nn > 1.0){
			printf("     %.0f\n", nn);
		}
		printf("\n");
	}
	return 0;
}

void
try(double arg)
{
	double temp;
retry:
	modf(nn/arg, &temp);
	if(nn == temp*arg){
		printf("     %.0f\n", arg);
		nn = nn/arg;
		vv = 1 + sqrt(nn);
		goto retry;
	}
	return;
}
