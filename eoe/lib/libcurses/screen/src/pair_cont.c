/*	Copyright (c) 1990, 1991 UNIX System Laboratories, Inc.	*/
/*	Copyright (c) 1988 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF     	*/
/*	UNIX System Laboratories, Inc.                     	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ident	"@(#)curses:pair_cont.c	1.4"

#include "curses_inc.h"

int
pair_content(short pair, short *f, short *b)
{
    register _Color_pair *ptp;

    if (pair < 1 || pair >= COLOR_PAIRS ||
	(ptp = cur_term->_pairs_tbl) == (_Color_pair *) NULL)
	return (ERR);

    ptp += pair;

    if (!ptp->init)
        return (ERR);

    *f = ptp->foreground;
    *b = ptp->background;
    return (OK);
}
