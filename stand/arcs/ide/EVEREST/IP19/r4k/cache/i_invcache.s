/*
 *
 * Copyright 1991,1992 Silicon Graphics, Inc.
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

#ident "$Revision: 1.1 $"



#include "asm.h"
#include "regdef.h"
#include "cpu.h"

	.globl icache_linesize
/*
 *		I n v C a c h e _ I ( )
 *
 * InvCache_I - Invalidates n Primary Icache Lines by writing a zero into
 * the tag.
 *
 * Register Used:
 *	a0 - Address to Invalidate
 *	a1 - number of lines to Invalidate
 *	t0 - mask for bits 31-29
 *	t1 - Kseg1 mask
 *	
 */
LEAF(InvCache_I)
	.set	noreorder

	/* Invalidate primary data cache */

	li	t0, 0x1fffffff		/* mask off top bits */	
	and	a0, t0			/**/
	li	t1, 0xa0000000		/* Address to write, avoid tlb misses*/
	or	a0, t1			/* put address into kseg1 space*/
	lw	t0, icache_linesize	/* cache line size */

	mtc0	zero,C0_TAGLO		/* Set tag low register */
	nop
1:
	cache	Index_Store_Tag_I,0(a0) /* Write the tag location */

	addi	a1, -1			/* number of lines -1 */

	bne	a1, zero, 1b		/* Are we done? */
	add	a0, t0			/* BDSLOT, Next line */

	j	ra
	nop

	.set	reorder
END(InvCache_I)
