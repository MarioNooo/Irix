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
/* $Header: /proj/irix6.5.7m/isms/eoe/cmd/lp_svr4/include/RCS/errorMgmt.h,v 1.1 1992/12/14 13:22:10 suresh Exp $ */
/*	Copyright (c) 1984, 1986, 1987, 1988, 1989 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/


#ifndef	ERROR_MGMT_H
#define	ERROR_MGMT_H
/*==================================================================*/
/*
*/

#include	<errno.h>

/*----------------------------------------------------------*/
/*
*/
typedef	enum
{

	Fatal,
	NonFatal

}  errorClass;

typedef	enum
{

	Unix,
	TLI,
	XdrEncode,
	XdrDecode,
	Internal

}  errorType;
	

/*----------------------------------------------------------*/
/*
**	Interface definition.
*/
#if (defined(__STDC__) || (__SVR4__STDC))

extern	void	TrapError (errorClass, errorType, char *, char *);

#else

extern	void	TrapError ();

#endif


/*----------------------------------------------------------*/
/*
*/
extern	int	errno;

/*==================================================================*/
#endif