/*	Copyright (c) 1990, 1991 UNIX System Laboratories, Inc.	*/
/*	Copyright (c) 1984, 1986, 1987, 1988, 1989, 1990 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF     	*/
/*	UNIX System Laboratories, Inc.                     	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ident  "$Revision: 2.13 $"

/*******************************************************************

		PROPRIETARY NOTICE (Combined)

This source code is unpublished proprietary information
constituting, or derived under license from AT&T's UNIX(r) System V.
In addition, portions of such source code were derived from Berkeley
4.3 BSD under license from the Regents of the University of
California.

		Copyright Notice 

Notice of copyright on this source code product does not indicate 
publication.

	(c) 1986,1987,1988,1989  Sun Microsystems, Inc
	(c) 1983,1984,1985,1986,1987,1988,1989  AT&T.
	          All rights reserved.
********************************************************************/ 

#include <sys/types.h>
#include <sys/syssgi.h>
#include <locale.h>	/* For LC_ALL */
#include <unistd.h>
#include <pfmt.h>
#include "sh.h"
#include "sh.proc.h"
#include "sh.wconst.h"

struct limits {
	int	limconst;
	wchar_t *limname;
	int	limdiv;
	wchar_t *limscale;
};

static void		doagain(void);
static void		echo(wchar_t, wchar_t **);
static struct limits	*findlim(wchar_t *);
static rlim_t		getval(struct limits *, wchar_t **);
static int		getword(wchar_t *);
static void		islogin(void);
static void		limtail(wchar_t *, wchar_t *);
static void		plim(struct limits *, wchar_t);
static void		preread_(void);
static void		reexecute(struct command *);
static int		setlim(struct limits *, wchar_t, rlim_t);
static void		toend(void);
static void		unsetenv(wchar_t *);

/*
 * C shell
 */

static void
dolabel(void)
{
#ifdef TRACE
	tprintf("TRACE- dolabel()\n");
#endif
}

static	struct biltins label = { S_, (bf_t)dolabel, 0, 0 };
static	struct biltins foregnd = { S_Pjob, (bf_t)dofg1, 0, 0 };
static	struct biltins backgnd = { S_PjobAND, (bf_t)dobg1, 0, 0 };

static void
preread_(void)
{
#ifdef TRACE
	tprintf("TRACE- preread()\n");
#endif
	whyles->w_end = -1;
	if(setintr)
	    (void)sigsetmask(sigblock(0) & ~sigmask(SIGINT));
	search(ZBREAK, 0, (wchar_t *)0);
	if(setintr)
	    (void)sigblock(sigmask(SIGINT));
	whyles->w_end = btell();
}


struct biltins *
isbfunc(struct command *t)
{
	register wchar_t *cp = t->t_dcom[0];
	register struct biltins *bp, *bp1, *bp2;
	register int i;

#ifdef TRACE
	tprintf("TRACE- isbfunc()\n");
#endif
	if(lastchr(cp) == ':') {
	    label.bname = cp;
	    return(&label);
	}
	if(*cp == '%') {
	    if(t->t_dflg & FAND) {
		t->t_dflg &= ~FAND;
		backgnd.bname = cp;
		return(&backgnd);
	    }
	    foregnd.bname = cp;
	    return(&foregnd);
	}
	/*
	 * Binary search
	 * Bp1 is the beginning of the current search range.
	 * Bp2 is one past the end.
	 */
	for(bp1 = bfunc, bp2 = bfunc + nbfunc; bp1 < bp2;) {
	    bp = bp1 + ((bp2 - bp1) >> 1);
	    if( !(i = *cp - *bp->bname) && !(i = wscmp(cp, bp->bname)) )
		return(bp);
	    if(i < 0)
		bp2 = bp;
	    else
		bp1 = bp + 1;
	}
	return(0);
}

void
func(struct command *t, struct biltins *bp)
{
	int i;

#ifdef TRACE
	tprintf("TRACE- func()\n");
#endif
	xechoit(t->t_dcom);
	setname(bp->bname);
	i = blklen(t->t_dcom) - 1;
	if(i < bp->minargs)
	    bferr(gettxt(_SGI_DMMX_csh_2fewargs, "Too few arguments"));
	if(i > bp->maxargs)
	    bferr(gettxt(_SGI_DMMX_csh_2manyargs, "Too many arguments"));
	(*bp->bfunct)(t->t_dcom, t);
}

