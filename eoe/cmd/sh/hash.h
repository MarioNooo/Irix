/*	Copyright (c) 1990, 1991 UNIX System Laboratories, Inc.	*/
/*	Copyright (c) 1984, 1986, 1987, 1988, 1989, 1990 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF     	*/
/*	UNIX System Laboratories, Inc.                     	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ident	"@(#)sh:hash.h	1.4.5.1"
/*
 *	UNIX shell
 */

#define		HASHZAP		0x03FF
#define		CDMARK		0x8000

#define		NOTFOUND		0x0000
#define		BUILTIN			0x0100
#define		FUNCTION		0x0200
#define		COMMAND			0x0400
#define		REL_COMMAND		0x0800
#define		PATH_COMMAND	0x1000
#define		DOT_COMMAND		0x8800		/* CDMARK | REL_COMMAND */

#define		hashtype(x)	(x & 0x1F00)
#define		hashdata(x)	(x & 0x00FF)


typedef struct entry
{
	unsigned char	*key;
	short	data;
	unsigned char	hits;
	unsigned char 	cost;
	struct entry	*next;
} ENTRY;

extern ENTRY	*hfind();
extern ENTRY	*henter();
extern int	chk_access();
extern short	pathlook();
extern short	hash_cmd();
extern void	hcreat();
extern void	hscan();
extern void	zaphash();
extern void	zapcd();
extern void	hashpr();
extern void	set_dotpath();
extern void	hash_func();
extern void	func_unhash();
extern int	what_is_path();