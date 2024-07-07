/*****************************************************************************
 * $Id: mvp7185.h,v 1.1 1996/11/16 00:36:39 travis Exp $
 *
 * Copyright 1995, Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics, Inc.;
 * the contents of this file may not be disclosed to third parties, copied or
 * duplicated in any form, in whole or in part, without the prior written
 * permission of Silicon Graphics, Inc.
 *
 * RESTRIRTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions
 * as set forth in subdivision (c)(1)(ii) of the Rights in Technical Data
 * and Computer Software clause at DFARS 252.227-7013, and/or in similar or
 * successor clauses in the FAR, DOD or NASA FAR Supplement. Unpublished -
 * rights reserved under the Copyright Laws of the United States.
 *
 *****************************************************************************/

/*
 * Interface module for 7185 Video Encoder
 */

/*
 *       7185  7185b
 * 0x5f  0x00  0x3a
 * 0x6e  0x95  0x92
 * (pal) 0xab  0xaa
 * 0x6f  0x06  0x60
 * 
 */
CHIPNAME(7185)

static i2c_chipreg_t chipregs_7185[] = {

 /* book: 0, dos: 0f */
 /* 11111, 0x80: color bars, 00: input (note: was 0x1f!) */
 /* mp: alpha, vp: data */
RT( "input port control",	IPC,	0x3a, 0x1f, 0x1f, 0x9f, 0	),

RT( "reserved",			RES,	0x3b, 0x00, 0x00, 0x00, NU ),
RT( "reserved",			RES,	0x3c, 0x00, 0x00, 0x00, NU ),
RT( "reserved",			RES,	0x3d, 0x00, 0x00, 0x00, NU ),
RT( "reserved",			RES,	0x3e, 0x00, 0x00, 0x00, NU ),
RT( "reserved",			RES,	0x3f, 0x00, 0x00, 0x00, NU ),
RT( "reserved",			RES,	0x40, 0x00, 0x00, 0x00, NU ),
RT( "reserved",			RES,	0x41, 0x00, 0x00, 0x00, NU ),

 /* 75% color bars */
			/* white */
RT( "osd lut y0",		OSDY0,	0x42, 0x6b, 0x6b, 0xff, 0	),
RT( "osd lut u0",		OSDU0,	0x43, 0x00, 0x00, 0xff, 0	),
RT( "osd lut v0",		OSDV0,	0x44, 0x00, 0x00, 0xff, 0	),

			/* yellow */
RT( "osd lut y1",		OSDY1,	0x45, 0x22, 0x22, 0xff, 0	),
RT( "osd lut u1",		OSDU1,	0x46, 0xac, 0xac, 0xff, 0	),
RT( "osd lut v1",		OSDV1,	0x47, 0x0e, 0x0e, 0xff, 0	),

			/* cyan */
RT( "osd lut y2",		OSDY2,	0x48, 0x03, 0x03, 0xff, 0	),
RT( "osd lut u2",		OSDU2,	0x49, 0x1d, 0x1d, 0xff, 0	),
RT( "osd lut v2",		OSDV2,	0x4a, 0xac, 0xac, 0xff, 0	),

			/* green */
RT( "osd lut y3",		OSDY3,	0x4b, 0xf0, 0xf0, 0xff, 0	),
RT( "osd lut u3",		OSDU3,	0x4c, 0xc8, 0xc8, 0xff, 0	),
RT( "osd lut v3",		OSDV3,	0x4d, 0xb9, 0xb9, 0xff, 0	),

			/* magenta */
RT( "osd lut y4",		OSDY4,	0x4e, 0xd4, 0xd4, 0xff, 0	),
RT( "osd lut u4",		OSDU4,	0x4f, 0x38, 0x38, 0xff, 0	),
RT( "osd lut v4",		OSDV4,	0x50, 0x47, 0x47, 0xff, 0	),

			/* red */
RT( "osd lut y5",		OSDY5,	0x51, 0xc1, 0xc1, 0xff, 0	),
RT( "osd lut u5",		OSDU5,	0x52, 0xe3, 0xe3, 0xff, 0	),
RT( "osd lut v5",		OSDV5,	0x53, 0x54, 0x54, 0xff, 0	),

			/* blue */
RT( "osd lut y6",		OSDY6,	0x54, 0xa3, 0xa3, 0xff, 0	),
RT( "osd lut u6",		OSDU6,	0x55, 0x54, 0x54, 0xff, 0	),
RT( "osd lut v6",		OSDV6,	0x56, 0xf2, 0xf2, 0xff, 0	),

			/* black */
RT( "osd lut y7",		OSDY7,	0x57, 0x90, 0x90, 0xff, 0	),
RT( "osd lut u7",		OSDU7,	0x58, 0x00, 0x00, 0xff, 0	),
RT( "osd lut v7",		OSDV7,	0x59, 0x00, 0x00, 0xff, 0	),

/* 0xaa from IDE, was 0x00 */
RT( "chroma phase",		CP,	0x5a, 0xaa, 0xaa, 0xff, 0	),

RT( "gain u",			GU,	0x5b, 0x81, 0x82, 0xff, 0	),
RT( "gain v",			GV,	0x5c, 0xbd, 0xb6, 0xff, 0	),
RT( "gain u/black level",	GUBL,	0x5d, 0x3c, 0x2d, 0xbf, 0	),
RT( "gain v/blank level",	GVBL,	0x5e, 0x3a, 0x3f, 0xbf, 0	),

RT( "X-Col_Select",		CCRS1,	0x5f, 0x3a, 0x3f, 0xff, 0	),

RT( "cross color reduction",	CCR,	0x60, 0x00, 0x00, 0xc0, 0	),

 /* dos: 1d; 0: ntsc, 2: pal, 8:rtc, 0, no rtc */
RT( "standard control",		SC,	0x61, 0x15, 0x06, 0x7f, 0	),

 /* dos:69, 0x80 <special>, */
RT( "burst amplitude",		BA,	0x62, 0xee, 0xce, 0xff, 0	),

 /* dos:1f */
RT( "subcarrier 0",		SC0,	0x63, 0x1f, 0xcb, 0xff, 0	),
RT( "subcarrier 1",		SC1,	0x64, 0x7c, 0x8a, 0xff, 0	),
RT( "subcarrier 2",		SC2,	0x65, 0xf0, 0x09, 0xff, 0	),
RT( "subcarrier 3",		SC3,	0x66, 0x21, 0x2a, 0xff, 0	),

RT( "cc odd field first",	CCOFF,	0x67, 0x00, 0x00, 0xff, 0	),
RT( "cc odd field second",	CCOFS,	0x68, 0x00, 0x00, 0xff, 0	),
RT( "cc even field first",	CCEFF,	0x69, 0x00, 0x00, 0xff, 0	),
RT( "cc even field second",	CCEFS,	0x6a, 0x00, 0x00, 0xff, 0	),

 /* dos: 91, c0:video, 40:alpha */
RT( "encod ctrl/ cc line",	ECCCL,	0x6b, 0x11, 0x15, 0xdf, 0	),

 /* dos:6d,  */
RT( "recv port control",	RPC,	0x6c, 0x6c, 0x6c, 0xff, 0	),

 /* dos:07, */
RT( "rcm/ cc mode",		RCM,	0x6d, 0x00, 0x00, 0x0f, 0	),

 /* dos: 9e,06, from ide, was 92,aa */
RT( "h trigger 0",		HT0,	0x6e, 0x9a, 0xae, 0xff, 0	),
RT( "h trigger 1",		HT1,	0x6f, 0x60, 0x60, 0xe0, 0	),

 /* dos: 0e, from ide was 0x0e, 0x0c */
RT( "fsc res mode/ v trigger",	FRM,	0x70, 0x00, 0x00, 0xff, 0	),

 /* dos: 0, 80, 0 */
RT( "begin mp request",		BMR,	0x71, 0x00, 0x00, 0xff, 0	),
RT( "end mp request",		EMR,	0x72, 0x80, 0x80, 0xff, 0	),
RT( "msbs mp request",		MMR,	0x73, 0x00, 0x00, 0x77, 0	),

RT( "reserved",			RES,	0x74, 0x00, 0x00, 0x00, NU ),
RT( "reserved",			RES,	0x75, 0x00, 0x00, 0x00, NU ),
RT( "reserved",			RES,	0x76, 0x00, 0x00, 0x00, NU ),

RT( "begin rcv2 out",		BRO,	0x77, 0x00, 0x00, 0xff, 0	),
RT( "end rcv2 out",		ERO,	0x78, 0x00, 0x00, 0xff, 0	),
RT( "msbs rcv2 out",		MRO,	0x79, 0x00, 0x00, 0x7f, 0	),

 /* dos: 0c, 12, 03, 22 */
RT( "field length",		FL,	0x7a, 0x0c, 0x70, 0xff, 0	),
RT( "first active line",	FAL,	0x7b, 0x04, 0x06, 0xff, 0	),
RT( "last active line",		LAL,	0x7c, 0x03, 0x35, 0xff, 0	),
RT( "msbs field control",	MFC,	0x7d, 0x20, 0x20, 0x30, 0	),
};

static i2c_chip_t chip_7185 = {
CT( "Video Encoder", ENC, 7185, 0x88, 0x3a, 0x7d, I2C_STATUS_REGNUM, I2C_FLAGS_AUTOINCREMENT | I2C_FLAGS_PALMODE | I2C_FLAGS_FAST_MODE, chipregs_7185 )
};

/* === */