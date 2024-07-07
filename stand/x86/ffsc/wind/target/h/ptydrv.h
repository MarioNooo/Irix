/* ptyDrv.h - header file for ptyDrv.c */

/* Copyright 1984-1992 Wind River Systems, Inc. */

/*
modification history
--------------------
01e,22sep92,rrr  added support for c++
01d,04jul92,jcf  cleaned up.
01c,26may92,rrr  the tree shuffle
01b,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed copyright notice
01a,05oct90,shl created.
*/

#ifndef __INCptyDrvh
#define __INCptyDrvh

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern STATUS 	ptyDevCreate (char *name, int rdBufSize, int wrtBufSize);
extern STATUS 	ptyDrv (void);

#else	/* __STDC__ */

extern STATUS 	ptyDevCreate ();
extern STATUS 	ptyDrv ();

#endif	/* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCptyDrvh */
