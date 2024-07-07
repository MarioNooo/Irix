/*
 * Performance Metrics Name Space Map
 * Built by pmgenmap from the file
 * pmnsmap.spec
 * on Wed Oct 22 16:15:03 EST 1997
 *
 * Do not edit this file!
 */
#ident "$Id: pmnsmap.h,v 1.2 1999/04/30 04:03:45 kenmcd Exp $"

char *_sample[] = {
#define LOADAV	0
	"kernel.all.load",
#define CPU_USER	1
	"kernel.all.cpu.user",
#define CPU_KERNEL	2
	"kernel.all.cpu.sys",
#define CPU_SXBRK	3
	"kernel.all.cpu.sxbrk",
#define CPU_INTR	4
	"kernel.all.cpu.intr",
#define CPU_IDLE	5
	"kernel.all.cpu.idle",
#define CPU_WAIT	6
	"kernel.all.cpu.wait.total",
#define FREEMEM	7
	"mem.freemem",
#define RUNQ	8
	"kernel.all.runque",
#define RUNQ_OCC	9
	"kernel.all.runocc",
#define SWAPQ	10
	"kernel.all.swap.swpque",
#define SWAPQ_OCC	11
	"kernel.all.swap.swpocc",
#define SWAPOUT	12
	"swap.pagesout",
#define SYSCALL	13
	"kernel.all.syscall",
#define CONTEXTSW	14
	"kernel.all.pswitch",
#define INTR	15
	"kernel.all.intr.non_vme",
#define DKREAD	16
	"disk.all.read",
#define DKWRITE	17
	"disk.all.write",

};


char *_extra[] = {
#define PACK_IN	0
	"network.interface.in.packets",
#define PACK_OUT	1
	"network.interface.out.packets",

};
