/*
 * |-----------------------------------------------------------|
 * | Copyright (c) 1991, 1990 MIPS Computer Systems, Inc.      |
 * | All Rights Reserved                                       |
 * |-----------------------------------------------------------|
 * |          Restricted Rights Legend                         |
 * | Use, duplication, or disclosure by the Government is      |
 * | subject to restrictions as set forth in                   |
 * | subparagraph (c)(1)(ii) of the Rights in Technical        |
 * | Data and Computer Software Clause of DFARS 252.227-7013.  |
 * |         MIPS Computer Systems, Inc.                       |
 * |         950 DeGuigne Avenue                               |
 * |         Sunnyvale, California 94088-3650, USA             |
 * |-----------------------------------------------------------|
 */
#ident	"$Header: /proj/irix6.5.7m/isms/eoe/cmd/lp_svr4/lib/oam/RCS/retmsg.c,v 1.1 1992/12/14 13:32:31 suresh Exp $"
/*	Copyright (c) 1984, 1986, 1987, 1988, 1989 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/* LINTLIBRARY */

#include <stdio.h>
#include <string.h>
#include "oam.h"
#include <locale.h>
#include <unistd.h>

/**
 ** retmsg()
 **/

char *
#if	defined(__STDC__)
retmsg (
	int                     seqnum,
	long int                arraynum
)
#else
retmsg ( seqnum, arraynum )
	int                     seqnum;
	long int                arraynum;
#endif
{
        static char             buf[MSGSIZ];
        char                    msg_text[MSGSIZ];
	char			*msg;

        (void)setlocale(LC_ALL, "");
        setcat("uxlp");
        sprintf(msg_text,":%d",seqnum);
        msg = gettxt(msg_text,agettxt(arraynum,buf,MSGSIZ));
        return (msg);
}
