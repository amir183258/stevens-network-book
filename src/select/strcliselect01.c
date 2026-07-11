/******************************************************************************
 *
 * Project:  Stevens Book - Echo Server Project
 * Purpose:  This is the client file for echo server. It creates main function.
 * 	     In this file, we use select() to manage socket and stdin.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <sys/select.h>

#include "unp.h"

void str_cli(FILE *fp, int sockfd) {
	int maxfdp1;
	fd_set rset;
	char sendline[MAXLINE], recvline[MAXLINE];

	FD_ZERO(&rset);

	for ( ; ; ) {
		FD_SET(fileno(fp), &rset);
		FD_SET(sockfd, &rset);
		maxfdp1 = max(fileno(fp), sockfd) + 1;
		Select(maxfdp1, &rset, NULL, NULL, NULL);

		// socket is readable
		if (FD_ISSET(sockfd, &rset)) {
			if (Readline(sockfd, recvline, MAXLINE) == 0)
				err_quit("str_cli: server terminated prematurely");
			Fputs(recvline, stdout);
		}

		// input is readable
		if (FD_ISSET(fileno(fp), &rset)) {
			if (Fgets(sendline, MAXLINE, fp) == NULL)
				return; // all done
			Writen(sockfd, sendline, strlen(sendline));
		}
	}
}