void
doonintr(wchar_t **v)
{
	register wchar_t *cp;
	register wchar_t *vv = v[1];

#ifdef TRACE
	tprintf("TRACE- doonintr()\n");
#endif
	if(parintr == SIG_IGN)
	    return;
	if(setintr && intty)
	    err_notfromtty();
	cp = gointr, gointr = 0, xfree(cp);
	if( !vv) {
	    if(setintr)
		(void)sigblock(sigmask(SIGINT));
	    else
		(void)signal(SIGINT, SIG_DFL);
	    gointr = 0;
	} else if(eq((vv = strip(vv)), S_MINUS)) {
	    (void) signal(SIGINT, SIG_IGN);
	    gointr = S_MINUS;
	} else {
	    gointr = savestr(vv);
	    (void) signal(SIGINT, pintr);
	}
}

void
donohup(void)
{
#ifdef TRACE
	tprintf("TRACE- donohup()\n");
#endif
	if(intty)
	    err_notfromtty();
	if(setintr == 0) {
	    (void) signal(SIGHUP, SIG_IGN);
#ifdef CC
	    submit(getpid());
#endif
	}
}

void
dozip(void)
{
}

void
prvars(void)
{
#ifdef TRACE
	tprintf("TRACE- prvars()\n");
#endif
	plist(&shvhed);
}

void
doalias(wchar_t **v)
{
	register struct varent *vp;
	register wchar_t *p;

#ifdef TRACE
	tprintf("TRACE- doalias()\n");
#endif
	v++;					/* 'alias' already checked */
	p = *v++;
	if( !p)
	    plist(&aliases);
	else if( !*v) {
	    vp = adrof1(strip(p), &aliases);
	    if(vp)
		blkpr(vp->vec), shprintf("\n");
	} else {
	    if(eq(p, S_alias) || eq(p, S_unalias)) {
		setname(p);
		bferr(gettxt(_SGI_DMMX_csh_xalias,
		    "Too dangerous to alias that"));
	    }
	    set1(strip(p), saveblk(v), &aliases);
	}
}

void
unalias(wchar_t **v)
{
#ifdef TRACE
	tprintf("TRACE- unalias()\n");
#endif
	unset1(v, &aliases);
}

void
dologout(void)
{
#ifdef TRACE
	tprintf("TRACE- dologout()\n");
#endif
	islogin();
	goodbye();
}

void
dologin(wchar_t **v)
{
	register char *v_;

#ifdef TRACE
	tprintf("TRACE- dologin()\n");
#endif
	islogin();
	rechist();
	(void)signal(SIGTERM, parterm);
	if(v[1])			
	    v_ = tstostr(NOSTR, v[1], 0);	/* No need to free */
	else
	    v_ = 0;
	execl("/bin/login", "login", v_, 0);
	untty();
	done(1);
}

#ifdef NEWGRP
void
donewgrp(wchar_t **v)
{
	register char *v_;

#ifdef TRACE
	tprintf("TRACE- donewgrp()\n");
#endif
	if( !chkstop && setintr)
	    panystop(0);
	(void)signal(SIGTERM, parterm);

	if(v[1])
	    v_ = tstostr(NOSTR, v[1], 0);	/* No need to free */
	else
	    v_ = 0;
	execl("/bin/newgrp", "newgrp", v_, 0);
	execl("/usr/bin/newgrp", "newgrp", v_, 0);
	untty();
	done(1);
}
#endif

static void
islogin(void)
{
#ifdef TRACE
	tprintf("TRACE- islogin()\n");
#endif
	if( !chkstop && setintr) {
	    panystop(0);
	}
	if(loginsh)
	    return;
	err_notlogin();
}

void
doif(wchar_t **v, struct command *kp)
{
	register int i;
	register wchar_t **vv;

#ifdef TRACE
	tprintf("TRACE- doif()\n");
#endif
	v++;
	i = exp(&v);
	vv = v;
	if(*vv == NOSTR)
	    bferr(gettxt(_SGI_DMMX_csh_emptyIF, "Empty if"));
	if(eq(*vv, S_then)) {
	    if(*++vv)
		bferr(gettxt(_SGI_DMMX_csh_ImprTHEN, "Improper then"));
	    setname(S_then);
	    /*
	     * If expression was zero, then scan to else,
	     * otherwise just fall into following code.
	     */
	    if( !i)
		search(ZIF, 0, (wchar_t *)0);
	    return;
	}
	/*
	 * Simple command attached to this if.
	 * Left shift the node in this tree, munging it
	 * so we can reexecute it.
	 */
	if(i) {
	    lshift(kp->t_dcom, vv - kp->t_dcom);
	    reexecute(kp);
	    donefds();
	}
}

/*
 * Reexecute a command, being careful not
 * to redo i/o redirection, which is already set up.
 */
