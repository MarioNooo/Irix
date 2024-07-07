/*
 * @OSF_COPYRIGHT@
 * COPYRIGHT NOTICE
 * Copyright (c) 1990, 1991, 1992, 1993, 1996 Open Software Foundation, Inc.
 * ALL RIGHTS RESERVED (DCE).  See the file named COPYRIGHT.DCE in the
 * src directory for the full copyright text.
 */
/*
 * HISTORY
 * $Log: rs_bind.h,v $
 * Revision 65.2  1999/02/03 22:44:22  mek
 * Convert from IDL to C style include format.
 *
 * Revision 65.1  1997/10/20 19:46:35  jdoak
 * *** empty log message ***
 *
 * Revision 1.1.4.2  1996/03/09  23:28:26  marty
 * 	Update OSF copyright year
 * 	[1996/03/09  22:43:54  marty]
 *
 * Revision 1.1.4.1  1995/12/08  17:34:17  root
 * 	Submit OSF/DCE 1.2.1
 * 	[1995/12/08  16:55:26  root]
 * 
 * Revision 1.1.2.5  1993/02/26  23:49:09  emartin
 * 	em_bl6f: add cellname and update_site_name args
 * 	[1993/02/24  22:06:39  emartin]
 * 
 * Revision 1.1.2.4  1992/12/29  13:30:50  zeliff
 * 	Embedding copyright notice
 * 	[1992/12/28  20:48:48  zeliff]
 * 
 * Revision 1.1.2.3  1992/11/04  23:00:26  ahop
 * 	Third replication drop: bl6a
 * 	[1992/11/04  22:58:48  ahop]
 * 
 * Revision 1.1.2.2  1992/11/04  22:51:40  john
 * 	Initial Creation.
 * 	[1992/11/04  22:51:12  john]
 * 
 * $EndLog$
 */
/* Generated by IDL compiler version OSF DCE T1.2.0-09 */
#ifndef rs_bind_v2_0_included
#define rs_bind_v2_0_included
#ifndef IDLBASE_H
#include <dce/idlbase.h>
#endif
#include <dce/rpc.h>

#ifdef __cplusplus
    extern "C" {
#endif

#ifndef nbase_v0_0_included
#include <dce/nbase.h>
#endif
#ifndef rgynbase_v0_0_included
#include <dce/rgynbase.h>
#endif
#ifndef rplbase_v0_0_included
#include <dce/rplbase.h>
#endif
extern void rs_bind_get_update_site(
#ifdef IDL_PROTOTYPES
    /* [in] */ handle_t h,
    /* [out] */ sec_rgy_name_t cellname,
    /* [out] */ boolean32 *update_site,
    /* [out] */ rs_replica_name_p_t *update_site_name,
    /* [out] */ uuid_t *update_site_id,
    /* [out] */ rs_replica_twr_vec_p_t *update_site_twrs,
    /* [out] */ error_status_t *st
#endif
);
typedef struct rs_bind_v2_0_epv_t {
void (*rs_bind_get_update_site)(
#ifdef IDL_PROTOTYPES
    /* [in] */ handle_t h,
    /* [out] */ sec_rgy_name_t cellname,
    /* [out] */ boolean32 *update_site,
    /* [out] */ rs_replica_name_p_t *update_site_name,
    /* [out] */ uuid_t *update_site_id,
    /* [out] */ rs_replica_twr_vec_p_t *update_site_twrs,
    /* [out] */ error_status_t *st
#endif
);
} rs_bind_v2_0_epv_t;
extern rpc_if_handle_t rs_bind_v2_0_c_ifspec;
extern rpc_if_handle_t rs_bind_v2_0_s_ifspec;

#ifdef __cplusplus
    }

#else
#endif
#endif
