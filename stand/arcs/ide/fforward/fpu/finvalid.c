/*
 * fpu/finvalid.c
 *
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

#ident "$Revision: 1.16 $"

/*
 *					
 *	Floating Point Exerciser - basic functions with simple single
 *	invalid
 *					
 */

#include <sys/param.h>
#include <sys/cpu.h>
#include <sys/sbd.h>
#include <sys/fpu.h>
#include <fault.h>
#include <setjmp.h>
#include "libsk.h"
#include "libsc.h"
#include "uif.h"

static jmp_buf fault_buf;

#ifdef TFP
#define DIVIDEND_1	0x7fffffff
#define DIVIDEND_2	0xffffffff
#define FPUINVALID	0xfc0		/* all exceptions enabled , V cause */
#else
#define FPUINVALID	0x10f80		/* all exceptions enabled , V cause */
#endif
#define DIVIDEND	0
#if defined(TFP)
#define	SR_EXCEPT	(SR_CU0 | SR_CU1 | SR_IEC | SR_FR)
#elif _MIPS_SIM == _ABI64	/* R4K/10K */
#define	SR_EXCEPT	(SR_CU0 | SR_CU1 | SR_IEC | SR_KX | SR_FR)
#else
#define	SR_EXCEPT	(SR_CU0 | SR_CU1 | SR_IEC)
#endif

int
finvalid(void)
{
    volatile float f1, f2, f3;
    register unsigned int i1;
    volatile int fail;
    ulong status;

    fail = 0;
    status = GetSR();

    if (setjmp(fault_buf))
    {
	if (GetFPSR() != FPUINVALID) 
	    fail = 1;
	SetFPSR(0);

	i1 = (unsigned int)f1;
#if TFP
	/* TFP + various compiler revisions can produce different values */
	if (! ((i1 == DIVIDEND) || (i1 == DIVIDEND_1) || (i1 == DIVIDEND_2)) )
#else
	if (i1 != DIVIDEND)
#endif
	    fail = 1;
    }
    else
    {
	/* set the exception "goto" */
	set_nofault(fault_buf);

	/* clear cause register */
	set_cause(0);

	/* enable cache and fpu - cache ecc errors still enabled */
	SetSR(SR_EXCEPT);

	/* clear the FPSR */
	SetFPSR(0);

	/* set up fpu status register for exception */
	SetFPSR(FP_ENABLE);

	/* Convert to floating point */
	f1 = 0.0;
	f1 = f1/f1;

	DELAY(10);

	/* error if test does not generate an exception */
	fail = 1;
	nofault = 0;
    }

    /* return the status register to original state */
    SetSR(status);

    /* report any error */
    return(fail);
}