static void
reexecute(struct command *kp)
{
#ifdef TRACE
	tprintf("TRACE- reexecute()\n");
#endif
	kp->t_dflg &= FSAVE;
	kp->t_dflg |= FREDO;
	/*
	 * If tty is still ours to arbitrate, arbitrate it;
	 * otherwise dont even set pgrp's as the jobs would
	 * then have no way to get the tty (we can't give it
	 * to them, and our parent wouldn't know their pgrp, etc.
	 */
	execute(kp, tpgrp > 0 ? tpgrp : -1);
}

void
doelse(void)
{
#ifdef TRACE
	tprintf("TRACE- doelse()\n");
#endif
	search(ZELSE, 0, (wchar_t *)0);
}

void
dogoto(wchar_t **v)
{
	register struct whyle *wp;
	register wchar_t *lp;

#ifdef TRACE
	tprintf("TRACE- dogoto()\n");
#endif

	/*
	 * While we still can, locate any unknown ends of existing loops.
	 * This obscure code is the WORST result of the fact that we
	 * don't really parse.
	 */
	for (wp = whyles; wp; wp = wp->w_next)
		if (wp->w_end == 0) {
			search(ZBREAK, 0, (wchar_t *)0);
			wp->w_end = btell();
		} else
			bseek(wp->w_end);
	search(ZGOTO, 0, lp = globone(v[1]));
	xfree(lp);
	/*
	 * Eliminate loops which were exited.
	 */
	wfree();
}

void
doswitch(wchar_t **v)
{
	register wchar_t *cp, *lp;

#ifdef TRACE
	tprintf("TRACE- doswitch()\n");
#endif
	v++;
	if( !*v || (*(*v++) != '('))
	    goto syntax;
	cp = (**v == ')')? S_ : *v++;
	if(*(*v++) != ')')
	    v--;
	if (*v)
syntax:
	    syntaxerr();
	search(ZSWITCH, 0, lp = globone(cp));
	xfree(lp);
}

void
dobreak(void)
{
#ifdef TRACE
	tprintf("TRACE- dobreak()\n");
#endif
	if(whyles)
	    toend();
	else
	    err_notinwf();
}

void
doexit(wchar_t **v)
{
#ifdef TRACE
	tprintf("TRACE- doexit()\n");
#endif
	if( !chkstop) {
	    panystop(0);
	}
	/*
	 * Don't DEMAND parentheses here either.
	 */
	v++;
	if(*v) {
	    set(S_status, putn(exp(&v)));
	    if(*v)
		err_experr();
	}
	btoeof();
	if(intty)
	    (void)close(SHIN);
}

void
doforeach(wchar_t **v)
{
	register wchar_t *cp;
	register struct whyle *nwp;

#ifdef TRACE
	tprintf("TRACE- doforeach()\n");
#endif
	v++;
	cp = strip(*v);
	while (*cp && alnum(*cp))
		cp++;
	if(*cp || !letter(**v))
	    bferr(gettxt(_SGI_DMMX_csh_invvar, "Invalid variable"));
	cp = *v++;
	if (v[0][0] != '(' || v[blklen(v)-1][0] != ')')
	    bferr(gettxt(_SGI_DMMX_csh_wordsned, "Words not ()'ed"));
	v++;
	gflag = 0, tglob(v);
	v = glob(v);
	if (v == 0)
	    err_nomatch();
	nwp = (struct whyle *)salloc(1, sizeof(struct whyle));
	nwp->w_fe = nwp->w_fe0 = v; gargv = 0;
	nwp->w_start = btell();
	nwp->w_fename = savestr(cp);
	nwp->w_next = whyles;
	whyles = nwp;

	/*
	 * Pre-read the loop so as to be more
	 * comprehensible to a terminal user.
	 */
	if(intty)
	    preread_();
	doagain();
}

void
dowhile(wchar_t **v)
{
	register int status;
	register struct whyle *nwp;
	register bool again;

#ifdef TRACE
	tprintf("TRACE- dowhile()\n");
#endif
	again = (whyles
		&& (whyles->w_start == lineloc)
		&& (whyles->w_fename == 0));
	v++;

	/*
	 * Implement prereading here also, taking care not to
	 * evaluate the expression before the loop has been read up
	 * from a terminal.
	 */
	if(intty && !again)
	    status = !exp0(&v, 1);
	else
	    status = !exp(&v);
	if(*v)
	    err_experr();
	if( !again) {
	    nwp = (struct whyle *)salloc(1, sizeof(struct whyle));
	    nwp->w_start = lineloc;
	    nwp->w_end = 0;
	    nwp->w_next = whyles;
	    whyles = nwp;
	    if(intty) {
		preread_();			/* tty preread */
		doagain();
		return;
	    }
	}
	if(status)
	    toend();				/* ain't gonna loop no more */
}

void
doend(void)
{
#ifdef TRACE
	tprintf("TRACE- doend()\n");
#endif
	if( !whyles)
	    err_notinwf();
	whyles->w_end = btell();
	doagain();
}

