/******************************************************************************
 *
 * Project:  Stevens Book - Advanced I/O
 * Purpose:  This is the dg_cli function with alarm to timeout recvfrom();
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/socket.h>

#include "unp.h"

static void sig_alrm(int);

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen) {
	int n;
	char sendline[MAXLINE], recvline[MAXLINE + 1];

	Signal(SIGALRM, sig_alrm);

	while (Fgets(sendline, MAXLINE, fp) != NULL) {
		Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);

		alarm(5);
		if ( (n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL)) < 0) {
			if (errno = EINTR)
				fprintf(stderr, "socket timeout\n");
			else
				err_sys("recvfrom error");
		}
		else {
			alarm(0);
			recvline[n] = 0; // null terminate
			Fputs(recvline, stdout);
		}
	}
}

static void sig_alrm(int signo) {
	return; // just interrupt the recvfrom()
}
