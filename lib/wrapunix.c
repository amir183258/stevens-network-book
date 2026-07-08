/******************************************************************************
 *
 * Project:  Stevens Book - Big Library
 * Purpose:  These are wrapper functions for syscalls such as close or read.
 * 	     They handle error codes and the user does not need to know about
 * 	     these errors.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>

#include "./unp.h"

void Close(int fd) {
	if (close(fd) == -1)
		err_sys("close error");
}

pid_t Fork(void) {
	pid_t pid;

	if ( (pid = fork()) == -1)
		err_sys("fork error");
	return pid;
}

ssize_t Read(int fd, void *ptr, size_t nbytes) {
	ssize_t n;
	if ((n = read(fd, ptr, nbytes)) == -1)
		err_sys("read error");
	return n;
}

void Write(int fd, void *ptr, size_t nbytes) {
	if (write(fd, ptr, nbytes) != nbytes)
		err_sys("write error");
}
