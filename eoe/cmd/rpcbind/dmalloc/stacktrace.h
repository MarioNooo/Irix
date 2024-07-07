/*
 * Copyright 1996, Silicon Graphics, Inc.
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
 * Permission to use, copy, modify, distribute, and sell this software
 * and its documentation for any purpose is hereby granted without
 * fee, provided that (i) the above copyright notices and this
 * permission notice appear in all copies of the software and related
 * documentation, and (ii) the name of Silicon Graphics may not be
 * used in any advertising or publicity relating to the software
 * without the specific, prior written permission of Silicon Graphics.
 *
 * THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 *
 * IN NO EVENT SHALL SILICON GRAPHICS BE LIABLE FOR ANY SPECIAL,
 * INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND, OR ANY
 * DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY
 * THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE
 * OR PERFORMANCE OF THIS SOFTWARE.
 *
 */


/*
 * stacktrace.h
 */

#ifndef __stacktrace_h_
#define __stacktrace_h_

#   ifdef __cplusplus
    extern "C" {
#   endif

	/* XXX some of this is defunct */

	extern void initstacktrace(char **argv);
	extern int stacktrace (char *filename, int startpc, int startsp,
			       int regs[], int (*getword)(unsigned));
	extern int stacktrace_print(int skip);

	extern int stacktrace_get(int skip, int n, void *trace[]);
	extern int simple_stacktrace_write(int fd, char *fmt, char *executable,
							int n, void *trace[]);
	extern int simple_stacktrace_print(int fd, char *fmt, int skip, int n);
	extern void stacktrace_cleanup();
	extern char *stacktrace_get_argv0();
	extern void stacktrace_set_argv0(const char *);
	extern char *stacktrace_get_executable();
	extern void stacktrace_set_executable(const char *);

	extern void stacktrace_get_ffl(void *pc,
				       char *fun, char *file, int *line,
				       int funbufsiz, int filebufsiz);

#   ifdef __cplusplus
    }
#   endif

#endif /* __stacktrace_h_ */
