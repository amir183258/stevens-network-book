/******************************************************************************
 *
 * Project:  Stevens Book - Big Library
 * Purpose:  This is the implementation for error messages.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdarg.h>
#include <syslog.h>

#include "./unp.h"

int daemon_proc;

static void err_doit(int errnoflag, int level, const char *fmt, va_list ap);

/* Nonfatal error related to system call
 * Print message and return */

void err_ret(const char *fmt, ...) {
	va_list ap;

	va_start(ap, fmt);
	err_doit(1, LOG_INFO, fmt, ap);
	va_end(ap);
	return;
}

/* Fatal error related to system call
 * Print message and terminate */

void err_sys(const char *fmt, ...) {
	va_list ap;

	va_start(ap, fmt);
	err_doit(1, LOG_ERR, fmt, ap);
	exit(1);
}

/* Nonfatal error unrelated to system call
 * Print message and return */

void err_msg(const char *fmt, ...) {
	va_list ap;

	va_start(ap, fmt);
	err_doit(0, LOG_INFO, fmt, ap);
	va_end(ap);
	return;
}

/* Fatal error unrelated to system call
 * Print message and terminate */

void err_quit(const char *fmt, ...) {
	va_list ap;

	va_start(ap, fmt);
	err_doit(0, LOG_ERR, fmt, ap);  // LOG_ERR is syslog level
	va_end(ap);
	exit(1);
}

/* Print message and return to caller
 * Caller specifies "errnoflag" and "level" */

static void err_doit(int errnoflag, int level, const char *fmt, va_list ap) {
	int errno_save, n;
	char buf[MAXLINE + 1];

	errno_save = errno;

	vsnprintf(buf, MAXLINE, fmt, ap);  // safe

	n = strlen(buf);
	if (errnoflag)
		snprintf(buf + n, MAXLINE - n, ": %s", strerror(errno_save));
	strcat(buf, "\n"); // DANGER: maybe unsafe

	if (daemon_proc)
		syslog(level, "%s", buf);
	else {
		fflush(stdout);
		fputs(buf, stderr);
		fflush(stderr);
	}
}
