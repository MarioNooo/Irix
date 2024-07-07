/*
 * @OSF_COPYRIGHT@
 * COPYRIGHT NOTICE
 * Copyright (c) 1990, 1991, 1992, 1993, 1994, 1996 Open Software Foundation, Inc.
 * ALL RIGHTS RESERVED (DCE).  See the file named COPYRIGHT.DCE for
 * the full copyright text.
 */
/*
 * HISTORY
 * $Log: authz_encode.h,v $
 * Revision 65.2  1999/02/03 22:44:19  mek
 * Convert from IDL to C style include format.
 *
 * Revision 65.1  1997/10/20 19:46:29  jdoak
 * *** empty log message ***
 *
 * Revision 1.1.4.2  1996/03/09  23:27:46  marty
 * 	Update OSF copyright year
 * 	[1996/03/09  22:43:13  marty]
 *
 * Revision 1.1.4.1  1995/12/08  17:31:00  root
 * 	Submit OSF/DCE 1.2.1
 * 	[1995/12/08  16:54:49  root]
 * 
 * Revision 1.1.2.2  1994/06/17  18:42:16  devsrc
 * 	cr10872 - fix copyright
 * 	[1994/06/17  18:08:55  devsrc]
 * 
 * Revision 1.1.2.1  1994/05/11  19:09:40  ahop
 * 	hp_sec_to_osf_2 drop
 * 	DCE Service Ticket authorization data encoding
 * 	[1994/04/29  21:03:43  ahop]
 * 
 * $EndLog$
 */
/* Generated by IDL compiler version OSF DCE T1.2.0-09 */
#ifndef sec_authz_encode_v0_0_included
#define sec_authz_encode_v0_0_included
#ifndef IDLBASE_H
#include <dce/idlbase.h>
#endif
#include <dce/rpc.h>
#include <dce/idl_es.h>

#ifdef __cplusplus
    extern "C" {
#endif

#ifndef nbase_v0_0_included
#include <dce/nbase.h>
#endif
#ifndef authz_base_v0_0_included
#include <dce/authz_base.h>
#endif
extern void v1_1_authz_data_encode(
#ifdef IDL_PROTOTYPES
    /* [in] */ idl_es_handle_t h,
    /* [in, out] */ sec_v1_1_authz_data_t *v1_1_authz_data
#endif
);
typedef struct sec_authz_encode_v0_0_epv_t {
void (*v1_1_authz_data_encode)(
#ifdef IDL_PROTOTYPES
    /* [in] */ idl_es_handle_t h,
    /* [in, out] */ sec_v1_1_authz_data_t *v1_1_authz_data
#endif
);
} sec_authz_encode_v0_0_epv_t;
extern rpc_if_handle_t sec_authz_encode_v0_0_c_ifspec;
extern rpc_if_handle_t sec_authz_encode_v0_0_s_ifspec;

#ifdef __cplusplus
    }

#else
#endif
#endif