/*
 * @OSF_COPYRIGHT@
 * COPYRIGHT NOTICE
 * Copyright (c) 1990, 1991, 1992, 1993, 1994 Open Software Foundation, Inc.
 * ALL RIGHTS RESERVED (DCE).  See the file named COPYRIGHT.DCE for
 * the full copyright text.
 */
/*
 *      Copyright (C) 1996, 1992 Transarc Corporation
 *      All rights reserved.
 */

/*
 * zlc_trace.h:
 * This file is automatically generated; please do not edit it.
 */
#define ZLC_TRACE_RCSID                          (704851968L)
#define ZLC_TRACE_ENTER_TRYREMOVE                (704851969L)
#define ZLC_TRACE_TRYREMOVE_ITEM                 (704851970L)
#define ZLC_TRACE_EXIT_TRYREMOVE                 (704851971L)
#define ZLC_TRACE_ENTER_GETDELETETOKEN           (704851972L)
#define ZLC_TRACE_GETDELETETOKEN_NOVOL           (704851973L)
#define ZLC_TRACE_GETDELETETOKEN_MOVE            (704851974L)
#define ZLC_TRACE_GETDELETETOKEN_WAIT_REMMOVE    (704851975L)
#define ZLC_TRACE_GETDELETETOKEN_WAIT_LCLMOVE    (704851976L)
#define ZLC_TRACE_GETDELETETOKEN_REMOVE_GRANTED  (704851977L)
#define ZLC_TRACE_GETDELETETOKEN_REQUEST_QUEUED  (704851978L)
#define ZLC_TRACE_EXIT_GETDELETETOKEN            (704851979L)
#define ZLC_TRACE_ENTER_CLEANVOLUME              (704851980L)
#define ZLC_TRACE_EXIT_CLEANVOLUME               (704851981L)
#define ZLC_TRACE_MGR_PRUNING                    (704851982L)
#define ZLC_TRACE_MGR_WAITING                    (704851983L)
#define ZLC_TRACE_ENTER_PRUNEQUEUE               (704851984L)
#define ZLC_TRACE_PRUNEQUEUE_GRANTED             (704851985L)
#define ZLC_TRACE_PRUNEQUEUE_CLEAN               (704851986L)
#define ZLC_TRACE_PRUNEQUEUE_WAIT_TRYTOKEN       (704851987L)
#define ZLC_TRACE_PRUNEQUEUE_WAIT                (704851988L)
#define ZLC_TRACE_PRUNEQUEUE_TSRREPWAIT          (704851989L)
#define ZLC_TRACE_PRUNEQUEUE_TSRWAIT             (704851990L)
#define ZLC_TRACE_PRUNEQUEUE_TSR_TRYTOKEN        (704851991L)
#define ZLC_TRACE_EXIT_PRUNEQUEUE                (704851992L)
#define ZLC_TRACE_ENTER_WAKEUPMGR                (704851993L)
#define ZLC_TRACE_ENTER_FREEDOWNTOQUOTA          (704851994L)
#define ZLC_TRACE_FD2Q_MORIBUND                  (704851995L)
#define ZLC_TRACE_FD2Q_ASYNC                     (704851996L)
#define ZLC_TRACE_FD2Q_DALLY                     (704851997L)
#define ZLC_TRACE_FD2Q_WAIT                      (704851998L)
#define ZLC_TRACE_FD2Q_SKIP                      (704851999L)
#define ZLC_TRACE_EXIT_FREEDOWNTOQUOTA           (704852000L)
#define ZLC_TRACE_ENTER_SETRESTARTSTATE          (704852001L)
#define ZLC_TRACE_EXIT_SETRESTARTSTATE           (704852002L)
#define ZLC_TRACE_ENTER_ASYNCGRANT               (704852003L)
#define ZLC_TRACE_ASYNCGRANT_FOUND               (704852004L)
#define ZLC_TRACE_ASYNCGRANT_NOVOL               (704852005L)
#define ZLC_TRACE_ASYNCGRANT_MOVE                (704852006L)
#define ZLC_TRACE_ASYNCGRANT_WAIT_REMMOVE        (704852007L)
#define ZLC_TRACE_ASYNCGRANT_GRANTED             (704852008L)
#define ZLC_TRACE_ASYNCGRANT_NOTFOUND            (704852009L)
#define ZLC_TRACE_ENTER_REVOKETOKEN              (704852010L)
#define ZLC_TRACE_ASYNCGRANT_ENTRY_FOUND         (704852011L)
#define ZLC_TRACE_ASYNCGRANT_STATETRANS          (704852012L)
#define ZLC_TRACE_EXIT_ASYNCGRANT                (704852013L)
#define ZLC_TRACE_CLEANVOLUME_STATETRANS         (704852014L)
#define ZLC_TRACE_ENTER_GETDELETETOKEN_2         (704852015L)
#define ZLC_TRACE_GETDELETETOKEN_OFD_GRANTED     (704852016L)
#define ZLC_TRACE_GETDELETETOKEN_OFD_QUEUED      (704852017L)
#define ZLC_TRACE_GETDELETETOKEN_TKMGETERR       (704852018L)
#define ZLC_TRACE_GETDELETETOKEN_TKMRETURNERR    (704852019L)
#define ZLC_TRACE_GETDELETETOKEN_STATETRANS      (704852020L)
#define ZLC_TRACE_ENTER_TRYREMOVE_2              (704852021L)
#define ZLC_TRACE_TRYREMOVE_INITSTATE            (704852022L)
#define ZLC_TRACE_GOTONEXTSTATE_NOVOL            (704852023L)
#define ZLC_TRACE_ENTER_FD2T                     (704852024L)
#define ZLC_TRACE_FD2T_STATETRANS                (704852025L)
#define ZLC_TRACE_EXIT_FD2T                      (704852026L)
#define ZLC_TRACE_ENTER_PRUNEQUEUE_2             (704852027L)
#define ZLC_TRACE_PRUNEQUEUE_STATETRANS          (704852028L)
#define ZLC_TRACE_EXIT_PRUNEQUEUE_2              (704852029L)
#define ZLC_TRACE_ENTER_WAKEUPMGR_2              (704852030L)
#define ZLC_TRACE_MGR_WAKETIME                   (704852031L)
#define ZLC_TRACE_EXIT_INIT                      (704852032L)
#define initialize_zzl_error_table()
#define ERROR_TABLE_BASE_zzl (704851968L)

/* for compatibility with older versions... */
#define init_zzl_err_tbl initialize_zzl_error_table
#define zzl_err_base ERROR_TABLE_BASE_zzl
