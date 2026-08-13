/******************************************************************************
 *
 * Project:  Stevens Book - Advanced I/O
 * Purpose:  This is the dg_cli function that calls readable_timeo to set
 * 	     a timeout.
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

	while (Fgets(sendline, MAXLINE, fp) != NULL) {
		Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);

		if (Readable_timeo(sockfd, 5) == 0)
			fprintf(stderr, "sock timeout\n");
		else {
			n = Recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
			recvline[n] = 0; // null terminate
			Fputs(recvline, stdout);
		}
	}
}
