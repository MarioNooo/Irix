/*	Copyright (c) 1990, 1991 UNIX System Laboratories, Inc.	*/
/*	Copyright (c) 1988 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF     	*/
/*	UNIX System Laboratories, Inc.                     	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ident	"@(#)curses:screen/_mvwinstr.c	1.2"

#define		NOMACROS
#include	"curses_inc.h"

int
mvwinstr(WINDOW *win, int y, int x, char *s)
{
    return (wmove(win,y,x)==ERR?ERR:winstr(win,s));
}
