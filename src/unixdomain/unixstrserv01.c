/******************************************************************************
 *
 * Project:  Stevens Book - Unix Domain Sockets
 * Purpose:  Unix domain stream protocol echo server.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <signal.h>
#include <errno.h>

#include "unp.h"

int main(int argc, char **argv) {
	int listenfd, connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_un cliaddr, servaddr;

	listenfd = Socket(AF_LOCAL, SOCK_STREAM, 0);

	unlink(UNIXSTR_PATH);
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sun_family = AF_LOCAL;
	strcpy(servaddr.sun_path, UNIXSTR_PATH);

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	void sig_chld(int signo);
	Signal(SIGCHLD, sig_chld);

	for ( ; ; ) {
		clilen = sizeof(cliaddr);
		if ( (connfd = accept(listenfd, (SA *) &cliaddr, &clilen)) < 0) {
			if (errno = EINTR)
				continue; // back to for
			else
				err_sys("accept error");
		}

		// child process
		if ( (childpid = Fork()) == 0) {
			Close(listenfd); // close listening socket
			str_echo(connfd); // process request
			exit(0);
		}
		Close(connfd);
	}
}