void
docontin(void)
{
#ifdef TRACE
	tprintf("TRACE- docontin()\n");
#endif
	if( !whyles)
	    err_notinwf();
	doagain();
}

static void
doagain(void)
{
#ifdef TRACE
	tprintf("TRACE- doagain()\n");
#endif
	/*
	 * Repeating a while is simple
	 */
	if( !whyles->w_fename) {
	    bseek(whyles->w_start);
	    return;
	}
	/*
	 * The foreach variable list actually has a spurious word
	 * ")" at the end of the w_fe list.  Thus we are at the
	 * of the list if one word beyond this is 0.
	 */
	if( !whyles->w_fe[1]) {
	    dobreak();
	    return;
	}
	set(whyles->w_fename, savestr(*whyles->w_fe++));
	bseek(whyles->w_start);
}

void
dorepeat(wchar_t **v, struct command *kp)
{
	register int i, omask;

#ifdef TRACE
	tprintf("TRACE- dorepeat()\n");
#endif
	i = getn(v[1]);
	if(setintr)
	    omask = sigblock(sigmask(SIGINT)) & ~sigmask(SIGINT);
	lshift(v, 2);
	while(i > 0) {
	    if(setintr)
		(void)sigsetmask(omask);
	    reexecute(kp);
	    --i;
	}
	donefds();
	if(setintr)
	    (void)sigsetmask(omask);
}

void
doswbrk(void)
{
#ifdef TRACE
	tprintf("TRACE- doswbrk()\n");
#endif
	search(ZBRKSW, 0, (wchar_t *)0);
}

int
srchx(wchar_t *cp)
{
	register struct srch *sp, *sp1, *sp2;
	register i;

#ifdef TRACE
	tprintf("TRACE- srchx()\n");
#endif
	/*
	 * Binary search
	 * Sp1 is the beginning of the current search range.
	 * Sp2 is one past the end.
	 */
	for(sp1 = srchn, sp2 = srchn + nsrchn; sp1 < sp2;) {
	    sp = sp1 + (sp2 - sp1 >> 1);
	    if( !(i = *cp - *sp->s_name) && !(i = wscmp(cp, sp->s_name)))
		return(sp->s_value);
	    if(i < 0)
		sp2 = sp;
	    else
		sp1 = sp + 1;
	}
	return(-1);
}

wchar_t Stype;
wchar_t *Sgoal;

void
search(int type, int level, wchar_t *goal)
{
	register wchar_t *aword;
	register wchar_t *cp;
	wchar_t wordbuf[CSHBUFSIZ];

#ifdef TRACE
	tprintf("TRACE- search()\n");
#endif
	aword = wordbuf;
	Stype = type; Sgoal = goal;
	if (type == ZGOTO)
		bseek((off_t)0);
	do {
		if (intty && fseekp == feobp)
			shprintf("? "), flush();
		aword[0] = 0;
		(void) getword(aword);
		switch (srchx(aword)) {

		case ZELSE:
			if (level == 0 && type == ZIF)
				return;
			break;

		case ZIF:
			while (getword(aword))
				continue;
			if((type == ZIF || type == ZELSE) && eq(aword, S_then))
				level++;
			break;

		case ZENDIF:
			if (type == ZIF || type == ZELSE)
				level--;
			break;

		case ZFOREACH:
		case ZWHILE:
			if (type == ZBREAK)
				level++;
			break;

		case ZEND:
			if (type == ZBREAK)
				level--;
			break;

		case ZSWITCH:
			if (type == ZSWITCH || type == ZBRKSW)
				level++;
			break;

		case ZENDSW:
			if (type == ZSWITCH || type == ZBRKSW)
				level--;
			break;

		case ZLABEL:
			if (type == ZGOTO && getword(aword) && eq(aword, goal))
				level = -1;
			break;

		default:
			if (type != ZGOTO && (type != ZSWITCH || level != 0))
				break;
			if (lastchr(aword) != ':')
				break;
			aword[wslen(aword) - 1] = 0;
			if(type == ZGOTO && eq(aword, goal)
			    || type == ZSWITCH && eq(aword, S_default))
				level = -1;
			break;

		case ZCASE:
			if (type != ZSWITCH || level != 0)
				break;
			(void) getword(aword);
			if (lastchr(aword) == ':')
				aword[wslen(aword) - 1] = 0;
			cp = strip(Dfix1(aword));
			if (Gmatch(goal, cp))
				level = -1;
			xfree(cp);
			break;

		case ZDEFAULT:
			if (type == ZSWITCH && level == 0)
				level = -1;
			break;
		}
		(void) getword(NOSTR);
	} while (level >= 0);
}

