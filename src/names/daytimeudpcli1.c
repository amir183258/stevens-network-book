/******************************************************************************
 *
 * Project:  Stevens Book - Day Time Client in DNS Chapters
 * Purpose:  This is UDP daytime client using udp_client function in lib.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>

#include "unp.h"

int main(int argc, char **argv) {
	int sockfd, n;
	char recvline[MAXLINE + 1];
	socklen_t salen;
	struct sockaddr *sa;

	if (argc != 3)
		err_quit("usage daytimeudpcli1 <hostname/IPaddress> <service/port#>");

	sockfd = Udp_client(argv[1], argv[2], (SA **) &sa, &salen);

	printf("sending to %s\n", Sock_ntop_host(sa, salen));

	Sendto(sockfd, "", 1, 0, sa, salen); // send 1-byte datagram
	n = Recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
	recvline[n] = '\0'; // null terminate

	return 0;
}
