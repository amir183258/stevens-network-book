/******************************************************************************
 *
 * Project:  Stevens Book - Echo Server Project in UDP
 * Purpose:  This function reads datagrams from client and count them; Then it
 * 	     prints this count in stdout.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <signal.h>

#include "unp.h"

static void recvfrom_int(int);
static int count;

void dg_echo(int sockfd, SA *pcliaddr, socklen_t clilen) {
	socklen_t len;
	char mesg[MAXLINE];

	Signal(SIGINT, recvfrom_int);

	for ( ; ; ) {
		len = clilen;
		Recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);

		count++;
	}
}

static void recvfrom_int(int signo) {
	printf("\nreceived %d datagrams\n", count);
	exit(0);
}
