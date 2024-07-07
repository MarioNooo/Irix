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
 *  MGRAS - INFO.
 *
 *  $Revision: 1.7 $
 */

#include <sys/types.h>

/* bit patterns */

__uint32_t mco_patrn[12] = {
	0x5a5a5a5a, 0x3c3c3c3c, 0xf0f0f0f0,
	0xa5a5a5a5, 0xc3c3c3c3, 0x0f0f0f0f,
	0x5a5a5a5a, 0x3c3c3c3c, 0xf0f0f0f0,
	0xa5a5a5a5, 0xc3c3c3c3, 0x0f0f0f0f
};

ushort_t mco_walk_1_0[34]  = {  
	0x0001, 0x0002, 0x0004, 0x0008,
	0x0010,	0x0020,	0x0040, 0x0080,
	0x0100,	0x0200,	0x0400, 0x0800,
	0x1000,	0x2000,	0x4000, 0x8000,

	0xFFFE, 0xFFFD, 0xFFFB, 0xFFF7,
	0xFFEF,	0xFFDF,	0xFFBF, 0xFF7F,
	0xFEFF,	0xFDFF,	0xFBFF, 0xF7FF,
	0xEFFF,	0xDFFF,	0xBFFF, 0x7FFF,

	0x0000, 0xFFFF
};

__uint32_t mco_walk_1_0_32_rss[64]  = {  
	0x00000001, 0x00000002, 0x00000004, 0x00000008,
	0x00000010, 0x00000020, 0x00000040, 0x00000080,
	0x00000100, 0x00000200, 0x00000400, 0x00000800,
	0x00001000, 0x00002000, 0x00004000, 0x00008000,
	0x00010000, 0x00020000, 0x00040000, 0x00080000,
	0x00100000, 0x00200000, 0x00400000, 0x00800000,
	0x01000000, 0x02000000, 0x04000000, 0x08000000,
	0x10000000, 0x20000000, 0x40000000, 0x80000000,
	0xFFFFFFFE, 0xFFFFFFFD, 0xFFFFFFFB, 0xFFFFFFF7,
	0xFFFFFFEF, 0xFFFFFFDF, 0xFFFFFFBF, 0xFFFFFF7F,
	0xFFFFFEFF, 0xFFFFFDFF, 0xFFFFFBFF, 0xFFFFF7FF,
	0xFFFFEFFF, 0xFFFFDFFF, 0xFFFFBFFF, 0xFFFF7FFF,
	0xFFFEFFFF, 0xFFFDFFFF, 0xFFFBFFFF, 0xFFF7FFFF,
	0xFFEFFFFF, 0xFFDFFFFF, 0xFFBFFFFF, 0xFF7FFFFF,
	0xFEFFFFFF, 0xFDFFFFFF, 0xFBFFFFFF, 0xF7FFFFFF,
	0xEFFFFFFF, 0xDFFFFFFF, 0xBFFFFFFF, 0x7FFFFFFF
};

__uint32_t  mco_walk_1_0_32[8]  = {  
	0x00000001, 0x00000002, 0x00000004, 0x00000008,
	0x10000000, 0x20000000, 0x40000000, 0x80000000
};

ushort_t mco_walking_patrn[16]= {
        0x01, 0x02, 0x04, 0x08,
        0x10, 0x20, 0x40, 0x80,
        0xFE, 0xFD, 0xFB, 0xF7,
        0xEF, 0xDF, 0xBF, 0x7F,
};


