/*
 * @OSF_COPYRIGHT@
 * COPYRIGHT NOTICE
 * Copyright (c) 1990, 1991, 1992, 1993, 1994, 1996 Open Software Foundation, Inc.
 * ALL RIGHTS RESERVED (DCE).  See the file named COPYRIGHT.DCE for
 * the full copyright text.
 */
/*
 * HISTORY
 * $Log: sec_acl_encode.h,v $
 * Revision 65.4  1999/02/03 22:44:22  mek
 * Convert from IDL to C style include format.
 *
 * Revision 65.3  1997/11/07 19:57:08  gwehrman
 * Oops, undo last change.
 *
# Revision 65.1  1997/10/20  19:46:39  jdoak
# *** empty log message ***
#
 * Revision 1.1.4.2  1996/03/09  23:29:03  marty
 * 	Update OSF copyright year
 * 	[1996/03/09  22:44:28  marty]
 *
 * Revision 1.1.4.1  1995/12/08  17:36:57  root
 * 	Submit OSF/DCE 1.2.1
 * 	[1995/12/08  16:55:58  root]
 * 
 * Revision 1.1.2.2  1994/06/10  17:13:21  annie
 * 	cr10872 - fixed copyright
 * 	[1994/06/10  17:08:38  annie]
 * 
 * Revision 1.1.2.1  1994/06/02  21:28:40  mdf
 * 	hp_sec_to_osf_3 drop, merge up with latest.
 * 	[1994/05/24  15:16:20  mdf]
 * 
 * 	hp_sec_to_osf_3 drop
 * 
 * 	 /main/secd_auth/1  1994/05/03  15:39 UTC  burati
 * 	Public API for the DCE ACL encoding interface.
 * 
 * $EndLog$
 */
/* Generated by IDL compiler version OSF DCE T1.2.0-09 */
#ifndef sec_acl_encode_v0_0_included
#define sec_acl_encode_v0_0_included
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
extern void sec_acl_entry_encode(
#ifdef IDL_PROTOTYPES
    /* [in] */ idl_void_p_t (*allocate)(
#ifdef IDL_PROTOTYPES
    /* [out] */ unsigned32 size
#endif
),
    /* [in] */ void (*dealloc)(
#ifdef IDL_PROTOTYPES
    /* [out] */ idl_void_p_t ptr
#endif
),
    /* [in] */ sec_acl_entry_t *entry,
    /* [out] */ unsigned32 *num_bytes,
    /* [out] */ idl_byte **bytes,
    /* [out] */ error_status_t *stp
#endif
);
extern void sec_acl_entry_decode(
#ifdef IDL_PROTOTYPES
    /* [in] */ idl_void_p_t allocate(
#ifdef IDL_PROTOTYPES
    /* [out] */ unsigned32 size
#endif
),
    /* [in] */ void (*dealloc)(
#ifdef IDL_PROTOTYPES
    /* [out] */ idl_void_p_t ptr
#endif
),
    /* [in] */ unsigned32 num_bytes,
    /* [in] */ idl_byte *bytes,
    /* [out] */ sec_acl_entry_t *entry,
    /* [out] */ error_status_t *stp
#endif
);
extern void sec_acl_entry_decoded_data_free(
#ifdef IDL_PROTOTYPES
    /* [in] */ void (*dealloc)(
#ifdef IDL_PROTOTYPES
    /* [out] */ idl_void_p_t ptr
#endif
),
    /* [in] */ sec_acl_entry_t *epac_data
#endif
);
extern void sec_acl_encode_v0_entries(
#ifdef IDL_PROTOTYPES
    /* [in] */ idl_void_p_t (*allocate)(
#ifdef IDL_PROTOTYPES
    /* [out] */ unsigned32 size
#endif
),
    /* [in] */ void (*deallocate)(
#ifdef IDL_PROTOTYPES
    /* [out] */ idl_void_p_t ptr
#endif
),
    /* [in] */ boolean32 free_old_entries,
    /* [in, out] */ sec_acl_list_t *aclsP,
    /* [out] */ error_status_t *stp
#endif
);
extern void sec_acl_decode_v0_entries(
#ifdef IDL_PROTOTYPES
    /* [in] */ idl_void_p_t (*allocate)(
#ifdef IDL_PROTOTYPES
    /* [out] */ unsigned32 size
#endif
),
    /* [in] */ void (*deallocate)(
#ifdef IDL_PROTOTYPES
    /* [out] */ idl_void_p_t ptr
#endif
),
    /* [in] */ boolean32 free_old_entries,
    /* [in, out] */ sec_acl_list_t *aclsP,
    /* [out] */ error_status_t *stp
#endif
);

#ifdef __cplusplus
    }

#endif
#endif