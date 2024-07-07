/* @OSF_COPYRIGHT@
 * COPYRIGHT NOTICE
 * Copyright (c) 1990, 1991, 1992, 1993, 1994 Open Software Foundation, Inc.
 * ALL RIGHTS RESERVED (DCE).  See the file named COPYRIGHT.DCE for
 * the full copyright text.
 *
 * HISTORY
 * $Log: tkc_trace.h,v $
 * Revision 65.2  1999/02/04 19:19:44  mek
 * Provide C style include file for IRIX kernel integration.
 *
 * Revision 65.1  1997/10/20 19:18:03  jdoak
 * *** empty log message ***
 *
 * Revision 1.1.143.1  1996/10/02  21:01:35  damon
 * 	Newest DFS from Transarc
 * 	[1996/10/01  18:48:13  damon]
 *
 * Revision 1.1.138.2  1994/06/09  14:20:45  annie
 * 	fixed copyright in src/file
 * 	[1994/06/09  13:32:07  annie]
 * 
 * Revision 1.1.138.1  1994/02/04  20:30:44  devsrc
 * 	Merged from 1.0.3a to 1.1
 * 	[1994/02/04  15:18:15  devsrc]
 * 
 * Revision 1.1.136.1  1993/12/07  17:34:03  jaffe
 * 	New File from Transarc 1.0.3a
 * 	[1993/12/02  21:56:11  jaffe]
 * 
 * $EndLog$
 */

/*
 * tkc_trace.h:
 * This file is automatically generated; please do not edit it.
 */
#define TKC_TRACE_NULL                           (702357504L)
#define TKC_TRACE_GETTOKENSTART                  (702357505L)
#define TKC_TRACE_GETTOKENEND                    (702357506L)
#define TKC_TRACE_REVOKESTART                    (702357507L)
#define TKC_TRACE_REVOKEEND                      (702357508L)
#define TKC_TRACE_READSTART                      (702357509L)
#define TKC_TRACE_READEND                        (702357510L)
#define TKC_TRACE_WRITESTART                     (702357511L)
#define TKC_TRACE_WRITEEND                       (702357512L)
#define TKC_TRACE_PURGEVM                        (702357513L)
#define TKC_TRACE_GETACLSTART                    (702357514L)
#define TKC_TRACE_GETACLGVFAILED                 (702357515L)
#define TKC_TRACE_GETACLGETFAILED                (702357516L)
#define TKC_TRACE_GETACLDONE                     (702357517L)
#define TKC_TRACE_SETACLSTART                    (702357518L)
#define TKC_TRACE_SETACLGVFAILED                 (702357519L)
#define TKC_TRACE_SETACLGETFAILED                (702357520L)
#define TKC_TRACE_SETACLDONE                     (702357521L)
#define TKC_TRACE_GET                            (702357522L)
#define TKC_TRACE_GET_HAVE                       (702357523L)
#define TKC_TRACE_GET_FAIL                       (702357524L)
#define TKC_TRACE_GET_GOT                        (702357525L)
#define TKC_TRACE_PUT                            (702357526L)
#define TKC_TRACE_RELEASE                        (702357527L)
#define TKC_TRACE_GETTOKENS                      (702357528L)
#define TKC_TRACE_GETTOKENS_END                  (702357529L)
#define TKC_TRACE_RELEASETOKENS                  (702357530L)
#define TKC_TRACE_PUTTOKENS                      (702357531L)
#define TKC_TRACE_REVOKETOKEN                    (702357532L)
#define initialize_zkc_error_table()
#define ERROR_TABLE_BASE_zkc (702357504L)

/* for compatibility with older versions... */
#define init_zkc_err_tbl initialize_zkc_error_table
#define zkc_err_base ERROR_TABLE_BASE_zkc