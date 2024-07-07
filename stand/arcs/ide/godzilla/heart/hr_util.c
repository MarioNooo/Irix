/*
 * hr_util.c : 
 *	utilities for debugging Heart diags
 *
 * Copyright 1995, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 *
 * UNPUBLISHED -- Rights reserved under the copyright laws of the United
 * States.   Use of a copyright notice is precautionary only and does not
 * imply publication or disclosure.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions
 * as set forth in FAR 52.227.19(c)(2) or subparagraph (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS 252.227-7013 and/or
 * in similar or successor clauses in the FAR, or the DOD or NASA FAR
 * Supplement.  Contractor/manufacturer is Silicon Graphics, Inc.,
 * 2011 N. Shoreline Blvd. Mountain View, CA 94039-7311.
 *
 * THE CONTENT OF THIS WORK CONTAINS CONFIDENTIAL AND PROPRIETARY
 * INFORMATION OF SILICON GRAPHICS, INC. ANY DUPLICATION, MODIFICATION,
 * DISTRIBUTION, OR DISCLOSURE IN ANY FORM, IN WHOLE, OR IN PART, IS STRICTLY
 * PROHIBITED WITHOUT THE PRIOR EXPRESS WRITTEN PERMISSION OF SILICON
 * GRAPHICS, INC.
 */

#ident "ide/godzilla/heart/hr_util.c:  $Revision: 1.3 $"

/*
 * hr_util.c - utilities for debugging Heart diags
 */
#include "sys/types.h"
#include "sys/cpu.h"
#include "sys/sbd.h"
#include "libsk.h"
#include "libsc.h"
#include "uif.h"
#include "d_godzilla.h"
#include "d_heart.h"

/*
 * Forward References 
 */
bool_t	hr_read_reg(__uint32_t argc, char **argv);
bool_t	hr_write_reg(__uint32_t argc, char **argv);

/*
 * Name:	hr_read_reg.c
 * Description:	reads a 64 bit register from Heart
 * Input:	following switches are currently used: (with or without space)
 *		-p <PIU register offset> (status register by default)
 *		-w <widget register offset> 
 *		-m <mask> (no mask by default)
 * Output:	displays the value of the register
 * Error Handling: 
 * Side Effects: 
 * Remarks:     
 * Debug Status: compiles, simulated, not emulated, not debugged
 */
bool_t
hr_read_reg(__uint32_t argc, char **argv)
{
	char		bad_arg = 0, pflag = 0, wflag = 0;
	heartreg_t	wid_reg_off = HEART_WID_STAT-HEART_BASE;
	heartreg_t	piu_reg_off = HEART_STATUS-HEART_PIU_BASE;
	heartreg_t	reg_val, mask = ~0x0;

	d_errors = 0;

   	/* get the args */
   	argc--; argv++;

	while (argc && argv[0][0]=='-' && argv[0][1]!='\0') {
	    switch (argv[0][1]) {
		case 'w':
			wflag = 1;
			if (argv[0][2]=='\0') {
				atob_L(&argv[1][0], (long long *)&wid_reg_off);
				argc--; argv++;
			} else {
				atob_L(&argv[0][2], (long long *)&wid_reg_off);
			}
			break;
		case 'p':
			pflag = 1;
			if (argv[0][2]=='\0') {
				atob_L(&argv[1][0], (long long *)&piu_reg_off);
				argc--; argv++;
			} else {
				atob_L(&argv[0][2], (long long *)&piu_reg_off);
			}
			break;
		case 'm':
			if (argv[0][2]=='\0') {
				atob_L(&argv[1][0], (long long *)&mask);
				argc--; argv++;
			} else {
				atob_L(&argv[0][2], (long long *)&mask);
			}
			break;
		default: 
			bad_arg++; break;
	    }
	    argc--; argv++;
   	}

   	if ( bad_arg || argc || (pflag && wflag)) {
	    msg_printf(ERR, "Usage: -p <PIU register offset> -m <mask> \n");
	    msg_printf(ERR, "Usage: OR -w <widget register offset> -m <mask> \n");
	    msg_printf(INFO, "defaults: register=HEART STATUS mask=~0 \n");
	    return(1);
   	} 
	else {
	    if (wflag) {
		PIO_REG_RD_64((HEART_BASE + wid_reg_off), mask, reg_val);
	    	msg_printf(SUM, "Heart Register 0x%016x has 0x%016x masked value\n",
				wid_reg_off+HEART_BASE, reg_val);
	    }
	    else if (pflag) {
		PIO_REG_RD_64((HEART_PIU_BASE + piu_reg_off), mask, reg_val);
	    	msg_printf(SUM, "Heart Register 0x%016x has 0x%016x masked value\n",
				piu_reg_off+HEART_PIU_BASE, reg_val);
	    }
	    else {
		PIO_REG_RD_64(HEART_STATUS, mask, reg_val);
	        msg_printf(SUM, "Heart STATUS Register has 0x%016x masked value\n",
				reg_val);
	    }
	    return(0);
	}
}

