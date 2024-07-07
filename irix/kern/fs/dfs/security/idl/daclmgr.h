/*
 * @OSF_COPYRIGHT@
 * COPYRIGHT NOTICE
 * Copyright (c) 1990, 1991, 1992, 1993, 1996 Open Software Foundation, Inc.
 * ALL RIGHTS RESERVED (DCE).  See the file named COPYRIGHT.DCE in the
 * src directory for the full copyright text.
 */
/*
 * HISTORY
 * $Log: daclmgr.h,v $
 * Revision 65.2  1999/02/03 22:44:19  mek
 * Convert from IDL to C style include format.
 *
 * Revision 65.1  1997/10/20 19:46:30  jdoak
 * *** empty log message ***
 *
 * Revision 1.1.8.2  1996/03/09  23:27:49  marty
 * 	Update OSF copyright year
 * 	[1996/03/09  22:43:16  marty]
 *
 * Revision 1.1.8.1  1995/12/08  17:31:10  root
 * 	Submit OSF/DCE 1.2.1
 * 	[1995/12/08  16:54:52  root]
 * 
 * Revision 1.1.6.2  1994/06/02  21:28:24  mdf
 * 	hp_sec_to_osf_3 drop, merge up with latest.
 * 	[1994/05/24  15:15:57  mdf]
 * 
 * 	hp_sec_to_osf_3 drop
 * 
 * Revision 1.1.6.1  1994/01/28  23:10:43  burati
 * 	Delegation changes (rpc_authz_cred_handle_t) (dlg_bl1)
 * 	[1994/01/18  20:51:55  burati]
 * 
 * Revision 1.1.4.2  1992/12/29  13:29:01  zeliff
 * 	Embedding copyright notice
 * 	[1992/12/28  20:48:12  zeliff]
 * 
 * Revision 1.1.2.2  1992/05/08  14:48:58  burati
 * 	Add sec_acl_mgr_get_mgr_types_semantics
 * 	[1992/05/07  19:11:07  burati]
 * 
 * Revision 1.1  1992/01/19  14:54:37  devrcs
 * 	Initial revision
 * 
 * $EndLog$
 */
/* Generated by IDL compiler version OSF DCE T1.2.0-09 */
#ifndef sec_acl_mgr_v0_0_included
#define sec_acl_mgr_v0_0_included
#ifndef IDLBASE_H
#include <dce/idlbase.h>
#endif

#ifdef __cplusplus
    extern "C" {
#endif

#ifndef nbase_v0_0_included
#include <dce/nbase.h>
#endif
#ifndef sec_acl_base_v0_0_included
#include <dce/aclbase.h>
#endif
#ifndef lbase_v0_0_included
#include <dce/lbase.h>
#endif
#ifndef rpcbase_v0_0_included
#include <dce/rpcbase.h>
#endif
typedef idl_void_p_t sec_acl_mgr_handle_t;
typedef idl_void_p_t sec_acl_key_t;
typedef unsigned32 sec_acl_mgr_config_t;
#define sec_acl_mgr_config_create (1)
#define sec_acl_mgr_config_stable (2)
extern void sec_acl_mgr_configure(
#ifdef IDL_PROTOTYPES
    /* [in] */ sec_acl_mgr_config_t config_info,
    /* [in] */ unsigned_char_p_t db_name,
    /* [out] */ sec_acl_mgr_handle_t *sec_acl_mgr,
    /* [out] */ error_status_t *st
#endif
);
extern boolean32 sec_acl_mgr_is_authorized(
#ifdef IDL_PROTOTYPES
    /* [in] */ sec_acl_mgr_handle_t sec_acl_mgr,
    /* [in] */ sec_acl_permset_t desired_access,
    /* [in] */ rpc_authz_cred_handle_t *accessor_info,
    /* [in] */ sec_acl_key_t sec_acl_key,
    /* [in] */ uuid_t *manager_type,
    /* [in] */ sec_id_t *user_obj,
    /* [in] */ sec_id_t *group_obj,
    /* [out] */ error_status_t *st
#endif
);
extern void sec_acl_mgr_get_access(
#ifdef IDL_PROTOTYPES
    /* [in] */ sec_acl_mgr_handle_t sec_acl_mgr,
    /* [in] */ rpc_authz_cred_handle_t accessor_info,
    /* [in] */ sec_acl_key_t sec_acl_key,
    /* [in] */ uuid_t *manager_type,
    /* [in] */ sec_id_t *user_obj,
    /* [in] */ sec_id_t *group_obj,
    /* [out] */ sec_acl_permset_t *net_rights,
    /* [out] */ error_status_t *st
#endif
);
extern void sec_acl_mgr_replace(
#ifdef IDL_PROTOTYPES
    /* [in] */ sec_acl_mgr_handle_t sec_acl_mgr,
    /* [in] */ sec_acl_key_t sec_acl_key,
    /* [in] */ uuid_t *manager_type,
    /* [in] */ sec_acl_type_t sec_acl_type,
    /* [in] */ sec_acl_list_t *sec_acl_list,
    /* [out] */ error_status_t *st
#endif
);
extern void sec_acl_mgr_lookup(
#ifdef IDL_PROTOTYPES
    /* [in] */ sec_acl_mgr_handle_t sec_acl_mgr,
    /* [in] */ sec_acl_key_t sec_acl_key,
    /* [in] */ uuid_t *manager_type,
    /* [in] */ sec_acl_type_t sec_acl_type,
    /* [out] */ sec_acl_list_t **sec_acl_list,
    /* [out] */ error_status_t *st
#endif
);
extern void sec_acl_mgr_get_manager_types(
#ifdef IDL_PROTOTYPES
    /* [in] */ sec_acl_mgr_handle_t sec_acl_mgr,
    /* [in] */ sec_acl_key_t sec_acl_key,
    /* [in] */ sec_acl_type_t sec_acl_type,
    /* [in] */ unsigned32 size_avail,
    /* [out] */ unsigned32 *size_used,
    /* [out] */ unsigned32 *num_types,
    /* [out] */ uuid_t manager_types[],
    /* [out] */ error_status_t *st
#endif
);
extern void sec_acl_mgr_get_types_semantics(
#ifdef IDL_PROTOTYPES
    /* [in] */ sec_acl_mgr_handle_t sec_acl_mgr,
    /* [in] */ sec_acl_key_t sec_acl_key,
    /* [in] */ sec_acl_type_t sec_acl_type,
    /* [in] */ unsigned32 size_avail,
    /* [out] */ unsigned32 *size_used,
    /* [out] */ unsigned32 *num_types,
    /* [out] */ uuid_t manager_types[],
    /* [out] */ sec_acl_posix_semantics_t posix_semantics[],
    /* [out] */ error_status_t *st
#endif
);
extern void sec_acl_mgr_get_printstring(
#ifdef IDL_PROTOTYPES
    /* [in] */ sec_acl_mgr_handle_t sec_acl_mgr,
    /* [in] */ uuid_t *manager_type,
    /* [in] */ unsigned32 size_avail,
    /* [out] */ uuid_t *manager_type_chain,
    /* [out] */ sec_acl_printstring_t *manager_info,
    /* [out] */ boolean32 *tokenize,
    /* [out] */ unsigned32 *total_num_printstrings,
    /* [out] */ unsigned32 *size_used,
    /* [out] */ sec_acl_printstring_t printstrings[],
    /* [out] */ error_status_t *st
#endif
);

#ifdef __cplusplus
    }

#endif
#endif