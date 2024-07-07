/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1990, Silicon Graphics, Inc.               *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright law.  They  may  not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 **************************************************************************/

/*
 *  VC2 Diagnostics
 *  $Revision: 1.14 $
 */


#include <math.h>
#include <sys/types.h>
#include <sys/sema.h>
#include <sys/gfx.h>
#include "sys/ng1hw.h"
#include "sys/vc2.h"
#include "sys/ng1.h"
#include "sys/ng1_cmap.h"
#include "sys/xmap9.h"
#include "ide_msg.h"
#include "local_ng1.h"
#include "libsk.h"
#include "libsc.h"
#include "uif.h"

#ifndef NULL
#define NULL 0
#endif

extern struct ng1_info ng1_ginfo[];
extern Rex3chip *REX;
extern int REXindex;

/*
 * Disable vc2 cursor, did, and video timing functions 
 */

void vc2_off(void)
{
	int state;

	vc2GetReg (REX, VC2_DC_CONTROL, state);
	state &= ~(VC2_ENA_VIDEO | VC2_ENA_DIDS | VC2_ENA_CURS_FUNCTION);
	vc2SetReg (REX, VC2_DC_CONTROL, state);
}

/*
 * Enable vc2 cursor, did, and video timing functions 
 */

void vc2_on(void)
{
	int state;

	vc2GetReg (REX, VC2_DC_CONTROL, state);
	state |= (VC2_ENA_VIDEO | VC2_ENA_DIDS | VC2_ENA_CURS_FUNCTION);
	vc2SetReg (REX, VC2_DC_CONTROL, state);

}

#ifndef PROM
/*
 * wvc2() - write VC2 register
 *
 *	This is a tool to allow writing of arbitrary values to the various
 *	VC2 registers from the IDE command line.
 */
int ng1wvc2(int argc, char **argv)
{
	int reg;		/* VC2 register offset */
	int data;	  	/* VC2 register data */

	if(!ng1checkboard())
		return -1;

	if (argc < 3) {
		printf("usage: %s VC2_reg_ data\n", argv[0]);
		return -1;
	}
	atohex(argv[1], &reg);
	atohex(argv[2], &data);

	msg_printf(DBG,"Writing VC2 reg %d with %#04x\n", reg, data);
	vc2SetReg(REX,reg,data);
	return 0;
}


/*
 * rvc2() - read VC2 register
 *
 *	This is a tool to allow reading of values from the various
 *	VC2 registers from the IDE command line.
 */
int ng1rvc2(int argc, char **argv)
{
	int reg;	/* VC2 register offset */
	int data;   	/* VC2 register data */

	if(!ng1checkboard())
		return -1;

	if (argc < 2) {
		printf("usage: %s VC2_reg\n", argv[0]);
		return -1;
	}
	atohex(argv[1], &reg);

	vc2GetReg(REX,reg,data);
	msg_printf(DBG,"Reading VC2 reg %d returns %#02x\n", reg, data);
	return 0;
}

#endif /* !PROM */

int test_vc2_register(unsigned int reg, unsigned int pattern)
{
	unsigned int got;

	vc2SetReg(REX,reg,pattern);
	vc2GetReg(REX,reg,got);
	if (got != pattern) {
#if !PROM
		msg_printf(ERR, "Error reading from VC2 reg %d returned: %#04x, expected: %#04x\n", reg, got, pattern);
#endif
		return 1;
	}
	return 0;
}

int ng1vc2test(void)
{
	unsigned int pattern;
	int errors = 0;
	int i;

	if(!ng1checkboard())
		return -1;

	msg_printf(VRB, "Starting VC2 tests...\n");

	vc2_off();

	for (pattern = 0; pattern <= 0xffff; pattern += 0x5555) {
		errors += test_vc2_register(VC2_VIDEO_ENTRY_PTR, pattern);
		errors += test_vc2_register(VC2_CURS_ENTRY_PTR, pattern);
		errors += test_vc2_register(VC2_CURS_X_LOC, pattern);
		errors += test_vc2_register(VC2_CURS_Y_LOC, pattern);
		errors += test_vc2_register(VC2_CURRENT_CURS_X_LOC, pattern);
		errors += test_vc2_register(VC2_DID_ENTRY_PTR, pattern);
		errors += test_vc2_register(VC2_SCAN_LENGTH, pattern);
		errors += test_vc2_register(VC2_RAM_ADDR, pattern);
		errors += test_vc2_register(VC2_VT_FRAME_PTR, pattern);
		errors += test_vc2_register(VC2_VT_LINESEQ_PTR, pattern);
		errors += test_vc2_register(VC2_VT_LINES_IN_RUN, pattern);
		errors += test_vc2_register(VC2_VERTICAL_LINE_CTR, pattern);
		errors += test_vc2_register(VC2_CURS_TABLE_PTR, pattern);
		errors += test_vc2_register(VC2_WORKING_CURS_Y, pattern);
		errors += test_vc2_register(VC2_DID_FRAME_PTR, pattern);
		errors += test_vc2_register(VC2_DID_LINE_TABLE_PTR, pattern);
	}
	ng1_test_sram(0,0);		/* argv unused! */

	Ng1RegisterInit(REX, &ng1_ginfo[REXindex]);
	if (!errors) {
		msg_printf(INFO, "All of the VC2 register r/w tests have passed.\n");
		return 0;
	} else {
		msg_printf(ERR, "Total of %d errors detected in VC2 register r/w tests.\n", errors);
		return -1;
	}
}


