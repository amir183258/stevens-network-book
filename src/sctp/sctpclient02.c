/******************************************************************************
 *
 * Project:  Stevens Book - Echo Server Project in SCTP
 * Purpose:  This is the client file of the SCTP iterative server. In this
 * 	     file, the client aborts the association before closing.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdio.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/sctp.h>

#include "unp.h"

int main(int argc, char **argv) {
	int sock_fd;
	struct sockaddr_in servaddr;
	struct sctp_event_subscribe evnts;
	int echo_to_all = 0;
	char byemsg[10];

	if (argc < 2)
		err_quit("Missing host argument - use '%s host [echo] '\n", argv[0]);
	if (argc > 2) {
		printf("Echoing messages to all streams\n");
		echo_to_all = 1;
	}

	// function declaration
	void sctpstr_cli(FILE*, int, struct sockaddr*, socklen_t);
	void sctpstr_cli_echoall(FILE*, int, struct sockaddr*, socklen_t);
	int Sctp_sendmsg(int, void*, size_t, struct sockaddr*, socklen_t,
			uint32_t, uint32_t, uint16_t, uint32_t, uint32_t);

	sock_fd = Socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	bzero(&evnts, sizeof (evnts));
	evnts.sctp_data_io_event = 1;
	Setsockopt(sock_fd, IPPROTO_SCTP, SCTP_EVENTS, &evnts, sizeof(evnts));
	if (echo_to_all == 0)
		sctpstr_cli(stdin, sock_fd, (SA *) &servaddr, sizeof(servaddr));
	else
		sctpstr_cli_echoall(stdin, sock_fd, (SA *) &servaddr, sizeof(servaddr));

	strcpy(byemsg, "goodbye");
	Sctp_sendmsg(sock_fd, byemsg, strlen(byemsg), (SA *)&servaddr, sizeof(servaddr),
			0, SCTP_ABORT, 0, 0, 0);

	Close(sock_fd);

	return 0;
}
