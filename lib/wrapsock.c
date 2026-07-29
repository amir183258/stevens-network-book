/******************************************************************************
 *
 * Project:  Stevens Book - Big Library
 * Purpose:  This file implements function wrappers for network sys calls.
 * 	     These wrappers handle errors and the user does not need to know
 * 	     about these errors.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdlib.h>
#include <errno.h>

#include <sys/socket.h>
#include <sys/select.h>
#include <poll.h>

#include "./unp.h"

int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr) {
	int n;

again:
	if ((n = accept(fd, sa, salenptr)) < 0) {
#ifdef EPROTO
		if (errno == EPROTO || errno == ECONNABORTED)
#else
		if (errno == ECONNABORTED)
#endif
			goto again;
		else
			err_sys("accept error");
	}
	return n;
}

void Shutdown(int fd, int how) {
	if (shutdown(fd, how) < 0)
		err_sys("shutdown error");
}

int Socket(int family, int type, int protocol) {
	int n;
	if ((n = socket(family, type, protocol)) < 0)
		err_sys("socket error");
	return n;
}

void Connect(int fd, const struct sockaddr *sa, socklen_t salen) {
	if (connect(fd, sa, salen) < 0)
		err_sys("connect error");
}

void Bind(int fd, const struct sockaddr *sa, socklen_t salen) {
	if (bind(fd, sa, salen) < 0)
		err_sys("bind error");
}

void Getsockname(int fd, struct sockaddr *sa, socklen_t *salenptr) {
	if (getsockname(fd, sa, salenptr) < 0)
		err_sys("getsockname error");
}

void Getsockopt(int fd, int level, int optname, void *optval, socklen_t *optlenptr) {
	if (getsockopt(fd, level, optname, optval, optlenptr) < 0)
		err_sys("getsockopt error");
}

void Listen(int fd, int backlog) {
	char *ptr;

	if ((ptr = getenv("LISTENQ")) != NULL)
		backlog = atoi(ptr);

	if (listen(fd, backlog) < 0)
		err_sys("listen error");
}

#ifdef HAVE_POLL
int Poll(struct pollfd *fdarray, unsigned long nfds, int timeout) {
	int n;

	if ( (n = poll(fdarray, nfds, timeout)) < 0)
		err_sys("poll error");

	return n;
}
#endif

ssize_t Recvfrom(int fd, void *ptr, size_t nbytes, int flags, struct sockaddr *sa, socklen_t *salenptr) {
	ssize_t n;
	if ( (n = recvfrom(fd, ptr, nbytes, flags, sa, salenptr)) < 0)
		err_sys("recvfrom error");
	return n;
}

int Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
		struct timeval *timeout) {
	int n;
	if ( (n = select(nfds, readfds, writefds, exceptfds, timeout)) < 0)
		err_sys("select error");
	return n;
}

void Sendto(int fd, const void *ptr, size_t nbytes, int flags, const struct sockaddr *sa, socklen_t salen) {
	if (sendto(fd, ptr, nbytes, flags, sa, salen) != (ssize_t)nbytes)
		err_sys("sendto error");
}

void Setsockopt(int fd, int level, int optname, const void *optval, socklen_t optlen) {
	if (setsockopt(fd, level, optname, optval, optlen) < 0)
		err_sys("setsockopt error");
}