static int
getword(wchar_t *wp)
{
	register int found = 0;
	int first;
	register wchar_t c, d;

#ifdef TRACE
	tprintf("TRACE- getword()\n");
#endif
	c = readc(1);
	d = 0;
	do {
		while (issp(c))
			c = readc(1);
		if (c == '#')
			do
				c = readc(1);
			while (c >= 0 && c != '\n');
		if (c < 0)
			goto past;
		if (c == '\n') {
			if (wp)
				break;
			return (0);
		}
		unreadc(c);
		found = 1;
		first = 1;
		do {
			c = readc(1);
			if (c == '\\' && (c = readc(1)) == '\n')
				c = ' ';
			if (c == '\'' || c == '"')
				if (d == 0)
					d = c;
				else if (d == c)
					d = 0;
			if (c < 0)
				goto past;
			if (wp) {
				*wp++ = c;
				*wp = '\0'; /* end the string before test */
			}
			if (!first && !d && c == '(') {
				if (wp) {
					unreadc(c);
					*--wp = '\0';
					return found;
				}
				else
					break;
			}
			first = 0;
		} while ((d || !issp(c) ) && c != '\n');
/*WAS:		} while ((d || c != ' ' && c != '\t') && c != '\n');*/
	} while (wp == 0);

	unreadc(c);
	if (found)
		*--wp = '\0';

	return (found);

past:
	switch(Stype) {
	    case ZIF:
		bferr(gettxt(_SGI_DMMX_csh_tenotfnd, "then/endif not found"));
	    case ZELSE:
		bferr(gettxt(_SGI_DMMX_csh_endif, "endif not found"));
	    case ZBRKSW:
	    case ZSWITCH:
		bferr(gettxt(_SGI_DMMX_csh_endsw, "endsw not found"));
	    case ZBREAK:
		bferr(gettxt(_SGI_DMMX_csh_end, "end not found"));
	    case ZGOTO:
		setname(Sgoal);
		bferr(gettxt(_SGI_DMMX_csh_label, "label not found"));
	}
	/*NOTREACHED*/
}

static void
toend(void)
{
#ifdef TRACE
	tprintf("TRACE- toend()\n");
#endif
	if (whyles->w_end == 0) {
		search(ZBREAK, 0, (wchar_t *)0);
		whyles->w_end = btell() - 1;
	} else
		bseek(whyles->w_end);
	wfree();
}

void
wfree(void)
{
	off_t o = btell();

#ifdef TRACE
	tprintf("TRACE- wfree()\n");
#endif
	while (whyles) {
		register struct whyle *wp = whyles;
		register struct whyle *nwp = wp->w_next;

		if (o >= wp->w_start && (wp->w_end == 0 || o < wp->w_end))
			break;
		if (wp->w_fe0)
			blkfree(wp->w_fe0);
		if (wp->w_fename)
			xfree(wp->w_fename);
		xfree(wp);
		whyles = nwp;
	}
}

void
doecho(wchar_t **v)
{

#ifdef TRACE
	tprintf("TRACE- doecho()\n");
#endif
	echo(' ', v);
}

void
doglob(wchar_t **v)
{

#ifdef TRACE
	tprintf("TRACE- doglob()\n");
#endif
	echo(0, v);
	flush();
}

static void
echo(wchar_t sep, wchar_t **v)
{
	register wchar_t *cp;
	int nonl = 0;

#ifdef TRACE
	tprintf("TRACE- echo()\n");
#endif
	if (setintr)
		(void) sigsetmask(sigblock(0) & ~sigmask(SIGINT));
	v++;
	if (*v == 0) {
		if (sep)
			wputchar('\n');
		return;
	}
	gflag = 0, tglob(v);
	if (gflag) {
		v = glob(v);
		if (v == 0)
			err_nomatch();
	} else
		trim(v);
	if((sep == ' ') && *v && !wscmp(*v, S_n))
		nonl++, v++;
	while (cp = *v++) {
		register int c;

		/* handle back-slash processing */
		while (c = *cp++) {
			if (c == '\\')
				switch (c = *cp++) {
				  case 'c':
					nonl++;
					break;;
				  case 'b':
					wputchar('\b' | QUOTE);
					break;
				  case 'f':
					wputchar('\f' | QUOTE);
					break;
				  case 'n':
					wputchar('\n' | QUOTE);
					break;
				  case 'r':
					wputchar('\r' | QUOTE);
					break;
				  case 't':
					wputchar('\t' | QUOTE);
					break;
				  case '\\':
					wputchar('\\' | QUOTE);
					break;
				  case '\000':
					wputchar('\\' | QUOTE);
					cp--;
					break;
				  /*
				   * pdc: change to allow \0xxx, which is
				   * what /bin/echo takes, and \nnn, which
				   * is the irix 4.0 csh syntax.  Basically,
				   * if we see a leading zero, don't count
				   * it.
				   */
				  default:
					if (c >= '0' && c <= '7') { /* 1 */
					  int val;

					  if (c == '0') {  /* echo compat */
					    c = *cp++;		/* new 1 */
					  }
					  val = c - '0';
					  c = *cp;
					  if (c >= '0' && c <= '7') { /* 2 */
					    val = val * 8 + c - '0';
					    cp++;
					    c = *cp;
					    if (c >= '0' && c <= '7') { /* 3 */
					      val = val * 8 + c - '0';
					      cp++;
					    }
					  }
					  wputchar((wchar_t)(val | QUOTE));
					} else {
						wputchar('\\' | QUOTE);
						wputchar((wchar_t)(c | QUOTE));
					}
					break;
				}
			else
				wputchar((wchar_t)(c | QUOTE));
		}
		if (*v)
			wputchar((wchar_t)(sep | QUOTE));
	}
	if (sep && nonl == 0)
		wputchar('\n');
	else
		flush();
	if (setintr)
		(void) sigblock(sigmask(SIGINT));
	if (gargv)
		blkfree(gargv), gargv = 0;
}

