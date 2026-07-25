/******************************************************************************
 *
 * Project:  Stevens Book - Exercises
 * Purpose:  This program checks SO_LINGER tcp option.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdio.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#include "unp.h"

int main(int argc, char **argv) {
	int sockfd;
	struct sockaddr_in servaddr;

	if (argc != 2)
		err_quit("usage: tcpcli01 <IP address>");

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

	str_cli(stdin, sockfd); // do it all
	
	// check SO_LINGER option
	struct linger linger_time;
	socklen_t len;

	linger_time.l_onoff = 1;
	linger_time.l_linger = 0;

	setsockopt(sockfd, SOL_SOCKET, SO_LINGER, &linger_time, len);
	puts("SO_LINGER set successfully");

	//exit(0);

	return 0;
}