#ifndef PROM

/*
 * Set vc2 cursor x,y position
 */

int ng1vc2cursor(int argc, char **argv)
{
	int x, y;

	if(!ng1checkboard())
		return -1;

	if (argc < 3) {
		printf("usage: %s x y\n", argv[0]);
		return -1;
	}
	atob(argv[1], &x);
	atob(argv[2], &y);

	vc2SetReg (REX, VC2_CURS_X_LOC, x);
	vc2SetReg (REX, VC2_CURS_Y_LOC, y);

	return 0;
}



    /*
     *  32 by 32 pixel arrow cursor
     */
static unsigned int arrow_32x32[] = {
	0x0C000000,
	0x0F000000,
	0x07C00000,
	0x07F00000,
	0x03FC0000,
	0x03FF0000,
	0x01F00000,
	0x01F00000,
	0x00C80000,
	0x00C40000,
	0x00420000,
	0x00410000,
	0x00008000,
	0x00004000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,	/* from here up is bit 0 */

	0x1E000000,	/* from here down is bit 1 */
	0x0F800000,
	0x0FE00000,
	0x07F80000,
	0x07FE0000,
	0x03FFC000,
	0x03FFC000,
	0x01FFC000,
	0x01FC0000,
	0x00FE0000,
	0x00F70000,
	0x00738000,
	0x0071C000,
	0x0070E000,
	0x00007000,
	0x00003000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000 };

	/* 
	 * 64 by 64 pixel sgi logo cursor
	 */
