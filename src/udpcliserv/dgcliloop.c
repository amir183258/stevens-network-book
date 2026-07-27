/******************************************************************************
 *
 * Project:  Stevens Book - Echo Server Project in UDP
 * Purpose:  This function sends 2000 datagrams of 1400 bytes to the server.
 * 	     We use this function to show lack of flow control in UDP.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdio.h>

#include <sys/socket.h>

#include "unp.h"

#define NDG 	2000 	// datagrams to send
#define DGLEN	1400	// length of each datagram

void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen) {
	int i;
	char sendline[DGLEN];

	for (i = 0; i < NDG; i++)
		Sendto(sockfd, sendline, DGLEN, 0, pservaddr, servlen);
}
