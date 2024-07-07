/*
 * @OSF_COPYRIGHT@
 * COPYRIGHT NOTICE
 * Copyright (c) 1990, 1991, 1992, 1993, 1996 Open Software Foundation, Inc.
 * ALL RIGHTS RESERVED (DCE).  See the file named COPYRIGHT.DCE in the
 * src directory for the full copyright text.
 */
/*
 * HISTORY
 * $Log: id_base.h,v $
 * Revision 65.2  1999/02/03 22:44:19  mek
 * Convert from IDL to C style include format.
 *
 * Revision 65.1  1997/10/20 19:46:30  jdoak
 * *** empty log message ***
 *
 * Revision 1.1.6.2  1996/03/09  23:27:52  marty
 * 	Update OSF copyright year
 * 	[1996/03/09  22:43:19  marty]
 *
 * Revision 1.1.6.1  1995/12/08  17:31:20  root
 * 	Submit OSF/DCE 1.2.1
 * 	[1995/12/08  16:54:54  root]
 * 
 * Revision 1.1.4.1  1994/01/28  23:10:44  burati
 * 	Delegation/EPAC changes (dlg_bl1)
 * 	[1994/01/18  20:52:05  burati]
 * 
 * Revision 1.1.2.2  1992/12/29  13:29:11  zeliff
 * 	Embedding copyright notice
 * 	[1992/12/28  20:16:38  zeliff]
 * 
 * Revision 1.1  1992/01/19  14:54:52  devrcs
 * 	Initial revision
 * 
 * $EndLog$
 */
/* Generated by IDL compiler version OSF DCE T1.2.0-09 */
#ifndef sec_id_base_v0_0_included
#define sec_id_base_v0_0_included
#ifndef IDLBASE_H
#include <dce/idlbase.h>
#endif

#ifdef __cplusplus
    extern "C" {
#endif

#ifndef nbase_v0_0_included
#include <dce/nbase.h>
#endif
typedef struct  {
uuid_t uuid;
idl_char *name;
} sec_id_t;
typedef struct  {
sec_id_t id;
sec_id_t realm;
} sec_id_foreign_t;
typedef struct  {
sec_id_t realm;
unsigned16 num_groups;
sec_id_t *groups;
} sec_id_foreign_groupset_t;
typedef enum {sec_id_pac_format_v1=0} sec_id_pac_format_t;
typedef struct  {
sec_id_pac_format_t pac_type;
boolean32 authenticated;
sec_id_t realm;
sec_id_t principal;
sec_id_t group;
unsigned16 num_groups;
unsigned16 num_foreign_groups;
sec_id_t *groups;
sec_id_foreign_t *foreign_groups;
} sec_id_pac_t;
typedef sec_id_pac_t sec_id_pac_format_v1_t;
typedef struct  {
ndr_format_t format_label;
unsigned32 num_bytes;
idl_byte pickled_data[1];
} sec_id_pickled_pac_t;

#ifdef __cplusplus
    }

#endif
#endif