extern char **environ; 

/*
 * Check if the environment variable vp affects this csh's behavior
 * and therefore we should call setlocale() or not.
 */
static bool
islocalevar(wchar_t *vp)
{      
	static wchar_t *categories_we_care[] = {
		S_LANG,
		S_LC_CTYPE,
		S_LC_MESSAGES,
		NOSTR
	};
	register wchar_t **p;

	p = categories_we_care;
	do {
	    if( !wscmp(vp, *p))
		return(1);
	} while(*(++p));
	return(0);
}

void
dosetenv(wchar_t **v)
{
	register char **ep;
	register wchar_t *vp, *lp;
	char chbuf[CSHBUFSIZ];

#ifdef TRACE
	tprintf("TRACE- dosetenv()\n");
#endif
	v++;
	if( !(vp = *v++)) {
	    if(setintr)
		(void)sigsetmask(sigblock(0) & ~ sigmask(SIGINT));
	    for(ep = environ; *ep; ep++)
		shprintf("%s\n", *ep);
	    return;
	}
	if( !(lp = *v++))
	    lp = S_;
	setenv(vp, lp = globone(lp));
	if(eq(vp, S_PATH)) {
	    importpath(lp);
	    dohash();
	} else {
	    /*
	     * if locale is affected, change it
	     */
	    if(islocalevar(vp)) {
		if( !setlocale(LC_ALL, "") && intty ) {
		    showstr(MM_INFO,
			gettxt(_SGI_DMMX_csh_illlocale,
			    "%s: Invalid locale - csh locale unchanged"),
			tstostr(chbuf, lp, NOFLAG));
		}
	    }
	}
	xfree(lp);
}

void
dounsetenv(wchar_t **v)
{
	bool	locale_changed=0;
#ifdef TRACE
	tprintf("TRACE- dounsetenv()\n");
#endif
	v++;
	do{
		unsetenv(*v);
		if(islocalevar(*v++)) locale_changed=1;
	}while (*v);
	if(locale_changed) setlocale(LC_ALL, "");/* Hope no error! */
}

void
setenv(wchar_t *name, wchar_t *val)
{
	register wchar_t *cp, *ep;
	register char *s;

#ifdef TRACE
	tprintf("TRACE- setenv(%t, %t)\n", name, val);
#endif
	cp = strspl(S_EQ, val);
	ep = strspl(name, cp);
	xfree(cp);
	s = tstostr(NOSTR, ep, NOFLAG);
	xfree(ep);
	putenv(s);
}

static void
unsetenv(wchar_t *name)
{
	register char **ep = environ;
	register char **oep = ep;
	register int n;
	char *dp;
	char *cp_;	/* tmp use */

#ifdef TRACE
	tprintf("TRACE- unsetenv()\n");
#endif
	for(; *ep; ep++) {
	    if((n = cmpmbwc(name, *ep, &dp)) < 0) {
		illmbchar(*ep);
		illenvvar(*ep);
		continue;
	    }
	    if(name[n] || (*dp != '='))
		continue;
	    cp_ = *ep;
	    *ep = 0;
	    environ = blkspl_(environ, ep+1);
	    *ep = cp_;
	    xfree(cp_);
	    xfree(oep);
	    return;
	}
}

