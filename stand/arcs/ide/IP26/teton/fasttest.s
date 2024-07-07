/***********************************************************************
*
* fasttest:  a directed fast iu chip test 
*
* (c) 1994, Silicon Graphics, Inc.
************************************************************************
*
* Description:
*    This test tries to recreate the symptom for apparant iu hold time
*    that occurs during particular bcopy calls (under write syscall)
*    in a very small directed test.	
*
*    In original problem:
*       SrcAddr = 0x101312cf, DstAddr = 0xa8000000106f4000,  cnt = 0x1425
*	 Bad copy at 0x137f into the block (when SrcAddr=0x1013264e).
*	 src data = 0xff and dst data = 0xbf
*
************************************************************************/

/*  DO NOT CHANGE THIS UNLESS YOU UNDERSTAND IT.  IT WAS GENERATED BY THE
 * HARDWARE GUYS TO FIND A HARDWARE BUG.  IT IS CODE AND DATA DEPENDENT
 * SO BE CAREFULL!	jeffs.
 */

#include <regdef.h>
     .set noreorder
     .text

#ifndef  _USE_SURESH_TEST
    .globl fasttest
    .ent   fasttest 2
    .set   noreorder
.align 4
       nop       
       nop       
       nop       
fasttest:
        daddu   a3, a1, a2
16:
        lwl	t0,0(a0)
        lwr	t0,3(a0)
        lwl	t1,4(a0)
        lwr	t1,7(a0)
        sw	t0,0(a1)
        lwl	t2,8(a0)
        lwr	t2,11(a0)
        sw	t1,4(a1)
        lwl	t3,12(a0)
        lwr	t3,15(a0)
        daddiu	a0,a0,16
        sw	t2,8(a1)
        sw	t3,12(a1)
        daddiu	a1,a1,16
        bne	a3,a1,16b
	nop
	j	ra
        nop

.end fasttest
#else
    .globl fasttest
    .ent   fasttest 2
    .set   noreorder
.align 4
       nop       
       nop       
       nop       
fasttest:
        daddu   a3, a1, a2
	ori a2, $0, 0x10
	nada
	nada
	nada
16:
        ldl	t0,0(a0)
        ldr	t0,7(a0)
	nada
	nada
        sd	t0,0(a1)
        ldl	t2,8(a0)
        ldr	t2,15(a0)
	ssnop
	ssnop
	nada
        daddu	a0,a0,a2
	ssnop
        sd	t2,8(a1)
        daddiu	a1,a1,16
        bne	a3,a1,16b
        ori a2, $0, 0x20
	j	ra
        nop

.end fasttest
#endif