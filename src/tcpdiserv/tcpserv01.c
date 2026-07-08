/******************************************************************************
 *
 * Project:  Stevens Book - Echo Server Project
 * Purpose:  This is the server file for echo server. It creates main function.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include "unp.h"

int main(int argc, char **argv) {
	int listenfd, connfd;
	pid_t childpid;

	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
	Listen(listenfd, LISTENQ);

	for ( ; ; ) {
		clilen = sizeof(cliaddr);
		connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);

		// child process
		if ( (childpid = Fork()) == 0) {
			Close(listenfd); // close listening socket
			str_echo(connfd); // process the request
			exit(0);
		}

		// parent closes connected socket
		Close(connfd);
	}

	return 0;
}