static char sgi64_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
   0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x3e, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xfe, 0x3f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0xfe,
   0x3f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x3f, 0xf0, 0x00, 0x00,
   0x00, 0x00, 0x1f, 0xfe, 0x3f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfe,
   0x3f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0xff, 0xfe, 0x3f, 0xff, 0x80, 0x00,
   0x00, 0x01, 0xff, 0x3e, 0x3e, 0x7f, 0xc0, 0x00, 0x00, 0x07, 0xfc, 0x3e,
   0x3e, 0x1f, 0xf0, 0x00, 0x00, 0x1f, 0xf8, 0x3e, 0x3e, 0x0f, 0xfc, 0x00,
   0x00, 0x3f, 0xe0, 0x3e, 0x3e, 0x03, 0xfe, 0x00, 0x00, 0xff, 0x80, 0x3e,
   0x3e, 0x00, 0xff, 0x80, 0x00, 0xfe, 0x00, 0x3e, 0x3e, 0x00, 0x3f, 0x80,
   0x01, 0xfc, 0x00, 0x3e, 0x3e, 0x00, 0x1f, 0xc0, 0x00, 0xff, 0x00, 0x3e,
   0x3e, 0x00, 0x7f, 0x80, 0x00, 0xff, 0xc0, 0x3e, 0x3e, 0x01, 0xff, 0x80,
   0x00, 0x3f, 0xf0, 0x3e, 0x3e, 0x07, 0xfe, 0x00, 0x02, 0x0f, 0xfc, 0x3e,
   0x3e, 0x1f, 0xf8, 0x20, 0x0f, 0x87, 0xff, 0x3e, 0x3e, 0x7f, 0xf0, 0xf8,
   0x1f, 0xe1, 0xff, 0xce, 0x39, 0xff, 0xc3, 0xfc, 0x1f, 0xf0, 0x7f, 0xf2,
   0x27, 0xff, 0x07, 0xfc, 0x3f, 0xfc, 0x1f, 0xfc, 0x1f, 0xfc, 0x1f, 0xfe,
   0x3f, 0xff, 0x07, 0xff, 0xff, 0xf0, 0x7f, 0xfe, 0x3f, 0xff, 0xc1, 0xff,
   0xff, 0xc1, 0xff, 0xfe, 0x3f, 0xff, 0xe0, 0xff, 0xff, 0x83, 0xff, 0xfe,
   0x3e, 0x7f, 0xf8, 0x3f, 0xfe, 0x0f, 0xff, 0x3e, 0x3e, 0x1f, 0xfe, 0x4f,
   0xf9, 0x3f, 0xfc, 0x3e, 0x3e, 0x07, 0xff, 0xb3, 0xe6, 0x7f, 0xf0, 0x3e,
   0x3e, 0x03, 0xff, 0xcc, 0x99, 0xff, 0xe0, 0x3e, 0x3e, 0x00, 0xff, 0xf0,
   0x07, 0xff, 0x80, 0x3e, 0x3e, 0x00, 0x3f, 0xfc, 0x1f, 0xfe, 0x00, 0x3e,
   0x3e, 0x00, 0x4f, 0xfe, 0x3f, 0xf9, 0x00, 0x3e, 0x3e, 0x01, 0xf3, 0xfe,
   0xbf, 0xe7, 0xc0, 0x3e, 0x3e, 0x07, 0xfd, 0xfe, 0xbf, 0x9f, 0xf0, 0x3e,
   0x3e, 0x1f, 0xfe, 0x7e, 0xbf, 0x3f, 0xfc, 0x3e, 0x3e, 0x7f, 0xf0, 0x3e,
   0xbe, 0x07, 0xff, 0x3e, 0x3f, 0xff, 0xc1, 0xbe, 0xbe, 0xc1, 0xff, 0xfe,
   0x3f, 0xff, 0x07, 0xbe, 0xbe, 0xf0, 0x7f, 0xfe, 0x3f, 0xfc, 0x1f, 0xbe,
   0x3e, 0xfc, 0x1f, 0xfe, 0x3f, 0xf0, 0x7f, 0xbe, 0x3e, 0xff, 0x07, 0xfe,
   0x3f, 0xc0, 0xff, 0xbe, 0x3e, 0xff, 0x81, 0xfe, 0x1f, 0x03, 0xff, 0xbe,
   0x3e, 0xff, 0xe0, 0x7c, 0x0c, 0x0f, 0xff, 0x3e, 0x3e, 0x7f, 0xf8, 0x18,
   0x00, 0x3f, 0xfc, 0x3e, 0x3e, 0x1f, 0xfe, 0x00, 0x00, 0xff, 0xf0, 0x3e,
   0x3e, 0x07, 0xff, 0x80, 0x01, 0xff, 0xc0, 0x3e, 0x3e, 0x01, 0xff, 0xc0,
   0x01, 0xff, 0x00, 0x3e, 0x3e, 0x00, 0x7f, 0xc0, 0x03, 0xfc, 0x00, 0x3e,
   0x3e, 0x00, 0x1f, 0xe0, 0x03, 0xfe, 0x00, 0x3e, 0x3e, 0x00, 0x3f, 0xe0,
   0x01, 0xff, 0x80, 0x3e, 0x3e, 0x00, 0xff, 0xc0, 0x01, 0xff, 0xe0, 0x3e,
   0x3e, 0x03, 0xff, 0xc0, 0x00, 0x7f, 0xf8, 0x3e, 0x3e, 0x0f, 0xff, 0x00,
   0x00, 0x1f, 0xfe, 0x3e, 0x3e, 0x3f, 0xfc, 0x00, 0x00, 0x07, 0xff, 0xbe,
   0x3e, 0xff, 0xf0, 0x00, 0x00, 0x01, 0xff, 0xfe, 0x3f, 0xff, 0xc0, 0x00,
   0x00, 0x00, 0x7f, 0xfe, 0x3f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xfe,
   0x3f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x3f, 0xf0, 0x00, 0x00,
   0x00, 0x00, 0x01, 0xfe, 0x3f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e,
   0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x1c, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	/* 
	 * 32 by 32 pixel hourglass cursor
	 */
