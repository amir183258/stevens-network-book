/******************************************************************************
 *
 * Project:  Stevens Book - Echo Server Project
 * Purpose:  This is the client file for echo server. It creates main function.
 * 	     In this file, we create 4 socket connections to examine wait
 * 	     function.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdio.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#include "unp.h"

int main(int argc, char **argv) {
	int i, sockfd[5];
	struct sockaddr_in servaddr;

	if (argc != 2)
		err_quit("usage: tcpcli04 <IP address>");

	for (i = 0; i < 5; i++) {
		sockfd[i] = Socket(AF_INET, SOCK_STREAM, 0);

		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(SERV_PORT);
		Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

		Connect(sockfd[i], (SA *) &servaddr, sizeof(servaddr));
	}

	str_cli(stdin, sockfd[0]); // do it all

	return 0;
}
