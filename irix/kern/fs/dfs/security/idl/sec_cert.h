/*
 * @OSF_COPYRIGHT@
 * COPYRIGHT NOTICE
 * Copyright (c) 1990, 1991, 1992, 1993, 1996 Open Software Foundation, Inc.
 * ALL RIGHTS RESERVED (DCE).  See the file named COPYRIGHT.DCE in the
 * src directory for the full copyright text.
 */
/*
 * HISTORY
 * $Log: sec_cert.h,v $
 * Revision 65.2  1999/02/03 22:44:23  mek
 * Convert from IDL to C style include format.
 *
 * Revision 65.1  1997/10/20 19:46:39  jdoak
 * *** empty log message ***
 *
 * Revision 1.1.4.2  1996/03/09  23:29:10  marty
 * 	Update OSF copyright year
 * 	[1996/03/09  22:44:34  marty]
 *
 * Revision 1.1.4.1  1995/12/08  17:37:25  root
 * 	Submit OSF/DCE 1.2.1
 * 	[1995/12/08  16:56:04  root]
 * 
 * Revision 1.1.2.2  1992/12/29  13:54:04  zeliff
 * 	Embedding copyright notice
 * 	[1992/12/28  20:22:14  zeliff]
 * 
 * Revision 1.1  1992/01/19  14:55:21  devrcs
 * 	Initial revision
 * 
 * $EndLog$
 */
/* Generated by IDL compiler version OSF DCE T1.2.0-09 */
#ifndef sec_cert_v0_0_included
#define sec_cert_v0_0_included
#ifndef IDLBASE_H
#include <dce/idlbase.h>
#endif

#ifdef __cplusplus
    extern "C" {
#endif

#ifndef nbase_v0_0_included
#include <dce/nbase.h>
#endif
#ifndef sec_login_v0_0_included
#include <dce/sec_login.h>
#endif
extern void sec_login_validate_cert_auth(
#ifdef IDL_PROTOTYPES
    /* [in] */ sec_login_handle_t login_context,
    /* [out] */ error_status_t *status
#endif
);

#ifdef __cplusplus
    }

#endif
#endif