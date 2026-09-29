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

#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ioctl.h>

#include "./unp.h"

void* Calloc(size_t n, size_t size) {
	void *ptr;

	if ( (ptr = calloc(n, size)) == NULL)
		err_sys("calloc error");

	return ptr;
}

void Close(int fd) {
	if (close(fd) == -1)
		err_sys("close error");
}

int Fcntl(int fd, int cmd, int arg) {
	int n;

	if ( (n = fcntl(fd, cmd, arg)) == -1)
		err_sys("fcntl error");

	return n;
}

int Ioctl(int fd, int request, void *arg) {
	int n;
	if ( (n = ioctl(fd, request, arg)) == -1)
		err_sys("ioctl error");
	return n; // streamio of I_LIST returns value
}

pid_t Fork(void) {
	pid_t pid;

	if ( (pid = fork()) == -1)
		err_sys("fork error");
	return pid;
}

void* Malloc(size_t size) {
	void *ptr;
	if ( (ptr = malloc(size)) == NULL)
		err_sys("malloc error");
	return ptr;
}

ssize_t Read(int fd, void *ptr, size_t nbytes) {
	ssize_t n;
	if ((n = read(fd, ptr, nbytes)) == -1)
		err_sys("read error");
	return n;
}

pid_t Waitpid(pid_t pid, int *iptr, int options) {
	pid_t retpid;

	if ( (retpid = waitpid(pid, iptr, options)) == -1)
		err_sys("waitpid error");

	return retpid;
}

void Write(int fd, void *ptr, size_t nbytes) {
	if (write(fd, ptr, nbytes) != nbytes)
		err_sys("write error");
}
