/******************************************************************************
 *
 * Project:  Stevens Book - Big Library
 * Purpose:  This function writes line to a server and then gets the result and
 * 	     prints it. This function is used for echo server as a client.
 * 	     program.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "unp.h"

void str_cli(FILE *fp, int sockfd) {
	char sendline[MAXLINE], recvline[MAXLINE];

	while (Fgets(sendline, MAXLINE, fp) != NULL) {
		Writen(sockfd, sendline, strlen(sendline));

		if (Readline(sockfd, recvline, MAXLINE) == 0)
			err_quit("str_cli: server terminated prematurely");

		Fputs(recvline, stdout);
	}
}
