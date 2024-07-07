/*
 * AIM Suite III v3.1.1
 * (C) Copyright AIM Technology Inc. 1986,87,88,89,90,91,92.
 * All Rights Reserved.
 */

#ifndef	lint
	static char sccs_id[] = { " @(#) mul.c:3.2 5/30/92 20:18:42" };
#endif

#include "suite3.h"

/*
 *      mul_double
 *
 *	Note:  Version 3.0 was changed dramatically from earlier
 *	version.  The loop counters are no longer 32 by 16 or
 *	whatever it was.  Eventhough it seems that the various
 *	operations (+ * /) are all done with the same frequency,
 *	it's not really.  We do that by adjusting the percentage
 *	of the 'mix' in the defs file.  That keeps the source code
 *	consistent, yet still allow us to 'tweak' the % to fit
 *	our needs.
 *	3/12/90 Tin Le
 */
mul_double( argv, res )
char *argv;
Result *res;
{
	register int	n, i;
	register double	*ap, *bp;
        register double	d = 0.0;
	double		a, b, d1, d2;
	int		i64;

	if ( sscanf(argv, "%d %lf %lf", &i64, &d1, &d2) < 3 ) {
		fprintf(stderr, "mul_double(): needs 3 arguments!\n");
		exit(-1);
	}

	n = 100;
	a = d1;
	b = d2;
	ap = &a;
	bp = &b;
	while (n--)  {
		i = i64;
		while (i--) {
			*ap *= *bp;
		}
		d += a;
		a = d1;
	}
        res->d = d;
	return(0);
}

/*
 *      mul_float
 */
mul_float( argv, res )
char *argv;
Result *res;
{
	register int	n, i;
	register float	*ap, *bp;
        register float	d = 0.0;
	float		a, b, f1, f2;
	int		i64;

	if ( sscanf(argv, "%d %f %f", &i64, &f1, &f2) < 3 ) {
		fprintf(stderr, "mul_float(): needs 3 arguments!\n");
		exit(-1);
	}

	n = 100;
	a = f1;
	b = f2;
	ap = &a;
	bp = &b;
	while (n--)  {
		i = i64;
		while (i--) {
			*ap *= *bp;
		}
		d += a;
		a = f1;
	}
        res->d = d;
	return(0);
}

/*
 *      mul_long
 */
mul_long( argv, res )
char *argv;
Result *res;
{
	register int	n, i;
	register long	*ap, *bp;
	register long	d = 0;
	long		a, b, l1, l2;
	int		i64;

	if ( sscanf(argv, "%ld %ld %d", &l1, &l2, &i64) < 3 ) {
		fprintf(stderr, "mul_long(): needs 3 arguments!\n");
		exit(-1);
	}

	n = 100;
	a = l1;
	b = l2;
	ap = &a;
	bp = &b;
	while (n--)  {
		i = i64;
		while (i--) {
			*ap *= *bp;
		}
		d += a;
		a = l1;
	}
        res->d = d;
	return(0);
}

/*
 *      mul_short
 */
mul_short( argv, res )
char *argv;
Result *res;
{
	register int	n, i;
	register short	*ap, *bp;
	register short	d = 0;
	short		a, b;
	int		s1, s2;
	int		i64;

	if ( sscanf(argv, "%d %d %d", &s1, &s2, &i64) < 3 ) {
		fprintf(stderr, "mul_short(): needs 3 arguments!\n");
		exit(-1);
	}

	n = 100;
	a = (short)s1;
	b = (short)s2;
	ap = &a;
	bp = &b;
	while (n--)  {
		i = i64;
		while (i--) {
			*ap *= *bp;
		}
		d += a;
		a = (short)s1;
	}
        res->d = d;
	return(0);
}