void
doumask(wchar_t **v)
{
	register wchar_t *cp = v[1];
	register int i;

#ifdef TRACE
	tprintf("TRACE- dounmask()\n");
#endif
	if (cp == 0) {
		i = (int)umask(0);
		(void) umask(i);
		shprintf("%o\n", i);
		return;
	}
	i = 0;
	while (digit(*cp) && *cp != '8' && *cp != '9')
		i = i * 8 + *cp++ - '0';
	if (*cp || i < 0 || i > 0777)
		bferr(gettxt(_SGI_DMMX_csh_imprmask, "Improper mask"));
	(void) umask(i);
}

struct limits limits[] = {
	RLIMIT_CPU,	S_cputime/*"cputime"*/,1,S_seconds/*"seconds"*/,
	RLIMIT_FSIZE,	S_filesize/*"filesize"*/,1024,S_kbytes/*"kbytes"*/,
	RLIMIT_DATA,	S_datasize/*"datasize"*/,1024,S_kbytes/*"kbytes"*/,
	RLIMIT_STACK,	S_stacksize/*"stacksize"*/,1024,S_kbytes/*"kbytes"*/,
	RLIMIT_CORE,	S_coredumpsize/*"coredumpsize"*/,1024,S_kbytes/*"kbytes"*/,
	RLIMIT_RSS,	S_memorysize/*"memoryuse"*/,	1024,S_kbytes/*"kbytes*/,
#ifdef RLIMIT_NOFILE	/* SunOS 4.1 and later. */
	RLIMIT_NOFILE,	S_descriptors,	1,	S_,
#endif

#ifdef RLIMIT_VMEM
	RLIMIT_VMEM,	S_vmemoryuse,	1024,	S_kbytes,
#endif
#ifdef RLIMIT_PTHREAD
	RLIMIT_PTHREAD,	S_threads,	1,	S_,
#endif

	-1,		0,
};

static struct limits *
findlim(wchar_t *cp)
{
	register struct limits *lp, *res;

#ifdef TRACE
	tprintf("TRACE- findlim()\n");
#endif
	res = 0;
	for (lp = limits; lp->limconst >= 0; lp++)
		if (prefix(cp, lp->limname)) {
			if (res)
				ambiguous();
			res = lp;
		}
	if (res)
		return (res);
	bferr(gettxt(_SGI_DMMX_csh_nolimit, "No such limit"));
	/*NOTREACHED*/
}

void
dolimit(wchar_t **v)
{
	wchar_t hard = 0;
	register struct limits *lp;
	register rlim_t limit;

#ifdef TRACE
	tprintf("TRACE- dolimit()\n");
#endif
	v++;
	if (*v && eq(*v, S_h/*"-h"*/)) {
		hard = 1;
		v++;
	}
	if (*v == 0) {
		for (lp = limits; lp->limconst >= 0; lp++)
			plim(lp, hard);
		return;
	}
	lp = findlim(v[0]);
	if (v[1] == 0) {
		plim(lp,  hard);
		return;
	}

	limit = (rlim_t) getval(lp, v+1);
	if (setlim(lp, hard, limit) < 0)
		error(NOSTR);
	
}

static rlim_t
getval(struct limits *lp, wchar_t **v)
{
	register double f;
	wchar_t *cp = *v++;

#ifdef TRACE
	tprintf("TRACE- getval()\n");
#endif
	f = atof_(cp);
	while (digit(*cp) || *cp == '.' || *cp == 'e' || *cp == 'E')
		cp++;
	if (*cp == 0) {
		if (*v == 0)
			return ((rlim_t)(f+0.5) * lp->limdiv);
		cp = *v;
	}
	switch (*cp) {

	case ':':
		if (lp->limconst != RLIMIT_CPU)
			goto badscal;
		return ((rlim_t)(f * 60.0 + atof_(cp+1)));

	case 'h':
		if (lp->limconst != RLIMIT_CPU)
			goto badscal;
		limtail(cp, S_hours/*"hours"*/);
		f *= 3600.;
		break;

	case 'm':
		if (lp->limconst == RLIMIT_CPU) {
			limtail(cp, S_minutes/*"minutes"*/);
			f *= 60.;
			break;
		}
	case 'M':
		if (lp->limconst == RLIMIT_CPU)
			goto badscal;
		*cp = 'm';
		limtail(cp, S_megabytes/*"megabytes"*/);
		f *= 1024.*1024.;
		break;

	case 's':
		if (lp->limconst != RLIMIT_CPU)
			goto badscal;
		limtail(cp, S_seconds/*"seconds"*/);
		break;

	case 'k':
		if (lp->limconst == RLIMIT_CPU)
			goto badscal;
		limtail(cp, S_kbytes/*"kbytes"*/);
		f *= 1024;
		break;

	case 'u':
		limtail(cp, S_unlimited/*"unlimited"*/);
		return (RLIM_INFINITY);

	default:
badscal:
		bferr(gettxt(_SGI_DMMX_csh_illscale,
		    "Improper or unknown scale factor"));
	}

	return ((rlim_t)(f+0.5));
}

