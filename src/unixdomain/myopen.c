/******************************************************************************
 *
 * Project:  Stevens Book - Unix Domain Sockets
 * Purpose:  This function opens a file and returns a descriptor.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#include "unp.h"

int my_open(const char *pathname, int mode) {
	int fd, sockfd[2], status;
	pid_t childpid;
	char c, argsockfd[10], argmode[10];

	Socketpair(AF_LOCAL, SOCK_STREAM, 0, sockfd);

	// child process
	if ( (childpid = Fork()) == 0) {
		Close(sockfd[0]);
		snprintf(argsockfd, sizeof(argsockfd), "%d", sockfd[1]);
		snprintf(argmode, sizeof(argmode), "%d", mode);
		execl("./openfile", "openfile", argsockfd, pathname, argmode,
				(char *) NULL);
		err_sys("execl error");
	}

	// parent process - wait for the child to terminate
	Close(sockfd[1]); // close the end we don't use
	Waitpid(childpid, &status, 0);
	if (WIFEXITED(status) == 0)
		err_quit("child did not terminate");
	if ( (status = WEXITSTATUS(status)) == 0)
		Read_fd(sockfd[0], &c, 1, &fd);
	else {
		errno = status; // set errno value from child's status
		fd = -1;
	}

	Close(sockfd[0]);

	return fd;
}
