/******************************************************************************
 *
 * Project:  Stevens Book - Big Library
 * Purpose:  This function is a wrapper for connect() syscall which add a
 * 	     timeout to this syscall using alarm() syscall.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/socket.h>

#include "unp.h"

static void connect_alarm(int);

int connect_timeo(int sockfd, const SA *saptr, socklen_t salen, int nsec) {
	Sigfunc *sigfunc;
	int n;

	sigfunc = Signal(SIGALRM, connect_alarm);
	if (alarm(nsec) != 0)
		err_msg("connect_timeo: alarm was already set");

	if ( (n = connect(sockfd, saptr, salen)) < 0) {
		close(sockfd);
		if (errno == EINTR)
			errno = ETIMEDOUT;
	}

	alarm(0); // turn off the alarm
	Signal(SIGALRM, sigfunc); // restore previous signal handler

	return n;
}

static void connect_alarm(int signo) {
	return; // just interrupt the connect()
}
