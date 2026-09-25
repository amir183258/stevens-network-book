/******************************************************************************
 *
 * Project:  Stevens Book - Non-blocking Sockets
 * Purpose:  This program is to check nonblocking sockets in accept().
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdlib.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#include "unp.h"

int main(int argc, char **argv) {
	int sockfd;
	struct linger ling;
	struct sockaddr_in servaddr;

	if (argc != 2)
		err_quit("usage: tcpcli <IPaddress>");

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

	ling.l_onoff = 1; // cause RST to be sent on close()
	ling.l_linger = 0;
	Setsockopt(sockfd, SOL_SOCKET, SO_LINGER, &ling, sizeof(ling));

	exit(0);
}
