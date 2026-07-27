/******************************************************************************
 *
 * Project:  Stevens Book - Echo Server Project in UDP
 * Purpose:  This functions improves normal dg_cli function. It connects to
 * 	     the server and in this way, other packets can't pollute our
 * 	     client.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>

#include "unp.h"

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen) {
	int n;
	char sendline[MAXLINE], recvline[MAXLINE + 1];

	Connect(sockfd, (SA *) pservaddr, servlen);

	while (Fgets(sendline, MAXLINE, fp) != NULL) {
		Write(sockfd, sendline, strlen(sendline));

		n = Read(sockfd, recvline, MAXLINE);

		recvline[n] = 0; // null terminate
		Fputs(recvline, stdout);
	}
}
