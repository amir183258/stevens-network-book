/******************************************************************************
 *
 * Project:  Stevens Book - Echo Server Project
 * Purpose:  This is the client file for echo server. It creates main function.
 * 	     In this file, we use select() to manage socket and stdin. We use
 * 	     shutdown() here to process incoming reads.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <sys/select.h>

#include "unp.h"

void str_cli(FILE *fp, int sockfd) {
	int maxfdp1, stdineof;
	fd_set rset;
	char buf[MAXLINE];
	int n;

	stdineof = 0;
	FD_ZERO(&rset);
	for ( ; ; ) {
		if (stdineof == 0)
			FD_SET(fileno(fp), &rset);
		FD_SET(sockfd, &rset);
		maxfdp1 = max(fileno(fp), sockfd) + 1;
		Select(maxfdp1, &rset, NULL, NULL, NULL);

		// socket is readable
		if (FD_ISSET(sockfd, &rset)) {
			if ( (n = Read(sockfd, buf, MAXLINE)) == 0) {
				if (stdineof == 1)
					return; // normal termination
				else
					err_quit("str_cli: server terminated prematurely");
			}
			Write(fileno(stdout), buf, n);
		}

		// input is readable
		if (FD_ISSET(fileno(fp), &rset)) {
			if ( (n = Read(fileno(fp), buf, MAXLINE)) == 0) {
				stdineof = 1;
				Shutdown(sockfd, SHUT_WR); // send FIN
				FD_CLR(fileno(fp), &rset);
				continue;
			}
			Writen(sockfd, buf, n);
		}
	}
}
