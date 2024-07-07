/*
 * bgets.c
 *
 *
 * Copyright 1991, Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;
 * the contents of this file may not be disclosed to third parties, copied or
 * duplicated in any form, in whole or in part, without the prior written
 * permission of Silicon Graphics, Inc.
 *
 * RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions
 * as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
 * and Computer Software clause at DFARS 252.227-7013, and/or in similar or
 * successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -
 * rights reserved under the Copyright Laws of the United States.
 */

#ident "$Revision: 1.4 $"



/*
	read no more than <count> characters into <buf> from stream <fp>,
	stoping at any character slisted in <stopstr>.
	NOTE: This function will not work for multi-byte characters.
*/
#ifdef __STDC__
	#pragma weak bgets = _bgets
#endif
#include "synonyms.h"

#include <sys/types.h>
#include <stdio.h>

#define CHARS	256

static char	stop[CHARS];
static int	first_bgets = 1;

char *
bgets(char *buf, register size_t count, FILE *fp, char *stopstr)
{
	register char	*cp;
	register int	c;
	register size_t i;

	/* clear and set stopstr array */
	if ((stopstr) || (first_bgets)) {
		for( cp = stop;  cp < &stop[CHARS]; )
			*cp++ = 0;
		first_bgets = 0;
	}
	if (stopstr)
		for( cp = stopstr;  *cp; )
			stop[(unsigned char)*cp++] = 1;
	i = 0;
	for( cp = buf;  ; ) {
		if(i++ == count) {
			*cp = '\0';
			break;
		}
		if( (c = getc(fp)) == EOF ) {
			*cp = '\0';
			if( cp == buf )
				cp = (char *) 0;
			break;
		}
		*cp++ = (char) c;
		if( stop[ c ] ) {
			*cp = '\0';
			break;
		}
	}
	return  cp;
}