static char hour32_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xfe,
   0x31, 0x00, 0x00, 0x8c, 0x32, 0x00, 0x00, 0x4c, 0x32, 0x00, 0x00, 0x4c,
   0x32, 0x00, 0x00, 0x4c, 0x32, 0x00, 0x00, 0x4c, 0x32, 0x00, 0x00, 0x4c,
   0x31, 0x00, 0x00, 0x8c, 0x30, 0xfe, 0x7f, 0x0c, 0x30, 0x7f, 0xfe, 0x0c,
   0x30, 0x3f, 0xfc, 0x0c, 0x30, 0x1f, 0xf8, 0x0c, 0x30, 0x07, 0xe0, 0x0c,
   0x30, 0x01, 0x80, 0x0c, 0x30, 0x01, 0x80, 0x0c, 0x30, 0x06, 0x60, 0x0c,
   0x30, 0x18, 0x18, 0x0c, 0x30, 0x20, 0x04, 0x0c, 0x30, 0x40, 0x02, 0x0c,
   0x30, 0x80, 0x01, 0x0c, 0x31, 0x00, 0x00, 0x8c, 0x32, 0x01, 0x80, 0x4c,
   0x32, 0x0c, 0xc0, 0x4c, 0x32, 0x0f, 0xf8, 0x4c, 0x32, 0xff, 0xff, 0x4c,
   0x33, 0xff, 0xff, 0xcc, 0x31, 0xff, 0xff, 0x8c, 0x7f, 0xff, 0xff, 0xfe,
   0x7f, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xfe,
   0x31, 0x00, 0x00, 0x8c, 0x32, 0x00, 0x00, 0x4c, 0x32, 0x00, 0x00, 0x4c,
   0x32, 0x00, 0x00, 0x4c, 0x32, 0x00, 0x00, 0x4c, 0x32, 0x00, 0x00, 0x4c,
   0x31, 0x00, 0x00, 0x8c, 0x30, 0xfe, 0x7f, 0x0c, 0x30, 0x7f, 0xfe, 0x0c,
   0x30, 0x3f, 0xfc, 0x0c, 0x30, 0x1f, 0xf8, 0x0c, 0x30, 0x07, 0xe0, 0x0c,
   0x30, 0x01, 0x80, 0x0c, 0x30, 0x01, 0x80, 0x0c, 0x30, 0x06, 0x60, 0x0c,
   0x30, 0x18, 0x18, 0x0c, 0x30, 0x20, 0x04, 0x0c, 0x30, 0x40, 0x02, 0x0c,
   0x30, 0x80, 0x01, 0x0c, 0x31, 0x00, 0x00, 0x8c, 0x32, 0x01, 0x80, 0x4c,
   0x32, 0x0c, 0xc0, 0x4c, 0x32, 0x0f, 0xf8, 0x4c, 0x32, 0xff, 0xff, 0x4c,
   0x33, 0xff, 0xff, 0xcc, 0x31, 0xff, 0xff, 0x8c, 0x7f, 0xff, 0xff, 0xfe,
   0x7f, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00
   };

/*
 * Set vc2 cursor type :
 * 0 : 32x32x2 glyph,
 * 1 : 64x64x1 glyph,
 * 2 : crosshair.
 */

int ng1vc2cursormode(int argc, char **argv)
{
	int mode;
	int state;
	unsigned short *glyph;

	if(!ng1checkboard())
		return -1;

	if (argc < 2) {
		printf("usage: %s mode (0|1|2|3)\n", argv[0]);
		return -1;
	}

	atob(argv[1], &mode);

	/* Ng1CursorInit(REX, 0xff, 0, 0, 0xff, 0xff, 0xff); */

	/* turn off the cursor */
	vc2GetReg (REX, VC2_DC_CONTROL, state);
	state &= ~(VC2_ENA_CURS_FUNCTION | VC2_ENA_CURS_DISPLAY );
	vc2SetReg (REX, VC2_DC_CONTROL, state);

	switch (mode) {
	    case 2:
		state |=  VC2_ENA_CROSS_CURS;
		state |= (VC2_ENA_CURS_FUNCTION | VC2_ENA_CURS_DISPLAY );
		break;
	    case 1:
		glyph = (unsigned short *) sgi64_bits;
		vc2LoadSRAM( REX, glyph, VC2_CURSOR_GLYPH_ADDR, 256 );
		state &=  ~VC2_ENA_CROSS_CURS;
		state |=  VC2_CURS_GLYPH_64;
		state |= (VC2_ENA_CURS_FUNCTION | VC2_ENA_CURS_DISPLAY );
		break;
	    case 0:
		glyph = (unsigned short *) arrow_32x32;
/*		glyph = (unsigned short *) hour32_bits; */
		vc2LoadSRAM( REX, glyph, VC2_CURSOR_GLYPH_ADDR, 256 );
		state &=  ~(VC2_ENA_CROSS_CURS | VC2_CURS_GLYPH_64);
		state |= (VC2_ENA_CURS_FUNCTION | VC2_ENA_CURS_DISPLAY );
		break;
	    /*
	     * Default action will turn off the cursor
	     */
	}

	/* Set the cursor entry pointer */
	vc2SetReg (REX, VC2_CURS_ENTRY_PTR, VC2_CURSOR_GLYPH_ADDR);

	/* Turn the cursor back on */
	vc2SetReg (REX, VC2_DC_CONTROL, state);

	return 0;
}

#endif	/* !PROM */
