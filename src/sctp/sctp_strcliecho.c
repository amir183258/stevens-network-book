/******************************************************************************
 *
 * Project:  Stevens Book - Echo Server Project in SCTP
 * Purpose:  This function is a client which sends messages to all streams
 * 	     (0-9) to server and prints the echoed results from the server.
 * Author:   A. H. Ebrahimi <amirhossein183258 at gmail.com>
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/sctp.h>

#include "unp.h"

#define SCTP_MAXLINE 800

void sctpstr_cli_echoall(FILE *fp, int sock_fd, struct sockaddr *to, socklen_t tolen) {
	struct sockaddr_in peeraddr;
	struct sctp_sndrcvinfo sri;
	char sendline[SCTP_MAXLINE], recvline[SCTP_MAXLINE];
	socklen_t len;
	int rd_sz, i, strsz;
	int msg_flags;

	// declare functions
	int Sctp_recvmsg(int, void*, size_t, struct sockaddr*, socklen_t*,
			struct sctp_sndrcvinfo*, int*);
	int Sctp_sendmsg(int, void*, size_t, struct sockaddr*, socklen_t,
			uint32_t, uint32_t, uint16_t, uint32_t, uint32_t);

	bzero(sendline, sizeof(sendline));
	bzero(&sri, sizeof(sri));
	while (fgets(sendline, SCTP_MAXLINE - 9, fp) != NULL) {
		strsz = strlen(sendline);
		if (sendline[strsz - 1] == '\n') {
			sendline[strsz - 1] = '\0';
			strsz--;
		}
		for (i = 0; i < SERV_MAX_SCTP_STRM; i++) {
			snprintf(sendline + strsz, sizeof(sendline) - strsz,
					".msg.%d", i);
			Sctp_sendmsg(sock_fd, sendline, sizeof(sendline),
					to, tolen, 0, 0, i, 0, 0);
		}
		for (i = 0; i < SERV_MAX_SCTP_STRM; i++) {
			len = sizeof(peeraddr);
			rd_sz = Sctp_recvmsg(sock_fd, recvline, sizeof(recvline),
					(SA *)&peeraddr, &len, &sri, &msg_flags);
			printf("From str:%d seq:%d (asssoc:0x%x):",
					sri.sinfo_stream, sri.sinfo_ssn,
					(unsigned int)sri.sinfo_assoc_id);
			printf("%.*s\n", rd_sz, recvline);
		}
	}
}
