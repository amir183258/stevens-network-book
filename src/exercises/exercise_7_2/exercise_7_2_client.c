/******************************************************************************
 *
 * Project:  Stevens Book - Exercises
 * Purpose:  This program returns buffer sizes and MSS of a client app.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdio.h>

#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

#include "unp.h"

void print_stats(int fd) {
	if (fd < 0) {
		puts("invalid fd");
		return;
	}

	int rcv_buf_size;
	int snd_buf_size;
	int mss;
	socklen_t len; // for socket options

	if (getsockopt(fd, SOL_SOCKET, SO_RCVBUF, &rcv_buf_size, &len) < 0)
		err_sys("getsockopt error");
	else
		printf("Receive buffer size: %d\n", rcv_buf_size);

	if (getsockopt(fd, SOL_SOCKET, SO_SNDBUF, &snd_buf_size, &len) < 0)
		err_sys("getsockopt error");
	else
		printf("Send buffer: %d\n", snd_buf_size);

	if (getsockopt(fd, IPPROTO_TCP, TCP_MAXSEG, &mss, &len) < 0)
		err_sys("getsockopt error");
	else
		printf("MSS before: %d\n", mss);
}

int main(int argc, char **argv) {
	int sockfd, n;
	char recvline[MAXLINE + 1];
	struct sockaddr_in servaddr;

	if (argc != 2)
		err_quit("usage: a.out <IPaddress>");

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	// check socket MSS and buffer sizes before connect
	puts("Before using connect(): ");
	print_stats(sockfd);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);	/* daytime server */
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		err_quit("inet_pton error for %s", argv[1]);

	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
		err_sys("connect error");

	// check socket MSS and buffer sizes after connect
	puts("After using connect: ");
	print_stats(sockfd);

	while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;	/* null terminate */
		if (fputs(recvline, stdout) == EOF)
			err_sys("fputs error");
	}
	if (n < 0)
		err_sys("read error");
	
	return 0;
}