/*
 * Name:	hr_write_reg.c
 * Description:	writes a 64 bit value into a register from Heart
 * Input:	following switches are currently used: (with or without space)
 *		-p <PIU register offset> (MUST be provided)
 *		-w <widget register offset> (MUST be provided)
 *		-m <mask>
 *		-d <data>
 * Output:	none.
 * Error Handling: 
 * Side Effects: 
 * Remarks:     
 * Debug Status: compiles, simulated, not emulated, not debugged
 */
bool_t
hr_write_reg(__uint32_t argc, char **argv)
{
	char		bad_arg = 0;
	char		reg_value_provided = 0, reg_offset_provided = 0;
	char		pflag = 0, wflag = 0;
	heartreg_t	reg_val = 0, mask = ~0x0;
	heartreg_t	wid_reg_off = HEART_WID_STAT-HEART_BASE;
	heartreg_t	piu_reg_off = HEART_STATUS-HEART_PIU_BASE;

	d_errors = 0;

   	/* get the args */
   	argc--; argv++;
   	while (argc && argv[0][0]=='-' && argv[0][1]!='\0') {
	    switch (argv[0][1]) {
		case 'w':
			wflag = 1;
			if (argv[0][2]=='\0') {
				atob_L(&argv[1][0], (long long *)&wid_reg_off);
				argc--; argv++;
			} else {
				atob_L(&argv[0][2], (long long *)&wid_reg_off);
			}
			reg_offset_provided = 1;
			break;
		case 'p':
			pflag = 1;
			if (argv[0][2]=='\0') {
				atob_L(&argv[1][0], (long long *)&piu_reg_off);
				argc--; argv++;
			} else {
				atob_L(&argv[0][2], (long long *)&piu_reg_off);
			}
			reg_offset_provided = 1;
			break;
		case 'm':
			if (argv[0][2]=='\0') {
				atob_L(&argv[1][0], (long long *)&mask);
				argc--; argv++;
			} else {
				atob_L(&argv[0][2], (long long *)&mask);
			}
			break;
		case 'd':
			if (argv[0][2]=='\0') {
				atob_L(&argv[1][0], (long long *)&reg_val);
				argc--; argv++;
			} else {
				atob_L(&argv[0][2], (long long *)&reg_val);
			}
			reg_value_provided = 1;
			break;
		default: bad_arg++; break;
	    }
	    argc--; argv++;
   	}

   	if ( bad_arg || argc || !reg_offset_provided || !reg_value_provided
						|| (pflag && wflag)) {
	    msg_printf(ERR,"Usage: -r <register offset> -m <mask> -d <data>\n");
	    msg_printf(INFO,"Usage: the register offset and value must be provided\n");
	    return(1);
   	}
	else {
	    if (wflag) {
		PIO_REG_WR_64((HEART_BASE + wid_reg_off), mask, reg_val);
	    	msg_printf(SUM, "Heart Register 0x%016x: 0x%016x value written\n",
				wid_reg_off+HEART_BASE, reg_val & mask);
	    }
	    else if (pflag) {
		PIO_REG_WR_64((HEART_PIU_BASE + piu_reg_off), mask, reg_val);
	    	msg_printf(SUM, "Heart Register 0x%016x: 0x%016x value written\n",
				piu_reg_off+HEART_PIU_BASE, reg_val & mask);
	    }
	    else 
		msg_printf(INFO,"you MUST provide a register offset\n");
	    return(0);
	}
}