static void
limtail(wchar_t *cp, wchar_t *str0)
{
	register wchar_t *str = str0;
	char chbuf[CSHBUFSIZ];

#ifdef TRACE
	tprintf("TRACE- limtail()\n");
#endif
	while(*cp && *cp == *str)
	    cp++, str++;
	if(*cp)
	    error(gettxt(_SGI_DMMX_csh_badscal,
		    "Bad scaling; did you mean ``%s''?"),
		tstostr(chbuf, str0, NOFLAG));
}

static void
plim(struct limits *lp, wchar_t hard)
{
	struct rlimit rlim;
	rlim_t limit;

#ifdef TRACE
	tprintf("TRACE- plim()\n");
#endif
	shprintf("%t \t", lp->limname);

	(void) getrlimit(lp->limconst, &rlim);

	limit = hard ? rlim.rlim_max : rlim.rlim_cur;
	if (limit == RLIM_INFINITY)
		shprintf("unlimited");
	else if (lp->limconst == RLIMIT_CPU)
		psecs(limit);
	else
		shprintf("%lld %t", limit / lp->limdiv, lp->limscale);
	shprintf("\n");
}

void
dounlimit(wchar_t **v)
{
	register struct limits *lp;
	int err = 0;
	wchar_t hard = 0;

#ifdef TRACE
	tprintf("TRACE- dounlimit()\n");
#endif
	v++;
	if (*v && eq(*v, S_h/*"-h"*/)) {
		hard = 1;
		v++;
	}
	if (*v == 0) {
		for (lp = limits; lp->limconst >= 0; lp++)
			if (setlim(lp, hard, RLIM_INFINITY) < 0)
				err++;
		if (err)
			error(NULL);
		return;
	}
	while (*v) {
		lp = findlim(*v++);
		if (setlim(lp, hard, RLIM_INFINITY) < 0)
			error(NULL);
	}
}

static int
setlim(struct limits *lp, wchar_t hard, rlim_t limit)
{
	struct rlimit rlim;

#ifdef TRACE
	tprintf("TRACE- setlim()\n");
#endif

	(void) getrlimit(lp->limconst, &rlim);

	if (hard)
		rlim.rlim_max = limit;
  	else if (limit == RLIM_INFINITY && geteuid() != 0)
 		rlim.rlim_cur = rlim.rlim_max;
 	else
 		rlim.rlim_cur = limit;

	if (setrlimit(lp->limconst, &rlim) < 0) {
		shprintf("%t: %t: Can't %s%s limit\n", bname, lp->limname,
		    limit == RLIM_INFINITY ? "remove" : "set",
		    hard ? " hard" : "");
		return (-1);
	}
	return (0);
}

void
dosuspend(void)
{
	int ctpgrp;
	void (*old)();

#ifdef TRACE
	tprintf("TRACE- dosuspend()\n");
#endif
	if (loginsh)
	    error(gettxt(_SGI_DMMX_csh_cantsusp,
		"Can't suspend a login shell (yet)"));
	untty();
	old = signal(SIGTSTP, SIG_DFL);
	(void) kill(0, SIGTSTP);
	/* the shell stops here */
	(void) signal(SIGTSTP, old);
	if (tpgrp != -1) {
retry:
		ctpgrp = tcgetpgrp(FSHTTY);
		if (ctpgrp != opgrp) {
			old = signal(SIGTTIN, SIG_DFL);
			(void) kill(0, SIGTTIN);
			(void) signal(SIGTTIN, old);
			goto retry;
		}
		(void) setpgid(0, shpgrp);
		(void) tcsetpgrp(FSHTTY, shpgrp);
	}
}

void
doeval(wchar_t **v)
{
	wchar_t **oevalvec = evalvec;
	wchar_t *oevalp = evalp;
	jmp_buf osetexit;
	volatile int reenter;
	wchar_t **gv = 0;

#ifdef TRACE
	tprintf("TRACE- doeval()\n");
#endif
	v++;
	if (*v == 0)
		return;
	gflag = 0, tglob(v);
	if (gflag) {
		gv = v = glob(v);
		gargv = 0;
		if (v == 0)
			err_nomatch();
		v = copyblk(v);
	} else
		trim(v);
	getexit(osetexit);
	reenter = 0;
	setexit();
	reenter++;
	if (reenter == 1) {
		evalvec = v;
		evalp = 0;
		process(0);
	}
	evalvec = oevalvec;
	evalp = oevalp;
	doneinp = 0;
	if (gv)
		blkfree(gv);
	resexit(osetexit);
	if (reenter >= 2)
		error(NULL);
}