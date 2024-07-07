/*	Copyright (c) 1990, 1991 UNIX System Laboratories, Inc.	*/
/*	Copyright (c) 1988 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF     	*/
/*	UNIX System Laboratories, Inc.                     	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ident	"@(#)curses:screen/_mvwaddstr.c	1.1"

#define		NOMACROS
#include	"curses_inc.h"

int
mvwaddstr(WINDOW *win, int y, int x, char *str)
{
    return (wmove(win, y, x)==ERR?ERR:waddstr(win, str));
}
