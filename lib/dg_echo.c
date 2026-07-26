/******************************************************************************
 *
 * Project:  Stevens Book - Big Library
 * Purpose:  This functin reads datagrams from client socket then echoes it
 * 	     back to the client.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <sys/socket.h>

#include "unp.h"

void dg_echo(int sockfd, SA *pcliaddr, socklen_t clilen) {
	int n;
	socklen_t len;
	char mesg[MAXLINE];

	for ( ; ; ) {
		len = clilen;
		n = Recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);

		Sendto(sockfd, mesg, n, 0, pcliaddr, len);
	}
}
