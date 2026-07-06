/******************************************************************************
 *
 * Project:  Stevens Book - Big Library
 * Purpose:  This function use read() syscall to read from a socket file
 * 	     descriptor. 
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#include "unp.h"

ssize_t readn(int fd, void *vptr, size_t n) {
	size_t nleft;
	ssize_t nread;
	char *ptr;

	ptr = vptr;
	nleft = n;
	while  (nleft > 0) {
		if ( (nread = read(fd, ptr, nleft)) < 0) {
			if (errno == EINTR)
				nread = 0; // and call read() again
			else
				return -1;
		}
		else if (nread == 0)
			break; // EOF


		nleft -= nread;
		ptr += nread;
	}

	return n - nleft; // return >= 0
}

ssize_t Readn(int fd, void *ptr, size_t nbytes) {
	ssize_t n;

	if ( (n = readn(fd, ptr, nbytes)) < 0)
		err_sys("readn error");

	return n;
}
